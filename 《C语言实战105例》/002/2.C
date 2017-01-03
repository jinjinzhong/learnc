#include <stdio.h>
int main()
{
	int i=5,j;
	clrscr();
	j=i++;
	printf("i=%d,j=%d\n",i,j);
	i=++j;
	printf("\ni=%d,j=%d\n",i,j);
	
	printf("\ni=%d\n",++i);
	printf("\ni=%d\n",--i);
	printf("\ni=%d\n",i++);
	printf("\ni=%d\n",i--);
	
	j=-i++;
	printf("\ni=%d,j=%d\n",i,j);
	j=-i--;
	printf("\ni=%d,j=%d\n",i,j);
	printf("\ni = %d,%d,%d\n",i,i--,i--);
	getchar();
	return 0;
}
