		@ stm32f030f4p6 asm
	 .thumb
	         .syntax unified
.section .data
zhengxian1k:
	.short 0x32,0x35,0x39,0x3c,0x3f,0x42,0x45,0x48,0x4b,0x4e,0x50,0x53,0x55,0x58,0x5a,0x5c,0x5d,0x5f,0x60,0x61,0x62,0x63,0x64,0x64,0x64,0x64,0x64,0x63,0x62,0x61,0x60,0x5f,0x5d,0x5c,0x5a,0x58,0x55,0x53,0x50,0x4e,0x4b,0x48,0x45,0x42,0x3f,0x3c,0x39,0x35,0x32,0x2f,0x2b,0x28,0x25,0x22,0x1f,0x1c,0x19,0x16,0x14,0x11,0xf,0xc,0xa,0x8,0x7,0x5,0x4,0x3,0x2,0x1,0x0,0x0,0x0,0x0,0x0,0x1,0x2,0x3,0x4,0x5,0x7,0x8,0xa,0xc,0xf,0x11,0x14,0x16,0x19,0x1c,0x1f,0x22,0x25,0x28,0x2b,0x2f,0x32
qingping:
	.ascii "                "
fute:
	.ascii "V"
fute1:
	.ascii	"V="
lcdshuju:
	.ascii  "yjmwxwx-20180225"
dianhua:	
	.ascii	"      15552208295"
qq:
	.ascii	"   QQ:3341656346"
	.equ STACKINIT,                 0x20001000
	.equ asciimabiao,       0x20000000
	.equ dianyabiao,	0x20000010
	.equ pingjundianya,	0x20000410
	.equ jishu,		0x20000414
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
dmachushihua:
	@+0=LSR,+4=IFCR,
	@+8=CCR1,+c=CNDTR1,+10=CPAR1+14=CMAR1,
	@+1c=CCR2,+20=CNDTR2,+24=CPAR2,+28=CMAR2
	@+30=CCR3,+34=CNDTR3,+38=CPAR2,+3c=CMAR3
	@+44=CCR4,+48=CNDTR4,+4c=CPAR4,+50=CMAR4
	@+58=CCR5,+5c=CNDTR5,+60=CPAR5,+64=CMAR5
	@+6C=CCR6,+70=CNDTR6,+74=CPAR6,+78=CMAR6
	@+80=CCR7,+84=CNDTR7,+88=CPAR7,+8c=CMAR7

	@ adc dma
	ldr r0, = 0x40020000
	ldr r1, = 0x40012440
	str r1, [r0, # 0x10]
	ldr r1, = dianyabiao
	str r1, [r0, # 0x14]
	ldr r1, =  0xff
	str r1, [r0, # 0x0c]
	ldr r1, = 0xaa1
	str r1, [r0, # 0x08]

	@tim1ch3DMA
	ldr r0, = 0x40020000
	ldr r1, = 0x40012c3c @ 外设地址
	str r1, [r0, # 0x60]
	ldr r1, = zhengxian1k @ 储存器地址
	str r1, [r0, # 0x64]
	ldr r1, = 96             @点数
	str r1, [r0, # 0x5c]
	ldr r1, = 0x25b1         @ 储存到外设
	str r1, [r0, # 0x58]
tim1chushiha:
	ldr r0, = 0x40012c00 @ tim1_cr1
	movs r1, # 0
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 100
	str r1, [r0, # 0x2c] @ ARR
	ldr r1, = 0x68
	str r1, [r0, # 0x1c] @ ccmr2  CC3
	ldr r1, = 0x100    @  CC3
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 0x8000
	str r1, [r0, # 0x44] @ BDTR
	ldr r1, = 0x800 @ CC3 DMA
	str r1, [r0, # 0x0c] @ DIER
	ldr r1, = 0xe1
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
	ldr r1, = 0x01
	str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
	ldr r1, = 0x3003        @ 13 连续转换
	str r1, [r0, # 0x0c]    @ 配置寄存器 1 (ADC_CFGR1)
	movs r1, # 0x07         @
	str r1, [r0, # 0x14]    @ ADC 采样时间寄存器 (ADC_SMPR)
	ldr r1, [r0, # 0x08]
	ldr r2, = 0x04         @ 开始转换
	orrs r1, r1, r2
	str r1, [r0, # 0x08]    @ 控制寄存器 (ADC_CR)



_waishezhongduan:			@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效

	
_systick:				@ systick定时器初始化

	ldr r0, = 0xe000e010
	ldr r1, = 0xffffff
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	movs r1, # 0x07
	str r1, [r0]

	
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
	ldr r1, = 0x28205553
	str r1, [r0]

	ldr r1, = 0x200
	str r1, [r0, # 0x24]

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
	ldr r0, = jishu
	ldr r1, [r0]
	cmp r1, # 10
	beq _lcddi1
	cmp r1, # 20
	beq _lcddi2
	cmp r1, # 30
	beq _lcddi3
	b _tiaoguolcdxunhuan
_lcddi1:
	movs r0, # 0x80
	ldr r1, = lcdshuju
	movs r2, # 16
	movs r3, # 0xff
	bl _lcdxianshi
	b _tiaoguolcdxunhuan
_lcddi2:
	movs r0, # 0x80
	ldr r1, = dianhua
	movs r2, # 16
	movs r3, # 0xff
	bl _lcdxianshi
	b _tiaoguolcdxunhuan
_lcddi3:
	
	movs r0, # 0x80
	ldr r1, = qq
	movs r2, # 16
	movs r3, # 0xff
	bl _lcdxianshi
	ldr r0, = jishu
	movs r1, # 0
	str r1, [r0]
_tiaoguolcdxunhuan:
	
	



	

_adcpingjun:
	ldr r0, = dianyabiao
	ldr r1, = 0x3fc
	movs r2, # 0
	mov r3, r2
	mov r4, r3
	mov r5, r4
_adcpingjunxunhuan:
	ldr r2, [r0, r3]
	cmp r2, # 0
	bne _leijia
	adds r5, r5, # 1
	b _tiaoguoleijia
_leijia:	
	adds r4, r4, r2
_tiaoguoleijia:	
	adds r3, r3, # 4
	cmp r3, r1
	bne _adcpingjunxunhuan
	movs r3, # 0xff
	subs r3, r3, r5
	mov r1, r3
	mov r0, r4
	bl _chufa
	
	ldr r1, = 3300
	muls r0, r0, r1
	ldr r1, = pingjundianya
	lsrs r0, r0, # 13		@求电压
	str r0, [r1]

	
	movs r0, # 0xc0
	ldr r1, = fute1
	movs r2, # 2
	bl _lcdxianshi

	ldr r3, = pingjundianya
	movs r1, # 5
	ldr r0, [r3]
	ldr r2, = asciimabiao
	movs r3, # 1
	bl _zhuanascii

	movs r0, # 0xc3
	ldr r1, = asciimabiao
	movs r2, # 5
	bl _lcdxianshi

	movs r0, # 0xc8
	ldr r1, = fute
	ldr r2, = 1
	movs r3, # 0xff
	bl _lcdxianshi
	
	b tingting

_lcdxianshi:  		@r0=LCD位置，r1=数据地址，r2=长度
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
	
_xielcd:		@入R0=8位,r1=0命令,r1=1数据
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
	.ltorg


_zhuanascii:				@ 16进制转数码管码
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
