// 数组测试

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

#define ROW 3
#define COL 3

// 函数声明
void testArray();
void init1DArray();
void init2DArray();
template<class T> void print1DArray(T* arr);
template<class T> void print2DArray_malloc(T** arr, int row, int col);
template<class T> void print2DArray_normal(T (*arr)[COL], int row);


// 测试用变量
int a[] = {1, 2, 3, 4, 5};
char charArray[ROW];
int* c;
int **arr_malloc;
int (*arr_normal)[COL];

void testArray(){
    init1DArray();
    init2DArray();
}


//---------------------------- 初始化 ----------------------------//

// 初始化一维数组
void init1DArray(){
    // 初始化字符数组b
    // 使用循环将每个元素设置为对应的ASCII字符，'0'到'0'+ROW-1
    for(int i=0;i<ROW;i++) charArray[i] = (char)('0'+i);
    print1DArray(charArray);

    c = (int*)malloc(sizeof(int) * 5);
}


// 初始化二维数组
void init2DArray(){
    // 动态分配二维数组：地址不连续
    int row = 3;
    int col = 4;
    // 分配行空间：row个行指针
    arr_malloc = (int**)malloc(sizeof(int*) * row);
    // 为每一行分配列空间：col个元素指针
    for(int i=0;i<row;i++)
    {
        arr_malloc[i] = (int*)malloc(sizeof(int) * col);
        for(int j=0;j<col;j++)
            arr_malloc[i][j] = i*col + j + 1;
    }
    print2DArray_malloc(arr_malloc, row, col);

    // 精确定义
    int temp[5][COL] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    // 数组指针：指向行长为3的5x3数组
    arr_normal = (int (*)[COL])temp;
    print2DArray_normal(arr_normal, 5);
}



//---------------------------- 输出 ----------------------------// 
/*
    数组以参数形式传入后，会退化一个层级
    例如：
        一维数组：退化为指向首变量的指针
        二维数组：退化为指向首行的指针
*/
template<class T>
void print1DArray(T* arr)
{
    int arrSize = sizeof(arr);
    int elementSize = sizeof(*arr);
    int arrLen = arrSize/elementSize;
    printf("（数组大小：%d\t元素大小：%d\t数组长度：%d）\n", arrSize, elementSize, arrLen);
    for(int i=0;i<arrLen;i++)  cout<< arr[i] << " ";
    cout<< "\n" <<endl;
}

template<class T>
void print2DArray_malloc(T** arr, int row, int col)
{
    int rowSize = sizeof(arr[0]);
    int elementSize = sizeof(arr[0][0]);
    // int rowLen = rowSize/elementSize;
    int rowLen = col;
    printf("动态分配\t数组：%d x %d\t行大小：%d\t单个元素大小：%d\n", row, rowLen, rowSize, elementSize);
    for(int i=0;i<row;i++){
        for(int j=0;j<rowLen;j++) cout<< arr[i][j] << "\t";
        cout<<endl;
    }
    cout<<endl;
}
template<class T>
void print2DArray_normal(T (*arr)[COL], int row)
{
    // 已传入行数，求单行元素数量
    int rowSize = sizeof(*arr);
    int elementSize = sizeof(**arr);
    int rowLen = sizeof(*arr)/sizeof(**arr);
    printf("普通定义\t数组：%d x %d\t行大小：%d\t单个元素大小：%d\n", row, rowLen, rowSize, elementSize);
    
    for(int i=0;i<row;i++){
        for(int j=0;j<rowLen;j++) cout<< arr[i][j] << "\t";
        cout<<endl;
    }
    cout<<endl;
}
