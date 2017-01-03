#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <bios.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#define BORDER  1
#define ESC 27
#define REV_VID 0x1e
#define NORM_VID 0x40
char *main_menu[] = 
{
	"F --- 文件管理",
	"D --- 磁盘管理",
	"H --- 打印服务",
	"X --- 退出菜单",
};
char* file_menu[] = 
{
	"S --- 文件显示",
	"P --- 文件打印",
	"C --- 文件拷贝",
	"D --- 文件删除",
	"X --- 返回上级",
};
char* disk_menu[] = 
{
	"B --- BOOT区备份",
	"R --- BOOT区恢复",
	"X --- 返回上级",
};
char* print_menu[] =
{
	"O --- 打印图形",
	"F --- 打印文本",
	"X --- 返回上级",
};
/*将光标移动到指定位置*/
void gotoXY(int x,int y) 
{
	union REGS regs;
	regs.h.ah=2;
	regs.h.dl=x;
	regs.h.dh=y;
	regs.h.bh=0;
	int86(0x10,&regs,&regs);
}
/*将指定区域的视频模式存储到指定的内存中去*/
void SaveVideo(int x1,int x2,int y1,int y2,unsigned int* buffer )
{
	union REGS r;
	register int i, j;
	for( i = y1; i < y2; i++)
		for( j = x1; j < x2; j++ )
		{
			gotoXY(j, i);
			r.h.ah = 8;
			r.h.bh = 0;
			*buffer++ = int86( 0x10, &r, &r );
			putchar(' ');
		}
}
/*在指定的位置显示中文字符*/
void PutChinese( int x, int y, char *p, int attrib ) 
{
	union REGS r;
	while(*p)
	{
		r.h.ah = 2;
		r.h.dl = x++;
		r.h.dh = y;
		int86(0x10, &r, &r);
		r.h.ah = 9;
		r.h.bh = 0;
		r.x.cx = 1;
		r.h.al = *p++;
		r.h.bl = attrib;
		int86( 0x10, &r, &r );
		
	}
}
/*显示边框*/
void DisplayBox(int x1,int y1,int x2,int y2,int attrib) 
{
	unsigned char* boxchar[6] = {"┏","━","┓","┃","┗","┛"};
	register int i;
	for( i = x1; i <= x2; i++ )
	{
		PutChinese( i, y1, boxchar[1], attrib );
		PutChinese( i, y2, boxchar[1], attrib );
	}
	for( i = y1; i <= y2; i++ )
	{
		PutChinese( x1, i, boxchar[3], attrib );
		PutChinese( x2, i, boxchar[3], attrib );
	}
	PutChinese( x1, y1, boxchar[0], attrib );
	PutChinese( x2, y1, boxchar[2], attrib );
	PutChinese( x2, y2, boxchar[5], attrib );
	PutChinese( x1, y2, boxchar[4], attrib );
}
 /*显示菜单项*/
