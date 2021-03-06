#include "s3c2440_soc.h"
#include "uart.h"
#include "init.h"

char g_char = 'A';
char g_char3 = 'a';
const char g_char2 = 'B';
int g_A = 0;
int g_B;

int main(void)
{
	puts("\n\rg_A = ");
	printHex(g_A);
	puts("\n\r");

	//在链接脚本中设置bss段位4字节对齐，否则由于start.S中已经
	//修改了ldrb为ldr，即从1字节变为4字节，这样导致bss段需要4字节对齐
	//所以擦除掉了data的数据
	while(1)
	{
	#if 0
		puts("\n\rg_char = ");
		printHex(g_char);
		puts("\n\r");
	#endif
		
		putchar(g_char);
		g_char++;

	#if 0
		puts("\n\rg_char3 = ");
		printHex(g_char3);
		puts("\n\r");
	#endif
	
		putchar(g_char3);
		g_char3++;
		
		delay(1000000);
	}
	
	return 0;
}
