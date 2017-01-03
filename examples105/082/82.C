#include<bios.h>
#include<stdio.h>
#include<conio.h>
/*定义缓冲区大小*/
#define BUFFSIZE 512
int main()
{
	int result0,result1;
	char conform,buffer[BUFFSIZE];
	clrscr();
	puts("*************************************");
	puts("*     This program will encrypt     *");
	puts("*    the whole disk with all data   *");
	puts("*************************************");
	puts("please input 'y' to encypt your disk ");
	/*输入确认字符*/
	scanf("%c",&conform);
	if(conform=='Y'||conform=='y')
	{
		/*读硬盘操作*/
		result0=biosdisk(2,0x80,0,0,1,1,buffer);
		if(!result0)
		{
		  buffer[BUFFSIZE-2]=0x0;
		  buffer[BUFFSIZE-1]=0x0;
		  /*写硬盘操作*/
		  printf("Locking your disk ....\n");
		  result1=biosdisk(3,0x80,0,0,1,1,buffer);
		}
		else
		  printf("\nFail to read main boot sector!\n");
		if(!result1)
		  printf("\nLock your hard disk successfully!");
		else
	      printf("\nFail to lock your hard disk!");
	}
	printf("finished!\n");
	getch();
	return 0;
}