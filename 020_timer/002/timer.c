#include "s3c2440_soc.h"

void timer_irq(void)
{
	/* 点灯计数 */
	static int cnt = 0;
	puts("timer_irq");
	puts("\r\n");
}

/*
* 定时器初始化
*/
void timer_init(void)
{
	/* 设置TIMER0的时钟 */
	/* 
	 *	公式: Timer   clk = PCLK / {prescaler value + 1} / {divider value} 
	 *                  = 500000000 / (99 + 1) / 16
	 *					= 312500
	 */
	TCFG0 = 99;	/* prescaler 0 = 99, 用于timer0，1 */
	TCFG1 &= ~0xf;
	TCFG1 |= 3;
	
	/* 设置TIMER0初始值 */
	TCNTB0 = 15625;		/* 0.5s中断一次 */

	/* 加载初值，启动TIMER0       */
	TCON |= (1 << 1);	/* */

	/* 设置为自动加载并启动 */
	TCON &= ~(1 << 1);
	//start | auto start
	TCON |= (1 << 0) | (1 << 3);
	
	/* 设置中断 */
	register_irq(10, timer_irq);
}
