#include <stdio.h>
#include <stdlib.h>


// 顺序表


int end_code;			// 存放结束密码，输入后停止当前循环

#define MAX 10
typedef int Datatype;	// 定义数据类型为int
typedef struct node
{ Datatype data[MAX]; int last = -1;} List;
List list;


void func_style()
{
	printf("\n\n//--------------------- 函数名称 ---------------------//\n");
	printf("\n//--------------------- 函数名称 ---------------------//\n\n");
}


/////////////////////////////////////////////////////////////////////////////

void CreateList()
{
	printf("\n\n//--------------------- 创建 ---------------------//\n");
    int data,i;
    printf("请输入 %d 个数据进行初始化,你也可以输入-999来提前结束",MAX);
    for(i = 0;i<MAX;i++)
    {
        data = scanf("%d",&data);
        if(data != -999) list.data[i] = data;
        else break;
    }
    list.last = i-1;
    printf("创建完毕");
	printf("\n//--------------------- 创建 ---------------------//\n\n");
}


void visit_all()
{
	printf("\n\n//--------------------- 查询全部 ---------------------//\n");
    if(list.last == -1) printf("请先创建！\n");
    int i;
    printf("下面循环输出全部数据：\n");
    for(i=0;i<=list.last;i++)
    {
        printf("%d，",list.data[i]);
    }
	printf("\n//--------------------- 查询全部 ---------------------//\n\n");
}

void visit_index()
{
	printf("\n\n//--------------------- 按序号查询 ---------------------//\n");
    if(list.last == -1) printf("请先创建！\n");
    int index;
    printf("请输入要查询的序号（从0开始）：");
    scanf("%d",&index);
    if(index>list.last) printf("\n序号超出范围！");
    else if(index<0) printf("\n序号输入有误！");
    else printf("\n序号为 %d 的数据为： %d",index,list.data[index]);
	printf("\n//--------------------- 按序号查询 ---------------------//\n\n");
}

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("\n请设定结束密码：\n");
	scanf("%d",&end_code);			// 设定结束密码
	char options[] = "\n\t1 —— 创建\n\t2 —— 查询全部\n\t3 —— 按序号查询\n";

	int go;							// 循环变量
	int choice;						// 每个循环进行的操作选择
	while(1)
	{
		printf("%s\n请输入你想要进行的操作：",options);
		scanf("%d",&choice);
		switch (choice)
		{
			case 1:CreateList();
				break;
			case 2:visit_all();
				break;
			case 3:visit_index();
				break;
		}
		// 循环结束判断
		printf("\n是否结束？若需结束，请输入结束密码；若继续，输入任意数：");
		scanf("%d",&go);
		if(go==end_code) 
		{
			printf("\n循环结束。\n");
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////