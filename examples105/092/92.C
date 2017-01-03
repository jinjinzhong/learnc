#include <stdio.h>
#include <stdlib.h>
#include <time.h>
  

/*生成每个骰子的点数*/
int GenPoint(int sidenum)
{
	return (rand()%sidenum + 1);
}
int SumDicepoint(int dicenum,int sidenum)
{
	int i;
	int sum = 0;
	for(i = 0;i<dicenum;i++)
     sum +=	GenPoint(sidenum);
  return sum;
}
int PlayGame()
{
	int dicenum,sum,sidenum;
	do
  {
  	printf("input the type of dice:\n");
    scanf("%d",&sidenum);
    if(sidenum == 0)
      return 0;
  }while(!((sidenum == 4)||(sidenum == 6)||(sidenum == 8)||(sidenum == 12)||(sidenum == 20)));
 
  puts("input the number of dices:");
  scanf("%d",&dicenum);
  sum = SumDicepoint(dicenum,sidenum);
  clrscr();
  printf("The result of the game:\n");
  printf(">>the number of the dice sides:%d\n",sidenum);
  printf(">>the number of the dices :%d\n",dicenum);
  printf(">>the number of all points:%d\n",sum);
  printf("press any key to continue....\n");
  getch();
  return 1;
}
int main()
{
	srand((unsigned int)time(0));
	while(1)
	{
		clrscr();
		puts("*******************************************");
		puts("*  Welcome to the Game of Dropping dice   *");
		puts("*    You can choose the type of dice:     *");
		puts("*     4: 4 sides on a dice                *");
		puts("*     6: 6 sides on a dice                *");
		puts("*     8: 8 sides on a dice                *");
		puts("*     12: 12 sides on a dice              *");
		puts("*     20: 20 sides on a dice              *");
		puts("*     0: quit the game                    *");
	  puts("*******************************************");
	  if(PlayGame() == 0)
	    return 0;
	  
  }
  return 0;
}
