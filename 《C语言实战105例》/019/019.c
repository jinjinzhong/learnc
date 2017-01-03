#include<stdio.h>
#include<stdlib.h>

#define MAX_VEX_NUM 6
#define MAX_INT 1024
#define TRUE 1
#define FALSE 0
#define NOTHING -1

int arcs[MAX_VEX_NUM][MAX_VEX_NUM] = {{MAX_INT,MAX_INT,10,MAX_INT,30,100},{MAX_INT,MAX_INT,5,MAX_INT,MAX_INT,MAX_INT},{MAX_INT,MAX_INT,MAX_INT,50,MAX_INT,MAX_INT},{MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,10},{MAX_INT,MAX_INT,MAX_INT,20,MAX_INT,60},{MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT,MAX_INT}};

int D[MAX_VEX_NUM] = {0,0,0,0,0,0};
int final[MAX_VEX_NUM] = {0,0,0,0,0,0};
int previous[MAX_VEX_NUM] = {-1,-1,-1,-1,-1,-1};

void ShortestPath()
{
    int i, j, min, v;
    /*初始化*/
    for(i = 0;i<MAX_VEX_NUM;i++)
    {
    	D[i] = arcs[0][i];
	    final[i] = FALSE;
	    previous[i] =  NOTHING;
    }
    D[0] = 0;
    final[0] = TRUE;             /* 初始化v0顶点属于S集 */
    for(i =1;i<MAX_VEX_NUM ;i++) /*进行MAX_VEX_NUM -1 次循环*/
    {
    	min = MAX_INT;             /* 当前所知据v0的最短距离 */
	    for(j = 0;j<MAX_VEX_NUM;j++)
	    {
	       if(final[j]==FALSE)
	    	 {
	    		  if(min > D[j])
	    		  {
	    			  min = D[j];
				      v = j;             
	    		  }
	    	 }
	    }
	    final[v] = TRUE;
	    D[0] = 0;
	    if(i==1)
	    {
	    	previous[v] = 0;
	    }
	    for(j = 0;j<MAX_VEX_NUM;j++)
	    {
	       if(!final[j])/* 第j个顶点在V-S中 */
	    	 {
	    		  if(D[j] > (arcs[v][j] + min))
	    		  {
	    			  D[j] = arcs[v][j] + min;/*修改 D[j]*/
				      previous[j] = v;
	    		  }
			      else 
			      {
			        if(arcs[0][j] != MAX_INT)
				        previous[j] = 0;
			      }
	       }
	    }
    }
}

void PrintPath(int k)
{
    
    if(previous[k] == -1)
    {
       	printf("\nthere is path!!\n");
    }
	  else
    {	
        if(previous[k] == 0)
	        printf("\n0 -> %d ",k);
	      else
	      {
	        PrintPath(previous[k]);
		      printf(" -> %d ",k);	
	      }
	  }
}
int main()
{
    int i;
    clrscr();
    ShortestPath();
    for(i=1;i<MAX_VEX_NUM;i++)
    {
         printf("the shortest path from v[0] to v[%d] is:",i);    
         PrintPath(i);
         if(D[i] != MAX_INT)
             printf("::[%d]\n",D[i]);
    }
    getch();
    return 0;
}


