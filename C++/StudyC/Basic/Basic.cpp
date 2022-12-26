// Basic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#include <iostream>
#include "testStruct.h"
#include "util.h"

using namespace std;
using namespace util;


// 包含的测试项
void testString(char* pStr);
void testStruct();


int main()
{
    char pStr[] = "param";
    //testString(pStr);
    testStruct();
    
}


void testString(char *pStr)
{
    string funcName = "字符串测试";
    func(funcName,true);

    cout << "C-Type String" << endl;
    int len = strlen(pStr);
    cout << "通过 char* 接受字符串参数：" << pStr << "    长度：" << len << endl;
    pStr[1] = '#';
    cout << pStr << "（可更改单个字符）\n" << endl;
    string newStr = "C++ String";
    cout << "C++字符串：" << newStr << "    长度：" << newStr.size() << endl;
    char x = newStr[0];
    newStr[0] = 'D';
    cout << "单个字符修改：" << x << " --> " << newStr[0] << endl;

    func(funcName, false);
}


void testStruct()
{
    string funcName = "结构体";
    func(funcName, true);

    struct PersonStruct* p = &PersonS;
    p->name = "dsh";
    p->age = 23;
    p->height = 164.5;
    cout << p->name << endl;

    PersonStruct x;
    x.name = "htm";
    x.age = 21;
    x.height = 180.1;
    cout << x.name << endl;

    func(funcName, false);
}





