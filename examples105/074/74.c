#include <dos.h>
#include <conio.h>
#include <stdio.h>
#define START_X 20
#define START_Y 20/*��START_X��START_Y�޶������������Ͻǵ�λ�� */
#define END_X 260
#define END_Y 160/*��END_X��END _Y�޶������������½ǵ�λ�� */
/* ���㺯�� */
void DrawPoint(int x,int y,int color)   
{
   char far *pointer;
   pointer = (char far*)(0x0a0000000L);
   *(x+y*320+pointer) = color;
}
/* �����κ���*/
void DrawRectangle(int left_x,int left_y,int right_x,int right_y,int color)  
{
   int i;
   /*���û��㺯����������*/
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
    /*��ʼ������λ��*/
    left_x = START_X;
    left_y = START_Y;
    right_x = END_X;
  	right_y = END_Y;
    /*����13Hģʽ  */
    In.x.ax=0x13;                 
    int86(0x10,&In,&In);
    for(i = 0;i < 20; i++)
       DrawRectangle(left_x++,left_y++,right_x--,right_y--,i+1);
    getch();
    /* �˳�13Hģʽ */
    In.x.ax=0x03;             
    int86(0x10,&In,&In);
    return 0;
}
