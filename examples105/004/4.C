#include <stdio.h> 
#include <math.h>

void main()
{
	int x = 25, y = 25 , z = 30;
	float f = 25.095, h = 25.095;
	printf("*************************************\n");
	printf("** This is a logical calculator:   **\n");
	printf("*************************************\n");
	if ( x == y )
		printf("x == y\n");
	else printf("x != y\n");
	if ( x != z)
		printf("x != z\n");
	else printf("x == z\n");
	if ( x == f)
		printf("x == f\n");
	else printf("x != f\n");
	if ( f == h)
		printf("f == h\n");
	else printf("f != h\n");
	if ( f == 25.095)
		printf("f == 25.095\n"); 
		else printf("f != 25.095\n");
	if ( fabs (f - 25.095) <= 0.0001)
		printf("f == 25.095\n");

	else printf("f != 25.095\n");
	if ((x != y) && (f != h))
		printf("x != y and f != h\n");
	else if (( x != z) || (h != z))
		printf("x != z or h !=  z\n");
	scanf("%d",x);
} 
	