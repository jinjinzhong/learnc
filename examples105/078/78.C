#include<dos.h> 
#include<bios.h> 
#include<stdio.h> 
#include<conio.h> 
#include<stdlib.h>
 
struct HSC 
{
	char track,head,sector;/*（柱、头、扇）*/
}; 
struct PartitionTable 
{
	char Flag; /* 激活标志 */ 
	HSC begin; /* 开始位置 */ 
	char Type; /* 分区类型 */ 
	HSC end;   /* 结束位置 */ 
	long id;   /* 开始扇区的相对序号 */ 
	long size; /* 分区大小 */ 
}; 
struct note /* 结点结构 */ 
{
	char boot1[366]; 
	PartitionTable PT[1]; 
	PartitionTable PT1[4]; /* 普通分区表项 */
	PartitionTable PT2[4]; /* 主DOS分区表项 */ 
	char f[2]; 
}dosboot;
/*分区所用函数*/ 
void new_pri_dos(); /* 建立(将扩展分区修改成)主DOS分区 */ 
void hide_dos(char n); /* 只保留一个主DOS分区,其余均隐含 */
 
void main(int argc,char *argv[]) 
{ 
	char n; 
	if (argc!=2) 
	{
		printf("Bad connamd !"); 
		return 0; 
	}                       
	printf("**********************************************\n");
	printf("** This program is a disk partition tool.   **\n");
	printf("** The usage is:                            **\n");
	printf("** c : new a primary dos partition.         **\n");
	printf("** 1 : left only the first pridos partition **\n");
	printf("** 2 : left only the second pridos partition**\n");
	printf("** 3 : left only the third pridos partition **\n");
	printf("** 4 : left only the forth pridos partition **\n");
	printf("**********************************************\n");
	printf("Please input your choose:");
	scanf("%c",n); 
	switch(n){ 
		case 'c': 
			new_pri_dos(); 
			break; 
		case '1': /* 只保留主DOS分区表项中的第一项,其余主DOS分区表项均隐含 */ 
			hide_dos(n); 
			break; 
		case '2': /* 只保留主DOS分区表项中的第二项 */ 
			hide_dos(n); 
			break; 
		case '3': /* 只保留主DOS分区表项上的第三项 */ 
			hide_dos(n); 
			break; 
		case '4': /* 只保留主DOS分区表项上的第四项 */ 
			hide_dos(n); 
			break; 
		default: 
			return 0; 
	} 
	return 0; 
} 
void new_pri_dos() 
{
	int i; 
	biosdisk(2,0x80,0,0,1,1,&dosboot); 
	for (i=0;i<4;i++) 
	{
		if ((dosboot.PT2[i].Type!=0)&&(dosboot.PT2[i].Type!=5))/*不是扩展分区就将该分区隐藏*/ 
		{
			dosboot.PT2[i].Flag=0x00;
		} 
                if (dosboot.PT2[i].Type==5)/*将扩展分区变为PRI分区，并激活这样就建立了一个PRI分区*/ 
                {
                	dosboot.PT2[i].Type=6; 
                        dosboot.PT2[i].Flag=0x80;
                } 
         } 
         biosdisk(3,0x80,0,0,1,1,&dosboot); 
         return; 
} 
void hide_dos(char n) 
{
	int i,m; 
	m=n-49; 
	biosdisk(2,0x80,0,0,1,1,&dosboot); 
	if (dosboot.PT1[m].Type!=0) 
	{ 
		for (i=0;i<4;i++) 
		{
			if (dosboot.PT1[i].Type!=0) 
                        {
                        	dosboot.PT2[i]=dosboot.PT[0];
                        }
                } 
                dosboot.PT2[m]=dosboot.PT1[m]; 
                dosboot.PT2[m].Flag=0x80; 
         } 
         biosdisk(3,0x80,0,0,1,1,&dosboot); 
         return; 
} 