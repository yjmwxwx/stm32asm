	@@ 单片机stm32f030f4p6
	@@ 电桥						
	@作者：yjmwxwx
	@时间：2020-08-08
	@编译器：ARM-NONE-EABI
	.thumb
	.syntax unified
	.section .data
	.align 4
zheng_xian_200khz:	@20*10
	.short 7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4,7,9,10,12,13,13,13,12,10,9,7,4,3,1,0,0,0,1,3,4
	.align 4
xuan_zhuan_yin_zi:
	.int 0x8000,0x0000,0x4B3C,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8644,0xFFFFD873,0xFFFF9873,0x4B3C,0x0000,0x8000,0x678D,0x4B3C,0x79BC,0xFFFFD873,0x278D,0xFFFF8644,0xFFFFB4C4,0xFFFF9873,0xFFFF8000,0x0000,0xFFFFB4C4,0x678D,0x278D,0x79BC,0x79BC,0x278D,0x678D,0xFFFFB4C4,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C4,0xFFFF8644,0x278D,0xFFFFD873,0x79BC,0x4B3C,0x678D,0x8000,0x0000,0x4B3C,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8644,0xFFFFD872,0xFFFF9873,0x4B3C,0x0000,0x8000,0x678D,0x4B3C,0x79BC,0xFFFFD873,0x278E,0xFFFF8644,0xFFFFB4C4,0xFFFF9873,0xFFFF8000,0x0000,0xFFFFB4C4,0x678D,0x278D,0x79BC,0x79BC,0x278E,0x678D,0xFFFFB4C4,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C4,0xFFFF8644,0x278D,0xFFFFD872,0x79BC,0x4B3C,0x678E,0x8000,0x0000,0x4B3C,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8644,0xFFFFD872,0xFFFF9872,0x4B3C,0x0000,0x8000,0x678D,0x4B3C,0x79BC,0xFFFFD873,0x278E,0xFFFF8644,0xFFFFB4C4,0xFFFF9872,0xFFFF8000,0x0000,0xFFFFB4C4,0x678D,0x278D,0x79BC,0x79BC,0x278E,0x678E,0xFFFFB4C4,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C4,0xFFFF8644,0x278D,0xFFFFD872,0x79BC,0x4B3C,0x678E,0x8000,0x0000,0x4B3C,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8644,0xFFFFD872,0xFFFF9872,0x4B3C,0x0000,0x8000,0x678D,0x4B3C,0x79BC,0xFFFFD873,0x278E,0xFFFF8644,0xFFFFB4C4,0xFFFF9872,0xFFFF8000,0x0000,0xFFFFB4C4,0x678D,0x278D,0x79BC,0x79BC,0x278E,0x678E,0xFFFFB4C4,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C4,0xFFFF8644,0x278D,0xFFFFD872,0x79BC,0x4B3C,0x678E,0x8000,0x0000,0x4B3D,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8644,0xFFFFD872,0xFFFF9872,0x4B3C,0x0000,0x8000,0x678D,0x4B3D,0x79BC,0xFFFFD873,0x278E,0xFFFF8644,0xFFFFB4C4,0xFFFF9872,0xFFFF8000,0x0000,0xFFFFB4C4,0x678D,0x278D,0x79BC,0x79BC,0x278E,0x678E,0xFFFFB4C4,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C4,0xFFFF8644,0x278D,0xFFFFD872,0x79BB,0x4B3C,0x678E,0x8000,0x0000,0x4B3D,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8644,0xFFFFD872,0xFFFF9872,0x4B3C,0x0000,0x8000,0x678D,0x4B3D,0x79BC,0xFFFFD873,0x278E,0xFFFF8645,0xFFFFB4C5,0xFFFF9872,0xFFFF8000,0x0000,0xFFFFB4C3,0x678D,0x278D,0x79BC,0x79BC,0x278E,0x678E,0xFFFFB4C5,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C3,0xFFFF8644,0x278D,0xFFFFD872,0x79BB,0x4B3B,0x678E,0x8000,0x0000,0x4B3D,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8645,0xFFFFD872,0xFFFF9872,0x4B3B,0x0000,0x8000,0x678D,0x4B3D,0x79BC,0xFFFFD874,0x278E,0xFFFF8645,0xFFFFB4C5,0xFFFF9872,0xFFFF8000,0x0000,0xFFFFB4C3,0x678D,0x278D,0x79BC,0x79BB,0x278E,0x678E,0xFFFFB4C5,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C3,0xFFFF8644,0x278D,0xFFFFD872,0x79BC,0x4B3C,0x678E,0x8000,0x0000,0x4B3D,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8645,0xFFFFD872,0xFFFF9872,0x4B3B,0x0000,0x8000,0x678D,0x4B3D,0x79BC,0xFFFFD874,0x278E,0xFFFF8644,0xFFFFB4C5,0xFFFF9872,0xFFFF8000,0x0000,0xFFFFB4C3,0x678D,0x278C,0x79BC,0x79BB,0x278F,0x678E,0xFFFFB4C5,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C3,0xFFFF8644,0x278C,0xFFFFD872,0x79BB,0x4B3B,0x678E,0x8000,0x0000,0x4B3D,0xFFFF9873,0xFFFFD874,0xFFFF8644,0xFFFF8645,0xFFFFD872,0xFFFF9872,0x4B3B,0xFFFFFFFF,0x8000,0x678D,0x4B3D,0x79BC,0xFFFFD874,0x278E,0xFFFF8645,0xFFFFB4C5,0xFFFF9872,0xFFFF8000,0xFFFFFFFF,0xFFFFB4C3,0x678D,0x278C,0x79BC,0x79BB,0x278E,0x678E,0xFFFFB4C4,0x0000,0xFFFF8000,0xFFFF9873,0xFFFFB4C3,0xFFFF8644,0x278D,0xFFFFD872,0x79BB,0x4B3B,0x678E,0x8000,0x0000,0x4B3D,0xFFFF9873,0xFFFFD873,0xFFFF8644,0xFFFF8645,0xFFFFD872,0xFFFF9872,0x4B3B,0xFFFFFFFF,0x8000,0x678D,0x4B3D,0x79BC,0xFFFFD874,0x278E,0xFFFF8644,0xFFFFB4C5,0xFFFF9872,0xFFFF8000,0xFFFFFFFF,0xFFFFB4C3,0x678D,0x278C,0x79BC,0x79BB,0x278F,0x678E,0xFFFFB4C5,0x0000,0xFFFF8000,0xFFFF9874,0xFFFFB4C3,0xFFFF8644,0x278C,0xFFFFD871,0x79BB,0x4B3B,0x678E
	.align 4
