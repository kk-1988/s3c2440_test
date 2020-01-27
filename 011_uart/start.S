.text
.global _start

_start:
	/* 关闭看门狗 */
	ldr r0, = 0x53000000
	ldr r1, = 0
	/* 把r1的值存放在r0的地址上 */
	str r1, [r0]

	/* 设置MPLL 频率比较: FCLK:HCLK:PCLK => 400m : 100m : 50m */
	/* LOCKTIME(0x4c000000) = 0xFFFFFFFF */
	ldr r0, = 0x4c000000
	ldr r1, = 0xFFFFFFFF
	str r1, [r0] 

	/* CLKDIVN(0x4c000014) = 0x5, 周期比较: tFCLK:tHCLK:tPCLK => 1:4:8 */
	ldr r0, = 0x4c000014
	ldr r1, = 0x5
	str r1, [r0]

	/* 设置CPU工作于异步模式 */
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000	//:OR:R1_iA
	mcr p15,0,r0,c1,c0,0

	/* 设置MPLLCON(0x4C000004) = (92 << 12) | (1 << 4) | (1 << 0) */
	ldr r0, = 0x4C000004
	ldr r1, = (92 << 12) | (1 << 4) | (1 << 0)
	str r1, [r0]

	/* 一旦设置PLL,就会锁定LOCKTIME，直到PLL输出稳定，然后CPU工作于新的频率 
	 * 如果要看到现象，可以在c程序中使用delay接口，delay数值可以修改，然后观察在不同频率下的灯闪频率
	 * 频率越高，同一个delay数值情况下，灯闪频率越快
	 */
	

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

