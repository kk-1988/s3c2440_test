int main(int argc,char *argv[])
{
	unsigned int *p_gpfcon = (unsigned int *)0x56000010;
	unsigned int *p_gpfdat = (unsigned int *)0x56000014;

	/*
	* config output
	*/
	*p_gpfcon = 0x400;

	/*
	* set high
	*/
	*p_gpfdat = 0;
	
	return 0;
}
