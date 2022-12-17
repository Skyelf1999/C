#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int createMaze();                   //创建随机迷宫
int createFreeMaze();               //创建自定义迷宫
void createWall();                  //创建迷宫外墙
void show_mazemap();
int visit(int row2, int col2);

int startI = 1, startJ = 1;         // 入口
int success = 0;
int k=0,l;                          // 循环变量
int end_code;                       // 主函数结束密码

//迷宫数组，row 行，col 列，2代表墙壁，0代表通道
int maze[100][100];
int row = 0;
int col = 0;

// 节点结构体，x 行数，y 列数，cost 估价，par 父节点在数组中的位置
typedef struct 
{ 
    int x = -1; int y = -1; 
    int g = -1; 
    int h;
    int cost;
    int par = -1;
} node;
node helper;
node open[1000];                    // open表
node closed[1000];                  // closed表
int open_i;                         // open表最后一个节点的位置
int closed_i;                       // closed表最后一个节点的位置


//////////////////////////////////////////////////////////////////////////////////////


//-----------------------<创建迷宫外墙>-----------------------//
void createWall()
{
	int i;
    //创建迷宫外墙,第一行、第一列、最后一行、最后一列均为墙壁
    for (i = 0; i < col; i++)               //第一行
        maze[0][i] = 2;
    for (i = 1; i < row; i++)               //第一列
        maze[i][0] = 2;
    for (i = 1; i < col; i++)               //最后一行
        maze[row - 1][i] = 2;
    for (i = 1; i < row - 1; i++)           //最后一列
        maze[i][col - 1] = 2;
}
//-----------------------<创建迷宫外墙>-----------------------//


//-----------------------<创建随机迷宫>-----------------------//
int createMaze()
{
    int i;
    srand(time(0));
    for (int i = 1; i < row - 1; i++)       
    {
        for (int j = 1; j < col - 1; j++)
        {
            if ((rand() % 100 + 1) % 4 == 0)
                maze[i][j] = 2;
            else
                maze[i][j] = 0;
        }
    }
    maze[1][1] = 0;                         // 迷宫起点
    if(maze[1][2]+maze[2][1] == 4)          // 如果迷宫起点被包围
    {
        i = rand()%2;
        switch (i)
        {
            case 0:
                maze[1][2] = 0;break;
            case 1:
                maze[2][1] = 0;break;
        }
    }
    maze[row - 2][col - 2] = 0;             // 迷宫终点
    if(maze[row - 2][col - 3]+maze[row - 3][col - 2]==4)
    {
        i = rand()%2;
        switch (i)
        {
            case 0:
                maze[row - 2][col - 3] = 0;break;
            case 1:
                maze[row - 3][col - 2] = 0;break;
        }
    }
    return 0;
}
//-----------------------<创建随机迷宫>-----------------------//


//-----------------------<创建自定义迷宫>-----------------------//
int createFreeMaze()
{
    for (int i = 1; i < row - 1; i++)
    {
        //第一行，第一格为入口
        if (i == 1)
        {
            printf("迷宫第%d行，共%d格：  ", i, col - 3);
            for (int j = 2; j < col - 1; j++)
                scanf("%d", &maze[i][j]);
        }
        //最后一行,最后一格为出口
        else if (i == row - 2)
        {
            printf("迷宫第%d行，共%d格：", i, col - 3);
            for (int j = 1; j < col - 2; j++)
                scanf("%d", &maze[i][j]);
        }
        else
        {
            printf("迷宫第%d行，共%d格：", i, col - 2);
            for (int j = 1; j < col - 1; j++)
                scanf("%d", &maze[i][j]);
        }
    }
    maze[1][1] = 0;                         // 迷宫起点
    int i;
    if(maze[1][2]+maze[2][1] == 4)          // 如果迷宫起点被包围
    {
        i = rand()%2;
        switch (i)
        {
            case 0:
                maze[1][2] = 0;break;
            case 1:
                maze[2][1] = 0;break;
        }
    }
    maze[row - 2][col - 2] = 0;             // 迷宫终点
    if(maze[row - 2][col - 3]+maze[row - 3][col - 2]==4)
    {
        i = rand()%2;
        switch (i)
        {
            case 0:
                maze[row - 2][col - 3] = 0;break;
            case 1:
                maze[row - 3][col - 2] = 0;break;
        }
    }
    return 0;
}
//-----------------------<创建自定义迷宫>-----------------------//


