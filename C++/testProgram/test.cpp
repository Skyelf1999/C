#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <utility>
#include <unordered_set>
#include <map>

#include "testStruct.h"
#include "Person.h"
#include "Student.h"
#include "Player.h"

using namespace std;


// 测试函数
void test();
void testString();
void testArray(int (*arr)[4]);

void testSet();
void testVector();
void testStack();
void testList();
void testPair();
void testMap();

void testStruct();
void testPerson(int& x);
void testStudent();
void testPlayer();


int main()
{
    // string s1 = "11";
    // string s2 = "13";
    // s2[1] = (char)(57);
    // cout<<s2<<endl;
    // cout<<pow(10.0,2.0)<<endl;
    
    // test();

    // testString();
    // int arr[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // printf("%d %d %d\n",sizeof(arr),sizeof(arr[0]),sizeof(arr[0][0]));
    // testArray(arr);

    // testPair();
    // testSet();
    // testVector();
    // testStack();
    // testList();
    // testMap();

    testStruct();

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


void test()
{
    
}


void testString()
{
    // 比较
    string s1 = "dsh";
    cout<<(s1=="dsh")<<endl;
    string s2 = "htm hahaha";
    cout<<(s2[3]==' ')<<endl;
    printf("\n");

    // 长度
    cout<<s1.size()<<endl;
    cout<<s1.length()<<endl;
    printf("\n");

    // 赋值
    string s3 = s1;
    s1 += "?";
    cout<<s3<<endl;

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

void testPair()
{
    pair<int,int> left(-1,0);
    pair<int,int> dir = left;
    pair<int,int> right(1,0);
    cout<< (dir==left) << endl;
    cout<< (dir==right) << endl;
    cout<< (pair<int,int>(1,0)==right) << endl;
}

void testSet()
{
    set<string> st{"cwf","htm"};
    st.insert("dsh");
    if(st.find("cwf")!=st.end()) cout<<"存在"<<endl;

    printf("\n");
    
    unordered_set<int> ust{1,2,3,5};
    printf("%d %d",ust.count(2),ust.count(10));
}

void testVector()
{
    
    vector<int> v(1,1);
    v.push_back(2);
    vector<int> v2(3,3);
    vector<int> v3(5,0);
    copy(v2.begin(),v2.end(),v3.begin()+1);
    cout<<v3[3]<<endl;
    cout<<v3[4]<<endl;
    v = vector<int>{3,3,3};
    cout<<(v==v2)<<endl;
    // cout<<v.at(5)<<endl;

    cout<<"\n";

    vector<vector<int>> vv;
    vv.push_back({1,2});
    vv.push_back({0,4});
    vv.push_back({5,8,7});
    vv.push_back({2,6});
    sort(vv.begin(),vv.end());
    for(int i=0;i<vv.size();i++) cout<<vv[i][0]<<endl;

    cout<<"\n";

    vector<vector<int>> unruledV(3);
    unruledV[0] = vector<int>(4);
    unruledV[1] = vector<int>(0);
    for(int i=0;i<unruledV.size();i++) cout<< unruledV[i].size() <<endl;

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

void testMap()
{
    map<string,int> mp;
    mp["dsh"] += 23;
    cout<<mp.count("htm")<<endl;
    cout<<mp["htm"]<<endl;      // int默认值为0
    cout<<mp.count("htm")<<endl;
    
    printf("\n");

    map<char,string> mp2;
    mp2['a']="dsh";
    mp2['b'] = "htm";
    cout<<(mp2['c']=="")<<endl;
    cout<<mp2['a']<<endl;
}



////////////////////////////////// 面向对象 //////////////////////////////////

void testStruct()
{
    printf("直接使用结构体名称定义：\n");
    PersonStruct x("dsh",23,164.5);
    cout<<x.name + "\n"<<endl;

    printf("使用地址创建结构体指针：\n");
    PersonStruct* dsh = &x;
    cout<<dsh->height<<endl;
    printf("使用new创建结构体指针：\n");
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