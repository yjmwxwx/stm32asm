		@ stm32f030f4p6 asm
	 .thumb
	         .syntax unified
	.section .data
zhuansulianbiao:				@1000到16000转，每150转一个点
	.int 1000,1150,1300,1450,1600,1750,1900,2050,2200,2350,2500,2650,2800,2950,3100,3250,3400,3550,3700,3850,4000,4150,4300,4450,4600,4750,4900,5050,5200,5350,5500,5650,5800,5950,6100,6250,6400,6550,6700,6850,7000,7150,7300,7450,7600,7750,7900,8050,8200,8350,8500,8650,8800,8950,9100,9250,9400,9550,9700,9850,10000,10150,10300,10450,10600,10750,10900,11050,11200,11350,11500,11650,11800,11950,12100,12250,12400,12550,12700,12850,13000,13150,13300,13450,13600,13750,13900,14050,14200,14350,14500,14650,14800,14950,15100,15250,15400,15550,15700,15850,16000,0xffff
dianhuotiqianjiaobiao:			@点火提前角表
	.int 0,512,1024,1536,2048,2560,3072,3584,4096,4608,5120,5632,6144,6656,7168,7680,8192,8704,9216,9728,10240,10752,11264,11776,12288,12800,13312,13824,14336,14848,15360,15872,16384,16896,17408,17920,18432,18944,19456,19968,20480,20992,21504,22016,22528,23040,23552,24064,24576,25088,25600,26112,26624,27136,27648,28160,28672,29184,29696,30208,30720,31232,31744,32256,32768,33280,33792,34304,34816,35328,35840,36352,36864,37376,37888,38400,38912,39424,39936,40448,40960,41472,41984,42496,43008,43520,44032,44544,45056,45568,46080,46592,47104,47616,48128,48640,49152,49664,50176,50688,51200

lcdshuju:
	.ascii  "yjmwxwx-20180317"
dianhua:	
	.ascii	"      15552208295"
qq:
	.ascii	"   QQ:3341656346"
	.equ STACKINIT,        	        0x20001000
	.equ asciimabiao,		0x20000000
	.equ quanshu,			0x20000010
	.equ zhuansu,			0x20000014
	.equ meizhuanshijian,		0x20000018
	.equ diyicibudianhuo,		0x2000001c
	.equ dianhuotiqianjiao,		0x20000020
	.equ tqjbzhizhen,		0x20000024	@提前角表指针
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
	.word aaa +1	@ _systickzhongduan +1               @ 15
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
	.word _tim1_buhuo +1    @ 14
	.word aaa +1         @_tim2 +1       @ 15
	.word aaa +1          @_tim3 +1      @ 16
	.word aaa +1                         @ 17
	.word aaa +1		                @ 18
	.word aaa +1		@_tim14 +1    @ 19
	.word aaa +1                         @ 20
	.word _tim16 +1      @ 21
	.word aaa +1         @_tim17 +1      @ 22
	.word aaa +1          @_i2c   +1     @ 23
	.word aaa +1                         @ 24
	.word aaa +1           @_spi   +1    @ 25
	.word aaa +1                         @ 26
	.word aaa +1         @_usart1 +1     @ 27
_start:
neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne neicunqinglingxunhuan

