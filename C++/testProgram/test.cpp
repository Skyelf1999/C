#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vInt(5,2);
    for(int i=0;i<vInt.size();i++)
        vInt[i] = i;
    
    vInt.erase(vInt.begin()+1,vInt.end()-2);
    for(int i=0;i<vInt.size();i++)
        cout<<vInt[i]<<endl;

    return 0;
}
