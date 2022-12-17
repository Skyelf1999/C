#include<stdio.h>
#include<string.h>

/*
    读取N>3个整数
    用冒泡法对这些数字排序
*/

#define N 5

int main()
{
    int data[N];
    int i,j,help;
    printf("\n请输入%d个整形参数进行排序：\n",N);
    for(i=1;i<=N;i++)
    {
        scanf("%d",&data[i-1]);
    }
    // 冒泡法排序
    for(i=0;i<N;i++)
    {
        for(j=i+1;j<N;j++)
        {
            if(data[i]>data[j])
            {
                help = data[i];
                data[i] = data[j];
                data[j] = help;
            }
        }
    }
    // 数组输出
    for(i=0;i<N;i++) printf("%d ",data[i]);
}