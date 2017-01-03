#include<stdio.h>
void simpleDebug(int i,char ch,float fl,char a_char[],int a_int[],int size,int option)
{
    int j;
    switch(option)
    {
        case 1:/*整型数*/
            printf("The int value is %d\n",i);
            break;
        case 2:/*字符型*/
            printf("The char is %c\n",ch);
            break;
        case 3:/*浮点型*/
            printf("The float value is %f\n",fl);
            break;
        case 4: /*字符型数组*/
        {
            printf("The char array is\n");
            for(j=0;j<size;++j)
            	printf(" %c",a_char[j]);
            printf("\n");
            break;
        }
        case 5: /*整型数组*/
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
    simpleDebug(i,0,0,0,0,0,1); /*输出整型i的值*/
    simpleDebug(0,ch,0,0,0,0,2);/*输出字符型ch的值*/
    simpleDebug(0,0,fl,0,0,0,3);/*输出字符型ch的值*/
    simpleDebug(0,0,0,a_char,0,8,4);/*输出字符型数组a_char中各元素的值*/
    simpleDebug(0,0,0,string,0,13,4);/*输出字符串string的值*/
    simpleDebug(0,0,0,0,a_int,8,3);/*输出整形数组a_int中各元素的值*/
    simpleDebug(0,0,0,0,0,0,10);/*出错*/
}
