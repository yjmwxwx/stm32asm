@ stm32f030f4p6 asm 
@ 电感表
	 .thumb                 
         .syntax unified
.section .data
        .equ STACKINIT,         0x20001000
	.equ shumaguanma,	0x20000000
shumaguanmabiao:
	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6
shumaguanshuaxinbiao:
	.int 0xfe00,0xfd00,0xfb00,0xf700,0xef00,0xdf00,0xbf00,0x7f00,0
zhengxian1k:
	.int 250,253,256,259,263,266,269,272,275,278,281,284,288,291,294,297,300,303,306,309,312,315,318,321,324,327,330,333,336,339,342,345,348,351,354,356,359,362,365,368,370,373,376,379,381,384,387,389,392,394,397,399,402,404,407,409,412,414,417,419,421,423,426,428,430,432,434,436,439,441,443,445,447,448,450,452,454,456,458,459,461,463,464,466,468,469,471,472,473,475,476,478,479,480,481,482,484,485,486,487,488,489,490,491,491,492,493,494,494,495,496,496,497,497,498,498,498,499,499,499,500,500,500,500,500,500,500,500,500,500,500,499,499,499,498,498,498,497,497,496,496,495,494,494,493,492,491,491,490,489,488,487,486,485,484,482,481,480,479,478,476,475,473,472,471,469,468,466,464,463,461,459,458,456,454,452,450,448,447,445,443,441,439,436,434,432,430,428,426,423,421,419,417,414,412,409,407,404,402,399,397,394,392,389,387,384,381,379,376,373,370,368,365,362,359,356,354,351,348,345,342,339,336,333,330,327,324,321,318,315,312,309,306,303,300,297,294,291,288,284,281,278,275,272,269,266,263,259,256,253,250,247,244,241,237,234,231,228,225,222,219,216,212,209,206,203,200,197,194,191,188,185,182,179,176,173,170,167,164,161,158,155,152,149,146,144,141,138,135,132,130,127,124,121,119,116,113,111,108,106,103,101,98,96,93,91,88,86,83,81,79,77,74,72,70,68,66,64,61,59,57,55,53,52,50,48,46,44,42,41,39,37,36,34,32,31,29,28,27,25,24,22,21,20,19,18,16,15,14,13,12,11,10,9,9,8,7,6,6,5,4,4,3,3,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,4,4,5,6,6,7,8,9,9,10,11,12,13,14,15,16,18,19,20,21,22,24,25,27,28,29,31,32,34,36,37,39,41,42,44,46,48,50,52,53,55,57,59,61,64,66,68,70,72,74,77,79,81,83,86,88,91,93,96,98,101,103,106,108,111,113,116,119,121,124,127,130,132,135,138,141,144,146,149,152,155,158,161,164,167,170,173,176,179,182,185,188,191,194,197,200,203,206,209,212,216,219,222,225,228,231,234,237,241,244,247,250
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
	.word 0 @_svc_handler +1
	.word 0
	.word 0
	.word 0 @_pendsv_handler +1
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
	.word 0         @_dma1_1  +1    @ 9
	.word 0    @_dma1_2_3 +1        @ 10
	.word 0       @_dma1_4_5 +1     @ 11
	.word 0      @_adc1 +1          @ 12
	.word 0       @_tim1_brk_up +1  @ 13
	.word 0        @ _tim1_cc +1    @ 14
	.word 0         @_tim2 +1       @ 15
	.word 0  @_tim3 +1      @ 16
	.word 0                         @ 17
	.word 0		                @ 18
	.word @ _tim14 +1    @ 19
	.word 0                         @ 20
	.word 0         @_tim16 +1      @ 21
	.word 0         @_tim17 +1      @ 22
	.word 0          @_i2c   +1     @ 23
	.word 0                         @ 24
	.word 0           @_spi   +1    @ 25
	.word 0                         @ 26
	.word 0         @_usart1 +1     @ 27
