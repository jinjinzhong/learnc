#include<stdio.h>
#include<stdlib.h>
#define NUM 3
main( )
{
    FILE *fp1; /*�����ļ�ָ��*/
    char *temp;
    int i,j;
    struct rec{ /*����ṹ������*/
        char id[10];
        char name[15];
        char department[15];
    }record[NUM];     
    printf("***********************************************************\n");
    printf("** This program is to show the random file input & output**\n");
    printf("***********************************************************\n"); 
    if ((fp1=fopen("d:\\infile.txt","wb"))==NULL) /*�Զ�����ֻд��ʽ���ļ�*/
    {
	printf("cannot open file");/*��������*/
	exit(1);
    }
    for( i=0;i<NUM;i++)
    {
	printf("Please input id:");
	scanf("%s",record[i].id); /*�Ӽ�������*/
	printf("Please input name:");
	 scanf("%s",record[i].name);
	printf("Please input department:");
	 scanf("%s",record[i].department);
	fwrite(&record[i],sizeof(struct rec),1,fp1); /* �ɿ�д��*/
    }
    fclose(fp1); /*�ر�*/
    if((fp1=fopen("d:\\infile.txt","rb+"))==NULL)/*�Կɶ�д��ʽ���ļ�*/
    {
	printf("cannot open file"); /*��������*/
	exit(1);
    }
    printf("************************************\n");
    printf("%-10s%-15s%-15s\n","id","name","department");
    printf("************************************\n");
    for (i=0;i<NUM;i++)
    { /*��ʾȫ���ļ�����*/
	fread(&record[i],sizeof(struct rec),1,fp1);
	printf("%-10s%-15s%-15s\n",record[i].id,record[i].name,record[i].department);
    }
    /*���½����ļ��������д*/
    fseek(fp1,2*sizeof(struct rec),0); /* ��λ�ļ�ָ��ָ���������¼*/
    fwrite(&record[1],sizeof(struct rec),1,fp1);
    /* �ڵ�������¼��д��ڶ�����¼*/
    rewind(fp1); /*�ƶ��ļ�ָ�뵽�ļ�ͷ*/
    printf("************************************\n");
    printf("%-10s%-15s%-15s\n","id","name","department");
    printf("************************************\n");
    for (i=0;i<NUM;i++)
    { /*��������ļ�����*/
	fread(&record[i],sizeof(struct rec),1,fp1);
	printf("%-10s%-15s%-15s\n",record[i].id,record[i].name,record[i].department);
    }
    fclose(fp1); /*�ر��ļ�*/ 
    scanf("%d",i);
}