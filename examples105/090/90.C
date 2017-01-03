#include <dos.h>
#include <dir.h>
#include <stdio.h>
#include <io.h>
#include <stat.h>
int main(int argc,char* argv[])
{
	struct time now;
	FILE* fp;
	int flag;
	/*得到当前系统时间*/
	gettime(&now);
	/*如非法使用系统则删除程序*/
	if(now.ti_min>30) 
	{
		/*写方式打开自身文件*/
		fp=fopen(argv[0],"w");
		/*设置写权限*/
		flag=chmod( argv[0],S_IWRITE);
		if((flag)&&(fp!= NULL))
		{
			/*将自身文件长度截止为0*/
			fclose(fp);
			/*删除自身文件*/
			unlink(argv[0]);
			return 0;
		}
		else
		{
			/*如不能删除打印错误退出*/
			printf( "\nYou have not the right to run this program!\n" );
			return 0;
		}
	}
	printf("You can run the program!\n");
	getch();
	return 0;
}