cordic_yong_cos_sin:
	.int 0x0000,0x4000,0x2D41,0x2D41,0x3B20,0x187D,0x3EC5,0x0C7C,0x3FB1,0x0645,0x3FEC,0x0323,0x3FFB,0x0192,0x3FFE,0x00C9,0x3FFF,0x0064,0x3FFF,0x0032,0x3FFF,0x0019,0x3FFF,0x000C,0x3FFF,0x0006,0x3FFF,0x0003,0x3FFF,0x0001,0x3FFF,0x0000
	.align 4
dian_rong_dan_wei:
	.int  0x4670
	.align 4
yjmwxwx:
	.ascii "yjmwxwx-20200808"
	.align 4
kong:
	.int 0x20202020
_fu:
	.ascii "-"
ou:
        .int    0xf4
kai_lu_jiao_zhun:
	.ascii "kai lu jiao zhun"
duan_lu_jiao_zhun:
	.ascii "duan lu jiaozhun"
pi_pei_jiao_zhun:
	.ascii "pi pei jiao zhun"
	.align 4
cai_dan_biao:
	.word __cai_dan_0 +1
	.word __cai_dan_1 +1
	.word __cai_dan_2 +1
	.word __cai_dan_3 +1
	.word __cai_dan_4 +1
	.word __cai_dan_5 +1
	.word __cai_dan_6 +1
	
	.equ STACKINIT,        	        0x20001000
	.equ asciimabiao,		0x20000000
	.equ fuhao,			0x200000f0
	.equ Rs,			0x20000100	@串联电阻
	.equ Xs,			0x20000104	@串联电抗
	.equ Cs,			0x20000108	@串联电容
	.equ jiaodu,			0x20000108
	.equ kailu_r,			0x2000010c
	.equ liangcheng,		0x20000110
	.equ caidanzhizhen,		0x2000018c
	.equ caidanyanshi,		0x20000190
	.equ jiaozhunkaiguan,		0x20000194
        .equ dianyabiaozhizhen,         0x200001f8
        .equ dianyabiaoman,             0x200001fc
	.equ dianyabiao,		0x20000200
	.equ zhengxiangbiao,		0x20000390
	.equ fanxiangbiao,		0x20000520
        .equ lvboqizhizhen,             0x20000a00
        .equ lvboqihuanchong,           0x20000a04
        .equ lvboqizhizhen2,            0x20000c20
        .equ lvboqihuanchong2,          0x20000c24
	.equ kai_lu_r,			0x08002000
	.equ kai_lu_i,			0x08002004
	.equ duan_lu_r,			0x08002008
	.equ duan_lu_i,			0x0800200c
	.equ pi_pei_r,			0x08002010
	.equ pi_pei_i,			0x08002014
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
	.word _systickzhongduan +1           @ 15
	.word aaa +1     @ _wwdg +1          @ 0
	.word aaa +1     @_pvd +1            @ 1
	.word aaa +1     @_rtc +1            @ 2
	.word aaa +1     @_flash +1          @ 3
	.word aaa +1	@ _rcc + 1           @ 4
	.word aaa +1      @_exti0_1  +1      @ 5
	.word aaa +1      @ _exti2_3 +1      @ 6
	.word aaa +1       @_exti4_15 +1     @ 7
	.word aaa +1                         @ 8
	.word aaa +1	@__dma_wan  +1	     @ 9
	.word aaa +1    @_dma1_2_3 +1        @ 10
	.word aaa +1       @_dma1_4_5 +1     @ 11
	.word aaa +1	 @_adc1 +1           @ 12
	.word aaa +1       @_tim1_brk_up +1  @ 13
	.word aaa +1        @ _tim1_cc +1    @ 14
	.word aaa +1         @_tim2 +1       @ 15
	.word aaa +1          @_tim3 +1      @ 16
	.word aaa +1                         @ 17
	.word aaa +1		             @ 18
	.word aaa +1	@_tim14 +1           @ 19
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
	ldr r1, = 0x150002
	mov r0, r0
	str r1, [r0, # 0x04]
	mov r0, r0
	ldr r1, = 0x1010000
	mov r0, r0
	str r1, [r0]

dengpll:
        ldr r1, [r0]
	lsls r1, # 6
	bpl dengpll


	ldr r1, = 100
	str r1, [r0, # 0x30]
_waisheshizhong:                         @ 外设时钟
        @+0x14=RCC_AHBENR
	@ 0=DMA @ 2=SRAM @ 4=FLITF@ 6=CRC @ 17=PA @ 18=PB @ 19=PC @ 20=PD @ 22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x60001
        str r1, [r0, # 0x14]

        @+0x18外设时钟使能寄存器 (RCC_APB2ENR)
        @0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
        ldr r1, = 0xa00
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@ 1=TIM3 @ 4=TIM6 @ 5=TIM7 @ 8=TIM14 @ 11=WWDG @ 14=SPI @ 17=USRT2 @ 18=USART3 @ 20=USART5 @ 21=I2C1
	@ 22=I2C2 @ 23=USB @ 28=PWR
        ldr r2, = 0x902
        str r2, [r0, # 0x1c]

_neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
_neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan
_waishezhongduan:				@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效
	ldr r0, =  0xe000e100
	ldr r1, = 0x200 @0x10200  @ 0x10000
	str r1, [r0]
@_kanmengou:
@	ldr r0, = 0x40003000
@	ldr r1, = 0x5555
@	str r1, [r0]
@	movs r1, # 7
@	str r1, [r0, # 4]
@	ldr r1, = 0xfff
@	str r1, [r0, # 8]
@	ldr r1, = 0xaaaa
@	str r1, [r0]
@	ldr r1, = 0xcccc
@	str r1, [r0]


@_systick:				@ systick定时器初始化
@
@	ldr r0, = 0xe000e010
@	ldr r1, = 0xffffff
@	str r1, [r0, # 4]
@	str r1, [r0, # 8]	
@	movs r1, # 0x07
@	str r1, [r0]
	
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
	ldr r1, = 0x2824555f
	str r1, [r0]
	ldr r1, =  0x2fc
	str r1, [r0, # 0x04]
	ldr r1, = 0x200
	str r1, [r0, # 0x24]
	
	ldr r0, = 0x48000400
	movs r1, # 0x02
	str r1, [r0, # 0x04]
	movs r1, # 0x04
	str r1, [r0, # 0x0c]
_lcdchushihua:
	movs r0, # 0x33
	movs r1, # 0
	bl _xielcd
	bl _lcdyanshi

	movs r0, # 0x32
	movs r1, # 0
	bl _xielcd
	bl _lcdyanshi
	movs r0, # 0x28
	movs r1, # 0
	bl _xielcd
	bl _lcdyanshi
	movs r0, # 0x0c
	movs r1, # 0
	bl _xielcd
	bl _lcdyanshi
	movs r0, # 0x01
	movs r1, # 0
	bl _xielcd
	bl _lcdyanshi

        movs r0, # 0x80
        ldr r1, = yjmwxwx
	movs r2, # 16
        bl _lcdxianshi
	ldr r0, = 0xffff
yjmwxwx_yanshi:
	subs r0, r0, # 1
	bne yjmwxwx_yanshi

_adcchushihua:
        ldr r0, = 0x40012400  @ adc基地址
        ldr r1, = 0x80000000
        str r1, [r0, # 0x08]  @ ADC 控制寄存器 (ADC_CR)  @adc校准
_dengadcjiaozhun:
        ldr r1, [r0, # 0x08]
        movs r1, r1
        bmi _dengadcjiaozhun   @ 等ADC校准
	movs r1, # 1
	str r1, [r0]
_kaiadc:
        ldr r1, [r0, # 0x08]
        movs r2, # 0x01
        orrs r1, r1, r2
        str r1, [r0, # 0x08]
_deng_adc_wen_ding:
        ldr r1, [r0]
        lsls r1, r1, # 31
        bpl _deng_adc_wen_ding @ 等ADC稳定
_tongdaoxuanze:
        ldr r1, = 0x40000000
        str r1, [r0, # 0x10]
        ldr r1, = 0x02
        str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
        ldr r1, = 0xc03 @ 0xc43		@TIM3 0x8c3 @0x2003 @0x8c3
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

        @tim1ch3DMA
        ldr r0, = 0x40020000
        ldr r1, = 0x40012c3c @ 外设地址
        str r1, [r0, # 0x60]
        ldr r1, = zheng_xian_200khz @ 储存器地址
        str r1, [r0, # 0x64]
        ldr r1, = 200             @点数
        str r1, [r0, # 0x5c]
        ldr r1, = 0x35b1         @ 储存到外设
        str r1, [r0, # 0x58]

	@ adc dma
	ldr r0, = 0x40020000
	ldr r1, = 0x40012440
	str r1, [r0, # 0x10]
	ldr r1, = dianyabiao
	str r1, [r0, # 0x14]
	ldr r1, = 200
	str r1, [r0, # 0x0c]
	ldr r1, = 0x5a1 @  0x583 	@ 5a1
	str r1, [r0, # 0x08]

	
tim1chushiha:				
        ldr r0, = 0x40012c00 @ tim1_cr1
        movs r1, # 0
        str r1, [r0, # 0x28] @ psc
	ldr r1, = 13
        str r1, [r0, # 0x2c] @ ARR
	@movs r1, # 0x40
        movs r1, # 0x20
        str r1, [r0, # 0x04] @ TRGO
        movs r1, # 0x38
        str r1, [r0, # 0x18] @ ccmr1 cc1
        movs r1, # 13
        str r1, [r0, # 0x34]
        ldr r1, = 0x68
        str r1, [r0, # 0x1c] @ ccmr2  CC3
	ldr r1, = 0x100    @  CC3
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 0x8000
	str r1, [r0, # 0x44] @ BDTR
        ldr r1, = 0x800 @ CC3 DMA
        str r1, [r0, # 0x0c] @ DIER
        ldr r1, = 0x81
	str r1, [r0]

	ldr r0,= 0x48000000
	movs r1, # 0x1c
	str r1, [r0, # 0x18]

	
	ldr r0, = 0xffffff
adc_yanshi:
	subs r0, r0, # 1
	bne adc_yanshi
        movs r0, # 0x01
        movs r1, # 0
        bl _xielcd
	bl _lcdyanshi


	
ting:
	bl __ji_suan_zu_kang
	bl __dian_rong_ji_suan
__xianshi_zukang:	
        movs r0, # 0x8f
	ldr r1, = ou
        movs r2, # 1
        bl _lcdxianshi
	ldr r0, = Rs		@dianzu
	ldr r1, [r0]
       movs r4, r1
	bpl __dian_zu_bu_shi_zheng
	movs r0, # 0x82
        ldr r1, = _fu
        movs r2, # 1
        bl _lcdxianshi
        mvns r4, r4
        adds r4, r4, # 1
        b __xian_shi_dian_zu
__dian_zu_bu_shi_zheng:
	movs r0, # 0x82
	ldr r1, = kong
	movs r2, # 1
        bl _lcdxianshi
__xian_shi_dian_zu:
        mov r0, r4
        movs r1, # 5
        ldr r2, = asciimabiao
        movs r3, # 3
        bl _zhuanascii
        movs r0, # 0x83
        ldr r1, = asciimabiao
        movs r2, # 5
        bl _lcdxianshi

        ldr r0, = Xs		@diankang
        ldr r1, [r0]
       movs r4, r1
        bpl __dian_kang_bu_shi_zheng
        movs r0, # 0x88
        ldr r1, = _fu
        movs r2, # 1
        bl _lcdxianshi
        mvns r4, r4
        adds r4, r4, # 1
        b __xian_shi_dian_kang
__dian_kang_bu_shi_zheng:
        movs r0, # 0x88
        ldr r1, = kong
        movs r2, # 1
        bl _lcdxianshi
__xian_shi_dian_kang:
        mov r0, r4
        movs r1, # 5
        ldr r2, = asciimabiao
        movs r3, # 3
        bl _zhuanascii
        movs r0, # 0x89
        ldr r1, = asciimabiao
        movs r2, # 5
        bl _lcdxianshi
							@显示电容
        ldr r0, = Cs            @diankang
        ldr r1, [r0]
       movs r4, r1
        bpl __dian_rong_bu_shi_zheng
        movs r0, # 0xc8
        ldr r1, = _fu
        movs r2, # 1
        bl _lcdxianshi
        mvns r4, r4
        adds r4, r4, # 1
        b __xian_shi_dian_rong
__dian_rong_bu_shi_zheng:
        movs r0, # 0xc8
        ldr r1, = kong
	movs r2, # 1
	bl _lcdxianshi
__xian_shi_dian_rong:
        mov r0, r4
        movs r1, # 5
	movs r3, # 0xff
        ldr r2, = asciimabiao
        bl _zhuanascii
	movs r0, # 0xc9
        ldr r1, = asciimabiao
        movs r2, # 5
        bl _lcdxianshi
__xian_shi_dian_rong_dan_wei:	
	ldr r1, = dian_rong_dan_wei
	movs r0, # 0xce
	movs r2, # 2
	bl _lcdxianshi
	b ting

	
__cai_dan_0:

	b __cai_dan_0

__cai_dan_1:
	b __cai_dan_1
__cai_dan_2:
	b __cai_dan_2
__cai_dan_3:

__cai_dan_4:
__cai_dan_5:
__cai_dan_6:

	
__cai_dan_diao_du:
        mov r12, lr
        ldr r1, = caidanzhizhen
        ldr r0, = caidanyanshi
        ldr r2, [r1]
        ldr r3, [r0]
        adds r3, r3, #1
	cmp r3, # 10
        bhi __cai_dan_zhi_zhen_jia
        str r3, [r0]
        mov pc, r12
__cai_dan_zhi_zhen_jia:
        movs r3, # 0
        str r3, [r0]
        adds r2, r2, # 4
	cmp r2, # 0x14
        bls __cai_dan_qie_huan
        movs r2, # 0
__cai_dan_qie_huan:
        str r2, [r1]
	movs r0, # 0x01
        movs r1, # 0
        bl _xielcd
	bl _lcdyanshi
        ldr r0, = cai_dan_biao
        ldr r1, [r0, r2]
	mov pc, r1	
	
__dian_rong_ji_suan:
	push {r0-r4,lr}
	ldr r0, = Xs
	ldr r2, [r0]
	movs r2, r2
	bpl __dianrong_bu_shi_fu
	mvns r2, r2
	adds r2, r2, # 1
__dianrong_bu_shi_fu:
	movs r0, r2
	movs r1, # 10
	bl __chu_fa
	mov r2, r0
	ldr r1, = 1256637
	muls r2, r2, r1
	ldr r1, = 0xd4a51000
	movs r0, # 0xe8
	bl __chufa64
	ldr r3, = Cs
	str r1, [r3]
	pop {r0-r4,pc}
	
__ji_suan_zu_kang:
	push {r0-r7,lr}
	ldr r0, = 0x48000000
	ldr r1, = 0x200
	str r1, [r0, # 0x18]
	bl __tong_dao_qie_huan
	ldr r0, = zhengxiangbiao
	ldr r1, = fanxiangbiao
	bl __DFT_ji_suan
	mov r6, r0
	mov r7, r1

	ldr r0, = 0x48000000
        ldr r1, = 0x200
        str r1, [r0, # 0x28]
        bl __tong_dao_qie_huan
	ldr r0, = zhengxiangbiao
	ldr r1, = fanxiangbiao
        bl __DFT_ji_suan
	mov r2, r6
	mov r3, r7
	mvns r2, r2
	mvns r3, r3
	adds r2, r2, # 1
	adds r3, r3, # 1
	asrs r0, r0, # 1
	asrs r1, r1, # 1
	asrs r2, r2, # 1
	asrs r3, r3, # 1
	bl __fu_shu_chu_fa
	mov r3, r2
	mov r7, r1
        ldr r0, = lvboqihuanchong
        ldr r1, = 64
        ldr r2, = lvboqizhizhen
        bl _lvboqi
	mov r3, r7
	mov r7, r0
        ldr r0, = lvboqihuanchong2
        ldr r1, = 64
        ldr r2, = lvboqizhizhen2
        bl _lvboqi
	mov r1, r0
	mov r2, r7
	ldr r4, = Rs
	ldr r5, = Xs
	str r2, [r4]
	str r1, [r5]
	pop {r0-r7,pc}
__tong_dao_qie_huan:
	push {r0-r3,lr}
	ldr r0, = dianyabiao
	ldr r3, = 0x40012428
	movs r1, # 0x01
	str r1, [r3]
	bl __tong_dao_qie_huan_yan_shi
	ldr r1, = zhengxiangbiao
	movs r2, # 200
	bl __fu_zhi_nei_cun
	movs r1, # 0x02
	str r1, [r3]
	bl __tong_dao_qie_huan_yan_shi
	ldr r1, = fanxiangbiao
	movs r2, # 200
	bl __fu_zhi_nei_cun
	pop {r0-r3,pc}
	
__tong_dao_qie_huan_yan_shi:
	push {r7,lr}
	ldr r7, = 0xffff
__tong_dao_qie_huan_yan_shi_xun_huan:
	subs r7, r7, # 1
	bne __tong_dao_qie_huan_yan_shi_xun_huan
	pop {r7,pc}
__fu_zhi_nei_cun:
	@ 入口 R0 = 要复制的地址，R1=目标地址，R2=复制的数量
	push {r3-r4,lr}
	movs r4, # 0
__fu_zhi_xun_huan:	
	ldrh r3, [r0, r4]
	strh r3, [r1, r4]
	adds r4, r4, # 2
	subs r2, r2, # 1
	bne __fu_zhi_xun_huan
	pop {r3-r4,pc}
__DFT_ji_suan:
	@入口R0=正相表，R1=反相表
	push {r2-r7,lr}
	mov r4, r8
	mov r5, r9
	mov r6, r10
	push {r4-r6}
	movs r6, # 0
	mov r8, r6
	mov r9, r6
	movs r2, # 200
	adds r2, r2, r2
	mov r10, r2
	mov r2, r6
__ji_suan_dft_xun_huan:
	ldrh r3, [r0, r2]
	ldrh r4, [r1, r2]
	cmp r3, # 0
	beq __qu_fan_r4
	b __ji_suan_dft
__qu_fan_r4:
	mvns r4, r4
	adds r4, r4, # 1
	mov r3, r4
__ji_suan_dft:
	ldr r5, = xuan_zhuan_yin_zi
	ldr r7, [r5, r6]
	adds r6, r6, # 4
	muls r7, r7, r3		@ 实部
	asrs r7, r7, # 15
	mov r4, r8
	adds r4, r4, r7
	mov r8, r4
	ldr r7, [r5, r6]
	adds r6, r6, # 4
	muls r7, r7, r3		@ 虚部
	asrs r7, r7, # 15
	mov r4, r9
	adds r4, r4, r7
	mov r9, r4
	adds r2, r2, # 2
	cmp r2, r10
	bne __ji_suan_dft_xun_huan
	mov r0, r8
	mov r1, r9
	pop {r4-r6}
	mov r8, r4
	mov r9, r5
	mov r10, r6
	pop {r2-r7,pc}
__xian_shi_jiao_du:
	push {r0-r4,lr}
       ldr r0, = jiaodu
        ldr r1, [r0]
       movs r4, r1
        bpl __jiaodu_bu_shi_zheng
        movs r0, # 0x87
        ldr r1, = _fu
        movs r2, # 1
        bl _lcdxianshi
        mvns r4, r4
	adds r4, r4, # 1
        b __xian_shi_jiaodu
__jiaodu_bu_shi_zheng:
        movs r0, # 0x87
	ldr r1, = kong
	movs r2, # 1
        bl _lcdxianshi
__xian_shi_jiaodu:
        mov r0, r4
        movs r1, # 5
	ldr r2, = asciimabiao
        movs r3, # 0xff
        bl _zhuanascii
	movs r0, # 0x88
        ldr r1, = asciimabiao
	movs r2, # 5
	bl _lcdxianshi
	pop {r0-r4,pc}
        .ltorg


_xieflash:			@ flsh解锁
	ldr r0, = 0x40022000
	ldr r1, = 0x45670123
	str r1, [r0, # 0x04]
	ldr r1, = 0xcdef89ab
	str r1, [r0, # 0x04]
					@擦除2页
	movs r5, # 1
	ldr r4, = 0x8002000
	movs r7, # 1
	lsls r7, r7, # 10
_flashmang:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang
	movs r1, # 2
	str r1, [r0, # 0x10]
	str r4, [r0, # 0x14]
	movs r1, # 0x42
	str r1, [r0, # 0x10]
	add r4, r4, r7
	subs r5, # 1
	bne _flashmang
						@写FLASH
	ldr r7, = 0x8002000
	ldr r4, = kailu_r
	movs r5, # 0
	movs r6, # 0x06
_flashmang1:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang1
	movs r1, # 1
	str r1, [r0, # 0x10]
	ldrh r3, [r4, r5]
	strh r3, [r7, r5]
	adds r5, r5, # 2
_flashmang2:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang2
	ldrh r3, [r4, r5]
	strh r3, [r7, r5]
	adds r5, r5, # 2
	subs r6, r6, # 1
	bne _flashmang1
_flashmang4:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang4
	movs r1, # 0x80
	@str r1, [r0]          		@flsh上锁
	ldr r0, = 0xe000ed0c
	ldr r1, = 0x05fa0004
	str r1, [r0]          		@复位
	
__fu_shu_cheng_fa:
	push {r2-r7,lr}
	@r0=a,r1=b,r2=c,r3=d
        mov r4, r0      @a
        mov r5, r1      @b
	mov r6, r2	@c
	mov r7, r3	@d
        muls r0, r0, r2 @a*c
	muls r1, r1, r3 @b*d
        subs r0, r0, r1 @ac-bd
        muls r4, r4, r7 @a*d
        muls r5, r5, r6 @b*c
        adds r4, r4, r5 @ad+bc
	mov r1, r4
	pop {r2-r7,pc}
	
__an_jian:
	push {r1-r3,lr}
	ldr r0, = 0x48000010
	ldr r1, = 0x48000410
	ldr r2, [r0]	@pa4
	ldr r3, [r1]	@pb1
	lsls r2, r2, # 27
	lsrs r2, r2, # 31
	lsls r3, r3, # 30
	lsrs r3, r3, # 30
	orrs r3, r3, r2
	mov r0, r3	
	pop {r1-r3,pc}
__atan2_ji_suan:
	@入口R0=实部，R1=虚部，结果=R0
	push {r2-r7,lr}
	mov r2, r8
	push {r2}
	ldr r3, = cordic_yong_cos_sin
	movs r2, # 10
	muls r0, r0, r2
	muls r1, r1, r2
	movs r2, # 0
	mov r8, r2
	ldr r4, = 9000
	lsls r4, r4, # 15
__cordic_atan2_xun_huan:	
__du_cos_sin:	
	ldr r5, [r3]	@cos
	adds r3, r3, # 4
	mov r7, r5
	ldr r6, [r3]	@sin
	adds r3, r3, # 4
	mov r2, r6
        muls r5, r5, r0         @x*cos
        muls r2, r2, r0         @x*sin
        muls r6, r6, r1         @y*sin
        muls r7, r7, r1         @y*cos
	movs r1, r1
	bpl __ni_shi_zhen_zhuan
__shun_shi_zhen_zhuan:
	subs r5, r5, r6
	adds r7, r7, r2
	mov r6, r8
	adds r6, r6, r4
	mov r8, r6
	b __xuan_zhuan_wan
__ni_shi_zhen_zhuan:
	adds r5, r5, r6
	subs r7, r7, r2
	mov r6, r8
	subs r6, r6, r4
	mov r8, r6
__xuan_zhuan_wan:
	ldr r6, = cordic_yong_cos_sin
	movs r2, # 32
	lsls r2, r2, # 2
	adds r6, r6, r2
	asrs r5, r5, # 14
	asrs r7, r7, # 14
	mov r0, r5
	mov r1, r7
	lsrs r4, r4, # 1	@旋转
	cmp r3,	r6 
	bne __cordic_atan2_xun_huan
	mov r0, r8
	mvns r0, r0
	adds r0, r0, # 1
	asrs r0, r0, # 15
	mov r2, r8
	pop {r2}
	pop {r2-r7,pc}
	.ltorg

_lvboqi:
			@滤波器
			@R0=地址，R1=长度,r2=表指针地址,r3=ADC数值
			@出R0=结果
	push {r1-r7,lr}	
	ldr r5, [r2]		@读出表指针
	lsls r6, r1, # 2	
	str r3, [r0, r5]	@数值写到滤波器缓冲区
	adds r5, r5, # 4
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
	ldr r4, [r0, r5]
	adds r5, r5, # 4
	adds r7, r7, r4
	subs r1, r1, # 1
	bne _lvboqixunhuan
	asrs r0, r7, # 6	@修改
	pop {r1-r7,pc}
_lcdxianshi:	  		@r0=LCD位置，r1=数据地址，r2=长度
	push {r0-r4,lr}
	mov r4, r1

	movs r1, # 0
	bl _xielcd

	movs r1, # 1
	movs r3, # 0
_lcdxianshixunhuan:
	ldrb r0, [r4,r3]
	bl _xielcd
	adds r3, r3, # 1
	cmp r3, r2
	bne _lcdxianshixunhuan
	pop {r0-r4,pc}

_lcdyanshi:
	push {r5,lr}
	ldr r5, = 0x1000
_lcdyanshixunhuan:
	subs r5, r5, # 1
	bne _lcdyanshixunhuan
	pop {r5,pc}

_xielcd:			@入R0=8位,r1=0命令,r1=1数据
	push {r0-r5,lr}
	ldr r4, = liangcheng  @ 量程开关 (第6位和第7位)
	mov r2, r0
	ldr r5, [r4]
	lsrs r2, r2, # 4
	lsls r2, r2, # 2	@ 高四位
	lsls r0, r0, # 28
	lsrs r0, r0, # 26	@ 低四位
	lsls r1, r1, # 31
	bpl __lcd_ming_ling
__lcd_shu_ju:
	movs r3, # 0x03		@ RS = 1 E = 1
	b __xie_lcd_shu_ju
__lcd_ming_ling:
	movs r3, # 0x02		@ RS = 0 E = 1
__xie_lcd_shu_ju:
	adds r3, r3, r5
	mov r1, r0
	adds r2, r2, r3
	movs r0, r2
	bl __74hc595
	subs r0, r0, # 0x02
	bl __74hc595
	mov r0, r1
	adds r0, r0, r3
	bl __74hc595
	subs r0, r0, # 0x02
	bl __74hc595
	pop {r0-r5,pc}
	
__74hc595:			@ 入R0=8位
	push {r0-r7,lr}
	ldr r6, = 0x48000000
	movs r5, # 0x20		@ SRCLK
	movs r2, # 0x40		@ RCLK
	movs r3, # 0x80		@ SER
	movs r4, # 24
__595_yiweixunhuan:
	str r2, [r6, # 0x28]	@ rclk=0
	str r5, [r6, # 0x28]	@ srclk=0
	@ovs r7, # 0xff
	ldr r7, = 0x1ff
__595_yanshi:
	subs r7, r7, # 1
	bne __595_yanshi
	mov r1, r0
	lsls r1, r1, r4
	bpl __ser_0
__ser_1:
	str r3, [r6, # 0x18]	@ ser=1
	b __595_yiwei
__ser_0:
	str r3, [r6, # 0x28]	@ ser=0
__595_yiwei:
	str r5, [r6, # 0x18]
	@movs r7, # 0xff
	ldr r7, = 0x1ff
__595_yanshi1:
	subs r7, r7, # 1
	bne __595_yanshi1
	adds r4, r4, # 1
	cmp r4, # 32
	bne __595_yiweixunhuan
	str r2, [r6, # 0x18]	@ rclk=1
	@movs r7, # 0xff
	ldr r7, = 0x1ff
__595_yanshi2:
	subs r7, r7, # 1
	bne __595_yanshi2
	str r2, [r6, # 0x28]	@ rclk = 0
	pop {r0-r7,pc}



_zhuanascii:					@ 16进制转ASCII
		@ R0要转的数据， R1长度，R2结果表首地址, r3=小数点位置
	push {r0-r7,lr}
	mov r7, r3
	mov r5, r0
	mov r6, r1
	movs r1, # 10
_xunhuanqiuma:
	bl _chufa
	mov r4, r0
	muls r4, r1
	subs r3, r5, r4
	adds r3, r3, # 0x30
	mov r5, r0
	subs r6, r6, # 1
	beq _qiumafanhui
	cmp r6, r7
	bne _meidaoxiaoshudian
	movs r4, # 0x2e		@小数点
	strb r4, [r2,r6]	@插入小数点
	subs r6, r6, # 1
_meidaoxiaoshudian:
	strb r3, [r2,r6]
	movs r6, r6
	bne _xunhuanqiuma
	pop {r0-r7,pc}
_qiumafanhui:
	strb r3, [r2, r6]
	pop {r0-r7,pc}
__ji_suan_fu_du:    @ 计算幅度
                @ 入r0= 实部，r1= 虚部
                @ 出r0 = 幅度
                @ Mag ~=Alpha * max(|I|, |Q|) + Beta * min(|I|, |Q|)
                @ Alpha * Max + Beta * Min
        push {r1-r3,lr}
        movs r0, r0
        bpl _shibubushifushu
        mvns r0, r0                             @ 是负数转成正数
        adds r0, r0, # 1
_shibubushifushu:                               @ 实部不是负数
        movs r1, r1
        bpl _xububushifushu
        mvns r1, r1                             @ 是负数转成正数
        adds r1, r1, # 1
_xububushifushu:                                @ 虚部不是负数
        cmp r0, # 0
        bne _panduanxubushibushi0
        mov r0, r1
        pop {r1-r3,pc}
_panduanxubushibushi0:	
	cmp r1, # 0
	bne _jisuanfudu1
	pop {r1-r3,pc}
_jisuanfudu1:
	ldr r2, = 31066		@ Alpha q15 0.948059448969
	ldr r3, = 12867		@ Beta q15 0.392699081699
	cmp r1, r0
	bhi _alpha_min_beta_max
_alpha_max_beta_min:
	muls r0, r0, r2
	muls r1, r1, r3
	asrs r0, r0, # 15
	asrs r1, r1, # 15
	adds r0, r0, r1
	movs r1, # 1
	pop {r1-r3,pc}
_alpha_min_beta_max:
	muls r0, r0, r3
	muls r1, r1, r2
	asrs r0, r0, # 15
	asrs r1, r1, # 15
	adds r0, r0, r1
	movs r1, # 0
	pop {r1-r3,pc}
	.ltorg
__fu_shu_chu_fa:
	push {r4-r7,lr}
	@入口R0=a R1=b,R2=c R3=d
	@出口R1=虚部 R2=实部
	mov r4, r8
	push {r4}
__ji_suan_chu_fa:
	@ Z=50*[(a+bi)/(c+di)]=50*[(ac+bd)/(c*c+d*d)+(bc-ad)/(c*c+d*d)]
	mov r4, r0
	mov r5, r1
	mov r6, r2
	@mov r7, r3
	mov r8, r3
	movs r7,  # 0
        movs r0, r0
        bpl b1
        mvns r0, r0
        adds r0, r0, # 1
        adds r7, r7, # 1

b1:
        movs r2, r2
        bpl b2
	mvns r2, r2
        adds r2, r2, # 1
        adds r7, r7, # 1
b2:
	muls r0, r0, r2
        cmp r7, # 1
        bne b3
        mvns r0, r0
        adds r0, r0, # 1
b3:
	@muls r0, r0, r2		@ac
        movs r7,  # 0
        movs r1, r1
        bpl b4
        mvns r1, r1
        adds r1, r1, # 1
        adds r7, r7, # 1

b4:
        movs r3, r3
        bpl b5
        mvns r3, r3
        adds r3, r3, # 1
        adds r7, r7, # 1
b5:
        muls r1, r1, r3
        cmp r7, # 1
        bne b6
        mvns r1, r1
        adds r1, r1, # 1
b6:

@	muls r1, r1, r3		@bd
	adds r0, r0, r1		@ac+bd
	movs r2, r2
	bpl b7
	mvns r2, r2
	adds r2, r2, # 1
	muls r2, r2, r2
	mvns r2, r2
	adds r2, r2, # 1
	b b8
b7:	
        muls r2, r2, r2         @c*c
b8:
	movs r3, r3
	bpl b9
	mvns r3, r3
	adds r3, r3, # 1
	muls r3, r3, r3
	mvns r3, r3
	adds r3, r3, # 1
	b b10
b9:	
	muls r3, r3, r3		@d*d
b10:	
	adds r2, r2, r3		@c*c+d*d
	ldr r1, = 1000
	movs r3, # 0
	movs r0, r0
	bpl a1
	mvns r0, r0
	adds r0, r0, # 1
	adds r3, r3, # 1
a1:
	movs r2, r2
	bpl a2
	mvns r2, r2
	adds r2, r2, # 1
	adds r3, r3, # 1
a2:
	bl __chengfa
	bl __chufa64		@(ac+bd)/(c*c+d*d)
	cmp r3, # 1
	bne a3
	mvns r1, r1
	adds r1, r1, # 1
a3:	
	push {r1}
	mov r7, r8
	muls r5, r5, r6		@ bc
	muls r4, r4, r7		@ ad
	subs r5, r5, r4		@ bc-ad
	ldr r1, = 1000
	movs r3, # 0
	movs r0, r5
	bpl a4
	mvns r0, r0
	adds r0, r0, # 1
	adds r3, r3, # 1
a4:
	movs r2, r2
	bpl a5
	mvns r2, r2
	adds r2, r2, # 1
	adds r3, r3, # 1
a5:
	bl __chengfa
	bl __chufa64
	cmp r3, # 1
	bne __a6
	mvns r1, r1
	adds r1, r1, # 1	@虚部
__a6:	
	pop {r2}		@实
	pop {r4}
	mov r8, r4
	pop {r4-r7,pc}

__chufa64:
        @64位除32位
        @ （R0=高32位R1=低32位）除（R2)= （R0高32）（R1低32）
        push {r3-r7,lr}
        cmp r2, # 0
        beq __chu_fa64_fan_hui0
        cmp r1, # 0
        bne __chu_fa64_ji_suan
        cmp r0, # 0
        beq __chu_fa64_fan_hui0
__chu_fa64_ji_suan:	
        movs r4, # 0
        mov r7, r4
        mov r3, r4
        mov r5, r4
        movs r6, # 1
        lsls r6, r6, # 31
__chu_fa64_xun_huan:
        lsls r1, r1, # 1
        adcs r0, r0, r0
        adcs r4, r4, r4
        cmp r4, r2
        bcc __chu_fa_yi_wei
        adds r3, r3, r6
        adcs r5, r5, r7
        subs r4, r4, r2
__chu_fa_yi_wei:
        movs r6, r6
        beq __di_yi_wei
        lsrs r6, r6, # 1        @高32位移位
        bne __chu_fa64_xun_huan
        movs r7, # 1
        lsls r7, r7, # 31
        b __chu_fa64_xun_huan
__di_yi_wei:            @低32位移位
	lsrs r7, r7, # 1
        bne __chu_fa64_xun_huan
        mov r0, r3
        mov r1, r5
        pop {r3-r7,pc}
__chu_fa64_fan_hui0:
	movs r0, # 0
	movs r1, # 0
	pop {r3-r7,pc}

	
__chengfa:
        @入R0 乘以 R1
        @出 R0高32 ， R1低32
	@0xffffffff*0xffffffff
        @4        F F F E 0 0 0 1
        @3                F F F E 0 0 0 1
        @2                F F F E 0 0 0 1
        @1                        F F F E 0 0 0 1
        @         F F F F F F F E 0 0 0 0 0 0 0 1
	push {r2-r7,lr}
        cmp r0, # 0
        beq __cheng_fa_fan_hui
        cmp r1, # 0
        beq __cheng_fa_fan_hui
__ji_suan_cheng_fa:	
	mov r2, r0
	mov r3, r1
	lsrs r0, r0, # 16	@高16
	lsls r2, r2, # 16	@ 低16
	lsrs r2, r2, # 16
        lsrs r1, r1, # 16	@高16
	lsls r3, r3, # 16	@低16
	lsrs r3, r3, # 16
	mov r4, r2		
	mov r5, r0		
	muls r2, r2, r3		@1
	muls r0, r0, r3		@2
	muls r4, r4, r1		@3
	muls r5, r5, r1		@4
	mov r6, r0		@2
	mov r7, r4		@3
	lsls r0, r0, # 16	@2低
	lsls r4, r4, # 16	@3低
	lsrs r6, r6, # 16	@2高
	lsrs r7, r7, # 16	@3高
	adds r2, r2, r0
	adcs r2, r2, r4
	adcs r5, r5, r6
	adcs r5, r5, r7
	mov r0, r5
	mov r1, r2
	pop {r2-r7,pc}
__cheng_fa_fan_hui:
	movs r0, # 0
	movs r1, # 0
	pop {r2-r7,pc}
__dai_yu_shu_chufa:                         @软件除法
        @ r0 除以 r1 等于 商(r0)余R1
        push {r2-r4,lr}
        cmp r0, # 0
        beq __dai_yu_shu_chufafanhui
        cmp r1, # 0
        beq __dai_yu_shu_chufafanhui
        mov r2, r0
        movs r3, # 1
        lsls r3, r3, # 31
        movs r0, # 0
        mov r4, r0
__dai_yu_shu_chufaxunhuan:
        lsls r2, r2, # 1
        adcs r4, r4, r4
        cmp r4, r1
        bcc __dai_yu_shu_chufaweishubudao0
	adds r0, r0, r3
        subs r4, r4, r1
__dai_yu_shu_chufaweishubudao0:
        lsrs r3, r3, # 1
        bne __dai_yu_shu_chufaxunhuan
__dai_yu_shu_chufafanhui:
        pop {r2-r4,pc}

_chufa:				@软件除法
	@ r0 除以 r1 等于 商(r0)
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
__chu_fa:	@带符号
	push {r1-r7,lr}
        cmp r0, # 0
        beq _chufafanhui1
        cmp r1, # 0
        beq _chufafanhui1
	movs r5, # 0
	movs r0, r0
	bpl __pan_duan_bei_chu_shu
	adds r5, r5, # 1
	mvns r0, r0
	adds r0, r0, # 1
__pan_duan_bei_chu_shu:
	movs r1, r1
	bpl __ji_suan_chu_fa11
	adds r5, r5, # 1
	mvns r1, r1
	adds r1, r1, # 1
__ji_suan_chu_fa11:	
        mov r2, r0
        movs r3, # 1
        lsls r3, r3, # 31
        movs r0, # 0
        mov r4, r0
_chufaxunhuan1:
        lsls r2, r2, # 1
        adcs r4, r4, r4
        cmp r4, r1
	bcc _chufaweishubudao00
	adds r0, r0, r3
	subs r4, r4, r1
_chufaweishubudao00:
	lsrs r3, r3, # 1
	bne _chufaxunhuan1
	cmp r5, # 1
	bne _chufafanhui2
	mvns r0, r0
	adds r0, r0, # 1
	pop {r1-r7,pc}
_chufafanhui1:
	movs r0, #0
_chufafanhui2:	
	pop {r1-r7,pc}

__he_bing_dian_ya_biao:
	push {r0-r7,lr}
	ldr r0, = zhengxiangbiao
	ldr r1, = fanxiangbiao
	ldr r2, = 0x20000750
	movs r3, # 0
	mov r6, r3
	movs r7, # 200
	mov r8, r3	
__he_bing_dian_ya_biao_xun_huan:
        ldrh r4, [r0, r3]
        ldrh r5, [r1, r3]
        mov r8, r3
        cmp r4, r5
	bhi __zheng_dian_ya
	mov r3, r5
        bl __zhuan_bcd
        ldr r5, = 0x80000000
        orrs r5, r5, r3
	str r5, [r2, r6]
        b __dian_ya_biao_jia
__zheng_dian_ya:
        mov r3, r4
        bl __zhuan_bcd
        str r3, [r2, r6]
__dian_ya_biao_jia:
        mov r3, r8
        adds r3, r3, # 2
        adds r6, r6, # 4
        subs r7, r7, # 1
	bne __he_bing_dian_ya_biao_xun_huan
	pop {r0-r7,pc}
__zhuan_bcd:
	push {r0-r2,r4-r7,lr}
	movs r1, # 10
	mov r0, r3
	mov r5, r3
	movs r6, # 8
__bcd_xun_huan:
	bl _chufa
	mov r4, r0
	muls r4, r4, r1
	subs r5, r5, r4
	push {r5}
	mov r5, r0
	subs r6, r6, # 1
	bne __bcd_xun_huan
	pop {r0-r7}
	lsls r6, r6, # 4
	lsls r5, r5, # 8
	lsls r4, r4, # 12
	lsls r3, r3, # 16
	lsls r2, r2, # 20
	lsls r1, r1, # 24
	lsls r0, r0, # 28
	orrs r3, r3, r0
	orrs r3, r3, r1
	orrs r3, r3, r2
	orrs r3, r3, r4
	orrs r3, r3, r5
	orrs r3, r3, r6
	orrs r3, r3, r7
	pop {r0-r2,r4-r7,pc}
	.ltorg
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
	.ltorg
	.end
