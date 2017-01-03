#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<malloc.h>

/*����GDT����������ṹ*/
struct DESCRIPTION
{
	unsigned int size;
	unsigned int low16;
	unsigned int high8;
	unsigned char arribution;
	unsigned int res;
};
/*����ȫ�ֵ�ַ����������ṹ*/
struct GDT
{
	struct DESCRIPTION NullDsc;
	struct DESCRIPTION GDTDsc;
	struct DESCRIPTION SrcDsc;
	struct DESCRIPTION DstDsc;
	struct DESCRIPTION BioscsDsc;
	struct DESCRIPTION BiosssDSC;
};

unsigned char *buffer;
long filelength=0;
long loop;
struct GDT gdtAddrTable={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0x93,0},{0,0,0,0x93,0},{0,0,0,0,0},{0,0,0,0,0}};

/*���庯��GetEmmsize��ȡ��չ�ڴ�����*/
unsigned int GetEmmsize()
{
	union REGS rd,op;
	rd.h.ah=0x88;
	int86(0x15,&rd,&op);
	return op.x.bx;
}
/*����Դ���ݿ��ַ����ֵ*/
struct GDT SetSrcaddr(struct GDT *emm,long emmaddr,unsigned size)
{
	emm->SrcDsc.low16=emmaddr&0x0ffff;
	emm->SrcDsc.high8=emmaddr>>16;
	emm->SrcDsc.size=size;
	return (*emm);
}
/*����Ŀ�����ݿ��ַ����ֵ*/
struct GDT SetDstaddr(struct GDT *emm,long emmaddr,unsigned size)
{
	emm->DstDsc.low16=emmaddr&0x0ffff;
	emm->DstDsc.high8=emmaddr>>16;
	emm->DstDsc.size=size;
	return (*emm);
}
/*Դ���ݿ鵽Ŀ�����ݿ�֮������ݴ���*/
void TrasData(struct GDT *emm,unsigned size)
{
	union REGS in,out;
	struct SREGS seg;
	seg.es=FP_SEG(emm);
	in.x.si=FP_OFF(emm);
	in.x.cx=size>>1;
	in.x.ax=0x8700;
	int86x(0x15,&in,&out,&seg);
}
/*���庯������չ�ڴ���д����*/
int InputEmm(char *filename,long emmaddr)
{
	FILE *fp;
	long size,addr;
	unsigned num,i,buffersize=0x8000;
	if(!(fp=fopen(filename,"rb")))
	{
		printf("can't open file %s \n",filename);
		exit(0);
	}
	fseek(fp,0L,SEEK_END);
	filelength=ftell(fp);
	rewind(fp);
	size=GetEmmsize();
	/*���������ļ���ҳ��*/
	loop=filelength/buffersize+1;
	/*�����ַ*/
	addr=FP_SEG(buffer);
	addr=(addr<<4)+FP_OFF(buffer);
	/*����Դ���ݿ��ַ����ֵ*/
	SetSrcaddr(&gdtAddrTable,addr,buffersize);
	addr=emmaddr;
	/*���ν���ҳд�뵽��չ�ڴ���ȥ*/
	for(i=0;i<loop;i++)
	{
		num=fread(buffer,sizeof(char),buffersize,fp);
		SetDstaddr(&gdtAddrTable,addr,num);
		TrasData(&gdtAddrTable,num);
		addr=addr+buffersize;
	}
	fclose(fp);
	return 1;
}
int main(int argc,char **argv)
{
	int i=0;
	if(argc!=2)
	{
	  printf("Please input the sourcefile\n");
	  return 0;
	}
	buffer=malloc(0x8000*sizeof(char));
	if(!buffer)
	{
		printf("malloc memery error!\n");
		exit(0);
	}
	i=InputEmm(argv[1],0x400000);
	if(i==1)
		printf("Input the file %s to extend memorsy successfully!\n",argv[1]);
	else
		printf("Input the file to extend memory error\n");
	free(buffer);
	getch();
	return 1;
}