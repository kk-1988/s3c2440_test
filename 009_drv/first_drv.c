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

volatile unsigned long *gpbcon = 0;
volatile unsigned long *gpbdat = 0;

static int first_drv_open(struct inode *inode,struct file *file)
{
	/* 配置GPB为输出 */
	gpbcon &= ~();
	return 0;	
}

static ssize_t first_drv_write(struct file *file, const char _user *buf,size_t count,loff_t *ppos)
{
	int val;
	/* 对相关引脚拉高拉低 */
	copy_from_user(&val, buf, count);
	if(1 == val)
	{
		//点亮,拉低
		
	}
	else
	{
		//熄灭,清0
	}
	
	return 0;
}

static struct file_operations first_drv_fops = {
	.owner = THIS_MODULES,
	.open = first_drv_open,
	.write = first_drv_write,
}

int first_drv_init(void)
{
	register_chrdev(111, "first_drv", first_drv_fops);		//注册驱动程序(告诉内核)
	gpbcon = (volatile unsigned long *)ioremap(0x56000050,16);
	gpbdat = gpbcon + 1;
	
	return 0;
}

void first_drv_exit(void)
{
	unregister_chrdev(111, "first_drv");		//卸载驱动程序
	iounremap(gpbcon);
	return 0;
}

//入口函数
module_init(first_drv_init);
//出口函数
module_exit(first_drv_exit);
