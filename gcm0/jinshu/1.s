		@ stm32f030f4p6 asm
	 .thumb
	         .syntax unified
	.section .data
zheng_xian_biao:
.short 0x30,0x33,0x36,0x38,0x3b,0x3e,0x41,0x44,0x47,0x49,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x59,0x5b,0x5c,0x5d,0x5e,0x5e,0x5f,0x5f,0x5f,0x5f,0x5f,0x5e,0x5d,0x5c,0x5b,0x5a,0x59,0x57,0x55,0x53,0x51,0x4f,0x4d,0x4a,0x48,0x45,0x43,0x40,0x3d,0x3a,0x37,0x34,0x31,0x2e,0x2b,0x28,0x25,0x22,0x1f,0x1c,0x1a,0x17,0x15,0x12,0x10,0xe,0xc,0xa,0x8,0x6,0x5,0x4,0x3,0x2,0x1,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x2,0x3,0x4,0x6,0x7,0x9,0xb,0xd,0xf,0x11,0x13,0x16,0x18,0x1b,0x1e,0x21,0x24,0x27,0x29,0x2c,0x30
	.align 4
shumaguanmabiao:
	.int 0x02,0xae,0x14,0x0c,0xa8,0x48,0x40,0x2e,0x00,0x08
	
	.equ STACKINIT,        	        0x20001000
	.equ shumaguanma,		0x20000000
	.equ dianyabiao,		0x20000100
	.equ lvboqizhizhen,		0x20000200
	.equ lvboqihuanchong,		0x20000204
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
	.word _systickzhongduan +1               @ 15
	.word aaa +1     @ _wwdg +1          @ 0
	.word aaa +1     @_pvd +1            @ 1
	.word aaa +1     @_rtc +1            @ 2
	.word aaa +1     @_flash +1          @ 3
	.word aaa +1	@ _rcc + 1          @ 4
	.word aaa +1	@_exti0_1  +1      @ 5
	.word aaa +1      @ _exti2_3 +1      @ 6
	.word aaa +1       @_exti4_15 +1     @ 7
	.word aaa +1                         @ 8
	.word aaa +1 	@_dma1_1  +1    @ 9
	.word aaa +1    @_dma1_2_3 +1        @ 10
	.word aaa +1       @_dma1_4_5 +1     @ 11
	.word aaa +1	 @_adc1 +1          @ 12
	.word aaa +1	@_tim1_brk_up +1  @ 13
	.word aaa +1 @_tim1_buhuo +1    @ 14
	.word aaa +1         @_tim2 +1       @ 15
	.word aaa +1          @_tim3 +1      @ 16
	.word aaa +1                         @ 17
	.word aaa +1		                @ 18
	.word aaa +1		@_tim14 +1    @ 19
	.word aaa +1                         @ 20
	.word aaa +1 	@_tim16 +1      @ 21
	.word aaa +1         @_tim17 +1      @ 22
	.word aaa +1          @_i2c   +1     @ 23
	.word aaa +1                         @ 24
	.word aaa +1           @_spi   +1    @ 25
	.word aaa +1                         @ 26
	.word aaa +1         @_usart1 +1     @ 27
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

