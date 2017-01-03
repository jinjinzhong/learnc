#include <stdio.h>  
#include <math.h>
#include <dos.h>
#include <conio.h>      
void main()
{
 	struct time curtime;
	float th_hour,th_min,th_sec;	
	do
	{
		printf("*********************************************\n");
		printf("** This is a simple clock program.         **\n");
		printf("**                                         **\n");
		printf("*********************************************\n");
		printf("The current time is:\n");
		gettime(&curtime);   /*得到当前系统时间*/
		if((float)curtime.ti_hour<=12)         /*午前的处理*/
		{
			printf("AM ");
			if((float)curtime.ti_hour<10) printf("0");   /*十点之前在小时数前加零*/
			printf("%.0f:",(float)curtime.ti_hour);
		}
		else         /*午后的处理*/
		{
			printf("PM ");
			if((float)curtime.ti_hour-12<10) printf("0");
			printf("%.0f:",(float)curtime.ti_hour-12);
		}
		if((float)curtime.ti_min<10) printf("0");
		printf("%.0f:",(float)curtime.ti_min);
		if((float)curtime.ti_sec<10) printf("0");
		printf("%.0f",(float)curtime.ti_sec);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		sleep(1);      /*延时一秒后刷新*/
		clrscr();
	}while(1);
}
