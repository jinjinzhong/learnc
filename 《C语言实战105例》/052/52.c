#include<stdio.h>
#include<ctype.h>
#include<dos.h>
#include<dir.h>
#include<stat.h>
#include<io.h>
#include<string.h>

int main()
{
	struct ffblk ffblock;
	struct date today;
	struct time now;
	FILE *fp;
	register long int dfv;
	char pat[128];
	int virus=0,vsize=0;
	clrscr();
	printf("*********************************\n");
	printf("| This is a virus test function |\n");
	printf("*********************************\n\n");
	printf("Testing virus.................\n\n");
	/*取得当前工作路径*/
	getcwd(pat,128);
	/*切换目录*/
	chdir(pat);
	/*找到文件COMMAND.COM*/
	dfv=findfirst("\\*.*",&ffblock,23);
	while(!dfv)
	{
		if(!strcmp(ffblock.ff_name,"COMMAND.COM"));
		vsize=ffblock.ff_fsize/100;
		dfv=findnext(&ffblock);
	}
	if(vsize!=0&&vsize!=478&&vsize!=232&&vsize!=253&&vsize!=2237&&159&&vsize!=252)
	{
		vsize=0;
		printf("This is virus in your computer\n");
		virus=1;
	}
	if((fp=fopen("record.txt","w"))==NULL)
	{
		printf("Can't open the file record.txt\n");
		exit(0);
	}
	/*取得日期时间*/
	getdate(&today);
	gettime(&now);
	/*记录病毒信息到文件 record.txt*/
	if(virus==1)
		fprintf(fp,"%d-%d-%d-%d:%0d",today.da_year,today.da_mon,today.da_day,now.ti_hour,now.ti_min);
	else
		printf("Don't find virus in your computer\n");
	fclose(fp);
	getch();
	return 0;
}