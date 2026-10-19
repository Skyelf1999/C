#pragma once
#include <string>
#include "Person.h"

using namespace std;


class Student: public Person
{
public:
    int studentId = 0;          // 学号
    string school = "学校";
    int grade     = 1;          // 年级

    using Person::Person;       // 继承父类的构造函数
    Student(string name, int age, bool gender,int studentId,string school,int grade);
    ~Student();
    void setScore(float s);
    float getScore();
    string getType();

private:
    float score   = 0;
};


Student::Student(string name, int age, bool gender,int studentId,string school,int grade):studentId(studentId),school(school),grade(grade),Person(name)
{
    curNum++;
}
Student::~Student()
{
    cout << "Student Clear\t";
}


void Student::setScore(float s)
{
    score = s;
}
float Student::getScore()
{
    return score;
}


string Student::getType()
{
    return "Student";
}
