.text
.global _start

_start:

	/* 设置内存: sp 栈(stack point) */
	ldr sp, = 4096	/* nand 启动 */
	//ldr sp, = 0x40000000 + 4096	/* nor 启动 */

	/* r0 - r3可以传递参数，现在只有一个参数，所以我们只使用r0 */
	mov r0,	#1
	bl led_on

	ldr r0, = 100000
	bl delay

	mov r0,	#2
	bl led_on
	
halt:
	b halt

