#include <linux/module.h>
#include <linux/kernel.h>

static int major;
static struct class *thirddrv_class;
static struct class_device *thirddrv_class_dev;

sturct pin_desc{
	unsigned int pin;
	unsigned int key_value;
};

/*
* EINT1,4,2,0(K1,K2,K3,K4)
*/
struct pin_desc pins_desc[4] = {
	{S3C2410_GPG10, 0x01},
	{S3C2410_GPG10, 0x01},
	{S3C2410_GPG10, 0x01},
	{S3C2410_GPG10, 0x01},
};

int third_drv_init(void)
{
	major = register_chrdev(0, "sencond_drv", sencond_drv_fops);		//×¢²áÇý¶¯³ÌÐò(¸æËßÄÚºË)
	senconddrv_class = class_create(THIS_MODULE, "senconddrv");
	senconddrv_class_dev = class_device_create(senconddrv_class, NULL, MKDEV(major,0), NULL, "buttons");	/* /dev/xyz */
	return 0;
}

void third_drv_exit(void)
{
	unregister_chrdev(major, "sencond_drv");		//Ð¶ÔØÇý¶¯³ÌÐò
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
	if(size != 1)
		return -EINVAL;

	/* å¦‚æžœæ²¡æœ‰æŒ‰é”®åŠ¨ä½œï¼Œä¼‘çœ  */

	/*
	* å¦‚æžœæœ‰æŒ‰é”®åŠ¨ä½œï¼Œè¿”å›ž
	*/
	copy_to_user(buf,key_val, 1);

	

	return 1;
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

//Èë¿Úº¯Êý
module_init(third_drv_init);
//³ö¿Úº¯Êý
module_exit(third_drv_exit);
//license
MODULE_LICENSE("GPL");
