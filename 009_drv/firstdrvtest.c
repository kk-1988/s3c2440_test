#include <stdio.h>

int main(int argc,char *argv[])
{
	int fd;
	int val = 1;
	fd = open("/dev/xyz",O_RDWR);
	if(fd < 0)
	{
		printf("cannot open!!!\n");
	}

	if(argc != 2)
	{
		
	}
	
	return 0;
}
