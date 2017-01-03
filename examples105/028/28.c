#include<stdio.h>
#define ROW 8
#define COLUMN 8
#define STEP ROW*COLUMN
/*ROW表示迷宫的行数，COLUMN表示迷宫的列数，STEP表示队列的容量*/
/*定义一个用来记录迷宫探路的队列*/
struct StepQueue
{
	int x,y;    
	int PreStep;
}StepQ[STEP],tmpStepQ[STEP];
/*定义一个结构体用来表示迷宫中的移动方向，一共有8种方向*/
struct MoveD
{
	/*x,y坐标增量，取值-1，0，1*/
	int x, y;  
}move[8];
/*迷宫探路函数*/
int PathMaze(int maze[ROW][COLUMN])  
{
	int i,j,k,v,front,rear,x,y,l;
	/*声明一个标记数组来记录一个是否到达过某个点，并进行初始化*/
	int mark[ROW][COLUMN];
	for(i=0;i<ROW;i++)
		for(j=0;j<COLUMN;j++)
			mark[i][j]=0;
	/*初始化入口点*/		
	StepQ[1].x=1;
	StepQ[1].y=1;
	StepQ[1].PreStep=0;
	front=1;
	rear=1;
	mark[1][1]=1;   
	while(front<=rear)
	{
		/*以(x,y)为出发点进行搜索*/
		x=StepQ[front].x;
		y=StepQ[front].y;
		/*搜索(x,y)的8个相邻(i,j)是否可以到达*/   
		for(v=0;v<8;v++)  
		{
			i=x+move[v].x;
			j=y+move[v].y;
			/*(i,j)为可以到达点，将起入队*/
			if((maze[i][j]==0)&&(mark[i][j]==0))
			{
				rear++;
				StepQ[rear].PreStep=front;
				StepQ[rear].x=i;
				StepQ[rear].y=j;
				mark[i][j]=1; 
			}
			/*如果到达出口，则输出路径*/
			if((i==ROW-2)&&(j==COLUMN-2))    
			{
				printf("\nThe Path in this maze is: \n\n");
				k=rear;
				l=0;
				/*k==0说明已经到达*/
				while(k!=0)
				{
					tmpStepQ[l++].x=StepQ[k].x;
					tmpStepQ[l++].y=StepQ[k].y;
					/*找前一点*/
					k=StepQ[k].PreStep;
				}
				/*输出路径*/
				while(l>0)
					printf("(%d,%d)>",tmpStepQ[--l].x,tmpStepQ[--l].y);
				printf("(%d,%d)",tmpStepQ[0].x,tmpStepQ[0].y);
				return(1);      
			}
		}
		/*从队列中弹出一个点，front指向新的出发点*/
		front++;   
	} 
  /*队空说明没有路径*/
	printf("There is no Path in the maze! \n");
	return(0); 
}
/*迷宫生成函数*/
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
	/*声明一个用来放迷宫的数组*/
	int maze[ROW][COLUMN];
	clrscr();
	/*初始化移动方向数组*/
	move[0].x=-1;move[0].y=-1;move[1].x=-1;move[1].y=0;
	move[2].x=-1;move[2].y=1;move[3].x=0;move[3].y=-1;
	move[4].x=0;move[4].y=1;move[5].x=1;move[5].y=-1;
	move[6].x=1;move[6].y=0;move[7].x=1;move[7].y=1;
	
	printf("*********************************\n");
	printf("|      Welcome to our maze      |\n");
	printf("*********************************\n");
	/*创建一个迷宫*/
	CreateMaze(maze);
	/*迷宫中探路*/
	PathMaze(maze);
	getch();
	return 0;
}