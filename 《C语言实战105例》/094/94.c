#include<stdio.h>
#include<stdlib.h> 
#include<graphics.h> 
#include<bios.h>
/*���涨����һЩ��������*/
/*�ػ���������*/
#define CMDDRAW       5 
/*��ȥһ�����е�����*/
#define CMDDELLINE    6 
/*�Զ�����һ�е�����*/
#define CMDAOTODOWN   7 
/*�����µķ���*/
#define CMDGEN        8 
/*�����ƶ�����������ͷ<-���ƣ�����ASCII��ֵ��75*/
#define CMDLEFTMOVE   75 
/*�����ƶ���������Ҽ�ͷ->���ƣ�����ASCII��ֵ��77*/
#define CMDRINGHTMOVE 77 
/*��ת���������Կո�������*/
#define CMDROTATE     57 
/*�����ƶ�����������µļ�ͷ���ƣ�����ASCII��ֵ��80*/
#define CMDDOWNMOVE   80 
/*�˳���Ϸ�Ŀ��������esc�����ƣ�����ASCII��ֵ��1*/
#define CMDESC        1 

/*�����˷����½���ʱ����*/
#define TIMEINTERVAL  4 

/*���涨������Ϸ���Ĵ�С*/
#define MAXWIDTH      15 
#define MAXHEIGHT  		30 
/*��ɷ����С���ӵĿ��*/
#define BOXWIDTH      15 

