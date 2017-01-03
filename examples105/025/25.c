#include<stdio.h>
#include<stdlib.h>
#define PAGENUM 6 /*主存中允许的最大的页数*/
#define MAXPAGENUM 15 /* 一个程序包含的最大页数*/
/*定义栈的结构  即置换器*/
typedef struct stack
{
	int page[PAGENUM];
	int head;
}PAGER;
/*定义一个置换器*/
PAGER pager;
/*栈的初始化*/
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
/*栈中成员的移动,即移动页面的操作*/
void MovingPage(int Begin )
{
	int i;
	for(i = Begin; i < PAGENUM-1; i++)
	{
		pager.page[i]  = pager.page[i+1] ;
	}
}
/*出栈操作,即 交换出页面的操作 */
void PopPage(int p)
{
	MovingPage(p);
	pager.head = PAGENUM - 2;
}
/*入栈操作 ,即换进新页面的操作*/
void PushPage(int page)
{
	pager.head = PAGENUM-1;
	pager.page[pager.head] = page;
}
/*打印主存中的页面*/
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
/*处理页面的换进和换出*/
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



