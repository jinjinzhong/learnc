#include "graphics.h"
#include "bios.h"
#include "conio.h"
#include "stdlib.h"
#include "dos.h"

#define UP 			0x4800
#define DOWN 		0x5000
#define LEFT 		0x4600
#define RIGHT 	0x4d00
#define ESC 		0x0016

/*定义两种屏幕显示模式*/
#define VGA256 	0x13
#define TEXT 		0x03

int x,y,l,sxzy=0,zx=0,xx=5,yy=167;
int x1=5,y1=3,x3=0,y3=0,x4=0,y4=0;
int enemylife=10,playerlife=20;
int board[100][170];
unsigned char far *VideoBuffer=(char far *)0xA0000000L;

/*设置屏幕显示模式*/
void SetScreenMode(int mode)
{ 
	union REGS inregs,outregs;
  inregs.h.ah=0;
  inregs.h.al=(unsigned char)mode;
  int86(0x10,&inregs,&outregs);
}
/*画垂直线函数*/
void DrawVerticalLine(int y0,int y1,int x,unsigned int color)
{ 
	unsigned int address,n,temp;
  address=320*y0+x;
  for(n=0;n<=y1-y0;n++)
  {
    if(y0>y1)
    {
      temp=y1;
      y1=y0;
      y0=temp;
    }
    VideoBuffer[address]=color;
    address+=320;
  }
}
/*绘制水平线函数*/
void DrawHorizontalLine(int x0,int x1,int y,unsigned int color)
{ 
	unsigned int address,n,temp;
  address=320*y+x0;
  for(n=0;n<=x1-x0;n++)
  {
    if(x0>x1)
    {
      temp=x1;
      x1=x0;
      x0=temp;
    }
    VideoBuffer[address]=color;
    address+=1;
  }
}

void p_pixel(int x,int y,unsigned int color)
{ 
	VideoBuffer[y*320+x]=color;
}
/*绘制正方形函数*/
void DrawSquare(int x,int y,int side,int color)
{
  DrawHorizontalLine(x,x+side,y,color);
  DrawHorizontalLine(x,x+side,y+side,color);
  DrawVerticalLine(y,y+side,x,color);
  DrawVerticalLine(y,y+side,x+side,color);
}
/*绘制矩形函数*/
void DrawRectangle(int x1,int y1,int x2,int y2,int color)
{
  DrawHorizontalLine(x1,x2,y1,color);
  DrawHorizontalLine(x1,x2,y2,color);
  DrawVerticalLine(y1,y2,x1,color);
  DrawVerticalLine(y1,y2,x2,color);
}
/*绘制实心矩形函数*/
void FillRectangle(int x1,int y1,int x2,int y2,int color)
{
 int i;
 for(i=y1;i<=y2;i++)
 		DrawHorizontalLine(x1,x2,i,color);
}

/*每次出拳后，删除拳头*/
void ClearBox()                           

