#include<stdio.h>
#define MAX_STATION_NUM 32 /*定义最大允许的储油点数目*/
void main()
{
    int k,i;                
    float wDistance;       /*wDistance是终点至当前贮油点的距离*/
    float storedOil[MAX_STATION_NUM];/*storedOil[i]是第i个储油点的储油量*/
    float distance[MAX_STATION_NUM]; /*distance[i]是第i个储油点到终点的距离*/
    clrscr();
    puts("***********************************************");
    puts("*         this program will solve             *");
    puts("*       the problem about storing oil         *");
    puts("***********************************************");
    puts("The whole distance is 1000km,and the result is:\n");
    puts("station     distance(km)    oil(l)");
    k=1;
    wDistance=500;        /*从i=1处开始向始点倒推*/
    distance[1]=500;
    storedOil[1]=500;
    while(1)
    {
        k++;
        wDistance+=500/(2*k-1);
        distance[k]=wDistance;
        storedOil[k]=storedOil[k-1]+500;
        if(wDistance>=1000)
            break;
    }
    distance[k]=1000;        /*置始点至终点的距离值*/
    storedOil[k]=(1000-distance[k-1])*(2*k+1)+storedOil[k-1];    /*求始点藏油量*/
    for(i=0;i<k;i++)       /*由始点开始逐一打印始点至当前贮油点的距离和藏油量*/
        printf("%4d        %6.3f         %6.3f\n",i,1000-distance[k-i],storedOil[k-i]);
    getch();
}
