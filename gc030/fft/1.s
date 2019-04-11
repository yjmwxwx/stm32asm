	@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000

	.equ shumaguanma,	0x20000000
	.equ temp,		0x200000fc
	.equ fftshuchu,		0x20000100
	.equ fftshuchu1,	0x20000200
sin_2pi_16:	.long	     	38268
sin_4pi_16:	.long		70710
sin_6pi_16:	.long		92387
c_p_s_2pi_16:	.long	       130656
c_m_s_2pi_16:	.long		54119
c_p_s_6pi_16:	.long	       130656
c_m_s_6pi_16:	.long		0xffff2c98
fftshuru:	.long 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
shumaguanmabiao:
	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6
shumaguanshuaxinbiao:
	.int 0xfe00,0xfd00,0xfb00,0xf700,0xef00,0xdf00,0xbf00,0x7f00,0
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
	.word 0 @_systick +1               @ 15   
	.word 0     @ _wwdg +1          @ 0
	.word 0     @_pvd +1            @ 1
	.word 0     @_rtc +1            @ 2
	.word 0     @_flash +1          @ 3
	.word 0     @ _rcc + 1          @ 4
	.word 0      @_exti0_1  +1      @ 5
	.word 0      @ _exti2_3 +1      @ 6
	.word 0       @_exti4_15 +1     @ 7
	.word 0                         @ 8
	.word 0 	@_dma1_1  +1    @ 9
	.word 0    @_dma1_2_3 +1        @ 10
	.word 0       @_dma1_4_5 +1     @ 11
	.word 0 @_adc1 +1          @ 12
	.word 0       @_tim1_brk_up +1  @ 13
	.word 0        @ _tim1_cc +1    @ 14
	.word 0         @_tim2 +1       @ 15
	.word 0          @_tim3 +1      @ 16
	.word 0                         @ 17
	.word 0		                @ 18
	.word @_tim14 +1    @ 19
	.word 0                         @ 20
	.word 0         @_tim16 +1      @ 21
	.word 0         @_tim17 +1      @ 22
	.word 0          @_i2c   +1     @ 23
	.word 0                         @ 24
	.word 0           @_spi   +1    @ 25
	.word 0                         @ 26
	.word 0         @_usart1 +1     @ 27
	
