#include<stdio.h>
#include<stdlib.h>
/*������������λ��*/
#define MAXARRAY 1000
int main()
{
	int fac[MAXARRAY],add[MAXARRAY];
	int top,n,i,j;
	char ch;
	clrscr();
	while(1)
	{
		/*����Ҫ���������*/
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
		/*��ʼ���������ͽ�λ����*/
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
			/*�����λ����add*/
			for(j=0;j<=top;j++)
			{
				fac[j]=fac[j]*i;
				if(j==0)
					add[j]=fac[j]/10;
				else
					add[j]=(fac[j]+add[j-1])/10;
			}
			/*����top��ֵ*/
			if(add[top]>=1)
				top++;
			/*����������fac*/
			for(j=0;j<=top;j++)
			{
				if(j==0)
					fac[j]=fac[j]%10;
				else
					fac[j]=(fac[j]+add[j-1])%10;
			}
		}
		/*����������fac*/
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
