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

#include "Person.h"
#include "Student.h"
#include "Player.h"
#include "util.h"

using namespace std;


// 测试函数
void test();
void testString();

void testSet();
void testVector();
void testStack();
void testQueue();
void testList();
void testPair();
void testMap();

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

    // testPair();
    // testSet();
    // testVector();
    // testStack();
    // testQueue();
    // testList();
    // testMap();

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
    string s11 = "ds";
    s11 += 'h';
    cout<<(s1==s11)<<endl;
    string s2 = "htm hahaha";
    cout<<(s2[3]==' ')<<endl;
    printf("\n");

    // 字符操作
    char c = s1[0];
    s1[0] = s1[1];
    s1[1] = c;
    cout<<s1<<endl;
    printf("\n");

    // 长度
    cout<<s1.size()<<endl;
    cout<<s1.length()<<endl;
    printf("\n");

    // 赋值
    string s3 = s1;
    s1 += '?';
    cout<<s1<<endl;

    // ASCII码
    cout<<('a'>64)<<endl;
    cout<<(char)('a'+2)<<endl;

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

    st.insert("dsh");
    for(auto name : st) cout<<name<<endl;

    printf("\n");
    
    unordered_set<int> ust{1,2,3,5};
    printf("%d %d",ust.count(2),ust.count(10));
}

void testVector()
{
    
    vector<int> v(1,1);
    v.push_back(2);
    vector<int> v2(3,4);
    vector<int> v3(5,1);
    copy(v2.begin(),v2.end(),v3.begin()+1);
    printVector(v3);
    auto res = find(v3.begin(),v3.end(),5);
    if(res!=v3.end())
    {
        cout<< *(res-1) << " " << *(res+1) <<endl;
        vector<int> temp(3);
        copy(res-1,res+2,temp.begin());
        printVector(temp);
    }
    else cout<<"目标不存在"<<endl;

    v3[3] = 10;
    auto l = v3.end()-1;
    while(l>=v3.begin())
    {
        cout<<*(l--)<<endl;
    }

    v = vector<int>{4,4,4};
    cout<<(v==v2)<<endl;
    // cout<<v.at(5)<<endl;

    cout<<"\n";

    vector<vector<int>> vv;
    vv.push_back({1,2});
    vv.push_back({0,4});
    vv.push_back({5,8,7});
    vv.push_back({2,6});
    sort(vv.begin(),vv.end());
    for(auto ele : vv) cout<<ele[0]<<endl;

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

void testQueue()
{
    queue<int> q;
    q.push(5);
    q.push(7);
    q.push(1);
    q.emplace(8);
    // while(!q.empty())
    // {
        
    // }
    int len = q.size();
    for(int i=0;i<len;i++)
    {
        cout<<q.front()<<endl;
        q.pop();
    }
    cout<<q.empty()<<endl;
}


void testList()
{
    list<int> myList{5,3,2,4,9};
    myList.sort();
    cout<<myList.front()<<endl;
}

/**
 * 测试map容器的使用
 */
void testMap()
{
    // 创建一个string到int的map容器
    map<string,int> mp;
    // 对不存在的键"dsh"进行自增操作，会自动初始化为0再自增
    mp["dsh"] += 23;
    // 输出自增后的值，应为23
    printf("对不存在的k进行自增后的v：%d\n",mp["dsh"]);
    // 检查"htm"是否存在于map中，不存在则返回0
    cout<<mp.count("htm")<<endl;    // 0
    cout<<mp.count("htm")<<endl;    // 0
    // 注释掉的代码：对不存在的键"htm"进行自增后输出，会先初始化为0再自增
    // cout<<mp["htm"]++<<endl;        // int默认值为0
    // 对"htm"的值进行自增操作
    mp["htm"]++;
    // 输出"htm"是否存在于map中及其值，应为1和1
    cout<<mp.count("htm")<< ", " << mp["htm"] <<endl;    // 1
    
    printf("\n");

    // 创建一个char到string的map容器
    map<char,string> mp2;
    
    // 向map2中添加键值对
    mp2['a']="dsh";
    mp2['b'] = "htm";
    // 检查并输出'c'对应的值是否为空字符串
    cout<<(mp2['c']=="")<<endl;
    // 输出'a'对应的值
    cout<<mp2['a']<<endl;

    cout<<"map自动排序测试"<<endl;
    // 创建一个int到string的map容器
    map<int,string> mp3;
    // 向map3中添加键值对
    mp3[2] = "dsh";
    mp3[15] = "zdd";
    mp3[1] = "zrq";
    mp3[4] = "htm";
    // 调用printMap函数输出map3的内容
    printMap(mp3);
    // 使用反向迭代器逆序输出map3的内容
    map<int,string>::reverse_iterator it;
    for(it=mp3.rbegin();it!=mp3.rend();++it)
            cout<< it->first << "\t" << it->second <<endl;
}



////////////////////////////////// 面向对象 //////////////////////////////////


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
    Student htm("htm",21,true);
    cout<<htm.gender<<endl;
    cout<<htm.school<<endl;
    Student dsh("dsh",23,true,41823162,"USTB",4);
    cout<<dsh.age<<endl;
    cout<<dsh.school<<endl;
}