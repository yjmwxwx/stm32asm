	@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000

	.equ shumaguanma,	0x20000000
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


stage_rfft_f32:				@ CODE XREF: arm_rfft_fast_f32+38p


		PUSH	{R4-R7,LR}	@ Alternative name is 'BuildAttributes$$THM_ISAv3M$S$PE$A:L22$X:L11$S22$IEEE1$IW$USESV6$~STKCKD$USESV7$~SHL$OTIME$EBA8$REQ8$PRES8$EABIv2'
		LDRH	R7, [R0]
		LDR	R5, [R0,#0x14]
		SUB	SP, SP,	#0x3C
		SUBS	R0, R7,	#1
		STR	R0, [SP,#0x30]
		MOV	R4, R2
		LDR	R2, [R1,#4]
		LDR	R0, [R1]
		MOV	R6, R1
		MOV	R1, R0
		STR	R2, [SP,#8]
		ADDS	R5, #8
		STR	R2, [SP,#0x10]
		BL	__aeabi_fadd
		STR	R0, [SP,#4]
		LDR	R1, [SP,#0x10]
		LDR	R0, [SP,#8]
		BL	__aeabi_fadd
		MOV	R1, R0
		STR	R0, [SP]
		LDR	R0, [SP,#4]
		BL	__aeabi_fadd
		MOVS	R1, #0
		MVNS	R1, R1
		BL	__ARM_scalbnf
		STMIA	R4!, {R0}
		LDR	R1, [SP]
		LDR	R0, [SP,#4]
		BL	__aeabi_fsub
		MOVS	R1, #0
		MVNS	R1, R1
		BL	__ARM_scalbnf
		STMIA	R4!, {R0}
		LSLS	R0, R7,	#3
		SUBS	R0, #8
		ADDS	R7, R0,	R6
		ADDS	R6, #8

loc_60:					@ CODE XREF: stage_rfft_f32+F6j
		LDR	R0, [R7,#4]
		STR	R0, [SP,#8]
		LDR	R0, [R7]
		STR	R0, [SP,#0xC]
		LDR	R0, [R6]
		STR	R0, [SP,#0x14]
		LDR	R0, [R6,#4]
		STR	R0, [SP,#0x10]
		LDR	R0, [R5]
		STR	R0, [SP,#0x1C]
		LDR	R0, [R5,#4]
		STR	R0, [SP,#0x18]
		ADDS	R5, #8
		LDR	R1, [SP,#0x14]
		LDR	R0, [SP,#0xC]
		BL	__aeabi_fsub
		STR	R0, [SP,#4]
		LDR	R1, [SP,#0x10]
		LDR	R0, [SP,#8]
		BL	__aeabi_fadd
		STR	R0, [SP]
		LDR	R1, [SP,#4]
		LDR	R0, [SP,#0x1C]
		BL	__aeabi_fmul
		STR	R0, [SP,#0x24]
		LDR	R1, [SP,#4]
		LDR	R0, [SP,#0x18]
		BL	__aeabi_fmul
		STR	R0, [SP,#0x28]
		LDR	R1, [SP]
		LDR	R0, [SP,#0x1C]
		BL	__aeabi_fmul
		STR	R0, [SP,#4]
		LDR	R1, [SP]
		LDR	R0, [SP,#0x18]
		BL	__aeabi_fmul
		STR	R0, [SP]
		LDR	R1, [SP,#0xC]
		LDR	R0, [SP,#0x14]
		BL	__aeabi_fadd
		LDR	R1, [SP,#0x24]
		BL	__aeabi_fadd
		LDR	R1, [SP]
		BL	__aeabi_fadd
		MOVS	R1, #0
		MVNS	R1, R1
		BL	__ARM_scalbnf
		STMIA	R4!, {R0}
		LDR	R1, [SP,#8]
		LDR	R0, [SP,#0x10]
		BL	__aeabi_fsub
		LDR	R1, [SP,#0x28]
		BL	__aeabi_fadd
		LDR	R1, [SP,#4]
		BL	__aeabi_fsub
		MOVS	R1, #0
		MVNS	R1, R1
		BL	__ARM_scalbnf
		STMIA	R4!, {R0}
		LDR	R0, [SP,#0x30]
		ADDS	R6, #8
		SUBS	R0, R0,	#1
		SUBS	R7, #8
		STR	R0, [SP,#0x30]
		CMP	R0, #0
		BNE	loc_60
		ADD	SP, SP,	#0x3C
		POP	{R4-R7,PC}

merge_rfft_f32:				@ CODE XREF: arm_rfft_fast_f32+16p


		PUSH	{R4-R7,LR}
		MOV	R6, R1
		LDRH	R7, [R0]
		LDR	R1, [R0,#0x14]
		SUB	SP, SP,	#0x3C
		LDR	R0, [R6]
		STR	R0, [SP,#4]
		LDR	R0, [R6,#4]
		ADDS	R1, #8
		STR	R1, [SP,#0x2C]
		STR	R0, [SP]
		MOV	R1, R0
		MOV	R4, R2
		SUBS	R5, R7,	#1
		LDR	R0, [SP,#4]
		BL	__aeabi_fadd
		MOVS	R1, #0
		MVNS	R1, R1
		BL	__ARM_scalbnf
		STMIA	R4!, {R0}
		LDR	R1, [SP]
		LDR	R0, [SP,#4]
		BL	__aeabi_fsub
		MOVS	R1, #0
		MVNS	R1, R1
		BL	__ARM_scalbnf
		STMIA	R4!, {R0}
		LSLS	R0, R7,	#3
		SUBS	R0, #8
		ADDS	R7, R0,	R6
		ADDS	R6, #8
		CMP	R5, #0
		BEQ	loc_1F0

loc_14E:				@ CODE XREF: merge_rfft_f32+EAj
		LDR	R0, [R7,#4]
		STR	R0, [SP,#0x18]
		LDR	R0, [R7]
		STR	R0, [SP,#0x28]
		LDR	R0, [R6]
		STR	R0, [SP,#4]
		LDR	R0, [R6,#4]
		STR	R0, [SP]
		LDR	R0, [SP,#0x2C]
		LDR	R0, [R0]
		STR	R0, [SP,#0x14]
		LDR	R0, [SP,#0x2C]
		LDR	R1, [R0,#4]
		ADDS	R0, #8
		STR	R1, [SP,#0x10]
		STR	R0, [SP,#0x2C]
		LDR	R1, [SP,#0x28]
		LDR	R0, [SP,#4]
		BL	__aeabi_fsub
		STR	R0, [SP,#0xC]
		LDR	R1, [SP,#0x18]
		LDR	R0, [SP]
		BL	__aeabi_fadd
		STR	R0, [SP,#8]
		LDR	R1, [SP,#0xC]
		LDR	R0, [SP,#0x14]
		BL	__aeabi_fmul
		STR	R0, [SP,#0x24]
		LDR	R1, [SP,#8]
		LDR	R0, [SP,#0x10]
		BL	__aeabi_fmul
		STR	R0, [SP,#0x20]
		LDR	R1, [SP,#0xC]
		LDR	R0, [SP,#0x10]
		BL	__aeabi_fmul
		STR	R0, [SP,#0xC]
		LDR	R1, [SP,#8]
		LDR	R0, [SP,#0x14]
		BL	__aeabi_fmul
		STR	R0, [SP,#8]
		LDR	R1, [SP,#0x28]
		LDR	R0, [SP,#4]
		BL	__aeabi_fadd
		LDR	R1, [SP,#0x24]
		BL	__aeabi_fsub
		LDR	R1, [SP,#0x20]
		BL	__aeabi_fsub
		MOVS	R1, #0
		MVNS	R1, R1
		BL	__ARM_scalbnf
		STMIA	R4!, {R0}
		LDR	R1, [SP,#0x18]
		LDR	R0, [SP]
		BL	__aeabi_fsub
		LDR	R1, [SP,#0xC]
		BL	__aeabi_fadd
		LDR	R1, [SP,#8]
		BL	__aeabi_fsub
		MOVS	R1, #0
		MVNS	R1, R1
		BL	__ARM_scalbnf
		STMIA	R4!, {R0}
		SUBS	R5, R5,	#1
		ADDS	R6, #8
		SUBS	R7, #8
		CMP	R5, #0
		BNE	loc_14E

loc_1F0:				@ CODE XREF: merge_rfft_f32+48j
		ADD	SP, SP,	#0x3C
		POP	{R4-R7,PC}

arm_rfft_fast_f32:
		PUSH	{R3-R7,LR}
		MOV	R4, R0
		LDRH	R0, [R0,#0x10]
		MOV	R5, R3
		LSRS	R0, R0,	#1
		MOV	R6, R2
		MOV	R7, R1
		STRH	R0, [R4]
		CMP	R3, #0
		BEQ	loc_21C
		MOV	R0, R4
		BL	merge_rfft_f32
		MOVS	R3, #1
		MOV	R2, R5
		MOV	R1, R6
		MOV	R0, R4
		BL	arm_cfft_f32
		POP	{R3-R7,PC}

loc_21C:				@ CODE XREF: arm_rfft_fast_f32+12j
		MOVS	R3, #1
		MOV	R2, R5
		MOV	R0, R4
		BL	arm_cfft_f32
		MOV	R2, R6
		MOV	R1, R7
		MOV	R0, R4
		BL	stage_rfft_f32
		POP	{R3-R7,PC}


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
