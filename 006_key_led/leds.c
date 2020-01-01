#include "s3c2440_soc.h"

//防止编译器优化省略掉delay
void delay(volatile int d)
{
	while(d--);
}

int main(int which)
{
	int val;
	
	/*
	* config output set 0
	*/
	GPBCON &= ~((3 << 10) | (3 << 12) | (3 << 14) | (3 << 16));
	GPBCON |= ((1 << 10) | (1 << 12) | (1 << 14) | (1 << 16));
	GPBDAT |= (0xf << 5);
	
	/*
	* 配置相关脚位输入引脚，分别为:GPF1(3:2= 0b00)，GPF4(9:8= 0b00)，GPF2(5:4 = 0b00)，GPF0(1:0 = 0b00)
	*/
	GPFCON &= ~((3 << 2) | (3 << 8) | (3 << 4) | (3 << 0));

	/*
	* 读取相关按键值，然后根据按键值去点亮相关led
	*/
	while(1)
	{	
		val = GPFDAT;
		if(val & (1 << 1))
		{
			/* 松开 */
			GPBDAT |= (1 << 5);
		}
		else
		{
			/* 按下 */
			GPBDAT &= ~(1 << 5);
		}

		if(val & (1 << 4))
		{
			/* 松开 */
			GPBDAT |= (1 << 6);
		}
		else
		{
			/* 按下 */
			GPBDAT &= ~(1 << 6);
		}	

		if(val & (1 << 2))
		{
			/* 松开 */
			GPBDAT |= (1 << 7);
		}
		else
		{
			/* 按下 */
			GPBDAT &= ~(1 << 7);
		}

		if(val & (1 << 0))
		{
			/* 松开 */
			GPBDAT |= (1 << 8);
		}
		else
		{
			/* 按下 */
			GPBDAT &= ~(1 << 8);
		}
	}

	return 0;
}