{ 
	delay(100);
  DrawSquare(x3,y3,5,0);
  DrawSquare(x3,y3-6,5,0);
  x3=0;
  y3=0;
}
/*绘制我方机器人*/
void DrawPlayer()                             
{ 
	int cas=0;
  if(sxzy==18432)                    
	/*如果按上键，就往上移动*/
  { 
  	yy-=5;
    if(yy < y1+30)
      yy+=5;
    if(yy==12)
      yy=17;
  }
  if(sxzy==20480)   /*如果按下键，就往下移动*/
  { 
  	yy+=5;
    if(yy==172)
      yy=167;
  }
  if(sxzy==19200)   /*如果按左键，就往左移动*/
  { 
  	xx--;
    if(xx==-1)
      xx=0;
  }
  if(sxzy==19712)   /*如果按右键，就往右移动*/
  { 
  	xx++;
    if(xx==13)
      xx=12;
  }
  sxzy=0;
  for(x=xx;x<5+xx;x++)   /*给自己搭建骨架*/
  {
     if(x==xx)                        /*左手*/
     {
        y=167;
        board[x][yy]=1;
        if(zx==11386)
        {
     			board[x][yy-12]=3;
     			board[x][yy-11]=3;
					if((yy-11 < y1+30) && (xx>=x1 && xx<=x1+4))
              enemylife--;
					cas=1;
          zx=0;
        }
        x++;
    }
    if(x==xx+4)   /*右手*/
    {
       y=167;
       board[x][yy]=1;
       if(zx==11640)
       {
			   board[x][yy-12]=3;
				 board[x][yy-11]=3;
         if((yy-11 < y1+30)&&(xx+4<=x1+4 && xx+4>=x1))
            enemylife--;
         cas=2;
         zx=0;
      }
      break;
   }
   for(y=yy;y<yy+3;y++)         /*身体*/
   {
      board[x][y]=1;
   }
  }
  for(x=0;x<100;x++)     /*开始往骨架上放‘肉’*/
  {
  	l=1;
    for(y=0;y<170;y++)
    if(board[x][y]==1 || board[x][y]==3)
		{
		 if(cas==1)
     { 
      	board[x][yy-10]=1;
        board[x][yy]=0;
        cas=0;
     }
	   if(cas==2)
	   { 
	  		board[x+4][yy-10]=1;
	    	board[x+4][yy]=0;
	      cas=0;
	   }
	   if(board[x][y]==3)
     {
       x3=x+105+x*5;
       y3=y+l*5;
     }
     DrawSquare(x+105+x*5,y+l*5,5,3);
     l++;
    }
  }
  ClearBox();
}
/*搭建设对方骨架*/
void DrawEnemySk()                           

{ 
	int ran,cas=0,p=0;
  delay(200);
  for(x=99;x>=0;x--)
  {
    l=1;
    for(y=169;y>=0;y--)
			if(board[x][y]==2 || board[x][y]==4)
      {
         DrawSquare(x+105+x*5,35+y-l*5,5,0);
         l++;
         board[x][y]=0;
     }
  }
  ran=random(5);
  if(ran==0)                       /*往上走*/
  { 
  	y1-=5;
    if(y1==-2)
      y1=3;
  }
  if(ran==1)
  { 
  	y1+=5;
    if(y1+30 > yy)  /*不允许超过我的机器人的身后*/
    y1-=5;
    if(y1==158)  
		/*往下走，如果超过外框，就减去一步，实际上是永远也不会超过*/
 		 y1=153;
  }
  if(ran==2)       /*往左走*/
 	{ 
 		x1--; 
   	if(x1==-1)
      x1=0;
 	}
  if(ran==3)    /*往右走*/
  { 
  	x1++;
    if(x1==13)
      x1=12;
  }
  if(ran==4)
  { 
  	y1+=5;
    if(y1+30 > yy)            
		/*不允许超过我的机器人的身后*/
    	y1-=5;
    if(y1==158)               
		/*往下走，如果超过外框，就减去一步，实际上是永远也不会超过*/
			y1=153;
   }
   for(x=x1;x<x1+5;x++)               /*对方拳头*/
   {
     if(x==x1)
     {  
     	if((y1+45 >= yy) && x>=xx)      
			/*判断敌人是否靠近，如果是就出拳头*/
     	{ 
     		p=random(2);
        if(p==1)
  			{
    			board[x][y1+15]=4;
    			board[x][y1+16]=4;
    			board[x][y1+17]=4;
          if((yy-11 < y1+30)&&(xx+4<=x1+4 && xx+4>=x1))
             playerlife--;
          cas=1;
        }
        p=0;
      }
      if(cas==1)
      { 
      	board[x][y1+14]=2;
        cas=0;
      }
      else
        board[x][y1]=2;
      x++;
    }
    if(x==x1+4)
    {  
    	if((y1+45 >= yy) && x<=xx+4)
     	{ 
     		p=random(2);
        if(p==1)
  			{
    			board[x][y1+15]=4;
    			board[x][y1+16]=4;
    			board[x][y1+17]=4;
          if((yy-11 < y1+30)&&(xx>=x1 && xx<=x1+4))
            playerlife--; 
          cas=1;
        }
        p=0;
     }
     if(cas==1)
     { 
     	  board[x][y1+14]=2;
				cas=0;
     }
     else
       board[x][y1]=2;
     break;
   }
   for(y=y1;y+3>y1;y--)
   {
      board[x][y]=2;
   }
  }
}
void ClearEnemyBox()    /*删除对方拳头*/
{ 
	delay(100);
  DrawSquare(x4,y4+12,5,0);
  DrawSquare(x4,y4+6,5,0);
  DrawSquare(x4,y4,5,0);
  x4=0;
  y4=0;
}

