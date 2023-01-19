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

	// ����
	// Person();
	Person(string name="����", int age=0, bool gender = true);
	
	// ����
	~Person();
	
	// ��Ա����
	void printInfo();
	void grow();
	void setCurNum(int x);
	int getCurNum();
	int getTag();
	int getTag() const;
	string getType();


protected:
	static int curNum;		// ��¼���ж���Person����
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
	cout << "�˷���Ϊconst����" << endl;
	return tag;
}

string Person::getType()
{
	return "Person";
}
