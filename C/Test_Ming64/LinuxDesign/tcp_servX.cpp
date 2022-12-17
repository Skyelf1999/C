#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


// 全局变量与宏定义
#define portnumber 2233             // 端口号
#define maxUser 10                  // 最大连接/侦听数
#define maxBuffSize 1024            // 最大消息缓存空间大小
#define endcmd "end"                // 服务器关闭指令
pthread_t pid[maxUser];             // 线程id
struct sockaddr_in server;          // 服务器地址结构体 
struct sockaddr_in client;          // 客户端地址结构体
typedef struct                      // 存放已登录用户的信息
{ 
    int number; int state; int client_fd; char name[20]; char given_pw[20];
}user;

struct MyStruct
{
    char name[20];
    char pw[20];
};
MyStruct uni_buffer;
user unsure_user;                   // 在成功登陆前，先用unsure_user存放用户信息

struct List             
{
    char known_name[20];
    char correct_pw[20];
};
List list[20];                      // 用于存储读取的已注册用户信息，假定最多20个已注册用户

// 用i存储总连接数，用available存储可连接空位信息，互不干扰
int total = 0;                      // 目前已连接的客户端数量
user available[maxUser];            // 记录可连接空位,0为空



///////////////////////////////////////////////////////////////////////////////////////////////////////


// 初始化在线列表
void client_list_initial()
{
    printf("初始在线列表：\n");
    for(int k=0;k<maxUser;k++)
    {
        available[k].state = 0;
        available[k].client_fd = 0;
        available[k].number = k;
        strcpy(available[k].name,"xxx");
	    printf("%d：%s\n",available[k].number+1,available[k].name);
    }
}


// 显示在线列表
void client_list_show()
{
    printf("\n<--当前在线列表-->\n");
    for(int k=0;k<maxUser;k++)
    {
        printf("%d：%s\n",available[k].number+1,available[k].name);
    }
}


// 读取已注册用户的信息
void get_information()
{
    // 从用户名密码文件读取用户信息存入结构体数组
    // （用户名与密码文件还未创建）
    FILE* fd1 = fopen("./data/users.txt", "r"); // 读取存放用户名和密码的文件
    if (fd1 == NULL)
    {
        printf("用户名密码文件打开失败\n");
        exit(1);
    }
    else
    {
        printf("用户名密码文件打开成功\n");
    }
            
    for (int i = 0; i < 20; i++)
    {
        char uname[20];
        char upw[20];
        fscanf(fd1, "%s%s", uname, upw);
        strcpy(list[i].known_name, uname);
        strcpy(list[i].correct_pw, upw);
    }
    fclose(fd1);            //关闭文件描述符
}


// 登录成功时，输出相关信息，并用available记录
void client_register()
{
    // 输出基本信息
    strcpy(available[j].name, unsure_user.name);
    printf("\n客户端%d的IP地址：%s，用户名为：%s\n", available[j].number+1, inet_ntoa(client.sin_addr), available[j].name);
    
    // 存入密码、client_fd，改变位置空闲状态
    strcpy(available[j].given_pw, unsure_user.given_pw);
    available[j].client_fd = unsure_user.client_fd;
    available[j].state = 1;
    
    // 已连接客户端总数+1
    total++;
}


// 尝试登录
void try_login(int j)
{
    int byte,i;
    int try_time;

    // 多次尝试登录，若错误次数过多则拒绝客户端的登录,目前可尝试3次
    for (try_time = 0; try_time < 3; try_time++)
    {
        // 获取待登录用户的用户名、密码
        byte = read(unsure_user.client_fd, uni_buffer, maxBuffSize - 1);
        if (byte > 0)
        {
            strcpy(unsure_user.name, uni_buffer.name);
            strcpy(unsure_user.given_pw, uni_buffer.pw);
        }
        // 根据已注册用户信息，判断密码正确与否
        for (i = 0; i < 20; i++)
        {
            if (0 == strcmp(list[i].known_name, unsure_user.name) && 0 == strcmp(list[i].correct_pw, unsure_user.given_pw))
            {
                write(unsure_user.client_fd, "登录成功！", maxBuffSize);
                // 调用函数：登录成功时，输出相关信息，并用available记录
                client_register();
                // 利用多线程，同时从多个客户端接收数据
                pthread_create(&pid[j], NULL, pthread_recv, (void*)&available[j]);
                return;
            }
        }
        write(unsure_user.client_fd, "用户不存在或密码错误！请再次输入！\n", maxBuffSize);
    }
    // 循环结束，超过了最大尝试次数
    write(unsure_user.client_fd, "错误次数过多！请重新连接服务器！\n", maxBuffSize);
    return;
}


