.text
.global _start

_start:
	b reset	/* vector 0: reset */
	b do_und	/* vectro 4:und */

reset:

do_und:
	/* sp undæœªè®¾ç½®ï¼Œå…ˆè®¾ç½®å®ƒ */
	ldr sp, = 0x34000000
	
	stmdb sp!, {r0-r12, lr}	/* åœ¨undå¼‚å¸¸å¤„ç†å‡½æ•°ä¸­æœ‰å¯èƒ½ä¼šä¿®æ”¹r0-r12ï¼Œæ‰€ä»¥å…ˆä¿å­˜ä¸‹æ¥ */
	
	/* ä¿å­˜ç°åœº */	
	/* å¤„ç†undå¼‚å¸¸ */
	mrs r0, cpsr
	ldr r1, = und_string
	bl printException
	
	/* æ¢å¤ç°åœº */
	ldmfa sp!, {r0-r12, pc}^	/*å°–æ‹¬å·ä¼šæŠŠspsrçš„å€¼æ¢å¤åˆ°cpsrä¸­*/ 
	
und_string:
	.string "undefined instruction exception"

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
	bl sdram_init2		/* ç”¨åˆ°äº†æœ‰åˆå§‹å€¼çš„rodataé‡Œé¢ï¼Œä¸èƒ½ä½¿ç”¨ä½ç½®æ— å…³ç  */

	/*
	* é‡å®šä½dataæ®µ,rodata,dataæ®µæ•´ä¸ªç¨‹åº
	*/
	bl copy2sdram

	/*
	* æ¸…é™¤bssæ®µ
	*/	
	bl clean_bss

	/* æ•…æ„åŠ å…¥ä¸€æ¡æœªå®šä¹‰æŒ‡ä»¤ */
und_code:
	.word 0xff123456

	//bl main
	ldr pc, = main /* ç»å¯¹è·³è½¬ï¼Œè·³åˆ°SDRAM */

halt:
	b halt
	
