	 .thumb                 
         .syntax unified
.section .data
fftbiao:
	.short  0x4000,0x0000,0x4000,0x0000,0x4000,0x0000,0xdd5d,0x3b21,0x22a3,0x187e,0x0000,0x2d41,0xa57e,0x2d41,0x0000,0x2d41,0xc000,0x4000,0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41, 0x4000,0x0000, 0x4000,0x0000, 0x4000,0x0000,0x2aaa,0x1294, 0x396b,0x0646, 0x3249,0x0c7c,0x11a8,0x238e, 0x3249,0x0c7c, 0x22a3,0x187e,0xf721,0x3179, 0x2aaa,0x1294, 0x11a8,0x238e,0xdd5d,0x3b21, 0x22a3,0x187e, 0x0000,0x2d41, 0xc695,0x3fb1, 0x1a46,0x1e2b, 0xee58,0x3537, 0xb4be,0x3ec5, 0x11a8,0x238e, 0xdd5d,0x3b21,0xa963,0x3871, 0x08df,0x289a, 0xcdb7,0x3ec5,0xa57e,0x2d41, 0x0000,0x2d41, 0xc000,0x4000,0xa963,0x1e2b, 0xf721,0x3179, 0xb4be,0x3ec5,0xb4be,0x0c7c, 0xee58,0x3537, 0xac61,0x3b21,0xc695,0xf9ba, 0xe5ba,0x3871, 0xa73b,0x3537,0xdd5d,0xe782, 0xdd5d,0x3b21, 0xa57e,0x2d41,0xf721,0xd766, 0xd556,0x3d3f, 0xa73b,0x238e,0x11a8,0xcac9, 0xcdb7,0x3ec5, 0xac61,0x187e,0x2aaa,0xc2c1, 0xc695,0x3fb1, 0xb4be,0x0c7c
	        
fftshuru:
	.long 0x00000,0x10000,0x20000,0x30000
	.long 0x40000,0x50000,0x60000,0x70000
	.long 0x80000,0x90000,0xa0000,0xb0000
	.long 0xc0000,0xd0000,0xe0000,0xf0000
	
	.long 0x100000,0x110000,0x120000,0x130000
	.long 0x140000,0x150000,0x160000,0x170000
	.long 0x180000,0x190000,0x1a0000,0x1b0000
	.long 0x1c0000,0x1d0000,0x1e0000,0x1f0000
	
        .long 0x200000,0x210000,0x220000,0x230000
	.long 0x240000,0x250000,0x260000,0x270000
	.long 0x280000,0x290000,0x2a0000,0x2b0000
	.long 0x2c0000,0x2d0000,0x2e0000,0x2f0000
	
	
	.long 0x300000,0x310000,0x320000,0x330000
	.long 0x340000,0x350000,0x360000,0x370000
	.long 0x380000,0x390000,0x3a0000,0x3b0000
	.long 0x3c0000,0x3d0000,0x3e0000,0x3f0000

	
	
	.equ STACKINIT,         0x20005000
	.equ fftshuchu,		0x20001000
.section .text
_xiangliangbiao:
	.word STACKINIT
	.word _start + 1
	.word _nmi_handler + 1
	.word _hard_fault  + 1
	.word _memory_fault + 1
	.word _bus_fault + 1
	.word _usage_fault + 1

_start:
_neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x5000
_neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan
	
	ldr r0, = fftshuchu
	ldr r1, = fftshuru
	movs r2, # 64
	bl _fft
	
tingting:

	b tingting
_fft:
	push {r4-r11,lr}
	mov r12, # 0
	mov r3, # 0
