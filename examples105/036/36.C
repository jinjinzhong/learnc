#include<stdio.h>
main( )
{
    FILE *fp;
    int i;
    struct rec{ /*����ṹ������*/
        char id[10];
        char name[15];
        char department[15];
    }record;
    printf("***********************************************************\n");
    printf("** This program is to show the block file input & output**\n");
    printf("***********************************************************\n"); 
    if( (fp=fopen("d:\\infile.txt","w"))==NULL ) /*���ı�ֻд��ʽ���ļ�*/
    { 
        printf("cannot open file");
        exit(1);
    }
    printf("please input data:\n");
    for( i=0;i<2;i++)
    {
    	printf("Please input id:\n");
        scanf("%s",record.id); /*�Ӽ�������*/
        printf("Please input name:\n");
         scanf("%s",record.name);
        printf("Please input department:\n");
         scanf("%s",record.department);
         fwrite(&record,sizeof(record),1,fp); /* �ɿ�д���ļ�*/
        /*fprintf(fp,"%s %s %s\n",record.id,record.name,record.department); /* д���ļ�*/
    }
    fclose(fp); /*�ر��ļ�*/
    if((fp=fopen("d:\\infile.txt","r"))==NULL)
    { /*���ı�ֻ����ʽ���´��ļ�*/
        printf("cannot open file");
        exit(0);
    }
    printf("output from file:\n");
    for (i=0;i<2;i++)
    {
    	fread(&record,sizeof(record),1,fp); /* ���ļ��ɿ��*/
    	printf("id:%s name:%s department:%s\n",record.id,record.name,record.department); /* ��ʾ����Ļ*/
    }
    /*���ļ�����*/
   /* while (fscanf(fp,"%s %s %s\n",record.id,record.name,record.department)!=EOF)
    {
        printf("id:%s name:%s department:%s\n",record.id,record.name,record.department); /* ��ʾ����Ļ*/
   /* }*/
    fclose(fp); /*�ر��ļ�*/
    scanf("%d",i);
}