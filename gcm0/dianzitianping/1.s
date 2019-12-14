	@@单片机stm32f030f4p6
	@@电子天平
	@作者：yjmwxwx
	@时间：2019-12-01
	@编译器：ARM-NONE-EABI
	 .thumb
	         .syntax unified
	.section .data
shumaguanmabiao:
	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6
shumaguanshuaxinbiao:
	.int 0xfe00,0xfd00,0xfb00,0xf700,0xef00,0xdf00,0xbf00,0x7f00,0
zheng_xian_biao:
	.short 0x30,0x33,0x36,0x38,0x3b,0x3e,0x41,0x44,0x47,0x49,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x59,0x5b,0x5c,0x5d,0x5e,0x5e,0x5f,0x5f,0x5f,0x5f,0x5f,0x5e,0x5d,0x5c,0x5b,0x5a,0x59,0x57,0x55,0x53,0x51,0x4f,0x4d,0x4a,0x48,0x45,0x43,0x40,0x3d,0x3a,0x37,0x34,0x31,0x2e,0x2b,0x28,0x25,0x22,0x1f,0x1c,0x1a,0x17,0x15,0x12,0x10,0xe,0xc,0xa,0x8,0x6,0x5,0x4,0x3,0x2,0x1,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x2,0x3,0x4,0x6,0x7,0x9,0xb,0xd,0xf,0x11,0x13,0x16,0x18,0x1b,0x1e,0x21,0x24,0x27,0x29,0x2c,0x30
