#include <linux/module.h>
#include <linux/kernel.h>

static int major;
static struct class *fourthdrv_class;
static struct class_device *fourthdrv_class_dev;

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

/* 中断事件标志,中断服务程序将它置1，fourth_drv_read将它清0 */
static volatile int ev_press = 0;

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

int fourth_drv_init(void)
{
	major = register_chrdev(0, "fourth_drv", fourth_drv_fops);		//ע����������(�����ں�)
	fourthdrv_class = class_create(THIS_MODULE, "fourthdrv");
	fourthdrv_class_dev = class_device_create(fourthdrv_class, NULL, MKDEV(major,0), NULL, "buttons");	/* /dev/xyz */
	return 0;
}

void fourth_drv_exit(void)
{
	unregister_chrdev(major, "fourth_drv");		//ж����������
	//??
	class_device_unregister(fourthdrv_class_dev);
	class_destroy(fourthdrv_class);

	return 0;
}

static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	struct pin_desc *pindesc = (struct pin_desc *)dev_id;
	unsigned int pinval;

	pinval = s3c2410_gpio_getpin(pindesc->pin);
	if(pinval)
	{
		printk("up\r\n");
	}
	else
	{
		printk("down\r\n");
	}

	ev_press = 1;							/* 表示中断发生了 */
	wake_up_interruptible(&button_waitq);	/* 唤醒休眠的进程 */
	
	return IRQ_RETVAL(IRQ_HANDLED);
}

static int fourth_drv_open(struct inode *inode,struct file *file)
{
	request_irq(IRQ_EINT1, buttons_irq, IRQT_BOTHEDGE, "K1", 1);
	request_irq(IRQ_EINT4, buttons_irq, IRQT_BOTHEDGE, "K2", 1);
	request_irq(IRQ_EINT2, buttons_irq, IRQT_BOTHEDGE, "K3", 1);
	request_irq(IRQ_EINT0, buttons_irq, IRQT_BOTHEDGE, "K4", 1);
	
	return 0;	
}

static ssize_t fourth_drv_write(struct file *file, const char _user *buf,size_t count,loff_t *ppos)
{
	return 0;
}

static ssize_t fourth_drv_read(struct file *file, char _user *buf, size_t size, loff_t *ppos)
{
	if(size != 1)
		return -EINVAL;

	/* 如果没有按键动作，休眠 */
	wait_event_interruptible(button_waitq, ev_press);

	/*
	* 如果有按键动作，返回
	*/
	copy_to_user(buf,&key_val, 1);
	ev_press = 0;
	
	return 1;
}

static int fourth_drv_close(struct inode *inode, struct file *file)
{
	//1,4,2,0->0,2,4,1
	free_irq(IRQ_EINT0, 1);
	free_irq(IRQ_EINT2, 1);
	free_irq(IRQ_EINT4, 1);
	free_irq(IRQ_EINT1, 1);

	return 0;
}

static struct file_operations fourth_drv_fops = {
	.owner = THIS_MODULE,
	.open = fourth_drv_open,
	.write = fourth_drv_write,
	.read = fourth_drv_read,
	.release = fourth_drv_close,
};

//��ں���
module_init(fourth_drv_init);
//���ں���
module_exit(fourth_drv_exit);
//license
MODULE_LICENSE("GPL");
