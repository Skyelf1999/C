#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
  1:以只读方式打开一个已有文件，从中读取20个字符并打印
  2:打开当前目录下的一个文件，写入字符串"Hello, welcome to Beijing!"
  3:访问判断，输入的文件名是否存在
  4:从键盘输入10个字符，将其写到一个文件中
*/

int main()
{
    int choice;
    printf("\n请选择功能：");
    scanf("%d",&choice);
    int fd;
    int x;

    switch(choice)
    {
        case 1:
        {
            printf("\n执行功能1：只读打开\n");
            char name[10];
            printf("请输入待打开的文件名称：\n");
            scanf("%s",&name);
            fd = open(name,O_RDONLY);
            if(fd>0)
            {
                printf("成功以只读方式打开\n");
                char buff[20];
                read(fd,buff,20);
                printf("读取结果：%s\n",buff);
            }
            else printf("打开失败\n");
            close(fd);
        }
        break;
        case 2:
        {
            printf("\n执行功能2：写入字符串\n");
            char name[10];
            printf("请输入待打开的文件名称：\n");
            scanf("%s",&name);
            fd = open(name,O_RDONLY);
            lseek(fd,0,SEEK_END);   // 移动到文件最后
            char buff[]="Hello, welcome to Beijing!";
            x = write(fd,buff,strlen(buff));
            if(x>-1) printf("写入成功\n");
            else printf("写入失败\n");
            close(fd);
        }
        break;
        case 3:
        {
            printf("\n执行功能3：访问判断\n");
            char name[10];
            printf("请输入待访问的文件名称：\n");
            scanf("%s",&name);
            x = access(name,F_OK);
            if(x==0) printf("文件存在\n");
            else printf("文件不存在\n");
        }
        break;
        case 4:
        {
            printf("\n执行功能4：输入字符并写入\n");
            char name[10];
            printf("请输入待打开的文件名称：\n");
            scanf("%s",&name);
            fd = open(name,O_RDONLY);
            char buff[50];
            printf("请输入字符串：");
            scanf("%s",&buff);
            lseek(fd,0,SEEK_END);   // 移动到文件最后
            x = write(fd,buff,strlen(buff));
            if(x>-1) printf("写入成功\n");
            else printf("写入失败\n");
            close(fd);
        }
        break;
    }
}