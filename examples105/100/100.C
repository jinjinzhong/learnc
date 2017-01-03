#include<dos.h>
#include<graphics.h>
#include<stdio.h>
int x,y;
void gameexit(),saverect(),drawrect();
void  *buff;
void main()
{
	int i,j,key;
 	int processkey();
 	char c[]="help:right,down,left,up,enter,esc;";
  	int gdriver=DETECT,gmode;
  	initgraph(&gdriver,&gmode,"E:\\TC");
  	cleardevice();
  	saverect();

  	cleardevice();
  	setbkcolor(7);
      	settextstyle(0,0,1);
  	setcolor(9);
  	outtextxy(130,380,c);

    setcolor(16);
  	for(i=0;i<5;i++)
   		for(j=0;j<5;j++)
    			rectangle(200+j*35,100+i*35,230+j*35,130+i*35);
  	setcolor(1);
  	rectangle(200,100,230,130);
  	x=200;
  	y=100;
  	while(1)
  	{
  		key=bioskey(0);
     		dokey(key);
   	}
}

void saverect()   /*存储方格*/
{
	bar(0,0,29,29);
	buff=sizeof(imagesize(0,0,29,29));
  	getimage(0,0,28,28,buff);
}
void drawrect(x,y)   /*画方格*/
{
	void judgefull();
    	putimage(x+1,y+1,buff,1);
    	if(x!=200)
    	putimage(x+1-35,y+1,buff,1);
    	if(x!=340)
    	putimage(x+1+35,y+1,buff,1);
    	if(y!=100)
    	putimage(x+1,y+1-35,buff,1);
    	if(y!=240)
    	putimage(x+1,y+1+35,buff,1);
    	judgefull();
}


int dokey(int key)  /*键盘处理*/
{
	int prect(),nrect();
    	switch(key)
    	{
    		case 0x4800 : if(y!=100) {prect(x,y);nrect(x,y-=35);} break;
    		case 0x4b00 : if(x!=200) {prect(x,y);nrect(x-=35,y);} break;
    		case 0x4d00 : if(x!=340) {prect(x,y);nrect(x+=35,y);} break;
    		case 0x5000 : if(y!=240) {prect(x,y);nrect(x,y+=35);} break;
    		case 0x11b  : gameexit();break;
    		case 0x1c0d : drawrect(x,y);break;
   }
}

void judgefull()   /*判断是否画满*/
{
	void win();
	int color=15,t=0,i,j;
 	for(i=0;i<5;i++)
   		for(j=0;j<5;j++)
    			if(color!=getpixel(215+i*35,115+j*35))
     				{t=1;break;}
  	if(t==0)
   	win();
}

void win()   

{
	char c;
	settextstyle(3,0,2);
	outtextxy(50,100,"Well done ! Do you want to replay (y/n) ");
	do
	{
 		c=getch();
 		if(c=='y'||c=='Y')
       		main();  /*从新玩就返回主函数*/
   		if(c=='n'||c=='N')
   		gameexit();
 	}while(c=='y'||c=='Y'||c=='n'||c=='N');
}

 

int prect(x,y)   /*在新位置画方框*/
{
 	setcolor(15);
 	rectangle(x,y,x+30,y+30);
}

int nrect(x,y)   /*将原来位置的方框清除*/
{
 	setcolor(1);
 	rectangle(x,y,x+30,y+30);
}

void gameexit()
{ 
 	free(buff);
   	closegraph();
 	exit(0);
}

