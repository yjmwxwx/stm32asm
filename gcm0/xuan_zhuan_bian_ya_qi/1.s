	@@ 单片机stm32f030f4p6
	@旋转变压器
	@作者：yjmwxwx
	@时间：2021-02-02
	@编译器：ARM-NONE-EABI
	.thumb
	.syntax unified
	.section .data
yjmwxwx:
	.ascii "yjmwxwx-20210202"
kong:
	.int 0x20202020
_fu:
	.ascii "-"
jiaodu1:
	.int 0x3df2
jiaodufuhao:
	.int 0xdf
	.align 4
zheng_xian_biao:
	.short 28,29,31,33,34,36,38,39,41,42,44,45,46,48,49,50,51,52,52,53,54,54,55,55,55,55,55,55,55,54,54,53,52,52,51,50,49,48,46,45,44,42,41,39,38,36,34,33,31,29,28,26,24,22,21,19,17,16,14,13,11,10,9,7,6,5,4,3,3,2,1,1,0,0,0,0,0,0,0,1,1,2,3,3,4,5,6,7,9,10,11,13,14,16,17,19,21,22,24,26,28	
	.align 4
cordic_yong_cos_sin:
	.int 0x0000,0x4000,0x2D41,0x2D41,0x3B20,0x187D,0x3EC5,0x0C7C,0x3FB1,0x0645,0x3FEC,0x0323,0x3FFB,0x0192,0x3FFE,0x00C9,0x3FFF,0x0064,0x3FFF,0x0032,0x3FFF,0x0019,0x3FFF,0x000C,0x3FFF,0x0006,0x3FFF,0x0003,0x3FFF,0x0001,0x3FFF,0x0000
