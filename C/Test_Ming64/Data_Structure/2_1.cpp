#include <stdio.h>
#include <stdlib.h>

typedef struct 
    node { float coef; float exp; struct node* next; }Element;
    // coef为项系数，exp为项次数，next指向下一项


/////////////////////////////////////////////////////////////////


//----------------< 多项式构造 > ----------------//
void CreateMulti(Element *head)
{
    Element *pre,*cur;
    pre = head;
    int number,i;               // number为多项式项数，i为循环变量
    printf("\n请输入该多项式的项数：\n");
        scanf("%d",&number);
    for(i=0;i<number;i++)
    {
        cur = (Element*)malloc(sizeof(Element));
        printf("请输入第%d项的系数：\n",i);
        scanf("%f",&cur->coef);
        printf("请输入第%d项的次数：\n",i);
        scanf("%f",&cur->exp);
        pre->next = cur;        // 连接
        pre = cur;
    }
    pre->next = NULL;           // 最后一项的next设为NULL
}
//----------------< 多项式构造 > ----------------//

//----------------< 多项式相加 > ----------------//
Element* Add(Element* a,Element* b)
{
    // 创建存放结果的多项式C的头指针
    Element *c = (Element*)malloc(sizeof(Element));
    Element *pa,*pb,*pc_pre,*pc_cur;
    pc_pre = c;
    pa = a->next;
    pb = b->next;
    while (pa && pb)                    // 当进行相加的两个多项式不为空且都未遍历完时
    {
        if (pa->exp == pb->exp)         // 次数相等，进行相加 
        {
            if (pa->coef+pb->coef !=0)  // 当相加后系数不为0时，存入C 
            {
                pc_cur = (Element*)malloc(sizeof(Element));
                pc_cur->coef = pa->coef + pb->coef;
                pc_cur->exp = pa->exp;
                pc_pre->next = pc_cur;
                pc_pre = pc_cur;
            }
            pa = pa->next;
            pb = pb->next;
        }
        else if (pa->exp < pb->exp)     // 当A的当前项次数小时，将其存入C 
        {
            pc_cur = (Element*)malloc(sizeof(Element));
            pc_cur->coef = pa->coef;
            pc_cur->exp = pa->exp;
            pc_pre->next = pc_cur;
            pc_pre = pc_cur; 
            pa = pa->next;              // 继续遍历A的下一项
        }
        else                            // 当B的当前项次数小时，将其存入C
        {
            pc_cur = (Element*)malloc(sizeof(Element));
            pc_cur->coef = pb->coef;
            pc_cur->exp = pb->exp;
            pc_pre->next = pc_cur;
            pc_pre = pc_cur; 
            pb = pb->next;              // 继续遍历B的下一项
        }
    }
    // 上述循环结束，可能是二者都遍历完，也可能是其中一个多项式有剩余项
    if (pb == NULL)
    {
        while (pa)                          // 将长的多项式的剩余项存入C 
        {
            pc_cur = (Element*)malloc(sizeof(Element));
            pc_cur->coef = pa->coef;
            pc_cur->exp = pa->exp;
            pc_pre->next = pc_cur;
            pc_pre = pc_cur; 
            pa = pa->next;
        }
    }
    else if(pa == NULL)
    {
        while (pb)                          // 将长的多项式的剩余项存入C 
        {
            pc_cur = (Element*)malloc(sizeof(Element));
            pc_cur->coef = pb->coef;
            pc_cur->exp = pb->exp;
            pc_pre->next = pc_cur;
            pc_pre = pc_cur; 
            pb = pb->next;
        } 
    }
    pc_pre->next = NULL;
    return c;
}
//----------------< 多项式相加 > ----------------//

//----------------< 多项式显示 > ----------------//
void ShowAll(Element *head)
{
    Element *p = head;
    int i = 0;                          // 计数变量
    while(p->next != NULL)
    {
        p=p->next;
        if(i==0)                        // 如果是第一项
        {
            if(p->exp !=0)              // 次数不为0，显示 x^
                printf(" %.2fx^%.2f",p->coef,p->exp);
            else
                printf(" %.2f",p->coef);
        }
        else                            // 不是第一项
        {
            if(p->exp >1)               // 次数大于1，显示 x^
            {
                if(p->coef>0)           // 系数大于0，显示 +
                    printf(" %s%.2fx^%.2f","+",p->coef,p->exp);
                else
                    printf(" %.2fx^%.2f",p->coef,p->exp);
            }
            else if(p->exp ==1)         // 次数为1，显示 x
            {
                if(p->coef>0)           // 系数大于0，显示 +
                    printf(" %s%.2fx","+",p->coef);
                else
                    printf(" %.2fx",p->coef);
            }
            else                        // 次数为0，只显示系数
            {
                if(p->coef>0)           // 系数大于0，显示 +
                    printf(" %s%.2f","+",p->coef);
                else
                    printf(" %.2f",p->coef);
            }
        }       
    }
}
//----------------< 多项式显示 > ----------------//



/////////////////////////////////////////////////////////////////


int main()
{
	// 创建多项式A和B
    Element *A,*B;
    A = (Element*)malloc(sizeof(Element));
    B = (Element*)malloc(sizeof(Element));
    CreateMulti(A); ShowAll(A);
    CreateMulti(B); ShowAll(B);
    // 将A、B相加并显示结果多项式C
    printf("\n结果为：\n");
    ShowAll(Add(A,B));
}
