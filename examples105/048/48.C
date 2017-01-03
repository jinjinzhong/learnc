#include <dos.h>
#include <stdio.h>
#include <string.h>
void EncryptBat(char *filename)
{
	char *pointer,*data;
	FILE *fp;
	int length,i;
	fp=fopen(filename,"rb+");
	if (fp==NULL)
	{
		printf("open file %s error\n",filename); 
		return 0;
	}
	else
	{
		fseek(fp,2,SEEK_END);
		length=ftell(fp);
		data = ( char *)calloc((unsigned)length,sizeof( char ));
		if ( !data )
		{
			printf("runtime error!");
			return 0;
		}               
		rewind(fp);
		i=0;
		while(!feof(fp))
			data[i++]=fgetc(fp);
		while(pointer = strrchr(data,'\n'))
			strnset(pointer,0,1);
	}  
	printf("encrypt file successfully!\n");
	rewind(fp);
	fwrite(data,1,length,fp);
	fclose(fp);                          
}
int main()
{
	char filename[20];
	clrscr();
	printf("*******************************************\n");
	printf("| This program will encrypt the .bat file |\n");
	printf("*******************************************\n");
	printf("Please enter the filename to encrypt:\n");
	scanf("%s",filename);
	EncryptBat(filename);
	getch();
	return 0;
}