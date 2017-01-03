#include<stdio.h>
#include<stdlib.h>
#define NUM 3
main( )
{
    FILE *fp1; /*定义文件指针*/
    char *temp;
    int i,j;
    struct rec{ /*定义结构体类型*/
        char id[10];
        char name[15];
        char department[15];
    }record[NUM];     
    printf("***********************************************************\n");
    printf("** This program is to show the random file input & output**\n");
    printf("***********************************************************\n"); 
    if ((fp1=fopen("d:\\infile.txt","wb"))==NULL) /*以二进制只写方式打开文件*/
    {
	printf("cannot open file");/*出错返回*/
	exit(1);
    }
    for( i=0;i<NUM;i++)
    {
	printf("Please input id:");
	scanf("%s",record[i].id); /*从键盘输入*/
	printf("Please input name:");
	 scanf("%s",record[i].name);
	printf("Please input department:");
	 scanf("%s",record[i].department);
	fwrite(&record[i],sizeof(struct rec),1,fp1); /* 成块写入*/
    }
    fclose(fp1); /*关闭*/
    if((fp1=fopen("d:\\infile.txt","rb+"))==NULL)/*以可读写方式打开文件*/
    {
	printf("cannot open file"); /*出错返回*/
	exit(1);
    }
    printf("************************************\n");
    printf("%-10s%-15s%-15s\n","id","name","department");
    printf("************************************\n");
    for (i=0;i<NUM;i++)
    { /*显示全部文件内容*/
	fread(&record[i],sizeof(struct rec),1,fp1);
	printf("%-10s%-15s%-15s\n",record[i].id,record[i].name,record[i].department);
    }
    /*以下进行文件的随机读写*/
    fseek(fp1,2*sizeof(struct rec),0); /* 定位文件指针指向第三条记录*/
    fwrite(&record[1],sizeof(struct rec),1,fp1);
    /* 在第三条记录处写入第二条记录*/
    rewind(fp1); /*移动文件指针到文件头*/
    printf("************************************\n");
    printf("%-10s%-15s%-15s\n","id","name","department");
    printf("************************************\n");
    for (i=0;i<NUM;i++)
    { /*重新输出文件内容*/
	fread(&record[i],sizeof(struct rec),1,fp1);
	printf("%-10s%-15s%-15s\n",record[i].id,record[i].name,record[i].department);
    }
    fclose(fp1); /*关闭文件*/ 
    scanf("%d",i);
}