yjmwxwx:
	.ascii  "yjmwxwx-20191201-dian_zi_tian_ping"
	.equ STACKINIT,        	        0x20001000
	.equ shumaguanma,		0x20000000
	.equ fuhao,			0x20000010
	.equ jishu,			0x20000030
	.equ lvboqizhizhen,		0x20000040
	.equ lvboqihuanchong,		0x20000044
	.equ dang_qin_cha,		0X2000025C
	.equ shang_ci_cha,		0x20000260
	.equ shang_ci_i,		0x20000264
	.equ anjianyanshi,		0x20000268
	.equ dianyabiao,		0x20000500
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
        ldr r1, = 0x110002
        str r1, [r0, # 0x04]
	ldr r1, = 0x1010001
	str r1, [r0]
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

_neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
_neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan

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
	movs r1, # 0x02
	str r1, [r0, # 0x1c]


_waishezhongduan:				@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效

@_systick:				@ systick定时器初始化

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
	ldr r1, = 0x2800a15b
	str r1, [r0]

	ldr r1, = 0x40400
	str r1, [r0, # 0x0c] @pa5 pa9上拉
	
	ldr r1, = 0x11000000
	str r1, [r0, # 0x20]	@ pa6\pa7 TIM3

	ldr r0, = 0x48000400
	movs r1, # 0x08 @ pb1
	str r1, [r0]
	movs r1, # 0x20
	str r1, [r0, # 0x20]

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

	
tim1chushihua:
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

_tim3chushiha:				
	ldr r0, = 0x40000400 @ tim3_cr1
	movs r1, # 0
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 4800
	str r1, [r0, # 0x2c] @ ARR
	ldr r1, = 0x6868
	str r1, [r0, # 0x18] @ ccmr1
	movs r1, # 0x11
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 1
	str r1, [r0, # 0x34]
	ldr  r1, = 100
	str r1, [r0, # 0x38]
	movs r1, # 0x81
	str r1, [r0]
_tingting:
	ldr r0, = 0x20000530
	ldr r2, = 0x20000590
	ldrh r1, [r0]
	ldrh r3, [r2]
	subs r3, r3, r1
		@ 1b6
	movs r1, # 0
	mov r0, r3
	subs r0, r0, r1
	bl __pid





	
__xian_shi_led:
	movs r3, r3
	bpl __bu_shi_fu_shu
	mvns r3, r3
	adds r3, r3, # 1
	ldr r0, = fuhao
	movs r1, # 0
	str r1, [r0]
	b __led_xian_shi
__bu_shi_fu_shu:
	ldr r0, = fuhao
	movs r1, # 0x02
	str r1, [r0]
__led_xian_shi:	
	ldr r0, = lvboqihuanchong
	ldr r1, = 256
	ldr r2, = lvboqizhizhen
	bl _lvboqi
	movs r1, # 4
        ldr r2, = shumaguanma
	movs r3, # 0xff		@小数点位置
        bl _zhuanshumaguanma
	movs r0, # 5
        bl _xieshumaguan
	b _tingting

__pid:
	@ 入口r0=e(t)当前差多少
	push {r2-r7,lr}
	mov r4, r0
	mov r5, r0
__bi_li:
	ldr r2, = 10000		@ KP
	muls r0, r0, r2
	asrs r0, r0, # 15
__ji_fen:
	ldr r7, = shang_ci_i
	ldr r2, = 10		@ KI
	ldr r3, [r7]
	muls r4, r4, r2
	asrs r4, r4, # 15
	adds r4, r4, r3
	str r4, [r7]
__wei_fen:
	ldr r7, = shang_ci_cha
	ldr r2, = 200		@ KD	
	ldr r3, [r7]
	subs r5, r5, r3
	muls r5, r5, r2
	asrs r5, r5, # 15
__pid_shu_chu:
	adds r0, r0, r4
	adds r0, r0, r5
	bl __dian_ci_tie
	pop {r2-r7,pc}
	
	
__dian_ci_tie:
	@ 入口 R0=输入值
	push {r1-r3,lr}
	ldr r1, = 0x40000400
	ldr r3, = 3000
	movs r0, r0
	bpl __dian_ci_tie_shang
__dian_ci_tie_xia:
	mvns r0, r0
	adds r0, r0, # 1
	cmp r0, r3
	bls __xia_shu_chu
	mov r0, r3
__xia_shu_chu:	
	movs r2, # 0
	str r2, [r1, # 0x34]
	str r0, [r1, # 0x38]
	pop {r1-r3,pc}
__dian_ci_tie_shang:
	cmp r0, r3
	bls __shang_shu_chu
	mov r0, r3
__shang_shu_chu:	
	movs r2, # 0
	str r2, [r1, # 0x38]
	str r0, [r1, # 0x34]
	pop {r1-r3,pc}

_zhuanshumaguanma:@ 16进制转数码管码
	@ R0要转的数据， R1长度，R2结果表首地址
	@ r3 小数点位置
	push {r4-r7,lr}
	ldr r7, = shumaguanmabiao
	mov r5, r0
	mov r6, r1
	movs r1, # 10
	mov r8, r3
_xunhuanqiuma:
	bl _chufa
	mov r4, r0
	muls r4, r1
	subs r3, r5, r4
	lsls r3, # 2
	ldr r4, [r7, r3]
	cmp r6, r8
	beq __tian_jia_xiao_shu_dian
	b __bao_cun_shu_ma_guan_ma
__tian_jia_xiao_shu_dian:
	adds r4, r4, # 1
__bao_cun_shu_ma_guan_ma:	
	str r4, [r2]
	mov r5, r0
	adds r2, r2, # 4
	subs r6, # 1
	bne _xunhuanqiuma
	pop {r4-r7,pc}
_xieshumaguan: @ r0=位数 @数码管码
	push {r1-r7,lr}
	lsls r0, r0, # 2
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
	pop {r1-r7,pc}
	
_xie595: @ R0=要写的数据
	push {r1-r7,lr}
	mov r5, r0
	movs r0, # 0x08      @pa6
	movs r7, # 0x10      @pa7
	movs r6, # 0x04      @pa5 
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
	pop {r1-r7,pc}


_yanshi:
	push {r7}
	ldr r7, = 30
_yanshi11:
	subs r7, # 1
	bne _yanshi11
	pop {r7}
	bx lr
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
	ldr r2, = jishu
	ldr r0, = 0xe0000d04
	ldr r3, [r2]
	ldr r1, = 0x02000000
	adds r3, r3, # 1
	str r3, [r2]
	str r1, [r0]                 @ 清除SYSTICK中断
aaa:
	bx lr
