#include "s3c2440_soc.h"

void copy2sdram(void)
{
	/* 
	* 要从lds文件中获得 __code_start 和 bss_start 
	* 然后从0地址把数据复制到__code_start
	*
	*/
	extern int __code_start,bss_start;
	volatile unsigned int *dst = (volatile unsigned int *)&__code_start;
	volatile unsigned int *end = (volatile unsigned int *)&bss_start;
	volatile unsigned int *src = (volatile unsigned int *)0;
	
	unsigned int i = 0;

	while(dst <= end)
	{
		*dst++ = *src++;
	}
}

void clean_bss(void)
{
	/* 
	* 要从lds文件中获得 bss_start 和 bss_end 
	*/
	extern int bss_end,bss_start;
	volatile unsigned int *start= (volatile unsigned int *)&bss_start;
	volatile unsigned int *end = (volatile unsigned int *)&bss_end;
	
	while(start <= end)
	{
		*start++ = 0;
	}
}

void sdram_init(void)
{
	BWSCON = 0x22000000;

	BANKCON6 = 0x18001;
	BANKCON7 = 0x18001;

	REFRESH  = 0x8404f5;

	BANKSIZE = 0xb1;

	MRSRB6   = 0x20;
	MRSRB7   = 0x20;
}

//下面的函数不是位置无关的，所以实际上在板子上是无法运行的
void sdram_init2(void)
{
	unsigned int arr[] = {
		0x22000000, 		//BWSCON
		0x00000700, 		//BANKCON0
		0x00000700, 		//BANKCON1
		0x00000700, 		//BANKCON2
		0x00000700, 		//BANKCON3
		0x00000700, 		//BANKCON4
		0x00000700, 		//BANKCON5
		0x00018001, 		//BANKCON6
		0x00018001, 		//BANKCON7
		0x008404f5, 		//REFRESH,HCLK=12MHz
		0x000000b1, 		//BANKSIZE
		0x00000020, 		//MRSRB6
		0x00000020,			//MRSRB7
		};
	volatile unsigned int *p = (volatile unsigned int *)0x48000000;
	int i;
	for(i = 0;i < 13;i++)
	{
		*p = arr[i];
		p++;
	}
}

int sdram_test(void)
{
	volatile unsigned char *p = (volatile unsigned char *)0x30000000;
	int i;

	// write sdram
	for (i = 0; i < 1000; i++)
		p[i] = 0x55;

	// read sdram
	for (i = 0; i < 1000; i++)
		if (p[i] != 0x55)
			return -1;

	return 0;
}

