#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/*
    编程说明exit()与_exit()的区别
    1.exit()会清除缓存，而_exit()不会
*/

// int main()
// {
//     pid_t grand,father,son;     // 分别存放爷爷、父、子的pid
//     int i=0,x=0,choice;
//     printf("正在执行爷爷，ID：%d，下面开始展示vfork与fork的区别\n",getpid());

//     printf("请选择使用exit还是_exit，1 exit；2 _exit\n");
//     scanf("%d",&choice);

//     if(choice==1)
//     {
//         father = vfork();   // 创建子进程
//         if(father<0) printf("子进程创建失败！\n");
//         else if(father==0)
//             {
//                 printf("现在执行的是子进程，进程ID：%d\n",getpid());
//                 while(i++<5)
//                 {
//                     printf("这是子进程的第%d次循环\n",i);
//                     x+=2; 
//                 }
//                 exit(0);
//             }
//         else
//             {
//                 printf("现在执行的是父进程，进程ID：%d\n",getpid());
//                 while(i++<3)
//                 {
//                     printf("这是父进程的第%d次循环\n",i);
//                     x+=1;
//                 }
//             }
//         printf("使用exit，x=%d\n",x);
//     }
//     else if(choice==2)
//     {
//         father = vfork();   // 创建子进程
//         if(father<0) printf("子进程创建失败！\n");
//         else if(father==0)
//             {
//                 printf("现在执行的是子进程，进程ID：%d\n",getpid());
//                 while(i++<5)
//                 {
//                     printf("这是子进程的第%d次循环\n",i);
//                     x+=2; 
//                 }
//                 _exit(0);
//             }
//         else
//             {
//                 printf("现在执行的是父进程，进程ID：%d\n",getpid());
//                 while(i++<3)
//                 {
//                     printf("这是父进程的第%d次循环\n",i);
//                     x+=1;
//                 }
//             }
//         printf("使用_exit，x=%d\n",x);
//     }
//     else printf("选择错误！\n");
// }

int main()
{
    int choice;
    printf("选择使用：1 exit，2 _exit\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        printf("举例说明区别\n");
        printf("如果是exit，会看到这句话\n");
        exit(0);
    }
    else
    {
        printf("举例说明区别\n");
        printf("如果是exit，会看到这句话\n");
        _exit(0);
    }
}