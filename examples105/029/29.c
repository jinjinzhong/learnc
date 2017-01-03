#include <stdio.h>
#include <timeb.h>
/*返回随机数序列初值*/
double Initial()
{
    double init;
    struct timeb *tmb;
    while(1)
    {
			ftime(tmb);
			/*利用DOS系统的时钟产生随机数序列初值*/
			init=tmb->millitm*0.9876543*0.001;
			if(init>=0.001) 
				break;
    }
    return init;
}
/*返回一个(0,1)之间的随机数*/
double Random(void)
{
    static double rndm=-1.0;
    if(rndm==-1.0)
    	rndm=Initial();
    else 
    	rndm=3.80*rndm*(1.0-rndm);
    return rndm;
}
int main()
{
	double randnum;
	int i;
	clrscr();
	puts("*********************************************");
	puts("| This program can generate a random number |");
	puts("|          Press 'q' to quit                |");
	puts("|     Press any other key to generate       |");
	puts("*********************************************");
	while(1)
	{
		  if(getch()=='q')
		  	break;
			randnum = Random();
			printf ( "\n   >> the randnum is:%f\n",randnum );
	}
	return 0;
}
