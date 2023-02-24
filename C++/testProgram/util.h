#pragma once

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
#include <map>
#include <utility>
#include <unordered_set>
#include <map>

using namespace std;


// 数组测试
template<class T>
void printArray(T *arr,int len)
{
    cout<<"长度："<<len<<endl;
    for(int i=0;i<len;i++)
        cout<<*(arr+i)<<endl;
}
template<class T>
void changeArray(T *arr,int len)
{
    arr[len-1] = 999;
}


// 输出vector
template<class T>
void printVector(vector<T> v)
{
    for(int i=0;i<v.size();i++)
        cout<< i << "\t" << v[i] << endl;
    cout<<"输出完毕"<<endl;
}


// 输出map
template<class T1,class T2>
void printMap(map<T1,T2> mp, bool choice=true)
{
    if(choice)
        for(auto p : mp)
            cout<< p.first << "\t" << p.second <<endl;
    else
    {
        // for(aotu it=mp.rbegin();it!=mp.rend();it++)
        //     cout<< it->first << "\t" << it->second <<endl;
    }
    cout<<"输出完毕"<<endl;
}