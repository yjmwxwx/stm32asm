	@@单片机stm32f030f4p6
	@@ 电阻桥
	@作者：yjmwxwx
	@时间：2019-07-20
	@编译器：arm-none-eabi
	 .thumb                 
         .syntax unified
	.section .data
wendubuchangbiao1:
	.int 0x5a1,0x5b1,0x5c9,0x5ff,0x92a,0x9ad,0xa2d,0xa88,0xaa6,0xae8,0xb95,0xbb2,0xbd3,0xc2b,0xc79,0xcb1,0xc05,0xcea,0xcfb
shumaguanmabiao:
	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6
shumaguanshuaxinbiao:
	.int 0xfe00,0xfd00,0xfb00,0xf700,0xef00,0xdf00,0xbf00,0x7f00,0
       	.equ STACKINIT,                 0x20001000
	.equ shumaguanma,		0x20000000
	.equ dianyabiao,		0x20000024
	.equ lvboqizhizhen,		0x2000002c
	.equ lvboqihuanchong,		0x20000030
	.equ lvboqizhizhen1,		0x20000530
	.equ lvboqihuanchong1,		0x20000534
	.equ wendubuchangbiao,		0x20000950
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
	.word aaa +1	@  _systickzhongduan +1               @ 15
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
        ldr r1, = 0x1010000
	movs r0, r0
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

neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne neicunqinglingxunhuan

