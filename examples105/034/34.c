#include <stdio.h>

void main()
{
	FILE *infile,*outfile,*otherfile;
	char input;
	char inputs[10];   
	int i=0;
	infile = fopen("d:\\infile.txt","r+");
	outfile = fopen("d:\\outfile.txt","a+");
	if ( !infile )
		printf("open infile failed....\n");
	if ( !outfile)
		printf("open outfile failed...\n");
	printf("*********************************************\n");
	printf("** This program is to show file operation! **\n");
	printf("** The input file is:                      **\n");
	printf("**                       d:\\infile.txt     **\n");
	printf("** The contents in this file is:           **\n");
	printf("\n");
	for(;;)
	{ 
		input = fgetc(infile);
		printf("%c",input);
	 	putc(input,outfile);
	 	i++;
	 	if(input == '\n' || input == EOF)
	 		break;
	 }
	 fclose(infile);
	 fclose(outfile); 
	 scanf("%d",i);	
}