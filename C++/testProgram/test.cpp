#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> arr(2);
    arr[0] = 1;
    arr[1] = 3;
    arr.push_back(5);
    cout<<arr[2]<<endl;

    return 0;
}
