#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int createMaze();                   //��������Թ�
int createFreeMaze();               //�����Զ����Թ�
void createWall();                  //�����Թ���ǽ
void show_mazemap();
int visit(int row2, int col2);

int startI = 1, startJ = 1;         // ���
int success = 0;
int k=0,l;                          // ѭ������
int end_code;                       // ��������������

//�Թ����飬row �У�col �У�2����ǽ�ڣ�0����ͨ��
int maze[100][100];
int row = 0;
int col = 0;

// �ڵ�ṹ�壬x ������y ������cost ���ۣ�par ���ڵ��������е�λ��
typedef struct 
{ 
    int x = -1; int y = -1; 
    int g = -1; 
    int h;
    int cost;
    int par = -1;
} node;
node helper;
node open[1000];                    // open��
node closed[1000];                  // closed��
int open_i;                         // open�����һ���ڵ��λ��
int closed_i;                       // closed�����һ���ڵ��λ��


//////////////////////////////////////////////////////////////////////////////////////


//-----------------------<�����Թ���ǽ>-----------------------//
void createWall()
{
	int i;
    //�����Թ���ǽ,��һ�С���һ�С����һ�С����һ�о�Ϊǽ��
    for (i = 0; i < col; i++)               //��һ��
        maze[0][i] = 2;
    for (i = 1; i < row; i++)               //��һ��
        maze[i][0] = 2;
    for (i = 1; i < col; i++)               //���һ��
        maze[row - 1][i] = 2;
    for (i = 1; i < row - 1; i++)           //���һ��
        maze[i][col - 1] = 2;
}
//-----------------------<�����Թ���ǽ>-----------------------//


//-----------------------<��������Թ�>-----------------------//
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
    maze[1][1] = 0;                         // �Թ����
    if(maze[1][2]+maze[2][1] == 4)          // ����Թ���㱻��Χ
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
    maze[row - 2][col - 2] = 0;             // �Թ��յ�
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
//-----------------------<��������Թ�>-----------------------//


