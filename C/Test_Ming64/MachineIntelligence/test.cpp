#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int x=-1; int y=-1;
}node;


int main()
{
    node x1;
    x1.x = 10;
    x1.y = 20;
    node x2 = x1;
    printf("%d",x2.x);
    return 1;
}