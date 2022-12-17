#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
    创建线程，并向该线程处理函数传递整形数和字符型数
    父进程等到线程结束后才继续运行
*/ 

pthread_t pid;                          // 线程id
pthread_key_t key;                      // 指向键值的指针
struct data_struct
{
    int x;
    char c;
}*data;

void *pthread(void* args)
{
    printf("正在执行创建的线程……\n");
    data_struct *pack = (data_struct*)args;
    printf("从主进程中传递的数据 x=%d；c=%c\n",pack->x,pack->c);
    sleep(2);
    printf("线程休眠结束\n");
}

int main()
{
    // 传递数据包赋值
    printf("请输入待传递的整形数：");
    scanf("%d",&data->x);
    printf("请输入待传递的字符型数：");
    scanf("%c",&data->c);
    
    pthread_create(&pid,NULL,pthread,(void*)data);
    pthread_join(pid,NULL);               // 等待线程结束
    printf("父进程结束\n");
    exit(0);
}