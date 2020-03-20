
.text
.global _start

_start:

	/* ¹Ø±Õ¿´ÃÅ¹· */
	ldr r0, =0x53000000
	ldr r1, =0
	str r1, [r0]

	/* ÉèÖÃMPLL, FCLK : HCLK : PCLK = 400m : 100m : 50m */
	/* LOCKTIME(0x4C000000) = 0xFFFFFFFF */
	ldr r0, =0x4C000000
	ldr r1, =0xFFFFFFFF
	str r1, [r0]

	/* CLKDIVN(0x4C000014) = 0X5, tFCLK:tHCLK:tPCLK = 1:4:8  */
	ldr r0, =0x4C000014
	ldr r1, =0x5
	str r1, [r0]

	/* ÉèÖÃCPU¹¤×÷ÓÚÒì²½Ä£Ê½ */
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000   //R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0

	/* ÉèÖÃMPLLCON(0x4C000004) = (92<<12)|(1<<4)|(1<<0) 
	 *  m = MDIV+8 = 92+8=100
	 *  p = PDIV+2 = 1+2 = 3
	 *  s = SDIV = 1
	 *  FCLK = 2*m*Fin/(p*2^s) = 2*100*12/(3*2^1)=400M
	 */
	ldr r0, =0x4C000004
	ldr r1, =(92<<12)|(1<<4)|(1<<0)
	str r1, [r0]

	/* Ò»µ©ÉèÖÃPLL, ¾Í»áËø¶¨lock timeÖ±µ½PLLÊä³öÎÈ¶¨
	 * È»ºóCPU¹¤×÷ÓÚĞÂµÄÆµÂÊFCLK
	 */
	
	

	/* ÉèÖÃÄÚ´æ: sp Õ» */
	/* ·Ö±æÊÇnor/nandÆô¶¯
	 * Ğ´0µ½0µØÖ·, ÔÙ¶Á³öÀ´
	 * Èç¹ûµÃµ½0, ±íÊ¾0µØÖ·ÉÏµÄÄÚÈİ±»ĞŞ¸ÄÁË, Ëü¶ÔÓ¦ram, Õâ¾ÍÊÇnandÆô¶¯
	 * ·ñÔò¾ÍÊÇnorÆô¶¯
	 */
	mov r1, #0
	ldr r0, [r1] /* ¶Á³öÔ­À´µÄÖµ±¸·İ */
	str r1, [r1] /* 0->[0] */ 
	ldr r2, [r1] /* r2=[0] */
	cmp r1, r2   /* r1==r2? Èç¹ûÏàµÈ±íÊ¾ÊÇNANDÆô¶¯ */
	ldr sp, =0x40000000+4096 /* ÏÈ¼ÙÉèÊÇnorÆô¶¯ */
	moveq sp, #4096  /* nandÆô¶¯ */
	streq r0, [r1]   /* »Ö¸´Ô­À´µÄÖµ */

	/*
	* åˆå§‹åŒ–sdram
	*/
	/* bl sdram_init1 */
	bl sdram_init2		//ç”¨åˆ°äº†æœ‰åˆå§‹å€¼çš„rodataé‡Œé¢ï¼Œä¸èƒ½ä½¿ç”¨ä½ç½®æ— å…³ç 

	/*
	* é‡å®šä½dataæ®µ,rodata,dataæ®µæ•´ä¸ªç¨‹åº
	*/
	mov r0, #0
	ldr r1, = _start		/* ç¬¬1æ¡æŒ‡ä»¤è¿è¡Œæ—¶åœ°å€ */
	ldr r2, = bss_start		/* bssæ®µçš„èµ·å§‹åœ°å€ */
	sub r2, r2, r1			/* r2 = r2 - r1 */

	bl copy2sdram		/* ç›´æ¥è°ƒç”¨cå‡½æ•°,éœ€è¦çš„å‚æ•°ä¸º=> src,dst,len */

	/*
	* æ¸…é™¤bssæ®µ
	*/
	ldr r0, = bss_start
	ldr r1, = bss_end
	
	bl clean_bss	/* cå‡½æ•°ï¼Œç”¨äºæ¸…é™¤bssæ®µï¼Œéœ€è¦çš„å‚æ•°ä¸ºstartï¼Œend */
	

	bl main

halt:
	b halt
	
