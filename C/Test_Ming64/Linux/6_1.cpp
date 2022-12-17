#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

/*
    无名管道通信练习：
        创建两个无名管道，实现父子进程双向通信
*/

int main()
{
    pid_t pid;
    char buff_r[100];                   // 内存
    int number;                         // 读取到的字符数量
    memset(buff_r,0,sizeof(buff_r));    // 给buff_r分配内存
    int pipe_1[2],pipe_2[2];            // 管道参数数组，[0]为读端，[1]为写端
    char data_1[]="这是父进程写入pipe_1的数据。";
    char data_2[]="这是子进程写入pipe_2的数据。";

    // 先创建管道
    printf("开始创建无名管道……\n");
    if(pipe(pipe_1)<0) printf("无名管道1创建创建失败\n");
    if(pipe(pipe_2)<0) printf("无名管道2创建创建失败\n");
    else printf("无名管道创建成功！\n\n");

    // 后创建子进程
    pid = fork();
    if(pid<0) printf("子进程创建失败！\n");
    else if(pid==0)
    {
        printf("正在执行子进程……\n");
        // 读取父进程写入pipe_1的数据
        close(pipe_1[1]);
        sleep(2);                           // 等待父进程的写入动作
        number = read(pipe_1[0],buff_r,strlen(buff_r));
        if(number>0)
            printf("父进程写入pipe_1的数据是：%s\n",buff_r);
        else printf("子进程读取来自父进程的数据失败！\n");
        close(pipe_1[0]);
        // 向pipe_2写数据
        close(pipe_2[0]);
        if(write(pipe_2[1],data_2,strlen(data_2))>0)
            printf("子进程向pipe_2写入数据成功，写入内容：%s\n",data_2);
        close(pipe_2[1]);
        printf("子进程执行完毕\n");
        exit(0);
    }
    else
    {
        printf("正在执行父进程……\n");
        // 向pipe_1写数据
        close(pipe_1[0]);
        if(write(pipe_1[1],data_1,strlen(data_1))>0)
            printf("父进程向pipe_1写入数据成功，写入内容：%s\n",data_1);
        close(pipe_1[1]);
        waitpid(pid,NULL,0);               // 等待子进程结束
        // 读取子进程写入pipe_2的数据
        close(pipe_2[1]);
        number = read(pipe_2[0],buff_r,strlen(buff_r));
        if(number>0)
            printf("子进程写入pipe_2的数据是：%s\n",buff_r);
        else printf("父进程读取来自子进程的数据失败！\n");
        close(pipe_2[0]);
        exit(0);
    }
}