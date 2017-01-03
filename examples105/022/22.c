#include<stdio.h>

#define NUM 10/* 定义物品总数*/
#define CONTENT 10 /*定义包的容量*/
void knapsack(int v[NUM],int w[NUM],int c,int m[NUM ][CONTENT])
{
    int n=NUM-1;
    int i,j;
    int jMax;
    if((w[n]-1)< c)
	jMax = w[n]-1;
    else
	jMax = c;
    /* 初始化m[n][j] */
    for(j = 0; j <= jMax; j++)
	m[n][j] = 0; 
    for(j = jMax +1; j <= c; j++)
	m[n][j] = v[n]; 
   /*使用非递归的算法来求解m[i][j] */
   for(i = n-1; i > 0; i--)
   {
   	 if((w[i]-1)< c)
	    jMax = w[i]-1;
        else
	    jMax = c;
        for(j = 0; j <= jMax; j++)
	    m[i][j] = m[i+1][j] ; 
        for(j = jMax +1; j <= c; j++)
        {
            if(m[i+1][j] >= (m[i+1][j-w[i]]+v[i]))
	        m[i][j] = m[i+1][j] ; 
	    else
		m[i][j] = 	m[i+1][j-w[i]]+v[i];
	}
   }
   if(c>w[0])
   {
	   if(m[1][c] >= (m[1][c-w[0]]+v[0]))
	   	 m[0][c]= m[1][c]; 
	   else
		m[0][c]= m[1][c-w[0]]+v[0]; 
   }
   else
   	m[0][c]= m[1][c];
	
}
/*寻找最优解*/
void traceback(int flag[NUM],int w[NUM],int m[NUM][CONTENT])
{
	int n = NUM -1;
	int i;
	int c = CONTENT;
	for(i = 0; i < n; i++)
	{
		if(m[i][c] == m[i+1][c])
			flag[i] = 0;
		else
		{
			flag[i] = 1;
			c-=w[i];
		}
	}
	if(m[n][c] >0)
	    flag[n] = 1;
	else
	    flag[n] = 0;
}
/* 打印最优解*/
void printResult(int flag[NUM],int w[NUM],int v[NUM],int m[NUM][CONTENT])
{
	int i;
	printf("the knapsack should contain:\n");
	printf(" num weight value \n");
	for(i = 0;i < NUM; i++)
	{
		if(flag[i] == 1)
	            printf("  %d    %d     %d\n",i,w[i],v[i]);
	}
	printf("the max value in the knapsack is: %d\n",m[0][CONTENT]);
}
int main()
{
	int value[NUM]={5,2,3,4,3,6,5,7,8,2};
	int weight[NUM]={2,1,3,2,4,3,5,6,2,2};
	int c = CONTENT;
	int maxvalue[NUM][CONTENT];
	int flag[NUM]={0,0,0,0,0,0,0,0,0,0};
	clrscr();
	printf("****************************************\n");
        printf("*      this program will solve         *\n");
        printf("*    the problem of 0-1knapsack        *\n");
        printf("****************************************\n");
	/*计算最优值*/
	knapsack(value,weight,c,maxvalue);
	/*构造最优解*/
	traceback(flag,weight,maxvalue);
	/*打印程序的结果*/
	printResult(flag,weight,value,maxvalue);
	getch();
	return 0;	
}
