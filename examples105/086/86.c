#include <stdio.h>
#include <conio.h>
#include <dos.h>
int PassInput()
{
	struct date today;
	getdate(&today);  /*把系统当前日期存入today所指向的date结构中*/
	/*当输入口令不对时，反复进行以下循环*/
	do{
		clrscr();     /*调用清屏函数*/
		puts("-------------------------------------------");
		puts("*      Welcome to use this  program!      *");
		puts("-------------------------------------------");
		printf(" Please input the password:\n");
	}
	while (atoi((char *) getpass("password:")) != today.da_mon * 100 + today.da_day);
	return 1;
}
void main(void)
{
	int i;
	i=PassInput();
	if(i==1)
	{
		/*如果输入正确，则显示正确信息*/
		printf(" Password Correct!\n");
		printf(" You can use the program....\n");
	}
	getchar();
}
