#pragma once
#include <string>
#include <iostream>

using namespace std;

class Person
{
public:
	string name 	= ".";
	int age 		= -1;
	bool gender 	= false;
	const int tag 	= 1;

	// 构造
	// Person();
	Person(string name="无名", int age=0, bool gender = true);
	
	// 析构
	~Person();
	
	// 成员方法
	void printInfo();
	void grow();
	void setCurNum(int x);
	int getCurNum();
	int getTag();
	int getTag() const;
	virtual string getType();


protected:
	static int curNum;		// 记录共有多少Person对象
};



Person::Person(string name, int age, bool gender) : name(name), age(age), gender(gender)
{
	curNum++;
}


Person::~Person()
{
	curNum--;
	cout << curNum << "\tPerson Clear" << endl;
}


int Person::curNum = 0;


void Person::printInfo()
{
	string sex;
	if(gender) sex = "male";
	else sex = "female";
	cout << "\nPerson Property" << endl;
	cout << name << endl;
	cout << age << endl;
	cout << sex << endl;
	cout << "---------------------\n" <<endl;
}


void Person::grow()
{
	age++;
}

void Person::setCurNum(int x)
{
	curNum = x;
}
int Person::getCurNum()
{
	return curNum;
}


int Person::getTag()
{
	return tag;
}
int Person::getTag() const
{
	cout << "此方法为const方法" << endl;
	return tag;
}

string Person::getType()
{
	return "Person";
}
