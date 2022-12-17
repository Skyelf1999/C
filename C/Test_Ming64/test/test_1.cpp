#include <stdio.h>
#include "stdlib.h"
#include "time.h"


int main(void)
{
    int a[]={1,7,8,9,10},i,j,k,t;
    srand((unsigned)time(NULL));
    for(k=10,i=0;i<2;i++){
        printf("%d ",a[j=rand()%k]);
        t=a[--k],a[k]=a[j],a[j]=t;
    }
    printf("\n");
    return 0;
} 