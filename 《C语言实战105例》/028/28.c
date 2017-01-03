#include<stdio.h>
#define ROW 8
#define COLUMN 8
#define STEP ROW*COLUMN
/*ROW��ʾ�Թ���������COLUMN��ʾ�Թ���������STEP��ʾ���е�����*/
/*����һ��������¼�Թ�̽·�Ķ���*/
struct StepQueue
{
	int x,y;    
	int PreStep;
}StepQ[STEP],tmpStepQ[STEP];
/*����һ���ṹ��������ʾ�Թ��е��ƶ�����һ����8�ַ���*/
struct MoveD
{
	/*x,y����������ȡֵ-1��0��1*/
	int x, y;  
}move[8];
/*�Թ�̽·����*/
int PathMaze(int maze[ROW][COLUMN])  
{
	int i,j,k,v,front,rear,x,y,l;
	/*����һ�������������¼һ���Ƿ񵽴��ĳ���㣬�����г�ʼ��*/
	int mark[ROW][COLUMN];
	for(i=0;i<ROW;i++)
		for(j=0;j<COLUMN;j++)
			mark[i][j]=0;
	/*��ʼ����ڵ�*/		
	StepQ[1].x=1;
	StepQ[1].y=1;
	StepQ[1].PreStep=0;
	front=1;
	rear=1;
	mark[1][1]=1;   
	while(front<=rear)
	{
		/*��(x,y)Ϊ�������������*/
		x=StepQ[front].x;
		y=StepQ[front].y;
		/*����(x,y)��8������(i,j)�Ƿ���Ե���*/   
		for(v=0;v<8;v++)  
		{
			i=x+move[v].x;
			j=y+move[v].y;
			/*(i,j)Ϊ���Ե���㣬�������*/
			if((maze[i][j]==0)&&(mark[i][j]==0))
			{
				rear++;
				StepQ[rear].PreStep=front;
				StepQ[rear].x=i;
				StepQ[rear].y=j;
				mark[i][j]=1; 
			}
			/*���������ڣ������·��*/
			if((i==ROW-2)&&(j==COLUMN-2))    
			{
				printf("\nThe Path in this maze is: \n\n");
				k=rear;
				l=0;
				/*k==0˵���Ѿ�����*/
				while(k!=0)
				{
					tmpStepQ[l++].x=StepQ[k].x;
					tmpStepQ[l++].y=StepQ[k].y;
					/*��ǰһ��*/
					k=StepQ[k].PreStep;
				}
				/*���·��*/
				while(l>0)
					printf("(%d,%d)>",tmpStepQ[--l].x,tmpStepQ[--l].y);
				printf("(%d,%d)",tmpStepQ[0].x,tmpStepQ[0].y);
				return(1);      
			}
		}
		/*�Ӷ����е���һ���㣬frontָ���µĳ�����*/
		front++;   
	} 
  /*�ӿ�˵��û��·��*/
	printf("There is no Path in the maze! \n");
	return(0); 
}
/*�Թ����ɺ���*/
void CreateMaze(int maze[ROW][COLUMN])
{
	int i,j;
	for(i=0;i<COLUMN;i++)
	{
		maze[0][i]=1;
		maze[ROW-1][i]=1;
	}
	for(i=0;i<ROW;i++)
	{
		maze[i][0]=1;
		maze[i][COLUMN-1]=1;
	}
	maze[1][1]=0;maze[1][2]=1;maze[1][3]=0;maze[1][4]=1;maze[1][5]=1;maze[1][6]=0;
  maze[2][1]=1;maze[2][2]=0;maze[2][3]=0;maze[2][4]=1;maze[2][5]=1;maze[2][6]=0;
	maze[3][1]=0;maze[3][2]=1;maze[3][3]=1;maze[3][4]=0;maze[3][5]=0;maze[3][6]=1;
	maze[4][1]=1;maze[4][2]=0;maze[4][3]=0;maze[4][4]=1;maze[4][5]=1;maze[4][6]=0;
	maze[5][1]=1;maze[5][2]=1;maze[5][3]=0;maze[5][4]=0;maze[5][5]=1;maze[5][6]=1;
	maze[6][1]=0;maze[6][2]=1;maze[6][3]=1;maze[6][4]=1;maze[6][5]=0;maze[6][6]=0;
	for(i=0;i<ROW;i++)
	{
		printf("\n        ");
		for(j=0;j<COLUMN;j++)
			printf("%2d",maze[i][j]);
	}
}
int main()
{
	/*����һ���������Թ�������*/
	int maze[ROW][COLUMN];
	clrscr();
	/*��ʼ���ƶ���������*/
	move[0].x=-1;move[0].y=-1;move[1].x=-1;move[1].y=0;
	move[2].x=-1;move[2].y=1;move[3].x=0;move[3].y=-1;
	move[4].x=0;move[4].y=1;move[5].x=1;move[5].y=-1;
	move[6].x=1;move[6].y=0;move[7].x=1;move[7].y=1;
	
	printf("*********************************\n");
	printf("|      Welcome to our maze      |\n");
	printf("*********************************\n");
	/*����һ���Թ�*/
	CreateMaze(maze);
	/*�Թ���̽·*/
	PathMaze(maze);
	getch();
	return 0;
}