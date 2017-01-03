#include <dos.h> 
int main () 
{
	int i,j,n;
	char dh,ch; 
	clrscr();
	/*选择驱动*/
	printf("The program will recover your fdisk\n\n");
	do
	{
		printf ("Plese select the drive(A/B):\n"); 
   	scanf("%c",&ch); 
  }while(ch!= 'a'&& ch !='b'&&ch !='A'&&ch !='B');
  /*选择软盘类型*/ 
  printf("\nPlese select the fdisk type:\n\n"); 
  printf("--  a : 360KBfdisk   --\n");
  printf("--  b : 720KBfdisk   --\n");
  printf("--  c : 1.2MBfdisk   --\n");
  printf("--  d : 1.44MBfdisk  --\n");
  while(1)
  {
   	scanf("%c",&dh);
   	/*输入正确推出循环*/
   	if(dh=='a'||dh=='b'||dh=='c'||dh=='d')
   	  break;	 
  }
  /*按选定的软盘类型进行处理*/ 
  switch(dh) 
  {
  	/*处理360KB软盘*/
    case 'a': 
    	n=3;
	    break; 
	  /*处理720KB软盘*/
    case 'b':  
    	n=4;
	    break; 
	  /*处理1.2MB软盘*/
    case 'c':  
    	n=8;
	    break; 
	  /*处理1.44MB软盘*/
    case 'd':  
    	n=10;
	    break; 
    } 
   for (i=1;i<n;i++) 
	 { 
		 j=i+n-1; 
		 absread(ch,1,j,0); 
		 abswrite(ch,1,i,0); 
	 } 
   printf ("Recover your fdisk successfully!\n");
   getch();
   return 0; 
} 
