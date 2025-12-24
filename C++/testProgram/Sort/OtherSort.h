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

using namespace std;

//---------------------------- 二路归并 ----------------------------//
int* temp;
/*
 * 合并两个数组（一个数组的两个部分）
 * @param arr 待排序数组
 * @param low 第1个数组的起始位置
 * @param mid 第2个数组的起始位置
 * @param high 第2个数组的结束位置
*/
void MergeArray(int arr[], int low, int mid, int high)
{
    
}
void MergeSort(int arr[], int low, int mid, int high)
{
    temp = (int*)malloc( sizeof(int) * (high-low+1) );


    free(temp);
}






//---------------------------- 计数排序 ----------------------------//
void InitCountArray(int arr[], int* count, int n)
{
    
}
void CountSort(int arr[], int n)
{}