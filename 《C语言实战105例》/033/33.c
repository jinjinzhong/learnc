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
	
	/*得到画图坐标*/
	midx=getmaxx()/2;
	midy=getmaxy()/2;
	/*在屏幕中心位置绘制并填充矩形来检测屏幕*/
	for(i=SOLID_FILL,j=0;i<USER_FILL;i++,j++)
	{
		/*设置填充类型*/
		setfillstyle(i,getmaxcolor()-j);
		/*绘制柱状图*/
		bar(midx-WIDTH,midy-WIDTH,midx+WIDTH,midy+WIDTH);
		delay(DALAY);
	}
	getch();
	closegraph();
	return(0);
}
