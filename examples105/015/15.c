#include<stdio.h>
void simpleDebug(int i,char ch,float fl,char a_char[],int a_int[],int size,int option)
{
    int j;
    switch(option)
    {
        case 1:/*������*/
            printf("The int value is %d\n",i);
            break;
        case 2:/*�ַ���*/
            printf("The char is %c\n",ch);
            break;
        case 3:/*������*/
            printf("The float value is %f\n",fl);
            break;
        case 4: /*�ַ�������*/
        {
            printf("The char array is\n");
            for(j=0;j<size;++j)
            	printf(" %c",a_char[j]);
            printf("\n");
            break;
        }
        case 5: /*��������*/
        {
            printf("The integer array is:\n");
            for(i=0;j<size;++j)
            	printf(" %d",a_int[j]);
            printf("\n");
            break;
        }
        default:
            printf("Option Error!\n");
            break;
    }
    printf(" Please press any key to continue:\n");
    getch();
}
void main()
{
   	int i,j,a_int[8];
    char ch,a_char[8];
    float fl;
    char *string="I love china";
    for(i=0;i<8;i++)
    {
        a_int[i]=i+1;
    }
    for(j=0;j<8;j++)
    {
        a_char[j]=(char)(j+65);
    }
    ch='x';
    fl=6.5;
    clrscr();
    simpleDebug(i,0,0,0,0,0,1); /*�������i��ֵ*/
    simpleDebug(0,ch,0,0,0,0,2);/*����ַ���ch��ֵ*/
    simpleDebug(0,0,fl,0,0,0,3);/*����ַ���ch��ֵ*/
    simpleDebug(0,0,0,a_char,0,8,4);/*����ַ�������a_char�и�Ԫ�ص�ֵ*/
    simpleDebug(0,0,0,string,0,13,4);/*����ַ���string��ֵ*/
    simpleDebug(0,0,0,0,a_int,8,3);/*�����������a_int�и�Ԫ�ص�ֵ*/
    simpleDebug(0,0,0,0,0,0,10);/*����*/
}
