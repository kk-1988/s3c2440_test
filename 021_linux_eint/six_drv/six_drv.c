#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/poll.h>

static int major;
static struct class *sixthdrv_class;
static struct class_device *sixthdrv_class_dev;

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

atomic_t canopen = ATOMIC_INIT(1);


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

int sixth_drv_init(void)
{
	major = register_chrdev(0, "sixth_drv", sixth_drv_fops);		//ע����������(�����ں�)
	sixthdrv_class = class_create(THIS_MODULE, "sixthdrv");
	sixthdrv_class_dev = class_device_create(sixthdrv_class, NULL, MKDEV(major,0), NULL, "buttons");	/* /dev/xyz */
	return 0;
}

void sixth_drv_exit(void)
{
	unregister_chrdev(major, "sixth_drv");		//ж����������
	//??
	class_device_unregister(sixthdrv_class_dev);
	class_destroy(sixthdrv_class);

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

static int sixth_drv_open(struct inode *inode,struct file *file)
{
	if (!atomic_dec_and_test(&canopen))
	{
		atomic_inc(&canopen);
		return -EBUSY;		
	}

	request_irq(IRQ_EINT1, buttons_irq, IRQT_BOTHEDGE, "K1", 1);
	request_irq(IRQ_EINT4, buttons_irq, IRQT_BOTHEDGE, "K2", 1);
	request_irq(IRQ_EINT2, buttons_irq, IRQT_BOTHEDGE, "K3", 1);
	request_irq(IRQ_EINT0, buttons_irq, IRQT_BOTHEDGE, "K4", 1);
	
	return 0;	
}

static ssize_t sixth_drv_write(struct file *file, const char _user *buf,size_t count,loff_t *ppos)
{
	return 0;
}

static ssize_t sixth_drv_read(struct file *file, char _user *buf, size_t size, loff_t *ppos)
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

static int sixth_drv_close(struct inode *inode, struct file *file)
{	
	atomic_inc(&canopen);
	//1,4,2,0->0,2,4,1
	free_irq(IRQ_EINT0, 1);
	free_irq(IRQ_EINT2, 1);
	free_irq(IRQ_EINT4, 1);
	free_irq(IRQ_EINT1, 1);

	return 0;
}

static unsigned sixth_drv_poll(struct file *file, poll_table *table)
{
	unsigned int res = 0;
	poll_wait(file, &button_waitq, wait);	//不会立即休眠
	if (ev_press)
		res |= POLLIN | POLLRDNORM;

	return res;
}

static struct file_operations sixth_drv_fops = {
	.owner = THIS_MODULE,
	.open = sixth_drv_open,
	.write = sixth_drv_write,
	.read = sixth_drv_read,
	.release = sixth_drv_close,
	.poll = sixth_drv_poll,
};

//��ں���
module_init(sixth_drv_init);
//���ں���
module_exit(sixth_drv_exit);
//license
MODULE_LICENSE("GPL");
