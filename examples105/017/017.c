#include <stdlib.h>
#include <stdio.h>
 
#define MAX_VEXTEX_NUM 9 /* ͼ�ж����� */
#define ARC_NUM 12       /* ͼ�л��� */
#define MAX_QUEUEMEM (MAX_VEXTEX_NUM+1)

/* ��������ͼ�Ķ���֮��������Ϣ������ */
int GraphEdge[ARC_NUM * 2][2] = {{0,1},{1,0},{1,2},{2,1},{2,3},{3,2},{3,4},{4,3},{4,5},{5,4},{5,0},{0,5},{0,6},{6,0},{6,8},{8,6},{6,7},{7,6},{7,8},{8,7},{7,3},{3,7},{8,4},{4,8}};
/*��������visited������ʾһ�������Ƿ񱻷��ʹ�*/
int visited[MAX_VEXTEX_NUM]={0,0,0,0,0,0,0,0,0};
/*������㣬��ÿ������Ӧ�Ľ�� */
typedef struct ArcNode{
  int adjvex;                 /* �û���ָ��Ķ����λ�� */
  struct ArcNode * nextarc;   /* ָ����һ������ָ�� */
}ArcNode;

/* ����ͷ��� */
typedef struct VNode{
  int data;                    /* ������Ϣ */
  struct ArcNode * firstarc;   /* ָ���һ�������ö���Ļ���ָ�� */
}VNode,AdjList[MAX_VEXTEX_NUM]; 

/* ����ͼ�Ľṹ */
typedef struct {
	VNode vertices[MAX_VEXTEX_NUM];/* �����ͷ���� */
	int vexnum;      /* ����ͼ�ж����� */
	int arcnum;      /* ����ͼ�л��� */
}ALGraph;

/*����һ��ʹ���ڽӱ�洢��ͼ*/
void CreateGraph(ALGraph * alGraph)
{
	int i,j;
	ArcNode * newnode;
	ArcNode * vexNode;
	alGraph->vexnum = MAX_VEXTEX_NUM;
	alGraph->arcnum = ARC_NUM;
	/* ��ʼ����ͷ */
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
/* ��ӡ���ͼ */
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
/*�ݹ�ʵ��DFS*/
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
/* ͼ��������ȱ��� */
void DFSTraverse(ALGraph * alGraph)
{
	int i;
	/*���ʱ�־�����ʼ��*/
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
/*Ϊ��ʵ�ֹ�����ȱ�������Ҫ����һ������ */
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
/* ������ȱ��� */
void BFSTraverse(ALGraph * alGraph)
{
	int i;
	int w;
	ArcNode * vexNode;
	QUEUE queue;
	InitQueue(&queue);
	/*���ʱ�־�����ʼ��*/
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
	/*����ͼ���*/
    ALGraph alGraph;
    
    clrscr();
    /*����ͼ���ڽӱ�*/
    CreateGraph(&alGraph);
    /*���ͼ���ڽӱ�*/
    OutputGraph(&alGraph);
    /*������ȱ���*/
    DFSTraverse(&alGraph);
    /*������ȱ���*/
    BFSTraverse(&alGraph);
    getch();
    return 0;
}