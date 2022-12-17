#include <stdio.h>
#include <stdlib.h>


// 链表


typedef int Datatype;	// 定义数据类型为int
// 结构体中，data用于存放数据，指针next指向下一个节点
typedef struct 
	node{ Datatype data; struct node *next;} LLN;

int end_code;			// 存放结束密码，输入后停止当前循环
int length = 0;			// 链表长度
LLN *head;				// 头结点

void func_style()
{
	printf("\n\n//--------------------- 函数名称 ---------------------//\n");
	printf("\n//--------------------- 函数名称 ---------------------//\n\n");
}


/////////////////////////////////////////////////////////////////////////////


// 1.头结点初始化
void Head_initial()
{
	printf("\n\n//--------------------- 头结点初始化 ---------------------//\n");
	head = NULL;
	head = (LLN*)malloc(sizeof(LLN));
	if(head==NULL) printf("\n初始化失败\n");
	else 
	{
		head->next=NULL;
		printf("\n初始化成功\n");
	}
	printf("\n//--------------------- 头结点初始化 ---------------------//\n\n");
}


// 2.建表函数CreateList
void CreateList()
{
	printf("\n\n//--------------------- 链表建立 ---------------------//\n");
	LLN *pre,*cur;					// 创建当前节点和前驱节点辅助链表建立
	pre = head;
	while(1)
	{
		cur = (LLN*)malloc(sizeof(LLN));
		printf("\n请输入当前插入节点的数据：");
		scanf("%d",&(cur->data));	// 输入数据，存入data
		if(cur->data==end_code)
		{
			// 输入结束密码，链表创建结束
			printf("\n链表创建结束，长度为：%d\n",length);
			break;
		}
		pre->next = cur;			// 进行连接
		length++;
		pre = cur;
	}
	printf("\n//--------------------- 链表建立 ---------------------//\n\n");
}

// 求相邻节点之和为最大的第一节点的函数AdjMax
void AdjMax()
{
	printf("\n\n//--------------------- 求相邻节点之和为最大的第一节点 ---------------------//\n");
	if(head->next==NULL)			// 判断链表是否为空
	{
		printf("\n链表为空，请先创建\n");
		return;
		//return NULL;
	}
	printf("\n开始求相邻节点之和为最大的第一节点……\n");
	if(length==1) 
    {
        printf("\n查找成功，最大值为：%d；第一节点数据为：%d\n",head->next->data,head->next->data);
        return;
    }
	int max = 0;					// 存放相邻两节点之和的最大值
	int i=0;						// 计数变量i
	LLN *pre,*cur,*x;				// 创建当前节点和前驱节点辅助求解
	pre = head->next;				// pre指向第1个节点
	cur = pre->next;				// cur指向第2个节点
	if(length!=1)
	{
		while(1)
		{
			printf("循环……");
			if(pre->data+cur->data > max) 
			{
				max = pre->data+cur->data;
				x = pre;
			}
			printf("当前最大值为：%d\n",max);
			// if(cur->next == NULL) break;
			if(++i==length-1)	break;	// 判断是否完成遍历
			pre = cur;					// 向后遍历
			cur = cur->next;
		}
		printf("\n查找成功，最大值为：%d；第一节点数据为：%d\n",max,x->data);
	}
	printf("\n//--------------------- 求相邻节点之和为最大的第一节点 ---------------------//\n\n");
}

// 3.根据序号查找节点的函数Find_Index
void Find_Index()
{
	printf("\n\n//--------------------- 按序号查找 ---------------------//\n");
	int index;
	printf("请输入目标节点序号（从1开始）：");
	scanf("%d",&index);
	if(length==0)					// 判断链表是否为空
	{
		printf("\n链表为空，请先创建\n");
	}
	if(index<1 || index>length)		// 判断输入的序号是否正确
	{
		printf("\n输入序号错误\n");
	}
	int i=0;						// 计数变量i
	LLN *finder;					// 辅助查找指针finder
	finder = head;		
	while(i<index && finder->next!=NULL)
	{
		finder = finder->next;		// 不断循环
		i++;
	}
	printf("\n成功找到目标节点，数据为：%d \n",finder->data);
	printf("\n//--------------------- 按序号查找 ---------------------//\n\n");
}

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////

int main()
{
	printf("\n请设定结束密码：\n");
	scanf("%d",&end_code);			// 设定结束密码
	char options[] = "\n\t1 —— 创建链表\n\t2 —— 按序号查询\n\t3 —— 插入\n\t4 —— 求相邻节点之和为最大的第一节点\n";

	int go;							// 循环变量
	int choice;						// 每个循环进行的操作选择
	while(1)
	{
		if(head == NULL) Head_initial;
		else
		{
			printf("\n是否需要重新初始化头结点：1 —— 是；0 —— 否");
			scanf("%d",&choice);
			if(choice == 1) Head_initial;
		}
		printf("%s\n请输入你想要进行的操作：",options);
		scanf("%d",&choice);
		switch (choice)
		{
			case 1:CreateList();
				break;
			case 2:Find_Index();
				break;
			case 3:CreateList();
				break;
			case 4:AdjMax;
				break;
		}
		// 循环结束判断
		printf("\n是否结束？若需结束，请输入结束密码；若继续，输入任意数：");
		scanf("%d",&go);
		if(go==end_code) 
		{
			printf("\n循环结束。\n");
			free(head);	length = 0;
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////