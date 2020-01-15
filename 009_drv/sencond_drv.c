#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

static int major;
static struct class *senconddrv_class;
static struct class_device *senconddrv_class_dev;

int sencond_drv_init(void)
{
	major = register_chrdev(0, "sencond_drv", sencond_drv_fops);		//ע����������(�����ں�)
	senconddrv_class = class_create(THIS_MODULE, "senconddrv");
	senconddrv_class_dev = class_device_create(senconddrv_class, NULL, MKDEV(major,0), NULL, "xyz");	/* /dev/xyz */
	return 0;
}

void sencond_drv_exit(void)
{
	unregister_chrdev(major, "sencond_drv");		//ж����������
	iounremap(gpbcon);
	return 0;
}

static int sencond_drv_open(struct inode *inode,struct file *file)
{
	return 0;	
}

static ssize_t sencond_drv_write(struct file *file, const char _user *buf,size_t count,loff_t *ppos)
{
	return 0;
}

static ssize_t sencond_drv_read(struct file *file, char _user *buf, size_t size, loff_t *ppos)
{
	return 0;
}
	
static struct file_operations sencond_drv_fops = {
	.owner = THIS_MODULES,
	.open = sencond_drv_open,
	.write = sencond_drv_write,
	.read = sencond_drv_read,
};

//��ں���
module_init(sencond_drv_init);
//���ں���
module_exit(sencond_drv_exit);

