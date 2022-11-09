#include <stdio.h>
#include <stdlib.h>


int main()
{
    int x = 1;
    for(int i=0;i<5;i++)
    {
        x += i;
        printf("当前 x=%d",x);
    }
    return 0;
}
