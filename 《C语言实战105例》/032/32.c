#include<conio.h>
#include<alloc.h>
#include<stdio.h>
#include<stdlib.h>

#define WIDTH 25 /*窗口宽度*/
#define HEIGHT 15 /*窗口宽度*/
#define START_X 10
#define START_Y 5  /* 窗口左上角坐标(START_X,START_Y) */
int main()
{
	int i;
	/*绘制窗口*/
	window(START_X,START_Y,START_X+WIDTH,START_Y+HEIGHT);
	textattr(128+BLACK+(WHITE<<4)); 
	clrscr();
	/*绘制横边框*/
	for(i = 2;i<=24;i++)
	{
		gotoxy(i,1);
		putch('=');
		gotoxy(i,15);
		putch('=');
	}
	/*绘制竖边框*/
	for(i = 2;i<=14;i++)
	{
		gotoxy(2,i);
		putch('|');
		gotoxy(24,i);
		putch('|');
	}
	gotoxy(START_X,START_Y);
	cputs("\n\nHello World");
	getch();
	return 0;
}