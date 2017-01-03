#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#define PI 3.1415926 
int 	A=50;
float w=0.2;
/*(X,Y)是小球运动轨迹的坐标点*/
double Y=0.0,X=10.0;
char ch;
/*R为球体半径，longitude、latitude分别为半径与经纬线的夹角*/
void Ball(float R,int longitude,int latitude)
{    
 /*定义旋转变换前点坐标数组x,y,z.以及旋转变换后点坐标数组x1,z1*/
 float x[4],y[4],z[4],x1[4],z1[4];    
 int i,j,k;
 /*定义坐标转换后的屏幕坐标数组sx,sy*/
 float sx[4],sy[4];
 /*定义存放了5个顶点坐标序列的数组*/
 int fillcolor[10];  
 double a1,a2,b1,b2,c,d,yn;
 /*设置每次旋转的角度*/
 c=longitude*PI/180.0;  
 d=latitude*PI/180.0;
 cleardevice();
 for(j=0;j<180;j=j+20)
 {
   a1=j*PI/180.0;
   a2=(j+20)*PI/180.0;
   for(i=0;i<360;i=i+20)
   {
    b1=i*PI/180;
    b2=(i+20)*PI/180;
    /*求出图形旋转前点的坐标*/
    x[0]=R*sin(a1)*cos(b1);y[0]=R*sin(a1)*sin(b1);z[0]=R*cos(a1);
    x[1]=R*sin(a2)*cos(b1);y[1]=R*sin(a2)*sin(b1);z[1]=R*cos(a2);
    x[2]=R*sin(a2)*cos(b2);y[2]=R*sin(a2)*sin(b2);z[2]=R*cos(a2);
    x[3]=R*sin(a1)*cos(b2);y[3]=R*sin(a1)*sin(b2);z[3]=R*cos(a1);
    /*求出图形旋转后点的坐标*/
    for(k=0;k<4;k++)    
    {
     	x1[k]=x[k]*cos(c)-y[k]*sin(c);
     	z1[k]=-x[k]*sin(c)*sin(d)-y[k]*cos(c)*sin(d)+z[k]*cos(d);
     	/*将三维坐标转化为屏幕坐标*/
      sx[k]=100-x1[k];  
      sy[k]=100-z1[k];
  	}
    yn=-(x1[2]-x1[0])*(z1[3]-z1[1])+(x1[3]-x1[1])*(z1[2]-z1[0]);
    /*对可见部分进行画线，实现消隐*/
    if(yn>=0.0)   
    {
      moveto(sx[0],sy[0]);
      lineto(sx[1],sy[1]);
      lineto(sx[2],sy[2]);
      lineto(sx[3],sy[3]);
      lineto(sx[0],sy[0]);
      fillcolor[0]=(int)sx[0],fillcolor[1]=(int)sy[0];
      fillcolor[2]=(int)sx[1],fillcolor[3]=(int)sy[1];
      fillcolor[4]=(int)sx[2],fillcolor[5]=(int)sy[2];
      fillcolor[6]=(int)sx[3],fillcolor[7]=(int)sy[3];
      fillcolor[8]=(int)sx[0],fillcolor[9]=(int)sy[0];
      setfillstyle(1,WHITE);
      /*用当前颜色填充多边形*/
      fillpoly(5,fillcolor);  
    }
   }
 }
} 
/*轨迹方程函数*/ 
void Track()        
{ 
	X+=10.0;
 	Y=200-A*sin(w*X);
 	/*控制球体运动的最大坐标*/
 	if(X>=500&&Y>=400) 
 	{
 		X=10.0;
 		Y=0.0;
 	} 
}
int main()
{
	int gdrive=DETECT,gmode,k,t,i=0;
  int size; void *buf[10];
  initgraph(&gdrive,&gmode,"e:\\tc");
  setcolor(GREEN);  
  for(k=36;k<=360;k=k+36)
  {
  	/*调用Ball函数*/
   	Ball(50,k,k);  
   	size=imagesize(50,40,150,150); 
 		/*将保护位图象所需的字节数赋值给size*/
    if(size!=-1)
     	buf[i]=malloc(size);    /* 分配size字节的内存空间*/
    if(buf[i])
    	getimage(50,40,150,150,buf[i]);  
		/*在屏幕指定的位置将一个位图保存到内存*/
		i++;
  }
  cleardevice();
  for(t=0;t<=40;t++)
  {  
  	cleardevice();
  	/*在指定位置以拷贝形式输出一个位图*/
    putimage(X,Y,buf[t%10],COPY_PUT);  
		/*设置球运动的时间间隔*/
    delay(100);
 		Track();
  }
  /*释放内存空间*/
 	for(i=0;i<10;i++)
  	free(buf[i]);    
  getch();
  closegraph();
  return 0;
}     
