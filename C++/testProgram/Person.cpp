#include "Person.h"
#include <iostream>


Person::Person(string name, int age, bool gender) : name(name), age(age), gender(gender)
{
	curNum++;
}
//Person::Person(string name, int age, bool gender,int t) : name(name), age(age), gender(gender), tag(t)
//{
//	curNum++;
//}


Person::~Person()
{
	curNum--;
	cout << "清除Person对象" << endl;
}


int Person::curNum = 0;


void Person::printInfo()
{
	string sex;
	if (gender) sex = "男";
	else sex = "女";
	cout << "姓名：" << name << "，年龄：" << age << "，性别：" << sex << endl;
}


void Person::grow()
{
	age++;
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


