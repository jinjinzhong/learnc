#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h> 
/*定义使用的宏*/
#define STACK_INIT_SIZE 10
#define TRUE 1
#define FALSE  0
#define ERROR 0        
/*程序保存的密码*/
char PASSWORD[10]="passwd";
/*栈中元素类型*/ 
typedef char Node;
/*定义栈结构体*/
typedef struct STACK 
{
	Node *base;
	Node *top;
	int size;
	int count;
}Stack,*PStack;   
/*定义一个返回类型*/
typedef int Result; 
/*把数据压入栈*/
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
/*弹出并删除栈顶元素*/
void Pop(PStack *S)
{
	if((*S)->top==(*S)->base) return ERROR;
	(*S)->top--;
	--(*S)->count;
	return TRUE;
}
/*返回栈顶元素*/
Result GetTop(PStack S,Node *e)
{
	if(S->top==S->base) return ERROR;
	*e=*(S->top-1);
	S->top--;
} 
/*把栈置为空*/
void ClearStack(PStack *S)  
{
	(*S)->top=(*S)->base;
	(*S)->count=0;
}        
/*判断栈空否*/
Result StackEmpty(PStack S) 
{
	if(S.top==S.base) 
		return TRUE;
	else
		return FALSE;
}            
/*初始化栈*/
void Init(PStack *S) 
{
	*S=(PStack *)malloc(sizeof(PStack));
	(*S)->base=(Node *)malloc(STACK_INIT_SIZE*sizeof(Node));
	if(!(*S)->base)exit(-1);
	(*S)->top=(*S)->base;
	(*S)->size=STACK_INIT_SIZE;
	(*S)->count=0;
}     
/*销毁栈*/
Result Destroy(PStack *S) 
{
	free((*S)->base);
	free((*S));
	return OK;
}  
/*将栈中的元素反序*/
void Change(PStack S,char *a) 
{ 
	int n=S.count-1 ;
	while (!StackEmpty(S))
		GetTop(&S,&a[n--]);
}  
/*处理密码匹配工作*/
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
			gotoxy(1,1); /*定位光标位置*/
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
		for(;;)  /* 密码输入，可退格 */
		{
			ch=getch();  /* 退格 的ASCII 是8 */
			if(ch!=13)   /* 判断是否为回车，不是则把它赋给下面*/
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
	}/*最上面的for完*/
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