
/*
 * 点亮led:GPB5
 * .text 代码段
 * .global 全局变量
 */
.text
.global _start

_start:

 /* 配置GPB6为输出引脚 
  * 把0x800写到0x56000010
  */
  	ldr r1,=0x56000010
  	ldr r0,=0x1000 /* mov r0,#0x800 */
  	str r0,[r1]

 /* 
  * 配置GPB6为高电平
  * 把0x0写道0x56000014
  */ 
  	ldr r1,=0x56000014
  	ldr r0,=0x0 /* mov r0,#0 */
  	str r0,[r1]

/*
 * 死循环,因为只有几十个字节，执行完如果不死循环，
 * nor或者nand无法继续执行下去，后果不可预期
 */
halt:
	b halt