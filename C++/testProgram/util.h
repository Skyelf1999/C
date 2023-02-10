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
#include <utility>
#include <unordered_set>
#include <map>

using namespace std;


// 输出vector
template<class T>
void printVector(vector<T> v)
{
    for(int i=0;i<v.size();i++)
        cout<< i << "\t" << v[i] << endl;
    cout<<"输出完毕"<<endl;
}