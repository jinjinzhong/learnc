#include <stdio.h>
#include <graphics.h>
#include <conio.h>                  /*Ԥ���������⺯��*/

int main()
{
	int x=360,y=160,gdriver=DETECT,gmode;/*ѡ��VGA��2�ŵ�ɫ��ģʽ*/                 
	int top,bottom;                 /*����������еı�������ֵ*/ 
	initgraph(&gdriver,&gmode,"e:\\tc");     /*��ʼ��ͼ��ϵͳ*/
	setbkcolor(0);
	top=y-30;
	bottom=y-30;
	/*����仯����Բ*/                      
	while((!kbhit()) && (top != 0))/*�м�������ʱ������Ϊ0ʱ�˳�*/
	{
		ellipse(250,250,0,360,top,bottom);    /*������Բ����*/
		top-=5;
		bottom+=5;
		sleep(1);      /*��ʱһ���ˢ��*/
   		cleardevice();
	}
	cleardevice();
	/*����仯����Բ*/
	while((!kbhit()) && (bottom != 0))/*�м�������ʱ�����Ϊ0ʱ�˳�*/
	{
		ellipse(250,250,0,360,top,bottom);    /*������Բ����*/
		top+=5;
		bottom-=5;
		sleep(1);      /*��ʱһ���ˢ��*/
   		cleardevice();
	}
	closegraph();
	return 0;
}