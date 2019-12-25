.text
.global _start

_start:

	/* 设置内存: sp 栈(stack point) */
	ldr sp, = 4096	/* nand 启动 */
	//ldr sp, = 0x40000000 + 4096	/* nor 启动 */

	/* 调用main 函数 跳转到main并保存返回地址 */
	bl main

halt:
	b halt

