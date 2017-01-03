#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*加密子函数
这里采用加密函数是：
如果是数组，则不进行加密；
如果是字符，首先将a变成b,b变c,....依次类推，
然后再与加密字符异或*/
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
/*解密子函数：与加密的过程相反*/
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
/*输出文件内容*/
void OutputFile(FILE *fp)
{
	char ch;
	while((ch=fgetc(fp))!=EOF)
		putchar(ch);
}
int main()
{
		/*用户输入的要加密的文件名*/
		char sfilename[20];
		/*用户输入加密后保存的文件名*/
    char dfilename[20]; 
    /*用来保存密码字符*/
    char pwd;
    FILE *sfp,*dfp;
    clrscr();
    printf("\nPlease input filename to be encrypted:\n");
    /*得到要加密的文件名*/
    gets(sfilename);
    /*得到加密后你要的文件名*/
		printf("input filename to save the encrypted file:\n");
		gets(dfilename);
		/*得到加密字符*/
		printf("Please input your Password:\n");
		//scanf("%c",&pwd);
		pwd=getch();
		/*屏幕以*来表示输入的加密字符*/
		printf("*\n");
    /*以只读方式打开要加密的文件*/
		if((sfp=fopen(sfilename,"r"))==0)
		{
			printf("Can't open the file :%s\n",sfilename);
			exit(0);
		}
		/*输出要加密的文件*/
		printf("\nThe the text of file to be encrypted is:\n");
		OutputFile(sfp);
		/*建立加密后的文件*/
		if((dfp=fopen(dfilename,"w+"))==0)
		{
    	printf("Can't open or create the file :%s\n",dfilename);
    	//exit(0);
    }
		/*文件加密*/
		fseek(sfp,0L,SEEK_SET);
   	EncryptFile(sfp,dfp,pwd);
   	printf("\n\nEncrypted the file successfully!\n");
		/*输出加密后的文件*/
		printf("\nAfter encrypting the text of file is:\n");
		fseek(dfp,0L,SEEK_SET);
		OutputFile(dfp);
		fclose(sfp);
		fclose(dfp);
		getch();
		return 0;
}
