#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
    1. 有一个int型全局变量g_Flag初始值为0；
    2. 在主线程中起动线程1，打印“this is thread1”，并将g_Flag设置为1；
    3. 在主线程中启动线程2，打印“this is thread2”，并将g_Flag设置为2；
    4. 线程1需要在线程2退出后才能退出。
*/ 

pthread_t pid1,pid2;
int g_Flag = 0;

void *pthread2(void* arg)
{
    printf("this is thread2\n");
    g_Flag = 2;
    printf("线程2中，令 g_Flah = %d\n",g_Flag);
    pthread_exit(NULL);
}

void *pthread1(void* arg)
{
    printf("this is thread1\n");
    g_Flag = 1;
    printf("线程1中，令 g_Flah = %d\n",g_Flag);
    pthread_join(pid2,NULL);
    printf("线程2已退出，现在退出线程1\n");
    pthread_exit(NULL);
}

int main()
{
    printf("开始执行主线程……");
    pthread_create(&pid1,NULL,pthread1,NULL);
    pthread_create(&pid2,NULL,pthread2,NULL);
    pthread_join(pid1,NULL);
    printf("线程1退出成功\n");
}

