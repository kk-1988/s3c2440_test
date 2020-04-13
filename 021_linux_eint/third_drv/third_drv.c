#include <linux/module.h>
#include <linux/kernel.h>

static int major;
static struct class *thirddrv_class;
static struct class_device *thirddrv_class_dev;

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

static int third_drv_open(struct inode *inode,struct file *file)
{
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

static struct file_operations third_drv_fops = {
	.owner = THIS_MODULE,
	.open = third_drv_open,
	.write = third_drv_write,
	.read = third_drv_read,
};

//入口函数
module_init(third_drv_init);
//出口函数
module_exit(third_drv_exit);
//license
MODULE_LICENSE("GPL");