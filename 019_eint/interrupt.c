/* 初始化中断控制器 */
void interrupt_init(void)
{
	
}

/* 初始化按键，设为中断源 */
//GPF1,GPF4,GPF2,GPF0
void key_eint_init()
{
	/* 配置GPIO为中断引脚 */
	GPFCON &= ~(3 << 2 | 3<< 8 | 3 << 4 | 3 << 0 );
	GPFCON |= (2 << 2 | 2<< 8 | 2 << 4 | 2 << 0 );
	
	
	/* 设置中断触发方式:双边岩触发 */
	
}
