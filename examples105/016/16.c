#include<stdio.h>
/*����������������󳤶�*/
#define MAX 100
/*����������������������������������������������ֱ�Ӳ������򡪡�������������������������������������������������*/
void InsertSort(int *R,int n)
{ 
		/* ������R�е�Ԫ��R[1]..R[n-1]����������в�������*/
    int i,j;
    /*�ճ���λR[0]*/
    for(i=n;i>=1;i--)
			R[i]=R[i-1];
    /* ���β���R[2]������R[n] */
    for(i=2;i<=n;i++)
    /* ��R[i]���ڵ��������������е�R����R[i]Ӧ��ԭ��λ���ϣ�������в���*/ 
    if(R[i]<R[i-1])
    {
    	/* R[0]���ڱ�������R[i] */
      R[0]=R[i];
      j=i-1; 
      /* ����������������R[0]..R[-1]�в���R[i]�Ĳ���λ�� */
      while(1)
      { 
      	/* ���ؼ��ִ���R[i]�ļ�¼���� */
       	R[j+1]=R[j]; 
        j--;
     	 /* ��R[i]��R[j]ʱ��ֹ */
        if(R[0]>=R[j])
        	break;
      }
      /* R[i]���뵽��ȷ��λ���� */ 
      R[j+1]=R[0]; 
    }
    /*Ԫ�ظ�λ*/
    for(i=0;i<n;i++)
			R[i]=R[i+1];
}
/*���������������������������������������������� ϣ������ ����������������������������������������������������*/
void ShellSort(int *R,int n)//ϣ������
{
	int i,j,k;
	 /*�ճ��ݴ浥ԪR[0]*/
	for(i=n;i>=1;i--)
		R[i]=R[i-1];
	k=n/2;
	while(k>=1)
	{
		/* ϣ�������е�һ������kΪ��ǰ���� */
		/* ��R[d+1����n]�ֱ������鵱ǰ�������� */
		for(i=k+1;i<=n;i++)
		{
			/* R[0]ֻ���ݴ浥Ԫ�������ڱ� */
			R[0]=R[i];
			j=i-k;
			/* ����R[i]�Ĳ���λ�� */
			while((R[j]>R[0])&&(j>=0))
			{
				/* ���Ƽ�¼ */
				R[j+k]=R[j];
				/* ����ǰһ��¼ */
				j=j-k;
			}
			/* ����R[i]����ȷ��λ���� */
			R[j+k]=R[0];
		}
		/* ����һ���� */
		k=k/2;
	}
	/*Ԫ�ظ�λ*/
	for(i=0;i<n;i++)
		R[i]=R[i+1];
}
/*���������������������������������������������� ð������ ����������������������������������������������������*/
void BubbleSort(int *R,int n)
{ 
	 /* R[l]..R[n]�Ǵ�������ļ���������������ɨ�裬��R��ð������ */
   int i,j;
   /* ������־ */
   int flag; 
   /*�ճ��ݴ浥ԪR[0]*/
	 for(i=n;i>=1;i--)
		 R[i]=R[i-1];
   for(i=1;i<n;i++)
   { /* �����n-1������ */
       flag=0; /* ��������ʼǰ��������־ӦΪ�� */
       for(j=n-1;j>=i;j--) /* �Ե�ǰ������R[i..n]��������ɨ�� */
        /* ������¼ */
        if(R[j+1]<R[j])
        {
        	/* R[0]�����ڱ��������ݴ浥Ԫ */
          R[0]=R[j+1]; 
          R[j+1]=R[j];
          R[j]=R[0];
          /* �����˽�������������־��Ϊ�� */
          flag=1; 
        }
       /* ��������δ������������ǰ��ֹ�㷨 */
       if(!flag) 
       {
       	   /*Ԫ�ظ�λ*/
       	  for(i=0;i<n;i++)
				  	R[i]=R[i+1];
	        return;
	     }
     }
}
/*���������������������������������������������� �������� ����������������������������������������������������*/
/* ����������,����PartitionQuick(R,l,h)ʱ��
��R[l..h]������,�����������λ�� */
int PartitionQuick(int *R,int l,int h)
{
	int i,j;
	int x;
	i=l;
	j=h;
	/* ������ĵ�1����¼��Ϊ��׼ */
	x=R[i];
	/* ���������˽������м�ɨ�裬ֱ��i=jΪֹ */
	while(i<j)
	{
		/*��������ɨ�裬���ҵ�1���ؼ���С��x�ļ�¼R[j] */
		while((i<j)&&(R[j]>=x))
			j--;
		/*�ҵ���R[j]�Ĺؼ���С��x*/
		if(i<j)
		{
			/*����R[i]��R[j]��������iָ���1*/
			R[i]=R[j];
			i++;
		}
		/*��������ɨ�裬���ҵ�1���ؼ��ִ���x�ļ�¼R[i]*/
		while((i<j)&&(R[i]<=x))
			i++;
		/*��ʾ�ҵ���R[i]��ʹR[i]>x*/
		if(i<j)
		{
			/*����R[i]��R[j]��������jָ���1*/
			R[j]=R[i];
			j--;
		}
	}
	/*��׼��¼�����λ*/
	R[i]=x;
	return i;
}
void QuickSort(int *R,int l,int h)
{
	/*i�ǻ��ֺ�Ļ�׼��¼��λ��*/
	int i;
	/*�������䳤�ȴ���1ʱ��������*/
	if(l<h)
	{
		/*��R[l..h]������*/
		i=PartitionQuick(R,l,h);
		/*��������ݹ�����*/
		QuickSort(R,l,i-1);
		/*��������ݹ�����*/
		QuickSort(R,i+1,h);
	}
}
/*���������������������������������������������� ѡ������ ����������������������������������������������������*/
void SelectSort(int *R,int n)
{
   int i,j,k;
    /*�ճ��ݴ浥ԪR[0]*/
	 for(i=n;i>=1;i--)
		 R[i]=R[i-1];
	 /*����n-1��ѡ������*/
   for(i=1;i<n;i++)
   {
   	 /* ����i������(1��i��n-1) */
   	 /* k����Ŀǰ�ҵ�����СԪ�����ڵ�λ�� */
     k=i;
     /* �ڵ�ǰ������R[i..n]��ѡ��С�ļ�¼R[k] */
     for(j=i+1;j<=n;j++) 
       if(R[j]<R[k])
         k=j; 
       if(k!=i)
       { 
       	 /*����R[i]��R[k],R[0]���ݴ浥Ԫʹ��*/
         R[0]=R[i]; 
         R[i]=R[k]; 
         R[k]=R[0]; 
       } 
     } 
     /*Ԫ�ظ�λ*/
     for(i=0;i<n;i++)
				R[i]=R[i+1];
} 
/*�������������������������������������������������� ������ ��������������������������������������������������������*/
void HeapAdjust(int *R,int i,int n)
{ 
	 /*��R[1..n]���жѵ���*/
   int j,temp;
   temp=R[i];
   j=2*i;
   while (j<=n)
   {
	   if (R[j]>R[j+1]&&j<n) 
	  	 j++;
	   if (temp<R[j]) 
	  	 j=n+1;
	   else
	   {
	   	 R[i]=R[j];
     	 i=j;
    	 j=2*i;
     }
   }
   R[i]=temp;
}
void HeapSort(int *R,int n)
{ /* ��R[1..n]���ж�������R[0]���ݴ浥Ԫ*/
    int i;
    /*�ճ��ݴ浥ԪR[0]*/
	  for(i=n;i>=1;i--)
		 R[i]=R[i-1];
    /* ��R[1-n]���ɳ�ʼ��*/
    for(i=n/2;i>0;i--)
      HeapAdjust(R,i,n); 
    /*����n-1�˶�����*/
    for(i=n;i>1;i--)
    { 
    	/* ���Ѷ��Ͷ������һ����¼���� */
    	R[0]=R[1]; 
    	R[1]=R[i];
    	R[i]=R[0]; 
    	/* ��R[1]..R[i-1]���µ���Ϊ��*/
    	HeapAdjust(R,1,i-1); 
    }
    /*Ԫ�ظ�λ*/
    for(i=0;i<n;i++)
			R[i]=R[i+1];
} 
int main()
{
	/*����ʹ�õ�����*/
	int R[MAX]={1,82,63,4,65,69,37,98,39,46};
	int i;
	char c;
	clrscr();
	printf("***************************************\n");
	printf("|  Please choose the method to sort:  |\n");
	printf("|           i :  InsertSort           |\n");
	printf("|           l :  ShellSort            |\n");
  printf("|           b :  BubbleSort           |\n");
  printf("|           q :  QuickSort            |\n");
  printf("|           s :  SelectSort           |\n");
  printf("|           h :  HeapSort             |\n");
  printf("***************************************\n");
  while(1)
  {
    switch(getch())
    {
      case 'i':
        InsertSort(R,10);
        printf("\nThe result of InsertSort is:\n");
        break;
      case 'l':
        ShellSort(R,10);
        printf("\nThe result of ShellSort is:\n");
        break;
      case 'b':
        BubbleSort(R,10);
        printf("\nThe result of InsertSort is:\n");
        break;
      case 'q':
        QuickSort(R,0,9);
        printf("\nThe result of BubbleSort is:\n");
        break;
      case 's':
        SelectSort(R,10);
        printf("\nThe result of SelectSort is:\n");
        break;
      case 'h':
        HeapSort(R,10);
        printf("\nThe result of HeapSort is:\n");
        break;
      default:
        return 0;	
    }
    /*�����������Ľ��*/
	  for(i=0;i<10;i++)
		  printf("%3d",R[i]);
		printf("\n");
	}
}