void DrawEnemy()    /*画出对方*/
{
  int key=0;
  while(key!=283 && enemylife>0 && playerlife>0)
  {
    FillRectangle(250+enemylife,50,300,53,0);
    FillRectangle(250+playerlife,150,280,153,0);
    while(bioskey(1)==0)
    {   
    	DrawEnemySk();
      for(x=99;x>=0;x--)
      {
         l=1;
         for(y=169;y>=0;y--)
         if(board[x][y]==2||board[x][y]==4)
         {
            DrawSquare(x+105+x*5,35+y-l*5,5,3);
            if(board[x][y]==4)
     				{
              x4=x+105+x*5;
              y4=35+y-l*5;
            }
            l++;
         }
       }
       ClearEnemyBox();
    }
    key=bioskey(0);
		if(key==18432 || key==20480 || key==19200 || key==19712 || key==11386 || key==11640)
    {
      if(key==11386 || key==11640)        
			/*按键的判断*/
        zx=key;       
      else
        sxzy=key;
      key=0;
      for(x=0;x<100;x++)
      {
        l=1;
        for(y=0;y<170;y++)
        if(board[x][y]==1 || board[x][y]==3)
        {
          DrawSquare(x+105+x*5,y+l*5,5,0);
          l++;
          board[x][y]=0;
        }
      }
      DrawPlayer();
    }
  }
}
int  main()
{ 
	int x=0,y,i=1,key,c=0,p,k=0,e=1;
  int gdriver=DETECT,gmode;
  initgraph(&gdriver,&gmode,"e:\\tc");
  cleardevice();
  setcolor(RED);
  while(i)
  {
    settextstyle(1,0,5);
    setwritemode(XOR_PUT);
    outtextxy(x,200,"X man");
    delay(10);
    outtextxy(x,200,"X man");
    x+=2;
    if(x>200)
      i=0;
  }
  outtextxy(x,200,"X man");
  while(!kbhit())
  {
   	setcolor(c);
    outtextxy(x,200,"X man");
    c++;
    if(c>16)
      c=0;
  }
  settextstyle(0,0,1);
  setcolor(GREEN);
  outtextxy(300,300,"please press 's' to start");
  while(e)
  {
    k=bioskey(0);
    if(k==8051)
      e=0;
  }
 
  board[99][169]=4;
  closegraph();
  SetScreenMode(VGA256);
  /*绘制游戏区的边框*/
	DrawRectangle(104,20,207,190,7);
	
  FillRectangle(250,50,250+enemylife,53,4);
  FillRectangle(250,150,250+playerlife,153,4);
  DrawPlayer();
  DrawEnemy();
	initgraph(&gdriver,&gmode,"e:\\tc");
  if(enemylife==0)
  {
	   setcolor(WHITE);
	   settextstyle(0,0,4);
	   outtextxy(100,20,"You Win!");
	   setcolor(GREEN);
	   outtextxy(101,20,"You Win!");
	   getch();
	   getch();
	   getch();
  }
	else if(playerlife==0)
  {
	   setcolor(WHITE);
	   settextstyle(0,0,4);
	   outtextxy(100,20,"You Failed!");
	   setcolor(GREEN);
	   outtextxy(101,20,"You Failed!");
	   getch();
	   getch();
	   getch();
 	}
	getch();
	closegraph();
	SetScreenMode(TEXT);
	return 0;
}
