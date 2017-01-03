#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
struct SYSTEMINFO
{
	 unsigned char current_second;      /*��ǰϵͳʱ�䣨�룩*/
	 unsigned char alarm_second;        /*����ʱ�䣨�룩*/
	 unsigned char current_minute;      /*��ǰϵͳʱ�䣨�֣�*/
	 unsigned char alarm_minute;        /*����ʱ�䣨�֣�*/
	 unsigned char current_hour;        /*��ǰϵͳʱ�䣨Сʱ��*/
	 unsigned char alarm_hour;          /*����ʱ�䣨Сʱ��*/
	 unsigned char current_day_of_week; /*��ǰϵͳʱ�䣨���ڼ���*/
	 unsigned char current_day;         /*��ǰϵͳʱ�䣨�գ�*/
	 unsigned char current_month;       /*��ǰϵͳʱ�䣨�£�*/
	 unsigned char current_year;        /*��ǰϵͳʱ�䣨�꣩*/
	 unsigned char status_registers[4]; /*�Ĵ���״̬*/
	 unsigned char diagnostic_status;   /*���λ*/
	 unsigned char shutdown_code;				/*�ػ�����*/
	 unsigned char drive_types;					/*��������*/
	 unsigned char reserved_x;          /*����λ*/
	 unsigned char disk_1_type;					/*Ӳ������*/
	 unsigned char reserved;						/*����λ*/
	 unsigned char equipment;						/*�豸��*/
	 unsigned char lo_mem_base;					
	 unsigned char hi_mem_base;
	 unsigned char hi_exp_base;
	 unsigned char lo_exp_base;
	 unsigned char fdisk_0_type;				/*����������0����*/
	 unsigned char fdisk_1_type;				/*����������1����*/
	 unsigned char reserved_2[19];			/*����λ*/
	 unsigned char hi_check_sum;
	 unsigned char lo_check_sum;
	 unsigned char lo_actual_exp;
	 unsigned char hi_actual_exp;
	 unsigned char century;							/*������Ϣ*/
	 unsigned char information;
	 unsigned char reserved3[12];				/*����λ*/
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
	/*�������systeminfo��ռ���ֽ���*/
	size=sizeof(systeminfo);
	ptr_sysinfo=(char*)&systeminfo;
	for(i=0;i<size;i++)
	{
	    outportb(0x70,i);
	    byte=inportb(0x71);
	    /*���ֽ�Ϊ��λ����Ϊ����SYSTEMINFO��ֵ*/
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