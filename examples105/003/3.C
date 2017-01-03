#include <stdio.h>

void main()
{
	int i,j,k;
	float f,h;
	i = 22;
	j = 8;
	f = 1000.25;
	h = 830.78;
	printf("*************************************\n");
	printf("** This is a arithmetic calculator:**\n");
	printf("*************************************\n");
	printf("i = %d,j = %d\n",i,j);
	printf("i+j=%d\n",i+j);
	printf("i-j=%d\n",i-j);
	printf("i*j=%d\n",i*j);
	printf("i/j=%d\n",i/j);
	printf("i%%j=%d\n",i%j);
	
	k = 4*i - j/4 + i*(i-j)/(5*j-3*10);
	printf("4*i - j/4 + i*(i-j)/(5*j-3*10)=%d\n",k);
	
	printf("f+h=%.2f\n",f+h);
	printf("f-h=%.2f\n",f-h);
	printf("f/j=%.2f\n",f/j);
	
	scanf("%d",f);
}