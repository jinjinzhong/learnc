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
		gettime(&curtime);   /*�õ���ǰϵͳʱ��*/
		if((float)curtime.ti_hour<=12)         /*��ǰ�Ĵ���*/
		{
			printf("AM ");
			if((float)curtime.ti_hour<10) printf("0");   /*ʮ��֮ǰ��Сʱ��ǰ����*/
			printf("%.0f:",(float)curtime.ti_hour);
		}
		else         /*���Ĵ���*/
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
		sleep(1);      /*��ʱһ���ˢ��*/
		clrscr();
	}while(1);
}