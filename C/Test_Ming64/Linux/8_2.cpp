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
    客户端设计步骤
        创建socket，设置连接对象信息，连接服务器，收发数据
*/

#define portnumber 1234             // 端口号

int main(int argc,char *argv[])
{
    printf("开始运行客户端程序……\n\n");
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server;
    struct hostent *host;
    int bytes;

    // 使用hostname查询host，用域名/主机名获取ip地址
    host = gethostbyname(argv[1]);

    // 创建socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("socket创建错误\n");
        exit(0);
    }
    else printf("socket创建成功\n");
    
    // 设置服务器端的信息
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(portnumber);
    server.sin_addr = *((struct in_addr *)host->h_addr);
    printf("连接对象服务器信息填写完毕\n");

    // 连接服务器
    if(connect(sockfd,(struct sockaddr *)(&server),sizeof(struct sockaddr))==-1)
    {
        printf("请求连接失败\n");
        exit(1);
    }
    // 收发数据
    if((bytes = read(sockfd,buffer,1024))==-1)
    {
        printf("从服务器端读取数据失败\n");
        exit(1);
    }
    buffer[bytes]='\0';
    printf("服务器发送的信息是：%s\n",buffer);
    printf("输入要向服务器发送的数据：");
    fgets(buffer,1024,stdin);                   // 从键盘读数据暂存在buff
    if(write(sockfd,buffer,strlen(buffer))==-1)
    {
        printf("向客户端发送数据错误\n");
        exit(1);
    }

    close(sockfd);
    exit(0);
}
