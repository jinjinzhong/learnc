#define N 50
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
/*�漴����N��ѧ���ĳɼ�*/
void ScorePercent(int *score,int *percent)
{
	int i,j;
	randomize();
	/*��N��ѧ���ĳɼ����������ֵ*/
 	for(i=0;i<N;i++)
 		score[i]=random(101);
 	/*ͳ��ÿ��ѧ����*/
 	for(i=0;i<N;i++)
 	{
  		if((j=(score[i]/10))==10)
  			j--;
  		percent[j]++;
 	}
}
/*�������ắ��*/
void DrawXOY()
{
	int i;
	/*��x��*/
 	line(50,400,460,400);
 	/*x��ļ�ͷ*/
 	line(460,400,455,405);
 	line(460,400,455,395);
 	/*��y��*/
 	line(50,400,50,90);
 	/*y��ļ�ͷ*/
 	line(50,90,45,95);
 	line(50,90,55,95);
 	/*y���ϵĿ̶�*/
 	for(i=370;i>=100;i-=30)
 	line(48,i,52,i);
 	/*��ע�̶�ֵ*/
 	outtextxy(35,400,"0");
 	outtextxy(30,370,"10");
 	outtextxy(30,340,"20");
 	outtextxy(30,310,"30");
 	outtextxy(30,280,"40");
 	outtextxy(30,250,"50");
 	outtextxy(30,220,"60");
 	outtextxy(30,190,"70");
 	outtextxy(30,160,"80");
 	outtextxy(30,130,"90");
 	outtextxy(23,100,"100");
	/*x���ϵĿ̶�*/
 	for(i=90;i<=450;i+=40)
 	line(i,402,i,398);
 	/*��ע�̶�ֵ*/
 	outtextxy(80,410,"10");
 	outtextxy(130,410,"20");
 	outtextxy(170,410,"30");
 	outtextxy(200,410,"40");
 	outtextxy(250,410,"50");
 	outtextxy(290,410,"60");
 	outtextxy(330,410,"70");
 	outtextxy(370,410,"80");
 	outtextxy(410,410,"90");
 	outtextxy(450,410,"100");
 	/*���������������*/
 	outtextxy(470,400,"score");
 	outtextxy(25,80,"(%)");
}
void DrawBar(int *percent)
{
	int i,j;
 	for(i=60,j=0;i<450;i+=40,j++)
 	{
 		/*���������ɫ*/
 		setfillstyle(SOLID_FILL,j+2);
 		/*����״ͼ��*/
 		bar(i,399-300*percent[j]/N,i+20,399);
 	}
}
void main()
{
	int score[N],percent[10]={0};
	int gdrive=DETECT,gmode;
  initgraph(&gdrive,&gmode,"e:\\TC");
  /*����ѧ���ɼ��Լ�����ÿ��������ѧ���ĳɼ�*/
 	ScorePercent(score,percent);
 	/*���������Լ�����*/
 	DrawXOY();
 	/*����״ͼ��*/
 	DrawBar(percent);
 	getch();
 	closegraph();
}

