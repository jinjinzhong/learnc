#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h>
/*�������ָ�����Ƽ���ASCII��ֵ*/
#define ESCGAME 	1
#define SHOOT 		57
#define MOVELEFT 	75
#define MOVERIGHT 77
/*����Ǳͧ���ƶ��ٶ�*/
int  speed=300;
/*���̲����õı���*/
char keyState[128],keyPressed[128];
int  score=0;/*�÷�*/
char scorestring[10];/*��������ı���*/
struct bullet/*���׵Ľṹ��*/
{
	int x;
	int y;
	int shoot;/*�Ƿ�������*/
}enemyBullet[6];/*��Ļ�������5�����˿��Է�����*/

/*��ҵĽṹ��*/
struct Player
{
	int x;
	int y;
	struct bullet bullet[6];
	int life;
}Player;

/*���˵Ľṹ��*/
struct Enemy
{
	int x;
	int y;
	int speed;
	int color;
	int direction;
	int life;
}Enemy[6];

/*��������Ϸ*/
void PlayGame(void);	
/*�����*/
void DrawPlayer(void);
/*������*/
void DrawEnemy(int i);
/*���ӵ�,0ȥ��,1��ʾ*/
void DrawPlayerBullet(int x,int y,int n);
/*���ӵ�,0ȥ��,1��ʾ*/
void DrawEnemyBullet(int x,int y,int n);
/*ȥ��ԭ���ط�������*/
void DrawBlack(int x,int y,int color);
/*����÷�*/
void PrintScore();

/*�����ǰ�������*/
int  GetKey(int ScanCode);
void interrupt far (*OldInterupt9Handler)();
void far interrupt NewInterupt9();
/*���ؼ���*/
void InstallKeyboard();
/*�رռ���*/
void ShutDownKeyboard();

