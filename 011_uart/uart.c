#include "s3c2440_soc.h"

/*
* 115200 8n1
*/
void uart0_init()
{
	/* 设置引脚用于串口 */
	/* 配置相应GPIO脚 */

	/* 设置UART为内部上拉 */
		
	
	/* 设置波特率 */
	//UBRDIVn = (int)( UART clock / ( buad rate x 16) ) –1
	/*
	* 问题:
	* 1.UART clock 等于什么 == PCLK
	* 2.uart0 对应UCON0,寄存器地址为:0x50000004
	* 3.
	* 4.
	* UBRDIVn = (int)( 50000000 / (115200 x 16) ) –1 = 26.1 = 26
	*
	*/
	UCON0 = 0x00000005;	//PCLK,中断或查询
	UBRDIV0 = 26;

	/* 设置数据格式 */
	ULCON0 = 3;		//8n1,8个数据位，无校验位，1个停止位
	
}

//发送
int putchar(int c)
{
	//UTRSTAT0
	//UTXH0

	while(!(UTRSTAT0 & (1 << 2)));
	UTXH0 = c;
}

//接收
int getchar(void)
{
	//URXH0
	while(!(UTRSTAT0 & (1 << 0)));
	return URXH0;
}
