#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*文件内容转移函数，功能是：
将sfp所指向的文件中size字节的数据转移到dfp所指向的文件中去*/
void FilePartition(FILE *sfp,FILE *dfp,int size)
{
	int s=size;
	char ch;
	while(s!=0)
	{
		ch=fgetc(sfp);
		if(ch==EOF)
			break;
		fputc(ch,dfp);
		s--;
	}
	fclose(dfp);
}
int main()
{
		/*用户输入的要分割的文件名*/
		char sfilename[20];
		/*用户输入分割后要保存到的文件名*/
    char dfilename[20]; 
    /*定义要分割的字节数*/
    char ch;
    int size;
    FILE *sfp,*dfp;
    clrscr();
    printf("Please input filename to be partitioned:\n");
    /*得到要分割的文件名*/
    gets(sfilename);
			/*以只读方式打开要分割的文件*/
		if((sfp=fopen(sfilename,"rb"))==0)
		{
			printf("Can't open the file :%s\n",sfilename);
			exit(0);
		}
		while(!feof(sfp))
		{
			/*取得下一个要文件名*/
			printf("input filename to save the partitioned file:\n");
			scanf("%s",dfilename);
			if((dfp=fopen(dfilename,"wb"))==0)
			{
    		printf("Can't open or create the file :%s\n",dfilename);
    		exit(0);
   	  }
   	  /*读入此次分割的字节数*/
   	  printf("Please input the size of partition:\n");
   	  scanf("%d",&size);
			/*依次读入指定字节数的文件内容，并存入到相应文件中*/
			FilePartition(sfp,dfp,size);
	}
	printf ( "Partition the file %s successfully!",sfilename);
	getch();
	return 0;
}
