#include <dos.h>
#include <conio.h>
#include <stdio.h>
#define START_X 20
#define START_Y 20/*宏START_X和START_Y限定了相框的最左上角的位置 */
#define END_X 260
#define END_Y 160/*宏END_X和END _Y限定了相框的最右下角的位置 */
/* 画点函数 */
void DrawPoint(int x,int y,int color)   
{
   char far *pointer;
   pointer = (char far*)(0x0a0000000L);
   *(x+y*320+pointer) = color;
}
/* 画矩形函数*/
void DrawRectangle(int left_x,int left_y,int right_x,int right_y,int color)  
{
   int i;
   /*调用画点函数来画矩形*/
   for(i=left_x; i<=right_x; i++)
   {
      DrawPoint(i,left_y,color);
      DrawPoint(i,right_y,color);
   }
   for(i=left_y; i<=right_y; i++)
   {
      DrawPoint(left_x,i,color);
      DrawPoint(right_x,i,color);
   }
}
int main()
{
    int left_x, left_y, right_x, right_y, i;
    union REGS In;
    /*初始化坐标位置*/
    left_x = START_X;
    left_y = START_Y;
    right_x = END_X;
  	right_y = END_Y;
    /*进入13H模式  */
    In.x.ax=0x13;                 
    int86(0x10,&In,&In);
    for(i = 0;i < 20; i++)
       DrawRectangle(left_x++,left_y++,right_x--,right_y--,i+1);
    getch();
    /* 退出13H模式 */
    In.x.ax=0x03;             
    int86(0x10,&In,&In);
    return 0;
}