void DisplayMenu(char* menu[],int x,int y,int count )
{
	register int i;
	for( i = 0; i < count; i++, x++)
	{
		gotoXY( x, y );
		cprintf( menu[i]);
	}
}
/*返回字符串中热键的位置*/
int IsIn( char* s, char c) 
{
	register int i;
	for( i = 0; *s; i++ )
		if( *s++ == c ) return i + 1;
	return 0;
}
/*获得用户的响应*/
int GetResponse(int x,int y,int count,char* menu[],char* keys) 
{
	union inkey
	{
		char ch[2];
		int i ;
	} c ;
	int arrow_choice = 0, key_choice;
	y++;
	gotoXY(x, y);
	PutChinese( y, x, menu[0], REV_VID);
	for(;;)
	{
		while(!bioskey(1));
		c.i = bioskey(0);
		gotoXY( x + arrow_choice, y);
		PutChinese( y, x+arrow_choice, menu[arrow_choice], NORM_VID );
		if( c.ch[0] )
		{
			key_choice = IsIn( keys, tolower( c.ch[0] ));
			if( key_choice ) return key_choice - 1;
			switch( c.ch[0] )
			{
			case '\r': return arrow_choice;
			case ' ':  arrow_choice++;
				   break;
			case ESC : return -1;
			}
		}
		else
		{
			switch( c.ch[1] )
			{
			case 72: arrow_choice--;
				 break;
			case 80: arrow_choice++;
				 break;
			}
		}
		if( arrow_choice == count ) arrow_choice = 0;
		if( arrow_choice < 0 ) arrow_choice = count - 1;
		gotoXY( x + arrow_choice, y );
		PutChinese( y, x+arrow_choice, menu[ arrow_choice ], REV_VID );
	}
}
/*恢复原有的视频方式*/
void RestoreVideo(int x1,int x2,int y1,int y2,unsigned char* buffer)
{
	union REGS r;
	register int i, j;
        int startx,starty,endx,endy;
	for( j = startx; j < endx; j++)
		for( j = starty; j < endy; j++ )
		{
			gotoXY(i, j);
			r.h.ah = 9;
			r.h.bh = 0;
			r.x.cx = 1;
			r.h.al = *buffer++;
			r.h.bl = *buffer++;
			int86( 0x10, &r, &r );
		}
}
/*弹出式菜单的显示*/
int PopupMenu(char* menu[],char* keys,int count,int x,int y,int border)
{
	register int i, len;
	int endx, endy, choice;
	unsigned int *p;
	if((x>24)||(x<0)||(y>79)||(y<0))
	{
		printf("范围错");
		return -2;
	}
	len = 0;
	for( i = 0; i < count; i++ )
		if( strlen( menu[i]) > len ) len = strlen( menu[i] );
	endy = len + 2 + y;
	endx = count + 1 + x;
	if((endx+1>24)||(endy+1>79))
	{
		printf("菜单不匹配");
		return -2;
	}
	p = (unsigned int *) malloc((endx-x+1)*(endy-y+1));
	if( !p ) exit(1);
	SaveVideo( x, endx + 1, y, endy+1, p );
	if( border ) DisplayBox( y, x, endy, endx, YELLOW );
	DisplayMenu( menu, x + 1, y + 1, count );
	choice = GetResponse( x + 1, y, count, menu, keys );
	RestoreVideo( x, endx + 1, y, endy + 2, (unsigned char* ) p);
	free( p );
	return choice;
}

void main()
{
	int i, j;
	directvideo = 0;
	for(;;)
	{
		clrscr();
		gotoXY(0, 0);
		textcolor( BLACK  );
		textbackground( RED );
		switch( PopupMenu( main_menu, "fdhx", 4,5, 16, BORDER ))
		{
		case 0:
			clrscr();
			switch( PopupMenu( file_menu, "spcdx", 5, 5, 16, BORDER ))
			{
			case 0:
				clrscr();
				gotoXY( 24, 20 );
				cprintf("你选择了文件显示功能");
				getch();
				break;
			case 1:
				clrscr();
				gotoXY( 24, 20 );
				cprintf("你选择了文件打印功能");
				getch();
				break;
			case 2:
				clrscr();
				gotoXY( 24, 20 );
				cprintf("你选择了文件拷贝功能");
				getch();
				break;
			case 3:
				clrscr();
				gotoXY(24,20);
				cprintf("你选择了文件删除功能");
				getch();
				break;
			case 4:
				break;
			default:
				break;
			}
			break;
		case 1:
			clrscr();
			switch( PopupMenu( disk_menu, "brx", 3, 5, 16, BORDER ))
			{
			case 0:
				clrscr();
				gotoXY(24,20);
				cprintf("你选择了BOOT区备份功能");
				getch();
				break;
			case 1:
				clrscr();
				gotoXY(24,20);
				cprintf("你选择了BOOT区恢复功能");
				getch();
				break;
			case 2:
				break;
			default:
				break;
			}
			break;
		case 2:
			clrscr();
			switch( PopupMenu( print_menu, "of", 3, 5, 16, BORDER ))
			{
			case 0:
				clrscr();
				gotoXY( 24, 20 );
				cprintf("你选择了打印图形功能");
				getch();
				break;
			case 1:
				clrscr();
				gotoXY(24,20);
				cprintf("你选择了打印文本功能");
				getch();
				break;
			case 2:
				break;
			default:
				break;
			}
			break;
		case 3:
		case -1:
			return 0;
		default:
			break;
		}
	}
}