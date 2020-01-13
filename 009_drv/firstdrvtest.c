#include <stdio.h>

/*
* firstdrvtest on
* firstdrvtest off
*/
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
		printf("Useage :\n");
		printf("%s <on|off>",argv[0]);
		return 0;
	}

	if(strcmp(argv[1],"on") == 0)
	{
		val = 1;
	}
	else
	{
		val = 0;
	}

	write(fd,&val,4);
	return 0;
}
