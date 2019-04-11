@@ 设置PLL

pllshizhong:
        str lr, [sp, #-4]! 
shizhong:
	ldr r0, = rcckz
	ldr r1, = 0x14D83
	str r1, [r0]
gsszbz: 
	ldr r2, [r0]
	ldr r1, = 0x20000
	tst r1, r2           @高速时钟标志位           
	bne rccchushihua
	b gsszbz
rccchushihua: 

	
	ldr r0, = flashacr
	mov r1, # 0x00000032
	str r1, [r0]           @FLASH缓冲 缓冲开启 

	ldr r0, = rccpz
	ldr r1, = 0x1D8400
	str r1, [r0]
	
	ldr r0, = rcckz
	ldr r1, = 0x1033D03
	str r1, [r0]
chaxun:
	ldr r2, [r0]
	ldr r1, = 0x2000000
	tst r1, r2
	bne rccgg
	b chaxun
rccgg:

	ldr r0, = rccpz
	ldr r1, = 0x1D8402
	str r1, [r0]

        ldr pc, [sp], #4  
