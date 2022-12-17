#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*
    共享内存编程练习：
        利用共享内存实现文件的打开和读写
*/

int main()
{
    int shmid;                      // 共享内存标识符
    int pid;
    char *p_addr,*c_addr;           // 共享内存映射到进程中的段地址
    char *buff,name[10];
    int fp;
    // FILE *fp;

    // 创建共享内存
    shmid = shmget(IPC_PRIVATE,1024,IPC_CREAT | 0600);
    if(shmid==-1)
    {
        printf("共享内存创建失败！\n");
        exit(0);
    }

    pid = vfork();
	if(pid==0)                      // 子进程打开文件进行读取
	{ 
		c_addr = (char*)shmat(shmid,0,0);  // 映射
        fp = open("test1",O_RDONLY);
        if(fp==0)
        {
            printf("打开失败\n");
            getchar(); return 0;
        }
        if(read(fp,buff,1024)) printf("从文件中读取内容：%s\n",buff);
        strcpy(c_addr,buff);        // 将内容写入共享内存
        close(fp);
        shmdt(c_addr);              // 解除映射
		exit(0); 
	} 
    else if(pid<0)
    {
        printf("子进程创建失败！\n");
        exit(0);
    }
	else                            // 父进程将共享内存中的内容写入文件
	{	
		p_addr = (char*)shmat(shmid,0,0); 
        printf("共享内存中现有内容：%s\n",p_addr);
        fp = open("test2",O_RDWR);
        if(fp==0)
        {
            printf("打开失败\n");
            getchar(); return 0;
        }
        lseek(fp,0,SEEK_END);       // 找到待写入文件的末尾
        strcpy(buff,p_addr);        // 将共享内存中的内容读取
        if(write(fp,buff,strlen(buff))) printf("成功写入\n");
        close(fp);
        shmdt(c_addr);              // 解除映射
        shmctl(shmid,IPC_RMID,NULL);// 删除共享内存
		exit(0); 
	} 

}