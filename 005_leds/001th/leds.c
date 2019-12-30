//防止编译器优化省略掉delay
void delay(volatile int d)
{
	while(d--);
}

int main(int which)
{
	/*
	* gpb5/6/7/8
	*/
	volatile unsigned int *p_gpfcon = (unsigned int *)0x56000010;
	volatile unsigned int *p_gpfdat = (unsigned int *)0x56000014;
	int val = 0;
	int tmp;
	/*
	* config output set 0
	*/
	*p_gpfcon &= ~((3 << 10) | (3 << 12) | (3 << 14) | (3 << 16));
	*p_gpfcon |= ((1 << 10) | (1 << 12) | (1 << 14) | (1 << 16));

	/*
	* 循环点亮
	*/
	while(1)
	{	
		tmp = ~val;
		tmp &= 0xf;
		*p_gpfdat = ~(0xf << 5);
		*p_gpfdat |= tmp << 5;
		delay(100000);
		val++;
		if(val == 0x10)
			val = 0;
	}

	return 0;
}
