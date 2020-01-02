#include <stdio.h>

#define _DEBUG

int main(int argc,char *argv[])
{
	printf("hello world!!!\r\n");

#ifdef _DEBUG
	printf("_DEBUG hello world\r\n");
#endif

	return 0;
}
