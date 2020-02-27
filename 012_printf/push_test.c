#include <stdio.h>
#include <>

struct person{
	char *name;
	int age;
	char score;
	int id;
};

int push_test(const char *format,...)
{
	char *p = (char *)&format;
	int i;
	char c;
	struct person per;
	double d;
	va_list *p;
	
	printf("arg1 : %s",format);

	p = p + sizeof(char *);
	i = *((int *)p);
	printf("arg2 = %d\r\n", i);

	p = p + sizeof(int);
	per = *((struct person *)p);
	printf("name %s\r\n",per.name);
	printf("age %d\r\n",per.age);
	printf("score %c\r\n",per.score);
	printf("id %d\r\n",per.id);

	p = p + sizeof(struct person);
	c = *((char *)p);
	printf("arg4 =  %c\r\n", c);

	p = p + ((sizeof(char) + 3) & (~3));
	d = *((double *)p);
	printf("arg5 =  %f\r\n", d);
	
	return 0;
}

int main(int argc,char argv[])
{
	struct person per = {"kongxiaobo", 32, 'A',123};
	
	//push_test("abcd");
	//push_test("abcd", 123);
	//push_test("abcd", 123, per);
	//push_test("abcd", 123, per, 'c');
	push_test("abcd", 123, per, 'c', 2.79);
	return 0;
}
