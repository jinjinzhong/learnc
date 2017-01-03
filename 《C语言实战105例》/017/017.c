#include <stdlib.h>
#include <stdio.h>
 
#define MAX_VEXTEX_NUM 9 /* 图中顶点数 */
#define ARC_NUM 12       /* 图中弧数 */
#define MAX_QUEUEMEM (MAX_VEXTEX_NUM+1)

/* 定义描述图的顶点之间连接信息的数组 */
int GraphEdge[ARC_NUM * 2][2] = {{0,1},{1,0},{1,2},{2,1},{2,3},{3,2},{3,4},{4,3},{4,5},{5,4},{5,0},{0,5},{0,6},{6,0},{6,8},{8,6},{6,7},{7,6},{7,8},{8,7},{7,3},{3,7},{8,4},{4,8}};
/*定义数组visited用来标示一个顶点是否被访问过*/
int visited[MAX_VEXTEX_NUM]={0,0,0,0,0,0,0,0,0};
/*定义表结点，即每条弧对应的结点 */
typedef struct ArcNode{
  int adjvex;                 /* 该弧所指向的顶点的位置 */
  struct ArcNode * nextarc;   /* 指向下一条弧的指针 */
}ArcNode;

/* 定义头结点 */
typedef struct VNode{
  int data;                    /* 顶点信息 */
  struct ArcNode * firstarc;   /* 指向第一条依附该顶点的弧的指针 */
}VNode,AdjList[MAX_VEXTEX_NUM]; 

/* 定义图的结构 */
typedef struct {
	VNode vertices[MAX_VEXTEX_NUM];/* 定义表头数组 */
	int vexnum;      /* 定义图中顶点数 */
	int arcnum;      /* 定义图中弧数 */
}ALGraph;

/*建立一个使用邻接表存储的图*/
void CreateGraph(ALGraph * alGraph)
{
	int i,j;
	ArcNode * newnode;
	ArcNode * vexNode;
	alGraph->vexnum = MAX_VEXTEX_NUM;
	alGraph->arcnum = ARC_NUM;
	/* 初始化表头 */
	for(i=0;i<MAX_VEXTEX_NUM;i++)
	{
		alGraph->vertices[i].data = i;
		alGraph->vertices[i].firstarc = NULL;	
	}
	for(j=0;j<2*ARC_NUM;j++)
	{
		i = GraphEdge[j][0];
		if(alGraph->vertices[i].firstarc==NULL)
		{
		  newnode = ( ArcNode * ) malloc (sizeof(ArcNode));
		  newnode->adjvex = GraphEdge[j][1];
		  newnode->nextarc = NULL;
		  alGraph->vertices[i].firstarc = newnode;
		}
		else
		{
		  vexNode = alGraph->vertices[i].firstarc;
		  while(vexNode->nextarc != NULL)
		  {
			vexNode = vexNode->nextarc;
		  }
		  newnode = ( ArcNode * ) malloc (sizeof(ArcNode));
		  newnode->adjvex = GraphEdge[j][1];
		  newnode->nextarc = NULL;
		  vexNode->nextarc = newnode;
		}
	}
}
/* 打印这个图 */
void OutputGraph(ALGraph * alGraph)
{
	int i;
	ArcNode * vexNode;
	printf("The graph dedicated by adjacency list is:\n");
	for(i=0;i<MAX_VEXTEX_NUM;i++)
	{
		printf("the header is: [%d]  -> ",alGraph->vertices[i].data);
		vexNode = alGraph->vertices[i].firstarc;
		while(vexNode != NULL)
		{
		  printf("[%d] -> ",vexNode->adjvex);
		  vexNode=vexNode->nextarc;
		}
		printf("[END]\n");
	}
}
/*递归实现DFS*/
void DFS(ALGraph * alGraph,int v)
{
	int w;
	ArcNode * vexNode;
	visited[v] = 1;
	printf("[%d] -> ",v);
	vexNode = alGraph->vertices[v].firstarc;
	while(vexNode != NULL)
	{
		w = vexNode->adjvex;
		if(visited[w]==0)
		  DFS(alGraph,w);
		vexNode = vexNode->nextarc;
	}
}
/* 图的深度优先遍历 */
void DFSTraverse(ALGraph * alGraph)
{
	int i;
	/*访问标志数组初始化*/
	for(i=0;i<MAX_VEXTEX_NUM;i++)
	{
		visited[i] = 0;
	}
	printf("\n");
	puts("********************************************");
	puts("*  the function DFSTraverse will traverse  *");
	puts("*     the graphby Depth First Search       *");
	puts("********************************************");
	puts("the result of DFS is:");
	for(i=0;i<MAX_VEXTEX_NUM;i++)
	{
		if(visited[i] == 0)
		  DFS(alGraph,i);
	}
	printf("[end]\n");
}
/*为了实现广度优先遍历，需要借助一个队列 */
typedef struct{
  int queuemem[MAX_QUEUEMEM];
  int header;
  int rear;
}QUEUE;
void InitQueue(QUEUE *queue)
{
	queue->header = 0;
	queue->rear = 0;
}
void EnQueue(QUEUE *queue,int v)
{
	queue->queuemem[queue->rear] = v;
	queue->rear++;
}
int DelQueue(QUEUE *queue)
{
    return queue->queuemem[queue->header++];
}
int EmptyQueue(QUEUE *queue)
{
   if(queue->header == queue->rear)
     return 1;
   return 0;
}
/* 广度优先遍历 */
void BFSTraverse(ALGraph * alGraph)
{
	int i;
	int w;
	ArcNode * vexNode;
	QUEUE queue;
	InitQueue(&queue);
	/*访问标志数组初始化*/
	for(i=0;i<MAX_VEXTEX_NUM;i++)
	{
		visited[i] = 0;
	}
	printf("\n");
	puts("********************************************");
	puts("*  the function BFSTraverse will traverse  *");
	puts("*     the graph by Breadth First Search    *");
	puts("********************************************");
	puts("the result of BFS is:");
	for(i=0;i<MAX_VEXTEX_NUM;i++)
	{
		if(visited[i] == 0)
		{
			visited[i] = 1;
	        printf("[%d] -> ",i);
	        EnQueue(&queue,i);
	        while(!EmptyQueue(&queue))
	        {
	          w = DelQueue(&queue);
	          vexNode = alGraph->vertices[w].firstarc;
	          while(vexNode != NULL)
	          {
		        w = vexNode->adjvex;
		        if(visited[w]==0)
		        {
		          visited[w] = 1;
	              printf("[%d] -> ",w);
		          EnQueue(&queue,w);
		        }
		        vexNode = vexNode->nextarc;
	          }
	        }
		}
	}
	printf("[end]\n");
	
}
int main()
{
	/*定义图结点*/
    ALGraph alGraph;
    
    clrscr();
    /*建立图的邻接表*/
    CreateGraph(&alGraph);
    /*输出图的邻接表*/
    OutputGraph(&alGraph);
    /*深度优先遍历*/
    DFSTraverse(&alGraph);
    /*广度优先遍历*/
    BFSTraverse(&alGraph);
    getch();
    return 0;
}