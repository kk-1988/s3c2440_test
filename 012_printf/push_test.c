#include <stdio.h>

int push_test(const char *format,...)
{
	char *p = (char *)&format;
	int i;
	printf("arg1 : %s",format);

	p = p + sizeof(char *);
	i = *((int *)p);
	printf("arg2 = %d\r\n", i);
	
	return 0;
}

int main(int argc,char argv[])
{
	//push_test("abcd");
	push_test("abcd", 123);
	return 0;
}
