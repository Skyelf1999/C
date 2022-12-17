#include <stdio.h>
#include <string.h>

#define N 8                        // 叶子节点数，也是初始的待构造数据数
#define M 2*N-1                    // 哈夫曼树节点总数

// 哈夫曼树节点结构体，char 节点数据，weight 权值，parent/left/right 父、子节点位置
typedef struct
{ char data[10]; int weight=0; int parent; int left; int right;} Huff_node;

// 编码用结构体，code 哈夫曼编码，start 从start的位置开始读取code中的编码 
typedef struct 
{ char code[N]={'-','-','-','-','-','-','-','-'}; int length; } HuffCode;


//////////////////////////////////////////////////////////////////////////////

//----------------<哈夫曼树的叶子结点的创建>----------------//
void nodeInput(Huff_node tree[])                                                                 // 5N+4   
{
    printf("\n\n//--------------<开始输入初始节点>--------------//\n");
    int i;
    printf("\n请输入所有初始节点的数据并赋权值：");
    for(i=0;i<N;i++)                                                                                
    {
        printf("\n\n请输入第%d个初始节点的数据：",i+1);
        scanf("%s",&tree[i].data);
        printf("\n请输入第%d个初始节点的权值：",i+1);
        scanf("%d",&tree[i].weight);
        printf("\n第%d个初始节点的数据为：%s；权值为：%d",i+1,tree[i].data,tree[i].weight);
    }
    printf("\n\n//--------------<初始节点输入完毕>--------------//\n\n");
}
//----------------<哈夫曼树的叶子结点的创建>----------------//

//----------------<哈夫曼树的构造>----------------//
void createHuffTree(Huff_node tree[])                                           // 7.5N^2-3.5N-1
{
    printf("\n\n//--------------<开始进行哈夫曼树的构造>--------------//\n");     // M+4=2N+3
    int i,j;
    int min_1,min_2;                // 记录现有节点中最小的两个权值
    int node_left,node_right;       // 记录两个最小权值所对应的节点的位置
    for(i=0;i<M;i++)                // 为所有节点的指向变量赋初值
        tree[i].parent = tree[i].left = tree[i].right = -1;

    // 前N个为初始叶子结点，构成的子树的根节点放在后面，从第N+1个(序号为N)开始
    for(i=N;i<M;i++)                                                            // 7.5N^2-5.5N-4                
    {
        min_1 = min_2 = 999;                                                    // 2
        node_left = node_right = -1;
        for(j=0;j<i;j++)            // 在现有节点中寻找权值最小的两个节点构成子树   (4~6)*i
        {
            if(tree[j].parent==-1)  // 当前被遍历节点还未参与构造二叉树             
            {
                // 权值最小的节点放在左边
                if(tree[j].weight < min_1)
                {
                    min_2 = min_1;  node_right = node_left;
                    min_1 = tree[j].weight;
                    node_left = j;
                }
                // 权值次小的节点放在右边
                else if(tree[j].weight < min_2)
                {
                    min_2 = tree[j].weight;
                    node_right = j;
                }
            }
        }
        // 用选出的两个节点构成子树                                                  5
        tree[i].weight =tree[node_left].weight + tree[node_right].weight;
        tree[i].left = node_left;
        tree[i].right = node_right; 
        // 为用到的两个节点设置父节点，这两个节点之后不参与树的构建
        tree[node_left].parent = i;
        tree[node_right].parent = i;
    }
    printf("\n//--------------<哈夫曼树构造完毕>--------------//\n\n");
}
//----------------<哈夫曼树的构造>----------------//

//----------------<哈夫曼树编码>----------------//
void coding(Huff_node tree[],HuffCode codes[])
{
    printf("\n\n//--------------<开始进行哈夫曼编码>--------------//\n");           // 3
    // i为当前进行编码的节点的位置，k为其编码的位数
    // cur和pre分别为编码时遍历到的当前节点和其父节点
    int  i,k,cur,pre;
    char helper;
    for(i=0;i<N;i++)                // 为所有初始节点(叶子结点)编码                 // N*(5.5length+4.25)   log(2)N<length<N
    {
        cur=i;                                                                // 3
        pre = tree[cur].parent;     // pre为当前节点的父节点的号码
        k=0;                        // k记录节点i的码的位数
        while(pre!=-1)              // 循环编码直到根节点结束                   4*length
        {
            // 判断是左子还是右子
            if(tree[pre].left==cur) codes[i].code[k]='0';
            else codes[i].code[k]='1';
            k++;
            cur=pre;
            pre = tree[pre].parent; // 向上遍历
        }
        codes[i].length = k;         // 记录位置为i的节点的编码位数             2   
        printf("\n倒序编码：%s\n",codes[i].code);
        // 将存储编码的codes[].code倒序排列，方便输出
        for(k=codes[i].length-1;k>=(codes[i].length+codes[i].length%2)/2;k--)   // 1.5length-0.75
        {
            helper = codes[i].code[k];
            codes[i].code[k] = codes[i].code[codes[i].length-1-k];
            codes[i].code[codes[i].length-1-k] = helper;
        }
    }
    printf("\n//--------------<哈夫曼编码完成>--------------//\n\n");
}
//----------------<哈夫曼树编码>----------------//

//----------------<输出节点数据和其编码>----------------//
void outputAll(Huff_node tree[],HuffCode codes[])
{
    printf("\n\n//--------------<开始输出节点数据、权值、编码>--------------//\n");
    int i;
    for(i=0;i<N;i++)
    {
        printf("\n第%d项：数据 %s；权值 %d；编码 %s\n",i+1,tree[i].data,tree[i].weight,codes[i].code);
    }
    printf("\n//--------------<输出完毕>--------------//\n\n");
}
//----------------<输出节点数据和其编码>----------------//

//----------------<输出哈夫曼树表>----------------//
void outputList(Huff_node tree[])
{
    printf("\n\n//--------------<输出哈夫曼树表>--------------//\n");
    int i;
    for(i=0;i<M;i++)
    {
        printf("\n编号：%d；权值：%d；父节点位置：%d；左子位置：%d；右子位置：%d；\n",i,tree[i].weight,tree[i].parent,tree[i].left,tree[i].right);
    }
    printf("\n//--------------<输出完毕>--------------//\n\n");
}
//----------------<输出哈夫曼树表>----------------//

//////////////////////////////////////////////////////////////////////////////


int main()
{
    Huff_node tree[M];              // 用于存放哈夫曼树的数组                               1
    HuffCode codes[N];              // 用于存放树中相应位置节点的编码的数组                   1
    nodeInput(tree);                // 输入初始节点                                        5N+4
    createHuffTree(tree);           // 构造哈夫曼树                                        7.5N^2-3.5N-1
    //outputList(tree);             // 输出哈夫曼树表
    coding(tree,codes);             // 编码                                               N*(5.5length+4.25)+3   log(2)N<length<N
    outputAll(tree,codes);          // 输出编码结果                                        N+2
}
