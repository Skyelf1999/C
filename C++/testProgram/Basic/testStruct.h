#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<string>

using namespace std;

struct PersonStruct
{
	string name;
	int age;
	float height;
	// 可选内容：构造方法
	PersonStruct():name("无名"),age(-1),height(0.0f){}
	PersonStruct(string name,int age,float h=170):name(name),age(age),height(h)
	{
		cout<<"结构体 PersonStruct 创建完毕"<<endl;
	}
}Person_1;



void testStruct()
{
    printf("直接使用结构体名称定义：\n");
    PersonStruct x("dsh",23,164.5);
    cout<<x.name <<endl;

    printf("\n使用地址创建结构体指针：\n");
    PersonStruct* dsh = &x;
    cout<<dsh->height<<endl;
	PersonStruct* dsh2 = &Person_1;
    cout<<dsh2->name<<endl;

    printf("\n使用new创建结构体指针：\n");
    PersonStruct* zrq = new PersonStruct("zrq", 22);
    cout<<zrq->name<<endl;
}