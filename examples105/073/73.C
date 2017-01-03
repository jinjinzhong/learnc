#include<stdio.h>
#include<dos.h>
#include<graphics.h>
#include<fcntl.h>
#include<time.h>
void interrupt(* handler)( );
int handle,control;
enum NOTES
{
	C10=131,D10=147,E10=165,F10=175,G10=196,A10=220,B10=247,
	C0=262, D0=296, E0=330, F0=349, G0=392, A0=440, B0=494,
	C1=523, D1=587, E1=659, F1=698, G1=784, A1=880, B1=988,
	C2=1047, D2=1175, E2=1319, F2=1397, G2=1568, A2=1760, B2=1796
}song[]={
	E1,16,E1,8,E1,8,F1,16,G1,16,F1,16,F1,16,E1,16,D1,
  16,C1,16,C1,16,D1,16,E1,16,E1,16,D1,16,D1,16,E1,16,
  E1,8,E1,8,F1,16,G1,16,G1,16,F1,16,E1,16,D1,16,C1,
  16,C1,16,D1,16,E1,16,D1,16,D1,16,C1,16,D1,16,D1,8,
  D1,8,E1,16,C1,16,D1,16,E1,8,F1,8,E1,16,C1,16,D1,
  16,E1,8,F1,8,E1,16,C1,16,C1,16,D1,16,G0,16,E1,16,
  E1,16,E1,8,F1,16,G1,16,G1,16,F1,16,E1,16,D1,16,C1,
  16,C1,16,D1,16,E1,16,E1,16,D1,16,C1,16,D1,16,
  0,0};
void interrupt music()
{
	static int flag=0,note=0,fre,dur=8;
	flag++;
	fre=song[note];
	dur=song[note+1];
	if(fre)
	{
		flag=0;
		 /*打开计数器*/
		outportb(0x43,0xb6);
		/*计算频率*/
		fre=(unsigned)(1193180L/fre); 
		/*将频率写入计时器*/
		outportb(0x42,(char)fre); 
		outportb(0x42,(char)(fre>>8));
		 /*从扬声器端口读出控制信息*/
		control=inportb(0x61);
		/*写入扬声器，使之发声*/
		outportb(0x61,(control)|0x3); 
		note=note+2;
		if(note>=134)note=0;
	}
}
void main()
{
	int gdriver=DETECT,gmode,i,j;
	initgraph (&gdriver,&gmode,"e:\\tc");
	/*获取0x1c中断向量*/
	handler=getvect(0x1c); 
	/*将music函数写入到0x1c中断向量中去*/
	setvect(0x1c,music); 
	/*清除屏幕*/
	cleardevice( ); 
	/*将背景色设置成黑色*/
	setbkcolor(BLACK); 
	for(i=0;i<300;i++)
	{
		j=i%30;
		/*前景色设置*/
		setcolor(j/2);
		/*画圆*/
		circle(320,240,(j+1)*5); 
		if(j==0)cleardevice( ); 
		delay(100);
	}
	/*关闭PC扬声器*/
	outportb(0x61,control&0xfe); 
	/*将0x1c中断向量置成系统原有的处理例程*/
	setvect(0x1c,handler); 
	getch();
	cleardevice();
	closegraph();
}


