#include <stdio.h>
#include <stdlib.h> 


void main()
{
	unsigned long input_IP;
	unsigned int BeginByte,MidByte,ThirdByte,EndByte;
	unsigned int_rotate=0x07;
                                             
	printf("******************************************************\n");
	printf("** This program is to show how to parse a IP address**\n");
	printf("******************************************************\n");                                             
	printf("Please enter the IP address(hex) you want parse:");
	scanf("%lx",&input_IP);
	BeginByte   = (input_IP >> 24) & ~(~0 << 8);
	MidByte = (input_IP >> 16) & ~(~0 << 8);
	ThirdByte  = (input_IP >> 8 ) & ~(~0 << 8);
	EndByte   = input_IP         & ~(~0 << 8);
	printf("******************************************************\n");
	printf("The IP address after parsed is: %d.%d.%d.%d\n",BeginByte,MidByte,ThirdByte,EndByte);
	/*介绍两个循环移位函数*/     
	printf("******************************************************\n");
	printf("%u after rotated twice is =%u\n",int_rotate,_rotl(int_rotate,2));
	printf("%u after rotated once is =%u\n",int_rotate,_rotr(int_rotate,1));
	scanf("%d",int_rotate);

}