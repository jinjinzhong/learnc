#include <stdio.h>
#define MAX 100
void main()
{
	int i,ElecteeNum;
	/*定义三个一维数组分别存放三个年级的选票数*/
	int GradeA[MAX],GradeB[MAX],GradeC[MAX];
	/*定义一维数组ElecteeID来存放每个候选者的身份标示*/
	int ElecteeID[MAX];
	/*定义浮点型一维数组来存放各个年级的平均选票结果*/
	float VoteAverage[MAX];
	while(1)
	{
		clrscr();
		/*输入候选者的人数*/
		printf("Input the num of the electees in the election:");
		scanf("%d",&ElecteeNum);
		if( ElecteeNum>1&&ElecteeNum<MAX )
			break;
	}
	/*输入每个年级的每个候选者的票数*/
	printf("Please input a ElecteeID and the votes of three nations:\n");
	printf("    ElecteeID  GradeA  GradeB    GradeC\n");
	/*计算每个候选者的平均票数*/
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