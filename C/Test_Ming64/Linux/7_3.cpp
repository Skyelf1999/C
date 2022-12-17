#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
    创建线程
    使用pthread_cleanup_push和pthread_cleanup_pop进行退出保护
*/ 

pthread_t pid;

void clean(void *arg)
{
    printf("清除函数：%s\n",(char*)arg);
}

void *pthread(void* arg)
{
    printf("正在执行子线程……\n");
    pthread_cleanup_push(clean,"先入后出");
    pthread_cleanup_push(clean,"后入先出");
    printf("push完毕\n");
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}

int main()
{
    pthread_create(&pid,NULL,pthread,NULL);
    pthread_join(pid,NULL);
    printf("线程退出成功\n");
}

