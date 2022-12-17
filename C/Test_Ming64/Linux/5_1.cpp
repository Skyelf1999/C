#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/*
    创建子进程，父进程需要等待子进程运行结束后才能执行
*/

int main()
{
    pid_t pid;
    int i=0;
    printf("本进程ID：%d\n",getpid());

    pid = vfork();   // 创建子进程
    if(pid<0)
        printf("子进程创建失败！\n");
    else if(pid==0)
        {
            printf("现在执行的是子进程，进程ID：%d\n",getpid());
            while(i++<10)
            {
                printf("这是子进程的第%d次循环\n",i);
                if(i==7) exit(0);
            }
        }
    else
        {
            printf("现在执行的是父进程，进程ID：%d\n",getpid());
            while(i++<10)
            {
                printf("这是父进程的第%d次循环\n",i);
            }
        } 
}