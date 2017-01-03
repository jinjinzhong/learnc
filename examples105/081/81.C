#include <conio.h> 
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
int main()
{
	union REGS regs;
	int found; 
	clrscr();
	/* initialize mouse */
	printf("Initializing Mouse...\n\n");
	regs.x.ax=0;
	int86(0x33,&regs,&regs);
	found=regs.x.ax; 
	if(found==0) /* can not find mouse */ 
	{ 
	printf("initialize mouse error!"); 
	exit(1); 
	} 
	printf("Finished initializing!\n\n");
	/* show mouse */
	printf("Showing Mouse...\n");
	regs.x.ax=1;
	int86(0x33,&regs,&regs);
	printf("you can use the mouse.....\n\n");
	/* hide mouse */
	printf("Press any key to hide the mouse.\n");
	getch();
	regs.x.ax=2;
	int86(0x33,&regs,&regs);
	printf("\nthe mouse is hided\n");
	getch();
	return 1;
}

