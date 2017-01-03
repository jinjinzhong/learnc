#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*�����Ӻ���
������ü��ܺ����ǣ�
��������飬�򲻽��м��ܣ�
������ַ������Ƚ�a���b,b��c,....�������ƣ�
Ȼ����������ַ����*/
void EncryptFile(FILE *sfp,FILE *dfp,char pwd)
{
	char ch;
	if(sfp==0||dfp==0)
	{
		printf("ERROR!\n");
		return;
	}
	while((ch=fgetc(sfp))!=EOF)
	{
		if((ch>='a')&&(ch<='z'))
		{
			ch=(ch-'a'+1)%26+'a';
			ch=ch^pwd;
		}
		if((ch>='A')&&(ch<='Z'))
		{
			ch=(ch-'A'+1)%26+'A';
			ch=ch^pwd;
		}
		fputc(ch,dfp);
	}
}
/*�����Ӻ���������ܵĹ����෴*/
void DecryptFile(FILE *sfp,FILE *dfp,char pwd)
{
	char ch;
	while((ch=fgetc(sfp))!=EOF)
	{
		if((ch>='a')&&(ch<='z'))
		{
			ch=ch^pwd;
			ch=(ch-'a'+25)%26+'a';
		}
		if((ch>='A')&&(ch<='Z'))
		{
			ch=ch^pwd;
			ch=(ch-'A'+25)%26+'A';
		}
		fputc(ch,dfp);
	}
}
/*����ļ�����*/
void OutputFile(FILE *fp)
{
	char ch;
	while((ch=fgetc(fp))!=EOF)
		putchar(ch);
}
int main()
{
		/*�û������Ҫ���ܵ��ļ���*/
		char sfilename[20];
		/*�û�������ܺ󱣴���ļ���*/
    char dfilename[20]; 
    /*�������������ַ�*/
    char pwd;
    FILE *sfp,*dfp;
    clrscr();
    printf("\nPlease input filename to be encrypted:\n");
    /*�õ�Ҫ���ܵ��ļ���*/
    gets(sfilename);
    /*�õ����ܺ���Ҫ���ļ���*/
		printf("input filename to save the encrypted file:\n");
		gets(dfilename);
		/*�õ������ַ�*/
		printf("Please input your Password:\n");
		//scanf("%c",&pwd);
		pwd=getch();
		/*��Ļ��*����ʾ����ļ����ַ�*/
		printf("*\n");
    /*��ֻ����ʽ��Ҫ���ܵ��ļ�*/
		if((sfp=fopen(sfilename,"r"))==0)
		{
			printf("Can't open the file :%s\n",sfilename);
			exit(0);
		}
		/*���Ҫ���ܵ��ļ�*/
		printf("\nThe the text of file to be encrypted is:\n");
		OutputFile(sfp);
		/*�������ܺ���ļ�*/
		if((dfp=fopen(dfilename,"w+"))==0)
		{
    	printf("Can't open or create the file :%s\n",dfilename);
    	//exit(0);
    }
		/*�ļ�����*/
		fseek(sfp,0L,SEEK_SET);
   	EncryptFile(sfp,dfp,pwd);
   	printf("\n\nEncrypted the file successfully!\n");
		/*������ܺ���ļ�*/
		printf("\nAfter encrypting the text of file is:\n");
		fseek(dfp,0L,SEEK_SET);
		OutputFile(dfp);
		fclose(sfp);
		fclose(dfp);
		getch();
		return 0;
}
