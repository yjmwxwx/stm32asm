	@@ 单片机stm32f030f4p6
	@@ 阻抗桥
	@作者：yjmwxwx
	@时间：2019-08-12
	@编译器：ARM-NONE-EABI
	 .thumb
	         .syntax unified
.section .data
zheng_xian_biao:
	.short 0x18,0x19,0x1a,0x1c,0x1d,0x1f,0x20,0x22,0x23,0x24,0x25,0x26,0x28,0x29,0x2a,0x2b,0x2b,0x2c,0x2d,0x2d,0x2e,0x2e,0x2f,0x2f,0x2f,0x2f,0x2f,0x2f,0x2f,0x2e,0x2e,0x2d,0x2d,0x2c,0x2b,0x2b,0x2a,0x29,0x28,0x26,0x25,0x24,0x23,0x22,0x20,0x1f,0x1d,0x1c,0x1a,0x19,0x18,0x16,0x15,0x13,0x12,0x10,0xf,0xd,0xc,0xb,0xa,0x9,0x7,0x6,0x5,0x4,0x4,0x3,0x2,0x2,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x2,0x2,0x3,0x4,0x4,0x5,0x6,0x7,0x9,0xa,0xb,0xc,0xd,0xf,0x10,0x12,0x13,0x15,0x16,0x18
	.align 4
xuan_zhuan_yin_zi:
	.int 0x8000,0x0000,0x7EFD,0xFFFFEFF6,0x7BFA,0xFFFFE02B,0x7702,0xFFFFD0E2,0x702A,0xFFFFC256,0x678D,0xFFFFB4C4,0x5D4E,0xFFFFA861,0x5197,0xFFFF9D60,0x4495,0xFFFF93EE,0x367F,0xFFFF8C2F,0x278D,0xFFFF8644,0x17FC,0xFFFF8245,0x0809,0xFFFF8041,0xFFFFF7F7,0xFFFF8041,0xFFFFE804,0xFFFF8245,0xFFFFD873,0xFFFF8644,0xFFFFC981,0xFFFF8C2F,0xFFFFBB6B,0xFFFF93EE,0xFFFFAE69,0xFFFF9D60,0xFFFFA2B2,0xFFFFA861,0xFFFF9873,0xFFFFB4C4,0xFFFF8FD6,0xFFFFC256,0xFFFF88FE,0xFFFFD0E2,0xFFFF8406,0xFFFFE02B,0xFFFF8103,0xFFFFEFF6,0xFFFF8000,0x0000,0xFFFF8103,0x100A,0xFFFF8406,0x1FD5,0xFFFF88FE,0x2F1E,0xFFFF8FD6,0x3DAA,0xFFFF9873,0x4B3C,0xFFFFA2B2,0x579F,0xFFFFAE69,0x62A0,0xFFFFBB6B,0x6C12,0xFFFFC981,0x73D1,0xFFFFD873,0x79BC,0xFFFFE804,0x7DBB,0xFFFFF7F7,0x7FBF,0x0809,0x7FBF,0x17FC,0x7DBB,0x278D,0x79BC,0x367F,0x73D1,0x4495,0x6C12,0x5197,0x62A0,0x5D4E,0x579F,0x678D,0x4B3C,0x702A,0x3DAA,0x7702,0x2F1E,0x7BFA,0x1FD5,0x7EFD,0x100A,0x8000,0x0000,0x7EFD,0xFFFFEFF6,0x7BFA,0xFFFFE02B,0x7702,0xFFFFD0E2,0x702A,0xFFFFC256,0x678D,0xFFFFB4C4,0x5D4E,0xFFFFA861,0x5197,0xFFFF9D60,0x4496,0xFFFF93EE,0x367F,0xFFFF8C2F,0x278D,0xFFFF8644,0x17FC,0xFFFF8245,0x0809,0xFFFF8041,0xFFFFF7F7,0xFFFF8041,0xFFFFE804,0xFFFF8245,0xFFFFD873,0xFFFF8644,0xFFFFC981,0xFFFF8C2F,0xFFFFBB6B,0xFFFF93EE,0xFFFFAE69,0xFFFF9D60,0xFFFFA2B2,0xFFFFA861,0xFFFF9873,0xFFFFB4C4,0xFFFF8FD6,0xFFFFC256,0xFFFF88FE,0xFFFFD0E2,0xFFFF8406,0xFFFFE02B,0xFFFF8103,0xFFFFEFF6,0xFFFF8000,0x0000,0xFFFF8103,0x100A,0xFFFF8406,0x1FD5,0xFFFF88FE,0x2F1E,0xFFFF8FD6,0x3DAA,0xFFFF9873,0x4B3C,0xFFFFA2B2,0x579F,0xFFFFAE69,0x62A0,0xFFFFBB6A,0x6C12,0xFFFFC981,0x73D1,0xFFFFD873,0x79BC,0xFFFFE804,0x7DBB,0xFFFFF7F7,0x7FBF,0x0809,0x7FBF,0x17FC,0x7DBB,0x278D,0x79BC,0x367F,0x73D1,0x4495,0x6C12,0x5197,0x62A0,0x5D4E,0x579F,0x678D,0x4B3C,0x702A,0x3DAA,0x7702,0x2F1E,0x7BFA,0x1FD5,0x7EFD,0x100B
	.align 4