_start:
_shizhong:
	ldr r2, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r2]
	ldr r0, = 0x40021000 @ rcc
	ldr r1, = 0x1c0002
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
_dengdai14mshizhongwending:
	ldr r1, [r0, # 0x34]
	lsls r1, r1, # 30     @ 左移30位
	bpl _dengdai14mshizhongwending  @ 等待14M时钟稳定

_neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
_neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan

_waisheshizhong:	 @ 外设时钟  
	@+0x14=RCC_AHBENR
	@0=DMA @2=SRAM @4=FLITF@6=CRC @17=PA @18=PB @19=PC @20=PD @22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x460005
	str r1, [r0, # 0x14]
           
	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
	ldr r1, = 0x800
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@1=TIM3 @4=TIM6 @5=TIM7 @8=TIM14 @11=WWDG @14=SPI @17=USRT2 @18=USART3 @20=USART5 @21=I2C1 @22=I2C2 @23=USB @28=PWR
	movs r1, # 0x02
	str r1, [r0, # 0x1c]
waishezhongduan:		@外设中断
	@0xE000E100    0-31 写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效
_io_she_zhi:
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@a(0x48000000)b(0x48000400)c(0x48000800)d(0x48000c00)f(0x48001400)
	@ 输入（00），通用输出（01），复用功能（10），模拟（11）
	@偏移0x4 = 端口输出类型 @ （0 推挽），（ 1 开漏）
	@偏移0x8 = 输出速度  00低速， 01中速， 11高速
	@偏移0xC = 上拉下拉 00无上下拉，  01 上拉， 10下拉
	@偏移0x10 = 输入数据寄存器
	@偏移0x14 = 输出数据寄存器
	@偏移0x18 = 端口开  0-15置位 
	@偏移0x28 = 端口关
	@偏移0X20 = 复用低
	@GPIO口0（0-3位）每个IO口占用4位
	@ AF0 = 0X0000, AF1 = 0X0001, AF2 = 0X0010 AF3 = 0X0011, AF4 = 0X0100
	@ AF5 = 0X0101, AF6 = 0X0111, AF7 = 0X1000
	@0x24 = 复用高
	@GPIO口8 （0-3位）每个IO口占用4位
	@ AF0 = 0X0000, AF1 = 0X0001, AF2 = 0X0010 AF3 = 0X0011, AF4 = 0X0100
	@ AF5 = 0X0101, AF6 = 0X0111, AF7 = 0X1000
	@偏移0x24 复用高
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	ldr r0, = 0x48000000
	ldr r1, = 0x28105400
	str r1, [r0]

	ldr r0, = 0x48000400
	movs r1, # 0x08
	str r1, [r0]

	movs r1, # 0x10
	str r1, [r0, # 0x20]
	
	
	ldr r0, = 0x48001400
	movs r1, # 0
	str r1, [r0]
	movs r1, # 0x05 
	str r1, [r0, # 0x0c]

dmachushihua:
	@+0=LSR,+4=IFCR,
	@+8=CCR1,+c=CNDTR1,+10=CPAR1+14=CMAR1,
	@+1c=CCR2,+20=CNDTR2,+24=CPAR2,+28=CMAR2
	@+30=CCR3,+34=CNDTR3,+38=CPAR2,+3c=CMAR3
	@+44=CCR4,+48=CNDTR4,+4c=CPAR4,+50=CMAR4
	@+58=CCR5,+5c=CNDTR5,+60=CPAR5,+64=CMAR5
	@+6C=CCR6,+70=CNDTR6,+74=CPAR6,+78=CMAR6
	@+80=CCR7,+84=CNDTR7,+88=CPAR7,+8c=CMAR7
	ldr r0, = 0x40020000
	ldr r1, = 0x40000440 @ 外设地址
	str r1, [r0, # 0x38]
	ldr r1, = zhengxian1k  @ 储存器地址
	str r1, [r0, # 0x3c]
	ldr r1, = 500
	str r1, [r0, # 0x34]
	ldr r1, = 0x25b1         @ 储存到外设
	str r1, [r0, # 0x30]
_tim3chushihua:
	ldr r0, = 0x40000400
	ldr r1, = 0
	str r1, [r0, # 0x28]  @psc
	ldr r1, = 500
	str r1, [r0, # 0x2c]  @arr
	ldr r1, = 0x6000
	str r1, [r0, # 0x1c]
	ldr r1, =  0x1000
	str r1, [r0, # 0x20]
	ldr r1, = 0x1000
	str r1, [r0, # 0x0c] @dier
	ldr r1, = 0x01
	str r1, [r0]

_ting:
	b _ting

	
_maopaopaixu:	
	push {r0-r7,lr}
	@ r0= 表地址, r1= 长度
	movs r6, r1
_maopaopaixuxunhuan1:
	movs r5, r6
	ldr r1, [r0, r5]
_maopaopaixuxunhuan:
	subs r5, r5, # 0x04
	bmi _maopaopaixucun
	ldr r2, [r0, r5]
	cmp r1, r2
	bhi _maopaopaixuxunhuan
	mov r1, r2
	mov r7, r5
	b _maopaopaixuxunhuan
_maopaopaixucun:
	movs r7, r7
	bpl _r7bushifushu
	movs r7, # 0
_r7bushifushu:	
	ldr r3, [r0, r6]
	str r1, [r0, r6]
	str r3, [r0, r7]
	subs r6, r6, # 0x04
	bne _maopaopaixuxunhuan1
	pop {r0-r7,pc}
	
_zhuanshumaguanma:	@ 16进制转数码管码
		@ R0要转的数据， R1长度，R2结果表首地址
	push {r0-r7,lr}
	ldr r7, = shumaguanmabiao
	mov r5, r0
	mov r6, r1
	movs r1, # 10
_xunhuanqiuma:
	bl _chufa
	mov r4, r0
	muls r4, r1
	subs r3, r5, r4
	lsls r3, # 2
	ldr r4, [r7, r3]
	str r4, [r2]
	mov r5, r0
	adds r2, r2, # 4
	subs r6, # 1
	bne _xunhuanqiuma
	pop {r0-r7,pc}
_xieshumaguan:	 @ r0=位数 @数码管码
	push {r0-r7,lr}
	movs r7, # 0
	mov r6, r0
	ldr r5, = shumaguanma
	ldr r2, = shumaguanshuaxinbiao
_shumaguanshuaxin:
	ldr r3, [r5, r7]
	ldr r4, [r2, r7]
	orrs r4, r4, r3
	mov r0, r4
	bl _xie595
	adds  r7, r7, # 4
	cmp r7, r6
	bls _shumaguanshuaxin
	pop {r0-r7,pc}
_xie595: @ R0=要写的数据
	push {r0-r7,lr}
	mov r5, r0
	movs r0, # 0x40
	movs r7, # 0x80 
	movs r6, # 0x20 
	movs r3, # 16   @16位
	ldr r2, = 0x48000000 @ gpioa
	movs r1, # 0x01
_xunhuan595:
	str r7, [r2, # 0x18]
	bl _yanshi
	tst r5, r1
	bne _xie595_0
	str r0, [r2, # 0x28]
	b _suocun595
_xie595_0:
	str r0, [r2, # 0x18]
_suocun595:
	bl _yanshi
	lsrs r5, # 1
	str r7, [r2, # 0x28]
	bl _yanshi
	subs r3, r3, # 1
	bne _xunhuan595
	str r6, [r2, # 0x18]
	bl _yanshi
	str r6, [r2, # 0x28]
	bl _yanshi
	pop {r0-r7,pc}

_yanshi:
	push {r7,lr}
	ldr r7, = 30
_yanshi11:
	subs r7, # 1
	bne _yanshi11
	pop {r7,pc}
	
_chufa:	@软件除法
	@ r0 除以 r1 等于 商(r0)余数R1
	push {r1-r4,lr}
	cmp r0, # 0
	beq _chufafanhui
	cmp r1, # 0
	beq _chufafanhui
	mov r2, r0
	movs r3, # 1
	lsls r3, r3, # 31
	movs r0, # 0
	mov r4, r0
_chufaxunhuan:       
	lsls r2, r2, # 1
	adcs r4, r4, r4
	cmp r4, r1
	bcc _chufaweishubudao0
	adds r0, r0, r3
	subs r4, r4, r1
_chufaweishubudao0:
	lsrs r3, r3, # 1
	bne _chufaxunhuan
_chufafanhui:	
	pop {r1-r4,pc}
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
