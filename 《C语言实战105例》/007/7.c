#include<stdio.h>
#include<conio.h> 
#include<time.h> 
int main() 
{
	/*(x,y)��ʾ��������Ļ�ϵĳ�ʼλ��,
	depth��ʾ������غ󷴵��ĸ߶�,
	times��������ʱ����ӳ�,
	m���������˶��ķ���m=-1˵���������˶���m=1˵���������˶�*/
	int x=15,y=4,depth=20,times=20,m=1,i,j;
	for(;depth!=0;) 
	{
		m=-m;
		if(m==1)
			depth--; 
		for(i=1;i<=depth;i++) 
		{
			printf("*****************************\n");
			printf("|  The program will show :  |\n"); 
			printf("|    the Free Falling       |\n"); 
			printf("*****************************\n");
			/*��������ͼ��*/
			gotoxy(x,y);
			printf("***\n");
			gotoxy(x,y+1); 
			printf("|*|\n"); 
			gotoxy(x,y+2);
			printf("***");
			/*���Ʋ�ͬ���ӳ���ʾ��ʱ���С*/
			for(j=1;j<=times;j++) 
					delay(10);  
			clrscr(); 
			if(m==-1)
			{
				/*���������˶�*/
				y++;  
				/*��ʱԽ��ԽС��˵���ٶ�Խ��Խ��*/
				times--;
			}
			else
			{
				/*���������˶�*/
				y--;
				/*��ʱԽ��Խ��˵���ٶ�Խ��Խ����˵����*/
				times++; 
			}    
		} 
	} 
	getch();
	return 0;
} 