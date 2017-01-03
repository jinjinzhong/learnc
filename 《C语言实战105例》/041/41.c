/*
该程序实现统计一个或多个文件的行数、字数和字符数。
一个行由一个换行符限定;
一个字由空格分隔（包括空白符、制表符和换行符）;
字符是指文件中的所有字符;*/
#include <stdio.h>
/*定义全局变量，统计多有文件的字符数、字数和行数*/
int charcount,wordcount,linecount;
void CountLWC(char *filename)
{
	FILE *fp;
	char c;
	/*定义三个计数器，分别统计字符数、字数和行数*/
	int charnum,wordnum,linenum;
	/*初始化计数器*/
	charnum=0;
	wordnum=0;
	linenum=0;
	/* 以只读方式打开文件 */
	if((fp=fopen(filename,"r"))==NULL)	
	{
		printf("Can't open the file %s.\n",filename);
		return;
	}
	c=fgetc(fp);
	while(c!=EOF)
	{
			charnum++;
			if(c=='\n'||c==' '||c=='\t')
			{
				/*如果第一个字符是空格则不计字数*/
				if(charnum!=1)	
					wordnum++;
			}	
			if(c=='\n')
			{
				/*如果第一个字符是空格则不计行数*/
				if(charnum!=1)	
					linenum++;
			}
			c=fgetc(fp);
	}
	charcount+=charnum;
	wordcount+=wordnum;
	linecount+=linenum;
	printf("******The file %s*****\n",filename);
	printf(">>Lines =        %d\n",linenum);
	printf(">>Words =        %d\n",wordnum);
	printf(">>Chars =        %d\n",charnum);
	fclose(fp);	
}
void main(int argc, char **argv )
{
	int n=argc;
	if(argc<2)
		printf("Please input the command: 43 file1 file2 ... filen");
	/*初始化全局变量*/
	charcount=0;
	wordcount=0;
	linecount=0;
	/*依次统计每个文件的信息*/
	while(--n>0)
		CountLWC(*(++argv));
	/*输出所有文件的统计信息*/
	if(argc>2)
	{
		printf("\nThe information in all files is:\n");
		printf(">>Lines =         %d\n",linecount);
		printf(">>Words =         %d\n",wordcount);
		printf(">>Chars =    			%d\n",charcount);
	}
	getch();
}
