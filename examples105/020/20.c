#include<stdio.h>
#define MAX_STATION_NUM 32 /*�����������Ĵ��͵���Ŀ*/
void main()
{
    int k,i;                
    float wDistance;       /*wDistance���յ�����ǰ���͵�ľ���*/
    float storedOil[MAX_STATION_NUM];/*storedOil[i]�ǵ�i�����͵�Ĵ�����*/
    float distance[MAX_STATION_NUM]; /*distance[i]�ǵ�i�����͵㵽�յ�ľ���*/
    clrscr();
    puts("***********************************************");
    puts("*         this program will solve             *");
    puts("*       the problem about storing oil         *");
    puts("***********************************************");
    puts("The whole distance is 1000km,and the result is:\n");
    puts("station     distance(km)    oil(l)");
    k=1;
    wDistance=500;        /*��i=1����ʼ��ʼ�㵹��*/
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
    distance[k]=1000;        /*��ʼ�����յ�ľ���ֵ*/
    storedOil[k]=(1000-distance[k-1])*(2*k+1)+storedOil[k-1];    /*��ʼ�������*/
    for(i=0;i<k;i++)       /*��ʼ�㿪ʼ��һ��ӡʼ������ǰ���͵�ľ���Ͳ�����*/
        printf("%4d        %6.3f         %6.3f\n",i,1000-distance[k-i],storedOil[k-i]);
    getch();
}
