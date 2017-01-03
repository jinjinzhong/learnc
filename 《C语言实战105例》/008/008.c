
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i = 0;/* i为计数器 */
	int n;
	int factorial = 1;/* 保存阶乘的结果 */
	puts("*************************************");
	puts("*      The program will compute     *");
	puts("*    the factotial of an integer    *");
	puts("*************************************");
	puts("please input the number n:");
	scanf("%d",&n);
	if(n < 0)/*判断输入的书是否大于或等于0*/
	{
	  	printf("please input an interger >= 0.\n");
	    return 0;
	}
	if(n==0)/* 0的阶乘是1 */
	{
	    printf("factorial of 0 is 1.\n");
	    return 0;
	}
	i = 1;
    while(i <= n)
    {
    	factorial = factorial * i;
    	i++;
    }
    printf("factorial of %d is:%d.\n",n,factorial);
    getch();
    return 0;
	
}

 
 
