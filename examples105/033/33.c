#include <stdio.h>
#include <dos.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define WIDTH 200
#define DALAY 1000
int main(void)
{
	int gdriver=DETECT,gmode,errorcode;
	int midx,midy,i,j;
	initgraph(&gdriver,&gmode,"c:\\tc");
	
	/*�õ���ͼ����*/
	midx=getmaxx()/2;
	midy=getmaxy()/2;
	/*����Ļ����λ�û��Ʋ��������������Ļ*/
	for(i=SOLID_FILL,j=0;i<USER_FILL;i++,j++)
	{
		/*�����������*/
		setfillstyle(i,getmaxcolor()-j);
		/*������״ͼ*/
		bar(midx-WIDTH,midy-WIDTH,midx+WIDTH,midy+WIDTH);
		delay(DALAY);
	}
	getch();
	closegraph();
	return(0);
}
