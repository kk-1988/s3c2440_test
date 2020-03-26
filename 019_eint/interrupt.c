/* 初始化中断控制器 */
/*
* SRCPND 用来显示哪个中断产生了，需要清除对应位
* 
* 
*/
void interrupt_init(void)
{
	INTMSK &= ~();
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
*/

