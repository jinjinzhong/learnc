# include <stdio.h>
/*定义一个求每门课平均成绩的函数AverageCourse
	它的形参一个是二维数组，用来传递学生成绩；
	一个是指针变量（数组名），存放每门课的平均成绩*/
void AverageCourse(float score[][4],float *avg)
{
	int i,j;
	float sum;
	for(i=0;i<4;i++)
	{
		sum=0;
		for(j=0;j<4;j++)
			sum+=score[j][i];
		avg[i]=sum/4;
	}
}
/*定义一个求总平均成绩的函数AverageAll
	它的形参一个是指针变量（数组名）,传递一个首地址
	n是要计算的成绩个数*/
float AverageAll(float *score, int n)
{
	int i=0;
	float sum = 0;
	while(i<n)
	{
		sum+=score[i];
		i++;
	}
	return sum/n;
}
/*定义一个查询学生成绩的函数AStudentScore
	它的形参一个是指向数组的指针，n是要计算的学生号*/
void StudentScore(float(*score)[4], int n)
{
	int i;
	for(i=0; i<4; i++)
		printf("%4.2f ", *(*(score+n)+i));
	printf("\n");
}
int main()
{
	int num,i;
	/* 定义一个数组aveCourse来存储每门课的平均成绩，
		定义变量aveAll来存储总的平均成绩*/
	float aveAll,aveCourse[4];
	/* 定义一个数组score来存储每个学生每门课的成绩，并赋初值*/
	float score[4][4] = {{67, 78, 45, 88}, {76, 54, 90, 69},  
	                     {99, 45, 88, 99}, {98, 69, 77, 87}};
	clrscr();
	/* 调用函数AverageAll求16个分数的平均分 */
	aveAll=AverageAll(&score[0][0],16); 
	printf("The average of all courses is:\n  %f\n\n",aveAll);   
	/* 调用函数AverageCourse求4门客的平均分 */
	AverageCourse(score,aveCourse);
	for(i=0;i<4;i++)
		printf("The average of %dth course is:\n %f\n",i,aveCourse[i]);
	/* 求出序号是num的学生的成绩 */
	printf("\nPlease input the num of student(0-3):\n");
	scanf("%d", &num);
	printf("The score of the %dth student is:\n",num);
	StudentScore(score,num); 
	getch();
	return 0;
}

