#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <set>

#include "testStruct.h"
#include "Person.h"
#include "Student.h"
#include "Player.h"

using namespace std;


// 测试函数
void test();
void testArray(int (*arr)[4]);
void testSet();
void testVector();
void testStack();
void testList();
void testStruct();
void testPerson(int& x);
void testStudent();
void testPlayer();


int main()
{
    // int* temp = nullptr;
    // if(!temp) cout<<"空指针"<<endl;
    
    // test();

    // int arr[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // printf("%d %d %d\n",sizeof(arr),sizeof(arr[0]),sizeof(arr[0][0]));
    // testArray(arr);

    testSet();
    // testVector();
    // testStack();
    // testList();

    // testStruct();

    // int curAge = 0;
    // testPerson(curAge);
    // cout<<curAge<<endl;

    // testStudent();

    // Person a("dsh",23,true);
    // Person *temp;
    // Student b("dsh",23,true,41823162,"USTB",4);
    // Player c("htm");
    // temp = &c;
    // cout<<temp->getType()<<endl;

    return 0;
}

bool com(vector<int> &a,vector<int> &b)
{
    return a[0]<b[0];
}
void test()
{
    vector<vector<int>> testV{{0,3},{2,7},{-1,4}};
    sort(testV.begin(),testV.end());
    cout<<testV[0][0]<<endl;
}


// 以行指针形式接受二维数组
void testArray(int (*arr)[4])
{
    int len = sizeof(*arr)/sizeof(**arr);
    cout<<"行长度："<<len<<endl;
    for(int i=0;i<len;i++)
        cout<<*(*arr+i)<<endl;
}



////////////////////////////////// STL数据结构 //////////////////////////////////

void testSet()
{
    set<string> st{"cwf","htm"};
    st.insert("dsh");
    
    if(st.find("cwf")!=st.end()) cout<<"存在"<<endl;
}

void testVector()
{
    vector<int> v(5);
    vector<int>::iterator it;
    for(it=v.begin();it!=v.end();it++) *it = 5-(it-v.begin());
    sort(v.begin(),v.end());
    cout<<v[1]<<endl;
    cout<<v.at(5)<<endl;

    vector<vector<int>> vv;
    vv.push_back({1,2,3});
    cout<<vv[0][1]<<endl;
}


void testStack()
{
    stack<int> st;
    st.push(1);
    st.push(10);
    st.push(5);
    cout<<st.top()<<endl;
    st.pop();
    cout<<st.top()<<endl;
    queue<int> que;
    que.empty();
}

void testList()
{
    list<int> myList{5,3,2,4,9};
    myList.sort();
    cout<<myList.front()<<endl;
}



////////////////////////////////// 面向对象 //////////////////////////////////

void testStruct()
{
    PersonStruct x("dsh",23,164.5);
    cout<<x.name<<endl;

    PersonStruct* dsh = &x;
    cout<<dsh->height<<endl;
    dsh = new PersonStruct();
    cout<<dsh->name<<endl;
}


void testPerson(int& x)
{
    cout<<x<<endl;
    Person dsh("dsh",23);
    dsh.name = "狄仕豪";
    dsh.grow();
    x = dsh.age;
    dsh.printInfo();
}

void testStudent()
{
    // Student dsh("dsh",23,true);
    // cout<<dsh.gender<<endl;
    // cout<<dsh.school<<endl;
    Student dsh("dsh",23,true,41823162,"USTB",4);
    cout<<dsh.age<<endl;
    cout<<dsh.school<<endl;
}