// ClassTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "Person.h"


// 测试函数
void testPerson(int& x);


int main()
{
    int curAge = 0;
    testPerson(curAge);
}


void testPerson(int& x)
{
    const Person dsh("dsh",23,true);
    Person htm = Person("htm",21,true);
    cout << htm.getTag() << endl;
    cout << dsh.getTag() << endl;
}