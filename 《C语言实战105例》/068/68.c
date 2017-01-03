#include<stdio.h>
#include<fcntl.h>
#include<stat.h>
#include<io.h>
#include<string.h>
#include<stdlib.h>
#include<alloc.h>
#include<dos.h>
#include<conio.h>
#include<graphics.h>

unsigned char *buffer;
int main()
{
	int handle;
	int i;
	int gdriver=VGA,gmode=VGAHI;
	initgraph(&gdriver,&gmode,"e:\\tc");
	cleardevice();
	for(i=10;i<=140;i++)
	arc(320,240,0,150,i);
	outtextxy(160,300,"press any key to save the picture");
	getch();
	handle=_creat("save.pic",FA_ARCH);
	/*设定读模式*/
	outportb(0x3ce,5);
	outportb(0x3cf,0);
	/*选择影射寄存器*/
	outportb(0x3ce,4);
	/*0x3cf的D0、D1位共同决定了选择的页面*/
	outportb(0x3cf,3);
	_write(handle,(void *)buffer,28000);
	outportb(0x3cf,2);
	_write(handle,(void *)buffer,28000);
	outportb(0x3cf,1);
	_write(handle,(void *)buffer,28000);
	outportb(0x3cf,0);
	_write(handle,(void *)buffer,28000);
	_close(handle);
	closegraph();
	getch();
	return 0;
}