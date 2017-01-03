#include<stdio.h>
/*����ļ�����*/
void OutputFile(FILE *fp)
{
	char ch;
	while((ch=fgetc(fp))!=EOF)
		putchar(ch);
}
/*�ļ����Ӻ���*/
void JoinFile(char *sfilename,char *dfilename)
{
	char ch;
	FILE *fp1,*fp2;
	/*���������ض���*/
	if((fp1=freopen(sfilename,"r",stdin))==0)
	{
		printf("Can't open the file :%s\n",sfilename);
		return;
	}
	/*��������ض���*/
	if((fp2=freopen(dfilename,"a",stdout))==0)
	{
		printf("Can't open or create the file :%s\n",dfilename);
		return;
	}
	/*�����ļ��Ķ�д*/
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
	/*�õ�Ҫ�����ӵ��ļ���*/
  printf("\nPlease input source filename:\n");
  gets(sfilename);
  /*�õ�Ҫ���ӵ����ļ����ļ���*/
	printf("Please input destination filename:\n");
	gets(dfilename);
	/*�������ǰ�ļ�������*/
	if(((sfp=fopen(sfilename,"r"))==0)||((dfp=fopen(dfilename,"r"))==0))
		return 0;
	printf("\nThe text of the file %s before joining :\n",sfilename);
	OutputFile(sfp);
	printf("\nThe text of the file %s before joining :\n",dfilename);
  OutputFile(dfp);
  printf("\nPlease open the file %s to verify the text!\n",dfilename);
  getch();
  /*���������ļ�*/
	JoinFile(sfilename,dfilename);
	fclose(sfp);
  fclose(dfp);
	return 0;
}