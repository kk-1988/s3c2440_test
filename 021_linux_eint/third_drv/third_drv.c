#include <linux/module.h>
#include <linux/kernel.h>

static int major;
static struct class *thirddrv_class;
static struct class_device *thirddrv_class_dev;

sturct pin_desc{
	unsigned int pin;
	unsigned int key_value;
};

int third_drv_init(void)
{
	major = register_chrdev(0, "sencond_drv", sencond_drv_fops);		//注册驱动程序(告诉内核)
	senconddrv_class = class_create(THIS_MODULE, "senconddrv");
	senconddrv_class_dev = class_device_create(senconddrv_class, NULL, MKDEV(major,0), NULL, "buttons");	/* /dev/xyz */
	return 0;
}

void third_drv_exit(void)
{
	unregister_chrdev(major, "sencond_drv");		//卸载驱动程序
	//??
	class_device_unregister(senconddrv_class_dev);
	class_destroy(senconddrv_class);

	return 0;
}

static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	printk("irq = %d\n", irq);
	s3c2410_gpio_getpin(unsigned int pin);
	return IRQ_RETVAL(IRQ_HANDLED);
}

static int third_drv_open(struct inode *inode,struct file *file)
{
	request_irq(IRQ_EINT1, buttons_irq, IRQT_BOTHEDGE, "K1", 1);
	request_irq(IRQ_EINT4, buttons_irq, IRQT_BOTHEDGE, "K2", 1);
	request_irq(IRQ_EINT2, buttons_irq, IRQT_BOTHEDGE, "K3", 1);
	request_irq(IRQ_EINT0, buttons_irq, IRQT_BOTHEDGE, "K4", 1);
	
	return 0;	
}

static ssize_t third_drv_write(struct file *file, const char _user *buf,size_t count,loff_t *ppos)
{
	return 0;
}

static ssize_t third_drv_read(struct file *file, char _user *buf, size_t size, loff_t *ppos)
{
	unsigned char key_vals[4];
	int regval;

	if(size != size(key_vals))
		return -EINVAL;

	/*
	* 读
	*/
	

	

	return size(key_vals);
}

static int third_drv_close(struct inode *inode, struct file *file)
{
	//1,4,2,0->0,2,4,1
	free_irq(IRQ_EINT0, 1);
	free_irq(IRQ_EINT2, 1);
	free_irq(IRQ_EINT4, 1);
	free_irq(IRQ_EINT1, 1);

	return 0;
}

static struct file_operations third_drv_fops = {
	.owner = THIS_MODULE,
	.open = third_drv_open,
	.write = third_drv_write,
	.read = third_drv_read,
	.release = third_drv_close,
};

//入口函数
module_init(third_drv_init);
//出口函数
module_exit(third_drv_exit);
//license
MODULE_LICENSE("GPL");