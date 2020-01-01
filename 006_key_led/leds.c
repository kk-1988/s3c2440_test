#include "s3c2440_soc.h"

//��ֹ�������Ż�ʡ�Ե�delay
void delay(volatile int d)
{
	while(d--);
}

int main(int which)
{
	int val;
	
	/*
	* config output set 0
	*/
	GPBCON &= ~((3 << 10) | (3 << 12) | (3 << 14) | (3 << 16));
	GPBCON |= ((1 << 10) | (1 << 12) | (1 << 14) | (1 << 16));
	GPBDAT |= (0xf << 5);
	
	/*
	* ������ؽ�λ�������ţ��ֱ�Ϊ:GPF1(3:2= 0b00)��GPF4(9:8= 0b00)��GPF2(5:4 = 0b00)��GPF0(1:0 = 0b00)
	*/
	GPFCON &= ~((3 << 2) | (3 << 8) | (3 << 4) | (3 << 0));

	/*
	* ��ȡ��ذ���ֵ��Ȼ����ݰ���ֵȥ�������led
	*/
	while(1)
	{	
		val = GPFDAT;
		if(val & (1 << 1))
		{
			/* �ɿ� */
			GPBDAT |= (1 << 5);
		}
		else
		{
			/* ���� */
			GPBDAT &= ~(1 << 5);
		}

		if(val & (1 << 4))
		{
			/* �ɿ� */
			GPBDAT |= (1 << 6);
		}
		else
		{
			/* ���� */
			GPBDAT &= ~(1 << 6);
		}	

		if(val & (1 << 2))
		{
			/* �ɿ� */
			GPBDAT |= (1 << 7);
		}
		else
		{
			/* ���� */
			GPBDAT &= ~(1 << 7);
		}

		if(val & (1 << 0))
		{
			/* �ɿ� */
			GPBDAT |= (1 << 8);
		}
		else
		{
			/* ���� */
			GPBDAT &= ~(1 << 8);
		}
	}

	return 0;
}
