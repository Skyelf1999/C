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
	cout << "���Person����" << endl;
}


int Person::curNum = 0;


void Person::printInfo()
{
	string sex;
	if (gender) sex = "��";
	else sex = "Ů";
	cout << "������" << name << "�����䣺" << age << "���Ա�" << sex << endl;
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
	cout << "�˷���Ϊconst����" << endl;
	return tag;
}