//-----------------------<寻找路径·盲目搜索>-----------------------//
int visit(int row2, int col2)
{
    int endI = row - 2, endJ = col - 2;      // 标记出口位置
    // 该点走过，标记为1
    maze[row2][col2] = 1;
    // 走到终点，成功
    if (row2 == endI && col2 == endJ) success = 1;
    // 向四个方向递归调用函数visit()
    if (success != 1 && maze[row2][col2 + 1] == 0)
        visit(row2, col2 + 1);              // 向右
    if (success != 1 && maze[row2 + 1][col2] == 0)
        visit(row2 + 1, col2);              // 向下
    if (success != 1 && maze[row2][col2 - 1] == 0)
        visit(row2, col2 - 1);              // 向左
    if (success != 1 && maze[row2 - 1][col2] == 0)
        visit(row2 - 1, col2);              // 向上
    // 该点走过，但没成功，则该点重新置为0
    if (success != 1) maze[row2][col2] = 0;

    return success;
}
//-----------------------<寻找路径·盲目搜索>-----------------------//


//-----------------------<判断节点是否可以扩展>-----------------------//
int judge_available(node n)
{
    /*
        可以通过计算给定节点上下左右在maze对应位置的值来判断是否可以扩展
        能扩展，上下左右必有一个是0
    */
    int result = maze[n.x-1][n.y]*maze[n.x+1][n.y]*maze[n.x][n.y-1]*maze[n.x][n.y+1];
    // printf("\n节点(%d,%d)的上下左右分别是：%d,%d,%d,%d；判断乘积为：%d",n.x,n.y,maze[n.x-1][n.y],maze[n.x+1][n.y],maze[n.x][n.y-1],maze[n.x][n.y+1],result); 
    if (result > 0) return 0;
    else return 1; 
}
//-----------------------<判断节点是否可以扩展>-----------------------//


//-----------------------<根据坐标判断open表中节点是否重复>-----------------------//
int judge_same(int x,int y)
{
    for(int i=0;i<=open_i;i++)
    {
        if((open[open_i].x==x) && (open[open_i].y==y))
        return 0;
    }
    return 1;
}
//-----------------------<判断open表中节点是否重复>-----------------------//


//-----------------------<扩展closed表中的当前节点>-----------------------//
void expand(node n)
{
    printf("\n扩展点(%d,%d)……",closed[closed_i].x,closed[closed_i].y);
    if(maze[n.x-1][n.y]==0)                 // 上可扩展
    {
        if(judge_same(n.x-1,n.y))
        {
            open_i++;
            open[open_i]=closed[closed_i];
            open[open_i].x=closed[closed_i].x-1;
            open[open_i].g=closed[closed_i].g+1;
            open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
            open[open_i].cost = open[open_i].g + open[open_i].h; 
            printf("\n将点(%d,%d)装入open表……",open[open_i].x,open[open_i].y);
            open[open_i].par=closed_i;
        }
    }
    if(maze[n.x+1][n.y]==0)                 // 下可扩展
    {
        if(judge_same(n.x+1,n.y))
        {
            open_i++;
            open[open_i]=closed[closed_i];
            open[open_i].x=closed[closed_i].x+1;
            open[open_i].g=closed[closed_i].g+1;
            open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
            open[open_i].cost = open[open_i].g + open[open_i].h;
            printf("\n将点(%d,%d)装入open表……",open[open_i].x,open[open_i].y);
            open[open_i].par=closed_i;
        }
    }
    if(maze[n.x][n.y-1]==0)                 // 左可扩展
    {
        if(judge_same(n.x,n.y-1))
        {
            open_i++;
            open[open_i]=closed[closed_i];
            open[open_i].y=closed[closed_i].y-1;
            open[open_i].g=closed[closed_i].g+1;
            open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
            open[open_i].cost = open[open_i].g + open[open_i].h;
            printf("\n将点(%d,%d)装入open表……",open[open_i].x,open[open_i].y);
            open[open_i].par=closed_i;
        }
    }
    if(maze[n.x][n.y+1]==0)                 // 右可扩展
    {
        if(judge_same(n.x,n.y+1))
        {
            open_i++;
            open[open_i]=closed[closed_i];
            open[open_i].y=closed[closed_i].y+1;
            open[open_i].g=closed[closed_i].g+1;
            open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
            open[open_i].cost = open[open_i].g + open[open_i].h;
            printf("\n将点(%d,%d)装入open表……",open[open_i].x,open[open_i].y);
            open[open_i].par=closed_i;
        }
    }
    printf("\nopen表中还有%d个点",open_i+1);
}
//-----------------------<扩展closed表中的当前节点>-----------------------//


//-----------------------<根据cost对open表进行排序>-----------------------//
void order_open()
{
    for(int i = 0; i <= open_i; i++)
    {
        for(int j = i + 1; j <= open_i; j++)
        {
            if(open[j].cost < open[i].cost) //如果后一个元素小于前一个元素则交换
            {   
                helper = open[i];
                open[i] = open[j];
                open[j] = helper;
            }
        }
    }
}
//-----------------------<根据cost对open表进行排序>-----------------------//


//-----------------------<显示open表>-----------------------//
void show_open()
{
    printf("\n输出open表：\n");
    for(int i=0;i<=open_i;i++)
    {
        printf("节点：(%d,%d)；估价：%d\n",open[i].x,open[i].y,open[i].cost);
    }
}
//-----------------------<显示open表>-----------------------//


