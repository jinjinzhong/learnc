
/*企业发放的奖金根据利润提成，发放规则如下：
  利润(I)低于或等于10万元时，奖金可提10%；
  利润高于10万元，低于20万元时，低于10万元的部分按10%提成，高于10万元的部分，可可提成7.5%；
  20万到40万之间时，高于20万元的部分，可提成5%；
  40万到60万之间时高于40万元的部分，可提成3%；
  60万到100万之间时，高于60万元的部分，可提成1.5%，高于100万元时，超过100万元的部分按1%提成。
  从键盘输入当月利润I，求应发放奖金总数？*/
#include<stdio.h>
#include<stdlib.h>
int main()
{
	long int gain;
	int prize1,prize2,prize4,prize6,prize10,prize = 0;
	puts("*************************************");
	puts("*      The program will solve       *");
	puts("* the problem of prize distribution *");
	puts("*************************************");
	puts("please input the num of gain:");
	scanf("%ld",&gain);
	prize1=100000*0.1;
	prize2=prize1+100000*0.075;
	prize4=prize2+200000*0.05;
	prize6=prize4+200000*0.03;
	prize10=prize6+400000*0.015;
	if(gain<=100000)
	  prize=gain*0.1;
	else if(gain<=200000)
	       prize=prize1+(gain-100000)*0.075;
	     else if(gain<=400000)
		    prize=prize2+(gain-200000)*0.05;
		  else if(gain<=600000)
			 prize=prize4+(gain-400000)*0.03;
		       else if(gain<=1000000)
			      prize=prize6+(gain-600000)*0.015;
			    else
			      prize=prize10+(gain-1000000)*0.01;
	printf("The prize is :%d\n",prize);
	getch();
	return 0;
} 

