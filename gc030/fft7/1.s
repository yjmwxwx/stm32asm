	@ stm32f030f4p6 asm
	@fft 8点
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000
shuru:	.int 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.int 16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
hudie:	.int 0,64,32,96,16,80,48,112,8,72,40,104,24,88,56,120
	.int 4,68,36,100,20,84,52,116,12,76,44,108,28,92,60,124
.section .text
vectors:        
        .word STACKINIT         
        .word _start + 1        
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
        .word 0 
        .word 0    
        .word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word _svc_handler +1
	.word 0 
	.word 0
	.word _pendsv_handler +1
	
_start:
_fftjisuan:
_fft1:	
	ldr r0, = shuru
	ldr r1, = 0x20000000
	movs r2, # 16
	ldr r3, = hudie
_fft1xunhuan:
	ldm r3!, {r6,r7}
	ldr r6, [r0, r6]
	ldr r7, [r0, r7]
	adds r4, r6, r7
	subs r5, r6, r7
	stmia r1!, {r4,r5}
	ldmia r3!, {r6, r7}
	ldr r6, [r0, r6]
	ldr r7, [r0, r7]
	adds r4, r6, r7
	subs r5, r6, r7
	stmia r1!, {r4, r5}
	
	subs r2, r2, # 2
	bne _fft1xunhuan
_fft2:
	ldr r0, = 0x20000000
	mov r1, r0
	adds r1, r1, # 0x80
	mov r8, r1
	mov r9, r1
_fft2xunhuan:
	ldr r1, [r0]                @0
	ldr r2, [r0, # 0x08]	    @4
	adds r4, r1, r2
	movs r5, # 0
	subs r6, r1, r2
	movs r7, # 0
	mov r1, r9
	str r4, [r1]
	str r5, [r1, # 0x04]
	str r6, [r1, # 0x10]
	str r7, [r1, # 0x14]
	mov r9, r1
	ldr r1, [r0, # 0x04]	    @2
	ldr r2, [r0, # 0x0c]	    @6
	movs r3, # 0
	subs r3, r3, # 32
	muls r2, r2, r3
	mov r4, r1
	movs r5, r2
	mov r6, r4
	subs r7, r1, r2
	mov r1, r9
	str r4, [r1, # 0x08]
	str r5, [r1, # 0x0c]
	str r6, [r1, # 0x18]
	str r7, [r1, # 0x1c]
	adds r1, r1, # 0x20
	mov r9, r1
	adds r0, r0, # 0x10
	cmp r0, r8
	bne _fft2xunhuan
	bkpt
_fft3:
	ldr r0, = 0x20000fc0
	mov r1, r0
	subs r1, r1, # 0x80
	subs r1, r1, # 0x80
	mov r11, r1
_fft3xunhuan:
@@@@@@11111111111111111111111111111111111111111111111111
	ldr r4, [r0, # 0x30]
	ldr r5, [r0, # 0x34]
	ldr r6, [r0, # 0x10]
	ldr r7, [r0, # 0x14]

	adds r0, r4, r6
	movs r3, # 0
	subs r6, r4, r6
	mov r7, r3
	push {r0,r3,r6,r7}
	mov r0, r8
@@@@@@@222222222222222222222222222222222222222222222222
        ldr r4, [r0, # 0x20]
	ldr r5, [r0, # 0x24]
	ldr r6, [r0]
	ldr r7, [r0, # 0x04]
	movs r3, # 22               @sr
	movs r2, # 0               @si
	subs r2, r2, # 22
	mov r1, r6
	muls r1, r1, r3
	mov r8, r0
	mov r0, r7
	muls r0, r0, r2
	subs r1, r1, r0            @dr实
	mov r9, r1
	mov r1, r6
	muls r1, r1, r2
	mov r0, r7
	muls r0, r0, r3
	adds r1, r1, r0            @di虚
	mov r2, r9
	adds r0, r4, r2
	adds r3, r5, r1
	subs r6, r4, r2
	subs r7, r5, r1
	push {r0,r3,r6,r7}       @R0=1实，r3=1虚,r6=8实，r7=8虚
	mov r0, r8
	subs r0, r0, # 0x40

	
	
	

_tingting:
	b _tingting
		
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