_start:
shizhong:
	ldr r0, = 0x40021000 @ rcc
	ldr r2, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r2]           @FLASH缓冲 缓冲开启
	ldr r0, = 0x40021000 @ rcc
	ldr r1, = 0x100002
	str r1, [r0, # 0x04]
	ldr r1, = 0x1000001
	str r1, [r0]
dengrc:
	ldr r1, [r0]
	lsls r1, # 30
	bpl dengrc
dengpll:
	ldr r1, [r0]
	lsls r1, # 6
	bpl dengpll
	@0x34时钟控制寄存器 2 (RCC_CR2)
	movs r1, # 0x01
	str r1, [r0, # 0x34]  @ HSI开14M时钟
dengdai14mshizhongwending:
	ldr r1, [r0, # 0x34]
	lsls r1, r1, # 30     @ 左移30位
	bpl dengdai14mshizhongwending  @ 等待14M时钟稳定

neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne neicunqinglingxunhuan

	
	ldr r0, = fftshuru
	ldr r1, = fftshuchu

	@实
	ldr r2, [r0]
	ldr r3, [r0, # 0x20]
	adds r4, r2, r3
	str r4, [r1]

	ldr r2, [r0, # 0x04]
	ldr r3, [r0, # 0x24]
	adds r4, r2, r3
	str r4, [r1, # 0x04]

	ldr r2, [r0, # 0x08]
	ldr r3, [r0, # 0x28]
	adds r4, r2, r3
	str r4, [r1, # 0x08]

	ldr r2, [r0, # 0x0c]
	ldr r3, [r0, # 0x2c]
	adds r4, r2, r3
	str r4, [r1, # 0x0c]

	ldr r2, [r0, # 0x10]
	ldr r3, [r0, # 0x30]
	adds r4, r2, r3
	str r4, [r1, # 0x10]

	ldr r2, [r0, # 0x14]
	ldr r3, [r0, # 0x34]
	adds r4, r2, r3
	str r4, [r1, # 0x14]

	ldr r2, [r0, # 0x18]
	ldr r3, [r0, # 0x38]
	adds r4, r2, r3
	str r4, [r1, # 0x18]

	ldr r2, [r0, # 0x1c]
	ldr r3, [r0, # 0x3c]
	adds r4, r2, r3
	str r4, [r1, # 0x1c]

	@虚
	ldr r2, [r0]
	ldr r3, [r0, # 0x20]
	subs r4, r2, r3
	str r4, [r1, # 0x20]

	ldr r2, [r0, # 0x04]
	ldr r3, [r0, # 0x24]
	subs r4, r2, r3
	str r4, [r1, # 0x24]

	ldr r2, [r0, # 0x08]
	ldr r3, [r0, # 0x28]
	subs r4, r2, r3
	str r4, [r1, # 0x28]

	ldr r2, [r0, # 0x0c]
	ldr r3, [r0, # 0x2c]
	subs r4, r2, r3
	str r4, [r1, # 0x2c]

	ldr r2, [r0, # 0x30]
	ldr r3, [r0, # 0x10]
	subs r4, r2, r3
	str r4, [r1, # 0x30]

	ldr r2, [r0, # 0x34]
	ldr r3, [r0, # 0x14]
	subs r4, r2, r3
	str r4, [r1, # 0x34]

	ldr r2, [r0, # 0x38]
	ldr r3, [r0, # 0x18]
	subs r4, r2, r3
	str r4, [r1, # 0x38]

	ldr r2, [r0, # 0x3c]
	ldr r3, [r0, # 0x1c]
	subs r4, r2, r3
	str r4, [r1, # 0x3c]

	@@@@@@@@@@@@@@@
	
	ldr r2, [r1, # 0x34]
	ldr r3, [r1, # 0x24]
	ldr r4, = sin_2pi_16
	ldr r4, [r4]
	subs r2, r2, r3
	muls r2, r2, r4
	mov r5, r2                      @ 
	
	ldr r2, [r1, # 0x24]
	ldr r6, = c_p_s_2pi_16
	ldr r6, [r6]
	muls r2, r2, r6
	adds r2, r2, r5
	str r2, [r1, # 0x24]          @ 0x17c

	ldr r2, [r1, # 0x34]
	ldr r6, = c_m_s_2pi_16
	ldr r6, [r6]
	muls r2, r2, r6
	adds r2, r2, r5
	str r2, [r1, # 0x34]        @ 0x188

	ldr r2, [r1, # 0x38]
	ldr r6, = sin_4pi_16
	ldr r6, [r6]
	muls r2, r2, r6           @ 0x190

	ldr r3, [r1, # 0x28]
	muls r3, r3, r6          @ 0x194

	subs r2, r2, r3
	str r2, [r1, # 0x38]    @ 0x198

	adds r2, r2, r3
	adds r2, r2, r3
	str r2, [r1, # 0x28]  @ 0x19e

	ldr r2, [r1, # 0x3c]
	ldr r3, [r1, # 0x2c]
	ldr r6, = sin_6pi_16
	ldr r6, [r6]
	subs r4, r2, r3
	muls r4, r4, r6         @ 0x1aa

	ldr r6, = c_p_s_6pi_16
	ldr r6, [r6]
	muls r3, r3, r6
	adds r3, r3, r4
	str r3, [r1, # 0x2c]   @ 0x1b4

	ldr r6, = c_m_s_6pi_16
	ldr r6, [r6]
	muls r2, r2, r6
	adds r2, r2, r4
	str r2, [r1, # 0x3c]   @ 0x1be 有点问题

	@@@@@@@@@@@@@@@@@@@@@

	ldr r2, [r1, # 0x20]
	ldr r3, [r1, # 0x28]
	adds r2, r2, r3
	str r2, [r1, # 0x20] @ 0x1c6

	subs r2, r2, r3
	subs r2, r2, r3
	str r2, [r1, # 0x28] @ 0x1cc

	ldr r2, [r1, # 0x38]
	ldr r3, [r1, # 0x30]
	adds r3, r3, r2
	str r3, [r1, # 0x30] @ 0x1d4

	subs r3, r3, r2
	subs r3, r3, r2
	str r3, [r1, # 0x38]  @ 0x1da

	ldr r2, [r1, # 0x24]
	ldr r3, [r1, # 0x2c]
	adds r2, r2, r3
	str r2, [r1, # 0x24]  @ 0x1e2

	subs r2, r2, r3
	subs r2, r2, r3
	str r2, [r1, # 0x2c]  @ 0x1e8

	ldr r2, [r1, # 0x34]
	ldr r3, [r1, # 0x3c]
	adds r2, r2, r3
	str r2, [r1, # 0x34]     @ 0x1f0 结果有点不一样

	subs r2, r2, r3
	subs r2, r2, r3
	str r2, [r1, # 0x3c]    @ 0x1f6
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	ldr r7, = fftshuchu1
	ldr r2, [r1, # 0x20]
	ldr r3, [r1, # 0x24]
	adds r4, r2, r3
	str r4, [r7, # 0x04]      @ 0x200

	subs r5, r2, r3
	str r5, [r7, # 0x1c]     @ 0x204

	ldr r2, [r1, # 0x30]
	ldr r3, [r1, # 0x34]
	adds r4, r2, r3
	str r4, [r7, # 0x24]     @0x20c 不一样，差一点

	subs r3, r3, r2
	str r3, [r7, # 0x3c]    @ 0x210

	ldr r2, [r1, # 0x28]
	ldr r3, [r1, # 0x2c]
	ldr r4, [r1, # 0x38]
	ldr r5, [r1, # 0x3c]
	adds r6, r2, r5
	str r6, [r7, # 0x14]   @ 0x21c 不一样
	
	subs r6, r4, r3
	str r6, [r7, # 0x34]   @ 0x220
	
	subs r6, r2, r5
	str r6, [r7, # 0x0c]  @ 0x224 相差8

	movs r2, # 0
	subs r2, r2, r4
	subs r6, r2, r3
	str r6, [r7, # 0x2c]  @ 0x22c

	
	ldr r2, [r1]
	ldr r3, [r1, # 0x10]
	ldr r4, [r1, # 0x14]
	ldr r5, [r1, # 0x18]
	adds r6, r2, r4            @ out0=out0+out4
	str r6, [r1]              @0x238 相差差2
	
	subs r6, r2, r3
	subs r6, r6, r3
	str r6, [r1, # 0x10]
	ldr r6, [r1, # 0x04]
	adds r6, r6, r4
	str r6, [r1, # 0x04]       @ 0x23e
	
	subs r6, r6, r4
	subs r6, r6, r4
	str r6, [r1, # 0x14]   	   @ 0x24a
	
	ldr r2, [r1, # 0x08]
	adds r2, r2, r5
	str r2, [r1, # 0x08]   	   @ 0x250
	
	subs r2, r2, r5
	subs r2, r2, r5
	str r2, [r1, # 0x18]      @ 0x256 out6=out2-out6-out6
	
	ldr r2, [r1, # 0x0c]
	ldr r3, [r1, # 0x1c]
	adds r2, r2, r3
	str r2, [r1, # 0x0c]      @ 0x25e
	
	subs r2, r2, r3
	subs r2, r2, r3          @ 0x262
	str r2, [r1, # 0x1c]

	ldr r2, [r1]		@ output[0]=out0+out2
	ldr r3, [r1, # 0x08]
	adds r6, r2, r3
	str r6, [r7]            @ 0x26a 差了2

	subs r6, r2, r3
	str r6, [r7, # 0x10]   @ 0x26e
	
	ldr r2, [r1, # 0x04]
	ldr r3, [r1, # 0x0c]
	adds r2, r2, r3
	str r2, [r1, # 0x04]  @  0x270
	
	adds r3, r3, r3
	subs r3, r3, r2
	str r3, [r7, # 0x30]
	
	ldr r3, [r7]
	adds r3, r3, r2
	str r3, [r7]              @output[0] +=out1
	subs r3, r3, r2
	subs r3, r3, r2
	str r3, [r7, # 0x20]     @ 0x288

	ldr r2, = sin_4pi_16
	ldr r2, [r2]
	ldr r4, [r1, # 0x14]
	ldr r5, [r1, # 0x1c]
	muls r4, r4, r2
	str r4, [r1, # 0x14]      @ 0x294
	
	muls r5, r5, r2
	str r5, [r1, # 0x1c] 	@ 0x29a
	
	subs r4, r4, r5
	str r4, [r1, # 0x14]	@0x29e
	
	adds r4, r4, r5
	adds r4, r4, r5
	str r4, [r1, # 0x1c] 	@ 0x2a4

	ldr r2, [r1, # 0x18]
	ldr r3, [r1, # 0x1c]
	subs r2, r2, r3
	str r2, [r7, # 0x38]	@ 0x2ac

	ldr r2, [r1, # 0x14]
	ldr r3, [r1, # 0x10]
	adds r6, r2, r3
	str r6, [r7, # 0x08]

	subs r3, r3, r2
	str r3, [r7, # 0x18]

	movs r4, # 0
	ldr r2, [r1, # 0x1c]
	ldr r3, [r1, # 0x18]
	subs r4, r4, r2
	subs r4, r4, r3
	str r4, [r7, # 0x28]

	
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
