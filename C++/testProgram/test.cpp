#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int r,c;

    vector<vector<int>> mat(3);
    for(int i=0;i<3;i++)
    {
        vector<int> row(i+1);
        for(int j=0;j<i+1;j++) row[j] = i+j;
        mat[i] = row;
    }
    for(int i=0;i<3;i++)
    {
        vector<int>::iterator it;
        for(it=mat[i].begin();it!=mat[i].end();it++)
            cout<<*it<<endl;
        cout<<"\n"<<endl;
    }

    // vector<vector<int>> ret(r);

    // for(int i=0;i<r;i++)
    // {
    //     vector<int> row(c);
    //     for(int j=0;j<c;j++)
    //     {
    //         int index = i*r+c;
    //         row.push_back(mat[index/m][index-index/m*n]);
    //     }
    //     ret.push_back(row);
    // }


    return 0;
}
