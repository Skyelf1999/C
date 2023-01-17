#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "testStruct.h"
#include "Person.h"
#include "Student.h"
#include "Player.h"

using namespace std;


// 测试函数
void testPerson(int& x);
void testStudent();
void testPlayer();


int main()
{
    // int curAge = 0;
    // testPerson(curAge);
    // cout<<curAge<<endl;

    testStudent();

    return 0;
}


void testPerson(int& x)
{
    cout<<x<<endl;
    Person dsh("dsh",23);
    dsh.name = "狄仕豪";
    dsh.grow();
    x = dsh.age;
    cout<<dsh.gender<<endl;
}

void testStudent()
{
    // Student dsh("dsh",23,true);
    // cout<<dsh.gender<<endl;
    // cout<<dsh.school<<endl;
    Student dsh("dsh",23,true,41823162,"USTB",4);
    cout<<dsh.age<<endl;
    cout<<dsh.school<<endl;
}