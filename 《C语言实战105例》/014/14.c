#include<stdio.h>
int main()
{
	char cmd;
	float temperature;
	while(1)
	{
		printf("\n*****************************************\n");
		printf("\n|   Please select one of convertions:   |\n");
	  	printf("|    c:  Convert Celsius to Fahrenheit  |\n");
			printf("|    f:  Convert Fahrenheit to Celsius  |\n");
			printf("|    q:  Quit                           |\n");
		printf("\n*****************************************\n");
		scanf("%c",&cmd);
		switch (cmd)
		{
			case 'c':
			{
				printf("\n*****************************************\n");
				printf("\n|   Please input Celsius temperature:   |\n");
				scanf("%f",&temperature);
				printf("\n|  The Fahrenheit temperature is:%6.3f|\n",temperature*1.8+32);
				printf("\n*****************************************\n");
				break;
			}
			case 'f':
			{
				printf("\n*****************************************\n");
				printf("\n  Please input Fahrenheit temperature:  |\n");
				scanf("%f",&temperature);
				printf("\n  The Celsius temperature is : %6.3f  |\n",5*(temperature-32)/9);
				printf("\n*****************************************\n");
				break;
			}
			case 'q':
			{
				break;
			}
			default:
			{
				printf("Your Command Error!temperatureut Again\n");
			}
		}	
		getchar();
		if(cmd=='q')
			break;
		printf("\n   Please input any key to use again:   \n");
		getchar();
		clrscr();
	}
	return 0;
}
