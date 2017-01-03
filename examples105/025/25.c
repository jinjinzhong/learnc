#include<stdio.h>
#include<stdlib.h>
#define PAGENUM 6 /*���������������ҳ��*/
#define MAXPAGENUM 15 /* һ��������������ҳ��*/
/*����ջ�Ľṹ  ���û���*/
typedef struct stack
{
	int page[PAGENUM];
	int head;
}PAGER;
/*����һ���û���*/
PAGER pager;
/*ջ�ĳ�ʼ��*/
void InitPager()
{
	int top = 0;
	int i,j,tmp;
	int r;
	randomize();
	r = random(MAXPAGENUM);
	pager.page[top++] = r;
	while(top < PAGENUM )
	{
	        randomize();
		r = random(MAXPAGENUM);
		for(j =0;j<top;j++)
		{
			if(r == pager.page[j])
			{
				break;
			}
			if(j == top-1)
				pager.page[top++] = r;
		}
	}
	pager.head = PAGENUM - 1;
}
/*ջ�г�Ա���ƶ�,���ƶ�ҳ��Ĳ���*/
void MovingPage(int Begin )
{
	int i;
	for(i = Begin; i < PAGENUM-1; i++)
	{
		pager.page[i]  = pager.page[i+1] ;
	}
}
/*��ջ����,�� ������ҳ��Ĳ��� */
void PopPage(int p)
{
	MovingPage(p);
	pager.head = PAGENUM - 2;
}
/*��ջ���� ,��������ҳ��Ĳ���*/
void PushPage(int page)
{
	pager.head = PAGENUM-1;
	pager.page[pager.head] = page;
}
/*��ӡ�����е�ҳ��*/
void printPager()
{
        int i;
	printf("The pages in the pager is:");
	for(i = 0; i< PAGENUM;i++)
	{
		printf(" %d ",pager.page[i]);
	}
	printf("\n");
}
/*����ҳ��Ļ����ͻ���*/
void PagingProcess()
{
	int rdm;
	int i;
	randomize();
	rdm = random(MAXPAGENUM);
	for(i = 0; i< PAGENUM; i++)
	{
		if(rdm == pager.page[i])
		{
			printPager();
			printf("The page [%d]  will be accessed\n",rdm);
			PopPage(i);
			PushPage(rdm);
			printPager();
			break;
		}
		if(i == PAGENUM-1)
		{
			printPager();
			printf("The page [0]  will be paged out\n");
			PopPage(0);
			printf("The page [%d]  will be paged in\n",rdm);
			PushPage(rdm);
			printPager();
		}
	}
	
}
int main()
{
	int i; 
	clrscr();
	for(i = 0; i<3; i++)
	{
		InitPager();
		printf("ROUND %d:\n\n",i+1);
		PagingProcess();
	}
	getch();
	return 0;
}



