#include<stdio.h>
#include<string.h>

/*
    ��ȡN>3������
    ��ð�ݷ�����Щ��������
*/

#define N 5

int main()
{
    int data[N];
    int i,j,help;
    printf("\n������%d�����β�����������\n",N);
    for(i=1;i<=N;i++)
    {
        scanf("%d",&data[i-1]);
    }
    // ð�ݷ�����
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
    // �������
    for(i=0;i<N;i++) printf("%d ",data[i]);
}