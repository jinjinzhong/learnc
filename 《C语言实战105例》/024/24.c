#include<stdio.h>
#include<stdlib.h>
/*�������Ľ��ṹ*/

typedef struct TreeNode{
  char data;/*���н���������һ���ַ�*/
  struct TreeNode *lchild;
  struct TreeNode *rchild;
}TREENODE;
int NodeNum = 0;/*ͳ�����Ľ����*/
int LeafNum = 0;/*ͳ������Ҷ�ӽ����*/
char ch[] = {'a', 'b', 'c', ' ', ' ', 'd', ' ', ' ', 'e',  'f', ' ', ' ', 'g', ' ', ' '};
int inc = 0;
/*����һ�Ŷ�����*/
int CreateBiTree(TREENODE **T)
/*�������������������н���ֵ,�Կ��ַ���ʾ����*/
{
	char i;
	if(ch[inc++]==' ') 
		*T = NULL;
	else
	{
		printf("%c\n",ch[inc-1]);
		if(!(*T = (TREENODE *)malloc(sizeof(TREENODE)))) 
			return -1;
		(*T)->data = ch[inc-1];
		printf("%c\n",(*T)->data);
		CreateBiTree(&((*T)->lchild));
		CreateBiTree(&((*T)->rchild));
	}
	return 1;
}
/*�������������*/
int PreOderTraverse(TREENODE *T)
{
	if(T)
	{
		printf("%c  ",T->data);
		PreOderTraverse(T->lchild);
		PreOderTraverse(T->rchild);
	}
	return 1;
}
/*  �������������*/
int InOderTraverse(TREENODE *T)
{
	if(T)
	{
		InOderTraverse(T->lchild);
		printf("%c  ",T->data);
		InOderTraverse(T->rchild);
	}
	return 1;
}
/*  �������������*/
int BackOderTraverse(TREENODE *T)
{
	if(T)
	{
		BackOderTraverse(T->lchild);
		BackOderTraverse(T->rchild);
		printf("%c  ",T->data);
	}
	return 1;
}
/*��������������������еĽ����*/
void CountNodeNum(TREENODE *T)
{
	if(T)
	{
		NodeNum ++;
		CountNodeNum(T->lchild);
		CountNodeNum(T->rchild);
	}
}
/*���������������Ҷ�ӽڵ���*/
void CountLeafNum(TREENODE *T)
{
	if(T)
	{
		if((!(T->lchild))&&(!(T->rchild)))
		    LeafNum ++;
		CountLeafNum(T->lchild);
		CountLeafNum(T->rchild);
	}
}
int main()
{
	TREENODE *T;
	int i;
	CreateBiTree(&T);
	do
	{
	    clrscr();
	    puts("**************************************************");
	    puts("*                   you can choose:              *");
	    puts("*  1:  Traverse the Binary tree by pre order     *");
      puts("*  2:  Traverse the Binary tree by mid order     *");
      puts("*  3:  Traverse the Binary tree by back order    *");
      puts("*  4:  Count the node num of the Binary tree     *");	
      puts("*  5:  Count the leaf node num of the Binary tree*");
	    puts("**************************************************");
	    puts("please input your choice:");
	    scanf("%d",&i);
	    switch(i)
	    {
	        case 1:
					printf("The preoder is:\n");
					PreOderTraverse(T);
					printf("\n");
					break;
				case 2:
					printf("The midoder is:\n");
					InOderTraverse(T);
					printf("\n");
					break;
				case 3:
					printf("The backoder is:\n");
					BackOderTraverse(T);
					printf("\n");
					break;	
				case 4:
					CountNodeNum(T);
					printf("The nodenum of the tree is:%d\n",NodeNum);
					break;	
				case 5:
					CountLeafNum(T);
					printf("The leafnum of the tree is:%d\n",LeafNum);
					break;
	    }
	    printf("please input any char to go on\n");
	    getch();
	}while((i>=1)&&(i<6));
	
	getch();
	return 1;
}

