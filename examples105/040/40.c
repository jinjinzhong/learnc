#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*输出文件内容*/
void OutputFile(FILE *fp)
{
	char ch;
	while((ch=fgetc(fp))!=EOF)
		putchar(ch);
}
/*文件信息合并函数*/
void MergeFile(FILE *s1fp,FILE *s2fp,FILE *dfp,int *num)
{
	char ch1,ch2;
	/*初始化ch1和ch2为文件的首字符*/
	ch1=fgetc(s1fp);
  ch2=fgetc(s2fp);
  /*从文件中读取字符，直到有一个文件结束*/
 	while((ch1!=EOF)&&(ch2!=EOF))
 	/*进行字符的比较*/
  if(ch1<=ch2)
  {
  		fputc(ch1,dfp);
  		/*字符数增加1*/
  		*num=*num+1;
  		ch1=fgetc(s1fp);
  }
  else
  {
  		fputc(ch2,dfp);
  		/*字符数增加1*/
  		*num=*num+1;
  		ch2=fgetc(s2fp);
  }
  /*如果文件s1fp结束，则将文件s2fp的剩余内容写入到文件dfp*/
  if(ch1==EOF)
  	while((ch2=fgetc(s2fp))!=EOF)
  	{
  		fputc(ch2,dfp);
  		/*字符数增加1*/
  		*num=*num+1;
  	}
  /*如果文件s2fp结束，则将文件s1fp的剩余内容写入到文件dfp*/
  else
 		while((ch1=fgetc(s1fp))!=EOF)
 		{
  		fputc(ch1,dfp);
  		/*字符数增加1*/
  		*num=*num+1;
  	}
}

void main()
{
	char s1filename[20],s2filename[20],dfilename[20];
	FILE *s1fp,*s2fp,*dfp;
	int num=0;
	clrscr();
	/*得到第一个文件的文件名*/
  printf("Please input source1 filename:\n");
  gets(s1filename);
  /*得到另一个文件的文件名*/
  printf("Please input source2 filename:\n");
  gets(s2filename);
  /*得到要目标文件的文件名*/
	printf("Please input destination filename:\n");
	gets(dfilename);
	/*输出信息合并前的文件的内容*/
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
  /*输出信息合并前文件的内容*/
  printf("\nThe text of the file %s before merging :\n",s1filename); 
	OutputFile(s1fp);
	printf("\nThe text of the file %s before merging :\n",s2filename);
  OutputFile(s2fp);
  fseek(s2fp,0L,SEEK_SET);
  fseek(s1fp,0L,SEEK_SET);
  /*信息合并*/
  MergeFile(s1fp,s2fp,dfp,&num);
  /*输出信息合并后文件的内容*/
  printf("\nThe text of the file %s after merging :\n",dfilename); 
  fseek(dfp,0L,SEEK_SET);
	OutputFile(dfp);
	/*输出总的字符数*/
	printf("\nand the file %s has %d chars\n",dfilename,num);
  fclose(s1fp);
  fclose(s2fp);
  fclose(dfp);
  getch();
  //return 0;
}