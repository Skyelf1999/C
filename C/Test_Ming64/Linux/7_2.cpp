#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
    创建线程
    比较return(); pthread_exit; exit(0)
*/ 

pthread_t pid;                          // 线程id
int choice;

void *pthread(void* args)
{
    printf("请选择线程的退出方式：1.return(); 2.pthread_exit; 3.exit(0)\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            printf("使用return()退出\n\n");
            return (void*)1;
        case 2:
            printf("使用pthread_exit退出\n\n");
            pthread_exit((void*)2);
        case 3:
            printf("使用exit(0)退出\n\n");
            exit(0);
    }
}

int main()
{
    void *x;
    pthread_create(&pid,NULL,pthread,NULL);
    pthread_join(pid,&x);
    if(*(int*)x==1) printf("使用return()退出线程成功\n");
    else if(*(int*)x==2) printf("使用pthread_exit退出线程成功\n");
}
