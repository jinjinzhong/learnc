#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE * sourcefile;
	FILE * keyfile;
	FILE * destfile;
	char ch,keych;
	int i;
	puts("****************************************");
	puts("* The file will encrypt the source.txt *");
	puts("****************************************");
	
	if(!(sourcefile = fopen("source.txt","r")))
 	{
  		printf("Can not open the source file\n");
  		exit(-1);
 	}
	if(!(destfile = fopen("destfile.txt","w+")))
 	{
  		printf("Can not open the destination  file\n");
  		exit(-1);
 	}
	if(!(keyfile= fopen("keyfile.txt","w+")))
 	{
  		printf("Can not open the keyfile  file\n");
  		exit(-1);
 	}
	printf("\n.....Encrypting....\n");
	i = 0;
	while(!feof(sourcefile))
 	{
 		randomize();
		keych = random(112 - i) +16;
		ch = fgetc(sourcefile);
  		ch = ch ^ keych;
  		fputc(ch,destfile);
		fputc(keych,keyfile);
		i = ( ++i)%16;
 	}
	printf("Encrypted the souce.txt successfully!\n");
	fclose(sourcefile);
	fclose(keyfile);
	fclose(destfile);
	getch();
	return 1;
}