/*��������������ʾ�¾�����������Ϸ��*/
int oldarea[MAXHEIGHT+1][MAXWIDTH]; 
int area[MAXHEIGHT+1][MAXWIDTH]; 
/*����һ����Ҫ�ı����Ļ���򣬳���֮��������ý����ػ�*/
int actW,actH,actX,actY; 
/*��ǰ�����һЩ���ԣ����꣬��ɫ���ߣ���*/
int curX,curY,curColor,curW,curH; 
/*�µķ����һЩ���ԣ����꣬��ɫ���ߣ���*/
int newX,newY,newColor,newW,newH; 
/*�ƶ������״̬*/
int active; 
/*�洢��ǰ���������*/
int box[4][4]; 
/*��ǰ�������ɫ*/
int BOXCOLOR; 
/*��������*/
int CMD; 
/*�������ֻ����ķ�����״*/
int BOX[7][4][4]={ 
 {{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
 {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}} 
}; 
/*�õ�����Ŀ�ȣ������������һ�����յ���*/
int GetWidth() 
{ 
	int i,j; 
	for(i=3;i>0;i--) 
	for(j=0;j<4;j++) 
		if(box[j][i]) return i; 
	return 0; 
} 
/*�õ�����ĸ߶ȣ��������µ�һ�����յ���*/
int GetHeight() 
{ 
	int i,j; 
 	for(j=3;j>0;j--) 
  for(i=0;i<4;i++) 
   	if(box[j][i]) return j; 
 	return 0; 
} 
/*���ԭ�еķ���ռ�еĿռ�*/
void ClearOldspace() 
{ 
 	int i,j; 
 	for(j=0;j<=curH; j++) 
  for(i=0;i<=curW; i++) 
   	if(box[j][i]) 
    	area[curY+j][curX+i]=0; 
} 
/*��λ�·����λ��*/
void PutNewspace() 
{ 
 	int i,j; 
 	for(j=0;j<=newH;j++) 
  for(i=0;i<=newW;i++) 
   	if(box[j][i]) 
    	area[newY+j][newX+i]=BOXCOLOR; 
} 
/*�жϷ�����ƶ��Ƿ���������ͻ*/
int MoveCollision(int box[][4]) 
{ 
 	int i,j; 
 	if(newX<0) return 1; 
 	if(newX+newW>=MAXWIDTH) return 1; 
 	if(newY<0) return 1; 
 	for(j=0;j<=newH;j++) 
  	for(i=0;i<=newW;i++) 
   		if(area[newY+j][newX+i]&&box[j][i]) return 1; 
 	return 0; 
} 
/*�жϷ�ת�����Ƿ��������ĳ�ͻ*/
int RotateBoxCollision(int box[][4]) 
{ 
 	int i,j; 
 	if(newX+newW>=MAXWIDTH) newX=MAXWIDTH-1-newW; 
 	if(newY+newH>=MAXHEIGHT) newY=MAXHEIGHT-1-newH; 
 	if(MoveCollision(box)) return 1; 
 	for(i=0;i<=newW;i++) 
  	for(j=0;j<=newH;j++) 
   	if(area[newY+j][newX+i]) 
   	{ 
    	newX-=newW-i+1; goto L; 
   	} 
 	L: return MoveCollision(box); 
} 
/*��Ϸ����*/
int GameOver() 
{ 
 	if(!active &&(curY+curH>MAXHEIGHT-3)) 
 		return 1; 
 	else 
 		return 0; 
} 
/*�ж��Ƿ�ʱ�����Ƿ񳬹������ʱ����*/
int TimeOut() 
{ 
 	static long tm,old; 
 	tm=biostime(0,tm); 
 	if(tm-old<TIMEINTERVAL) 
 		return 0; 
 	else 
 	{ 
 		old=tm; 
 		return 1; 
 	} 
} 
/*�ػ���Ϸ��*/
void DrawSpace() 
{ 
 	int row,col,x1,y1,x2,y2; 
 	for(row=actY;row<=actY+actH;row++) 
  for(col=actX;col<=actX+actW;col++) 
   	if(area[row][col]!=oldarea[row][col]) 
   	{ 
    	if(area[row][col]==0) 
     		setfillstyle(SOLID_FILL,BLACK); 
    	else 
     		setfillstyle(SOLID_FILL,BOXCOLOR); 
			x1=56+col*BOXWIDTH;
			x2=x1+BOXWIDTH; 
    	y1=464-(row+1)*BOXWIDTH; 
    	y2=y1+BOXWIDTH; 
    	bar(++x1,++y1,--x2,--y2); 
    	oldarea[row][col]=area[row][col]; 
  	} 
	CMD=0; 
} 
/*��ȥ����*/
void ClearFullline() 
{ 
 	int row,col, rowEnd,full,i,j; 
 	rowEnd=newY+newH; 
 	if(rowEnd>=MAXHEIGHT-1) 
 		rowEnd=MAXHEIGHT-2; 
 	for(row=newY; row<=rowEnd;) 
 	{ 
  	full=1; 
  	for(col=0;col<MAXWIDTH;col++) 
   		if(!area[row][col])
   			{full=0; break;} 
  	if(!full)
  	{
  		++row;
  		continue;
  	} 
  	for(j=row; j<MAXHEIGHT-1;j++) 
   	for(i=0;i<MAXWIDTH;i++) 
    	area[j][i]=area[j+1][i]; 
  	actX=0;
  	actY=row; 
  	actW=MAXWIDTH-1;
  	actH=MAXHEIGHT-1-row; 
  	DrawSpace(); 
  	rowEnd--; 
 	} 
 	CMD=CMDGEN; 
} 
/*�����ƶ�����*/
int MoveLeft() 
{ 
 	newX=curX-1; 
 	ClearOldspace(); 
 	if(MoveCollision(box)) 
 	{ 
  	newX=curX; 
  	PutNewspace(); 
  	CMD=0; 
  	return 0; 
 	} 
 	PutNewspace(); 
 	actW=curW+1; 
 	actX=curX=newX; 
 	CMD=CMDDRAW; 
 	return 1; 
} 
/*�����ƶ�����*/
int MoveRight() 
{ 
 	newX=curX+1; ClearOldspace(); 
 	if(MoveCollision(box)) 
 	{ 
 	 	newX=curX; 
 	 	PutNewspace(); 
  	CMD=0; 
  	return 0; 
 	} 
 	PutNewspace(); 
 	actW=curW+1; 
 	actX=curX;
 	curX=newX; 
 	CMD=CMDDRAW; 
 	return 1; 
} 
/*�����ƶ�����*/
int MoveDown() 
{ 
 	int i,j; 
 	newY=curY-1; 
 	ClearOldspace(); 
 	if(MoveCollision(box)) 
 	{ 
 	 	newY=curY; 
  	PutNewspace(); 
  	active=0; 
  	CMD=CMDDELLINE; 
  	return 0; 
 	} 
 	PutNewspace(); 
 	actH=curH+1; 
 	actY=newY; 
 	curY=newY; 
 	CMD=CMDDRAW; 
 	return 1; 
} 
/*�����ټ��󷽿�Ѹ�����䵽��*/
void MoveBottom() 
{ 
 	while(active) 
 	{ 
 	 	MoveDown(); 
 	 	DrawSpace(); 
 	} 
 	CMD=CMDDELLINE; 
} 
/*��ʼ��*/
void InitialGame() 
{ 
 	int i,j,x1,y1,x2,y2; 
 	int driver=DETECT, mode=0; 
 	initgraph(&driver,&mode,"e:\\tc"); 
 	cleardevice(); 
 	randomize(); 
 	setfillstyle(SOLID_FILL,BLUE); 
 	bar(0,0,639,479); 
 	x1=56; 
 	y1=464-BOXWIDTH*MAXHEIGHT; 
 	x2=56+MAXWIDTH*BOXWIDTH; 
 	y2=464; 
 	rectangle(--x1,--y1,++x2,++y2); 
 	setfillstyle(SOLID_FILL,BLACK); 
 	bar(++x1,++y1,--x2,--y2); 
 	y1=464-MAXHEIGHT*BOXWIDTH; y2=464; 
 	setcolor(DARKGRAY); 
 	for(i=0;i<MAXWIDTH;i++) 
 	{ 
  	x1=56+i*BOXWIDTH; 
  	line(x1,y1,x1,y2); 
 	} 
	x1=56; x2=x1+MAXWIDTH*BOXWIDTH; 
 	for(j=0;j<MAXHEIGHT;j++) 
 	{ 
  	y1=464-j*BOXWIDTH; 
 	 	line(x1,y1,x2,y1); 
 	} 
 	for(j=0;j<MAXHEIGHT;j++) 
  for(i=0;i<MAXWIDTH;i++) 
   	area[j][i]=oldarea[j][i]=0; 
 	actX=0; actY=0; actW=MAXWIDTH-1; actH=MAXHEIGHT-1; 
 	DrawSpace(); 
 	CMD=CMDGEN; 
}
/*�õ���������*/ 
void GetCMD() 
{ 
 	if(CMD) return; 
 	if(TimeOut()) 
 	{ 
  	CMD=CMDAOTODOWN; 
  	return; 
 	} 
 	if(bioskey(1)) 
 	{ 
  	CMD=bioskey(0)>>8; 
  	return; 
 	} 
} 
/*����һ���µķ���*/
int GenerateNewbox() 
{ 
 int i,j,boxidx; 
 boxidx=random(7); BOXCOLOR=random(7)+1; 
 for(j=0;j<4;j++) 
  for(i=0;i<4;i++) 
   box[j][i]=BOX[boxidx][j][i]; 
 curW=GetWidth(); curH=GetHeight(); 
 curX=(MAXWIDTH+curW)/2; 
 if(curX+curW>=MAXWIDTH)curX=MAXWIDTH-1-curW; 
 curY=MAXHEIGHT-1-curH; 
 newX=curX; newY=curY; actX=curX;actY=curY; 
 actW=newW=curW; actH=newH=curH; 
 active=1; 
 if(MoveCollision(box)) return 0; 
 PutNewspace(); 
 DrawSpace(); CMD=0; 
 return 1; 
} 
/*��ת����*/
int RotateBox() 
{ 
 	int newBox[4][4]; 
 	int i,j; 
 	ClearOldspace(); 
 	for(j=0;j<4;j++) 
  for(i=0;i<4;i++) 
   	newBox[j][i]=0; 
 	for(j=0;j<4;j++) 
  for(i=0;i<4;i++) 
   	newBox[curW-i][j]=box[j][i]; 
 	newW=curH; 
 	newH=curW; 
 	if(RotateBoxCollision(newBox)) 
 	{ 
  	newW=curW; 
  	newH=curH; 
  	newX=curX; 
  	newY=curY; 
  	PutNewspace(); 
  	CMD=0; 
  	return 0; 
 	} 
 	for(j=0;j<4;j++) 
  for(i=0;i<4;i++) 
   	box[j][i]=newBox[j][i]; 
 	PutNewspace(); 
 	actH=newH>curH? newH:curH; 
 	actW=curX+actH-newX; 
 	actX=newX; 
 	actY=newY; 
 	curX=newX; 
 	curY=newY; 
 	curW=newW;
 	curH=newH; 
 	CMD=CMDDRAW; 
 	return 1; 
} 
/*���ݻ�õ�������ִ�в�ͬ�Ĳ���*/
void ExecuteCMD() 
{ 
 	switch(CMD) 
 	{ 
  	case CMDLEFTMOVE:  
  		MoveLeft();
  		break; 
  	case CMDRINGHTMOVE: 
  		MoveRight();
  		break; 
  	case CMDAOTODOWN: 
  		MoveDown();
  		break; 
  	case CMDROTATE: 
  		RotateBox();
  		break; 
  	case CMDDOWNMOVE:  
  		MoveBottom(); 
  		break; 
  	case CMDDRAW:  
  		DrawSpace();
  		break; 
  	case CMDDELLINE:  
  		ClearFullline();
  		break; 
  	case CMDGEN:   
  		GenerateNewbox();
  		break; 
  	case CMDESC:   
  		closegraph();
  		return 0; 
  	default:     
  		CMD=0; 
 } 
}
/*������*/ 
int main() 
{ 
 	int i; 
 	InitialGame(); 
 	do 
 	{ 
  	GetCMD(); 
  	ExecuteCMD(); 
 	} 
 	while(!GameOver()); 
 	getch(); 
 	closegraph(); 
 	return 0;
} 