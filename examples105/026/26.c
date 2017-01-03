#include<stdio.h>
#include<stdlib.h>
/*定义数组的最大位数*/
#define MAXARRAY 1000
int main()
{
	int fac[MAXARRAY],add[MAXARRAY];
	int top,n,i,j;
	char ch;
	clrscr();
	while(1)
	{
		/*输入要计算的整数*/
		while(1)
		{
			printf("Please input the integer to compute:\n");
			scanf("%d",&n);
			if(n<0)
			{
				printf("Please input an integer greater -1\n");
				continue;
			}
			else
				break;
		}
		/*初始化结果数组和进位数组*/
		fac[0]=1;
		add[0]=0;
		for(j=1;j<=MAXARRAY-1;j++)
		{
			fac[j]=0;
			add[j]=0;
		}
		top=0;
		for(i=1;i<=n;i++)
		{
			/*计算进位数组add*/
			for(j=0;j<=top;j++)
			{
				fac[j]=fac[j]*i;
				if(j==0)
					add[j]=fac[j]/10;
				else
					add[j]=(fac[j]+add[j-1])/10;
			}
			/*更新top的值*/
			if(add[top]>=1)
				top++;
			/*计算结果数组fac*/
			for(j=0;j<=top;j++)
			{
				if(j==0)
					fac[j]=fac[j]%10;
				else
					fac[j]=(fac[j]+add[j-1])%10;
			}
		}
		/*输出结果数组fac*/
		printf("\n%d!=",n);
		for(j=top;j>=0;j--)
		{
			printf("%d",fac[j]);
		}
		printf("\n\n");
		printf("Please input 'c' to continue.\n");
		ch=getch();
		if(ch!='c')
			break;
	}
	return 0;
}
