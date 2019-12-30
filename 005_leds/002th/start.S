.text
.global _start

_start:
	/* 关闭看门狗 */
	ldr r0, = 0x53000000
	ldr r1, = 0
	/* 把r1的值存放在r0的地址上 */
	str r1, [r0]

	/* 设置内存: sp 栈(stack point) */
	/* 判断是nor启动还是nand启动 
	* 写0到0地址，再读出来,如果得到0，表示0地址上的内存内容被修改
	* 它对应片内的ram，这就是nand启动，它对应nand启动
	* 否则就是nor启动
	*/
	mov r1,#0
	ldr r0, [r1]	/* 读出原来的值备份一下,读取r1地址上的值到r0中 */
	str r1, [r1]	/* 把r1的值存放在r1所在的地址上 */
	ldr r2, [r1]	/* 读取r1地址上的值到r2 */
	cmp r1, r2	/* r1 == r2？ 如果相等，表明是nand启动 */
	ldr sp, = 0x40000000 + 4096	/* 假设是nor启动 */
	moveq sp,#4096	/* 如果是nand启动，则sp重新设置 */
	streq r0, [r1]	/* 恢复原来的值 */
	
	bl main
	
halt:
	b halt

