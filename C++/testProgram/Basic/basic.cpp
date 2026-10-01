#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "testArray.h"
#include "testStruct.h"
#include "testLinkList.h"

using namespace std;

int main() {
    testArray();
    // testStruct();
    // testLinkList();
    printf("hello world\n");
    int x = 2;
    x += 3;
    printf("%d",x);
}