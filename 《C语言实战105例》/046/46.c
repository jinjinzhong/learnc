#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
/*定义结构体MCB表示内存控制块*/
struct MCB
{
	unsigned char type;
	unsigned int  owner;
	unsigned int  size;
	unsigned char unused[3];
	unsigned char dos[8];
};
unsigned char far *vector,vectdat[1024];
unsigned int seg,i;
FILE *fp;
struct MCB *mcb;
/*定义函数ClearMem*/
void ClearMem()
{
	fp=fopen("e:\\clrmen.dat","rb");
	seg=(unsigned int)getw(fp);
	mcb=(struct MCB far *)MK_FP(seg,0);
	while(mcb->type=='M')
	{
		mcb->owner=0;
		mcb=(struct MCB far *)MK_FP(FP_SEG(mcb)+mcb->size+1,0);
	}
	vector=(unsigned char far *)MK_FP(0,0);
	disable();
	for(i=0;i<1024;i++)
	*(vector+i)=fgetc(fp);
	enable();
	fclose(fp);
	_AX=0x3;
	geninterrupt(0x10);
}
/*定义函数SaveMem*/
void SaveMem()
{
	fp=fopen("e:\\clrmen.dat","wb");
	seg=*(unsigned int *)MK_FP(_psp,0x2c)-1;
	mcb=(struct MCB far *)MK_FP(seg,0);
	putw(seg,fp);
	vector=(unsigned char far *)0x0;
	for(i=0;i<1024;i++)
  fputc(*(vector+i),fp);
}
int main(int argc,char *argv[])
{
	puts("***************************************");
	puts("| This program will clear your memory |");
	puts("***************************************");
	mcb->size=0;
	if(argc==1)
	{
		ClearMem();
		printf("Clear your memory successfully!\n");
		return 1;
	}
	if(argc==2)
	{
		if(strcmp(argv[1],"-s")==0)
		{
			SaveMem();
		  printf("Save record Successfully!\n");
			return 1;
		}
	}
	printf("Clear your memory failly!");
	return 0;
}