//-----------------------<�����Զ����Թ�>-----------------------//
int createFreeMaze()
{
    for (int i = 1; i < row - 1; i++)
    {
        //��һ�У���һ��Ϊ���
        if (i == 1)
        {
            printf("�Թ���%d�У���%d��  ", i, col - 3);
            for (int j = 2; j < col - 1; j++)
                scanf("%d", &maze[i][j]);
        }
        //���һ��,���һ��Ϊ����
        else if (i == row - 2)
        {
            printf("�Թ���%d�У���%d��", i, col - 3);
            for (int j = 1; j < col - 2; j++)
                scanf("%d", &maze[i][j]);
        }
        else
        {
            printf("�Թ���%d�У���%d��", i, col - 2);
            for (int j = 1; j < col - 1; j++)
                scanf("%d", &maze[i][j]);
        }
    }
    maze[1][1] = 0;                         // �Թ����
    int i;
    if(maze[1][2]+maze[2][1] == 4)          // ����Թ���㱻��Χ
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
    maze[row - 2][col - 2] = 0;             // �Թ��յ�
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
//-----------------------<�����Զ����Թ�>-----------------------//


//-----------------------<Ѱ��·����äĿ����>-----------------------//
int visit(int row2, int col2)
{
    int endI = row - 2, endJ = col - 2;      // ��ǳ���λ��
    // �õ��߹������Ϊ1
    maze[row2][col2] = 1;
    // �ߵ��յ㣬�ɹ�
    if (row2 == endI && col2 == endJ) success = 1;
    // ���ĸ�����ݹ���ú���visit()
    if (success != 1 && maze[row2][col2 + 1] == 0)
        visit(row2, col2 + 1);              // ����
    if (success != 1 && maze[row2 + 1][col2] == 0)
        visit(row2 + 1, col2);              // ����
    if (success != 1 && maze[row2][col2 - 1] == 0)
        visit(row2, col2 - 1);              // ����
    if (success != 1 && maze[row2 - 1][col2] == 0)
        visit(row2 - 1, col2);              // ����
    // �õ��߹�����û�ɹ�����õ�������Ϊ0
    if (success != 1) maze[row2][col2] = 0;

    return success;
}
//-----------------------<Ѱ��·����äĿ����>-----------------------//


//-----------------------<�жϽڵ��Ƿ������չ>-----------------------//
int judge_available(node n)
{
    /*
        ����ͨ����������ڵ�����������maze��Ӧλ�õ�ֵ���ж��Ƿ������չ
        ����չ���������ұ���һ����0
    */
    int result = maze[n.x-1][n.y]*maze[n.x+1][n.y]*maze[n.x][n.y-1]*maze[n.x][n.y+1];
    // printf("\n�ڵ�(%d,%d)���������ҷֱ��ǣ�%d,%d,%d,%d���жϳ˻�Ϊ��%d",n.x,n.y,maze[n.x-1][n.y],maze[n.x+1][n.y],maze[n.x][n.y-1],maze[n.x][n.y+1],result); 
    if (result > 0) return 0;
    else return 1; 
}
//-----------------------<�жϽڵ��Ƿ������չ>-----------------------//


//-----------------------<���������ж�open���нڵ��Ƿ��ظ�>-----------------------//
int judge_same(int x,int y)
{
    for(int i=0;i<=open_i;i++)
    {
        if((open[open_i].x==x) && (open[open_i].y==y))
        return 0;
    }
    return 1;
}
//-----------------------<�ж�open���нڵ��Ƿ��ظ�>-----------------------//


//-----------------------<��չclosed���еĵ�ǰ�ڵ�>-----------------------//
void expand(node n)
{
    printf("\n��չ��(%d,%d)����",closed[closed_i].x,closed[closed_i].y);
    if(maze[n.x-1][n.y]==0)                 // �Ͽ���չ
    {
        if(judge_same(n.x-1,n.y))
        {
            open_i++;
            open[open_i]=closed[closed_i];
            open[open_i].x=closed[closed_i].x-1;
            open[open_i].g=closed[closed_i].g+1;
            open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
            open[open_i].cost = open[open_i].g + open[open_i].h; 
            printf("\n����(%d,%d)װ��open����",open[open_i].x,open[open_i].y);
            open[open_i].par=closed_i;
        }
    }
    if(maze[n.x+1][n.y]==0)                 // �¿���չ
    {
        if(judge_same(n.x+1,n.y))
        {
            open_i++;
            open[open_i]=closed[closed_i];
            open[open_i].x=closed[closed_i].x+1;
            open[open_i].g=closed[closed_i].g+1;
            open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
            open[open_i].cost = open[open_i].g + open[open_i].h;
            printf("\n����(%d,%d)װ��open����",open[open_i].x,open[open_i].y);
            open[open_i].par=closed_i;
        }
    }
    if(maze[n.x][n.y-1]==0)                 // �����չ
    {
        if(judge_same(n.x,n.y-1))
        {
            open_i++;
            open[open_i]=closed[closed_i];
            open[open_i].y=closed[closed_i].y-1;
            open[open_i].g=closed[closed_i].g+1;
            open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
            open[open_i].cost = open[open_i].g + open[open_i].h;
            printf("\n����(%d,%d)װ��open����",open[open_i].x,open[open_i].y);
            open[open_i].par=closed_i;
        }
    }
    if(maze[n.x][n.y+1]==0)                 // �ҿ���չ
    {
        if(judge_same(n.x,n.y+1))
        {
            open_i++;
            open[open_i]=closed[closed_i];
            open[open_i].y=closed[closed_i].y+1;
            open[open_i].g=closed[closed_i].g+1;
            open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
            open[open_i].cost = open[open_i].g + open[open_i].h;
            printf("\n����(%d,%d)װ��open����",open[open_i].x,open[open_i].y);
            open[open_i].par=closed_i;
        }
    }
    printf("\nopen���л���%d����",open_i+1);
}
//-----------------------<��չclosed���еĵ�ǰ�ڵ�>-----------------------//


//-----------------------<����cost��open���������>-----------------------//
void order_open()
{
    for(int i = 0; i <= open_i; i++)
    {
        for(int j = i + 1; j <= open_i; j++)
        {
            if(open[j].cost < open[i].cost) //�����һ��Ԫ��С��ǰһ��Ԫ���򽻻�
            {   
                helper = open[i];
                open[i] = open[j];
                open[j] = helper;
            }
        }
    }
}
//-----------------------<����cost��open���������>-----------------------//


//-----------------------<��ʾopen��>-----------------------//
void show_open()
{
    printf("\n���open��\n");
    for(int i=0;i<=open_i;i++)
    {
        printf("�ڵ㣺(%d,%d)�����ۣ�%d\n",open[i].x,open[i].y,open[i].cost);
    }
}
//-----------------------<��ʾopen��>-----------------------//


//-----------------------<����·��>-----------------------//
void update_path()
{
    int i=closed_i,j;
    while(i != -1)
    {
        maze[closed[i].x][closed[i].y] = 9;
        i = closed[i].par;
    }
}
//-----------------------<����·��>-----------------------//


//-----------------------<Ѱ��·��������ʽ������A�㷨>-----------------------//
int betterVisit()
{
    open_i = closed_i = -1;                                                 // 6
    // 1. �ѳ�ʼ�ڵ����open���У���������ۺ���
    open_i++;
    open[open_i].x = open[open_i].y = 1;
    open[open_i].g = 0;
    open[open_i].h = (row-2-open[open_i].x) + (col-2-open[open_i].y);
    open[open_i].cost = open[open_i].g + open[open_i].h;

    while(1)
    {
        // 2. ���open��Ϊ�գ������޽�
        if(open_i == -1) 
        {
            printf("\n�����޽⣡\n");
            return 0;
        }
        show_open();
        // 3. ��open��ĵ�һ���ڵ�ת�Ƶ�closed���У�
        printf("\n��λ��Ϊ(%d,%d)�ĵ����closed����",open[0].x,open[0].y);
        closed[++closed_i] = open[0];
        if(open_i == 0) open_i--;
        else
        {
            for(int i=0;i<open_i;i++) open[i]=open[i+1];
            open_i--;
        } 
        printf("\nopen���л���%d����",open_i+1);
        maze[closed[closed_i].x][closed[closed_i].y] = 1;
        show_mazemap();
        // 4. ����˽ڵ��Ƿ�Ϊ�յ㣬�������ɹ��˳�
        if(closed[closed_i].x==row-2 && closed[closed_i].y==col-2)
        {
            printf("\n�㷨�ɹ�\n");
            update_path();
            return 1;
        }
         // 5. ���ýڵ㲻����չ��ת��2��
         if(judge_available(closed[closed_i])==0)
         {
            printf("\n�ýڵ㲻����չ��");
            printf("\n=======��ʼ��һ���ж�=======");
            continue;
         }
         // 6. ��չ��ǰ�ڵ㣬���ӽڵ����open��
         expand(closed[closed_i]);
         // 7. ���ݽڵ�Ĺ��ۺ���ֵcost��open���������
         order_open();
         printf("\n=======��ʼ��һ���ж�=======\n");
    }
    
};
//-----------------------<Ѱ��·��������ʽ������A�㷨>-----------------------//


//-----------------------<��ʾ�Թ�>-----------------------//
void show_maze()
{
    int i,j;
    printf("\n��ʾ�Թ���\n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (maze[i][j] == 2) printf(" ��");
            else printf("  ");
        }
        printf("\n");
    }
}
//-----------------------<��ʾ�Թ�>-----------------------//


