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

    while(1)                        // 向消息队列写入数据，输入end即可退出循环
    {
        printf("请输入要写入的数据：\n\t");
        fgets(buff,1024,stdin);     // 从键盘读数据暂存在buff
        msg.type = 1;
        strcpy(msg.msg,buff);       // 将从键盘读到的数据存入消息
        if(msgsnd(msgid,(void*)&msg,msg_len,0)==-1)
        {
            printf("发送消息失败\n");
            exit(0);
        }
        if(strncmp(buff,"end",3)==0) break;
        sleep(1);
    }
}