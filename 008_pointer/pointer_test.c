#include <stdio.h>

void test0()
{
	char c;
	char *pc = &c;

	/* 所有变量都保存在内存中,用&取地址符 */
	printf("&c = %p\r\n",&c);
	printf("&pc = %p\r\n",&pc);

	printf("***********************************\r\n");

	/* 变量保存某些值 */
	c = 'A';
	pc = &c;
	printf("c = %c\r\n",c);
	printf("pc = %p\r\n",pc);
	printf("&pc = %p\r\n",&pc);

	/* 使用指针 */
	printf("***********************************\r\n");
	printf("*pc = %c\r\n",*pc);
	
}

void test1()
{
	int ia;
	int *pi;
	char *pc;

	/* 所有变量都保存在内存中,用&取地址符 */
	printf("&ia = %p\r\n",&ia);
	printf("&pi = %p\r\n",&pi);
	printf("&pc = %p\r\n",&pc);

	printf("***********************************\r\n");

	/* 变量保存某些值 */
	ia = 0x12345678;
	pi = &ia;
	pc = (char *)&ia;
	printf("ia = 0x%x\r\n",ia);
	printf("pi = %p\r\n",pi);
	printf("pc = %p\r\n",pc);
	printf("***********************************\r\n");

	/* 使用指针 */
	printf("*pi = 0x%x\r\n",*pi);
	printf("*pc = 0x%x\r\n",*pc);
	pc++;
	printf("*pc = 0x%x\r\n",*pc);
	pc++;
	printf("*pc = 0x%x\r\n",*pc);	
	pc++;
	printf("*pc = 0x%x\r\n",*pc);
}

void test2()
{
	char ca[3] = {'A','B','C'};
	char *pc;

	/* 所有变量都保存在内存中,用&取地址符 */
	printf("ca = %p\r\n",ca);
	printf("&pc = %p\r\n",&pc);

	printf("***********************************\r\n");

	/* 变量保存某些值 */
	pc = ca;
	printf("pc = %p\r\n",pc);
	printf("***********************************\r\n");

	/* 使用指针 */
	printf("*pc = %c\r\n",*pc);
	pc++;
	printf("*pc = %c\r\n",*pc);
	pc++;
	printf("*pc = %c\r\n",*pc);	
}

void test3()
{
	int ia[3] = {0x12345678,0x87654321,0x13572468};
	//易错点,int类型表示++移动int字节的数字，所以一次移动4个字节
	int *pi;

	/* 所有变量都保存在内存中,用&取地址符 */
	printf("ia = %p\r\n",ia);
	printf("&pi = %p\r\n",&pi);

	/* 变量保存某些值 */
	pi = ia;
	printf("pi = %p\r\n",pi);
	printf("***********************************\r\n");

	/* 使用指针 */
	printf("*pi = 0x%x\r\n",*pi);
	pi++;
	printf("*pi = 0x%x\r\n",*pi);
	pi++;
	printf("*pi = 0x%x\r\n",*pi);	
}

void test4()
{
	char *pc="abc";

	/* 所有变量都保存在内存中,用&取地址符 */
	printf("pc = %p\r\n",pc);
	printf("&pc = %p\r\n",&pc);

	/* 变量保存某些值 */

	/* 使用指针 */
	printf("*pc = %c\r\n",*pc);
	printf("pc = %p\r\n",pc);
	pc++;
	printf("*pc = %c\r\n",*pc);
	pc++;
	printf("*pc = %c\r\n",*pc);	
}

int main(int argc,char *argv[])
{
	printf("sizeof(char) = %d\r\n",sizeof(char));
	printf("sizeof(int) = %d\r\n",sizeof(int));
	printf("sizeof(char *) = %d\r\n",sizeof(char *));
	printf("sizeof(char **) = %d\r\n",sizeof(char **));
	printf("============================================\r\n");
	//test0();
	//test1();
	//test2();
	//test3();
	test4();

	return 0;
}
