#include <stdio.h>
#include <conio.h>
#include <dos.h>
int PassInput()
{
	struct date today;
	getdate(&today);  /*��ϵͳ��ǰ���ڴ���today��ָ���date�ṹ��*/
	/*����������ʱ��������������ѭ��*/
	do{
		clrscr();     /*������������*/
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
		/*���������ȷ������ʾ��ȷ��Ϣ*/
		printf(" Password Correct!\n");
		printf(" You can use the program....\n");
	}
	getchar();
}
