	@@单片机stm32f030f4p6
	@@ tim1 spwm,TIM3周期同步
	@作者：yjmwxwx
	@时间：2019-06-18
	@编译器：ARM-NONE-EABI-AS
	 .thumb
	         .syntax unified
	.section .data

zheng_xian_biao:
	.short 18,21,24,27,29,31,33,34,35,35,34,33,31,29,27,24,21,18,14,11,8,6,4,2,1,0,0,1,2,4,6,8,11,14,18
yjmwxwx:
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
	.word aaa +1      @_exti0_1  +1      @ 5
	.word aaa +1      @ _exti2_3 +1      @ 6
	.word aaa +1       @_exti4_15 +1     @ 7
	.word aaa +1                         @ 8
	.word aaa +1 	@_dma1_1  +1    @ 9
	.word aaa +1    @_dma1_2_3 +1        @ 10
	.word aaa +1       @_dma1_4_5 +1     @ 11
	.word aaa +1	 @_adc1 +1          @ 12
	.word aaa +1       @_tim1_brk_up +1  @ 13
	.word aaa +1        @ _tim1_cc +1    @ 14
	.word aaa +1         @_tim2 +1       @ 15
	.word aaa +1          @_tim3 +1      @ 16
	.word aaa +1                         @ 17
	.word aaa +1		                @ 18
	.word aaa +1	@_tim14 +1    @ 19
	.word aaa +1                         @ 20
	.word aaa +1         @_tim16 +1      @ 21
	.word aaa +1         @_tim17 +1      @ 22
	.word aaa +1          @_i2c   +1     @ 23
	.word aaa +1                         @ 24
	.word aaa +1           @_spi   +1    @ 25
	.word aaa +1                         @ 26
	.word aaa +1         @_usart1 +1     @ 27
	.align 2

_start:



_waisheshizhong:			 @ 外设时钟
	@+0x14=RCC_AHBENR
	@ 0=DMA @ 2=SRAM @ 4=FLITF@ 6=CRC @ 17=PA @ 18=PB @ 19=PC @ 20=PD @ 22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x60001
	str r1, [r0, # 0x14]

	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
	ldr r1, = 0x800
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@ 1=TIM3 @ 4=TIM6 @ 5=TIM7 @ 8=TIM14 @ 11=WWDG @ 14=SPI @ 17=USRT2 @ 18=USART3 @ 20=USART5 @ 21=I2C1
	@ 22=I2C2 @ 23=USB @ 28=PWR
	movs r2, # 2
	str r2, [r0, # 0x1c]
tim1chushiha:				@ 128M
	ldr r5, = 0x40012c00 @ tim1_cr1
	movs r1, # 0
	str r1, [r5, # 0x28] @ psc
	ldr r1, = 35
	str r1, [r5, # 0x2c] @ ARR
	ldr r1, = 0x68
	str r1, [r5, # 0x1c] @ ccmr2  CC3
	ldr r1, = 0x100    @  CC3
	str r1, [r5, # 0x20] @ ccer
	ldr r1, = 0x8000
	str r1, [r5, # 0x44] @ BDTR
	ldr r1, = 0x800 @ CC3 DMA
	str r1, [r5, # 0x0c] @ DIER
	ldr r4, = 0xe1
tim3chushihua:				@ 64M
	ldr r0, = 0x40000400 @ tim3_cr1
	movs r1, # 0 
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 595
	str r1, [r0, # 0x2c] @ ARR
	ldr r1, =   0x3800
	str r1, [r0, # 0x1c] @ ccmr2
	ldr r1, =  0x1000
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 595
	str r1, [r0, # 0x40] @ ccr4
	movs r1, # 0x81
	str r1, [r0]
	str r4, [r5]

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
	ldr r1, = 35             @点数
	str r1, [r0, # 0x5c]
	ldr r1, = 0x25b1         @ 储存到外设
	str r1, [r0, # 0x58]

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
	ldr r1, = 0x28205403
	str r1, [r0]
	ldr r1, = 0x200
	str r1, [r0, # 0x24]
	
	ldr r0, = 0x48000400
	movs r1, # 0x08 @ pb1
	str r1, [r0]
	movs r1, # 0x10  @ tim3_4到PB1
	str r1, [r0, # 0x20] @ ARRL
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
        ldr r1, = 0x3d0002
        str r1, [r0, # 0x04]
        ldr r1, = 0x1010000
	movs r0, r0
        str r1, [r0]
	
dengpll:
	ldr r1, [r0]
	lsls r1, # 6
	bpl dengpll
	
	bkpt # 1

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
