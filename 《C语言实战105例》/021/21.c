
#include<stdio.h>
int main()
{
  int i,j,count;
  clrscr();
  puts("***********************************************");
  puts("*         this program will solve             *");
  puts("*       the problem about colorful boll       *");
  puts("***********************************************");
  puts("The the result is:\n");
  printf(" RED BALL WHITE BALL BLACK BALL\n");
  count = 1;
  for(i=0;i<=3;i++)       /*i是红球个数，作为外层循环变量*/
      for(j=0;j<=3;j++)   /*j是白球个数，作为内层循环变量*/
          if((8-i-j)<=6) 
  printf("    %d         %d         %d\n",count++,i,j,8-i-j);
  getch();\
  return 0;
}