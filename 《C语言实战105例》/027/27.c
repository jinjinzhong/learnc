
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
/*��ʼ����������*/
int InitList(EvenList *L)
{
  *L=(LNode *)malloc(sizeof(LNode));
  if(!(*L))   exit(0);
  (*L)->next=NULL;
  return 1;
}
/*ɾ����ͷԪ��*/
int DeHead(EvenList *L,Event *e)
{ 
  LNode *pc,*q;
  pc=*L;
  q=pc->next;
  pc->next=q->next;
  *e=q->data;return 1;
}
/*�ж����������Ƿ�Ϊ��*/
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
/*�ж������¼��ķ���ʱ��*/
int CmpTime(Event a,Event b)
{ 
  if(a.OccurTime>b.OccurTime) return 1;
  else if(a.OccurTime==b.OccurTime) return 0;
  else return -1;
}
int OrderInsert(EvenList *L,Event e,int (* cmp)(Event ,Event ))
{ 
  LNode *p,*pc;/*���¼���������*/
  if((p=(LNode *)malloc(sizeof(LNode)))==NULL)/*����ռ�*/
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
		  p->next=pc->next;/*�������ڱ������ǰ*/
		  pc->next=p;
		  break;
        case 0:
          pc=(*L)->next;/*���ʱ��������ȵĺ���*/
          p->data=e;
          p->next=pc->next;
          pc->next=p;
          break;
        case 1:
          p->data=e;
          p->next=(*L)->next;
          (*L)->next=p;
          break;/*С��ʱ��������ǰ��*/
      }
    }
   return 1;
}
void DestroyList(EvenList *L)/*���ٱ�*/
{
  LNode *p;
  while(*L)
  {
  	p=(*L)->next;
  	free(*L);
  	*L=p;
  }
}
int InitQueue(LinkQueue *Q)/*��ʼ������*/
{ 
  Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
  if(!Q->front) exit(0);
  (Q->front)->next=NULL;
  return 1;
}
int DestroyQueue(LinkQueue *Q)/*���ٶ���*/
{ 
  while(Q->front)
  { 
  	Q->rear=Q->front->next;
    free(Q->front);
    Q->front=Q->rear;
  }
  return 1;
}
int EnQueue(LinkQueue *Q,QElemType e)/*���ڶ����*/
{
  QueuePtr p;
  if((p=(QueuePtr)malloc(sizeof(QNode)))== NULL)
  	exit(0);
  p->elem=e;p->next=NULL;
  (Q->rear)->next=p;
  Q->rear=p;/*�������ö�β*/
  return 1;
}
int QueueEmpty(LinkQueue Q)
{ 
  if(Q.front==Q.rear) return 1;
  else return 0;
}

int DelQueue(LinkQueue *Q,QElemType *e)/*ɾ���ӵĵ�һ��Ԫ��*/
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
int QueueLength(LinkQueue Q)/*�ӵĳ���*/
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
int Mininum(LinkQueue *Q)/*�󳤶���̵Ķ�*/
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
void OpenForDay()/*��ʼ������*/
{ 
  int i;
  TotalTime=0;
  CustomerNum=0;/*��ʼ���ۼ�ʱ��Ϳͻ���*/
  InitList(&ev);
  en.OccurTime=0;
  en.NType=0;/*�趨��һ���ͻ������¼�*/
  OrderInsert(&ev,en,CmpTime);/*���������¼���*/
  for(i=1;i<=4;i++) 
    InitQueue(&q[i]);/*�ÿն���*/
}
void RandomTime(int *a,int *b)/*�����������aΪÿ���ͻ�����ʱ����30�����ڣ�
                           b Ϊ������ͻ�����ļ��ʱ�䲻����5����*/
{ 
  *a=0+rand()%30;
  *b=0+rand()%5;
}
void CustomerArrived()/*����ͻ������¼�*/
{
  int durtime,intertime,t,i,b;
  ++CustomerNum;/*��¼�ͻ���*/
  RandomTime(&durtime,&intertime);
  b=en.OccurTime;
  t=en.OccurTime+intertime;/*��һ�ͻ�����ʱ��*/
  if(t<CloseTime)
  {
  	en.OccurTime=t;
  	en.NType=0;  
    OrderInsert(&ev,en,CmpTime);
  }
  i=Mininum(q);/*��������*/
  customer.ArrivalTime=b;customer.Duration=durtime;/*ΪҪ����ӵĿͻ����õ���ʱ��Ͱ�������ʱ��*/
  EnQueue(&q[i],customer);
  if(QueueLength(q[i])==1)
  {
  	en.OccurTime=b+durtime;
  	en.NType=i;
    OrderInsert(&ev,en,CmpTime);/*�趨��i ���뿪�¼��������¼���*/
  }
}
void CustomerDeparture()/*����ͻ��뿪�¼�*/
{
  int i;
  i=en.NType;
  DelQueue(&q[i],&customer);/*ɾ����i���е���ͷ�ͻ�*/
  TotalTime+=en.OccurTime-customer.ArrivalTime;/*�ۼƿͻ�����ʱ��*/
  if(!QueueEmpty(q[i]))/*�趨��i���е�һ����Ҫ�뿪�¼��������¼���*/
  { 
  	GetHead(q[i],&customer);/*�õ���������*/
    en.OccurTime+=customer.Duration;en.NType=i;
    OrderInsert(&ev,en,CmpTime);
  }
}
void Bank_Simulation()
{
  OpenForDay();/*��ʼ��*/
  while(!ListEmpty(*ev))/*�ǿ�ʱ��ɾ������ĵ�һ��*/
  { 
  	DeHead(&ev,&en);
    if(en.NType==0)
      CustomerArrived();/*�ǿͻ���û����ģ��ʹ������¼�*/
    else 
      CustomerDeparture();/*�������뿪�¼�*/
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
		scanf("%d",&CloseTime);/*�������ʱ��*/
	    Bank_Simulation();
    }while(CloseTime>=0);
    getch();
}
