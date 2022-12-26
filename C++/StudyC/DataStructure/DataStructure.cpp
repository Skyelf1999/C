// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "listNode.h"
using namespace std;


// 测试方法
void testNodeList();


int main()
{
    testNodeList();
}


void testNodeList()
{
    ListNode* head = CreateListNode();
    printNodeList(head);
}

