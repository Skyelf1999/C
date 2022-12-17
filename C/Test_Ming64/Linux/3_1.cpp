#include <stdio.h>
#include <string.h>

/*
    输入20个学生的成绩
    成绩为80~100的为A，60~79为B，60以下为C
    输入最终得到A、B、C各有几人
*/

#define X 5
typedef struct 
{
    float grades[X];
    int number = 0;
} grade_list;

int main()
{
    float grade;
    grade_list A,B,C;
    for(int i=1;i<=X;i++)      // X个成绩输入
    {
        printf("\n请输入第%d名学生的成绩：",i);
        scanf("%f",&grade);
        if(grade>=80)
        {
            A.grades[A.number] = grade;
            A.number++;
        }
        else if(grade>=60)
        {
            B.grades[B.number] = grade;
            B.number++; 
        }
        else
        {
            C.grades[C.number] = grade;
            C.number++;
        };
    } 
    printf("\n\nA:%d人；B:%d人；C:%d人；\n",A.number,B.number,C.number);   
}