liang_cheng_biao:
	.int 0x00c00000,0x00c00300,0x00c00000,0x00800000,0x00400000,0x00000000
fang_da_huan_suan_biao:	
	.int 0x00010001,0x00010003,0x00010001,0x00000064,0x0000000a,0x00010001
zu_kang_dan_wei:
	.short 0xf420,0xf46d,0xf420,0xf46b,0xf46b,0xf46b
xiao_shu_dian_wei_zhi:
	.byte 3,4,3,3,3,3
	.align 4
dian_rong_huan_suan_biao:
	.int 0x00000064,0x000003e8,0x00000064,0x000003e8,0x00000064,0x10000001
dian_rong_dan_wei:
	.short 0x4675,0x466d,0x4675,0x466e,0x4670,0x4670
dian_rong_xiao_shu_dian_wei_zhi:
	.byte 1,1,1,2,0xff,2
	.align 4
dian_gan_huan_suan_biao:
	.int 10000,100000,1,1,1,1
dian_gan_dan_wei:
	.short 0x4875,0x4875,0x4875,0x4875,0x4875,0x4875
dian_gan_xiao_shu_dian_wei_zhi:
	.byte 4,3,4,1,1,1
lcdshuju:
	.ascii  "yjmwxwx-20190812"
dianhua:	
	.ascii	"     15552208295"
qq:
	.ascii	"   QQ:3341656346"
_fu:
	.ascii "-"
pinlv10k:
	.ascii	"m"
kong:
	.int 0x20202020

	.equ STACKINIT,        	        0x20001000
	.equ asciimabiao,		0x20000000
	.equ liangcheng,		0x20000030
	.equ jishu,			0x20000034
	.equ jianbo,			0x20000038
	.equ dianyabiao,		0x20000040
	.equ zhengxiangbiao,		0x20000110
	.equ fanxiangbiao,		0x200001e0
	.equ lvboqizhizhen,		0x20000600
	.equ lvboqihuanchong,		0x20000604
	.equ lvboqizhizhen1,		0x20000700
	.equ lvboqihuanchong1,		0x20000704
	.equ lvboqizhizhen2,		0x20000800
	.equ lvboqihuanchong2,		0x20000804
	.equ lvboqizhizhen3,		0x20000900
	.equ lvboqihuanchong3,		0x20000904
	.equ xia_bi_shi_bu,		0x20000a00
	.equ shang_bi_shi_bu,		0x20000a04
	.equ xia_bi_xu_bu,		0x20000a08
	.equ shang_bi_xu_bu,		0x20000a0c
	.equ bu_chang_100r,		0x20000a10
	.equ zidongliangchengyanshi,	0x20000a14
	.equ dianzuzhi,			0x20000a18
	.equ diankangzhi,		0x20000a20
	.equ shangbifangda,		0x20000a28
	.equ xiabifangda,		0x20000a2c
	.equ anjian,			0x20000a30
	.equ bu_chang_1k,		0x20000a34
	.equ dianrongzhi,		0x20000a38
	.equ shang,			0x20000a40
	.equ xiaoshudian,		0x20000a44
	.equ anjianyanshi,		0x20000a48
	.equ liangcheng1,		0x20000a4c
	.equ fudu,			0x20000a50
	.equ dianrongxiaoshudian,	0x20000a54
	.equ dianganzhi,		0x20000a58
	.equ dianganxiaoshudian,	0x20000a5c
	.equ L_C_qie_huan,		0x20000a60
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
	ldr r0, = 0xffff
yanshi111:
	subs r0, r0, # 1
	bne yanshi111	
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

