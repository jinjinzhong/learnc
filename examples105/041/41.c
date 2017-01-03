/*
�ó���ʵ��ͳ��һ�������ļ����������������ַ�����
һ������һ�����з��޶�;
һ�����ɿո�ָ��������հ׷����Ʊ����ͻ��з���;
�ַ���ָ�ļ��е������ַ�;*/
#include <stdio.h>
/*����ȫ�ֱ�����ͳ�ƶ����ļ����ַ���������������*/
int charcount,wordcount,linecount;
void CountLWC(char *filename)
{
	FILE *fp;
	char c;
	/*�����������������ֱ�ͳ���ַ���������������*/
	int charnum,wordnum,linenum;
	/*��ʼ��������*/
	charnum=0;
	wordnum=0;
	linenum=0;
	/* ��ֻ����ʽ���ļ� */
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
				/*�����һ���ַ��ǿո��򲻼�����*/
				if(charnum!=1)	
					wordnum++;
			}	
			if(c=='\n')
			{
				/*�����һ���ַ��ǿո��򲻼�����*/
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
	/*��ʼ��ȫ�ֱ���*/
	charcount=0;
	wordcount=0;
	linecount=0;
	/*����ͳ��ÿ���ļ�����Ϣ*/
	while(--n>0)
		CountLWC(*(++argv));
	/*��������ļ���ͳ����Ϣ*/
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