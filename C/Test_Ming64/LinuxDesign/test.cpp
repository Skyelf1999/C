#include <stdio.h>
// #include <string.h>
// #define TCP_NET_SOCKET_H_
// #include <stdio.h>
// #include <sys/types.h>
// #include <string.h>
// #include <strings.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <time.h>
// #include <sys/stat.h>
// #include <fcntl.h>

extern int add(int a,int b);

int main()
{
    int a=1,b=4;
	printf("%d",add(a,b));
}

// 注册界面显示及处理
int regist()
{
    char pass1[20];
	char pass2[20];
	char temp;
	int i = 0;
	int j = 0;
	system("clear");
    printf("\n\n<---------------------- 注册界面 ---------------------->\n\n ");
	State = 0;					//禁言标志位
	send_buff.cmd = reg;
	send_buff.likes = 0;
	send_buff.vip = 0;
	// 设置账号、昵称、个性签名 ----------------------------------------
    printf("\n<--请输入账号：\n");
	scanf("%s",send_buff.account);
    printf("\n<--请输入昵称/用户名：\n");
	scanf("%s",send_buff.account);
	
	printf("\n<--请输入密码：\n");
	
	while(i < 20)
	{
		pass1[i] = mygetch();
		if(pass1[i] == 10)
		{
			if(j == 0)					////防止输入账号的最后一个回车影响 
			{	
				j++;
				continue;
			}
			break;
		}
		printf("*");
		i++;
	}
	pass1[i] = '\0';
	
	i = 0;
	printf("\n<-- 请确认您的密码：");
	while(i < 20)
	{
		pass2[i] = mygetch();
		if(pass2[i] == 10)
		{
			break;
		}
		printf("*");
		i++;
	}
	pass2[i] = '\0';
	
	
	printf("\n<--请设置您的个性签名：\n");
    scanf("%s",send_buff.moto);
	
	printf("\n<--请输入密码保护问题：\n");
	scanf("%s",send_buff.question);
	SCAN_N();
	
	printf("\n<--请输入密码保护答案：\n");
	scanf("%s",send_buff.answer);
	SCAN_N();
	
	system("clear");
	printf("\n\n\n\n\n\n\n\t\t\t正在注册......\n");
	sleep(1);
	
	if(strcmp(pass1, pass2) != 0)
	{
		printf("\n<-- 密码输入有误！请重新注册！-->\n");
		printf("\n<-- 输入ENTER键返回：-->");
		fgets(back, 20, stdin);
		return -9;
	}
	else
	{
		strcpy(send_buff.passward, pass1);
	}
}