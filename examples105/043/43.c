#include <stdio.h>
/*定义每个文件的输出宽度*/
#define LINEWIDTH   20
/*定义两个文件之间的间隔*/
#define INTERVAL    5
/*定义函数来完成从指定的文件中读出一行多至LINEWIDTH个字符并输出*/
int OutputFile(FILE *fp)
{
	int num=0;
	char c;
	while((c=fgetc(fp))!='\n')
	{
		/*文件结束推出循环*/
		if(feof(fp))
			break;
		printf("%c",c);
		num++;
		/*输出LINEWIDTH个字符则推出循环*/
		if(num>=LINEWIDTH)
			break;
	}
	/*返回读入并输出的字符数*/
	return num;
}
int main()
{
	FILE *fp1,*fp2;
	/*存贮文件名*/
	char filename1[128],filename2[128];
	/*分别记录两个文件当前行读入并输出的字符数*/
	int linenum1,linenum2,i;
	clrscr();
	printf("Input file1's name:\n");
	scanf("%s",filename1);
	/*打开文件1*/
	fp1=fopen(filename1,"r");
	if(fp1==NULL)
	{	
		printf("Can't open file %s.\n",filename1);
		return 0;
	}
	printf("Input file2's name:\n");
	scanf("%s",filename2);
	/*打开文件2*/
	fp2=fopen(filename2,"r");
	if(fp2==NULL)
	{	
		printf("Can't open file %s.\n",filename2);
		fclose(fp1);
		return 0;
	}
	/*在有文件还未结束时循环*/
	while(!feof(fp1)||!feof(fp2))
	{
		linenum1=0;
		linenum2=0;
		/*在文件未结束时读文件*/
		if(!feof(fp1)) 
			linenum1=OutputFile(fp1);
		/*输出空格*/
		for(i=0;i<(LINEWIDTH-linenum1+INTERVAL);i++)
			printf(" ");
		if(!feof(fp2)) 
			linenum2=OutputFile(fp2);
		for(i=0;i<(LINEWIDTH-linenum2+5);i++)
			printf(" ");
		/*输出每行的字符数*/
		printf("%2d\n",linenum1+linenum2);
	}
	fclose(fp1);
	fclose(fp2);
	getch();
	return 0;
}
