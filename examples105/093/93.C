#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
/*定义游戏级别*/
#define ELEMENTARY 15 /*初级*/
#define INTERMEDIATE 8/*中级*/
#define ADVANCED 3/*高级*/

#define  R 5              /*球半径*/
struct box
{ 
  int x;
  int y;
  int color;
}a[6][14];  
int delaytime = 30;/*表示球的移动速度，今而表示游戏的级别*/
int MouseX;
int MouseY=400;
int dx=1,dy=1;              /*计算球的反弹*/
int sizex=18,sizey=10;      /*box的宽度和长度*/

void InitGraphics()
{
	int gdriver = DETECT,gmode;
  initgraph(&gdriver,&gmode,"c:\\tc");
}
void InitGame()
{
	int grade;
	gotoxy(20,3);
	printf("Welcome to the Game of Striking ball\n\n");
	gotoxy(20,5);
	printf("please input the grade you want to play:");
	gotoxy(20,6);
	printf("   1: elementary \n");
	gotoxy(20,7);
	printf("   2: intermediate \n");
	gotoxy(20,8);
	printf("   3: advanded \n");
	scanf("%d",grade);
	switch(grade)
	{
		case 1 : 
			delaytime = ELEMENTARY;break;
		case 2 : 
			delaytime = INTERMEDIATE;break;
		case 3 : 
			delaytime = ADVANCED;break;
		default:
			delaytime = ELEMENTARY;break;
	}
}
void DrawBox(int x,int y)     /* x, y为左上角坐标sizex,sizey为长和宽*/
{
 int sizx=sizex-1;
 int sizy=sizey-1;
 setcolor(15);
 line(x,y,x+sizx-1,y);
 line(x,y+1,x+sizx-2,y+1);
 line(x,y,x,y+sizy-1);
 line(x+1,y,x+1,y+sizy-2);
 setcolor(8);
 line(x+1,y+sizy,x+sizx,y+sizy);
 line(x+2,y+sizy-1,x+sizx,y+sizy-1);
 line(x+sizx-1,y+1,x+sizx-1,y+sizy);
 line(x+sizx,y+2,x+sizx,y+sizy);
 setcolor(7);
 putpixel(x,y+sizy,3);
 putpixel(x+1,y+sizy-1,3);
 putpixel(x+sizx,y,3);
 putpixel(x+sizx-1,y+1,3);
 setfillstyle(1, 7);
 bar(x+2,y+2,x+sizx-2,y+sizy-2);
}
/*绘制游戏界面*/
void DrawInterface()
{ 
	int i,j;
	cleardevice();
  setcolor(15);
  rectangle(99,49,413,451);
  for(i=0;i<6;i++)
      for(j=0;j<14;j++)
      { 
      	a[i][j].color=0;
        a[i][j].x=104+j*22;
        a[i][j].y=54+i*14;
        DrawBox(104+j*22,54+i*14);
      }          
  sizex=50,sizey=5;
} 
/*鼠标光标显示*/
void DrawMouse(int x,int y)
{
  DrawBox(x,y);
}
/*设置鼠标左右边界*/
void MouseSetX(int lx,int rx)
{
   _CX=lx;
   _DX=rx;
   _AX=0x07;
   geninterrupt(0x33);
}
/*设置鼠标上下边界*/
void MouseSetMaxY(int uy,int dy)
{
   _CX=uy;
   _DX=dy;
   _AX=0x08;
   geninterrupt(0x33);
}
/*设置鼠标当前位置*/
void MouseSetXY(int x,int y)
{
   _CX=x;
   _DX=y;
   _AX=0x04;
   geninterrupt(0x33);
}
/*获取鼠标当前位置*/
void MouseGetXY()
{
   _AX=0x03;
   geninterrupt(0x33);
   MouseX=_CX;
   MouseY=_DX;
}

void MouseStatus()/*鼠标按键情况*/
{
  int x;
  int status;
  status=0;/*默认鼠标没又移动*/
  x=MouseX;
  if(x==MouseX&&status==0) /*鼠标没动*/
  {
    MouseGetXY();
    if(MouseX!=x)
      if(MouseX+50<413)
        status=1;
  }
  if(status)/*移动情况才重新显示鼠标*/
  {
    setfillstyle(1,0);
    bar(x,MouseY,x+sizex,MouseY+sizey);
    DrawMouse(MouseX,MouseY);/*新位置显示*/
  }
}

void BallStrike()
{
	int ballX;     /*球的圆心*/
  int ballY = MouseY-R;
  int i,j,t=0;
  randomize();
  while(ballX=random(409))
   if(ballX>=105 && ballX<=408)     
      break;
  while(kbhit)
  {
    MouseStatus();
    if(ballY<=(58-R))   /*碰上反弹*/
      dy*=(-1);
    if(ballX>=(413-R)||ballX<=(108-R)) /*碰左右反弹*/
      dx*=(-1);
    setcolor(WHITE);
    circle(ballX+=dx,ballY-=dy,R-1);
    delay(delaytime);
    setcolor(0);
    circle(ballX,ballY,R-1);
    for(i=0;i<6;i++)
     for(j=0;j<14;j++)       /*判断是否传记撞击box*/
         if(t<84&&a[i][j].color==0 && ballX>=a[i][j].x && ballX<=a[i][j].x+18 
              && ballY>=a[i][j].y && ballY<=a[i][j].y+10)
              {
              	t++;
                dy*=(-1);
                a[i][j].color=1;
                setfillstyle(1,0);
                bar(a[i][j].x,a[i][j].y,a[i][j].x+18,a[i][j].y+10);
              }          
  if(ballX==MouseX||ballX==MouseX-1||ballX==MouseX-2&&ballX==(MouseX+50+2)||ballX==(MouseX+50+1)||ballX==(MouseX+50)) /*碰板反弹*/
    if(ballY>=(MouseY-R))
      { 
      	dx*=(-1);
        dy*=(-1);         /*原路返回*/
      }
  if(ballX>MouseX && ballX<(MouseX+50)) /*碰板反弹*/
    if(ballY>=(MouseY-R))
       dy*=(-1);
  if(t==84)
  { 
  	 sleep(1);
     cleardevice();
     setcolor(RED);
     settextstyle(0,0,4);
     outtextxy(100,200,"You Win");
     sleep(1);
     break;
  }
  if(ballY>MouseY)
   { 
   	 sleep(1);
     cleardevice();
     setcolor(RED);
     settextstyle(0,0,4);
     outtextxy(100,200,"Game Over");
     sleep(1);
     break;
   } 
 }
}

void main()
{
  InitGraphics();
  InitGame();
  DrawInterface();
  MouseSetX(100,362);           /*设置鼠标移动的范围*/
  MouseSetMaxY(MouseY,MouseY);     /*鼠标只能左右移动*/
  MouseSetXY(150,MouseY);       /*鼠标的初始位置*/
  DrawMouse(MouseX,MouseY);       /*第一次显示鼠标*/
  BallStrike();
  closegraph();
}

 
