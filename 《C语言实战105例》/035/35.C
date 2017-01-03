#include<stdio.h>
main( )
{
    FILE *fp;
    int i;
    struct rec{ /*定义结构体类型*/
        char id[10];
        char name[15];
        char department[15];
    }record;
    printf("***********************************************************\n");
    printf("** This program is to show the format file input & output**\n");
    printf("***********************************************************\n"); 
    if( (fp=fopen("d:\\infile.txt","w"))==NULL ) /*以文本只写方式打开文件*/
    { 
        printf("cannot open file");
        exit(1);
    }
    printf("please input data:\n");
    for( i=0;i<2;i++)
    {
    	printf("Please input id:\n");
        scanf("%s",record.id); /*从键盘输入*/
        printf("Please input name:\n");
         scanf("%s",record.name);
        printf("Please input department:\n");
         scanf("%s",record.department);
        fprintf(fp,"%s %s %s\n",record.id,record.name,record.department); /* 写入文件*/
    }
    fclose(fp); /*关闭文件*/
    if((fp=fopen("d:\\infile.txt","r"))==NULL)
    { /*以文本只读方式重新打开文件*/
        printf("cannot open file");
        exit(0);
    }
    printf("output from file:\n");
    /*从文件读入*/
    while (fscanf(fp,"%s %s %s\n",record.id,record.name,record.department)!=EOF)
    {
        printf("id:%s name:%s department:%s\n",record.id,record.name,record.department); /* 显示到屏幕*/
    }
    fclose(fp); /*关闭文件*/
    scanf("%d",i);
}