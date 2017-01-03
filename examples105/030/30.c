#include "stdio.h"
#define STACKSIZE 2
struct Car
{
 	char   Label;
 	float  InTime;
};
struct StackCar
{
  struct Car *Top;
  struct Car *BottomStack;
  int Size;
};
int StackInitial(struct StackCar *stackcar)
{
  stackcar->BottomStack=(struct Car *)malloc(STACKSIZE*sizeof(struct Car));
  if(!(stackcar->BottomStack)) 
  	return 0;
  stackcar->Top=stackcar->BottomStack;
  stackcar->Size=STACKSIZE;
  return 1;
}
int StackEmpty(struct StackCar stackcar)
{
  if(stackcar.Top==stackcar.BottomStack)
    return 1;
  return 0;
}
int StackFull(struct StackCar stackcar)
{
 	if(stackcar.Top-stackcar.BottomStack>=STACKSIZE)
   	return 1;
 	return 0;
}
int Push(struct StackCar *stackcar,struct Car car)
{
  if(stackcar->Top-stackcar->BottomStack>=STACKSIZE)
    return 0;
  *(stackcar->Top++)=car;
  return 1;
  
}
int Pop(struct StackCar *stackcar,struct Car *car)
{
  if(stackcar->Top==stackcar->BottomStack)
    return 0;
  *car=*(--(stackcar->Top));
  return 1;
}
struct QueueCar
{
  struct Car Info;
  struct QueueCar *next;
};
struct LinkQueue
{
  struct QueueCar * front;
  struct QueueCar * rear;
};
int QueueInitial(struct LinkQueue *Q)
{
  
	Q->front=Q->rear=(struct QueueCar *)malloc(sizeof(struct QueueCar));
  if(!(Q->front)) 
  	return 0;
  Q->front->next=0;
  return 1;
}
int QueueEnter(struct LinkQueue *Queue,struct Car car)
{
  struct QueueCar *p;
  p=(struct QueueCar *)malloc(sizeof(struct QueueCar));
  if(!p) 
  	return 0;
  p->Info=car;
  p->next=0;
  Queue->rear->next=p;
  Queue->rear=p;
  return 1;
}
int QueueEmpty(struct LinkQueue Queue)
{
  if(Queue.front==Queue.rear)
    return 1;
  return 0;
}
int QueueDelete(struct LinkQueue *Queue,struct Car *car)
{
	 struct QueueCar * p;
	 if(Queue->front==Queue->rear) 
	 	return 0;
	 p=Queue->front->next;
	 *car=p->Info;
	 Queue->front->next=p->next;
	 if(Queue->rear==p)
	 Queue->rear=Queue->front;
	 free(p);
	 return 1;
}
int main()
{
 int i,label;
 char ch;
 float intime;
 struct Car carin,carout;
 struct StackCar S;
 struct LinkQueue Q;
 StackInitial(&S);
 QueueInitial(&Q);
 clrscr();
 printf("**************************************\n");
 printf("|            Please Input :          |\n");
 printf("|         i : a car comes in.        |\n");
 printf("|         o : a car comes out.       |\n");
 printf("|         q : query the status.      |\n");
 printf("**************************************\n");
 while(1)
 {
 		switch(getch())
 		{
 			case 'i':
 				printf("Please input the car lable:");
 				scanf("%d",&label);
 				carin.Label=label;
 				printf("Please input the car intime:");
 				scanf("%f",&intime);
 				carin.InTime=intime;
 				if(!StackFull(S))
 				{
 					Push(&S,carin);
 					printf("The %dth car comes in the garage\n",carin.Label);
 				}
 				else
 				{
 					 QueueEnter(&Q,carin);
 					 printf("The %dth car comes in the queue to wait\n",carin.Label);
 				}
 			  break;
 			case 'o':
 				if(!StackEmpty(S))
 				{
 					Pop(&S,&carout);
 					printf("The %dth car comes out\n",carout.Label);
 					if(!QueueEmpty(Q))
 					{
 						QueueDelete(&Q,&carout);
 						Push(&S,carout);
 					}
 				}
 				else
 					printf("There is on car!");
 				break;
 			case 'q':
 				printf("\nThere is %d cars in the garage\n",S.Top-S.BottomStack);
 				printf("There is %d cars in the queue waiting\n",Q.rear-Q.front);
 				break;
 			default :
 					return 0;
 				
 		}
 }
}