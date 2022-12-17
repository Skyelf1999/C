#include <tcp_net_socket.h>  // 用于初始化操作
int socket_fd;               // socket fd
pthread_t pid_CtoC;			 // 线程ID


///////////////////////////////////////////////////////////////////////////////////////////////////////


// 服务器基础设置：socket创建，设置服务器协议地址簇，绑定，设置侦听
int tcp_init()  
{
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);     //创建套接字
	if(socket_fd == -1)
	{
		perror("socket");
		return -1;
	}
	
	int ret;
	struct sockaddr_in serveraddr;


	memset(&serveraddr,0,sizeof(struct sockaddr));	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERV_PORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	ret = bind(socket_fd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}
	
	ret = listen(socket_fd,10);           //监听它，并设置允许最大的连接数为10个
	if(ret == -1)
	{
		perror("listen");
		close(socket_fd);
		return -1;
	}
	
	return socket_fd;
}


// 服务器接收信息
int tcp_accept(int socket_fd)
{
	struct sockaddr_in clientaddr;
	memset(&clientaddr, 0, sizeof(struct sockaddr));
	int addrlen = sizeof(struct sockaddr);
	
	//socket_fd接受客户端的连接，并创建新的socket为new_fd，将请求连接的客户端的ip、port保存在结构体clientaddr中
	int new_fd = accept(socket_fd, (struct sockaddr*)&clientaddr, &addrlen);       
	if(new_fd == -1)
	{
		perror("accept");
		close(socket_fd);
		return -1;
	}
	printf("%s %d success connet...\n", 
	inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	
	return new_fd;
}


// 用于客户端的连接(从创建socket到connect)
int tcp_connect(const char* ip)
{
	int ret;
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);     //申请新的socket
	if(socket_fd == -1)
	{
		perror("socket");
		return -1;
	}
	
	struct sockaddr_in serveraddr;
	
	memset(&serveraddr, 0,sizeof(struct sockaddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERV_PORT);
	serveraddr.sin_addr.s_addr = inet_addr(ip);    
	
	ret = connect(socket_fd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));       //将socket_fd连接至指定的服务器网络地址 serveraddr
	if(ret == -1)
	{
		perror("connect");
		close(socket_fd);
		return -1;
	}
	
	return socket_fd;
}


//用于信号处理，让服务器在按下Ctrl+c或Ctrl+\时不会退出
void signalhandler(void)
{
	sigset_t sigSet;
	sigemptyset(&sigSet);
	sigaddset(&sigSet,SIGINT);
	sigaddset(&sigSet,SIGQUIT);
	sigprocmask(SIG_BLOCK,&sigSet,NULL);
}


//用于将密码数字转换为*
int mygetch( )
{
	struct termios oldt,
	newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}


//获取当前时间 
int gettime()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "%s",asctime (timeinfo) );	
}


// 获取当前时间   指针 用于消息记录
char* nowtime()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return asctime (timeinfo);	
}


// 清除scanf后的缓存，回车
void SCAN_N()
{
	char ch;
	while((getchar()) != '\n' && ch != EOF);
}


int Get_time(void)//六位数组
{
	/* int *temp =p; */
	time_t now ;
	struct tm *t ;
	time(&now) ;
	t = localtime(&now);
	/* *(temp++) = t->tm_year+1900;
	*(temp++) = t->tm_mon+1;
	*(temp++) = t->tm_mday;
	*(temp++) = t->tm_hour;
	*(temp++) = t->tm_min;
	*temp = t->tm_sec; */
	return (t->tm_mon+1)*1000000+t->tm_mday*10000+t->tm_hour*100+t->tm_min;
}


