#include<stdio.h>
/*输出文件内容*/
void OutputFile(FILE *fp)
{
	char ch;
	while((ch=fgetc(fp))!=EOF)
		putchar(ch);
}
/*文件连接函数*/
void JoinFile(char *sfilename,char *dfilename)
{
	char ch;
	FILE *fp1,*fp2;
	/*进行输入重定向*/
	if((fp1=freopen(sfilename,"r",stdin))==0)
	{
		printf("Can't open the file :%s\n",sfilename);
		return;
	}
	/*进行输出重定向*/
	if((fp2=freopen(dfilename,"a",stdout))==0)
	{
		printf("Can't open or create the file :%s\n",dfilename);
		return;
	}
	/*进行文件的读写*/
	while((ch=getchar())!=EOF)
		putchar(ch);
	fclose(fp1);
	fclose(fp2);
	return;
}
int main()
{
	char sfilename[20];
	char dfilename[20];
	FILE *sfp,*dfp;
	clrscr();
	printf("**********************************************\n");
	printf("|  The program will join a file to another!  |\n");
	printf("|You can open the object file to verify this!|\n");
	printf("**********************************************\n");
	/*得到要被连接的文件名*/
  printf("\nPlease input source filename:\n");
  gets(sfilename);
  /*得到要连接到的文件的文件名*/
	printf("Please input destination filename:\n");
	gets(dfilename);
	/*输出连接前文件的内容*/
	if(((sfp=fopen(sfilename,"r"))==0)||((dfp=fopen(dfilename,"r"))==0))
		return 0;
	printf("\nThe text of the file %s before joining :\n",sfilename);
	OutputFile(sfp);
	printf("\nThe text of the file %s before joining :\n",dfilename);
  OutputFile(dfp);
  printf("\nPlease open the file %s to verify the text!\n",dfilename);
  getch();
  /*连接两个文件*/
	JoinFile(sfilename,dfilename);
	fclose(sfp);
  fclose(dfp);
	return 0;
}