cordic_yong_atan_biao:
	.int 0x00006487,0x00003B58,0x00001F5B,0x00000FEA,0x000007FD,0x000003FF,0x000001FF,0x000000FF,0x0000007F,0x0000003F,0x0000001F,0x0000000F,0x00000007,0x00000003,0x00000001,0x00000000
	.align 4
	.equ STACKINIT,        	        0x20001000
	.equ asciimabiao,		0x20000000
	.equ guoling_jishu,		0x200000a8
	.equ jiaodu2,			0x200000ac
	.equ zhuansu,			0x200000b0
	.equ jishu,			0x200000b4
	.equ cos,			0x200000b8
	.equ sin,			0x200000bc
	.equ cos1,			0x200000c0
	.equ sin1,			0x200000c4
	.equ jiaodu_cha,		0x200000c8
	.equ jiaodu_1,			0x200000cc
	.equ cos_jiaozheng,		0x200000e0
	.equ sin_jiaozheng,		0x200000e4
	.equ jiaodu_jiaozheng,		0x200000e8
	.equ guoling,			0x200000ec
	.equ jiaodu,			0x200000f0
	.equ sin_zheng,			0x200000f4
	.equ sin_fu,			0x200000f8
	.equ liangcheng,		0x200000fc
	.equ dianyabiao,		0x20000100
	.equ lvboqizhizhen,		0x20000300
	.equ lvboqihuanchong,		0x20000304
	.equ lvboqizhizhen1,		0x20000900
	.equ lvboqihuanchong1,		0x20000904
	.equ lvboqizhizhen2,		0x20000a10
	.equ lvboqihuanchong2,		0x20000a14
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
	ldr r1, = 0x281457c1
	str r1, [r0]
	ldr r1, =  0x6e0
	str r1, [r0, # 0x04]
	ldr r1, = 0x0c3c0000
	str r1, [r0, # 0x08]

	ldr r0, = 0x48000400
	movs r1, # 0x08 @ pb1
	str r1, [r0]
	movs r1, # 0x20
	str r1, [r0, # 0x20]
	
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
	movs r1, # 0x18
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
	ldr r1, = 0xaa1		@ 5a1
	str r1, [r0, # 0x08]

_systick:	@ systick定时器初始化

	ldr r7, = 0xe000e010
	ldr r6, = 5600
	str r6, [r7, # 4]
	str r6, [r7, # 8]
	movs r6, # 0x07
tim1chushiha:
	ldr r0, = 0x40012c00 @ tim1_cr1
	movs r1, # 0
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 56
	str r1, [r0, # 0x2c] @ ARR
	@	movs r1, # 0x40
	movs r1, # 0x20
	str r1, [r0, # 0x04] @ TRGO
	movs r1, # 0x38
	str r1, [r0, # 0x18] @ ccmr1 cc1
	movs r1, # 56
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
	str r6, [r7]	@systick 开
	
	
ting:
	b ting
	ldr r0, = cos1
	ldr r1, = sin1
	ldr r0, [r0]
	ldr r1, [r1]
	mov r7, r0
	mov r6, r1
	
	bl __atan2_ji_suan
        bpl __xianshi
	ldr r1, = 36000
	mvns r0, r0
	adds r0, r0, # 1
	subs r0, r1, r0
__xianshi:	
	bl __xian_shi_jiao_du
	
	movs r4, r7
	bpl a1
	movs r0, # 0xc0
	ldr r1, = _fu
	movs r2, # 1
	bl _lcdxianshi
	mvns r4, r4
	adds r4, r4, # 1
	b a2
a1:	
	movs r0, # 0xc0
	ldr r1, = kong
	movs r2, # 1
	bl _lcdxianshi
a2:	
	mov r0, r4
	movs r1, # 4
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0xc1
	ldr r1, = asciimabiao
	movs r2, # 4
	bl _lcdxianshi

	
	movs r4, r6
	bpl b1
	movs r0, # 0xc8
	ldr r1, = _fu
	movs r2, # 1
	bl _lcdxianshi
	mvns r4, r4
	adds r4, r4, # 1
	b b2
b1:
	movs r0, # 0xc8
	ldr r1, = kong
	movs r2, # 1
	bl _lcdxianshi
b2:
	mov r0, r4
	movs r1, # 4
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0xc9
	ldr r1, = asciimabiao
	movs r2, # 4
	bl _lcdxianshi

	bl __jisuan_zhuansu
	ldr r0, = zhuansu
	ldr r4, [r0]
	mov r0, r4
	movs r1, # 6
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0x80
	ldr r1, = asciimabiao
	movs r2, # 6
	bl _lcdxianshi
	
	b ting


__jisuan_zhuansu:
	@角度差0.01秒
	push {r0-r3,lr}
	ldr r0, = jiaodu_cha
	ldr r1, = 18849555
	ldr r0, [r0]
	movs r0, r0
	bpl __suan_zhuansu
	mvns r0, r0
	adds r0, r0, # 1
__suan_zhuansu:	
	ldr r2, = 113097335
	bl __chengfa
	bl __chufa64
	ldr r2, = zhuansu
	str r1, [r2]
	pop {r0-r3,pc}


	
__xian_shi_jiao_du:
	@入口R0=角度
	push {r0-r4,lr}
	mov r4, r0
	movs r0, # 0x8f
	ldr r1, = jiaodufuhao
	movs r2, # 1
	bl _lcdxianshi

	movs r4, r4
	bpl __jiaodu_bu_shi_zheng
	movs r0, # 0x88
	ldr r1, = _fu
	movs r2, # 1
	bl _lcdxianshi
	mvns r4, r4
	adds r4, r4, # 1
	b __xian_shi_jiaodu
__jiaodu_bu_shi_zheng:
	movs r0, # 0x88
	ldr r1, = kong
	movs r2, # 1
	bl _lcdxianshi
__xian_shi_jiaodu:
	mov r0, r4
	movs r1, # 6
	ldr r2, = asciimabiao
	movs r3, # 3
	bl _zhuanascii
	movs r0, # 0x89
	ldr r1, = asciimabiao
	movs r2, # 6
	bl _lcdxianshi
	pop {r0-r4,pc}

__xiang_wei_xuan_zhuan:
	push {r2-r7,lr}
	@R0=R,R1=I
	mov r3, r0
	mov r0, r1
	ldr r4, = cos_jiaozheng         @cos
	ldr r5, = sin_jiaozheng         @sin
	ldr r4, [r4]
	ldr r5, [r5]
	movs r4, r4
	bpl __xuan_zhuan_xiang_wei
	mov r6, r4
	mov r7, r5
	mov r4, r7
	mov r5, r6
__xuan_zhuan_xiang_wei:
	mov r6, r4
	mov r7, r5
	muls r4, r4, r3         @x*cos
	muls r6, r6, r0         @y*cos
	muls r5, r5, r3         @x*sin
	muls r7, r7, r0         @y*sin
	asrs r4, r4, # 15
	asrs r5, r5, # 15
	asrs r6, r6, # 15
	asrs r7, r7, # 15

	subs r4, r4, r7         @x
	adds r6, r6, r5         @y
	mov r1, r6		@i
	mov r0, r4		@r
	pop {r2-r7,pc}
__cordic_cos_sin:
	@入口R0
	@出口R0=COS，R1=SIN
	@ x= 0x4dba
	@ r1=x,r2=y,r0=z,r4=d,r5=k,r6=cordic_mabiao

	push {r2-r7,lr}
	mov r2, r8
	mov r3, r9
	push {r2-r3}
	movs r5, # 0
	mov r2, r5
	mov r4, r5
	ldr r1, = 0x4dba
cordicxunhuan:		 @ 循环
	asrs r4, r0, # 15
	@ x
	mov r7, r2
	asrs r2, r2, r5
	eors r2, r2, r4
	subs r2, r2, r4
	subs r3, r1, r2
	@ y
	mov r6, r1
	asrs r1, r1, r5
	eors r1, r1, r4
	subs r1, r1, r4
	adds r7, r7, r1
	@ z
	ldr r6, = cordic_yong_atan_biao
	lsls r2, r5, # 2
	ldr r1, [r6, r2]
	eors r1, r1, r4
	subs r1, r1, r4
	subs r0, r0, r1
	mov r1, r3
	mov r2, r7
	adds r5, # 1
	cmp r5, # 16
	bne cordicxunhuan
	mov r0, r3
	mov r1, r7
	pop {r2-r3}
	mov r8, r2
	mov r9, r3
	pop {r2-r7,pc}
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
	asrs r0, r0, # 15      @除32768等于角度
	pop {r2}
	mov r8, r2
	pop {r2-r7,pc}
	.ltorg


	
__xiangwei_jiaozheng:
	push {r0-r5,lr}
	ldr r0, = jiaodu_jiaozheng
	ldr r1, = 9000
	ldr r0, [r0]
	ldr r2, = 51471
	movs r0, r0
	bpl __jiaozheng_jiaodu_bushi0
	mvns r0, r0
	adds r0, r0, # 1
	movs r4, # 1
__jiaozheng_jiaodu_bushi0:
	movs r4, # 0
	ldr r5, = 10000
	muls r0, r0, r5
	bl _chufa
	muls r0, r0, r2
	mov r1, r5
	bl _chufa
	cmp r4, # 1
	bne __suan_cos_sin
	mvns r0, r0
	adds r0, r0, # 1
__suan_cos_sin:
	bl __cordic_cos_sin
	ldr r2, = cos_jiaozheng
	ldr r3, = sin_jiaozheng
	str r0, [r2]
	str r1, [r3]
	pop {r0-r5,pc}


__chuan_gan_qi_lvbo:
	push {r2-r7,lr}
	ldr r0, = 0x20000174 @sin_zheng
	ldr r1, = 0x2000023c @sin_fu
	ldr r3, = 0x20000170 @cos_zheng
	ldr r2, = 0x20000238 @cos_fu
	ldr r4, [r0]
	ldr r5, [r1]
	ldr r6, [r2]
	ldr r7, [r3]
	ldr r2, = guoling
	subs r4, r4, r5
	subs r6, r6, r7
	ldr r3, [r2]
	movs r4, r4
	bpl __zheng
__fan:
	movs r1, # 0
	str r1, [r2]
	b __guo_ling_jian_ce
__zheng:
	movs r1, # 1
	str r1, [r2]
__guo_ling_jian_ce:
	ldr r2, = jiaodu
	ldr r0, = jiaodu_jiaozheng
	ldr r2, [r2]
	subs r1, r1, r3
	bmi __zheng_90
	beq __xiangwei
__fu_90:
	b __xiangwei
	movs r2, r2
	bpl __xiangwei
	ldr r1, = -9000
	subs r1, r1, r2
	b __baocun_jiaozheng
__zheng_90:
	movs r6, r6
	bmi __xiangwei
	movs r4, r4
	bpl __xiangwei
	ldr r7, = guoling_jishu
	str r2, [r7]
	ldr r1, = 9000
	subs r1, r2, r1
__baocun_jiaozheng:
	str r1, [r0]
	bl __xiangwei_jiaozheng
__xiangwei:
	
__lv_bo:
	mov r3, r6
	ldr r2, = lvboqizhizhen
	ldr r0, =lvboqihuanchong
	ldr r1, = 128
	bl _lvboqi
	mov r3, r4
	mov r6, r0
	ldr r2, = lvboqizhizhen1
	ldr r0, = lvboqihuanchong1
	ldr r1, = 128
	bl _lvboqi
	mov r1, r6
	mov r4, r0
	bl __xiang_wei_xuan_zhuan
	ldr r7, = cos1
	ldr r5, = sin1
	str r0, [r7]
	str r1, [r5]
	mov r1, r6
	mov r0, r4
	pop {r2-r7,pc}


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
	asrs r0, r7, # 7	@修改
	pop {r1-r7,pc}

_lvboqi1:
	@滤波器
	@R0=地址，R1=长度,r2=表指针地址,r3=ADC数值
	@出R0=结果
	push {r1-r7,lr}
	ldr r5, [r2]            @读出表指针
	lsls r6, r1, # 1
	strh r3, [r0, r5]        @数值写到滤波器缓冲区
	adds r5, r5, # 2
	cmp r5, r6
	bne _lvboqimeidaohuanchongquding1
	movs r5, # 0
_lvboqimeidaohuanchongquding1:
	str r5, [r2]
	movs r7, # 0
_lvboqixunhuan1:
	cmp r5, r6
	bne _lvbozonghe1
	movs r5, # 0
_lvbozonghe1:
	ldrh r4, [r0, r5]
	adds r5, r5, # 2
	adds r7, r7, r4
	subs r1, r1, # 1
	bne _lvboqixunhuan1
	asrs r0, r7, # 9        @修改
	pop {r1-r7,pc}
	
	.ltorg
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
__di_yi_wei:	            @低32位移位
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
	@4        F F F E 0 0 0 1			@4
	@3                F F F E 0 0 0 1		@3
	@2                F F F E 0 0 0 1		@2
	@1                        F F F E 0 0 0 1	@1
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
	mov r6, r0
	mov r7, r4
	lsls r0, r0, # 16	@2低32
	lsls r4, r4, # 16	@3低32
	lsrs r6, r6, # 16	@2高32
	lsrs r7, r7, # 16	@3高32
	movs r1, # 0
	adds r2, r2, r0		@低32
	adcs r6, r6, r1		@高32
	adds r2, r2, r4
	adcs r6, r6, r7
	adds r6, r6, r5
	mov r0, r6
	mov r1, r2
	pop {r2-r7,pc}
__cheng_fa_fan_hui:
	movs r0, # 0
	movs r1, # 0
	pop {r2-r7,pc}
__dai_yu_shu_chufa:	                         @软件除法
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
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
_systickzhongduan:
	push {r4-r7,lr}
	ldr r0, = 0xe0000d04
	ldr r1, = 0x02000000
	str r1, [r0]                 @ 清除SYSTICK中断
	bl __chuan_gan_qi_lvbo
	ldr r2, = cos
	ldr r3, = sin
	str r0, [r2]		@r
	str r1, [r3]		@i
	bl __atan2_ji_suan
	ldr r4, = jiaodu
	str r0, [r4]

	ldr r0, = cos1
	ldr r1, = sin1
	ldr r0, [r0]
	ldr r1, [r1]
	bl __atan2_ji_suan
	
@	b __systick_fanhui
	b __led_jiance1

	
	movs r0, r0
	bpl __jiaodu_bushi_fu
	ldr r1, = 36000
	mvns r0, r0
	adds r0, r0, # 1
	subs r0, r1, r0
__jiaodu_bushi_fu:
	str r0, [r4]


__led_jiance1:
	ldr r3, = 100
	ldr r2, = 0x48000000
	movs r1, # 1
	cmp r0, # 10
	bls __led_guan1
	cmp r0, r3
	bhi __led_guan1
	str r1, [r2, # 0x18]
	b __ji_shu
__led_guan1:
	str r1, [r2, # 0x28]
	

__ji_shu:
	b __systick_fanhui
	
	
	
	ldr r3, = jishu
	ldr r2, [r3]
	adds r2, r2, # 1
	str r2, [r3]
	cmp r2, # 101
	bne __budao_jiaodu
	movs r2, # 0
	str r2, [r3]
	ldr r2, = 10000
	ldr r1, = jiaodu_1
	ldr r3, = jiaodu_cha
	ldr r1, [r1]
	subs r0, r0, r1
	movs r0, r0
	bpl __jiaodu_cha_bushi_fu
	mvns r0, r0
	adds r0, r0, # 1
__jiaodu_cha_bushi_fu:
	cmp r0, r2
	bhi __jiaodu_kua_360
	cmp r0, # 10
	bls __mei_zhuan 
	str r0, [r3]
	b __systick_fanhui
__mei_zhuan:
	movs r0, # 0
	str r0, [r3]
	b __systick_fanhui
__jiaodu_kua_360:
	b __systick_fanhui
__budao_jiaodu:
	cmp r2, # 1
	beq __baocun_jiaodu1
	b __systick_fanhui
__baocun_jiaodu1:
	ldr r2, = jiaodu_1
	str r0, [r2]
	b __systick_fanhui
__systick_fanhui:	
	pop {r4-r7,pc}
aaa:
	bx lr
	.ltorg
	.end