_waisheshizhong:			 @ 外设时钟
	@ +0x14=RCC_AHBENR
	@ 0=DMA 2=SRAM 4=FLITF 6=CRC  17=PA  18=PB 19=PC 20=PD 22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x460005
	str r1, [r0, # 0x14]

	@ +0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@ 0=SYSCFG 5=USART6EN 9=ADC 11=TIM1 12=SPI1 14=USART1
	@ 16=TIM15 17=TIM16 18=TIM17 22=DBGMCU
	ldr r1, = 0xa00
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@ 1=TIM3 4=TIM6 5=TIM7 8=TIM14 11=WWDG 14=SPI 17=USRT2 18=USART3
	@ 20=USART5 21=I2C1 22=I2C2  23=USB 28=PWR


io_she_zhi:
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@a(0x48000000)b(0x48000400)c(0x48000800)d(0x48000c00)f(0x48001400)
	@ 输入（00），通用输出（01），复用功能（10），模拟（11）
	@偏移0x4 = 端口输出类型 @ （0 推挽），（ 1 开漏）
	@偏移0x8 = 输出速度  00低速， 01中速， 11高速
	@偏移0xC = 上拉下拉 (00无上下拉，  01 上拉， 10下拉)
	@偏移0x10 = 输入数据寄存器
	@偏移0x14 = 输出数据寄存器
	@偏移0x18 = 端口开  0-15置位
	@偏移0x28 = 端口关
	@0X20 = 复用低
	@GPIO口0（0-3位）每个IO口占用4位
	@ AF0 = 0X0000, AF1 = 0X0001, AF2 = 0X0010 AF3 = 0X0011, AF4 = 0X0100
	@ AF5 = 0X0101, AF6 = 0X0111, AF7 = 0X1000
	@0x24 = 复用高
	@GPIO口8 （0-3位）每个IO口占用4位
	@ AF0 = 0X0000, AF1 = 0X0001, AF2 = 0X0010 AF3 = 0X0011, AF4 = 0X0100
	@ AF5 = 0X0101, AF6 = 0X0111, AF7 = 0X1000
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
	ldr r0, = 0x48000000
	ldr r1, = 0x28145557
	str r1, [r0]

	ldr r0, = 0x48000400
	movs r1, # 0x08 @ pb1
	str r1, [r0]
	movs r1, # 0x20
	str r1, [r0, # 0x20]

	
	ldr r0, = 0x48001400
	movs r1, # 0x05
	str r1, [r0]
	movs r1, # 0x00
	str r1, [r0, # 0x14]

_adcchushihua:
        ldr r0, = 0x40012400  @ adc基地址
        ldr r1, = 0x80000000
        str r1, [r0, # 0x08]  @ ADC 控制寄存器 (ADC_CR)  @adc校准
_dengadcjiaozhun:
        ldr r1, [r0, # 0x08]
        movs r1, r1
        bmi _dengadcjiaozhun   @ 等ADC校准
_kaiadc:
	ldr r1, [r0, # 0x08]
        movs r2, # 0x01
	orrs r1, r1, r2
        str r1, [r0, # 0x08]
_dengdaiadcwending:
	ldr r1, [r0]
	lsls r1, r1, # 31
	bpl _dengdaiadcwending @ 等ADC稳定
_tongdaoxuanze:
	ldr r1, = 1
        str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
        ldr r1, = 0x803
        str r1, [r0, # 0x0c]    @ 配置寄存器 1 (ADC_CFGR1)
	movs r1, # 0
        str r1, [r0, # 0x14]    @ ADC 采样时间寄存器 (ADC_SMPR)
	ldr r1, [r0, # 0x08]
        ldr r2, = 0x04         @ 开始转换
        orrs r1, r1, r2
	str r1, [r0, # 0x08]    @ 控制寄存器 (ADC_CR)


	
dmachushihua:
        @+0=LSR,+4=IFCR,
        @+8=CCR1,+c=CNDTR1,+10=CPAR1+14=CMAR1,
        @+1c=CCR2,+20=CNDTR2,+24=CPAR2,+28=CMAR2
        @+30=CCR3,+34=CNDTR3,+38=CPAR2,+3c=CMAR3
        @+44=CCR4,+48=CNDTR4,+4c=CPAR4,+50=CMAR4
        @+58=CCR5,+5c=CNDTR5,+60=CPAR5,+64=CMAR5
        @+6C=CCR6,+70=CNDTR6,+74=CPAR6,+78=CMAR6
        @+80=CCR7,+84=CNDTR7,+88=CPAR7,+8c=CMAR7

        @tim1ch3DMA
        ldr r0, = 0x40020000
        ldr r1, = 0x40012c3c @ 外设地址
        str r1, [r0, # 0x60]
        ldr r1, = zheng_xian_biao @ 储存器地址
        str r1, [r0, # 0x64]
        ldr r1, = 100             @点数
        str r1, [r0, # 0x5c]
        ldr r1, = 0x35b1         @ 储存到外设
        str r1, [r0, # 0x58]
	@ adc dma
	ldr r0, = 0x40020000
	ldr r1, = 0x40012440
	str r1, [r0, # 0x10]
	ldr r1, = dianyabiao
	str r1, [r0, # 0x14]
	ldr r1, =  100
	str r1, [r0, # 0x0c]
	ldr r1, = 0x5a1		@ 5a1
	str r1, [r0, # 0x08]

	
tim1chushiha:
        ldr r0, = 0x40012c00 @ tim1_cr1
        movs r1, # 0
        str r1, [r0, # 0x28] @ psc
        ldr r1, = 96
        str r1, [r0, # 0x2c] @ ARR
	@	movs r1, # 0x40
	movs r1, # 0x20
	str r1, [r0, # 0x04] @ TRGO
	movs r1, # 0x38
	str r1, [r0, # 0x18] @ ccmr1 cc1
	movs r1, # 96
	str r1, [r0, # 0x34]
        ldr r1, = 0x68
        str r1, [r0, # 0x1c] @ ccmr2  CC3
        ldr r1, = 0x400    @  CC3
        str r1, [r0, # 0x20] @ ccer
        ldr r1, = 0x8000
        str r1, [r0, # 0x44] @ BDTR
        ldr r1, = 0x800 @ CC3 DMA
        str r1, [r0, # 0x0c] @ DIER
        ldr r1, = 0x81
        str r1, [r0]

	
	ldr r5, = 0
	ldr r6, = 9999
_tingting:
	ldr r0, = 0x20000150
	ldr r2, = 0x20000190
	ldrh r1, [r0]
	ldrh r3, [r2]
	cmp r1, r3
	bhi __zheng
	subs r3, r3, r1
	b __xian_shi_led
__zheng:
	subs r1, r1, r3
	mov r3, r1
__xian_shi_led:	
	ldr r0, = lvboqihuanchong
	ldr r1, = 256
	ldr r2, = lvboqizhizhen
	bl _lvboqi
	movs r1, # 4
        ldr r2, = shumaguanma
        bl _zhuanshumaguanma
        bl _xieshumaguan
	b _tingting

_xieshumaguan:			@ r0=4位10进制数
	push {r0-r7,lr}
	ldr r2, = shumaguanma
	ldr r7, = 0xfff
	ldr r4, = 0x48000000
	ldr r5, = 0x48001400
	ldr r6, = 0x200
	ldr r1, [r2]
	str r6, [r4, # 0x18]
	strb r1, [r4, # 0x14]
_shumaguanyanshi:	
	subs r7, r7, # 1
	bne _shumaguanyanshi
	str r6, [r4, # 0x28]
	lsls r6, r6, # 1
	ldr r7, = 0xfff
	ldr r1, [r2, # 0x04]
	str r6, [r4, # 0x18]
	strb r1, [r4, # 0x14]
	ldr r6, = 0x600
_shumaguanyanshi1:	
	subs r7, r7, # 1
	bne _shumaguanyanshi1
	str  r6, [r4, # 0x28]
	movs r6, # 0x02
	ldr r7, = 0xfff
	ldr r1, [r2, # 0x08]
	str r6, [r5, # 0x14]
	strb r1, [r4, # 0x14]
_shumaguanyanshi2:	
	subs r7, r7, # 1
	bne _shumaguanyanshi2
	movs r6, # 0x01
	ldr r7, = 0xfff
	ldr r1, [r2, # 0x0c]
	str r6, [r5, # 0x14]
	strb r1, [r4, # 0x14]
_shumaguanyanshi3:
	subs r7,  r7, # 1
	bne _shumaguanyanshi3
	movs r3, # 0
	str r3, [r5, # 0x14]
	pop {r0-r7,pc}
	
_zhuanshumaguanma:			@ 16进制转数码管码
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

_lvboqi:				@滤波器
			@R0=地址，R1=长度,r2=表指针地址,r3=ADC数值
			@出R0=结果
	push {r1-r7,lr}	
	ldr r5, [r2]		@读出表指针
	lsls r6, r1, # 1	
	strh r3, [r0, r5]	@数值写到滤波器缓冲区
	adds r5, r5, # 2
	cmp r5, r6
	bne _lvboqimeidaohuanchongquding
	movs r5, # 0
_lvboqimeidaohuanchongquding:
	str r5, [r2]
	movs r7, # 0
_lvboqixunhuan:
	cmp r5, r6
	bne _lvbozonghe
	movs r5, # 0
_lvbozonghe:
	ldrh r4, [r0, r5]
	adds r5, r5, # 2
	adds r7, r7, r4
	subs r1, r1, # 1
	bne _lvboqixunhuan
	asrs r0, r7, # 8	@修改
	pop {r1-r7,pc}
_chufa:				@软件除法
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
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
_systickzhongduan:
aaa:
	bx lr


