#include<stdio.h>
#include<math.h>
#include<graphics.h>
#define PI 3.14159
void main()
{
    float t;
    int x0=320,y0=240;
    int n=30,i,j;
    int x[50],y[50];
    int gdriver=DETECT,gmode;
    initgraph(&gdriver,&gmode,"e:\\tc");    /*设置图形方式初始化*/
    cleardevice();       /*清屏*/
    setbkcolor(BLACK);     /*设置缘景为白色*/
    setcolor(RED);        /*设置绘图色为红色*/
    t=2*PI/n;
    for(i=0;i<n;i++)     /*利用数学公式计算端点坐标值*/
    {   x[i]=100*cos(i*t)+x0;
        y[i]=100*sin(i*t)+y0;
    }
    for(j=1;j<n;j++)
            line(x[j-1],y[j-1],x[j],y[j]);
    line(x[n-1],y[n-1],x[0],y[0]); 
    getch();
    closegraph();
} 
