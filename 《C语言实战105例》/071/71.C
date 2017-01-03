#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>
#define  PI 3.1415926
#define  START_X     100           
#define  START_Y     80			/*（START_X,START_Y）是起始位置*/
#define  F_WIDTH     300        /*红旗的宽度*/
#define  F_HEIHGT    150        /*红旗的高度*/
#define  W_WIDTH     100        /*波浪的宽度*/
#define  W_HEIGHT    5          /*波浪的高度*/  
#define  M_WIDTH     2          /*旗杆的宽度*/
#define  M_HEIGHT    300		/*旗杆的高度*/
int main()
{
  
  float angle;
  int x,y;
  int i;
  int modify_y[W_WIDTH];		          /*对纵坐标的修改量,来模拟红旗的波浪形状*/
  int gdriver=DETECT,gmode;
  initgraph(&gdriver,&gmode,"c:\\tc");    /*设置图形方式初始化*/
  cleardevice();       					  /*清屏*/
  for(i = 0; i < W_WIDTH; i++)            /*计算数组modify_y的值,这里采用了正玄波浪*/
  {
    angle = 2*PI*((float)i/W_WIDTH);
    modify_y[i] = W_HEIGHT * sin(angle);
  }
  setcolor(RED);
  for(i = 0; i < F_WIDTH; i++)             /*利用画线函数来绘制红旗*/
  {
    x = START_X + i;
    y = START_Y + modify_y[i%W_WIDTH];
    line(x,y,x,y + F_HEIHGT);   
  }
  for(i = 0;i < M_WIDTH; i++)				/*绘制旗杆*/
  {
  	x = START_X + i;
    y = START_Y;
    line(x,y,x,y + M_HEIGHT);   
  }
  getch();
  closegraph();
  return 0;
}   

