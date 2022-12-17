#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/*
    1.以字符串的形式显示本地时间
    2.测试一段循环代码的运行时间并显示
*/

int gettimeofday(struct timeval *tv,struct timezone *tz);

void function()
{
    int i=0;
    while(i<100) i++;
}

int main()
{
    int choice;
    printf("\n请选择功能：");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
        {
            printf("\n执行功能1：以字符串的形式显示本地时间\n");
            struct tm *local;
            time_t t;
            t = time(NULL);
            local = localtime(&t);  // 将t中的信息转换成本地时间
            printf("%d年%d月%d日 %d:%d:%d\n",
                local->tm_year+1900,local->tm_mon+1,local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);
        }
        break;
        case 2:
        {
            printf("\n执行功能2：测试一段循环代码的运行时间并显示\n");
            struct timeval start,end;
            float time;
            gettimeofday(&start,NULL);
            function();
            gettimeofday(&end,NULL);
            time = 1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
            time /= 1000000;
            printf("消耗时间：%.2fs\n",time);
        }
        break;
    }
}