_waishezhongduan:				@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效

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
	ldr r1, = 0x2824550f
	str r1, [r0]
	ldr r1, = 0x200
	str r1, [r0, # 0x24]

	movs r1, # 0x50 @ pa2 pa3上拉
	str r1, [r0, # 0x0c]

	ldr r0, = 0x48000400
	ldr r1, = 0x00000004
	str r1, [r0]

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
	ldr r1, = 2
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
        ldr r1, = 47
        str r1, [r0, # 0x2c] @ ARR
	@	movs r1, # 0x40
	movs r1, # 0x20
	str r1, [r0, # 0x04] @ TRGO
	movs r1, # 0x38
	str r1, [r0, # 0x18] @ ccmr1 cc1
	movs r1, # 47
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


	ldr r0, = liangcheng
	movs r1, # 0xc0
	str r1, [r0]
        ldr r0, = shangbifangda
        ldr r1, = xiabifangda
        movs r2, # 0
        str r2, [r0]
	movs r2, # 0
        str r2, [r1]
ting:
        bl __an_jian_ji_shu
        bl _jianbo
        bl __zhen_fu_lv_bo
	bl __zu_kang_ji_suan
	bl __fang_da_huan_suan
	bl __dian_rong_ji_suan
	bl __dian_gan_ji_suan
	bl __dan_wei_xian_shi
	bl __dian_rong_huan_suan
	bl __dian_gan_huan_suan
	bl __xiao_shu_dian_xian_shi
	ldr r0, = dianzuzhi
	ldr r4, [r0]
	movs r4, r4
        bpl __dian_zu_zheng
        movs r0, # 0x82
        ldr r1, = _fu
        movs r2, # 1
	bl _lcdxianshi
        mvns r4, r4
        adds r4, r4, # 1
        b __xian_shi_dian_zu
__dian_zu_zheng:
        movs r0, # 0x82
        ldr r1, = kong
        movs r2, # 1
        bl _lcdxianshi
__xian_shi_dian_zu:
	mov r0, r4
	ldr r3, = xiaoshudian
        movs r1, # 5
	ldr r3, [r3]
        ldr r2, = asciimabiao
	bl _zhuanascii
	movs r0, # 0x83
	ldr r1, = asciimabiao
        movs r2, # 5
        bl _lcdxianshi

        ldr r0, = diankangzhi
        ldr r4, [r0]
        movs r4, r4
        bpl __dian_kang_zheng
	movs r0, # 0x88
        ldr r1, = _fu
        movs r2, # 1
	bl _lcdxianshi
        mvns r4, r4
        adds r4, r4, # 1
        b __xian_shi_dian_kang
__dian_kang_zheng:
	movs r0, # 0x88
        ldr r1, = kong
        movs r2, # 1
        bl _lcdxianshi
__xian_shi_dian_kang:
        mov r0, r4
	ldr r3, = xiaoshudian
        movs r1, # 5
	ldr r3, [r3]
        ldr r2, = asciimabiao
        bl _zhuanascii
        movs r0, # 0x89
	ldr r1, = asciimabiao
	movs r2, # 5
        bl _lcdxianshi


	ldr r0, = liangcheng1
        movs r1, # 2
	ldr r0, [r0]
	ldr r2, = asciimabiao
        movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0x80
	ldr r1, = asciimabiao
	movs r2, # 2
	bl _lcdxianshi
__xian_shi_pin_lv:
        movs r0, # 0xc0
        ldr r1, = pinlv10k
        movs r2, # 1
        bl _lcdxianshi
	ldr r0, = L_C_qie_huan
	ldr r0, [r0]
	cmp r0, # 1
	bne __xian_shi_dian_gan
__xian_shi_dian_rong:
	ldr r0, = dianrongzhi
        movs r1, # 5
	ldr r0, [r0]
	ldr r3, = dianrongxiaoshudian
        ldr r2, = asciimabiao
        ldr r3, [r3]
        bl _zhuanascii
	movs r0, # 0xc9
        ldr r1, = asciimabiao
	movs r2, # 5
        bl _lcdxianshi
	b ting
__xian_shi_dian_gan:
	ldr r0, = dianganzhi
	movs r1, # 5
	ldr r3, = dianganxiaoshudian
	ldr r0, [r0]
	ldr r3, [r3]
	ldr r2, = asciimabiao
	bl _zhuanascii
	movs r0, # 0x0c9
	ldr r1, = asciimabiao
	movs r2, # 5
	bl _lcdxianshi
	b ting	
ddd:
	bl __an_jian_ji_shu
	bl _jianbo
        bl __zhen_fu_lv_bo
        ldr r0, = xia_bi_shi_bu
        ldr r1, = shang_bi_shi_bu
        ldr r2, = xia_bi_xu_bu
        ldr r3, = shang_bi_xu_bu
        ldr r0, [r0]
        ldr r1, [r1]
        ldr r2, [r2]
        ldr r3, [r3]
        bl __xian_shi_shang_xia_bi

	ldr r0, = liangcheng1
        ldr r0, [r0]
	movs r1, # 2
        ldr r2, = asciimabiao
        movs r3, # 0xff
        bl _zhuanascii
        movs r0, # 0xc7
        ldr r1, = asciimabiao
        movs r2, # 2
	bl _lcdxianshi

        ldr r0, = shangbifangda
        ldr r0, [r0]
        movs r1, # 1
        ldr r2, = asciimabiao
        movs r3, # 0xff
        bl _zhuanascii
        movs r0, # 0x87
        ldr r1, = asciimabiao
        movs r2, # 1
	bl _lcdxianshi

        ldr r0, = xiabifangda
        ldr r0, [r0]
        movs r1, # 1
        ldr r2, = asciimabiao
        movs r3, # 0xff
        bl _zhuanascii
        movs r0, # 0x88
        ldr r1, = asciimabiao
        movs r2, # 1
	bl _lcdxianshi

	b ddd
	.ltorg
__xiao_shu_dian_xian_shi:
	push {r0-r3,lr}
	ldr r0, = liangcheng1
	ldr r1, = xiao_shu_dian_wei_zhi
	ldr r3, [r0]
	ldr r2, = xiaoshudian
	ldrb r0, [r1, r3]
	str r0, [r2]
	ldr r1, = dian_rong_xiao_shu_dian_wei_zhi
	ldr r2, = dianrongxiaoshudian
	ldrb r0, [r1, r3]
	str r0, [r2]
	ldr r1, = dian_gan_xiao_shu_dian_wei_zhi
	ldr r2, = dianganxiaoshudian
	ldrb r0, [r1, r3]
	str r0, [r2]
	pop {r0-r3,pc}
__dan_wei_xian_shi:
	push {r0-r3,lr}
	ldr r0, = liangcheng1
	ldr r1, = zu_kang_dan_wei
	ldr r0, [r0]
	lsls r0, r0, # 1
	mov r3, r0
	adds r1, r1, r0
	movs r0, # 0x8e
	movs r2, # 2
	bl _lcdxianshi
	ldr r1, = L_C_qie_huan
	ldr r1, [r1]
	cmp r1, # 1
	beq __xian_shi_dian_rong_dan_wei
	ldr r1, = dian_gan_dan_wei
	adds r1, r1, r3
	movs r0, # 0xce
	movs r2, # 2
	bl _lcdxianshi
	pop {r0-r3,pc}
__xian_shi_dian_rong_dan_wei:	
	ldr r1, = dian_rong_dan_wei
	adds r1, r1, r3
	movs r0, # 0xce
	movs r2, # 2
	bl _lcdxianshi
	pop {r0-r3,pc}
__dian_rong_huan_suan:
	push {r0-r3,lr}
	ldr r0, = liangcheng1
	ldr r1, = dian_rong_huan_suan_biao
	ldr r2, [r0]
	lsls r2, r2, # 2
	ldr r3, [r1, r2]
	mov r2, r3
	lsrs r2, r2, # 31
	lsls r3, r3, # 16
	lsrs r3, r3, # 16
	cmp r2, # 1
	beq __dian_rong_cheng
	mov r1, r3
	ldr r3, = dianrongzhi
	ldr r0, [r3]
	bl _chufa
	str r0, [r3]
	pop {r0-r3,pc}
__dian_rong_cheng:
	ldr r0, = dianrongzhi
	ldr r1, [r0]
	muls r1, r1, r3
	str r1, [r0]
	pop {r0-r3,pc}
__dian_gan_huan_suan:
	push {r0-r3,lr}
	ldr r0, = liangcheng1
	ldr r3, = dian_gan_huan_suan_biao
	ldr r2, [r0]
	ldr r0, = dianganzhi
	lsls r2, r2, # 2
	ldr r1, [r3, r2]
	mov r3, r0
	ldr r0, [r0]
	bl _chufa
	str r0, [r3]
	pop {r0-r3,pc}
__fang_da_huan_suan:
	push {r0-r3,lr}
	ldr r0, = liangcheng1
	ldr r1, = fang_da_huan_suan_biao
	ldr r2, [r0]
	lsls r2, r2, # 2
	ldr r3, [r1, r2]
	mov r2, r3
	lsrs r2, r2, # 16
	lsls r3, r3, # 16
	lsrs r3, r3, # 16
	cmp r2, # 1
	beq __fang_da_cheng
	mov r1, r3
	ldr r3, = dianzuzhi
	ldr r0, [r3]
	bl __chu_fa
	str r0, [r3]
	ldr r3, = diankangzhi
	ldr r0, [r3]
	bl __chu_fa
	str r0, [r3]
	ldr r3, = fudu
	ldr r0, [r3]
	bl __chu_fa
	str r0, [r3]
	pop {r0-r3,pc}
__fang_da_cheng:
	ldr r0, = dianzuzhi
	ldr r1, [r0]
	muls r1, r1, r3
	str r1, [r0]
	ldr r0, = diankangzhi
	ldr r1, [r0]
	muls r1, r1, r3
	str r1, [r0]
	ldr r0, = fudu
	ldr r1, [r0]
	muls r1, r1, r3
	str r1, [r0]
	pop {r0-r3,pc}
__an_jian_ji_shu:
	push {r0-r3,lr}
	bl __an_jian
	cmp r0, # 1
	bne __dian_gan_dian_rong_qie_huan
	ldr r1, = anjianyanshi
	ldr r2, [r1]
	adds r2, r2, # 1
	str r2, [r1]
	cmp r2, # 10
	bne __an_jian_ji_shu_fan_hui
	movs r2, # 0
	str r2, [r1]
	ldr r1, = liangcheng1
	ldr r0, [r1]
	adds r0, r0, # 1
	str r0, [r1]
	cmp r0, # 6		@量程总数
	bne __xie_ru_liang_cheng
	movs r0, # 0
	str r0, [r1]
__xie_ru_liang_cheng:
	bl __liang_cheng_she_zhi
	pop {r0-r3,pc}
__dian_gan_dian_rong_qie_huan:
	cmp r0, # 2
	bne __an_jian_ji_shu_fan_hui
	ldr r1, = anjianyanshi
	ldr r2, [r1]
	adds r2, r2, # 1
	str r2, [r1]
	cmp r2, # 10
	bne __an_jian_ji_shu_fan_hui
	movs r2, # 0
	str r2, [r1]
	ldr r1, = L_C_qie_huan
	ldr r0, [r1]
	adds r0, r0, # 1
	str r0, [r1]
	cmp r0, # 2
	bne __an_jian_ji_shu_fan_hui
	movs r0, # 0
	str r0, [r1]
__an_jian_ji_shu_fan_hui:
	pop {r0-r3,pc}
	.ltorg
__liang_cheng_she_zhi:
	@ 入口=liangcheng
	push {r1-r7,lr}
	ldr r1, = liang_cheng_biao
	lsls r0, r0, # 2
	ldr r2, [r1, r0]	@ r2=liangcheng
	mov r3, r2		@ r3=shangbifangda
	mov r4, r2		@ r4=xiabifangda
	ldr r5, = liangcheng
	ldr r6, = shangbifangda
	ldr r7, = xiabifangda
	lsrs r2, r2, # 22
	lsls r2, r2, # 6
	lsls r3, r3, # 22
	lsrs r3, r3, # 30
	lsls r4, r4, # 30
	lsrs r4, r4, # 30
	str r2, [r5]
	str r3, [r6]
	str r4, [r7]
	pop {r1-r7,pc}

	
__zi_dong_liang_cheng:
	push {r0-r5,lr}	
	ldr r0, = zidongliangchengyanshi
	ldr r2, = 100
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	cmp r1, r2
	beq __liang_cheng_ji_suan
	pop {r0-r5,pc}
__liang_cheng_ji_suan:
	movs r1, # 0
	str r1, [r0]
	ldr r4, = 2000
	ldr r0, = liangcheng
	ldr r1, = xia_bi_shi_bu
	ldr r5, = xia_bi_xu_bu
	ldr r3, [r0]
	ldr r2, [r1]
	ldr r5, [r5]
	movs r2, r2
	bpl __pan_duan_xu_bu_liang_cheng
	mvns r2, r2
	adds r2, r2, # 1
__pan_duan_xu_bu_liang_cheng:	
	movs r5, r5
	bpl __xia_bi_da_xiao_pan_duan
	mvns r5, r5
	adds r5, r5, # 1
__xia_bi_da_xiao_pan_duan:	
	cmp r2, r4
	bcc __pan_duan_xu_bu
	b __gai_liang_cheng
__pan_duan_xu_bu:
	ldr r4, = 3000
	cmp r5, r4
	bcc __pan_duan_xuan_kong
__gai_liang_cheng:
	adds r3, r3, # 0x40
	cmp r3, # 0xc0
	bls __bao_cun_liang_cheng
	movs r3, # 0xc0
__bao_cun_liang_cheng:
	str r3, [r0]
__pan_duan_xuan_kong:
	cmp r2, # 20
	bcs __liang_cheng_fan_hui
	cmp r5, # 20
	bcs __liang_cheng_fan_hui
	movs r3, # 0
	str r3, [r0]
__liang_cheng_fan_hui:
	pop {r0-r5,pc}
__dian_gan_ji_suan:
	push {r0-r2,lr}
	ldr r0, = diankangzhi
	ldr r0, [r0]
	ldr  r1, = 1000000000
	bl __chengfa
	ldr r2, = 62831
	bl __chufa64
	ldr r2, = dianganzhi
	str r1, [r2]
	pop {r0-r2,pc}
__dian_rong_ji_suan:
	push {r0-r4,lr}
	ldr r0, = diankangzhi
	ldr r2, [r0]
	mvns r2, r2
	adds r2, r2, # 1
	ldr r1, = 62831
	muls r2, r2, r1
	ldr r1, = 0xd4a51000
	movs r0, # 0xe8
	bl __chufa64
	ldr r3, = dianrongzhi
	str r1, [r3]
	pop {r0-r4,pc}
__an_jian:
	@ 出口 R0=00(没有按)，1（按键1）2(按键2)3（按键1+2）
	push {r1}
	ldr r1, = 0x48000010
	ldr r0, [r1]
	mvns r0, r0
	lsls r0, r0, # 28
	lsrs r0, r0, # 30
	pop {r1}
	bx lr
__fang_da:
	@ 入口r0=0(放大1)，1（放大3），2（放大9）,3（放大29）
	push {r1-r4,lr}
        ldr r2, = 0x48000000
        ldr r1, = 0x48000400
	movs r3, # 0x02
	movs r4, # 0x10
	lsls r0, r0, # 30
	bmi __pa4_guan
	str r4, [r2, # 0x18]
	b __pan_duan_pb1
__pa4_guan:
	str r4, [r2, # 0x28]
__pan_duan_pb1:
        lsls r0, r0, # 1
        bmi __pb1_guan
        str r3, [r1, # 0x18]
	pop {r1-r4,pc}
__pb1_guan:
	str r3, [r1, # 0x28]
	pop {r1-r4,pc}
	
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
	
__zu_kang_ji_suan:
	push {r0-r7,lr}
	ldr r0, = shang_bi_shi_bu
	ldr r1, = shang_bi_xu_bu
	ldr r2, = xia_bi_shi_bu
	ldr r3, = xia_bi_xu_bu
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	ldr r3, [r3]
__ji_suan_zu_kang:
@ Z=R+jx
@ Z=R*[(a+bi)/(c+di)]=R*[(ac+bd)/(c*c+d*d)+(bc-ad)/(c*c+d*d)]
@c=1/[(2*pi*f)*xc]
	mov r4, r0
	mov r5, r1
	mov r6, r2
	mov r7, r3
	muls r0, r0, r2		@ac
	muls r1, r1, r3		@bd
	adds r0, r0, r1		@ac+bd
	muls r2, r2, r2		@c*c
	muls r3, r3, r3		@d*d
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
	adds r1, r1, # 1
__a6:	
	pop {r2}		@实
	ldr r4, = dianzuzhi
	ldr r5, = diankangzhi
	str r1, [r5]
	str r2, [r4]
	mov r0, r2
	bl __ji_suan_fu_du
	ldr r1, = fudu
	str r0, [r1]
	pop {r0-r7,pc}
__fu_zhi_nei_cun:
	@ 入口 R0 = 要复制的地址，R1=目标地址，R2=复制的数量
	push {r4,lr}
	movs r4, # 0
__fu_zhi_xun_huan:	
	ldrh r3, [r0, r4]
	strh r3, [r1, r4]
	adds r4, r4, # 2
	subs r2, r2, # 1
	bne __fu_zhi_xun_huan
	pop {r4,pc}

__xian_shi_shang_xia_bi:
@入口 R0= 下臂实部，R1=上臂实部，R2=下臂虚部，R3=上臂虚部
	push {r0-r7,lr}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
@显示上臂实部
	movs r4, r1
	bpl __shang_bi_shi_bu_zheng
        movs r0, # 0x80
        ldr r1, = _fu
        movs r2, # 1
        bl _lcdxianshi
	mvns r4, r4
	adds r4, r4, # 1
	b __xian_shi_shang_bi_shi_bu
__shang_bi_shi_bu_zheng:	
        movs r0, # 0x80
	ldr r1, = kong
        movs r2, # 1
        bl _lcdxianshi
__xian_shi_shang_bi_shi_bu:
	mov r0, r4
	movs r1, # 5
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0x81
	ldr r1, = asciimabiao
	movs r2, # 5
	bl _lcdxianshi
@显示上臂虚部
        mov r4, r11
	movs r4, r4
        bpl __shang_bi_xu_bu_zheng
        movs r0, # 0xc0
        ldr r1, = _fu
        movs r2, # 1
        bl _lcdxianshi
        mvns r4, r4
        adds r4, r4, # 1
        b __xian_shi_shang_bi_xu_bu
__shang_bi_xu_bu_zheng:
        movs r0, # 0xc0
	ldr r1, = kong
        movs r2, # 1
        bl _lcdxianshi
__xian_shi_shang_bi_xu_bu:
        mov r0, r4
        movs r1, # 5
        ldr r2, = asciimabiao
        movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0xc1
        ldr r1, = asciimabiao
        movs r2, # 5
	bl _lcdxianshi
@显示下臂实部：
        mov r4, r8
	movs r4, r4
        bpl __xia_bi_shi_bu_zheng
        movs r0, # 0x8a
        ldr r1, = _fu
        movs r2, # 1
        bl _lcdxianshi
        mvns r4, r4
	adds r4, r4, # 1
	b __xian_shi_xia_bi_shi_bu
__xia_bi_shi_bu_zheng:
        movs r0, # 0x8a
        ldr r1, = kong
        movs r2, # 1
	bl _lcdxianshi
__xian_shi_xia_bi_shi_bu:
	mov r0, r4
	movs r1, # 5
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
        movs r0, # 0x8b
        ldr r1, = asciimabiao
        movs r2, # 5
        bl _lcdxianshi

@显示下臂虚部
	mov r4, r10
	movs r4, r4
        bpl __xia_bi_xu_bu_zheng
        movs r0, # 0xca
        ldr r1, = _fu
        movs r2, # 1
        bl _lcdxianshi
        mvns r4, r4
        adds r4, r4, # 1
        b __xian_shi_xia_bi_xu_bu
__xia_bi_xu_bu_zheng:
        movs r0, # 0xca
        ldr r1, = kong
        movs r2, # 1
        bl _lcdxianshi
__xian_shi_xia_bi_xu_bu:
        mov r0, r4
        movs r1, # 5
        ldr r2, = asciimabiao
        movs r3, # 0xff
        bl _zhuanascii
        movs r0, # 0xcb
        ldr r1, = asciimabiao
        movs r2, # 5
        bl _lcdxianshi
	pop {r0-r7,pc}


__zhen_fu_lv_bo:
	@ 入口 R0= 下臂实部，R1=上臂实部，R2=下臂虚部，R3=上臂虚部
	push {r0-r7,lr}
	ldr r7, = xia_bi_shi_bu
	mov r5, r2
	mov r6, r3
	mov r4, r1
	mov r3, r0
	ldr r0, = lvboqihuanchong
	ldr r1, = 32
	ldr r2, = lvboqizhizhen
	bl _lvboqi
	str r0, [r7]			@保存下臂实部
        mov r3, r4
        ldr r0, = lvboqihuanchong1
	ldr r1, = 32
	ldr r2, = lvboqizhizhen1
        bl _lvboqi
        str r0, [r7, # 0x04]		@保存上臂实部
	mov r3, r5
	ldr r0, = lvboqihuanchong2
        ldr r1, = 32
        ldr r2, = lvboqizhizhen2
	bl _lvboqi
	str r0, [r7, # 0x08]		@保存下臂虚部

        mov r3, r6
	ldr r0, = lvboqihuanchong3
	ldr r1, = 32
	ldr r2, = lvboqizhizhen3
        bl _lvboqi
	str r0, [r7, # 0x0c]		@保存上臂虚部
	pop {r0-r7,pc}

	.ltorg
__jianbo:
	@入口R0=0（上臂）1（下臂）
	@出口R0=实部 R1=虚部
	push {r2-r7,lr}
	ldr r4, = 0x48000000
	ldr r5, = 0x200
	ldr r6, = 0x40012428
	cmp r0, # 0
	bne __xia_bi_kai
	str r5, [r4, # 0x18]	@上臂开
        movs r4, # 1
        str r4, [r6]            @ 反相通道开
        bl _jianboyanshi
        ldr r0, = dianyabiao
        ldr r1, = fanxiangbiao
        movs r2, # 100
        bl __fu_zhi_nei_cun
        movs r4, # 2
        str r4, [r6]            @ 正相通道开
	bl _jianboyanshi
        ldr r0, = dianyabiao
        ldr r1, = zhengxiangbiao
        movs r2, # 100
        bl __fu_zhi_nei_cun
        ldr r1, = zhengxiangbiao
        ldr r0, = fanxiangbiao
	bl __DFT_ji_suan
        pop {r2-r7,pc}
__xia_bi_kai:
	str r5, [r4, # 0x28]	@ 下臂开
	movs r4, # 1
	str r4, [r6]		@ 反相通道开
	bl _jianboyanshi
	ldr r0, = dianyabiao
	ldr r1, = fanxiangbiao
	movs r2, # 100
	bl __fu_zhi_nei_cun
	movs r4, # 2
	str r4, [r6]		@ 正相通道开
	bl _jianboyanshi
	ldr r0, = dianyabiao
	ldr r1, = zhengxiangbiao
	movs r2, # 100
	bl __fu_zhi_nei_cun
	ldr r0, = zhengxiangbiao
	ldr r1, = fanxiangbiao
	bl __DFT_ji_suan
	pop {r2-r7,pc}

	
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
_jianbo:
	push {r4-r5,lr}
	ldr r0, = shangbifangda		@上臂放大
	ldr r0, [r0]
	bl __fang_da
	movs r0, # 0		@上臂开
	bl __jianbo		
	push {r0,r1}
	ldr r0, = xiabifangda		@下臂放大
	ldr r0, [r0]
	bl __fang_da
	movs r0, # 1		@下臂开
	bl __jianbo
	pop {r4,r5}	
	movs r3, r5
	movs r2, r1
	movs r6, r4
	movs r1, # 50
	bl __chu_fa
	push {r0}
	mov r0, r2
	bl __chu_fa
	push {r0}
	mov r0, r6
	bl __chu_fa
	push {r0}
	mov r0, r3
	bl __chu_fa
	mov r3, r0
	pop {r1}
	pop {r2}
	pop {r0}
	pop {r4-r5,pc}
_jianboyanshi:
	push {r7,lr}
	ldr r7, = 0xffff
_jianboyanshixunhuan:
	subs r7, r7, # 1
	bne _jianboyanshixunhuan
	pop {r7,pc}	
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
	asrs r0, r7, # 5	@修改
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
	ldr r5, = 0x2000
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
	str r2, [r6, # 0x18]	@ rclk=0
	str r5, [r6, # 0x18]	@ srclk=0
	movs r7, # 0xff
__595_yanshi:
	subs r7, r7, # 1
	bne __595_yanshi
	mov r1, r0
	lsls r1, r1, r4
	bpl __ser_0
__ser_1:
	str r3, [r6, # 0x28]	@ ser=1
	b __595_yiwei
__ser_0:
	str r3, [r6, # 0x18]	@ ser=0
__595_yiwei:
	str r5, [r6, # 0x28]
	movs r7, # 0xff
__595_yanshi1:
	subs r7, r7, # 1
	bne __595_yanshi1
	adds r4, r4, # 1
	cmp r4, # 32
	bne __595_yiweixunhuan
	str r2, [r6, # 0x28]	@ rclk=1
	movs r7, # 0xff
__595_yanshi2:
	subs r7, r7, # 1
	bne __595_yanshi2
	str r2, [r6, # 0x18]	@ rclk = 0
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

__chu_fa_xiao_shu:
	@入口R0=除数，R1=被除数
	@出口R0=整数，R1=小数(5位)
	push {r2-r7,lr}
        cmp r0, # 0
        beq _chufafanhui_1
        cmp r1, # 0
        beq _chufafanhui_1
	movs r5, # 0
	movs r6, # 6
	movs r0, r0
	bpl __pan_duan_bei_chu_shu_1
	adds r5, r5, # 1
	mvns r0, r0
	adds r0, r0, # 1
__pan_duan_bei_chu_shu_1:
	movs r1, r1
	bpl __bao_cun_fu_hao
	adds r5, r5, # 1
	mvns r1, r1
	adds r1, r1, # 1
__bao_cun_fu_hao:
	push {r5}
__ji_suan_chu_fa_11:	
        mov r2, r0
        movs r3, # 1
        lsls r3, r3, # 31
        movs r0, # 0
        mov r4, r0
_chufaxunhuan_1:
        lsls r2, r2, # 1
        adcs r4, r4, r4
        cmp r4, r1
	bcc _chufaweishubudao0_0
	adds r0, r0, r3
	subs r4, r4, r1
_chufaweishubudao0_0:
	lsrs r3, r3, # 1
	bne _chufaxunhuan_1
	push {r0}
	mov r0, r4
	movs r2, # 10
	muls r0, r0, r2
	subs r6, r6, # 1
	bne __ji_suan_chu_fa_11
	pop {r0-r5}
	ldr r7, = 10000
	ldr r6, = 1000
	muls r4, r4, r7
	muls r3, r3, r6
	ldr r7, = 100
	movs r6, # 10
	muls r2, r2, r7
	muls r1, r1, r6
	adds r1, r1, r0
	adds r1, r1, r2
	adds r1, r1, r3
	adds r1, r1, r4
	mov r0, r5
	pop {r5}
	cmp r5, # 1
	bne _chufafanhui_1
	mvns r0, r0
	adds r0, r0, # 1
_chufafanhui_1:
	pop {r2-r7,pc}

__chu_fa:
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
	bne _chufafanhui1
	mvns r0, r0
	adds r0, r0, # 1
_chufafanhui1:
	pop {r1-r7,pc}
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
	.ltorg
	.end
