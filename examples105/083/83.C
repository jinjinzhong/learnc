#include <stdio.h> 
#include <dos.h> 
#include <conio.h> 
int main() 
{
	int i; 
	char password; 
	char byte=0;
	printf("**********************************************\n");
	printf("**This program is to get the bios password. **\n");
	printf("**                                          **\n");
	printf("**********************************************\n");
	printf("The award bios password in your computer is:\n"); 
	/*先读取高位字节*/
	outportb(0x70,0x1d);/*打开0x70端口，获取0x1d字节数据*/ 
	password=inportb(0x71);/*从0x71端口读出数据*/ 
	for(i=6;i>=0;i-=2) 
	{
		byte=password; 
		byte>>=i;/*右移位操作*/
		byte=byte&0x03;/*用四进制表示*/
		printf("%d",byte); 
	}
	/*读取地位字节*/
	outportb(0x70,0x1c);
	password=inportb(0x71);
	for(i=6;i>=0;i-=2)
	{
		byte=password;
		byte>>=i;/*右移位操作*/
		byte=byte&0x03;/*用四进制表示*/
		printf("%d",byte);
	}          
	scanf("%d",i);
	return 0;
} 