// 服务器接受信息线程函数
void *pthread_recv(void* arg)
{
    printf("\n<--正在执行服务器接受信息线程函数-->");
    user* x = (user*)arg;           // 获取现在连接的客户端信息，用x存储，不影响主函数中的变量
    int read_byte;                  // 读到的消息的大小（用于判断是否读取成功）
    char buffer[maxBuffSize];       // 消息缓存

    // 等待从客户端接收数据
    while(1)
    {
        // 从线程对应的客户端读信息
        read_byte = read(available[x->number].client_fd,buffer,maxBuffSize-1);
        if(read_byte == -1)
        {
            printf("\n从客户端读取数据失败\n");
            continue;
        }
        else if(read_byte == 0) { continue; }
        buffer[read_byte] = 0;       // 添加结束符号

        // 如果客户端断开连接 ----------------------------------------
        if(strcmp(endcmd,buffer)==0)
        {
            printf("\n客户端%d与服务器断开连接\n",x->number+1);
            // 在available[maxUser]中删除对应的客户端：设置对应位置为空，客户端总数-1
            available[x->number].state = 0;
            total--;                    
            break;
        }
        //-------------------------------------------------//

        // 如果客户端是正常消息 ----------------------------------------
        printf("\n-->接收到来自%s的数据：%s",x->name,buffer);
        //-------------------------------------------------//
        
    }
}


int main()
{
    printf("开始运行服务器程序……\n\n");
    // 局部变量 ----------------------------------------
    int i,j,k;                          // 辅助变量
    int read_byte;
    char cmd[10];
    int serverSocket_fd;            // socket文件描述符
    int addr_size = sizeof(struct sockaddr_in);  // 协议地址的长度（字节数）      
    char name_buffer[20];           // 用户名缓存   
    //-------------------------------------------------//

    // 调用函数：初始化在线列表
    client_list_initial();

    // 1.创建socket ----------------------------------------
    // 协议族：AF_INET，流式套接字，选择流式套接字对应的默认协议TCP
    serverSocket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket_fd==-1)
    {
        printf("socket创建错误\n");
        exit(0);
    }
    else printf("socket创建成功\n");
    //-------------------------------------------------//


    // 2.设置服务器协议地址簇 ----------------------------------------
    // bzero(&server,sizeof(struct sockaddr_in));
    memset(&server,0,sizeof(struct sockaddr));
    server.sin_family = AF_INET;    // AF_INET决定了要用IPV4地址
    server.sin_addr.s_addr = htonl(INADDR_ANY);     // 协议特定地址（IP地址），可在控制台利用ipconfig查看
    server.sin_port = htons(portnumber);            // 端口号，htos将16位主机字符顺序转换成网络字符顺序
    // printf("sin_family:%s \n",server.sin_family);
    // printf("sin_port:%s \n",server.sin_port);
    //-------------------------------------------------//


    // 3.bind()将服务器地址信息（IP地址、端口等）与socket绑定 ----------------------------------------
    if(bind(serverSocket_fd,(struct sockaddr *)(&server),sizeof(server))==-1)
    {
        printf("绑定服务器信息错误\n");
        exit(0);
    }
    //-------------------------------------------------//


    // 4.listen()设置监听的最大并发连接请求数maxUser ----------------------------------------
    if(listen(serverSocket_fd,maxUser)==-1)
    {
        printf("设置侦听错误\n");
        exit(0);
    }
    //-------------------------------------------------//


    printf("\n\n<---------------------- 下面进入通信环节 ---------------------->\n");


    // 5.accept()接收客户端连接请求，之后进行通信（需要循环进行） ----------------------------------------
    while(1)
    {
        // 调用函数：输出在线列表
        client_list_show(); 

        if(total<maxUser)               // 若连接数还有剩余，则寻找空位，接受客户端的连接请求
        {
            // 寻找可连接空位，空位用j记录
            for(j = 0;j<maxUser;j++)
            {
                if(available[j].state==0)
		        {
		            printf("位置%d空闲，可用于连接\n",available[j].number+1);
		            break;
		        }
            }

            // 调用函数：读取已注册用户的信息
            get_information();      
            
            // 接受连接
            // available[j].client_fd = accept(serverSocket_fd,(struct sockaddr *)(&client),&addr_size);
            unsure_user.client_fd = accept(serverSocket_fd, (struct sockaddr*)(&client), &addr_size);
            if (unsure_user.client_fd == -1)
            {
                printf("\n第%d次接受连接失败\n");
                continue;
            }
            
            // 调用函数：多次尝试登录，若错误次数过多则拒绝客户端的登录,目前可尝试3次
            try_login(j);
        }

        // 判断是否还有连接的客户端
        judge:
        if(i==0)
        {
            printf("\n现在以无连接的客户端，是否关闭服务器？如需关闭请输入“end”：\n");
            scanf("%s",cmd);
            if(strcmp(endcmd,cmd)==0)
            {
                printf("\n服务器关闭\n");
                
            }
        }
    }
    //-------------------------------------------------//


    // 6.结束 ----------------------------------------
    end:
    close(serverSocket_fd);
    exit(0);
    //-------------------------------------------------//
}