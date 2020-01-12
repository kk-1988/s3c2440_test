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

static struct class *firstdrv_class;
static struct class_device *firstdrv_class_dev;

static int first_drv_open(struct inode *inode,struct file *file)
{
	printk("first drv open\n");
	return 0;	
}

static ssize_t first_drv_write(struct file *file, const char _user *buf,size_t count,loff_t *ppos)
{
	printk("first drv write\n");
	return 0;
}

static struct file_operations first_drv_fops = {
	.owner = THIS_MODULES,
	.open = first_drv_open,
	.write = first_drv_write,
}

int first_drv_init(void)
{
	register_chrdev(111, "first_drv", first_drv_fops);		//ע����������(�����ں�)
	return 0;
}

void first_drv_exit(void)
{
	unregister_chrdev(111, "first_drv");		//ж����������
	return 0;
}

//��ں���
module_init(first_drv_init);
//���ں���
module_exit(first_drv_exit);
