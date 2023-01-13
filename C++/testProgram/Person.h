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

	// ����
	Person(string name="����", int age=0, bool gender = true);
	//Person(string name = "����", int age = 0, bool gender = true,int t=1);
	// ����
	~Person();
	
	// ��Ա����
	void printInfo();
	void grow();
	int getCurNum();
	int getTag();
	int getTag() const;


private:
	static int curNum;
};

