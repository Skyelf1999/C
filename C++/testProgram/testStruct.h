#pragma once
#include<string>
using namespace std;

struct PersonStruct
{
	string name;
	int age;
	float height;
	PersonStruct():name("无名"),age(-1),height(0.0f){}
	PersonStruct(string name,int age,float h):name(name),age(age),height(h)
	{
		cout<<"结构体 PersonStruct 创建完毕"<<endl;
	}
}PersonS;