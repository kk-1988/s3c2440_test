#include "s3c2440_soc.h"
#include "uart.h"
#include "init.h"

char g_char = 'A';
const char g_char2 = 'B';
const char g_char3 = 'c';

int g_a = 0;
int g_b;
static int a_jubu = 10;

int main(void)
{
	uart0_init();

	while(1)
	{
		putchar(g_char);
		g_char++;	/* nand能够正常运行，但是nor启动时,因为无法修改,所以不能直接的写,  此条语句无效        */
		delay(1000000);
	}
	
	return 0;
}



