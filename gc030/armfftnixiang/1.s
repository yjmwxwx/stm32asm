	@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000
shuru:	.int 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	
	
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
	.align 2
	
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
neicunxie:
	ldr r0, = 0x20000000
	ldr r2, = shuru
	movs r3, # 0
	movs r4, # 16
neicunxiexunhuan:
	ldr r1, [r2, r3]
	str r1, [r0, r3]
	adds r3, r3, # 4
	subs r4, r4, # 1
	bne neicunxiexunhuan



	ldr r0, = 0x20000000
	ldr r1, = 0x20000500
	bl arm_cfft_radix2_q15
tingtingting:
	b tingtingting
	.ltorg


arm_radix2_butterfly_q15:		
		PUSH	{R0-R7,LR}	
		SUB	SP, SP,	#0x3C
		LDR	R0, [SP,#0x40]
		STR	R0, [SP,#8]
		LSRS	R0, R0,	#1
		STR	R0, [SP,#0x2C]
		STR	R0, [SP,#4]
		MOVS	R0, #0
		STR	R0, [SP,#0x38]
		LDR	R0, [SP,#4]
		CMP	R0, #0
		BEQ	loc_D6
		MOVS	R0, #0
		STR	R0, [SP,#0]
		LDR	R0, [SP,#4]
		CMP	R0, #0
		BLS	loc_D6
		LDR	R0, [SP,#8]
		LSLS	R0, R0,	#2
		STR	R0, [SP,#0x30]
loc_30:					
		LDR	R0, [SP,#0x38]
		LDR	R1, [SP,#0x44]
		LSLS	R0, R0,	#2
		LDRSH	R1, [R1,R0]
		STR	R1, [SP,#0x28]
		LDR	R1, [SP,#0x44]
		MOVS	R4, #2
		ADDS	R0, R0,	R1
		LDRSH	R4, [R0,R4]
		LDR	R1, [SP,#0x48]
		LDR	R0, [SP,#0x38]
		ADDS	R0, R0,	R1
		STR	R0, [SP,#0x38]
		LDR	R1, [SP,#0]
		LDR	R0, [SP,#0x40]
		CMP	R0, R1
		BLS	loc_CA
		SUBS	R1, R0,	R1
		LDR	R0, [SP,#8]
		ADDS	R0, R1,	R0
		SUBS	R0, R0,	#1
		LDR	R1, [SP,#8]
		BL	__aeabi_uidivmod
		LDR	R2, [SP,#0]
		LDR	R1, [SP,#0x40]
		CMP	R2, R1
		BCS	loc_CA
		LDR	R1, [SP,#0x3C]
		LSLS	R2, R2,	#2
		ADDS	R2, R2,	R1
		LDR	R3, [SP,#4]
		LDR	R1, [SP,#0]
		ADDS	R1, R1,	R3
		LSLS	R3, R1,	#2
		LDR	R1, [SP,#0x3C]
		ADDS	R1, R3,	R1
loc_7A:					
		MOVS	R3, #0
		LDRSH	R3, [R2,R3]
		ASRS	R6, R3,	#1
		MOVS	R3, #0
		LDRSH	R3, [R1,R3]
		ASRS	R5, R3,	#1
		SUBS	R3, R6,	R5
		ADDS	R5, R6,	R5
		ASRS	R5, R5,	#1
		STRH	R5, [R2]
		MOVS	R5, #2
		LDRSH	R5, [R2,R5]
		ASRS	R6, R5,	#1
		MOVS	R5, #2
		LDRSH	R5, [R1,R5]
		ASRS	R7, R5,	#1
		SUBS	R5, R6,	R7
		ADDS	R6, R7,	R6
		ASRS	R6, R6,	#1
		STRH	R6, [R2,#2]
		LDR	R6, [SP,#0x28]
		MOV	R7, R5
		MULS	R6, R3
		MULS	R7, R4
		ASRS	R6, R6,	#0x10
		ASRS	R7, R7,	#0x10
		ADDS	R6, R6,	R7
		STRH	R6, [R1]
		LDR	R6, [SP,#0x28]
		MULS	R3, R4
		MULS	R5, R6
		ASRS	R5, R5,	#0x10
		ASRS	R3, R3,	#0x10
		SUBS	R3, R5,	R3
		STRH	R3, [R1,#2]
		LDR	R3, [SP,#0x30]
		ADDS	R2, R3,	R2
		ADDS	R1, R3,	R1
		SUBS	R0, R0,	#1
		BNE	loc_7A
loc_CA:				
		LDR	R0, [SP,#0]
		LDR	R1, [SP,#4]
		ADDS	R0, R0,	#1
		STR	R0, [SP,#0]
		CMP	R0, R1
		BCC	loc_30
loc_D6:					
		LDR	R0, [SP,#0x48]
		LSLS	R0, R0,	#0x11
		LSRS	R0, R0,	#0x10
		STR	R0, [SP,#0x48]
		LDR	R0, [SP,#0x2C]
		STR	R0, [SP,#0x30]
		CMP	R0, #2
		BLS	loc_1C2
loc_E6:					
		LDR	R0, [SP,#4]
		STR	R0, [SP,#8]
		LSRS	R0, R0,	#1
		STR	R0, [SP,#4]
		MOVS	R0, #0
		STR	R0, [SP,#0x38]
		LDR	R0, [SP,#4]
		CMP	R0, #0
		BEQ	loc_1B0
		MOVS	R0, #0
		STR	R0, [SP,#0]
		LDR	R0, [SP,#4]
		CMP	R0, #0
		BLS	loc_1B0
		LDR	R0, [SP,#8]
		LSLS	R0, R0,	#2
		STR	R0, [SP,#0x14]
loc_108:				
		LDR	R0, [SP,#0x38]
		LDR	R1, [SP,#0x44]
		LSLS	R0, R0,	#2
		LDRSH	R4, [R1,R0]
		ADDS	R0, R0,	R1
		MOVS	R5, #2
		LDRSH	R5, [R0,R5]
		LDR	R1, [SP,#0x48]
		LDR	R0, [SP,#0x38]
		ADDS	R0, R0,	R1
		STR	R0, [SP,#0x38]
		LDR	R1, [SP,#0]
		LDR	R0, [SP,#0x40]
		CMP	R0, R1
		BLS	loc_1A2
		MOV	R1, R0
		LDR	R0, [SP,#0]
		SUBS	R1, R1,	R0
		LDR	R0, [SP,#8]
		ADDS	R0, R1,	R0
		SUBS	R0, R0,	#1
		LDR	R1, [SP,#8]
		BL	__aeabi_uidivmod
		LDR	R2, [SP,#0x40]
		LDR	R1, [SP,#0]
		CMP	R1, R2
		BCS	loc_1A2
		LSLS	R2, R1,	#2
		LDR	R1, [SP,#0x3C]
		LDR	R3, [SP,#4]
		ADDS	R2, R2,	R1
		LDR	R1, [SP,#0]
		MOV	R12, R0
		ADDS	R1, R1,	R3
		LSLS	R3, R1,	#2
		LDR	R1, [SP,#0x3C]
		ADDS	R1, R3,	R1
loc_154:				
		MOVS	R3, #0
		MOVS	R0, #0
		LDRSH	R3, [R2,R3]
		LDRSH	R0, [R1,R0]
		MOVS	R7, #2
		SUBS	R6, R3,	R0
		ADDS	R0, R3,	R0
		ASRS	R0, R0,	#1
		STRH	R0, [R2]
		MOVS	R0, #2
		LDRSH	R0, [R2,R0]
		LDRSH	R7, [R1,R7]
		SXTH	R6, R6
		SUBS	R3, R0,	R7
		ADDS	R0, R7,	R0
		ASRS	R0, R0,	#1
		STRH	R0, [R2,#2]
		MOV	R0, R6
		MULS	R0, R4
		SXTH	R3, R3
		ASRS	R7, R0,	#0x10
		MOV	R0, R3
		MULS	R0, R5
		ASRS	R0, R0,	#0x10
		ADDS	R0, R7,	R0
		STRH	R0, [R1]
		MULS	R3, R4
		ASRS	R0, R3,	#0x10
		MULS	R6, R5
		ASRS	R3, R6,	#0x10
		SUBS	R0, R0,	R3
		STRH	R0, [R1,#2]
		LDR	R0, [SP,#0x14]
		ADDS	R2, R0,	R2
		ADDS	R1, R0,	R1
		MOV	R0, R12
		SUBS	R0, R0,	#1
		MOV	R12, R0
		BNE	loc_154
loc_1A2:						
		LDR	R0, [SP,#0]
		ADDS	R0, R0,	#1
		MOV	R1, R0
		STR	R0, [SP,#0]
		LDR	R0, [SP,#4]
		CMP	R1, R0
		BCC	loc_108
loc_1B0:				
		LDR	R0, [SP,#0x48]
		LSLS	R0, R0,	#0x11
		LSRS	R0, R0,	#0x10
		STR	R0, [SP,#0x48]
		LDR	R0, [SP,#0x30]
		LSRS	R0, R0,	#1
		STR	R0, [SP,#0x30]
		CMP	R0, #2
		BHI	loc_E6
loc_1C2:				
		LDR	R0, [SP,#4]
		STR	R0, [SP,#8]
		LSRS	R0, R0,	#1
		STR	R0, [SP,#4]
		BEQ	loc_236
		MOVS	R0, #0
		STR	R0, [SP,#0]
		LDR	R0, [SP,#4]
		CMP	R0, #0
		BLS	loc_236
		LDR	R0, [SP,#8]
		LSLS	R4, R0,	#2
loc_1DA:			
		LDR	R1, [SP,#0]
		LDR	R0, [SP,#0x40]
		CMP	R0, R1
		BLS	loc_22A
		SUBS	R1, R0,	R1
		LDR	R0, [SP,#8]
		ADDS	R0, R1,	R0
		SUBS	R0, R0,	#1
		LDR	R1, [SP,#8]
		BL	__aeabi_uidivmod
		LDR	R2, [SP,#0x40]
		LDR	R1, [SP,#0]
		CMP	R1, R2
		BCS	loc_22A
		LSLS	R2, R1,	#2
		LDR	R1, [SP,#0x3C]
		LDR	R3, [SP,#4]
		ADDS	R2, R2,	R1
		LDR	R1, [SP,#0]
		ADDS	R1, R1,	R3
		LSLS	R3, R1,	#2
		LDR	R1, [SP,#0x3C]
		ADDS	R1, R3,	R1
loc_20A:				
		LDRH	R6, [R2]
		LDRH	R5, [R1]
		SUBS	R3, R6,	R5
		ADDS	R5, R6,	R5
		STRH	R5, [R2]
		LDRH	R7, [R2,#2]
		LDRH	R6, [R1,#2]
		SUBS	R5, R7,	R6
		ADDS	R6, R7,	R6
		STRH	R6, [R2,#2]
		STRH	R3, [R1]
		STRH	R5, [R1,#2]
		ADDS	R2, R4,	R2
		ADDS	R1, R4,	R1
		SUBS	R0, R0,	#1
		BNE	loc_20A
loc_22A:				
					
		LDR	R1, [SP,#4]
		ADDS	R0, R0,	#1
		STR	R0, [SP,#0]
		CMP	R0, R1
		BCC	loc_1DA
loc_236:				
					
		ADD	SP, SP,	#0x4C
		POP	{R4-R7,PC}
		.ltorg
arm_radix2_butterfly_inverse_q15:	
		PUSH	{R0-R7,LR}
		SUB	SP, SP,	#0x3C
		LDR	R0, [SP,#0x40]
		STR	R0, [SP,#0]
		LSRS	R0, R0,	#1
		STR	R0, [SP,#0x24]
		STR	R0, [SP,#0xC]
		MOVS	R0, #0
		STR	R0, [SP,#0x38]
		LDR	R0, [SP,#0xC]
		CMP	R0, #0
		BEQ	loc_30C
		MOVS	R0, #0
		STR	R0, [SP,#0x18]
		LDR	R0, [SP,#0xC]
		CMP	R0, #0
		BLS	loc_30C
		LDR	R0, [SP,#0]
		LSLS	R0, R0,	#2
		STR	R0, [SP,#0x1C]
loc_262:				
		LDR	R0, [SP,#0x38]
		LDR	R1, [SP,#0x44]
		LSLS	R0, R0,	#2
		LDRSH	R1, [R1,R0]
		STR	R1, [SP,#0x14]
		LDR	R1, [SP,#0x44]
		MOVS	R4, #2
		ADDS	R0, R0,	R1
		LDRSH	R4, [R0,R4]
		LDR	R1, [SP,#0x38]
		LDR	R0, [SP,#0x48]
		ADDS	R0, R1,	R0
		STR	R0, [SP,#0x38]
		LDR	R1, [SP,#0x18]
		LDR	R0, [SP,#0x40]
		CMP	R0, R1
		BLS	loc_300
		MOV	R1, R0
		LDR	R0, [SP,#0x18]
		SUBS	R1, R1,	R0
		LDR	R0, [SP,#0]
		ADDS	R0, R1,	R0
		SUBS	R0, R0,	#1
		LDR	R1, [SP,#0]
		BL	__aeabi_uidivmod
		LDR	R2, [SP,#0x40]
		LDR	R1, [SP,#0x18]
		CMP	R1, R2
		BCS	loc_300
		LSLS	R2, R1,	#2
		LDR	R1, [SP,#0x3C]
		LDR	R3, [SP,#0xC]
		ADDS	R2, R2,	R1
		LDR	R1, [SP,#0x18]
		ADDS	R1, R1,	R3
		LSLS	R3, R1,	#2
		LDR	R1, [SP,#0x3C]
		ADDS	R1, R3,	R1

loc_2B0:				
		MOVS	R3, #0
		LDRSH	R3, [R2,R3]
		ASRS	R5, R3,	#1
		MOVS	R3, #0
		LDRSH	R3, [R1,R3]
		ASRS	R6, R3,	#1
		SUBS	R3, R5,	R6
		ADDS	R5, R5,	R6
		ASRS	R5, R5,	#1
		STRH	R5, [R2]
		MOVS	R5, #2
		LDRSH	R5, [R2,R5]
		ASRS	R7, R5,	#1
		MOVS	R5, #2
		LDRSH	R5, [R1,R5]
		ASRS	R6, R5,	#1
		SUBS	R5, R7,	R6
		ADDS	R6, R6,	R7
		ASRS	R6, R6,	#1
		STRH	R6, [R2,#2]
		LDR	R6, [SP,#0x14]
		MOV	R7, R5
		MULS	R6, R3
		MULS	R7, R4
		ASRS	R6, R6,	#0x10
		ASRS	R7, R7,	#0x10
		SUBS	R6, R6,	R7
		STRH	R6, [R1]
		LDR	R6, [SP,#0x14]
		MULS	R3, R4
		MULS	R5, R6
		ASRS	R5, R5,	#0x10
		ASRS	R3, R3,	#0x10
		ADDS	R3, R5,	R3
		STRH	R3, [R1,#2]
		LDR	R3, [SP,#0x1C]
		ADDS	R2, R3,	R2
		ADDS	R1, R3,	R1
		SUBS	R0, R0,	#1
		BNE	loc_2B0
loc_300:				
		LDR	R0, [SP,#0x18]
		LDR	R1, [SP,#0xC]
		ADDS	R0, R0,	#1
		STR	R0, [SP,#0x18]
		CMP	R0, R1
		BCC	loc_262
loc_30C:				
		LDR	R0, [SP,#0x48]
		LSLS	R0, R0,	#0x11
		LSRS	R0, R0,	#0x10
		STR	R0, [SP,#0x48]
		LDR	R0, [SP,#0x24]
		STR	R0, [SP,#0x34]
		CMP	R0, #2
		BLS	loc_3F2
loc_31C:				
		LDR	R0, [SP,#0xC]
		STR	R0, [SP,#0]
		LSRS	R0, R0,	#1
		STR	R0, [SP,#0xC]
		MOVS	R0, #0
		STR	R0, [SP,#0x38]
		LDR	R0, [SP,#0xC]
		CMP	R0, #0
		BEQ	loc_3E0
		MOVS	R0, #0
		STR	R0, [SP,#0x18]
		LDR	R0, [SP,#0xC]
		CMP	R0, #0
		BLS	loc_3E0
		LDR	R0, [SP,#0]
		LSLS	R0, R0,	#2
		STR	R0, [SP,#0x1C]
loc_33E:				
		LDR	R0, [SP,#0x38]
		LDR	R1, [SP,#0x44]
		LSLS	R0, R0,	#2
		LDRSH	R4, [R1,R0]
		ADDS	R0, R0,	R1
		MOVS	R5, #2
		LDRSH	R5, [R0,R5]
		LDR	R1, [SP,#0x48]
		LDR	R0, [SP,#0x38]
		ADDS	R0, R0,	R1
		STR	R0, [SP,#0x38]
		LDR	R1, [SP,#0x18]
		LDR	R0, [SP,#0x40]
		CMP	R0, R1
		BLS	loc_3D4
		SUBS	R1, R0,	R1
		LDR	R0, [SP,#0]
		ADDS	R0, R1,	R0
		SUBS	R0, R0,	#1
		LDR	R1, [SP,#0]
		BL	__aeabi_uidivmod
		LDR	R2, [SP,#0x40]
		LDR	R1, [SP,#0x18]
		CMP	R1, R2
		BCS	loc_3D4
		LSLS	R2, R1,	#2
		LDR	R1, [SP,#0x3C]
		LDR	R3, [SP,#0xC]
		ADDS	R2, R2,	R1
		LDR	R1, [SP,#0x18]
		MOV	R12, R0
		ADDS	R1, R1,	R3
		LSLS	R3, R1,	#2
		LDR	R1, [SP,#0x3C]
		ADDS	R1, R3,	R1
loc_386:				
		MOVS	R3, #0
		MOVS	R0, #0
		LDRSH	R3, [R2,R3]
		LDRSH	R0, [R1,R0]
		MOVS	R7, #2
		SUBS	R6, R3,	R0
		ADDS	R0, R3,	R0
		ASRS	R0, R0,	#1
		STRH	R0, [R2]
		MOVS	R0, #2
		LDRSH	R0, [R2,R0]
		LDRSH	R7, [R1,R7]
		SXTH	R6, R6
		SUBS	R3, R0,	R7
		ADDS	R0, R7,	R0
		ASRS	R0, R0,	#1
		STRH	R0, [R2,#2]
		MOV	R0, R6
		MULS	R0, R4
		SXTH	R3, R3
		ASRS	R7, R0,	#0x10
		MOV	R0, R3
		MULS	R0, R5
		ASRS	R0, R0,	#0x10
		SUBS	R0, R7,	R0
		STRH	R0, [R1]
		MULS	R3, R4
		ASRS	R0, R3,	#0x10
		MULS	R6, R5
		ASRS	R3, R6,	#0x10
		ADDS	R0, R0,	R3
		STRH	R0, [R1,#2]
		LDR	R0, [SP,#0x1C]
		ADDS	R2, R0,	R2
		ADDS	R1, R0,	R1
		MOV	R0, R12
		SUBS	R0, R0,	#1
		MOV	R12, R0
		BNE	loc_386
loc_3D4:				
					
		LDR	R0, [SP,#0x18]
		LDR	R1, [SP,#0xC]
		ADDS	R0, R0,	#1
		STR	R0, [SP,#0x18]
		CMP	R0, R1
		BCC	loc_33E
loc_3E0:			
					
		LDR	R0, [SP,#0x48]
		LSLS	R0, R0,	#0x11
		LSRS	R0, R0,	#0x10
		STR	R0, [SP,#0x48]
		LDR	R0, [SP,#0x34]
		LSRS	R0, R0,	#1
		STR	R0, [SP,#0x34]
		CMP	R0, #2
		BHI	loc_31C
loc_3F2:				
		LDR	R4, [SP,#0xC]
		LDR	R0, [SP,#0x40]
		LSRS	R5, R4,	#1
		CMP	R0, #0
		BEQ	loc_432
		ADDS	R0, R0,	R4
		MOV	R1, R4
		SUBS	R0, R0,	#1
		BL	__aeabi_uidivmod
		CMP	R0, #0
		BEQ	loc_432
		LDR	R2, [SP,#0x3C]
		LSLS	R1, R5,	#2
		ADDS	R3, R1,	R2
		LSLS	R1, R4,	#2
loc_412:				
		LDRH	R6, [R2]
		LDRH	R5, [R3]
		SUBS	R4, R6,	R5
		ADDS	R5, R6,	R5
		STRH	R5, [R2]
		LDRH	R7, [R2,#2]
		LDRH	R6, [R3,#2]
		SUBS	R5, R7,	R6
		ADDS	R6, R7,	R6
		STRH	R6, [R2,#2]
		STRH	R4, [R3]
		STRH	R5, [R3,#2]
		ADDS	R2, R1,	R2
		ADDS	R3, R1,	R3
		SUBS	R0, R0,	#1
		BNE	loc_412

loc_432:				
					
		ADD	SP, SP,	#0x4C
		POP	{R4-R7,PC}
		.ltorg
arm_cfft_radix2_q15:
		PUSH	{R4-R6,LR}
		MOV	R4, R0
		LDRB	R0, [R0,#2]
		MOV	R5, R1
		LDRH	R1, [R4]
		LDRH	R3, [R4,#0xC]
		LDR	R2, [R4,#4]
		CMP	R0, #1
		MOV	R0, R5
		BEQ	loc_45C
		BL	arm_radix2_butterfly_q15

loc_44E:			
		LDRH	R2, [R4,#0xE]
		LDRH	R1, [R4]
		MOV	R0, R5
		LDR	R3, [R4,#8]
		BL	arm_bitreversal_q15
		POP	{R4-R6,PC}

loc_45C:				
		BL	arm_radix2_butterfly_inverse_q15
		B	loc_44E
arm_bitreversal_q15:
		PUSH	{R4-R7,LR}
		SUB	SP, SP,	#0xC
		LSRS	R1, R1,	#1
		STR	R1, [SP,#4]
		ADDS	R1, R1,	#1
		STR	R1, [SP,#0]
		LDR	R1, [SP,#4]
		MOVS	R4, #0
		LSRS	R7, R1,	#1
		BEQ	loc_180
		LDR	R5, [SP,#0]
		MOVS	R6, #0
		LSLS	R5, R5,	#2
		ADDS	R5, R5,	R0
		LSLS	R2, R2,	#1
		MOV	R1, R0
		MOV	R12, R7
		STR	R2, [SP,#8]
loc_136:			
		LSLS	R2, R6,	#1
		CMP	R2, R4
		BCS	loc_15C
		LDR	R2, [R1]
		LSLS	R7, R4,	#2
		MOV	LR, R2
		LDR	R2, [R0,R7]
		STR	R2, [R1]
		MOV	R2, LR
		STR	R2, [R0,R7]
		LDR	R7, [SP,#0]
		LDR	R2, [R5]
		ADDS	R7, R4,	R7
		MOV	LR, R2
		LSLS	R7, R7,	#2
		LDR	R2, [R0,R7]
		STR	R2, [R5]
		MOV	R2, LR
		STR	R2, [R0,R7]

loc_15C:				
		LDR	R2, [SP,#4]
		LDR	R7, [R1,#4]
		ADDS	R2, R4,	R2
		LSLS	R2, R2,	#2
		LDR	R4, [R0,R2]
		STR	R4, [R1,#4]
		STR	R7, [R0,R2]
		LDR	R2, [SP,#8]
		LDRH	R4, [R3]
		ADDS	R3, R2,	R3
		MOV	R2, R12
		SUBS	R2, R2,	#1
		ADDS	R1, #8
		ADDS	R5, #8
		ADDS	R6, R6,	#1
		MOV	R12, R2
		CMP	R2, #0
		BNE	loc_136
loc_180:				
		ADD	SP, SP,	#0xC
		POP	{R4-R7,PC}
		.ltorg
		
__aeabi_uidivmod:
 	cmp	r1, #0
 	bne	L_no_div0
 	b	__aeabi_idiv0
L_no_div0:
 	@ Shift left the denominator until it is greater than the numerator
 	movs	r2, #1 @ counter
 	movs	r3, #0 @ result
 	cmp	r0, r1
 	bls	L_sub_loop0
 	adds	r1, #0 @ dont shift if denominator would overflow
 	bmi	L_sub_loop0
L_denom_shift_loop:
 	lsls	r2, #1
 	lsls	r1, #1
	 bmi	L_sub_loop0
 	cmp	r0, r1
 	bhi	L_denom_shift_loop
L_sub_loop0:
 	cmp	r0, r1
 	bcc	L_dont_sub0	@ if (num>denom)
 	subs	r0, r1 @ numerator -= denom
 	orrs	r3, r2 @ result(r3) |= bitmask(r2)
L_dont_sub0:
 	lsrs	r1, #1 @ denom(r1) >>= 1
 	lsrs	r2, #1 @ bitmask(r2) >>= 1
 	bne	L_sub_loop0
 	mov	r1, r0 @ remainder(r1) = numerator(r0)
 	mov	r0, r3 @ quotient(r0) = result(r3)
 	bx	lr
__aeabi_idiv0:
	bx lr
	.ltorg

	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
