#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "util.h"

using namespace std;



//---------------------------- 冒泡排序 ----------------------------// 
void SwapNormalSort(int arr[], int n)
{
    printf("排序前：");
    print1DArray(arr,n);

    bool flag;              // 本轮是否发生了交换
    for(int i=0;i<n;i++)    // 每轮得到[i,n-1]中的最小值
    {
        flag = false;
        for(int j=n-1;j>i;j--)
        {
            if(arr[j-1]>arr[j])
            {
                swap(arr[j-1],arr[j]);
                flag = true;
            }
        }

        if(!flag) break;    // 本轮未发生交换，已有序
        print1DArray(arr,n);
    }

    printf("排序后：");
    print1DArray(arr,n);
}



//---------------------------- 快速排序  ----------------------------// 
void SwapQuickSourt(int arr[], int left, int right)
{

    if(left>=right) return;

    int i = left;
    int j = right;
    int temp = arr[left];

    while(i<j)
    {
        // 右-->左
        while(i<j && arr[j]>=temp) j--;
        arr[i] = arr[j];
        // 左-->右
        while(i<j && arr[i]<temp) i++;
        arr[j] = arr[i];
    }

    // 确定轴点，对左右部分进行快排
    arr[i] = temp;
    SwapQuickSourt(arr,left,i-1);
    SwapQuickSourt(arr,i+1,right);
}