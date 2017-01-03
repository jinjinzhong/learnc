#include <stdio.h>
#include <graphics.h>
#include <conio.h>                  /*预定义三个库函数*/

int main()
{
	int x=360,y=160,gdriver=DETECT,gmode;/*选用VGA中2号调色板模式*/                 
	int top,bottom;                 /*定义变量，有的变量并赋值*/ 
	initgraph(&gdriver,&gmode,"e:\\tc");     /*初始化图形系统*/
	setbkcolor(0);
	top=y-30;
	bottom=y-30;
	/*纵轴变化的椭圆*/                      
	while((!kbhit()) && (top != 0))/*有键盘输入时或纵轴为0时退出*/
	{
		ellipse(250,250,0,360,top,bottom);    /*绘制椭圆函数*/
		top-=5;
		bottom+=5;
		sleep(1);      /*延时一秒后刷新*/
   		cleardevice();
	}
	cleardevice();
	/*横轴变化的椭圆*/
	while((!kbhit()) && (bottom != 0))/*有键盘输入时或横轴为0时退出*/
	{
		ellipse(250,250,0,360,top,bottom);    /*绘制椭圆函数*/
		top+=5;
		bottom-=5;
		sleep(1);      /*延时一秒后刷新*/
   		cleardevice();
	}
	closegraph();
	return 0;
}