#include <stdio.h>


int main()
{
    int sum,num;
    for(sum=0,num=0;num<4;num++,sum++)
    {
        sum+=num;
        printf("num = %d；sum = %d\n",num,sum);
    }
}