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


// 堆选择排序
template<class T>
void HeapSortArr(T *datas,int size)
{
    // 将原数组调整为大根堆
    for(int i=1;i<size;i++)
    {
        int child = i;
        int parent = GetParent(child);
        while(parent>=0 && datas[child]>datas[parent])
        {
            T temp = datas[child];
            datas[child] = datas[parent];
            datas[parent] = temp;
            child = parent;
            parent = GetParent(child);
        }
    }
    // printArray(datas,size);

    // 降序排列
    for(int maxIndex=size-1;maxIndex>0;maxIndex--)
    {
        printf("当前尾部index：%d\n",maxIndex);
        // 将当前根（当前最大值）换到最后
        T temp = datas[maxIndex];
        datas[maxIndex] = datas[0];
        datas[0] = temp;
        // 调整剩余部分
        int cur=0;
        while(cur<maxIndex)
        {
            int left = GetChild(0,Left);
            int right = GetChild(0,Right);
            int maxChild = max(datas[left],datas[right]);
            // 若根小，与左右最大者交换
            if(datas[cur]<maxChild)
                if(datas[left]==maxChild)
                {
                    datas[cur] = datas[left];
                    datas[left] = temp;
                    cur = left;
                }
                else
                {
                    datas[cur] = datas[right];
                    datas[right] = temp;
                    cur = right;
                }
            else break;
        }
    }
    
    printArray(datas,size);

    cout<<"排序完毕"<<endl;
}

template<class T>
void HeapSortVec(vector<T> &datas,int size)
{
    cout<<"排序完毕"<<endl;
}