void main(void)
{
 	int gd=DETECT,gm;
 	initgraph(&gd,&gm,"e:\\tc");
 	cleardevice();
 	/*���ؼ���*/
 	InstallKeyboard();
 	/*��������Ϸ*/
 	PlayGame();
  /*�رռ���*/
 	ShutDownKeyboard();
 	closegraph();
}
/*�����*/
void DrawPlayer(void)
{
	setfillstyle(SOLID_FILL,RED);
		bar(Player.x-20,Player.y-10,Player.x+20,Player.y);
	setfillstyle(SOLID_FILL,RED);
		bar(Player.x-20,Player.y-10,Player.x-10,Player.y);
}
/*������*/
void DrawEnemy(int i)
{
	setfillstyle(SOLID_FILL,Enemy[i].color);
	bar(Enemy[i].x-20,Enemy[i].y-10,Enemy[i].x+20,Enemy[i].y);
	setfillstyle(SOLID_FILL,GREEN);
	if(Enemy[i].direction==1)
		bar(Enemy[i].x-20,Enemy[i].y-10,Enemy[i].x-10,Enemy[i].y);
	else
		bar(Enemy[i].x+10,Enemy[i].y-10,Enemy[i].x+20,Enemy[i].y);
}
/*ȥ��ԭ���ط�������*/
void DrawBlack(int x,int y,int color)
{
	setfillstyle(SOLID_FILL,color);
	bar(x-20,y-10,x+20,y);
}
/*���ӵ�,0ȥ��,1��ʾ*/
void DrawPlayerBullet(int x,int y,int n)
{
	if(n==0)
		setfillstyle(SOLID_FILL,BLUE);
	else
		setfillstyle(SOLID_FILL,0);
	setcolor(BLUE);
	fillellipse(x,y,5,5);
}
/*���ӵ�,0ȥ��,1��ʾ*/
void DrawEnemyBullet(int x,int y,int n)
{
	if(n==0)
		setfillstyle(SOLID_FILL,BLUE);
	else
		setfillstyle(SOLID_FILL,YELLOW);/*���˵��ڵ��ǻƵ�*/
	setcolor(BLUE);
	fillellipse(x,y,3,3);
}
void PrintScore()/*����÷�*/
{
	setfillstyle(SOLID_FILL,8);/*��ԭ������ȥ��*/
	bar(30,0,200,40);
	setcolor(11);/*����µ÷�*/
	settextstyle(0,0,2);
	sprintf(scorestring,"%d",score);
	outtextxy(30,20,scorestring);
}
void PlayGame(void)/*��������Ϸ*/
{
	int i,j;
	setfillstyle(SOLID_FILL,BLUE);
	bar(0,100,640,480);
	setfillstyle(SOLID_FILL,8);
	bar(0,0,640,99);
	Player.x=200;Player.y=99;/*��ҳ�ʼλ��*/
	for(i=0;i<6;i++)
	{
		Player.bullet[i].shoot=0;/*һ��ʼ���ӵ���Ϊû����״̬*/
		enemyBullet[i].shoot=0;
		Enemy[i].life=0;
	}
	Player.life=1;
	DrawPlayer();/*��ҳ�ʼλ��*/
	PrintScore();/*����÷�*/
	randomize();
	while(1)
	{
	 for(i=0;i<6;i++)/*��������Ƿ��з�����ӵ�*/
	 {
	  if(Player.bullet[i].shoot==1)/*������ӵ�*/
	  {
		 DrawPlayerBullet(Player.bullet[i].x,Player.bullet[i].y,0);/*ȥ��ԭ���ӵ�λ��*/
	   Player.bullet[i].y+=3;
		 DrawPlayerBullet(Player.bullet[i].x,Player.bullet[i].y,1);/*��ʾ��λ��*/
	   for(j=0;j<6;j++)/*�ж��ӵ��Ƿ���е���*/          
			if(Player.bullet[i].x>(Enemy[j].x-22)&&Player.bullet[i].x<(Enemy[j].x+22)&&Player.bullet[i].y>(Enemy[j].y-14)&&Player.bullet[i].y<Enemy[j].y+5)/*���е���*/
	    {
	     Player.bullet[i].shoot=0;/*�ӵ���ʧ*/
	     Enemy[j].life=0;/*������������*/
	     score+=10;/*�÷�����*/
	     DrawPlayerBullet(Player.bullet[i].x,Player.bullet[i].y,0);/*ȥ��ԭ���ӵ�λ��*/
			 DrawBlack(Enemy[j].x,Enemy[j].y,BLUE);/*ȥ������*/
	     PrintScore();
	    }
	   	if(Player.bullet[i].y>480)/*�ӵ�������Ļ�͵�����ʧ*/
	   	{
	    	Player.bullet[i].shoot=0;
	    	DrawPlayerBullet(Player.bullet[i].x,Player.bullet[i].y,0);
	   	}
	  }
	 }
	for(i=0;i<6;i++)/*�����ڵ��Ĳ���*/
	{
	 
	if(Enemy[i].life==1&&Enemy[i].color<14&&enemyBullet[i].shoot==0)/*���˷����ڵ�������*/
	 {
	  enemyBullet[i].shoot=1;
	  enemyBullet[i].x=Enemy[i].x;
	  enemyBullet[i].y=Enemy[i].y-10;
	 }
	}
	for(i=0;i<6;i++)/*�����ڵ��ƶ��Լ��ƶ�*/
	{
	 if(enemyBullet[i].shoot==1)/*�ӵ�����*/
	 {
		 DrawEnemyBullet(enemyBullet[i].x,enemyBullet[i].y,0);
		 enemyBullet[i].y-=2;
		 DrawEnemyBullet(enemyBullet[i].x,enemyBullet[i].y,1);/*�������ڵ���λ��*/
	 }
	 
	if(enemyBullet[i].x>(Player.x-14)&&enemyBullet[i].x<(Player.x+14)&&(enemyBullet[i].y+3)<100)/*�������*/
	 {
		  Player.life=0;
		  enemyBullet[i].shoot=0;
		  DrawEnemyBullet(enemyBullet[i].x,enemyBullet[i].y,0);
		  DrawBlack(Player.x,Player.y,8);/*ȥ�����*/
		  break;
	 }
	 if(enemyBullet[i].y<96)/*�����ڵ������������ʧ*/
	 {
		 enemyBullet[i].shoot=0;
		 setfillstyle(SOLID_FILL,8);
		 setcolor(8);
		 fillellipse(enemyBullet[i].x,enemyBullet[i].y,3,3);
	 }
	}
	delay(speed);/*���ʱ������Լ���*/
	if(Player.life!=1)/*��ұ�����*/
		break;
	for(i=0;i<6;i++)
	{
	 if(Enemy[i].life==0)/*����һ�����˺������ѭ��*/
	 {
		 Enemy[i].life=1;
		 Enemy[i].color=rand()%4+10;/*���˵���ɫ*/
		 Enemy[i].y=rand()%300+130;/*�߶����*/
		 Enemy[i].speed=2+rand()%10;/*���˵��ƶ��ٶ����*/
		
		 Enemy[i].direction=rand()%2;/*���˵��ƶ�����,0���,1�ұ߳���*/
		 if(Enemy[i].direction==0)
		 		Enemy[i].x=-20;
		 else
		 		Enemy[i].x=660;
		 break;
	 }
	}
	if(GetKey(ESCGAME))/*�˳���*/
		break;
	if(GetKey(SHOOT))/*����*/
	{
	 for(i=0;i<6;i++)
	 if(Player.bullet[i].shoot==0)/*����һ���ӵ�������ѭ��*/
	 {
	  	Player.bullet[i].x=Player.x;
	  	Player.bullet[i].y=105;
	  	Player.bullet[i].shoot=1;
	  	break;
	 }
	}
	if(GetKey(MOVERIGHT)&&Player.x<620)/*�Ҽ��̵Ŀ���*/
	{
		DrawBlack(Player.x,Player.y,8);
		Player.x+=10;
		DrawPlayer();
	}
	if(GetKey(MOVELEFT)&&Player.x>20)/*����Ŀ���*/
	{
		DrawBlack(Player.x,Player.y,8);
		Player.x-=10;
		DrawPlayer();
	}
	for(i=0;i<6;i++)/*��ʾ����*/
	{
	 if(Enemy[i].life==1)/*������˴���*/
	 {
	  	DrawBlack(Enemy[i].x,Enemy[i].y,BLUE);/*ԭ��λ�����������ɫ*/
	  	if(Enemy[i].direction==0)
	  	Enemy[i].x+=Enemy[i].speed;/*���˺�����ı仯*/
	  	else
	  	Enemy[i].x-=Enemy[i].speed;
	  	DrawEnemy(i);/*������*/
	  	if(Enemy[i].x>660||Enemy[i].x<-20)/*���˳�����Ļ��Χ����ʧ*/
	  	Enemy[i].life=0;
	 }
	}
	}
	if(Player.life==0)/*������ʧ�ܵĻ�*/
	{
		setcolor(6);
		settextstyle(0,0,3);
		outtextxy(250,40,"GAME OVER");
	}
	while(1)
	{
		/*������Ϸ��ESC*/
		if(GetKey(ESCGAME))
		break;
	}
}

void far interrupt NewInterupt9(void)
{
	 unsigned char ScanCode,temp;
	 ScanCode=inportb(0x60);
	 temp=inportb(0x61);
	 outportb(0x61,temp | 0x80);
	 outportb(0x61,temp & 0x7f);
	 if(ScanCode&0x80)
	 {
	    ScanCode&=0x7f;
	    keyState[ScanCode]=0;
	 }
	 else
	 {
	    keyState[ScanCode]=1;
	    keyPressed[ScanCode]=1;
	 }
	 outportb(0x20,0x20);
}
void InstallKeyboard(void)
{
 	int i;
 	for(i=0;i<128;i++)
 	keyState[i]=keyPressed[i]=0;
 	OldInterupt9Handler=getvect(9);         /*�ж�����ֵ*/
 	setvect(9,NewInterupt9);                
 	/*�жϳ���NewInterupt9��ַ����ָ�����ж���������INT 09H*/
}
void ShutDownKeyboard(void)
{
 	setvect(9,OldInterupt9Handler);
}
int GetKey(int ScanCode)
{
 	int res;
 	res=keyState[ScanCode]|keyPressed[ScanCode];
 	keyPressed[ScanCode]=0;
 	return res;
}



