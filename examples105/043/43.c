#include <stdio.h>
/*����ÿ���ļ���������*/
#define LINEWIDTH   20
/*���������ļ�֮��ļ��*/
#define INTERVAL    5
/*���庯������ɴ�ָ�����ļ��ж���һ�ж���LINEWIDTH���ַ������*/
int OutputFile(FILE *fp)
{
	int num=0;
	char c;
	while((c=fgetc(fp))!='\n')
	{
		/*�ļ������Ƴ�ѭ��*/
		if(feof(fp))
			break;
		printf("%c",c);
		num++;
		/*���LINEWIDTH���ַ����Ƴ�ѭ��*/
		if(num>=LINEWIDTH)
			break;
	}
	/*���ض��벢������ַ���*/
	return num;
}
int main()
{
	FILE *fp1,*fp2;
	/*�����ļ���*/
	char filename1[128],filename2[128];
	/*�ֱ��¼�����ļ���ǰ�ж��벢������ַ���*/
	int linenum1,linenum2,i;
	clrscr();
	printf("Input file1's name:\n");
	scanf("%s",filename1);
	/*���ļ�1*/
	fp1=fopen(filename1,"r");
	if(fp1==NULL)
	{	
		printf("Can't open file %s.\n",filename1);
		return 0;
	}
	printf("Input file2's name:\n");
	scanf("%s",filename2);
	/*���ļ�2*/
	fp2=fopen(filename2,"r");
	if(fp2==NULL)
	{	
		printf("Can't open file %s.\n",filename2);
		fclose(fp1);
		return 0;
	}
	/*�����ļ���δ����ʱѭ��*/
	while(!feof(fp1)||!feof(fp2))
	{
		linenum1=0;
		linenum2=0;
		/*���ļ�δ����ʱ���ļ�*/
		if(!feof(fp1)) 
			linenum1=OutputFile(fp1);
		/*����ո�*/
		for(i=0;i<(LINEWIDTH-linenum1+INTERVAL);i++)
			printf(" ");
		if(!feof(fp2)) 
			linenum2=OutputFile(fp2);
		for(i=0;i<(LINEWIDTH-linenum2+5);i++)
			printf(" ");
		/*���ÿ�е��ַ���*/
		printf("%2d\n",linenum1+linenum2);
	}
	fclose(fp1);
	fclose(fp2);
	getch();
	return 0;
}