@_systick:				@ systick定时器初始化
@
@	ldr r0, = 0xe000e010
@	ldr r1, = 0xffff
@	str r1, [r0, # 4]
@	str r1, [r0, # 8]
@	movs r1, # 0x07
@	str r1, [r0]
_waisheshizhong:		 @ 外设时钟
	@ +0x14=RCC_AHBENR
	@ 0=DMA @ 2=SRAM @ 4=FLITF@ 6=CRC @ 17=PA @ 18=PB @ 19=PC @ 20=PD @ 22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x460005
	str r1, [r0, # 0x14]

	@ +0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@ 0=SYSCFG @ 5=USART6EN @ 9=ADC @ 11=TIM1 @ 12=SPI1 @ 14=USART1 @ 16=TIM15 @ 17=TIM16 @ 18=TIM17 @ 22=DBGMCU
	ldr r1, = 0xa00
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@ 1=TIM3 @ 4=TIM6 @5=TIM7 @8=TIM14 @11=WWDG @14=SPI @17=USRT2 @18=USART3 @20=USART5 @21=I2C1 @22=I2C2 @23=USB @28=PWR
	movs r1, # 0x02
	str r1, [r0, # 0x1c]
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
	ldr r1, = 0x2800540f
	str r1, [r0]

	ldr r1, = 0x200
	str r1, [r0, # 0x24]
tim3chushihua:				@ 48M
	ldr r0, = 0x40000400 @ tim3_cr1
	ldr r1, =  0
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 6
	str r1, [r0, # 0x2c] @ ARR
	ldr r1, =   0x3800
	str r1, [r0, # 0x1c] @ ccmr2
	ldr r1, = 9999
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 6
	str r1, [r0, # 0x40] @ ccr4
	movs r1, # 0x70
	str r1, [r0, # 0x04]
	movs r1, # 0x81
	str r1, [r0]
dmachushihua:
	@+0=LSR,+4=IFCR,
	@+8=CCR1,+c=CNDTR1,+10=CPAR1+14=CMAR1,
	@+1c=CCR2,+20=CNDTR2,+24=CPAR2,+28=CMAR2
	@+30=CCR3,+34=CNDTR3,+38=CPAR2,+3c=CMAR3
	@+44=CCR4,+48=CNDTR4,+4c=CPAR4,+50=CMAR4
	@+58=CCR5,+5c=CNDTR5,+60=CPAR5,+64=CMAR5
	@+6C=CCR6,+70=CNDTR6,+74=CPAR6,+78=CMAR6
	@+80=CCR7,+84=CNDTR7,+88=CPAR7,+8c=CMAR7
	@ tim1DMA
	@ adc dma
	ldr r0, = 0x40020000
	ldr r1, = 0x40012440
	str r1, [r0, # 0x10]
	ldr r1, = dianyabiao
	str r1, [r0, # 0x14]
	ldr r1, =  2
	str r1, [r0, # 0x0c]
	ldr r1, = 0xaa1
	str r1, [r0, # 0x08]

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
	ldr r1, = 0x03
	str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
	ldr r1, = 0xcc3         @ tim3触发ADC
@	ldr r1, = 0x3001
	str r1, [r0, # 0x0c]    @ 配置寄存器 1 (ADC_CFGR1)
	movs r1, # 0       
	str r1, [r0, # 0x14]    @ ADC 采样时间寄存器 (ADC_SMPR)
	ldr r1, [r0, # 0x08]
	ldr r2, = 0x04         @ 开始转换
	orrs r1, r1, r2
	str r1, [r0, # 0x08]    @ 控制寄存器 (ADC_CR)


	
_waishezhongduan:		@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效

	ldr r6, = 512
denglvboqiman:
        ldr r0, = lvboqihuanchong1
        ldr r1, = 512
        ldr r3, = dianyabiao
        adds r3, r3, # 4
        ldr r2, = lvboqizhizhen1
        ldr r3, [r3]
        bl _lvboqi1
	
        ldr r0, = lvboqihuanchong
        ldr r1, = 512
        ldr r3, = dianyabiao
        ldr r2, = lvboqizhizhen
        ldr r3, [r3]
        bl _lvboqi
	subs r6, r6, # 1
	bne denglvboqiman

	
ting:
        ldr r0, = lvboqihuanchong1
        ldr r1, = 512
        ldr r3, = dianyabiao
	adds r3, r3, # 4
        ldr r2, = lvboqizhizhen1
        ldr r3, [r3]
        bl _lvboqi1
	mov r6, r0

	ldr r0, = lvboqihuanchong
	ldr r1, = 512
	ldr r3, = dianyabiao
	ldr r2, = lvboqizhizhen
	ldr r3, [r3]
	bl _lvboqi
	ldr r1, = 3300
	muls r0, r0, r1
	lsrs r0, r0, # 12
	bl __wendubuchang1
	ldr r2, = shumaguanma
	movs r1, # 8
	bl _zhuanshumaguanma
	movs r0, # 8
	bl _xieshumaguan
	b ting
	
__wendubuchang1:
	push {r1-r6,lr}
	ldr r1, = wendubuchangbiao1
	movs r2, # 0
	movs r3, # 15
	lsls r3, r3, # 2
	movs r4, # 4
	lsls r4, r4, # 2
__gaowenbuchang:
	ldr r5, [r1, r2]
	cmp r5, r6
	bcs __gaowenbuchangfanhui
	adds r2, r2, # 4
	cmp r2, r3
	bne __diwenbuchang
__diwenbuchang:
	ldrh r5, [r1, r2]
	cmp r5, r6
	bcs __diwenbuchangfanhui
	adds r2, r2, # 4
	cmp r2, r3
	bne __diwenbuchang
	pop {r1-r6,pc}
__gaowenbuchangfanhui:
	lsrs r2, r2, # 2
	add r0, r0, r2
	pop {r1-r6,pc}
__diwenbuchangfanhui:
	lsrs  r2, r2, # 2
	subs r0, r0, r2
	pop {r1-r6,pc}
	
	
	




	
__wendubuchang:
	push {r1-r7,lr}
	ldr r1, = wendubuchangbiao
	ldr r3, = dianyabiao
	ldr r6, [r1]
	ldrh r4, [r1, r6]
@	ldrh r5, [r3, # 0x04]
	cmp r4, r0
	bcs __buchangfanhui
	mov r7, r6
	adds r7, r7, # 4
	strh r0, [r1, r7]
	adds r7, r7, # 2
	strh r5, [r1, r7]
	adds r6, r6, # 4
	str r6, [r1]
__buchangfanhui:
	pop {r1-r7,pc}
	
	
	
_zhuanshumaguanma:@ 16进制转数码管码
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
_xieshumaguan: @ r0=位数 @数码管码
	push {r0-r7,lr}
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
	push {r7}
	ldr r7, = 30
_yanshi11:
	subs r7, # 1
	bne _yanshi11
	pop {r7}
	bx lr
_chufa:			@软件除法
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


_lvboqi:
			@滤波器
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
	asrs r0, r7, # 9	@修改
	pop {r1-r7,pc}

_lvboqi1:
                        @滤波器
                        @R0=地址，R1=长度,r2=表指针地址,r3=ADC数值
                        @出R0=结果
	push {r1-r7,lr}
	ldr r5, [r2]            @读出表指针
        lsls r6, r1, # 1
        strh r3, [r0, r5]       @数值写到滤波器缓冲区
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
        asrs r0, r7, # 8       @修改
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
aaa:
	bx lr
