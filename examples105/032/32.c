#include<conio.h>
#include<alloc.h>
#include<stdio.h>
#include<stdlib.h>

#define WIDTH 25 /*���ڿ��*/
#define HEIGHT 15 /*���ڿ��*/
#define START_X 10
#define START_Y 5  /* �������Ͻ�����(START_X,START_Y) */
int main()
{
	int i;
	/*���ƴ���*/
	window(START_X,START_Y,START_X+WIDTH,START_Y+HEIGHT);
	textattr(128+BLACK+(WHITE<<4)); 
	clrscr();
	/*���ƺ�߿�*/
	for(i = 2;i<=24;i++)
	{
		gotoxy(i,1);
		putch('=');
		gotoxy(i,15);
		putch('=');
	}
	/*�������߿�*/
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