loc_c:
	add lr, r1, r12, lsr # 26
	
	ldrsh r5, [lr, # 2]
	ldrsh r4, [lr], # 0x40

	ldrsh r9, [lr, # 2]
	ldrsh r8, [lr], # 0x40

	ldrsh r7, [lr, # 2]
	ldrsh r6, [lr], # 0x40

	ldrsh r11, [lr, # 2]
	ldrsh r10, [lr], # 0x40

	add r8, r8, r10
	add r9, r9, r11
	
	sub r10, r8, r10, lsl # 1
	sub r11, r9, r11, lsl # 1

	mov r4, r4, asr # 2
	mov r5, r5, asr # 2

	add r4, r4, r6, asr # 2
	add r5, r5, r7, asr # 2

	sub r6, r4, r6, asr # 1
	sub r7, r5, r7, asr # 1

	add r4, r4, r8, asr # 2
	add r5, r5, r9, asr # 2

	sub r8, r4, r8, asr # 1
	sub r9, r5, r9, asr # 1

	add r6, r6, r11, asr # 2
	sub r7, r7, r10, asr # 2

	sub r11, r6, r11, asr # 1
	add r10, r7, r10, asr # 1

	strh r5, [r0, # 2]
	strh r4, [r0], # 4

	strh r7, [r0, # 2]
	strh r6, [r0], # 4

	strh r9, [r0, # 2]
	strh r11, [r0], # 4

	add r3, r3, # 1
	rbit r12, r3
	
	cmp r3, # 0x10
	bne loc_c

	sub r1, r0, r2, lsl # 2
	mov r3, # 0x10
	lsr r2, r2, # 4
	ldr  r0, = fftbiao
loc_ae:
	push {r1, r2}
	add r12, r3, r3, lsl # 1
	add r1, r1, r12
	sub r2, r2, # 0x10000

loc_ba:
	add r2, r2, r3, lsl # 14
loc_be:
	ldrsh r5, [r1, # 2]
	ldrsh r4, [r1]

	sub r1, r1, r3

	ldrsh r11, [r0, # 2]
	ldrsh r10, [r0]

	add r0, r0, # 4
	sub lr, r5, r4

	mul r12, lr, r11
	add lr, r10, r11, lsl # 1
	mla r11, r5, r10, r12
	mla r10, r4, lr, r12
	ldrsh r5, [r1, # 2]
	ldrsh r4, [r1]

	sub r1, r1, r3

	ldrsh r9, [r0, # 2]
	ldrsh r8, [r0]
	add r0, r0, # 4
	sub lr, r5, r4
	mul r12, lr, r9
	add lr, r8, r9, lsl # 1
	mla r9, r5, r8, r12
	mla r8, r4, lr, r12
	ldrsh r5, [r1, # 2]
	ldrsh r4, [r1]

	sub r1, r1, r3
	ldrsh r7, [r0, # 2]
	ldrsh r6, [r0]
	add r0, r0, # 4
	sub lr, r5, r4
	mul r12, lr, r7
	add lr, r6, r7, lsl # 1
	mla r7, r5, r6, r12
	mla r6, r4, lr, r12
	ldrsh r5, [r1, # 2]
	ldrsh r4, [r1]
	mov r1, r1
	add r8, r8, r10
	add r9, r9, r11
	sub r10, r8, r10, lsl # 1
	sub r11, r9, r11, lsl # 1

	mov r4, r4, asr # 2
	mov r5, r5, asr # 2

	add r4, r4, r6, asr # 16
	add r5, r5, r7, asr # 16
	sub r6, r4, r6, asr # 15
	sub r7, r5, r7, asr # 15
	add r4, r4, r8, asr # 16
	add r5, r5, r9, asr # 16
	sub r8, r4, r8, asr # 15
	sub r9, r5, r9, asr # 15
	add r6, r6, r11, asr # 16
	sub r7, r7, r10, asr # 16
	sub r11, r6, r11, asr # 16
	sub r10, r7, r10, asr # 15

	strh r5, [r1, # 2]
	strh r4, [r1]
	add r1, r1, r3
	strh r7, [r1, # 2]
	strh r4, [r1]
	add r1, r1, r3
	strh r7, [r1, # 2]
	strh r6, [r1]
	add r1, r1, r3
	strh r9, [r1, # 2]
	strh r8, [r1]
	add r1, r1, r3
	strh r10, [r1, # 2]
	strh r11, [r1], # 4
	subs r2, r2, # 0x10000
	bge loc_be
	add r12, r3, r3, lsl # 1
	add r1, r1, r12
	sub r2, r2, # 1
	movs lr, r2, lsl # 16
	it ne
	subne r0, r0, r12
	bne loc_ba
	pop {r1,r2}
	mov r3, r3, lsl # 2
	lsrs r2, r2, # 2
	bne loc_ae
	pop {r4-r11,pc}

	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_memory_fault:
	bx lr
_bus_fault:
	bx lr
_usage_fault:
 	bx lr
