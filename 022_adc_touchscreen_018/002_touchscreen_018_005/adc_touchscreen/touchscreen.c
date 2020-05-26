#include "touchscreen.h"
#include "../s3c2440_soc.h"

#define ADC_INT_BIT	(10)
#define TC_INT_BIT 	(9)
#define INT_ADC_TC	(31)

/* ADCTSC's bits */
#define UP_DOWN_STAT_BIT 	(8)
#define YM_ENABLE			(1 << 7)
#define YM_DISABLE			(0 << 7)
#define YP_ENABLE			(0 << 6)
#define YP_DISABLE			(1 << 6)
#define XM_ENABLE			(1 << 5)
#define XM_DISABLE			(0 << 5)
#define XP_ENABLE			(0 << 4)
#define XP_DISABLE			(1 << 4)
#define PULLUP_ENABLE		(0 << 3)
#define PULLUP_DISABLE		(1 << 3)
#define AUTO_PST			(1 << 2)
#define WAIT_INT_MODE		(3)
#define NO_OPR_MODE			(0)

void Isr_Tc(void)
{
	if(!(ADCUPDN & (1 << 1)))
		printf("pen down\n\r");
	else
		printf("pen up\n\r");
}

void AdcTsIntHandle(void)
{
	if (SUBSRCPND & (1 << TC_INT_BIT))	/* 如果是触摸屏中断 */
		Isr_Tc();
	
	//if(SUBSRCPND & (1 << ADC_INT_BIT))	/* 如果是ADC中断 */
		//Isr_Adc();
}

void adc_ts_int_init(void)
{
	//adc 中断号为31
	/* 注册中断处理函数 */
	register_irq(31, AdcTsIntHandle);

	/* 使能中断 */
	INTSUBMSK &= ~((1 << ADC_INT_BIT) | (1 << TC_INT_BIT));	
	//INTMASK &= ~(1 << INT_ADC_TC);
}

void adc_ts_reg_init(void)
{
	ADCCON = (1 << 14) | (49 << 6) | (0 << 3);
	ADCDLY = 0xff;
}

void enter_wait_pen_down_mode(void)
{
	ADCTSC = PULLUP_ENABLE | YM_ENABLE | YP_DISABLE | XP_DISABLE | XM_DISABLE | WAIT_INT_MODE;
}

void touchscreen_init(void)
{
	/* 设置中断 */
	adc_ts_int_init();

	/* 设置触摸屏接口：寄存器 */
	adc_ts_reg_init();

	/* 让触摸屏控制器进入"等待中断模式" */
	enter_wait_pen_down_mode();
}
