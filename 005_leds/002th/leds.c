//防止编译器优化省略掉delay
void delay(volatile int d)
{
	while(d--);
}

#define GPFCON	(*((volatile unsigned int *)0x56000010))
#define GPFDAT  (*((volatile unsigned int *)0x56000014))

int main(int which)
{
	/*
	* gpb5/6/7/8
	*/

	int val = 0;
	int tmp;
	
	/*
	* config output set 0
	*/
	GPFCON &= ~((3 << 10) | (3 << 12) | (3 << 14) | (3 << 16));
	GPFDAT |= ((1 << 10) | (1 << 12) | (1 << 14) | (1 << 16));

	/*
	* 循环点亮
	*/
	while(1)
	{	
		tmp = ~val;
		tmp &= 0xf;
		GPFCON = ~(0xf << 5);
		GPFDAT |= tmp << 5;
		delay(100000);
		val++;
		if(val == 0x10)
			val = 0;
	}

	return 0;
}
