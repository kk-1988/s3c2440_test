#include "../s3c2440_soc.h"

void adc_init()
{
	ADCCON = (1 << 14) | (49 << 6) | (0 << 3); 
	ADCDLY = 0xff;
}

int adc_read_ain0()
{
	ADCCON |= (1 << 0);
	while(!(ADCCON & (1 << 15)));	/* 等待ADC结束 */

	return ADCDAT0 & 0x3ff;
}
