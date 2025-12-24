#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <utility>
#include <unordered_set>
#include <map>
#include "DataClass.h"
#include "util.h"

#define Left 1
#define Right 2

using namespace std;

void AdjustMaxeHeap(int arr[], int n, int curRoot);



// // 直接选择排序
// void DirectSelectSortArray(T *datas,int size)
// {
//     return;
// }




// 计算目标序号的孩子的序号（从0开始）
int GetChild(int index,int choice)
{
    index++;
    if(choice==Left) return index*2-1;
    else return index*2;
}
int GetParent(int index)
{
    if(index>0) return (index+1)/2-1;
    return -1;
}



//---------------------------- 堆选择排序 ----------------------------//
// 将数组调整为大根堆
void BuildMaxHeap(int arr[], int n)
{
    int lastIndex = n-1;        // 数据存放于1~n-1
    // 从最后一个有子树的结点开始调整
    for(int i=lastIndex/2;i>=0;i--) AdjustMaxeHeap(arr,n,i);
}
// 将当前根和左右子调整为大根
void AdjustMaxeHeap(int arr[], int n, int curRoot)
{
    arr[0] = arr[curRoot];
    for(int i=2*curRoot;i<n;i*=2)
    {
        if(arr[i]<arr[i+1]) i++;
        // 确保根>子
        if(arr[0]>arr[i]) break;
        else{
            // 将当前根与较大子交换，下一轮对该子树进行调整
            arr[curRoot] = arr[i];
            curRoot = i;
        }
    }

    arr[curRoot] = arr[0];
}


// // 堆选择排序
// template<class T>
// void HeapSortArr(T *datas,int size)
// {
//     // 将原数组调整为大根堆
//     for(int i=1;i<size;i++)
//     {
//         int child = i;
//         int parent = GetParent(child);
//         while(parent>=0 && datas[child]>datas[parent])
//         {
//             T temp = datas[child];
//             datas[child] = datas[parent];
//             datas[parent] = temp;
//             child = parent;
//             parent = GetParent(child);
//         }
//     }
//     // printArray(datas,size);

//     // 降序排列
//     for(int maxIndex=size-1;maxIndex>0;maxIndex--)
//     {
//         printf("当前尾部index：%d\n",maxIndex);
//         // 将当前根（当前最大值）换到最后
//         T temp = datas[maxIndex];
//         datas[maxIndex] = datas[0];
//         datas[0] = temp;
//         // 调整剩余部分
//         int cur=0;
//         while(cur<maxIndex)
//         {
//             int left = GetChild(0,Left);
//             int right = GetChild(0,Right);
//             int maxChild = max(datas[left],datas[right]);
//             // 若根小，与左右最大者交换
//             if(datas[cur]<maxChild)
//                 if(datas[left]==maxChild)
//                 {
//                     datas[cur] = datas[left];
//                     datas[left] = temp;
//                     cur = left;
//                 }
//                 else
//                 {
//                     datas[cur] = datas[right];
//                     datas[right] = temp;
//                     cur = right;
//                 }
//             else break;
//         }
//     }
    
//     printArray(datas,size);

//     cout<<"排序完毕"<<endl;
// }


// template<class T>
// void HeapSortVec(vector<T> &datas,int size)
// {
//     cout<<"排序完毕"<<endl;
// }