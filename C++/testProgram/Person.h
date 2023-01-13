#pragma once
#include <string>

using namespace std;

class Person
{
public:
	string name;
	int age;
	bool gender;
	const int tag = 1;

	// 构造
	Person(string name="无名", int age=0, bool gender = true);
	//Person(string name = "无名", int age = 0, bool gender = true,int t=1);
	// 析构
	~Person();
	
	// 成员方法
	void printInfo();
	void grow();
	int getCurNum();
	int getTag();
	int getTag() const;


private:
	static int curNum;
};

