#include <stdio.h>
#define MAX 100
void main()
{
	int i,ElecteeNum;
	/*��������һά����ֱ��������꼶��ѡƱ��*/
	int GradeA[MAX],GradeB[MAX],GradeC[MAX];
	/*����һά����ElecteeID�����ÿ����ѡ�ߵ���ݱ�ʾ*/
	int ElecteeID[MAX];
	/*���帡����һά��������Ÿ����꼶��ƽ��ѡƱ���*/
	float VoteAverage[MAX];
	while(1)
	{
		clrscr();
		/*�����ѡ�ߵ�����*/
		printf("Input the num of the electees in the election:");
		scanf("%d",&ElecteeNum);
		if( ElecteeNum>1&&ElecteeNum<MAX )
			break;
	}
	/*����ÿ���꼶��ÿ����ѡ�ߵ�Ʊ��*/
	printf("Please input a ElecteeID and the votes of three nations:\n");
	printf("    ElecteeID  GradeA  GradeB    GradeC\n");
	/*����ÿ����ѡ�ߵ�ƽ��Ʊ��*/
	for( i=0; i<ElecteeNum; i++ )
	{
		printf("No.%d>",i+1);
		scanf("%d%d%d%d",&ElecteeID[i],&GradeA[i],&GradeB[i],&GradeC[i]);
		VoteAverage[i] = (GradeA[i]+GradeB[i]+GradeC[i])/3;
	}
	puts("\ElecteeID    GradeA   GradeB   GradeC  VoteAverage");
	puts("-------------------------------------------------");
	for( i=0; i<ElecteeNum; i++ )
	{
		printf("%8d %8d %8d %8d %8.1f\n",ElecteeID[i],GradeA[i],GradeB[i],GradeC[i],VoteAverage[i]);
	}
	puts("-------------------------------------------------");
	getch();
}
