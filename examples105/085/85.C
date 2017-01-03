#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/string.h> 
#include <linux/fs.h> 
#include <linux/malloc.h> 
#include <asm/unistd.h> 
#include <sys/syscall.h> 
#include <asm/fcntl.h> 
#include <asm/errno.h> 
#include <linux/types.h> 
#include <linux/dirent.h> 


static int  __init regist_device(void);
static void  __exit unregist_device(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define DEVICE_NAME "MyDevDriver" /*设备名同在文件夹/proc/devices中的相同*/
#define DEVICE_NUM 300;
#define MESS_LEN 80 /*从设备获取消息的最大长度*/

static int Major; /*分配给设备的主设备号*/
static int Already_Open = 0; /*设备已打开标志*/
static char msg[MESS_LEN]; /* The msg the device will give when asked */
static char *msg_Ptr;

static struct file_operations fops = {/*注意这里需要是静态变量, 不然会出现内核访问错误情况*/
	.read = device_read,/*将函数指针赋值给file_operations结构，添加驱动程序*/ 
	.write = device_write,
	.open = device_open,
	.release = device_release
}; 

static int __init regist_device(void)
{
	Major = register_chrdev(DEVICE_NUM, DEVICE_NAME, &fops);/*在系统中注册该设备驱动*/
	if (Major < 0) {
		printf ("Registering the character device failed with %d\n", Major);
		return Major;
	}
	else Major = DEVICE_NUM;
	return 0;
}


static void __exit unregist_device(void)/*取消注册，设备可以unload*/
{
	int ret = unregister_chrdev(Major, DEVICE_NAME);
	if (ret < 0) printf("Error in unregister_chrdev: %d\n", ret);
} 

static int device_open(struct inode *inode, FILE *fp)
{
	static int counter = 0;
	if (Already_Open) 
		return -EBUSY;
	Device_Open++;
	sprintf(msg);
	msg_Ptr = msg;
	printf("device_open call");
	return 0;
}

static int device_release(struct inode *inode, FILE *fp)
{
	Device_Open --;/*释放设备*/
	printf("device_release call\n");
	return 0;
}

static ssize_t device_read(FILE *fp,char *buffer, size_t length,loff_t *offset)
{/*最后一个为文件偏移量*/
	int n_read = 0;/
	if (*msg_Ptr == 0)/*消息为空则返回*/ 
		return 0;
	while (length && *msg_Ptr)
	{
	/*内核空间与用户空间内存是不同的,所以需要使用内存操作函数 而不可以直接赋值*/
		put_user(*(msg_Ptr++), buffer++);
		length--;
		n_read++;
	}
	return n_read;/*返回所读字节数*/
}

static ssize_t device_write(FILE *fp,const char *buffer,size_t len,loff_t *offset)
{/*最后一个为文件偏移量*/
	int n_write = 0;/
	while (length)
	{
		putc(buffer++,fp);
		length--;
		n_write++;
	}
	return n_write;/*返回所写字节数*/
}  

module_init(regist_device);
module_exit(unregist_device);

