#include<stdio.h>
void main()
{
    int i=1,j=1; 
    /*iΪ����Ľ�����,j��һ��������*/                 
    clrscr();
    puts("***************************************************");
    puts("|        This program is to solve                 |");
    puts("|     Einstein's interesting math question,       |");
    puts("|     which is presented by Albert Einstein.      |");
    puts("| The Problem is: there is a long ladder,         |");
    puts("| if one step strides 2 stages, 1 stages left,    |");
    puts("| if one step strides 3 stages, 2 stages left,    |");
    puts("| if one step strides 5 stages, 4 stages left,    |");
    puts("| if one step strides 7 stages, 0 stages left,    |");
    puts("| the question is, how many stages the ladder has?|");
    puts("***************************************************");
    /*ȡǰ�Ǹ�������������*/
    while(j<11)
    {
    	/*����һ��ͬ��ʽ���б�*/
    	if((i%2==1)&&(i%3==2)&&(i%5==4)&&(i%6==5)&&(i%7==0))
    	{
    		printf("  The ladder may has %d stages.\n",i);
    		/*��������1*/
    		j++;
    	}
    	/*�ж���һ����*/
    	i++;
    }
    getch();
}
