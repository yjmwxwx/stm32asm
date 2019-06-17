	@@单片机stm32f030f4p6
	@@io口输出SPWM_ram运行 
	@作者：yjmwxwx
	@时间：2019-06-17
	@编译器：ARM-NONE-EABI-AS
	 .thumb
	.syntax unified
	.section .data
_zhengxianbiao:
	.byte 0x8,0xb,0xe,0xf,0x10,0xf,0xe,0xb,0x8,0x5,0x2,0x1,0x0,0x1,0x2,0x5,0x8
	.align 2
_fanhui:
	.long 0x460a2101, 0x06d20289, 0x468f4411
	.equ STACKINIT,        	        0x20001000
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
	.word aaa +1	@_systickzhongduan +1               @ 15
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
	cpsid i
shizhong:
	ldr r2, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r2]           @FLASH缓冲 缓冲开启
	ldr r0, = 0x40021000 @ rcc
	ldr r1, = 0x10001
	str r1, [r0]
denghse:
	ldr r1, [r0]
	lsls r1, r1, # 14
	bpl denghse
dengpllguan:
	ldr r1, [r0]
	lsls r1, r1, # 6
	bmi dengpllguan
        ldr r1, = 0x310002
        str r1, [r0, # 0x04]
	ldr r1, = 0x1010000
	str r1, [r0]
dengpll:
	ldr r1, [r0]
	lsls r1, # 6
	bpl dengpll
_neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
_neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan
_waisheshizhong:			 @ 外设时钟
	@+0x14=RCC_AHBENR
	@0=DMA @2=SRAM @4=FLITF@6=CRC @17=PA @18=PB @19=PC @20=PD @22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x460005
	str r1, [r0, # 0x14]

	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
	ldr r1, = 0xa00
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@1=TIM3 @4=TIM6 @5=TIM7 @8=TIM14 @11=WWDG @14=SPI @17=USRT2 @18=USART3 @20=USART5 @21=I2C1
	@22=I2C2 @23=USB @28=PWR

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

_xiezhengxianbo:
        ldr r0, = _zhengxianbiao
	ldr r3, = 0x20000000
	movs r2, # 0
	movs r6, # 16		@ 点数
	mov r7, r2
_xiezhengxianbiao:
	ldrb r4, [r0, r2]
	adds r2, r2, # 1
	movs r5, # 30
	subs r5, r5, r4
_kai:
	cmp r4, # 0
	beq _guan
	ldr r1, = 0x2218
	strh r1, [r3, r7]
	adds r7, r7, # 2
	ldr r1, = 0x5083
_kaixunhuan:
	strh r1, [r3, r7]
	adds r7, r7, # 2
	subs r4, r4, # 1
	bne _kaixunhuan
_guan:
	cmp r5, # 0
	beq _xiezhengxianbiaoxunhuan1
	ldr r1, = 0x2228
	strh r1, [r3, r7]
	adds r7, r7, # 2
	ldr r1, = 0x5083
_guanxunhuan:
	strh r1, [r3, r7]
	adds r7, r7, # 2
	subs r5, r5, # 1
	bne _guanxunhuan
_xiezhengxianbiaoxunhuan1:	
	subs r6, r6, # 1
	bne _xiezhengxianbiao
	ldr r1, = 0x2101
	ldr r2, = 0x0749
	ldr r4, = 0x468f
	strh r1, [r3, r7]
	adds r7, r7, # 2
	strh r2, [r3, r7]
	adds r7, r7, # 2
	strh r4, [r3, r7]
	ldr r0, = 0x48000000
	ldr r1, = 0x28040000
	str r1, [r0]
	movs r1, # 1
	mov r3, r1
	lsls r3, r3, # 9
	lsls r1, r1, # 29
	mov pc, r1
	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
_systickzhongduan:
	bx lr
aaa:
	bx lr
