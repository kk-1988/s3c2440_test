#include "adc.h"

void adc_test(void)
{
	int val;
	double vol;
	int m;		/* 整数部分 */
	int n;		/* 小数部分 */
	
	adc_init();

	while(1)
	{
		val = adc_read_ain0();
		vol = val/1023*3.3;		/* 1023 == 3.3v */
		m = (int)vol;		/* 3.3 或者 3.01 */
		vol = vol - m;		/* 小数部分 */
		n = vol * 1000;		/* 300 */
		
		/* 在串口上打印出来 */
		printf("%d.%03dv",m,n);

		/* 在LCD上打印 */
		//fb_print_string();
		
	}
}
