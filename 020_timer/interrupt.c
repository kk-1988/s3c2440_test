#include "s3c2440_soc.h"

/* 初始化中断控制器 */
/*
* SRCPND 用来显示哪个中断产生了，需要清除对应位
* 
* 
*/
void interrupt_init(void)
{
	INTMSK &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 4));
}

/* 初始化按键，设为中断源 */
//GPF1(EINT1),GPF4(EINT4),GPF2(EINT2),GPF0(EINT0)
void key_eint_init()
{
	/* 配置GPIO为中断引脚 */
	GPFCON &= ~(3 << 2 | 3<< 8 | 3 << 4 | 3 << 0 );
	GPFCON |= (2 << 2 | 2<< 8 | 2 << 4 | 2 << 0 );

	/* 设置中断触发方式:双边岩触发 */
	EXTINT0 |= (7 << 4) | (7 << 16) | (7 << 8) | (7 << 0);

	/* 
	* 设置外部mask，使能外部中断eint4
	* 其余0，1，2，3位是reserved，所以不去设置
	* 可以直达中断控制器，4开始的，需要设置
	* 这个寄存器
	*/
	EINTMASK |= ~(1 << 4);	
}

/*
* 读EINTPEND分辨哪个EINT产生eint4-eint23
* 清除中断时，写EINTPEND寄存器相应位
* 用于控制某一栈灯
*/
void key_eint_irq(int irq)
{
	unsigned int val = EINTPEND;
	unsigned int val1 = GPFDAT;
	
	if(irq == 0) 	/* eint0 */
	{
		if(val1 & (1 << 0))
		{
			printf("irq0 => led off\r\n");
		}
		else
		{
			printf("irq0 => led on\r\n");
		}
	}
	else if(irq == 1)	/* eint1 */
	{
		if(val1 & (1 << 1))
		{
			printf("irq1 => led off\r\n");
		}
		else
		{
			printf("irq1 => led on\r\n");
		}
	}
	else if(irq == 2)  /* eint2 */
	{
		if(val1 & (1 << 2))
		{
			printf("irq2 => led off\r\n");
		}
		else
		{
			printf("irq2 => led on\r\n");
		}
	}
	else if(irq == 4)	/* eint4 按下这个按键，所有灯点亮或者熄灭*/
	{
		/* 这里处理较为复杂，因为irq4其实对应了好多中断源,具体是哪一个需要再单独确认 */
		if(val & (1 << 4))
		{
			if(val1 & (1 << 4))
			{
				printf("irq4 => led off\r\n");
			}
			else
			{
				printf("irq4 => led on\r\n");
			}
		} 
	}

	/* 清中断 */
	EINTPEND = val;
}

void handle_irq_c(void)
{
	/* 分辨中断源 */
	int bit = INTOFFSET;

	/* 调用对应的处理函数 */
	if (bit == 0 || bit == 1 || bit == 2 || bit == 4)  /* etnt0,1,2,eint8-23 */
	{
		key_eint_irq(bit);	/* 处理中断，清中断源EINTPEND */
	}
	
	/* 清中断: 从源头开始清 */
	SRCPND = (1 << bit);
	INTPND = (1 << bit);
}
