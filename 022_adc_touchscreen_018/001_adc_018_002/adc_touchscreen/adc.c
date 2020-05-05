#include "../s3c2440_soc.h"

void adc_init()
{
	ADCCON = (1 << 14) | (49 << 6) |; | 
}

int adc_read_ain0()
{
	
}


