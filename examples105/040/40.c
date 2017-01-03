#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*����ļ�����*/
void OutputFile(FILE *fp)
{
	char ch;
	while((ch=fgetc(fp))!=EOF)
		putchar(ch);
}
/*�ļ���Ϣ�ϲ�����*/
void MergeFile(FILE *s1fp,FILE *s2fp,FILE *dfp,int *num)
{
	char ch1,ch2;
	/*��ʼ��ch1��ch2Ϊ�ļ������ַ�*/
	ch1=fgetc(s1fp);
  ch2=fgetc(s2fp);
  /*���ļ��ж�ȡ�ַ���ֱ����һ���ļ�����*/
 	while((ch1!=EOF)&&(ch2!=EOF))
 	/*�����ַ��ıȽ�*/
  if(ch1<=ch2)
  {
  		fputc(ch1,dfp);
  		/*�ַ�������1*/
  		*num=*num+1;
  		ch1=fgetc(s1fp);
  }
  else
  {
  		fputc(ch2,dfp);
  		/*�ַ�������1*/
  		*num=*num+1;
  		ch2=fgetc(s2fp);
  }
  /*����ļ�s1fp���������ļ�s2fp��ʣ������д�뵽�ļ�dfp*/
  if(ch1==EOF)
  	while((ch2=fgetc(s2fp))!=EOF)
  	{
  		fputc(ch2,dfp);
  		/*�ַ�������1*/
  		*num=*num+1;
  	}
  /*����ļ�s2fp���������ļ�s1fp��ʣ������д�뵽�ļ�dfp*/
  else
 		while((ch1=fgetc(s1fp))!=EOF)
 		{
  		fputc(ch1,dfp);
  		/*�ַ�������1*/
  		*num=*num+1;
  	}
}

void main()
{
	char s1filename[20],s2filename[20],dfilename[20];
	FILE *s1fp,*s2fp,*dfp;
	int num=0;
	clrscr();
	/*�õ���һ���ļ����ļ���*/
  printf("Please input source1 filename:\n");
  gets(s1filename);
  /*�õ���һ���ļ����ļ���*/
  printf("Please input source2 filename:\n");
  gets(s2filename);
  /*�õ�ҪĿ���ļ����ļ���*/
	printf("Please input destination filename:\n");
	gets(dfilename);
	/*�����Ϣ�ϲ�ǰ���ļ�������*/
	if((s1fp=fopen(s1filename,"r"))==0)
	{
			printf("Can't open the file :%s\n",s1filename);
			exit(0);
	}
	if((s2fp=fopen(s2filename,"r"))==0)
	{
			printf("Can't open the file :%s\n",s2filename);
			exit(0);
	}
	if((dfp=fopen(dfilename,"w+"))==0)
	{
    	printf("Can't open or create the file :%s\n",dfilename);
    	exit(0);
  }
  /*�����Ϣ�ϲ�ǰ�ļ�������*/
  printf("\nThe text of the file %s before merging :\n",s1filename); 
	OutputFile(s1fp);
	printf("\nThe text of the file %s before merging :\n",s2filename);
  OutputFile(s2fp);
  fseek(s2fp,0L,SEEK_SET);
  fseek(s1fp,0L,SEEK_SET);
  /*��Ϣ�ϲ�*/
  MergeFile(s1fp,s2fp,dfp,&num);
  /*�����Ϣ�ϲ����ļ�������*/
  printf("\nThe text of the file %s after merging :\n",dfilename); 
  fseek(dfp,0L,SEEK_SET);
	OutputFile(dfp);
	/*����ܵ��ַ���*/
	printf("\nand the file %s has %d chars\n",dfilename,num);
  fclose(s1fp);
  fclose(s2fp);
  fclose(dfp);
  getch();
  //return 0;
}