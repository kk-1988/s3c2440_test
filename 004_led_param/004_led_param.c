//∑¿÷π±‡“Î∆˜”≈ªØ °¬‘µÙdelay
void delay(volatile int d)
{
	while(d--);
}

int led_on(int which)
{
	unsigned int *p_gpfcon = (unsigned int *)0x56000010;
	unsigned int *p_gpfdat = (unsigned int *)0x56000014;

	if(1 == which)
	{
		/*
		* config output
		*/
		*p_gpfcon = 0x400;
	}
	else if(2 == which)
	{
		/*
		* config output
		*/
		*p_gpfcon = 0x1000;
	}

	/*
	* set high
	*/
	*p_gpfdat = 0;

	return 0;
}
