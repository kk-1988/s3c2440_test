#include <stdio.h>

void test0()
{
	char c;
	char *pc = &c;

	/* ���б������������ڴ���,��&ȡ��ַ�� */
	printf("&c = %p\r\n",&c);
	printf("&pc = %p\r\n",&pc);

	printf("***********************************\r\n");

	/* ��������ĳЩֵ */
	c = 'A';
	pc = &c;
	printf("c = %c\r\n",c);
	printf("pc = %p\r\n",pc);
	printf("&pc = %p\r\n",&pc);

	/* ʹ��ָ�� */
	printf("***********************************\r\n");
	printf("*pc = %c\r\n",*pc);
	
}

void test1()
{
	int ia;
	int *pi;
	char *pc;

	/* ���б������������ڴ���,��&ȡ��ַ�� */
	printf("&ia = %p\r\n",&ia);
	printf("&pi = %p\r\n",&pi);
	printf("&pc = %p\r\n",&pc);

	printf("***********************************\r\n");

	/* ��������ĳЩֵ */
	ia = 0x12345678;
	pi = &ia;
	pc = (char *)&ia;
	printf("ia = 0x%x\r\n",ia);
	printf("pi = %p\r\n",pi);
	printf("pc = %p\r\n",pc);
	printf("***********************************\r\n");

	/* ʹ��ָ�� */
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

	/* ���б������������ڴ���,��&ȡ��ַ�� */
	printf("ca = %p\r\n",ca);
	printf("&pc = %p\r\n",&pc);

	printf("***********************************\r\n");

	/* ��������ĳЩֵ */
	pc = ca;
	printf("pc = %p\r\n",pc);
	printf("***********************************\r\n");

	/* ʹ��ָ�� */
	printf("*pc = %c\r\n",*pc);
	pc++;
	printf("*pc = %c\r\n",*pc);
	pc++;
	printf("*pc = %c\r\n",*pc);	
}

void test3()
{
	int ia[3] = {0x12345678,0x87654321,0x13572468};
	//�״��,int���ͱ�ʾ++�ƶ�int�ֽڵ����֣�����һ���ƶ�4���ֽ�
	int *pi;

	/* ���б������������ڴ���,��&ȡ��ַ�� */
	printf("ia = %p\r\n",ia);
	printf("&pi = %p\r\n",&pi);

	/* ��������ĳЩֵ */
	pi = ia;
	printf("pi = %p\r\n",pi);
	printf("***********************************\r\n");

	/* ʹ��ָ�� */
	printf("*pi = 0x%x\r\n",*pi);
	pi++;
	printf("*pi = 0x%x\r\n",*pi);
	pi++;
	printf("*pi = 0x%x\r\n",*pi);	
}

void test4()
{
	char *pc="abc";

	/* ���б������������ڴ���,��&ȡ��ַ�� */
	printf("pc = %p\r\n",pc);
	printf("&pc = %p\r\n",&pc);

	/* ��������ĳЩֵ */

	/* ʹ��ָ�� */
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
