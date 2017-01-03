#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
struct SYSTEMINFO
{
	 unsigned char current_second;      /*当前系统时间（秒）*/
	 unsigned char alarm_second;        /*闹钟时间（秒）*/
	 unsigned char current_minute;      /*当前系统时间（分）*/
	 unsigned char alarm_minute;        /*闹钟时间（分）*/
	 unsigned char current_hour;        /*当前系统时间（小时）*/
	 unsigned char alarm_hour;          /*闹钟时间（小时）*/
	 unsigned char current_day_of_week; /*当前系统时间（星期几）*/
	 unsigned char current_day;         /*当前系统时间（日）*/
	 unsigned char current_month;       /*当前系统时间（月）*/
	 unsigned char current_year;        /*当前系统时间（年）*/
	 unsigned char status_registers[4]; /*寄存器状态*/
	 unsigned char diagnostic_status;   /*诊断位*/
	 unsigned char shutdown_code;				/*关机代码*/
	 unsigned char drive_types;					/*驱动类型*/
	 unsigned char reserved_x;          /*保留位*/
	 unsigned char disk_1_type;					/*硬盘类型*/
	 unsigned char reserved;						/*保留位*/
	 unsigned char equipment;						/*设备号*/
	 unsigned char lo_mem_base;					
	 unsigned char hi_mem_base;
	 unsigned char hi_exp_base;
	 unsigned char lo_exp_base;
	 unsigned char fdisk_0_type;				/*软盘驱动器0类型*/
	 unsigned char fdisk_1_type;				/*软盘驱动器1类型*/
	 unsigned char reserved_2[19];			/*保留位*/
	 unsigned char hi_check_sum;
	 unsigned char lo_check_sum;
	 unsigned char lo_actual_exp;
	 unsigned char hi_actual_exp;
	 unsigned char century;							/*世纪信息*/
	 unsigned char information;
	 unsigned char reserved3[12];				/*保留位*/
};
int main()
{
	struct SYSTEMINFO systeminfo;
	int i,size;
	char *ptr_sysinfo,byte;
	clrscr();
	puts("****************************************");
	puts("*      This program will get the       *");
	puts("* configure information of your system *");
	puts("****************************************");
	/*计算变量systeminfo所占的字节数*/
	size=sizeof(systeminfo);
	ptr_sysinfo=(char*)&systeminfo;
	for(i=0;i<size;i++)
	{
	    outportb(0x70,i);
	    byte=inportb(0x71);
	    /*以字节为单位依次为变量SYSTEMINFO赋值*/
	    *ptr_sysinfo++=byte;
	}
    printf("--The shutdown type  is: %d.\n", systeminfo.shutdown_code);
	printf("--The hard disk type is: %d.\n", systeminfo.disk_1_type);
	printf("--The drive type     is: %d.\n", systeminfo.drive_types);
	printf("--The equipment_num  is: %d.\n", systeminfo.equipment);
	printf("--The current date   is: %x/%x/0%x.\n",systeminfo.current_day,systeminfo.current_month,systeminfo.current_year);
	printf("--The current time   is: %x:%x:%x.\n", systeminfo.current_hour,systeminfo.current_minute,systeminfo.current_second);
	printf("--The century        is: %x.\n",systeminfo.century);
	printf("--The alarm time     is: %x:%x:%x.\n", systeminfo.alarm_hour,systeminfo.alarm_minute,systeminfo.alarm_second);
	getch();
	return 0;
}