//-----------------------<��ʾ�Թ�����>-----------------------//
void show_mazemap()
{
    int i,j;
    printf("\n��ʾ�Թ�����\n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d",maze[i][j]);
        }
        printf("\n");
    }
}
//-----------------------<��ʾ�Թ�����>-----------------------//


//-----------------------<��ʾ·��>-----------------------//
void show_process()
{
    int i,j;
    printf("\n��ʾ·����\n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (maze[i][j] == 2) printf(" ��");
            else if (maze[i][j] == 1) printf("?");   // ��
            else if (maze[i][j] == 9) printf("��");
            else printf("  ");
        }
        printf("\n");
    }
}
//-----------------------<��ʾ·��>-----------------------//


//////////////////////////////////////////////////////////////////////////////////////


int main()
{
    printf("�붨���Թ�������ֹ���룺");
    scanf("%d",&end_code);
    while(1)
    {   
        k++;
        printf("\n��ʼ��%d���Թ�������\n",k);
        printf("�������Թ�����row(0<row<100)��");
        scanf("%d", &row);
        printf("�������Թ�����col(0<col<100)��");
        scanf("%d", &col);

        createWall();                           // �����Թ���ǽ

        int choice;
        printf("\n��ѡ�񴴽�����Թ������Զ����Թ���1Ϊ����Թ���2Ϊ�Զ����Թ���:");
        scanf("%d", &choice);
        if (choice == 1)                        // ��������Թ�
        {
            createMaze();                       
        }
        else if (choice == 2)                   // �����Զ����Թ�
        {
            printf("\n�������Զ����Թ���ǽ�ں�ͨ����2����ǽ�ڣ�0����ͨ��\n");
            createFreeMaze();                   
        }
        show_maze();
        show_mazemap();

        printf("\n��ѡ���ú��ַ���������⣨1ΪäĿ������2Ϊ����ʽ��������");
        scanf("%d",&choice);
        if(choice == 1)
        {
            printf("��äĿ����������⡭��\n");
            if (visit(startI, startJ) == 0) printf("\nû���ҵ����ڣ�\n");
            else 
            {
                show_process(); show_mazemap();
            }
        }
        else if(choice == 2)
        {
            printf("������ʽ����������⡭��\n");
            if(betterVisit()==1)
            {
                show_process(); show_mazemap();
            } 
        }

        printf("\n�����Ҫ�˳�����������ֹ���룻��Ҫ�������������������֣�");
        scanf("%d",&l);
        if(l==end_code) break;
        system("pause");
    }

    printf("\n�Թ��������\n");
    return 0;
}