_waisheshizhong:			 @ 外设时钟
	@+0x14=RCC_AHBENR
	@0=DMA @2=SRAM @4=FLITF@6=CRC @17=PA @18=PB @19=PC @20=PD @22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x460005
	str r1, [r0, # 0x14]


	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
	ldr r1, = 0x20801
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@1=TIM3 @4=TIM6 @5=TIM7 @8=TIM14 @11=WWDG @14=SPI @17=USRT2 @18=USART3 @20=USART5 @21=I2C1
	@22=I2C2 @23=USB @28=PWR
	ldr r1, = 0x102
	str r1, [r0, # 0x1c]
	
_tim1chushihua:				@8M
	ldr r0, = 0x40012c00
	ldr r1, = 79
	str r1, [r0, # 0x28]	@psc
	ldr r1, = 0xffff
	str r1, [r0, # 0x2c]	@arr
	ldr r1, = 0x100
	str r1, [r0, # 0x18]	@ccmr1
	movs r1, # 0x10
	str r1, [r0, # 0x20]	@ccer
	movs r1, # 0x04
	str r1, [r0, # 0x0c]
	movs r1, # 0x01
	str r1, [r0]
_tim3chushiha:				@8M
	ldr r0, = 0x40000400 @ tim3_cr1
	ldr r1, = 79
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 500
	str r1, [r0, # 0x2c] @ ARR
	ldr r1, = 0x6800
	str r1, [r0, # 0x1c] @ ccmr2
	ldr r1, = 0x1000
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 20
	str r1, [r0, # 0x40]
	movs r1, # 0x99
	str r1, [r0]

_tim16chushihua:		@8M
	ldr r0, = 0x40014400
	ldr r1, = 79
	str r1, [r0, # 0x28]
	ldr r1, = 0xffff
	str r1, [r0, # 0x2c]
	movs r1, # 0X01
	str r1, [r0, # 0x0c]
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
	ldr r1, = 0x28085550
	str r1, [r0]
	movs r1, # 0xfc  @ pa2-pa7开漏输出
	str r1, [r0, # 0x04]
	ldr r1, = 0x20
	str r1, [r0, # 0x24]
	
	ldr r0, = 0x48000400
	movs r1, # 0x08 @ pb1
	str r1, [r0]
	movs r1, # 0x10  @ tim3_4到PB1
	str r1, [r0, # 0x20] @ ARRL
	
_waishezhongduan:	
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效
	ldr r0, = 0xe000e100
	ldr r1, = 0x204000	@14号 19
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

tingting:

	ldr r3, = meizhuanshijian					
        ldr r0, [r3]
        movs r1, # 6
        ldr r2, = asciimabiao
        movs r3, # 0xff
        bl _zhuanascii

        movs r0, # 0x80
        ldr r1, = asciimabiao
        movs r2, # 6
        bl _lcdxianshi

	ldr r1, = tqjbzhizhen
        ldr r0, [r1]
        movs r1, # 6
        ldr r2, = asciimabiao
        movs r3, # 0xff
        bl _zhuanascii

        movs r0, # 0x88
        ldr r1, = asciimabiao
        movs r2, # 6
        bl _lcdxianshi
	
	ldr r3, = dianhuotiqianjiao
	ldr r0, [r3]
	movs r1, # 6
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
	
        movs r0, # 0xc0
        ldr r1, = asciimabiao
        movs r2, # 6
        bl _lcdxianshi

	bl _jisuandianhuotiqianjiao
	
	ldr r1, = zhuansu
	ldr r0, [r1]
        movs r1, # 6
        ldr r2, = asciimabiao
        movs r3, # 0xff
        bl _zhuanascii

        movs r0, # 0xc8
        ldr r1, = asciimabiao
        movs r2, # 6
        bl _lcdxianshi

	
	
        b tingting


_jisuandianhuotiqianjiao:
	push {r0-r5,lr}
	ldr r2, = zhuansu
	ldr r1, = meizhuanshijian
	ldr r0, = 6000000
	ldr r1, [r1]
	mov r5, r1
	bl _chufa
	str r0, [r2]
	ldr r1, = 1000
	cmp r0, r1
	bls _buyongtiqian
	ldr r1, = zhuansulianbiao
	movs r2, # 100
	lsls r2, r2, # 2
	movs r3, # 0
_zhaozhuansuhaoxunhuan:
	ldr r4, [r1, r3]
	cmp r4, r0
	bhi _zhuansudayu
	adds r3, r3, # 4
	cmp r3, r2
	bne _zhaozhuansuhaoxunhuan
	movs r3, # 0
_zhuansudayu:
	ldr r1, = dianhuotiqianjiaobiao
	ldr r2, = dianhuotiqianjiao
	ldr r4, [r1, r3]
	lsls r0, r5, # 8
	ldr r1, = 360
	bl _chufa
	muls r0, r0, r4
	asrs r0, r0, # 16
	str r0, [r2]
	ldr r0, = tqjbzhizhen
	str r3, [r0]
_buyongtiqian:	
	pop {r0-r5,pc}
	
	
	
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
	push {r0-r7,lr}
	lsrs r6, r0, # 4
	lsls r0, r0, # 28
	lsrs r0, r0, # 28
	movs r2, # 0x80		@ RS
	movs r3, # 0x40		@ E
	movs r5, # 0x3c
	ldr r4, = 0x48000000
	cmp r1, # 0
	beq _lcdmingling
	str r2, [r4, # 0x18]	@RS=1
	b _lcdshuju
_lcdmingling:
	str r2, [r4, # 0x28]	@RS=0
_lcdshuju:
	str r3, [r4, # 0x18]	@E=1
	str r5, [r4, # 0x28]

	lsls r7, r6, # 31
	lsrs r7, r7, # 26
	str r7, [r4, # 0x18]

	lsrs r7, r6, # 1
	lsls r7, r7, # 31
	lsrs r7, r7, # 27
	str r7, [r4, # 0x18]

	lsrs r7, r6, # 2
	lsls r7, r7, # 31
	lsrs r7, r7, # 28
	str r7, [r4, # 0x18]

	lsrs r7, r6, # 3
	lsls r7, r7, # 31
	lsrs r7, r7, # 29
	str r7, [r4, # 0x18]

	bl _lcdyanshi
	str r3, [r4, # 0x28]	@E=0


	str r3, [r4, # 0x18]    @E=1
	str r5, [r4, # 0x28]

	lsls r7, r0, # 31
	lsrs r7, r7, # 26
	str r7, [r4, # 0x18]

	lsrs r7, r0, # 1
	lsls r7, r7, # 31
	lsrs r7, r7, # 27
	str r7, [r4, # 0x18]

	lsrs r7, r0, # 2
	lsls r7, r7, # 31
	lsrs r7, r7, # 28
	str r7, [r4, # 0x18]

	lsrs r7, r0, # 3
	lsls r7, r7, # 31
	lsrs r7, r7, # 29
	str r7, [r4, # 0x18]

	bl _lcdyanshi
	str r3, [r4, # 0x28]    @E=0

	pop {r0-r7,pc}


_zhuanascii:					@ 16进制转数码管码
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
	.ltorg

_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
aaa:
	bx lr
_tim16:
	ldr r0, = 0x40000400
	movs r1, # 0x99
	str r1, [r0]
	
	ldr r0, = zhuansu
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	
	ldr r0, = 0x40014400
	movs r1, # 0
	str r1, [r0, # 0x10]
	str r1, [r0, # 0x24]
	str r1, [r0]
	bx lr
_tim1_buhuo:
	push {r4}
	ldr r0, = diyicibudianhuo
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	cmp r1, # 2
	beq _dianhuoshijian
	ldr r0, = 0x40014400
	movs r1, # 0
	str r1, [r0, # 0x2c]
	ldr r0, = 0x40012c10
	str r1, [r0]
	pop {r4}
	bx lr
_dianhuoshijian:
	movs r1, # 1
	str r1, [r0]

	ldr r0, = dianhuotiqianjiao
	ldr r4, = 500
	ldr r1, [r0]
	add r4, r4, r1
	
	cpsid i
	ldr r0, = quanshu
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	movs r3, r1
	ldr r0, = 0x40012c00
	ldr r2, [r0, # 0x38]
	movs r1, # 0
	str r1, [r0, # 0x10]
	str r1, [r0, # 0x24]
	ldr r0, = meizhuanshijian
	str r2, [r0]
	subs r2, r2, r4
	ldr r0, = 0x40014400
	cmp r3, # 1
	bne _bushidiyiquan
	movs r2, # 1
_bushidiyiquan:
	str r2, [r0, # 0x2c]
	ldr r4, = 0xe000e180
        ldr r1, = 0x200000      @
        str r1, [r4]

	movs r1, # 0x81
	str r1, [r0]
	movs r1, # 0
	str r1, [r0, # 0x10]
	ldr r4, = 0xe000e100
        ldr r1, = 0x200000      @
        str r1, [r4]
	cpsie i
	pop {r4}
	bx lr
