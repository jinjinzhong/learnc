#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
/*ȷ�������X����*/
int ObjX[12]={0,60,60,0,0,60,60,0,60,0,60,0}; 
/*ȷ�������Y����*/
int ObjY[12]={0,0,120,120,0,0,40,40,80,80,120,120};
/*ȷ�������Z����*/
int ObjZ[12]={0,0,0,0,80,80,80,80,40,40,40,40};
/*ȷ�����Ӹ����˳��*/
int LinkOrder[24]={0,1,2,3,0,4,5,6,7,4,10,11,9,8,10,2,3,11,8,6,9,7,1,5};
int Tag[24]={0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1};
int vh=100,vw=120,x0=240,y0=200;
/*���Ӷ�����ͼ*/
void LookDown(void)
{
	int x,y,i,j;
	for(i=0;i<24;i++)
	{
		j=LinkOrder[i];
		x=x0-ObjX[j];
		y=y0+ObjY[j]+vh;
		if(Tag[i]==0)
			moveto(x,y);
		lineto(x,y);
	}
}
/*����۲�������ͼ*/
void LookSide(void)
{
	int x,y,i,j;
	for(i=0;i<24;i++)
	{
		j=LinkOrder[i];
		x=x0+ObjY[j]+vw;
		y=y0-ObjZ[j];
		if(Tag[i]==0)
		moveto(x,y);
		lineto(x,y);
  }
}
/*�����������ͼ--���ͼ*/
void LookAll(void)
{
	int x,y,i,j;
	for(i=0;i<24;i++)
	{
		j=LinkOrder[i];
		x=x0-0.7071*ObjX[j]+0.7071*ObjY[j]+150;
		y=y0+0.4082*ObjX[j]+0.4082*ObjY[j]-0.8165*ObjZ[j]+150;
	 	if(Tag[i]==0)
			moveto(x,y);
		lineto(x,y);
	}
}
int main()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"e:\\tc");
	setbkcolor(BLACK);
	setcolor(WHITE);
	/*���Ӷ���*/
	LookDown();
	/*���Ӷ���*/
	LookSide();
	/*�����������ͼ*/
	LookAll();
	getch();
	closegraph();
	return 0;
}
