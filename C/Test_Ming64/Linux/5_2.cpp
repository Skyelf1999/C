#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/*
    编程说明fork()与vfork()的区别
    1.fork()函数子进程拷贝父进程的数据段、堆栈段，而vfork()是直接共享
    2.因此，vfork()创建的子进程在exec()或exit()前，父进程不可被调度运行
    3.fork()函数的父子进程的执行顺序不确定，而vfork()保证子进程优先运行
*/

int main()
{
    pid_t grand,father,son;     // 分别存放爷爷、父、子的pid
    int i=0,x=0,choice;
    printf("正在执行爷爷，ID：%d，下面开始展示vfork与fork的区别\n",getpid());

    printf("请选择使用fork还是vfork，1 fork；2 vfork\n");
    scanf("%d",&choice);

    if(choice==1)
    {
        father = fork();   // 创建子进程
        if(father<0) printf("子进程创建失败！\n");
        else if(father==0)
            {
                printf("现在执行的是子进程，进程ID：%d\n",getpid());
                while(i++<5)
                {
                    printf("这是子进程的第%d次循环\n",i);
                    x+=2;
                }
            }
        else
            {
                printf("现在执行的是父进程，进程ID：%d\n",getpid());
                while(i++<3)
                {
                    printf("这是父进程的第%d次循环\n",i);
                    x+=1;
                }
            }
        printf("使用fork，x=%d\n",x);
    }
    else if(choice==2)
    {
        father = vfork();   // 创建子进程
        if(father<0) printf("子进程创建失败！\n");
        else if(father==0)
            {
                printf("现在执行的是子进程，进程ID：%d\n",getpid());
                while(i++<5)
                {
                    printf("这是子进程的第%d次循环\n",i);
                    x+=2; 
                }
                exit(0);
            }
        else
            {
                printf("现在执行的是父进程，进程ID：%d\n",getpid());
                while(i++<3)
                {
                    printf("这是父进程的第%d次循环\n",i);
                    x+=1;
                }
            }
        printf("使用vfork，x=%d\n",x);
    }
    else printf("选择错误！\n");
}