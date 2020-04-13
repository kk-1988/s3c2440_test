#include <linux/module.h>
#include <linux/kernel.h>

static int major;
static struct class *senconddrv_class;
static struct class_device *senconddrv_class_dev;

int sencond_drv_init(void)
{
	major = register_chrdev(0, "sencond_drv", sencond_drv_fops);		//注册驱动程序(告诉内核)
	senconddrv_class = class_create(THIS_MODULE, "senconddrv");
	senconddrv_class_dev = class_device_create(senconddrv_class, NULL, MKDEV(major,0), NULL, "buttons");	/* /dev/xyz */
	return 0;
}

void sencond_drv_exit(void)
{
	unregister_chrdev(major, "sencond_drv");		//卸载驱动程序
	//??
	class_device_unregister(senconddrv_class_dev);
	class_destroy(senconddrv_class);
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
	unsigned char key_vals[4];
	int regval;

	if(size != size(key_vals))
		return -EINVAL;

	/*
	* 读
	*/
	

	

	return size(key_vals);
}

static struct file_operations sencond_drv_fops = {
	.owner = THIS_MODULE,
	.open = sencond_drv_open,
	.write = sencond_drv_write,
	.read = sencond_drv_read,
};

//入口函数
module_init(sencond_drv_init);
//出口函数
module_exit(sencond_drv_exit);
//license
MODULE_LICENSE("GPL");