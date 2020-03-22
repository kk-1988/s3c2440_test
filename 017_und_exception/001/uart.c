
#include "s3c2440_soc.h"


/* 115200,8n1 */
void uart0_init()
{
	/* ÉèÖÃÒı½ÅÓÃÓÚ´®¿Ú */
	/* GPH2,3ÓÃÓÚTxD0, RxD0 */
	GPHCON &= ~((3<<4) | (3<<6));
	GPHCON |= ((2<<4) | (2<<6));

	GPHUP &= ~((1<<2) | (1<<3));  /* Ê¹ÄÜÄÚ²¿ÉÏÀ­ */
	

	/* ÉèÖÃ²¨ÌØÂÊ */
	/* UBRDIVn = (int)( UART clock / ( buad rate x 16) ) ¨C1
	 *  UART clock = 50M
	 *  UBRDIVn = (int)( 50000000 / ( 115200 x 16) ) ¨C1 = 26
	 */
	UCON0 = 0x00000005; /* PCLK,ÖĞ¶Ï/²éÑ¯Ä£Ê½ */
	UBRDIV0 = 26;

	/* ÉèÖÃÊı¾İ¸ñÊ½ */
	ULCON0 = 0x00000003; /* 8n1: 8¸öÊı¾İÎ», ÎŞ½ÏÑéÎ», 1¸öÍ£Ö¹Î» */

	/*  */

}

int putchar(int c)
{
	/* UTRSTAT0 */
	/* UTXH0 */

	while (!(UTRSTAT0 & (1<<2)));
	UTXH0 = (unsigned char)c;
	
}

int getchar(void)
{
	while (!(UTRSTAT0 & (1<<0)));
	return URXH0;
}

int puts(const char *s)
{
	while (*s)
	{
		putchar(*s);
		s++;
	}
}

/* 0xABCDEF12 */
void printHex(unsigned int val)
{
	int i;
	unsigned char arr[8];

	/* å…ˆå–å‡ºæ¯ä¸€ä½çš„å€¼ */
	for(i = 0; i < 8; i++)
	{
		arr[i] = val & 0xf;
		val >>= 4; /* arr[0] = 2, arr[1] = 1 ... */
	}

	/* æ‰“å° */
	puts("0x");
	for(i = 7; i >= 0;i--)
	{
		if(arr[i] >= 0 && arr[i] <= 9)
			putchar(arr[i] + '0');
		else if(arr[i] >= 0xA && arr[i] <= 0xF)
			putchar(arr[i] - 0xA + 'A');
		
	}
}

/*
* è°ƒè¯•æ‰“å°ä¿¡æ¯
*/
void print1()
{
	puts("abc\n\r");
}

void print2()
{
	puts("123\n\r");
}
