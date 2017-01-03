# include <stdio.h>
/*����һ����ÿ�ſ�ƽ���ɼ��ĺ���AverageCourse
	�����β�һ���Ƕ�ά���飬��������ѧ���ɼ���
	һ����ָ��������������������ÿ�ſε�ƽ���ɼ�*/
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
/*����һ������ƽ���ɼ��ĺ���AverageAll
	�����β�һ����ָ���������������,����һ���׵�ַ
	n��Ҫ����ĳɼ�����*/
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
/*����һ����ѯѧ���ɼ��ĺ���AStudentScore
	�����β�һ����ָ�������ָ�룬n��Ҫ�����ѧ����*/
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
	/* ����һ������aveCourse���洢ÿ�ſε�ƽ���ɼ���
		�������aveAll���洢�ܵ�ƽ���ɼ�*/
	float aveAll,aveCourse[4];
	/* ����һ������score���洢ÿ��ѧ��ÿ�ſεĳɼ���������ֵ*/
	float score[4][4] = {{67, 78, 45, 88}, {76, 54, 90, 69},  
	                     {99, 45, 88, 99}, {98, 69, 77, 87}};
	clrscr();
	/* ���ú���AverageAll��16��������ƽ���� */
	aveAll=AverageAll(&score[0][0],16); 
	printf("The average of all courses is:\n  %f\n\n",aveAll);   
	/* ���ú���AverageCourse��4�ſ͵�ƽ���� */
	AverageCourse(score,aveCourse);
	for(i=0;i<4;i++)
		printf("The average of %dth course is:\n %f\n",i,aveCourse[i]);
	/* ��������num��ѧ���ĳɼ� */
	printf("\nPlease input the num of student(0-3):\n");
	scanf("%d", &num);
	printf("The score of the %dth student is:\n",num);
	StudentScore(score,num); 
	getch();
	return 0;
}

