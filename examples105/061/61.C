#include <stdio.h>
#include <graphics.h> 
#define BEGIN 160 /*起始点*/
#define END 400   /*终点*/
#define WIDTH 20  /*表格宽度*/                 
int main()
{
	int gdriver=DETECT,gmode;
	int i,j;
    initgraph(&gdriver,&gmode,"c:\\tc");    /*设置图形方式初始化*/
    cleardevice();       					/*清屏*/
    setbkcolor(BLACK);     					/*设置背景为黑色*/                         
	for(j = BEGIN;j <= END;j+=WIDTH)
	   for(i= BEGIN;i<=END;i++)             	/*绘制表格中的横坐标线*/
	   	putpixel(i,j,WHITE);      
	for(i = BEGIN;i <= END;i+=WIDTH)
	   for(j = BEGIN;j <= END;j++)             	/*绘制表格中的纵坐标线*/
		putpixel(i,j,WHITE);
	getch();
	return 0;
}