#include<dos.h> 
#include<bios.h> 
#include<stdio.h> 
#include<conio.h> 
#include<stdlib.h>
 
struct HSC 
{
	char track,head,sector;/*������ͷ���ȣ�*/
}; 
struct PartitionTable 
{
	char Flag; /* �����־ */ 
	HSC begin; /* ��ʼλ�� */ 
	char Type; /* �������� */ 
	HSC end;   /* ����λ�� */ 
	long id;   /* ��ʼ������������ */ 
	long size; /* ������С */ 
}; 
struct note /* ���ṹ */ 
{
	char boot1[366]; 
	PartitionTable PT[1]; 
	PartitionTable PT1[4]; /* ��ͨ�������� */
	PartitionTable PT2[4]; /* ��DOS�������� */ 
	char f[2]; 
}dosboot;
/*�������ú���*/ 
void new_pri_dos(); /* ����(����չ�����޸ĳ�)��DOS���� */ 
void hide_dos(char n); /* ֻ����һ����DOS����,��������� */
 
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
		case '1': /* ֻ������DOS���������еĵ�һ��,������DOS������������� */ 
			hide_dos(n); 
			break; 
		case '2': /* ֻ������DOS���������еĵڶ��� */ 
			hide_dos(n); 
			break; 
		case '3': /* ֻ������DOS���������ϵĵ����� */ 
			hide_dos(n); 
			break; 
		case '4': /* ֻ������DOS���������ϵĵ����� */ 
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
		if ((dosboot.PT2[i].Type!=0)&&(dosboot.PT2[i].Type!=5))/*������չ�����ͽ��÷�������*/ 
		{
			dosboot.PT2[i].Flag=0x00;
		} 
                if (dosboot.PT2[i].Type==5)/*����չ������ΪPRI�����������������ͽ�����һ��PRI����*/ 
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