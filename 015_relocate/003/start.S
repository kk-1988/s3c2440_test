
.text
.global _start

_start:

	/* πÿ±’ø¥√≈π∑ */
	ldr r0, =0x53000000
	ldr r1, =0
	str r1, [r0]

	/* …Ë÷√MPLL, FCLK : HCLK : PCLK = 400m : 100m : 50m */
	/* LOCKTIME(0x4C000000) = 0xFFFFFFFF */
	ldr r0, =0x4C000000
	ldr r1, =0xFFFFFFFF
	str r1, [r0]

	/* CLKDIVN(0x4C000014) = 0X5, tFCLK:tHCLK:tPCLK = 1:4:8  */
	ldr r0, =0x4C000014
	ldr r1, =0x5
	str r1, [r0]

	/* …Ë÷√CPUπ§◊˜”⁄“Ï≤Ωƒ£ Ω */
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000   //R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0

	/* …Ë÷√MPLLCON(0x4C000004) = (92<<12)|(1<<4)|(1<<0) 
	 *  m = MDIV+8 = 92+8=100
	 *  p = PDIV+2 = 1+2 = 3
	 *  s = SDIV = 1
	 *  FCLK = 2*m*Fin/(p*2^s) = 2*100*12/(3*2^1)=400M
	 */
	ldr r0, =0x4C000004
	ldr r1, =(92<<12)|(1<<4)|(1<<0)
	str r1, [r0]

	/* “ªµ©…Ë÷√PLL, æÕª·À¯∂®lock time÷±µΩPLL ‰≥ˆŒ»∂®
	 * »ª∫ÛCPUπ§◊˜”⁄–¬µƒ∆µ¬ FCLK
	 */
	
	

	/* …Ë÷√ƒ⁄¥Ê: sp ’ª */
	/* ∑÷±Ê «nor/nand∆Ù∂Ø
	 * –¥0µΩ0µÿ÷∑, ‘Ÿ∂¡≥ˆ¿¥
	 * »Áπ˚µ√µΩ0, ±Ì æ0µÿ÷∑…œµƒƒ⁄»›±ª–ﬁ∏ƒ¡À, À¸∂‘”¶ram, ’‚æÕ «nand∆Ù∂Ø
	 * ∑Ò‘ÚæÕ «nor∆Ù∂Ø
	 */
	mov r1, #0
	ldr r0, [r1] /* ∂¡≥ˆ‘≠¿¥µƒ÷µ±∏∑› */
	str r1, [r1] /* 0->[0] */ 
	ldr r2, [r1] /* r2=[0] */
	cmp r1, r2   /* r1==r2? »Áπ˚œ‡µ»±Ì æ «NAND∆Ù∂Ø */
	ldr sp, =0x40000000+4096 /* œ»ºŸ…Ë «nor∆Ù∂Ø */
	moveq sp, #4096  /* nand∆Ù∂Ø */
	streq r0, [r1]   /* ª÷∏¥‘≠¿¥µƒ÷µ */

	/*
	* ÈáçÂÆö‰ΩçdataÊÆµ
	*/
	mov r1, #0x800
	ldr r0, [r1]
	mov r1, #0x30000000
	str r0, [r1]

	bl main

halt:
	b halt
	
