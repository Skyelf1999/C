#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>

/*
    基于TCP的编程练习
        服务器发送数据，客户端接收数据；
        客户端从键盘输入待发送数据，服务器接收数据
    服务器设计步骤
        创建socket，绑定信息，设置侦听，接受连接，收发数据
*/

#define portnumber 1234             // 端口号

int main()
{
    printf("开始运行服务器程序……\n\n");
    int sockfd,new_fd;              // socket文件描述符和连接的客户端编号
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sin_size;                   // 数据大小
    char hello[]="请输入要发送至服务器的数据\n";
    char buffer[1024];
    int bytes;

    // 创建socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("socket创建错误\n");
        exit(0);
    }
    else printf("socket创建成功\n");

    // 完善服务器地址信息,设置服务器协议地址簇
    bzero(&server,sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;    // IPV4
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(portnumber);

    // 绑定信息
    if(bind(sockfd,(struct sockaddr *)(&server),sizeof(struct sockaddr))==-1)
    {
        printf("绑定端口信息错误\n");
        exit(0);
    }

    // 设置最大连接数
    if(listen(sockfd,3)==-1)
    {
        printf("设置侦听数错误\n");
        exit(0);
    }

    // 服务器阻塞，直到建立连接
    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);
         
        fprintf(stderr,"服务器接受连接",inet_ntoa(client.sin_addr));
        // 收发数据
        if(write(new_fd,hello,strlen(hello))==-1)
        {
            printf("向客户端发送数据错误\n");
            exit(1);
        }
        printf("等待客户端发送数据……\n");
        sleep(10);
        if((bytes = read(new_fd,buffer,1024))==-1)
        {
            printf("从客户端读取数据失败\n");
            exit(1);
        }
        buffer[bytes]='\0';
        printf("客户端发送的信息是：%s\n",buffer);
        
        close(new_fd);
    }
}