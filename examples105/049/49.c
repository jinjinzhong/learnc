#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h> 
/*����ʹ�õĺ�*/
#define STACK_INIT_SIZE 10
#define TRUE 1
#define FALSE  0
#define ERROR 0        
/*���򱣴������*/
char PASSWORD[10]="passwd";
/*ջ��Ԫ������*/ 
typedef char Node;
/*����ջ�ṹ��*/
typedef struct STACK 
{
	Node *base;
	Node *top;
	int size;
	int count;
}Stack,*PStack;   
/*����һ����������*/
typedef int Result; 
/*������ѹ��ջ*/
void Push(PStack *S,Node e) 
{
	if((*S)->top - (*S)->base>=(*S)->size)
	{
		(*S)->base=(Node *) realloc((*S)->base,
			((*S)->size + 2) * sizeof(Node));
		if(!(*S)->base)exit(-1);
		(*S)->top=(*S)->base+(*S)->size;
		(*S)->size += 2;
	}
	*((*S)->top++)=e;
	++(*S)->count;
} 
/*������ɾ��ջ��Ԫ��*/
void Pop(PStack *S)
{
	if((*S)->top==(*S)->base) return ERROR;
	(*S)->top--;
	--(*S)->count;
	return TRUE;
}
/*����ջ��Ԫ��*/
Result GetTop(PStack S,Node *e)
{
	if(S->top==S->base) return ERROR;
	*e=*(S->top-1);
	S->top--;
} 
/*��ջ��Ϊ��*/
void ClearStack(PStack *S)  
{
	(*S)->top=(*S)->base;
	(*S)->count=0;
}        
/*�ж�ջ�շ�*/
Result StackEmpty(PStack S) 
{
	if(S.top==S.base) 
		return TRUE;
	else
		return FALSE;
}            
/*��ʼ��ջ*/
void Init(PStack *S) 
{
	*S=(PStack *)malloc(sizeof(PStack));
	(*S)->base=(Node *)malloc(STACK_INIT_SIZE*sizeof(Node));
	if(!(*S)->base)exit(-1);
	(*S)->top=(*S)->base;
	(*S)->size=STACK_INIT_SIZE;
	(*S)->count=0;
}     
/*����ջ*/
Result Destroy(PStack *S) 
{
	free((*S)->base);
	free((*S));
	return OK;
}  
/*��ջ�е�Ԫ�ط���*/
void Change(PStack S,char *a) 
{ 
	int n=S.count-1 ;
	while (!StackEmpty(S))
		GetTop(&S,&a[n--]);
}  
/*��������ƥ�乤��*/
void Process(PStack *s)
{
	int i=0,k,j=0;
	Node ch,*a;
	k=strlen(PASSWORD);
	printf("input the password which has %d chars, you have 3 chances:\n",k);
	printf("Input:\\>");
	for(;;)
	{ 
		if(i>=3)
		{  
			i++;
			clrscr();
			gotoxy(1,1); /*��λ���λ��*/
			break;
		}
		else if(i>0&&i<3)
		{  
			gotoxy(5,2);
			for(j=1;j<=(*s)->count;j++)
				printf(" ");
			gotoxy(5,2);
			ClearStack(s);
		}
		for(;;)  /* �������룬���˸� */
		{
			ch=getch();  /* �˸� ��ASCII ��8 */
			if(ch!=13)   /* �ж��Ƿ�Ϊ�س��������������������*/
			{
				if(ch==8) 
				{
					Pop(s);
					gotoxy(4+j,2);
					printf(" ");
					gotoxy(4+j,2);
				}
				else 
				{
					printf("*");
					Push(s,ch);
				}
				j=(*s)->count;
			}
			else break;
		}
		i++;
		if(k!=j) 
			continue; 
		else  
		{
			a=(Node *)malloc((*s)->count*sizeof(Node));
			Change(**s,a);
			for(j=1;j<=(*s)->count;)
			{
				if(a[j-1]==PASSWORD[j-1]) j++;
				else {j=(*s)->count+2;break;}
			}
			if(j==(*s)->count+2) 
				continue;
			else break;
		}
	}/*�������for��*/
	if(i==4) 
		printf("\nwrong password");
	else 	printf("\ncorrect!\n");
	free(a);
}

void main()
{
	PStack s;
	Init(&s);
	Process(&s);
	getch();
	Destroy(&s);
	return 0;
}