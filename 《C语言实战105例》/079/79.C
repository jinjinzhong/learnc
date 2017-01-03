  #include   <stdio.h>     
  #include   <conio.h>     
  #include   <dos.h>     
    
  #define   VIDEO   0x10     
    
  void   movetoxy(int   x,   int   y)     
  {     
        union   REGS   regs;     
    
        regs.h.ah   =   2;     /*   set   cursor   postion   */     
        regs.h.dh   =   y;     
        regs.h.dl   =   x;     
        regs.h.bh   =   0;     /*   video   page   0   */     
        int86(VIDEO,   &regs,   &regs);     
  }     
    
  int   main(void)     
  {     
	int i;
	clrscr();
	printf("*******************************************\n");
	printf("** This is a simple dos interupt program **\n");
	printf("**                                       **\n");
	printf("*******************************************\n");
        movetoxy(10, 10);     
	printf("This is a simple dos interupt program!\n");
	scanf("%d",i);
	return   0;
  }     