void Welecome(void)
{
	system("clear");
	int a =Get_time();
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢                                    >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎                                  >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来                                >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到北                             >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到北科                           >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到北科聊                         >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到北科聊天                        >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到北科聊天室                      >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到北科聊天室                      >\n");
	printf("<                             嘿                >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);
	
	
	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到北科聊天室                      >\n");
	printf("<                             嘿嘿               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<         欢迎来到北科聊天室                      >\n");
	printf("<                             嘿嘿嘿             >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");


	sleep(1);
}


void Byebye(void)
{
	system("clear");
	int a =Get_time();
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<               走                              >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	int a =Get_time();
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<               走好                             >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	int a =Get_time();
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<               走好                             >\n");
	printf("<                     不                         >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");
	usleep(50000);


	system("clear");
	int a =Get_time();
	printf("<----------------------------------------------->\n");
	printf("< 2021-%02d-%02d-%02d-%02d                      >\n",a/1000000,a%1000000/10000,a%10000/100,a%100);
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<               走好                             >\n");
	printf("<                     不送                       >\n");
	printf("<                                               >\n");
	printf("<                                               >\n");
	printf("<----------- 狄仕豪 林世康 朱祥贵 许越 ----------->\n");
	printf("<------------------------------------------------->");


	sleep(1);
}


struct client_send_buff
{
	char toname[20];			    // 接收人
    int  cmd;					    // 提取操作符
	char account[20];			    // 账号
    char name[20];				    // 昵称
    char moto[300];				    // 个性签名
	char passward[20];			    // 密码
    char question[50];			    // 密保问题
	char answer[50];			    // 密保答案
	char msg[200];				    // 发送、接收消息
	char file_name[20];			    // 文件名
	char file[2048];			    // 发送文件存的数据
    int  likes;					    // 点赞数
    int  vip;					    // 是否是会员
	char e_s;					    // 确认发送的表情
	char p_s;					    // 确认发送的常用语
};


struct client_recv_buff
{
	char from_name[20];			    // 来源
	int  result;				    // 从服务器返回的结果
    char moto[300];				    // 个性签名
    char passward[20];			    // 密码
    char question[50];			    // 密保问题
	char answer[50];			    // 密保答案
	int  online_num;			    // 在线人数
	char num[20][20];			    // 在线人名
	char msg[200];				    // 发送、接收消息
	char file_name[20];			    // 文件名
	char file[2048];			    // 发送文件存的数据
	int  likes;					    // 点赞数
	int  vip;					    // 是否是会员
	char e_s;					    // 确认发送的表情
	char p_s;					    // 确认发送的常用语
};


struct client_send_buff send_buff;			// 发给服务器的消息
struct client_recv_buff recv_buff;			// 从服务器返回的消息
int ret;									// 返回结果
char back[20];			        			// 输入任意键返回
char Name[20];
int READEN = 0;                 			// 是否已经完成一次读信息
int State;
int LIKES = 0;
int OUT = 0;


// 主界面显示
void show()
{
	system("clear");
	printf("\n<-- ");
	printf("  欢迎来到聊天室!祝您聊天愉快！");
	printf("\n<-- ");
	printf("1  注册\n");
	printf("2  登录\n");
	printf("3  忘记密码\n");
	printf("4  退出\n");
	printf("<-- 请输入选择：");
}


// 注册界面显示及处理
int regist()
{
    int byte,i,j;                   // 辅助变量
    char pw1[20],pw2[20];           // 分别存储两次输入的密码，方便比对
	
    
    // 客户端数据初始化 ----------------------------------------
    system("clear");
	printf("\n\n<---------------------- 注册界面 ---------------------->\n\n ");
	State = 0;					    // 禁言标志位
    // 初始化用户信息，存储于send_buff
	send_buff.cmd = reg;                // 记录用户指令为：reg-注册
	send_buff.likes = 0;
	send_buff.vip = 0;
    //-------------------------------------------------//

    // 设置账号、昵称、个性签名 ----------------------------------------
    printf("\n<--请输入账号：\n");
	scanf("%s",send_buff.account);
    printf("\n<--请输入昵称/用户名：\n");
	scanf("%s",send_buff.account);
    printf("\n<--请设置您的个性签名：\n");
    scanf("%s",send_buff.moto);
	// strcpy(send_buff.moto, "来一场说走就走的旅行");
    SCAN_N();
    //-------------------------------------------------//

    // 设置密码 ----------------------------------------
    printf("\n<--请输入密码：\n");
	while(i < 20)
	{
		pw1[i] = mygetch();
		if(pw1[i] == 10)
		{
			if(j == 0)			
			{	
				j++;
				continue;
			}
			break;
		}
		printf("*");
		i++;
	}
	pw1[i] = '\0';
	i = 0;
	printf("\n<-- 请确认您的密码：");
	while(i < 20)
	{
		pw2[i] = mygetch();
		if(pw2[i] == 10)
		{
			break;
		}
		printf("*");
		i++;
	}
	pw2[i] = '\0';
    // 检验两次输入的密码是否相同
    if(strcmp(pw1, pw2) != 0)
	{
		printf("\n<--密码输入有误！请重新注册！-->\n输入ENTER键返回：");
		fgets(back, 20, stdin);
		return -1;
	}
	else
	{ 
		strcpy(send_buff.passward,pw1); 
		printf("\n<-- 设置密码成功 -->\n");
	}
    //-------------------------------------------------//

    // 设置密码保护 ----------------------------------------
    printf("\n<--请输入密码保护问题：\n");
	scanf("%s",send_buff.question);
	SCAN_N();
	printf("\n<--请输入密码保护答案：\n");
	scanf("%s",send_buff.answer);
	SCAN_N();
    //-------------------------------------------------//

    printf("\n<--正在注册，请稍后-->\n");
	sleep(1);
    return 1;
}


// 登录界面：获取用户名、密码
int login()
{
	char pw1[20];
	int i = 0;
	int j = 0;
	system("clear");
	printf("\n\n<---------------------- 登录界面 ---------------------->\n\n ");
    
    // 获取用户名
	printf("请输入账号：");
	scanf("%s",send_buff.account);
	
    // 获取密码
	printf("<-- 请输入密码：");
	while(i < 20)
	{
		pw1[i] = mygetch();
		if(pw1[i] == 10)
		{
			if(j == 0)						// 防止输入账号的最后一个回车影响 
			{	
				j++;
				continue;
			}
			break;
		}
		printf("<");
		i++;
	}
	pw1[i] = '\0';
	
	strcpy(send_buff.passward, pw1);
	
	system("clear");
	printf("\n<-- 正在登陆......\n");
	sleep(2);
}


// 登陆之后的主界面
int show_chat()
{
	system("clear");
	gettime();
	printf("\n%s   个性签名：%s   点赞数：%d", Name, recv_buff.moto, LIKES);
	if(recv_buff.vip == 1)
	{
		printf("尊贵的黄金会员");
	}
	else
	{
		printf("普通用户");
	}
	printf("\n<--  a 私聊\n");
	printf(" b 群聊\n");
	printf(" c 文件传输\n");
	printf(" d 查看在线人数\n");
	printf(" e 发送表情\n");
	printf(" f 常用语\n");
	printf(" g 点赞\n");
	printf(" h 更改个性签名\n");
	printf(" i 注册会员\n");
	printf(" j 禁言(需开通会员)\n");
	printf(" k 解禁(需开通会员)\n");
	printf(" l 踢人(需开通会员)\n");
	printf(" m 查看聊天记录\n");
	printf(" n 退出\n");
	printf("\n请输入您的选择：");
}


// 文件传输发送
int deal_sendfile(int socket_fd)
{
	char bs;
	int ret;
	int fd;
	ssize_t num;
	int i = 0;
	
	system("clear");
	printf("<-- ");
	
	if(State == Shutup)
	{
		printf("<-- 您处于被禁言状态！无法发言！开通会员可以解禁~(^_^)~\n");
		printf("\n<-- 输入ENTER键返回：");
		fgets(back, 20, stdin);
		return Shutup;
	}
	
	printf("\n您想给谁发文件呢？：");
	scanf("%s", send_buff.toname);
	
	strcpy(send_buff.name, Name);	
	
	printf("<-- 请告诉我本文件夹下要发送的文件名~(^_^)~：");
	scanf("%s", send_buff.file_name);
	SCAN_N();
	
	send_buff.cmd = file_transfer;
	
	if(strcmp(Name, send_buff.toname) == 0)
	{
		sleep(1);
		system("clear");
		printf("<-- 不可以给自己发送文件哦~(^_^)~");
		printf("\n<-- 输入ENTER键返回：");
		fgets(back, 20, stdin);
		return -1;
	}
	
	fd = open(send_buff.file_name, O_RDONLY, S_IRUSR | S_IWUSR);
	if(fd < 0)
	{
		printf("\n<-- 没有此文件！\n");
		printf("\n<-- 输入ENTER键返回：");
		fgets(back, 20, stdin);
		return -1;
	}
	
	while(1)
	{
		memset(&bs, 0, sizeof(bs));
		ssize_t read_bytes = read(fd, &bs, sizeof(bs));
		if(read_bytes == -1)
		{
			perror("read");
			return -1;
		}
		if(read_bytes == 0)
		{
			break;
		}
		send_buff.file[i] = bs;
		i++;
	}
	send_buff.file[i] = '\0';
	
	ret = write(socket_fd, &send_buff,sizeof(send_buff));
	if(ret == -1)
	{
		perror("write");
		return -1;
	}
	
	printf("<-- 正在发送...\n");
	sleep(2);
}


// 收文件
int back_file()
{
	system("clear");
	printf("<-- %s用户发送了一份文件给您，请确认接收！\n", recv_buff.from_name);
	sleep(2);
	
	int fd;
	fd = open(recv_buff.file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}
	
	ret = write(fd, recv_buff.file, strlen(recv_buff.file));
	if(ret == -1)
	{
		perror("write");
		return -1;
	}
	
	printf("<-- 恭喜您接收文件成功！~(^_^)~");
	printf("<-- 输入ENTER键返回~(^_^)~\n");
}


// 发送表情选择
int deal_send_expr(int socket_fd)
{
	char e[10];    	// 输入表情选项
	
	system("clear");
	printf("<-- ");
	if(State == Shutup)
	{
		printf("<-- 您处于被禁言状态！无法发言！开通会员可以解禁~(^_^)~\n");
		printf("\n<-- 输入ENTER键返回：");
		fgets(back, 20, stdin);
		return Shutup;
	}
	
	printf("\n您想发表情给谁呢？：");
	scanf("%s", send_buff.toname);
	strcpy(send_buff.name, Name);
	send_buff.cmd = expression;
	
	printf("\n<-- 1 开心       :-D\n");
	printf("2 生气       ＝　＝＃\n");
	printf("3 为你加油   *\(^_^)/>\n");
	printf("4 两手一摊   ╮(￣▽ ￣)╭\n");
	printf("5 飞吻       づ￣ 3￣)づ\n");
	printf("6 哭泣       (T_T)\n");
	printf("7 竖起大拇指 b（￣▽￣）d\n");
	printf("8 不满       (︶︿︶)\n");
	printf("9 亲亲       >3<<-- ");
	printf("请输入您想发送的表情：");
	scanf("%s", e);
	SCAN_N();
	
	send_buff.e_s = e[0];
	
	if(strcmp(Name, send_buff.toname) == 0)
	{
		sleep(1);
		system("clear");
		printf("<-- 不可以给自己发送表情哦~(^_^)~");
		printf("\n<-- 输入ENTER键返回：");
		fgets(back, 20, stdin);
		return -1;
	}
	
	ret = write(socket_fd, &send_buff, sizeof(send_buff));
	if(ret == -1)
	{
		perror("write");
		return -1;
	}
	system("clear");
	printf("<-- 正在发送...\n");
	sleep(2);
}


// 根据接收到的表情序号，显示表情
int back_ep()
{
	char er[20];                // 用于暂存要显示的表情
	switch (recv_buff.e_s)
	{
		case '1' :
		{
			strcpy(er, ":-D");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '2' :
		{
			strcpy(er, "＝　＝＃");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '3' :
		{
			strcpy(er, "*\(^_^)/*");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '4' :
		{
			strcpy(er, "╮(￣▽ ￣)╭");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '5' :
		{
			strcpy(er, "づ￣ 3￣)づ");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '6' :
		{
			strcpy(er, "(T_T)");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '7' :
		{
			strcpy(er, "b（￣▽￣）d");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '8' :
		{
			strcpy(er, "(︶︿︶)");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '9' :
		{
			strcpy(er, ">3<");
			system("clear");
			printf("<-- %s用户发送了一个表情给您！", recv_buff.from_name);
			printf("<-- %s\n",er);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		default :
		{
			system("clear");
			printf("<-- 抱歉！输入错误！/n");
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
	}
}


//发送常用语选择
int deal_phrases(int socket_fd)
{
	char p[10];    				//输入常用语选项
	
	system("clear");
	printf("<-- ");
	if(State == Shutup)
	{
		printf("<-- 您处于被禁言状态！无法发言！开通会员可以解禁~(^_^)~\n");
		printf("\n<-- 输入ENTER键返回：");
		fgets(back, 20, stdin);
		return Shutup;
	}
	
	printf("\n您想给谁发信息呢？：");
	scanf("%s", send_buff.toname);
	strcpy(send_buff.name, Name);			
	send_buff.cmd = phrases;					
	
	printf("\n1 はじめまして            (  初次见面 )\n");
	printf("2 どうぞよろしく          (  请多关照 )\n");
	printf("3 そうですか              (  是吗？   )\n");
	printf("4 はい                    (  是的     )\n");
	printf("5 よくいらっしゃいました  (欢迎，欢迎 )\n");
	printf("6 どういたしまして        (  不用客气 )\n");
	printf("7 おはよございます        (   早上好  )\n");
	printf("8 こんにちは              (  你好！   )\n");
	printf("9 こんばんは              (   晚上好！)\n");
	printf("\n请输入您想发送的常用语：");
	scanf("%s", p);
	SCAN_N();
	
	send_buff.p_s = p[0];
	
	if(strcmp(Name, send_buff.toname) == 0)
	{
		sleep(1);
		system("clear");
		printf("<-- 不可以给自己发送常用语哦~(^_^)~");
		printf("\n<-- 输入ENTER键返回：");
		fgets(back, 20, stdin);
		return -1;
	}
	
	ret = write(socket_fd, &send_buff, sizeof(send_buff));
	if(ret == -1)
	{
		perror("write");
		return -1;
	}
	system("clear");
	printf("<-- 正在发送...\n");
	sleep(2);
}


// 根据接收到的常用语序号，显示常用语
int back_ph()
{
	char ph[60];
	switch (recv_buff.p_s)
	{
		case '1' :
		{	
			strcpy(ph, "はじめまして  ( 初次见面 )");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '2' :
		{
			strcpy(ph, "どうぞよろしく  ( 请多关照 )");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("\n<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '3' :
		{
			strcpy(ph, "そうですか    ( 是吗？)");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("\n<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '4' :
		{
			strcpy(ph, "はい    ( 是的 )");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("\n<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '5' :
		{
			strcpy(ph, "よくいらっしゃいました  ( 欢迎，欢迎 )");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("\n<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '6' :
		{
			strcpy(ph, "どういたしまして	( 不用客气 )");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("\n<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '7' :
		{
			strcpy(ph, "おはよございます   ( 早上好 )");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("\n<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '8' :
		{
			strcpy(ph, "こんにちは	( 你好！)");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("\n<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		case '9' :
		{
			strcpy(ph, "こんばんは	( 晚上好！)");
			system("clear");
			printf("<-- %s用户发送了一句话给您！", recv_buff.from_name);
			printf("\n<-- %s\n",ph);
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
		default :
		{
			system("clear");
			printf("<-- 抱歉！输入错误！/n");
			printf("<-- 输入ENTER键返回~(^_^)~\n");
			break;
		}
	}
}


// 端-端通信处理的线程函数
void *c_to_c(void* arg)
{
    int i;
    
    // 读取循环，每次都要根据消息类型来进行相应处理，并且重置缓存
	while(1)
	{    
		if(read(socket_fd,&recv_buff,sizeof(recv_buff))==-1)
		{
			perror("read");
            printf("\n<-- 此次读取失败 -->");
            sleep(1);
			continue;
		}
		READEN = 1;                 // 设置读取状态为“已读”

        // 根据result判断消息类型，处理后重置接收消息结构体userBack
		switch (recv_buff.result)
		{
            // 私聊 ----------------------------------------
			case (private_chat):
			{
				//system("clear");
				printf("\n<-- %s 对您说了一句悄悄话：%s -->",recv_buff.from_name, recv_buff.msg);
				//printf("\n<--输入ENTER键返回-->\n");
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//

            // 群聊 ----------------------------------------
			case (group_chat):
			{
				//system("clear");
				printf("\n<-- %s用户发送了一条信息：%s -->\n", recv_buff.from_name, recv_buff.msg);
				//printf("<-- 输入ENTER键返回~(^_^)~\n");
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//

            // 当前在线人数 ----------------------------------------
			case (online_member):
			{
				//system("clear");
				printf("\n<-- 当前在线人数：%d -->\n",recv_buff.online_num);
                printf("\n<-- 在线列表 -->\n");
				for(i = 0; i < recv_buff.online_num; i++)
				{
					printf("\n%s\n",recv_buff.num[i]);
				}
				//printf("<-- 输入ENTER键返回~(^_^)~\n");
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//

            // 文件传输 ----------------------------------------
			case (file_transfer):
			{
				back_file();
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//

            // 表情 ----------------------------------------
			case (expression):
			{
				back_ep();
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//

            // 常用语 ----------------------------------------
			case (phrases):
			{
				back_ph();
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//

            // 点赞 ----------------------------------------
			case (like):
			{
				LIKES = recv_buff.likes;
				//system("clear");
				printf("\n<-- 伟大的（滑稽）%s给你点了一个赞！ -->\n", recv_buff.from_name);
				//printf("<-- 输入ENTER键返回~(^_^)~\n");
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//

            // 被禁言 ----------------------------------------
			case (Shutup):
			{
				State = Shutup;         // 将状态设置为“被禁言”
				//system("clear");
				printf("\n<-- 啊这，%s用户把您禁言了！建议付款开通会员对他重拳出击！ -->\n", recv_buff.from_name);
				//printf("<-- 输入ENTER键返回~(^_^)~\n");
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//

            // 被踢除 ----------------------------------------
			case (kick):
			{
				OUT = 1;                // 设置为“已被踢除”，后面根据OUT的值强制下线
				//system("clear");
				printf("\n<-- 很抱歉，您已被%s用户强制下线！建议付款开通会员对他重拳出击！ -->\n",recv_buff.from_name);
				//printf("<-- 输入ENTER键返回~(^_^)~\n");
				memset(&recv_buff.result, 0, sizeof(recv_buff.result));
				//break;
			}
            //-------------------------------------------------//
		}
        READEN = 0;
        /* 
            如果recv_buff.result不是以上switch中的值（是服务器反馈信息），将会在主线程中进行处理
            而该线程继续下一次读取
        */
	}
}


// 处理服务器反馈结果的函数
int deal()
{
    char choice[12];		    	// 输入的功能选择
	char x[2];                      // 用于支付确认  
	char talk_file[40];				// 聊天文本名字
	char talk_record[2048];			// 聊天记录
	
    // 执行完相应反馈之后退出循环，返回主函数中
	while(1)
	{
        // 如果客户端从服务器已经读到了一条消息
		if(READEN == 1)                 
		{
			READEN = 0;                 // 重置READEN
            // 根据result判断消息类型处理反馈
			switch(recv_buff.result)
			{
                // 发送消息成功 ----------------------------------------
				case (Send_success):
				{
					system("clear");
					printf("\n<-- \n发送成功！\n");
					memset(&recv_buff.result, 0, sizeof(recv_buff.result));
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					//break;
				}
                //-------------------------------------------------//

                // 点赞成功 ----------------------------------------
				case (like_success):
				{
					system("clear");
					printf("\n\n<-- 恭喜您点赞成功！~(^_^)~\n");
					memset(&recv_buff.result, 0, sizeof(recv_buff.result));
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					//break;
				}
                //-------------------------------------------------//
                
                // 更改个性签名成功 ----------------------------------------
				case (change_success):
				{
					system("clear");
					printf("<-- 恭喜您更改个性签名成功！~(^_^)~\n");
					memset(&recv_buff.result, 0, sizeof(recv_buff.result));
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					//break;
				} 
                //-------------------------------------------------//

                // 开通VIP成功 ----------------------------------------
				case (vip_success):
				{
					system("clear");
					printf("<-- 恭喜您成为尊贵的黄金会员！~(^_^)~\n");
					memset(&recv_buff.result, 0, sizeof(recv_buff.result));
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					//break;
				}
                //-------------------------------------------------//

				// 禁言别人成功 ----------------------------------------
                case (Shutup_success):
				{
					system("clear");
					printf("<-- 恭喜您，对方已成功被您禁言！~(^_^)~\n");
					memset(&recv_buff.result, 0, sizeof(recv_buff.result));
					printf("\n<-- 输入ENTER键离开：");
					fgets(back, 20, stdin);
					//break;
				}
                //-------------------------------------------------//

				// 踢人成功 ----------------------------------------
                case (kick_success):
				{
					system("clear");
					printf("<-- 恭喜您对方已成功被您踢下线！~(^_^)~\n");
					memset(&recv_buff.result, 0, sizeof(recv_buff.result));
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					//break;
				}
                //-------------------------------------------------//

				// 发送信息失败 ----------------------------------------
                case (Send_error):
				{
					system("clear");
					printf("<-- 对不起，对方暂时没有登录！\n");
					memset(&recv_buff.result, 0, sizeof(recv_buff.result));
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					//break;
				}
                //-------------------------------------------------//
			}
            READEN = 0;
            continue;
		}

        // 如果客户端还未从服务器读到消息，先显示发送信息主界面	
		show_chat();
		fgets(choice, 12, stdin);
		// 如果被踢了，返回Exit
		if(OUT == 1)
		{
			OUT--;
			return Exit; 
		}
		
        // 如果没被踢，根据选择的功能执行程序
        /*
            a：私聊，b:群聊，c：文件传输，d：在线列表，e：发表情，f：常用语，g：点赞，
            h：改签名，i：管理员认证，j：禁言，k：解除禁言，l：踢人，m：查看记录，n：退出
        */
		switch(choice[0])
		{
            // 私聊 ----------------------------------------
			case 'a':					
			{
				int chat_record;
				system("clear");
				printf("\n<-- 私聊界面 -->");
				if(State == Shutup)
				{
					printf("\n<-- 您处于被禁言状态！无法发言！开通会员可以解禁 -->\n");
					printf("\n<-- 输入ENTER键返回： -->");
					fgets(back, 20, stdin);
					//break;
				}
				memset(talk_record,0,strlen(talk_record));
				memset(talk_file,0,strlen(talk_file));
				printf("您想和谁聊天呢？请输入对方名字：");
				scanf("%s", send_buff.toname);
				SCAN_N();


				printf("<-- 请输入您想要说的话：");
				scanf("%[^\n]", send_buff.msg);
				SCAN_N();
				
				send_buff.cmd = private_chat;
				
				strcpy(send_buff.name,Name);
				
				if(strcmp(Name, send_buff.toname) == 0)
				{
					sleep(1);
					system("clear");
					printf("\n<-- \n不可以给自己发信息哦~(^_^)~");
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					//break;
				}
				
				ret = write(socket_fd, &send_buff,sizeof(&send_buff));
				if(ret == -1)
				{
					perror("write");
					//return -1;
				}
				
				sprintf(talk_file, "%s与%s的聊天记录.txt", Name, send_buff.toname);
				chat_record = open(talk_file, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
				if(chat_record == -1)
				{
					perror("open");
					//return -1;
				}
				
				sprintf(talk_record, "%s 对 %s 发送了一句悄悄话：%s%s", Name, send_buff.toname, send_buff.msg,nowtime());
				ret = write(chat_record, talk_record, strlen(talk_record));
				if(ret == -1)
				{
					perror("write");
					//return -1;
				}
				printf("<-- 正在发送...\n");
				sleep(2);
				
				//break;
			}
            //-------------------------------------------------//

			// 群聊 ----------------------------------------
            case 'b':				
			{
				system("clear");
				printf("<-- ");
				int i = 0;
				
				if(State == Shutup)
				{
					printf("<-- 您处于被禁言状态！无法发言！开通会员可以解禁~(^_^)~\n");
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					//break;
				}
				
				printf("\n<-- 请输入您想要说的话：");
				scanf("%[^\n]", send_buff.msg);
				SCAN_N();
				
				send_buff.cmd = group_chat;
				
				strcpy(send_buff.name,Name);
				
				ret = write(socket_fd, &send_buff,sizeof(&send_buff));
				if(ret == -1)
				{
					perror("write");
					//return -1;
				}
				system("clear");
				printf("\n<-- 正在发送...\n");
				sleep(2);
				//break;
			}
            //-------------------------------------------------//

            // 文件传输 ----------------------------------------
			case 'c':				
			{
				deal_sendfile(socket_fd);
				//break;
			}
            //-------------------------------------------------//

            // 在线列表 ----------------------------------------
			case 'd':					
			{
				send_buff.cmd = online_member;
				
				ret = write(socket_fd, &send_buff,sizeof(send_buff));
				if(ret == -1)
				{
					perror("write");
					return -1;
				}
				
				system("clear");
				printf("\n<-- \n...\n");
				//break;
			}
            //-------------------------------------------------//

            // 发送表情 ----------------------------------------
			case 'e':				
			{
				deal_send_expr(socket_fd);
				//break;
			}
            //-------------------------------------------------//

            // 发送常用语 ----------------------------------------
			case 'f':					
			{
				deal_phrases(socket_fd);
				//break;
			}
            //-------------------------------------------------//

			// 点赞 ----------------------------------------
            case 'g':				
			{
				send_buff.cmd = like;
				system("clear");
				printf("\n<-- \n您比较欣赏谁呢？~(^_^)~请告诉我：");
				scanf("%s", send_buff.toname);
				SCAN_N();
				strcpy(send_buff.name, Name);
				
				if(strcmp(Name, send_buff.toname) == 0)
				{
					sleep(1);
					system("clear");
					printf("\n<-- \n不可以给自己点赞哦~(^_^)~");
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					break;
				}
				
				ret = write(socket_fd, &send_buff,sizeof(send_buff));
				if(ret == -1)
				{
					perror("write");
					return -1;
				}
				printf("<-- 请稍等...\n");
				sleep(2);
				//break;
			}
            //-------------------------------------------------//

			// 更改个性签名 ----------------------------------------
            case 'h':					
			{
				send_buff.cmd = motto_change;
				system("clear");
				printf("\n<-- \n您想要一个什么样的个性签名呢？\n<-- ");
				scanf("%s", send_buff.moto);
				SCAN_N();
				
				strcpy(send_buff.name, Name);
				
				ret = write(socket_fd, &send_buff, sizeof(send_buff));
				if(ret == -1)
				{
					perror("write");
					return -1;
				}
				printf("<-- 请稍等...\n");
				sleep(2);
				//break;
			}
            //-------------------------------------------------//

            // 注册会员 ----------------------------------------
			case 'i':					
			{
				if(recv_buff.vip == 1)
				{
					system("clear");
					printf("\n<-- \n您已经是尊贵的黄金会员了！~(^_^)~\n");
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
				}
				else if(recv_buff.vip == 0)
				{
					system("clear");
					printf("\n<-- 您好，请先支付200元，然后就能永久享受vip权限了！~(^_^)~\n");
					printf("\n<-- 确认支付吗？（y/n）");
					scanf("%s",x);
					SCAN_N();
					
					if(x[0] == 'y')
					{
						strcpy(send_buff.name,Name);
						send_buff.vip = 1;
						send_buff.cmd = Vip;
						
						ret = write(socket_fd, &send_buff, sizeof(send_buff));
						if(ret == -1)
						{
							perror("write");
							return -1;
						}
						printf("<-- 请稍等...\n");
						sleep(2);
					}
				}
				//break;
			}
            //-------------------------------------------------//

			// 禁言 ----------------------------------------
            case 'j':					
			{
				if(recv_buff.vip == 0)
				{
					system("clear");
					printf("\n<-- \n您还没有开通会员，请先开通会员！~(^_^)~\n");
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
				}
				else if(recv_buff.vip == 1)
				{
					system("clear");
					printf("\n<-- \n您想让谁闭嘴呢？~(^_^)~请告诉我：");
					scanf("%s", send_buff.toname);
					SCAN_N();
					send_buff.cmd = Shutup;
					strcpy(send_buff.name,Name);
					
					if(strcmp(Name, send_buff.toname) == 0)
					{
						sleep(1);
						system("clear");
						printf("\n<-- \n不可以给自己禁言哦~(^_^)~");
						printf("\n<-- 输入ENTER键返回：");
						fgets(back, 20, stdin);
						break;
					}
					
					ret = write(socket_fd, &send_buff, sizeof(send_buff));
					if(ret == -1)
					{
						perror("write");
						//return;
					}
					printf("<-- 请稍等...\n");
					sleep(2);
				}
				//break;
			}
            //-------------------------------------------------//

            // 解除禁言 ----------------------------------------
			case 'k':					
			{
				if(State == 0)
				{
					system("clear");
					printf("\n<-- \n您没有被禁言！尽情聊天吧~(^_^)~\n");
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
				}
				else if(State == Shutup)
				{
					if(recv_buff.vip == 0)
					{
						system("clear");
						printf("\n<-- \n您还没有开通会员，请先开通会员！~(^_^)~\n");
						printf("\n<-- 输入ENTER键返回：");
						fgets(back, 20, stdin);
					}
					else if(recv_buff.vip == 1)
					{
						system("clear");
						printf("\n<-- \n您想现在解禁吗！(y/n)：");
						scanf("%s",x);
						SCAN_N();
						
						if(x[0] == 'y')
						{
							State = 0;
							system("clear");
							printf("\n<-- \n恭喜您成功解禁！尽情去嗨皮啊！~(^_^)~\n");
							printf("\n<-- 输入ENTER键返回：");
							fgets(back, 20, stdin);
						}
					}
				}
				//break;
			}
            //-------------------------------------------------//

            // 踢人 ----------------------------------------
			case 'l':					
			{
				if(recv_buff.vip == 0)
				{
					system("clear");
					printf("\n<-- \n您还没有开通会员，请先开通会员！~(^_^)~\n");
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
				}
				else
				{
					system("clear");
					printf("\n<-- \n您看谁不顺眼呢？~(^_^)~请告诉我：");
					scanf("%s", send_buff.toname);
					SCAN_N();
					
					strcpy(send_buff.name, Name);
					send_buff.cmd = kick;                      //vip踢人信号
					
					if(strcmp(Name, send_buff.toname) == 0)
					{
						sleep(1);
						system("clear");
						printf("\n<-- \n不可以踢自己哦~(^_^)~");
						printf("\n<-- 输入ENTER键返回：");
						fgets(back, 20, stdin);
						//break;
					}
					
					ret = write(socket_fd, &send_buff, sizeof(send_buff));
					if(ret == -1)
					{
						perror("write");
						return;
					}
					printf("<-- 请稍等...\n");
					sleep(2);
				}
				//break;
			}
            //-------------------------------------------------//

			// 产看聊天记录 ----------------------------------------
            case 'm':					
			{
				system("clear");
				char n[20];
				char chat_record_file[60];
				char records[2048];
				char kl;
				int fd2;
				int i = 0;
				printf("\n<-- \n您想看和谁的聊天记录呢？");
				scanf("%s",n);
				SCAN_N();
				sprintf(chat_record_file, "%s与%s的聊天记录.txt", Name, n);
				fd2 = open(chat_record_file,O_RDONLY,S_IRUSR | S_IWUSR);
				if(fd2 == -1)
				{
					system("clear");
					printf("\n<-- 您与%s还没有聊天记录！快去聊天吧~(^_^)~\n",n);
					printf("\n<-- 输入ENTER键返回：");
					fgets(back, 20, stdin);
					break;
				}
				
				while(1)
				{
					memset(&kl, 0, sizeof(kl));
					ssize_t read_bytes = read(fd2, &kl, sizeof(kl));
					if(read_bytes == -1)
					{
						perror("read");
						return -1;
					}
					if(read_bytes == 0)
					{
						break;
					}
					records[i] = kl; 
					i++;
				}
				records[i] = '\0';
				
				printf("\n%s\n", records);
				
				printf("\n<-- 输入ENTER键返回：");
				fgets(back, 20, stdin);
				//break;
			}
            //-------------------------------------------------//

			// 退出 ----------------------------------------
            case 'n':				
			{
				send_buff.cmd = exit;
				strcpy(send_buff.name, Name);
				
				ret = write(socket_fd, &send_buff, sizeof(&send_buff));
				if(ret == -1)
				{
					perror("write");
					//return -1;
				}
				return Exit;
			}
            //-------------------------------------------------//

			case 10:					//ENTER键返回刷新界面
			{
				//break;
			}
            //-------------------------------------------------//

            // 如果不是已有功能，报错
			default:
			{
				system("clear");
				printf("<-- ");
				printf("<-- 请输入a--n之间的选择！\n");
				printf("\n<-- 输入ENTER键返回：");
				fgets(back, 20, stdin);
				//break;
			}
		}
	}
    // 循环结束，返回主函数
}


// 忘记密码
void find_password()
{
	char answer_buff[100];
	int choice;
	send_buff.cmd = forget;
	system("clear");
	printf("<---------------------- 找回密码 ----------------------><-- ");
	
	printf("\n<-- 请输入您的账号： -->");
	scanf("%s", send_buff.account);			
	ret = write(socket_fd, &send_buff, sizeof(&send_buff));
	if(ret == -1)
	{
		perror("write");
		return;
	}				
	ret = read(socket_fd, &recv_buff, sizeof(&recv_buff));
	if(ret == -1)
	{
		perror("read");
		return;
	}

	// 输入密保答案循环
	while(1)
	{		
		printf("\n<-- 问题：%s",recv_buff.question);
		printf("\n<--请输入答案:");
		scanf("%s",answer_buff);
		SCAN_N();
				
		if(strcmp(answer_buff, recv_buff.answer) == 0)
		{
			printf("\n<-- 您的密码是：%s 请妥善保管您的密码 -->\n",recv_buff.passward);			
			printf("\n<-- 输入ENTER键返回主界面： -->");
			fgets(back, 20, stdin);
			return;
		}
		else
		{
			system("clear");
			printf("\n<-- 抱歉，您的答案不对！ -->\n");
			printf("\n<-- 是否需要重新输入密保答案：1.是，2.否 -->\n");
			scanf("%s",&choice);
			if(choice==1) continue;
			printf("\n<-- 输入ENTER键返回 -->");
			fgets(back, 20, stdin);
			return;
		}
	}
}


int communicate()
{
	// 创建接收消息线程，接收来自其他客户端的消息
	pthread_create(&pid_CtoC, NULL, c_to_c, (void*)socket_fd);
	pthread_detach(pid_CtoC);     // 主线程与子线程分离，子线程结束后，资源自动回收
	// 处理服务器对客户端操作结果的反馈
	ret = deal();
    // 若返回了Exit，退出循环，终止客户端
	if(deal() == Exit) return Exit;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Usage: ./cilent IP\n");
		return -1;
	}
	
	char choice[2];                    	    // 选择功能
	socket_fd = tcp_connect(argv[1]);		// 从创建socket到connect
	

	Welecome();								// 显示欢迎界面
	

    // 主界面循环
	while(1)
	{
		show();                     		// 显示主界面
		scanf("%s", choice);           		// 选择功能：注册，登录，忘记密码，退出
		
		switch (choice[0])
		{
            // 注册 ----------------------------------------
			case '1':				
			{
				if(regist()<0)    		// 两次设置的密码不一样
				{ break; }
				else
				{
                    // 向服务器发送此次注册的用户信息
					write(socket_fd,&send_buff,sizeof(send_buff));
					memset(&send_buff,0,sizeof(send_buff));
					// 接收服务器注册结果
					memset(&recv_buff,0,sizeof(recv_buff));
					read(socket_fd, &recv_buff, sizeof(recv_buff));
					if(recv_buff.result == reg_success)
					{
						printf("\n<-- 恭喜您注册成功！\n");
						printf("\n<-- 输入ENTER键返回：");
						fgets(back, 20, stdin);
					}
					else if(recv_buff.result == existing_acc)
					{
						printf("\n<-- 该账户已被注册！请重新注册！\n");
						printf("\n<-- 输入ENTER键返回：");
						fgets(back, 20, stdin);
					}
					break;          
				}
			}
            //-------------------------------------------------//

            // 登录 ----------------------------------------
			case '2':				
			{
                // 设置用户指令为：log-登录
				send_buff.cmd = log;
				login();
                // 将输入的用户名、密码发送至服务器进行比对
				write(socket_fd, &send_buff, sizeof(struct client_send_buff));
				read(socket_fd, &recv_buff,sizeof(recv_buff));
				
                // 若登陆成功
				if(recv_buff.result == log_success)
				{
					strcpy(Name, recv_buff.from_name);
					LIKES = recv_buff.likes;
					printf("\n<-- 恭喜您登陆成功！\n");
					sleep(2);
                    // 若返回了Exit，退出循环，终止客户端
					if(communicate() == Exit) break;
				}
                // 若登陆失败：账号密码错误/已被登录
				else if(recv_buff.result == error)
				{
					printf("\n<-- 账号密码错误！请重新登陆\n");
					printf("\n\n<-- 请问是否需要找回密码：y/n\n");
					scanf("%s", choice); 
					if(choice[0] == 'y')
					{
						sleep(1);
						SCAN_N;
						find_password();
					}
					sleep(2);
				}
				else if(recv_buff.result == logged_acc)
				{
					printf("\n<-- 此账号已被登录！\n");
					sleep(2);
				}
				break;
			}
            //-------------------------------------------------//

            // 忘记密码 ----------------------------------------
			case '3':			
			{
				find_password();
			}
            //-------------------------------------------------//

            // 退出 ----------------------------------------
			case '4':			
			{
				Byebye();
				system("clear");
				return 0;
			}
			default :
			{
				system("clear");
				printf("<-- ");
				printf("<-- 请输入1--3之间的选择！\n");
				sleep(2);
				break;
			}
            //-------------------------------------------------//
		}
	}
	return 0;
}