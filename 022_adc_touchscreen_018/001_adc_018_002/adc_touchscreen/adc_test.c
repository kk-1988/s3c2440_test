#include "adc.h"

void adc_test(void)
{
	int val;
	double vol;
	
	adc_init();

	while(1)
	{
		val = adc_read_ain0();
		vol = 		/* 1023 == 3.3v */

		/* 在串口上打印出来 */

		/* 在LCD上打印 */
		
		
	}
}
