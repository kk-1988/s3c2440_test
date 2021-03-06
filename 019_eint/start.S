.text
.global _start

_start:
	b reset	/* vector 0: reset */
	/* 如果下面处理函数是超过4k(nand启动)的，那么必定出错 */
	//b do_und	/* vectro 4:und */
	
	/* 需要跳转到sdram中去,但是如果start.S很大，超过了前面4k，那这里也会有问题 */
	//ldr pc, = do_und

	/* 这么处理之后，就是不管start.S多大，都会在4k里面了 */
	ldr pc, und_addr  /* vectro 4:und */
	ldr pc, swi_addr  /* vectro 8:swi */

	/* 这里处理之后 */
und_addr:
	.word do_und

swi_addr:
	.word do_swi

do_und:
	/* 
	* 执行到这里之前：
	* 1.lr_und 保存有被中断模式下的下一条即将执行的指令的地址
	* 2.SPSR_und 保存有被中断模式的CPSR
	* 3.CPSR中的M4-M0被设置位11011b,进入到und模式
	* 4.跳到0x4的地方执行程序
	*/

	/* sp und未设置，先设置它 */
	ldr sp, = 0x34000000

	/*
	* lr是异常处理完后的返回地址，也要保存
	*/
	stmdb sp!, {r0-r12, lr}	/* 在und异常处理函数中有可能会修改r0-r12，所以先保存下来 */
	
	/* 保存现场 */	
	/* 处理und异常 */
	mrs r0, cpsr
	ldr r1, = und_string
	bl printException
	
	/* 恢复现场 */
	ldmia sp!, {r0-r12, pc}^	/*尖括号会把spsr的值恢复到cpsr中*/ 
	
und_string:
	.string "undefined instruction exception"

.align 4

do_swi:
	/* 
	* 执行到这里之前：
	* 1.lr_svc 保存有被中断模式下的下一条即将执行的指令的地址
	* 2.SPSR_svc 保存有被中断模式的CPSR
	* 3.CPSR中的M4-M0被设置位10011b,进入到svc模式
	* 4.跳到0x8的地方执行swi向量
	*/

	/* sp und未设置，先设置它 */
	ldr sp, = 0x33e00000

	/*
	* lr是异常处理完后的返回地址，也要保存
	*/
	stmdb sp!, {r0-r12, lr}	/* 在und异常处理函数中有可能会修改r0-r12，所以先保存下来 */
	
	/* 保存现场 */	
	/* 处理swi异常 */
	mrs r0, cpsr
	ldr r1, = swi_string
	bl printException

	sub r0, r4, #4
	bl printSWIVal
	
	/* 恢复现场 */
	ldmia sp!, {r0-r12, pc}^	/*尖括号会把spsr的值恢复到cpsr中*/ 
	
swi_string:
	.string "swi exception"

/* 保证后面的指令是4字节对齐 */
.align 4

reset:
	/* �رտ��Ź� */
	ldr r0, =0x53000000
	ldr r1, =0
	str r1, [r0]

	/* ����MPLL, FCLK : HCLK : PCLK = 400m : 100m : 50m */
	/* LOCKTIME(0x4C000000) = 0xFFFFFFFF */
	ldr r0, =0x4C000000
	ldr r1, =0xFFFFFFFF
	str r1, [r0]

	/* CLKDIVN(0x4C000014) = 0X5, tFCLK:tHCLK:tPCLK = 1:4:8  */
	ldr r0, =0x4C000014
	ldr r1, =0x5
	str r1, [r0]

	/* ����CPU�������첽ģʽ */
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000   //R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0

	/* ����MPLLCON(0x4C000004) = (92<<12)|(1<<4)|(1<<0) 
	 *  m = MDIV+8 = 92+8=100
	 *  p = PDIV+2 = 1+2 = 3
	 *  s = SDIV = 1
	 *  FCLK = 2*m*Fin/(p*2^s) = 2*100*12/(3*2^1)=400M
	 */
	ldr r0, =0x4C000004
	ldr r1, =(92<<12)|(1<<4)|(1<<0)
	str r1, [r0]

	/* һ������PLL, �ͻ�����lock timeֱ��PLL����ȶ�
	 * Ȼ��CPU�������µ�Ƶ��FCLK
	 */
	
	
	/* �����ڴ�: sp ջ */
	/* �ֱ���nor/nand����
	 * д0��0��ַ, �ٶ�����
	 * ����õ�0, ��ʾ0��ַ�ϵ����ݱ��޸���, ����Ӧram, �����nand����
	 * �������nor����
	 */
	mov r1, #0
	ldr r0, [r1] /* ����ԭ����ֵ���� */
	str r1, [r1] /* 0->[0] */ 
	ldr r2, [r1] /* r2=[0] */
	cmp r1, r2   /* r1==r2? �����ȱ�ʾ��NAND���� */
	ldr sp, =0x40000000+4096 /* �ȼ�����nor���� */
	moveq sp, #4096  /* nand���� */
	streq r0, [r1]   /* �ָ�ԭ����ֵ */

	/*
	* 初始化sdram
	*/
	/* bl sdram_init1 */
	bl sdram_init2		/* 用到了有初始值的rodata里面，不能使用位置无关码 */

	/*
	* 重定位data段,rodata,data段整个程序
	*/
	bl copy2sdram

	/*
	* 清除bss段
	*/	
	bl clean_bss

	/* 
	* 1.复位之后，cpu处于svc模式(管理模式)
	* 2.现在，切换到usr模式，主要是这个用户模式
	*/
	mrs	r0, cpsr			/* 读出cpsr */
	bic r0, r0, #0xf		/* 修改m4-m0为0b10000,进入usr模式 */\
	bic r0, r0, #~(1<<7)	/* 清除I位，使能中断 */
	msr cpsr, r0			/* 把寄存器的值放入cpsr 中 */
	
	/* 设置sp_usr(usr模式下的栈) */
	ldr sp, =0x33f00000

	ldr pc, = sdram
sdram:
	bl uart0_init

	bl print1
	/* 故意加入一条未定义指令 */
und_code:
	.word 0x03000000		//0xdeadc0de,这条也是未定义指令
	
	bl print2

	/* 引入swi指令 */
	swi 0x123	/* 执行此命令，触发SWI异常,进入0x8地方执行(向量地址是0x8) */
	
	//bl main
	ldr pc, = main /* 绝对跳转，跳到SDRAM */

halt:
	b halt
	
