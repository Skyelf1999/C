#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
    1.依次读取每行内容并显示在屏幕上
    2.从键盘输入若干字符并用fputc写入一个文件
*/

int main()
{
    int choice;
    printf("\n请选择功能：");
    scanf("%d",&choice);
    FILE *fp;
    int x,y,i;

    switch(choice)
    {
        case 1:
        {
            printf("\n执行功能1：依次读取每行内容并显示在屏幕上\n");
            char name[10];
            printf("请输入待打开的文件名称：\n");
            scanf("%s",&name);
            fp=fopen(name,"rw");
            if(fp==NULL)
            {
                printf("打开失败\n");
                getchar(); return 0;
            }
            while(1)
            {
                x = fgetc(fp);
                if(x==-1) break;
                else printf("%c",x);
            }
            fclose(fp);
        }
        break;
        case 2:
        {
            printf("\n执行功能2：从键盘输入若干字符并用fputc写入一个文件\n");
            char name[10];
            printf("请输入待打开的文件名称：\n");
            scanf("%s",&name);
            fp=fopen(name,"wt+");
            if(fp==NULL)
            {
                printf("打开失败\n");
                getchar(); return 0;
            }
            char buff[200];
            printf("请输入内容：\n");
            scanf("%s",&buff);
            x = strlen(buff);
            fseek(fp,0,SEEK_END);
            fputc('\n',fp);
            for(i=0;i<x;i++)
            {
                y = fputc(buff[i],fp);
                if(y==-1) printf("写入发生错误！\n");
            }
            fclose(fp);
        }
        break;
    }
}