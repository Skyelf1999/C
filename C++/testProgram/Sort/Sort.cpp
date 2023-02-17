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

#include "DataClass.h"
#include "InsertSort.h"
#include "HalfSort.h"
#include "SelectSort.h"


using namespace std;



int main()
{
    int arr[] = {9,43,-54,4,-13,10,36};
    int len = sizeof(arr)/sizeof(arr[0]);
    HeapSortArr(arr,len);

}