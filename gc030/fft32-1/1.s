	@ stm32f030f4p6 asm
	@fft 32点
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000
	.equ xuanzhuanyinzi,		0x20000120
xinxi:	.ascii "fft-32dian-2018-01-04"
	.align 4
shuru:
	.int 0x0000,0x11BB,0xFFFFFAA2,0x0C71,0xFFFFE8D1,0x05BF,0x0864,0x04B1,0x0F3B,0xFFFFE92E,0x096D,0xFFFFFE0E,0x0F55,0x0DDB,0xFFFFEFB6,0x09B2,0xFFFFF5B6,0x17B2,0x09B1,0xFFFFFB0C,0x0667,0xFFFFF199,0x1B56,0x04D5,0x0876,0x00AC,0xFFFFF293,0x18F7,0x0157,0x149B,0xFFFFFA94,0xFFFFF7F1
	
hudie:	.int 0,64,32,96,16,80,48,112,8,72,40,104,24,88,56,120
	.int 4,68,36,100,20,84,52,116,12,76,44,108,28,92,60,124
fft3xuanzhuanyinzi:
	.int 0x8000,0x0000,0x5A82,0xFFFFA57E,0x0000,0xFFFF8000,0xFFFFA57E,0xFFFFA57E
fft4xuanzhuanyinzi:
	.int 0x8000,0x0000,0x7641,0xFFFFCF05,0x5A82,0xFFFFA57E,0x30FB,0xFFFF89BF,0x0000,0xFFFF8000,0xFFFFCF05,0xFFFF89BF,0xFFFFA57E,0xFFFFA57E,0xFFFF89BF,0xFFFFCF05
fft5xuanzhuanyinzi:
	.int	0x8000,0x0000,0x7D8A,0xFFFFE708,0x7641,0xFFFFCF05,0x6A6D,0xFFFFB8E4,0x5A82,0xFFFFA57E,0x471C,0xFFFF9593,0x30FB,0xFFFF89BF,0x18F8,0xFFFF8276,0x0000,0xFFFF8000,0xFFFFE708,0xFFFF8276,0xFFFFCF05,0xFFFF89BF,0xFFFFB8E4,0xFFFF9593,0xFFFFA57E,0xFFFFA57E,0xFFFF9593,0xFFFFB8E4,0xFFFF89BF,0xFFFFCF05,0xFFFF8276,0xFFFFE708

	
	           
	           
	
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
	.align 2
_start:
_shizhong:	                     @时钟设置
	ldr r2, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r2]
	ldr r0, = 0x40021000 @ rcc
	@0x34时钟控制寄存器 2 (RCC_CR2)
	movs r1, # 0x01
	str r1, [r0, # 0x34]  @ HSI开14M时钟
_dengdai14mshizhongwending:	    @等14M时钟稳定
	ldr r1, [r0, # 0x34]
	lsls r1, r1, # 30     @ 左移30位
	bpl _dengdai14mshizhongwending  @ 等待14M时钟稳定

_neicunqingling:	                         @ 0x1000的内存清零
	                                 @ 1K=1024BIT=0X400
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
_neicunqinglingxunhuan:	                   @ 内存清零循环
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan                @



	
_fftjisuan:
_fft1:	
	ldr r0, = shuru
	ldr r1, = 0x20000000
	movs r2, # 16
	ldr r3, = hudie
_fft1xunhuan:
	ldr r6, [r3]
	ldr r7, [r3, # 0x04]
	ldr r6, [r0, r6]
	ldr r7, [r0, r7]
	adds r4, r6, r7
	subs r5, r6, r7
	str r4, [r1]
	str r5, [r1, # 0x04]
	adds r1, r1, # 0x08
	adds r3, r3, # 0x08
	subs r2, r2, # 1
	bne _fft1xunhuan
	
_fft2:
	ldr r0, = 0x20000000
	mov r4, r0
	adds r4, r4, # 0x80
	mov r8, r4
_fft2xunhuan:
	ldr r4, [r0]
	ldr r5, [r0, # 0x08]
	ldr r6, [r0, # 0x04]
	ldr r7, [r0, # 0x0c]
	adds r1, r4, r5
	subs r2, r4, r5
	mov r3, r6		@0r
	movs r4, # 0	
	subs r4, r4, r7		@0i
	mov r5, r6		@3r
	mov r6, r7		@3i
	mov r7, r0
	adds r7, r7, # 0x80
	str r1, [r0]
	str r2, [r0, # 0x08]
	str r3, [r0, # 0x04]
	str r4, [r7, # 0x04]
	str r5, [r0, # 0x0c]
	str r6, [r7, # 0x0c]
	adds r0, r0, # 0x10
	cmp r0, r8
	bne _fft2xunhuan
_fft3:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft3xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, r0
	adds r1, r1, # 0x80
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x10
	mov r11, r5
	movs r5, # 4
	mov r12, r5
	bl _fftg
_fft4:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft4xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, r0
	adds r1, r1, # 0x80
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x20
	mov r11, r5
	movs r5, # 8
	mov r12, r5
	bl _fftg
_fft5:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft5xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, r0
	adds r1, r1, # 0x80
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x40
	mov r11, r5
	movs r5, # 16
	mov r12, r5
	bl _fftg
	
	
tingting:
	b tingting
_fftg:
	push {lr}
	movs r4, # 0
	mov lr, r4
_fftxunhuan:
	mov r0, r9
	mov r1, r8
	mov r2, r10
	mov r3, r11
	ldr r4, [r0]
	ldr r5, [r1]
	ldr r6, [r0, r3]
	ldr r7, [r1, r3]
	ldr r3, [r2]		@sr
	ldr r2, [r2, # 0x04]	@si
	push {r4,r5}
	mov r4, r6
	muls r4, r4, r3
	mov r5, r7
	muls r5, r5, r2
	subs r4, r4, r5		@r	
	asrs r4, r4, # 15
	mov r5, r6
	muls r5, r5, r2
	muls r7, r7, r3
	adds r7, r7, r5		@i
	asrs r7, r7, # 15
	pop {r2,r5}
	adds r3, r2, r4    @0r
	subs r2, r2, r4    @1r
	adds r4, r5, r7
	subs r5, r5, r7
	mov r6, r11
	str r3, [r0]
	str r4, [r1]
	str r2, [r0, r6]
	str r5, [r1, r6]
	adds r0, r0, # 0x04
	adds r1, r1, # 0x04
	mov r9, r0
	mov r8, r1
	mov r2, r10
	adds r2, r2, # 0x08
	mov r10, r2
	mov r4, lr
	adds r4, r4, # 1
	mov lr, r4
	mov r7, r12
	cmp r4, r7
	bne _fftxunhuan
	movs  r4, # 0
	ldr r6, = xuanzhuanyinzi
	ldr r5, = 0x20000080
	ldr r6, [r6]
	mov r10, r6
	mov lr, r4
	mov r7, r11
	adds r0, r0, r7
	adds r1, r1, r7
	mov r9, r0
	mov r8, r1
	cmp r0, r5
	bne _fftxunhuan
	pop {pc}
		
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
