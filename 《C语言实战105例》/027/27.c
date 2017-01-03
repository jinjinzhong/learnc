
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<conio.h>

typedef struct
{
  int OccurTime;
  int NType;
}Event,ElemType;

typedef struct
{
 int ArrivalTime;
 int Duration;
}QElemType;

struct LinkNode
{
  Event data;
  struct LinkNode *next;
};

typedef struct LinkNode LNode;
typedef struct LinkNode *LinkList;
typedef struct LinkNode *EvenList;

typedef struct QNode
{
 QElemType elem;
 struct QNode *next;
}QNode,*QueuePtr;

typedef struct LinkQueue
{ 
  QueuePtr front;
  QueuePtr rear;
}LinkQueue;

EvenList ev;
Event en;
LinkQueue q[5];
QElemType customer;
int TotalTime,CustomerNum,CloseTime;
/*初始化有序链表*/
int InitList(EvenList *L)
{
  *L=(LNode *)malloc(sizeof(LNode));
  if(!(*L))   exit(0);
  (*L)->next=NULL;
  return 1;
}
/*删除链头元素*/
int DeHead(EvenList *L,Event *e)
{ 
  LNode *pc,*q;
  pc=*L;
  q=pc->next;
  pc->next=q->next;
  *e=q->data;return 1;
}
/*判断有序链表是否为空*/
int ListEmpty(LNode L)
{
  LNode *p;
  int j=0;
  p=L.next;
  while(p)
  {
 	 j++;break;
  }
  if(j==0) return 1;
  else return 0;
}
/*判断两个事件的发生时刻*/
int CmpTime(Event a,Event b)
{ 
  if(a.OccurTime>b.OccurTime) return 1;
  else if(a.OccurTime==b.OccurTime) return 0;
  else return -1;
}
int OrderInsert(EvenList *L,Event e,int (* cmp)(Event ,Event ))
{ 
  LNode *p,*pc;/*把事件插入链表*/
  if((p=(LNode *)malloc(sizeof(LNode)))==NULL)/*分配空间*/
  { 
  	printf("error\n"); 
  	return(0);
  }
  if(ListEmpty(**L)) 
  { 
  	p->data=e;p->next=(*L)->next;(*L)->next=p;}
    else 
    {
      switch(cmp(((*L)->next)->data,e))
      {
      	case -1:
      	  pc=(*L)->next;
		  while(pc->next!=NULL)
		  {
		    if((pc->next)->data.OccurTime<=e.OccurTime)
		        pc=pc->next;
		    else break;
		  }
		  p->data=e;
		  p->next=pc->next;/*把它接在比它大的前*/
		  pc->next=p;
		  break;
        case 0:
          pc=(*L)->next;/*相等时，接在相等的后面*/
          p->data=e;
          p->next=pc->next;
          pc->next=p;
          break;
        case 1:
          p->data=e;
          p->next=(*L)->next;
          (*L)->next=p;
          break;/*小于时，接在最前面*/
      }
    }
   return 1;
}
void DestroyList(EvenList *L)/*销毁表*/
{
  LNode *p;
  while(*L)
  {
  	p=(*L)->next;
  	free(*L);
  	*L=p;
  }
}
int InitQueue(LinkQueue *Q)/*初始化队列*/
{ 
  Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
  if(!Q->front) exit(0);
  (Q->front)->next=NULL;
  return 1;
}
int DestroyQueue(LinkQueue *Q)/*销毁队列*/
{ 
  while(Q->front)
  { 
  	Q->rear=Q->front->next;
    free(Q->front);
    Q->front=Q->rear;
  }
  return 1;
}
int EnQueue(LinkQueue *Q,QElemType e)/*插在队最后*/
{
  QueuePtr p;
  if((p=(QueuePtr)malloc(sizeof(QNode)))== NULL)
  	exit(0);
  p->elem=e;p->next=NULL;
  (Q->rear)->next=p;
  Q->rear=p;/*重新设置队尾*/
  return 1;
}
int QueueEmpty(LinkQueue Q)
{ 
  if(Q.front==Q.rear) return 1;
  else return 0;
}

