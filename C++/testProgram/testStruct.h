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


struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};