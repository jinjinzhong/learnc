#include<stdio.h>
/*定义待排序数组的最大长度*/
#define MAX 100
/*———————————————————————直接插入排序——————————————————————————*/
void InsertSort(int *R,int n)
{ 
		/* 对数组R中的元素R[1]..R[n-1]按递增序进行插入排序*/
    int i,j;
    /*空出哨位R[0]*/
    for(i=n;i>=1;i--)
			R[i]=R[i-1];
    /* 依次插入R[2]，…，R[n] */
    for(i=2;i<=n;i++)
    /* 若R[i]大于等于有序区中所有的R，则R[i]应在原有位置上，否则进行插入*/ 
    if(R[i]<R[i-1])
    {
    	/* R[0]是哨兵，保存R[i] */
      R[0]=R[i];
      j=i-1; 
      /* 从右向左在有序区R[0]..R[-1]中查找R[i]的插入位置 */
      while(1)
      { 
      	/* 将关键字大于R[i]的记录后移 */
       	R[j+1]=R[j]; 
        j--;
     	 /* 当R[i]≥R[j]时终止 */
        if(R[0]>=R[j])
        	break;
      }
      /* R[i]插入到正确的位置上 */ 
      R[j+1]=R[0]; 
    }
    /*元素复位*/
    for(i=0;i<n;i++)
			R[i]=R[i+1];
}
/*——————————————————————— 希尔排序 ——————————————————————————*/
void ShellSort(int *R,int n)//希尔排序
{
	int i,j,k;
	 /*空出暂存单元R[0]*/
	for(i=n;i>=1;i--)
		R[i]=R[i-1];
	k=n/2;
	while(k>=1)
	{
		/* 希尔排序中的一趟排序，k为当前增量 */
		/* 将R[d+1．．n]分别插入各组当前的有序区 */
		for(i=k+1;i<=n;i++)
		{
			/* R[0]只是暂存单元，不是哨兵 */
			R[0]=R[i];
			j=i-k;
			/* 查找R[i]的插入位置 */
			while((R[j]>R[0])&&(j>=0))
			{
				/* 后移记录 */
				R[j+k]=R[j];
				/* 查找前一记录 */
				j=j-k;
			}
			/* 插入R[i]到正确的位置上 */
			R[j+k]=R[0];
		}
		/* 求下一增量 */
		k=k/2;
	}
	/*元素复位*/
	for(i=0;i<n;i++)
		R[i]=R[i+1];
}
/*——————————————————————— 冒泡排序 ——————————————————————————*/
void BubbleSort(int *R,int n)
{ 
	 /* R[l]..R[n]是待排序的文件，采用自下向上扫描，对R做冒泡排序 */
   int i,j;
   /* 交换标志 */
   int flag; 
   /*空出暂存单元R[0]*/
	 for(i=n;i>=1;i--)
		 R[i]=R[i-1];
   for(i=1;i<n;i++)
   { /* 最多做n-1趟排序 */
       flag=0; /* 本趟排序开始前，交换标志应为假 */
       for(j=n-1;j>=i;j--) /* 对当前无序区R[i..n]自下向上扫描 */
        /* 交换记录 */
        if(R[j+1]<R[j])
        {
        	/* R[0]不是哨兵，仅做暂存单元 */
          R[0]=R[j+1]; 
          R[j+1]=R[j];
          R[j]=R[0];
          /* 发生了交换，将交换标志置为真 */
          flag=1; 
        }
       /* 本趟排序未发生交换，提前终止算法 */
       if(!flag) 
       {
       	   /*元素复位*/
       	  for(i=0;i<n;i++)
				  	R[i]=R[i+1];
	        return;
	     }
     }
}
/*——————————————————————— 快速排序 ——————————————————————————*/
/* 分区处理函数,调用PartitionQuick(R,l,h)时，
对R[l..h]做划分,并返回枢轴的位置 */
int PartitionQuick(int *R,int l,int h)
{
	int i,j;
	int x;
	i=l;
	j=h;
	/* 用区间的第1个记录作为基准 */
	x=R[i];
	/* 从区间两端交替向中间扫描，直至i=j为止 */
	while(i<j)
	{
		/*从右向左扫描，查找第1个关键字小于x的记录R[j] */
		while((i<j)&&(R[j]>=x))
			j--;
		/*找到的R[j]的关键字小于x*/
		if(i<j)
		{
			/*交换R[i]和R[j]，交换后i指针加1*/
			R[i]=R[j];
			i++;
		}
		/*从左向右扫描，查找第1个关键字大于x的记录R[i]*/
		while((i<j)&&(R[i]<=x))
			i++;
		/*表示找到了R[i]，使R[i]>x*/
		if(i<j)
		{
			/*交换R[i]和R[j]，交换后j指针减1*/
			R[j]=R[i];
			j--;
		}
	}
	/*基准记录被最后定位*/
	R[i]=x;
	return i;
}
void QuickSort(int *R,int l,int h)
{
	/*i是划分后的基准记录的位置*/
	int i;
	/*仅当区间长度大于1时才须排序*/
	if(l<h)
	{
		/*对R[l..h]做划分*/
		i=PartitionQuick(R,l,h);
		/*对左区间递归排序*/
		QuickSort(R,l,i-1);
		/*对右区间递归排序*/
		QuickSort(R,i+1,h);
	}
}
/*——————————————————————— 选择排序 ——————————————————————————*/
void SelectSort(int *R,int n)
{
   int i,j,k;
    /*空出暂存单元R[0]*/
	 for(i=n;i>=1;i--)
		 R[i]=R[i-1];
	 /*进行n-1趟选择排序*/
   for(i=1;i<n;i++)
   {
   	 /* 做第i趟排序(1≤i≤n-1) */
   	 /* k记下目前找到的最小元素所在的位置 */
     k=i;
     /* 在当前无序区R[i..n]中选最小的记录R[k] */
     for(j=i+1;j<=n;j++) 
       if(R[j]<R[k])
         k=j; 
       if(k!=i)
       { 
       	 /*交换R[i]和R[k],R[0]作暂存单元使用*/
         R[0]=R[i]; 
         R[i]=R[k]; 
         R[k]=R[0]; 
       } 
     } 
     /*元素复位*/
     for(i=0;i<n;i++)
				R[i]=R[i+1];
} 
/*————————————————————————— 堆排序 ————————————————————————————*/
void HeapAdjust(int *R,int i,int n)
{ 
	 /*对R[1..n]进行堆调整*/
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
{ /* 对R[1..n]进行堆排序，用R[0]做暂存单元*/
    int i;
    /*空出暂存单元R[0]*/
	  for(i=n;i>=1;i--)
		 R[i]=R[i-1];
    /* 将R[1-n]建成初始堆*/
    for(i=n/2;i>0;i--)
      HeapAdjust(R,i,n); 
    /*进行n-1趟堆排序*/
    for(i=n;i>1;i--)
    { 
    	/* 将堆顶和堆中最后一个记录交换 */
    	R[0]=R[1]; 
    	R[1]=R[i];
    	R[i]=R[0]; 
    	/* 将R[1]..R[i-1]重新调整为堆*/
    	HeapAdjust(R,1,i-1); 
    }
    /*元素复位*/
    for(i=0;i<n;i++)
			R[i]=R[i+1];
} 
int main()
{
	/*排序使用的数组*/
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
    /*输出插入排序的结果*/
	  for(i=0;i<10;i++)
		  printf("%3d",R[i]);
		printf("\n");
	}
}