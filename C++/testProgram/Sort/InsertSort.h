#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "util.h"

using namespace std;


//---------------------------- 直接插入 ----------------------------// 
void InsertDirectSort(int a[], int n)
{
    printf("排序前：");
    print1DArray(a,n);

    int i,j,temp;
    for(i=1;i<n;i++)
    {
        if(a[i-1]>a[i])     // 顺序错误，需要排序
        {
            temp = a[i];
            // 在0~i-1中找到插入位置
            for(j=i-1; j>=0&&a[j]>temp; j--) a[j+1] = a[j];
            a[j+1] = temp;  // j为插入位置
        }
    }

    printf("排序后：");
    print1DArray(a,n);
}



//---------------------------- 折半插入 ----------------------------// 
void InsertHalfSort(int a[], int n)
{}



//---------------------------- 希尔排序 ----------------------------// 
void InsertShellSort(int a[], int n)
{
    printf("排序前：");
    print1DArray(a,n);

    int gap,i,j,temp;
    for(gap=n/2; gap>0; gap/=2)
        for(i=gap; i<n; i++)
            if(a[i-gap]>a[i])
            {
                /*
                    在[..., i-2*gap, i-gap]中找到插入位置
                    类似直接插入排序
                */
                int temp = a[i];
                for(j=i-gap; j>=0&&a[j]>temp; j-=gap) a[j+gap] = a[j];
                a[j+gap] = temp;
            }


    printf("排序后：");
    print1DArray(a,n);
}