int DelQueue(LinkQueue *Q,QElemType *e)/*删除队的第一个元素*/
{
  QueuePtr p;
  if(QueueEmpty(*Q)) return 0;
  p=(Q->front)->next;
  *e=p->elem;
  (Q->front)->next=p->next;
  if(Q->rear==p) Q->rear=Q->front;
  free(p);
  return 1;
}
void GetHead(LinkQueue Q,QElemType *a)
{
  QNode *p;
  if(Q.front==Q.rear) exit(0);
  p=(Q.front)->next;
  *a=p->elem;
}
int QueueLength(LinkQueue Q)/*队的长度*/
{ 
  int i=0;
  QNode *pc;
  if(Q.front==Q.rear) return 0;
  pc=Q.front;
  while(pc->next)
  {
  	i++;pc=pc->next;
  }
  return i;
}
int Mininum(LinkQueue *Q)/*求长度最短的队*/
{ 
  int a[4],e,j,i;
  for(i=1;i<=4;i++)
    a[i-1]=QueueLength(Q[i]);
  e=a[0];
  j=1;
  for(i=1;i<=3;i++)
    if(e>a[i]) 
    {
      e=a[i];
      j=i+1;
    }
  return j;
}
void OpenForDay()/*初始化操作*/
{ 
  int i;
  TotalTime=0;
  CustomerNum=0;/*初始化累计时间和客户数*/
  InitList(&ev);
  en.OccurTime=0;
  en.NType=0;/*设定第一个客户到达事件*/
  OrderInsert(&ev,en,CmpTime);/*把它插入事件表*/
  for(i=1;i<=4;i++) 
    InitQueue(&q[i]);/*置空队列*/
}
void RandomTime(int *a,int *b)/*生成随机数，a为每个客户办理时间在30分钟内，
                           b 为两相隔客户到达的间隔时间不超过5分钟*/
{ 
  *a=0+rand()%30;
  *b=0+rand()%5;
}
void CustomerArrived()/*处理客户到达事件*/
{
  int durtime,intertime,t,i,b;
  ++CustomerNum;/*记录客户数*/
  RandomTime(&durtime,&intertime);
  b=en.OccurTime;
  t=en.OccurTime+intertime;/*下一客户到达时刻*/
  if(t<CloseTime)
  {
  	en.OccurTime=t;
  	en.NType=0;  
    OrderInsert(&ev,en,CmpTime);
  }
  i=Mininum(q);/*求队列最短*/
  customer.ArrivalTime=b;customer.Duration=durtime;/*为要插入队的客户设置到达时间和办理所需时间*/
  EnQueue(&q[i],customer);
  if(QueueLength(q[i])==1)
  {
  	en.OccurTime=b+durtime;
  	en.NType=i;
    OrderInsert(&ev,en,CmpTime);/*设定第i 个离开事件并插入事件表*/
  }
}
void CustomerDeparture()/*处理客户离开事件*/
{
  int i;
  i=en.NType;
  DelQueue(&q[i],&customer);/*删除第i队列的排头客户*/
  TotalTime+=en.OccurTime-customer.ArrivalTime;/*累计客户逗留时间*/
  if(!QueueEmpty(q[i]))/*设定第i队列的一个将要离开事件并插入事件表*/
  { 
  	GetHead(q[i],&customer);/*得到它的资料*/
    en.OccurTime+=customer.Duration;en.NType=i;
    OrderInsert(&ev,en,CmpTime);
  }
}
void Bank_Simulation()
{
  OpenForDay();/*初始化*/
  while(!ListEmpty(*ev))/*非空时，删掉表里的第一个*/
  { 
  	DeHead(&ev,&en);
    if(en.NType==0)
      CustomerArrived();/*是客户还没办理的，就处理到达事件*/
    else 
      CustomerDeparture();/*否则处理离开事件*/
   }
  printf("The Average Time is %.3f\n\n",(float)TotalTime/CustomerNum);
}
void main()
{
	clrscr();
	puts("***************************************");
	puts("*  This is a bank simulation program  *");
	puts("***************************************");
	do
	{
		puts("please input the closetime of the bank:");
		scanf("%d",&CloseTime);/*输入关门时间*/
	    Bank_Simulation();
    }while(CloseTime>=0);
    getch();
}
