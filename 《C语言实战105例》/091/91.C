#include <conio.h>
#include <stdlib.h>
#include <graphics.h>

/*定义游戏级别*/
#define GRADE1 800 /*级别1的延时*/
#define GRADE2 400 /*级别2的延时*/
#define GRADE3 200 /*级别3的延时*/
#define GRADE4 100 /*级别4的延时*/
#define WINSCORE 50 /*成功游戏的分数*/

char ascKey[36];
int blosKey[36] = {0xb30,0x231,0x332,0x433,0x534,0x635,0x736,0x837,0x938,0xa39,0x1e61,0x3062,
		           0x2e63,0x2064,0x1265,0x2166,0x2267,0x2368,0x246a,0x1769,0x256b,0x266c,0x326d,0x316e,
		           0x186f,0x1970,0x1071,0x1372,0x1f73,0x1474,0x1675,0x2f76,0x1177,0x2d78,0x1579,0x2c7a};
int delayTime;
/*图形初始化*/
void InitGraphics()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"c:\\tc");
}
/*初始化游戏*/
void InitGame()
{
	int gameGrade;
	int i = 15;
	cleardevice();
	gotoxy(25,10);printf("Welcome to the hit Game\n");
	gotoxy(30,i++);printf("please choose the grade:");
	gotoxy(30,i++);printf(" 1 : grade1\n");
	gotoxy(30,i++);printf(" 2 : grade2\n");
	gotoxy(30,i++);printf(" 3 : grade3\n");
	gotoxy(30,i++);printf(" 4 : grade4\n");
	gameGrade = getch();
	switch(gameGrade)
	{
		case '1' :delayTime = 3000;break;
		case '2' :delayTime = 2000;break;
		case '3' :delayTime = 1000;break;
		case '4' :delayTime = 5000;break;
		default:delayTime = 3000;break;
	}
	 /*初始化ascKey数组*/
	 for(i=0;i<10;i++)ascKey[i]=48+i;
	 for(i=10;i<36;i++)ascKey[i]=55+i;
	 ascKey[i]=0;
	 cleardevice();
	 /*游戏界面初始化*/
	 for(i=1;i<81;i++) 
	 {
		 gotoxy(i,3);printf("_");
		 gotoxy(i,20);printf("_");
	 }
	 gotoxy(30,2);printf("score:");
}
void PlayGame()
{
	int i,j,x,key,score=0;
	randomize();
	while(1)
	{
		gotoxy(40,2);printf("%d",score);
		i = rand()%80; /* 随机生成产生字符的位置 */
		if(i==0)i=1;
		x = rand()%36; /* 随机生成一个字符 */
		for(j=4;!kbhit()&&j!=20;j++)
		{
			gotoxy(i,j);printf("%c",ascKey[x]);gotoxy(i,j);
			delay(delayTime);
			if(score == WINSCORE) /*游戏胜利*/
			{
			   cleardevice();
			   gotoxy(20,12);printf("You Win!");
			   delay(100000);
			   exit(1);
			}
			gotoxy(i,j);printf(" ");gotoxy(i,j);
		}
		if(j == 20)/*超时相当于没有真确按键*/
		{score--;continue;}
		key = bioskey(0);/*接收键值*/
		if(key==0x011b) /*如果是ESC则推出程序*/
		  break;
		if(key==blosKey[x])/*命中则加分*/
		{score++;continue;}
		score--;/*没有命中则减分*/
	}
}
int main()
{
	 InitGraphics();
	 InitGame();
	 PlayGame();
	 closegraph();
	 return 0;
}

