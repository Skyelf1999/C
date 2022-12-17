#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
    消息队列编程练习：
        创建一个消息队列，实现向队列中读写数据
        并对比读写结果是否一样
*/

#define msg_len 512

struct message                      // 消息结构体
{
    long int type;
    char msg[msg_len];
};

int main()
{
    // 创建消息队列
    int msgid = msgget((key_t)1234,0666|IPC_CREAT); 
    if(msgid==-1)
    {
        printf("消息队列创建失败\n");
        exit(0);
    }

    struct message msg;
    char buff[1024];
    int i=0;

    while(1)                        // 从消息队列读取数据，读取到end时退出循环
    {
        if(msgrcv(msgid,(void*)&msg,1024,1,0)==-1)
        {
            printf("接收消息失败\n");
            exit(0);
        }
        i++;
        printf("接收到的第%d条消息是：%s",i,msg.msg);
        if(strncmp(buff,"end",3)==0) break;
    }
    msgctl(msgid,IPC_RMID,0)==-1;   // 删除消息队列
}