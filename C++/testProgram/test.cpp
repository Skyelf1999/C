#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "testStruct.h"
using namespace std;

int main()
{
    PersonStruct dsh;
    dsh.name = "dsh";
    dsh.age = 23;
    dsh.height = 164.5;
    
    struct PersonStruct* p = &dsh;
    p->name = "htm";

    cout<<dsh.name<<endl;

    


    return 0;
}
