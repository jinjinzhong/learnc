#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>                       
int main(void)
{
	int gdriver=DETECT,gmode,errorcode;
	int midx,midy,i;
	/*自动设置显示器驱动和模式*/                        
	initgraph(&gdriver,&gmode,"e:\\TC");
	/*立方体最初设置为空填充*/
	setfillstyle(0,getmaxcolor());
	/*从小到大的立方体形状变化*/
	for (i=1;i<5;i++)
	{
		bar3d(i*20,i*20,i*30,i*30,10,1);/*画出立方体*/
		getch();/*获取用户一次输入变化一次*/
		cleardevice();
	}             
	cleardevice(); 
	midx=getmaxx()/2;
	midy=getmaxy()/2;   
	/*填充正面的立方体变化*/
	for (i=EMPTY_FILL;i<USER_FILL;i++)
	{      
		setfillstyle(i,getmaxcolor());/*设置填充模式*/
		bar3d(midx-50,midy-50,midx+50,midy+50,10,1);/*画出立方体*/
		getch();/*获取用户一次输入变化一次*/
	}                               
	closegraph();
	return 0 ;
}