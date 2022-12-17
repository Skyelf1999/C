#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// 全局变量
#define portnumber 2233             // 端口号
#define maxUser 10                  // 最大连接/侦听数
#define maxBuffSize 1024            // 最大消息缓存空间大小
#define endcmd "end"                // 客户端断开指令
pthread_t pid_send,pid_recv;        // 线程id
int clientSocket_fd;                // socket文件描述符
char name[20],pw[20];               // 用户名、密码
//***************************
struct MyStruct
{
    char name[20];
    char pw[20];
};
MyStruct login_mess;
//***************************
struct client_recv_buff
{
    char from_name[20];			// 来源
	int  result;				// 从服务器返回的结果
    char question[50];			// 密保问题
	char answer[50];			// 密保答案
	char passward[20];			// 密码
	int  online_num;			// 在线人数
	char num[20][20];			// 在线人名
	char msg[200];				// 发送、接收消息
	char file_name[20];			// 文件名
	char file[2048];			// 发送文件存的数据
	char moto[300];				// 个性签名
	int  likes;					// 点赞数
	int  vip;					// 是否是会员
	char e_s;					// 确认发送的表情
	char p_s;					// 确认发送的常用语
};
struct client_send_buff
{
    char name[20];				// 名字
	char toname[20];			// 接收人
    int  cmd;					// 提取操作符
	char account[20];			// 账号
	char passward[20];			// 密码
    char question[50];			// 密保问题
	char answer[50];			// 密保答案
	char msg[200];				// 发送、接收消息
	char file_name[20];			// 文件名
	char file[2048];			// 发送文件存的数据
    char moto[300];				// 个性签名
    int  likes;					// 点赞数
    int  vip;					// 是否是会员
	char e_s;					// 确认发送的表情
	char p_s;					// 确认发送的常用语
};

client_recv_buff *recv;
client_send_buff *send;

///////////////////////////////////////////////////////////////////////////////////////////////////////


int login()
{
    int byte;
    char buff[maxBuffSize];
    
    // 发送用户名&密码
    printf("请输入用户名：");
    scanf("%s",name);
    printf("请输入密码：");
    scanf("%s", pw);

    while(1)
    {
        strcpy(login_mess.name, name);
        strcpy(login_mess.pw, pw);
        byte = write(clientSocket_fd,&login_mess,maxBuffSize);
        // byte = write(clientSocket_fd,name,maxBuffSize);
        if(byte == -1) 
        { 
            printf("\n<发送失败，请重新发送>\n"); 
            continue;
        }
        else{ printf("用户名发送成功\n"); }
        read(clientSocket_fd,buff,maxBuffSize-1);
        if(strcmp("登录成功！",buff)==0)
        {
            printf("登陆成功！\n");
            return 1;
        }
        else if(strcmp("用户不存在或密码错误！请再次输入！\n",buff)==0)
        {
            printf("%s",buff);
            continue;
        }
        else if(strcmp("错误次数过多！请重新连接服务器！\n",buff)==0)
        {
            printf("%s",buff);
            return 0;
        }
    }
    return 0;
}



// 接受信息线程函数
void *pthread_recv(void* arg)
{
    int read_byte;                 // 写入的消息大小
    char buffer[maxBuffSize];      // 消息缓存

    // 等待从服务器接收数据
    while(1)
    {
        read_byte = read(clientSocket_fd,buffer,maxBuffSize-1);
        if(read_byte == -1)
        {
            printf("\n<从服务器读取数据失败>\n");
            continue;
        }
        buffer[read_byte] = 0;       // 添加结束符号
        printf("来自服务器：%s\n")
    }
}


// 发送信息线程函数
void *pthread_send(void* arg)
{
    int write_byte;                 // 写入的消息大小
    char buffer[maxBuffSize];       // 消息缓存

    while(1)
    {
        printf("\n请输入此次发送的消息：");
        scanf("%s",buffer);
        if(strcmp(endcmd,buffer)==0)
        {
            write(clientSocket_fd,buffer,maxBuffSize);
            printf("\n与服务器断开连接\n");
            sleep(1);
            break;
        }
        write_byte = write(clientSocket_fd,buffer,maxBuffSize);
        if(write_byte == -1)
        {
            printf("\n<发送失败>\n");
        }
    }
}


int main(int argc,char *argv[])
{
    printf("开始运行客户端程序……\n\n");
    // 局部变量 ----------------------------------------
    int x;
    int choice;                     // 主界面功能选择
    struct sockaddr_in server;      // 服务器地址
    // 使用hostname查询host，用域名/主机名获取ip地址
    struct hostent *host;
    if(argc>1)
    { host = gethostbyname(argv[1]); }
    //-------------------------------------------------//


    // 1.创建socket ----------------------------------------
    clientSocket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket_fd==-1)
    {
        printf("socket创建错误\n");
        exit(0);
    }
    else printf("socket创建成功\n");
    //-------------------------------------------------//


    // 2.设置/获取目标服务器协议地址簇 ----------------------------------------
    printf("开始设置目标服务器协议地址簇………………\n");
    memset(&server,0,sizeof(struct sockaddr));
    server.sin_family = AF_INET;    // AF_INET决定了要用IPV4地址
    // server.sin_addr = *((struct in_addr *)host->h_addr);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(portnumber);            // 端口号，htos将16位主机字符顺序转换成网络字符顺序
    printf("目标服务器协议地址簇设置成功\n");
    //-------------------------------------------------//


    // 3.connect()请求连接 ----------------------------------------
    printf("正在请求连接…………………\n");
    if(connect(clientSocket_fd,(struct sockaddr *)(&server),sizeof(struct sockaddr))==-1)
    {
        printf("请求连接失败\n");
        exit(1);
    }
    printf("请求连接成功\n");
    //-------------------------------------------------//


    printf("\n\n<---------------------- 下面进入通信环节 ---------------------->\n");

    x = login();                    // 进行登录
    if(x==1)                        // 登陆成功了
    {
        // 利用多线程，同时从多个客户端接收数据
        pthread_create(&pid_send,NULL,pthread_send,NULL);
        pthread_create(&pid_recv,NULL,pthread_recv,NULL);
        // 5.结束 ----------------------------------------
        pthread_join(pid_send,NULL);
        close(clientSocket_fd);
        exit(0);
        //-------------------------------------------------//
    }
    else                            // 登陆失败，直接关闭客户端
    {
        // 5.结束 ----------------------------------------
        close(clientSocket_fd);
        exit(0);
        //-------------------------------------------------//
    }
}
