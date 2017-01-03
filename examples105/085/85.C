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

#define DEVICE_NAME "MyDevDriver" /*�豸��ͬ���ļ���/proc/devices�е���ͬ*/
#define DEVICE_NUM 300;
#define MESS_LEN 80 /*���豸��ȡ��Ϣ����󳤶�*/

static int Major; /*������豸�����豸��*/
static int Already_Open = 0; /*�豸�Ѵ򿪱�־*/
static char msg[MESS_LEN]; /* The msg the device will give when asked */
static char *msg_Ptr;

static struct file_operations fops = {/*ע��������Ҫ�Ǿ�̬����, ��Ȼ������ں˷��ʴ������*/
	.read = device_read,/*������ָ�븳ֵ��file_operations�ṹ��������������*/ 
	.write = device_write,
	.open = device_open,
	.release = device_release
}; 

static int __init regist_device(void)
{
	Major = register_chrdev(DEVICE_NUM, DEVICE_NAME, &fops);/*��ϵͳ��ע����豸����*/
	if (Major < 0) {
		printf ("Registering the character device failed with %d\n", Major);
		return Major;
	}
	else Major = DEVICE_NUM;
	return 0;
}


static void __exit unregist_device(void)/*ȡ��ע�ᣬ�豸����unload*/
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
	Device_Open --;/*�ͷ��豸*/
	printf("device_release call\n");
	return 0;
}

static ssize_t device_read(FILE *fp,char *buffer, size_t length,loff_t *offset)
{/*���һ��Ϊ�ļ�ƫ����*/
	int n_read = 0;/
	if (*msg_Ptr == 0)/*��ϢΪ���򷵻�*/ 
		return 0;
	while (length && *msg_Ptr)
	{
	/*�ں˿ռ����û��ռ��ڴ��ǲ�ͬ��,������Ҫʹ���ڴ�������� ��������ֱ�Ӹ�ֵ*/
		put_user(*(msg_Ptr++), buffer++);
		length--;
		n_read++;
	}
	return n_read;/*���������ֽ���*/
}

static ssize_t device_write(FILE *fp,const char *buffer,size_t len,loff_t *offset)
{/*���һ��Ϊ�ļ�ƫ����*/
	int n_write = 0;/
	while (length)
	{
		putc(buffer++,fp);
		length--;
		n_write++;
	}
	return n_write;/*������д�ֽ���*/
}  

module_init(regist_device);
module_exit(unregist_device);