//-----------------------<更新路径>-----------------------//
void update_path()
{
    int i=closed_i,j;
    while(i != -1)
    {
        maze[closed[i].x][closed[i].y] = 9;
        i = closed[i].par;
    }
}
//-----------------------<更新路径>-----------------------//


//-----------------------<寻找路径·启发式搜索·A算法>-----------------------//
int betterVisit()
{
    open_i = closed_i = -1;                                                 // 6
    // 1. 把初始节点放入open表中，并计算估价函数
    open_i++;
    open[open_i].x = open[open_i].y = 1;
    open[open_i].g = 0;
    open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
    open[open_i].cost = open[open_i].g + open[open_i].h;

    while(1)
    {
        // 2. 如果open表为空，问题无解
        if(open_i == -1) 
        {
            printf("\n问题无解！\n");
            return 0;
        }
        show_open();
        // 3. 把open表的第一个节点转移到closed表中；
        printf("\n将位置为(%d,%d)的点放入closed表……",open[0].x,open[0].y);
        closed[++closed_i] = open[0];
        if(open_i == 0) open_i--;
        else
        {
            for(int i=0;i<open_i;i++) open[i]=open[i+1];
            open_i--;
        } 
        printf("\nopen表中还有%d个点",open_i+1);
        maze[closed[closed_i].x][closed[closed_i].y] = 1;
        show_mazemap();
        // 4. 考察此节点是否为终点，如果是则成功退出
        if(closed[closed_i].x==row-2 && closed[closed_i].y==col-2)
        {
            printf("\n算法成功\n");
            update_path();
            return 1;
        }
         // 5. 若该节点不可扩展，转第2步
         if(judge_available(closed[closed_i])==0)
         {
            printf("\n该节点不可扩展！");
            printf("\n=======开始下一次判断=======");
            continue;
         }
         // 6. 扩展当前节点，将子节点放入open表
         expand(closed[closed_i]);
         // 7. 根据节点的估价函数值cost对open表进行排序
         order_open();
         printf("\n=======开始下一次判断=======\n");
    }
    
};
//-----------------------<寻找路径·启发式搜索·A算法>-----------------------//


//-----------------------<显示迷宫>-----------------------//
void show_maze()
{
    int i,j;
    printf("\n显示迷宫：\n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (maze[i][j] == 2) printf(" █");
            else printf("  ");
        }
        printf("\n");
    }
}
//-----------------------<显示迷宫>-----------------------//


//-----------------------<显示迷宫矩阵>-----------------------//
void show_mazemap()
{
    int i,j;
    printf("\n显示迷宫矩阵：\n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d",maze[i][j]);
        }
        printf("\n");
    }
}
//-----------------------<显示迷宫矩阵>-----------------------//


//-----------------------<显示路径>-----------------------//
void show_process()
{
    int i,j;
    printf("\n显示路径：\n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (maze[i][j] == 2) printf(" █");
            else if (maze[i][j] == 1) printf("?");   // ◇
            else if (maze[i][j] == 9) printf("！");
            else printf("  ");
        }
        printf("\n");
    }
}
//-----------------------<显示路径>-----------------------//


//////////////////////////////////////////////////////////////////////////////////////


int main()
{
    printf("请定义迷宫问题终止密码：");
    scanf("%d",&end_code);
    while(1)
    {   
        k++;
        printf("\n开始第%d次迷宫问题解决\n",k);
        printf("请输入迷宫行数row(0<row<100)：");
        scanf("%d", &row);
        printf("请输入迷宫列数col(0<col<100)：");
        scanf("%d", &col);

        createWall();                           // 创建迷宫外墙

        int choice;
        printf("\n请选择创建随机迷宫还是自定义迷宫（1为随机迷宫，2为自定义迷宫）:");
        scanf("%d", &choice);
        if (choice == 1)                        // 创建随机迷宫
        {
            createMaze();                       
        }
        else if (choice == 2)                   // 创随自定义迷宫
        {
            printf("\n请输入自定义迷宫的墙壁和通道，2代表墙壁，0代表通道\n");
            createFreeMaze();                   
        }
        show_maze();
        show_mazemap();

        printf("\n请选择用何种方法解决问题（1为盲目搜索，2为启发式搜索）：");
        scanf("%d",&choice);
        if(choice == 1)
        {
            printf("用盲目搜索解决问题……\n");
            if (visit(startI, startJ) == 0) printf("\n没有找到出口！\n");
            else 
            {
                show_process(); show_mazemap();
            }
        }
        else if(choice == 2)
        {
            printf("用启发式搜索解决问题……\n");
            if(betterVisit()==1)
            {
                show_process(); show_mazemap();
            } 
        }

        printf("\n如果需要退出，请输入终止密码；想要继续，请输入任意数字：");
        scanf("%d",&l);
        if(l==end_code) break;
        system("pause");
    }

    printf("\n迷宫问题结束\n");
    return 0;
}
