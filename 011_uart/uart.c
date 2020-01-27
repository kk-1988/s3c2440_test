#include "s3c2440_soc.h"

/*
* 115200 8n1
*/
void uart0_init()
{
	/* �����������ڴ��� */
	/* ������ӦGPIO�� */

	/* ����UARTΪ�ڲ����� */
		
	
	/* ���ò����� */
	//UBRDIVn = (int)( UART clock / ( buad rate x 16) ) �C1
	/*
	* ����:
	* 1.UART clock ����ʲô == PCLK
	* 2.uart0 ��ӦUCON0,�Ĵ�����ַΪ:0x50000004
	* 3.
	* 4.
	* UBRDIVn = (int)( 50000000 / (115200 x 16) ) �C1 = 26.1 = 26
	*
	*/
	UCON0 = 0x00000005;	//PCLK,�жϻ��ѯ
	UBRDIV0 = 26;

	/* �������ݸ�ʽ */
	ULCON0 = 3;		//8n1,8������λ����У��λ��1��ֹͣλ
	
}

//����
int putchar(int c)
{
	//UTRSTAT0
	//UTXH0

	while(!(UTRSTAT0 & (1 << 2)));
	UTXH0 = c;
}

//����
int getchar(void)
{
	//URXH0
	while(!(UTRSTAT0 & (1 << 0)));
	return URXH0;
}
