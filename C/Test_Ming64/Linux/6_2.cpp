#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

/*
    信号通信编程练习：
        在进程中为SIGSTOP注册处理函数，并向该进程发送SIGSTOP(CTRL+Z)
        观察注册的函数是否被调用
*/

void sig(int x)          // 信号处理函数
{
    printf("这是SIGSTOP信号对应的信号处理函数\n");
    exit(0);
}

int main()
{
    signal(SIGSTOP,sig);
    printf("若输入SIGSTOP信号，会执行自定义的信号处理函数，否则睡眠15s\n");
    sleep(15);
    printf("程序睡醒了！\n");
}