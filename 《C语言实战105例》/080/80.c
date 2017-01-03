#include <process.h> 
#include <string.h> 
#include <stdio.h> 
#include <dos.h> 
#define BUFFERSIZE 128
int main() 
{ 
   char filename[BUFFERSIZE]; 
   struct fcb fctlblk; 
   clrscr();
   puts("*****************************************");
   puts("*     This program will get             *");
   puts("* the information of file control block *");
   puts("*****************************************");
   puts("Please input the drive and file name.");
   puts("Such as: c:filename.");
   while(1)
   {
	   /* get file name */  
	   gets(filename); 
	   if(filename[0] == '\0')
	     break;
	   /* put file name in fcb */ 
	   if (parsfnm(filename, &fctlblk, 1) == NULL) 
	   {
	      printf("Error in parsfm call\n"); 
	      return 0;
	   }
	   /*输出文件所在的磁盘*/
	   printf("\n >>The drive is:");
	   switch(fctlblk.fcb_drive)
	   {
	   	case 1:
	   	  printf("A.\n");break;
	   	case 2:
	   	  printf("B.\n");break;
	   	case 3:
	   	  printf("C.\n");break;
	    case 4:
	   	  printf("D.\n");break;
	    case 5:
	   	  printf("E.\n");break;
	   }
	   /*输出文件的名字*/
	   printf(" >>The filename is: %s\n",fctlblk.fcb_name);
	   /*输出文件的扩展名*/
	   printf(" >>The extention name is: %s\n\n",fctlblk.fcb_ext);
   }
   getch();
   return 1; 
} 