	@@单片机stm32f030f4p6
	@@ adc fft
	@作者：yjmwxwx
	@时间：2019-06-19
	@编译器：arm-none-eabi
	 .thumb                 
         .syntax unified
.section .data
shumaguanmabiao:
	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6
shumaguanshuaxinbiao:
	.int 0xfe00,0xfd00,0xfb00,0xf700,0xef00,0xdf00,0xbf00,0x7f00,0
       	.equ STACKINIT,                 0x20001000

	.equ shumaguanma,	0x20000804
	.equ xuanzhuanyinzi,	0x20000800
	.equ dianyabiao,	0x20000850
	.equ lvbozhizhen,	0x20000c50
	.equ lvbohuanchong,	0x20000c54
hudieweifanzhuan:
	.int 0,64,32,96,16,80,48,112,8,72,40,104,24,88,56,120
	.int 4,68,36,100,20,84,52,116,12,76,44,108,28,92,60,124
fft3xuanzhuanyinzi:
	.int 0x8000,0x0000,0x5A82,0xFFFFA57E,0x0000,0xFFFF8000,0xFFFFA57E,0xFFFFA57E
fft4xuanzhuanyinzi:
	.int 0x8000,0x0000,0x7641,0xFFFFCF05,0x5A82,0xFFFFA57E,0x30FB,0xFFFF89BF,0x0000,0xFFFF8000,0xFFFFCF05,0xFFFF89BF,0xFFFFA57E,0xFFFFA57E,0xFFFF89BF,0xFFFFCF05
fft5xuanzhuanyinzi:
	.int	0x8000,0x0000,0x7D8A,0xFFFFE708,0x7641,0xFFFFCF05,0x6A6D,0xFFFFB8E4,0x5A82,0xFFFFA57E,0x471C,0xFFFF9593,0x30FB,0xFFFF89BF,0x18F8,0xFFFF8276,0x0000,0xFFFF8000,0xFFFFE708,0xFFFF8276,0xFFFFCF05,0xFFFF89BF,0xFFFFB8E4,0xFFFF9593,0xFFFFA57E,0xFFFFA57E,0xFFFF9593,0xFFFFB8E4,0xFFFF89BF,0xFFFFCF05,0xFFFF8276,0xFFFFE708

	
		
	
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
	.word 0 @_systick +1               @ 15   
	.word 0     @ _wwdg +1          @ 0
	.word 0     @_pvd +1            @ 1
	.word 0     @_rtc +1            @ 2
	.word 0     @_flash +1          @ 3
	.word 0     @ _rcc + 1          @ 4
	.word 0      @_exti0_1  +1      @ 5
	.word 0      @ _exti2_3 +1      @ 6
	.word 0       @_exti4_15 +1     @ 7
	.word 0                         @ 8
	.word 0 	@_dma1_1  +1    @ 9
	.word 0    @_dma1_2_3 +1        @ 10
	.word 0       @_dma1_4_5 +1     @ 11
	.word 0 	@_adc1 +1          @ 12
	.word 0       @_tim1_brk_up +1  @ 13
	.word 0        @ _tim1_cc +1    @ 14
	.word 0         @_tim2 +1       @ 15
	.word 0          @_tim3 +1      @ 16
	.word 0                         @ 17
	.word 0		                @ 18
	.word 0		@_tim14 +1    @ 19
	.word 0                         @ 20
	.word 0         @_tim16 +1      @ 21
	.word 0         @_tim17 +1      @ 22
	.word 0          @_i2c   +1     @ 23
	.word 0                         @ 24
	.word 0           @_spi   +1    @ 25
	.word 0                         @ 26
	.word 0         @_usart1 +1     @ 27
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

_waisheshizhong:		 @ 外设时钟
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
	ldr r1, = 0x28005403
	str r1, [r0]

	ldr r1, = 0x200
	str r1, [r0, # 0x24]
tim3chushihua:				@ 24M
	ldr r0, = 0x40000400 @ tim3_cr1
	ldr r1, =  0
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 952
	str r1, [r0, # 0x2c] @ ARR
	ldr r1, =   0x3800
	str r1, [r0, # 0x1c] @ ccmr2
	ldr r1, =  0x1000
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 952
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
	ldr r1, =  0xff
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
	ldr r1, = 0x01
	str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
	ldr r1, = 0xcC3         @ tim3触发ADC
	str r1, [r0, # 0x0c]    @ 配置寄存器 1 (ADC_CFGR1)
	movs r1, # 0x01        
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



	
ting:
	ldr r0, = dianyabiao
	bl _fftjisuan
	ldr r0, = 0x20000000
	ldr r3, [r0]
	ldr r0, = lvbohuanchong
	ldr r1, = 16
	ldr r2, = lvbozhizhen
	bl _lvboqi
	mov r12, r0
	ldr r2, = shumaguanma
	movs r1, # 8
	bl _zhuanshumaguanma
	movs r0, # 8
	bl _xieshumaguan
	ldr r5, = 0xff
yanshi11:
	mov r0, r12
        ldr r2, = shumaguanma
        movs r1, # 8
        bl _zhuanshumaguanma
        movs r0, # 8
        bl _xieshumaguan

	subs r5, r5, # 1
	bne yanshi11
	bkpt # 1
neicunqingling1:
        ldr r0, = 0x20000000
        movs r1, # 0
        ldr r3, = 0x850
neicunqinglingxunhuan1:
        subs r3, # 4
        str r1, [r0, r3]
        bne neicunqinglingxunhuan1

	b ting
	

	

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
	asrs r0, r7, # 4	@修改
	pop {r1-r7,pc}
	
_maopaopaixu:
	push {r0-r7,lr}
	@ r0= 表地址, r1= 长度
	mov r7, r1
_paixu:
	lsls r1, r7, # 2
_paixuxunhuan:	
	ldrh r2, [r0, r1]
	subs r1, r1, # 2
	bmi _paixu1
	ldrh r4, [r0, r1]
	cmp r2, r4
	bls _paixuxunhuan
	strh r2, [r0, r1]
	adds r3, r1, # 2
	strh r4, [r0, r3]
	b _paixuxunhuan
_paixu1:
	adds r0, r0, # 2
	subs r7, r7, # 1
	bne _paixu
	pop {r0-r7,pc}

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
	.ltorg


_fftjisuan:
				@R0=输入地址
				@输出实部=0X20000000-0X20000400
				@输出虚部=0X20000400-0X20000800
	push {lr}
_fft1:
	ldr r1, = 0x20000000       @输出地址
	movs r2, # 16             @蝴蝶数量
	ldr r3, = hudieweifanzhuan @蝴蝶位反转表
_fft1xunhuan:
	ldr r6, [r3]               @取出位反转表里的地一个数据
	ldr r7, [r3, # 0x04]       @取出第二个
	ldr r6, [r0, r6]           @给据位反转表找到对应的输入数据  
	ldr r7, [r0, r7]           @第二个
	adds r4, r6, r7            @求出蝴蝶上
	subs r5, r6, r7            @求出蝴蝶下
	asrs r4, r4, # 1           @数据缩小一位防后面溢出
	asrs r5, r5, # 1           @数据缩小一位
	str r4, [r1]
	str r5, [r1, # 0x04]       @把反过来的顺序排列
	adds r1, r1, # 0x08        @输出的地址自增
	adds r3, r3, # 0x08        @反转表自增
	subs r2, r2, # 1           @蝴蝶数减1
	bne _fft1xunhuan           @蝴蝶数不到

_fft2:
	ldr r0, = 0x20000000       @实部输出地址
	movs r4, # 1               
	lsls r4, r4, # 10          
	adds r4, r4, r0            @虚部输出地址
	mov r8, r4                 @实部和虚部中间
_fft2xunhuan:
	ldr r4, [r0]               @取出数据0
	ldr r5, [r0, # 0x08]       @取出数据2
	ldr r6, [r0, # 0x04]       @取出数据1
	ldr r7, [r0, # 0x0c]       @取出数据3
	adds r1, r4, r5            @计算蝴蝶上
	subs r2, r4, r5            @计算蝴蝶下
	mov r3, r6		@0r 蝴蝶上实部
	movs r4, # 0
	subs r4, r4, r7		@0i 蝴蝶上虚部
	mov r5, r6		@3r 蝴蝶下实部
	mov r6, r7		@3i 蝴蝶下虚部
	movs r7, # 1
	lsls r7, r7, # 10       @内存实部和虚部中间
	adds r7, r7, r0         @R7等于虚部首地址  
	str r1, [r0]            @蝴蝶上保存实部
	str r2, [r0, # 0x08]    @蝴蝶下实部
	str r3, [r0, # 0x04]    @第二组蝴蝶上实部
	str r4, [r7, # 0x04]    @第二组蝴蝶上虚部
	str r5, [r0, # 0x0c]	@第二组蝴蝶下实部
	str r6, [r7, # 0x0c]    @第二组下虚部
	adds r0, r0, # 0x10     @蝴蝶组自增
	cmp r0, r8     
	bne _fft2xunhuan        @地址不到循环
_fft3:
	ldr r6, = xuanzhuanyinzi       @旋转因子自增变量
	ldr r2, = fft3xuanzhuanyinzi   @旋转因子第三部的表
	ldr r0, = 0x20000000           @实部输出地址
	str r2, [r6]                   @旋转因子表首地址写到变量
	movs r1, # 1
	lsls r1, r1, # 10             
	adds r1, r1, r0                @虚部输出地址
	mov r8, r1		       @R8虚部地址自增变量
	mov r9, r0                     @R9实部地址自增变量
	mov r10, r2		       @旋转因子地址写到R10
	movs r5, # 0x10		       @两组蝴蝶的距离	
	mov r11, r5                    @写到R11
	movs r5, # 4                   @旋转因子数量
	mov r12, r5		       @旋转因子数量写到R12
	bl _fftg
_fft4:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft4xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, # 1
	lsls r1, r1, # 10
	adds r1, r1, r0
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x20
	mov r11, r5
	movs r5, # 8
	mov r12, r5
	bl _fftg
_fft5:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft5xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, # 1
	lsls r1, r1, # 10
	adds r1, r1, r0
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x40
	mov r11, r5
	movs r5, # 16
	mov r12, r5
	bl _fftg


_fftjisuanfuzhi:
	ldr r0, = 0x20000000
	ldr r1, = 0x20000400
	mov r8, r1
_jisuanfuzhixunhuan:
	ldr r2, [r0]
	ldr r3, [r1]
	movs r3, r3
	bpl _fzbushifushu1
	mvns r3, r3
	adds r3, r3, # 1
_fzbushifushu1:
	asrs r2, r2, # 1
	bpl _fzbushifushu
	mvns r2, r2
	adds r2, r2, # 1
_fzbushifushu:
	adds r3, r3, r2
	lsls r3, r3, # 1
	str r3, [r0, r4]
	adds r0, r0, # 4
	adds r1, r1, # 4
	cmp r0, r8
	bne _jisuanfuzhixunhuan
	pop {pc}
_fftg:
	push {lr}
	movs r4, # 0
	mov lr, r4
_fftxunhuan:
	mov r0, r9
	mov r1, r8
	mov r2, r10
	mov r3, r11
	ldr r4, [r0]
	ldr r5, [r1]
	ldr r6, [r0, r3]
	ldr r7, [r1, r3]
	ldr r3, [r2]		@sr
	ldr r2, [r2, # 0x04]	@si
	push {r4,r5}
	mov r4, r6
	muls r4, r4, r3
	mov r5, r7
	muls r5, r5, r2
	subs r4, r4, r5		@r
	asrs r4, r4, # 15
	mov r5, r6
	muls r5, r5, r2
	muls r7, r7, r3
	adds r7, r7, r5    @i
	asrs r7, r7, # 15
	pop {r2,r5}
	adds r3, r2, r4    @0r
	subs r2, r2, r4    @1r
	adds r4, r5, r7
	subs r5, r5, r7
	mov r6, r11
	str r3, [r0]
	str r4, [r1]
	str r2, [r0, r6]
	str r5, [r1, r6]
	adds r0, r0, # 0x04
	adds r1, r1, # 0x04
	mov r9, r0
	mov r8, r1
	mov r2, r10
	adds r2, r2, # 0x08
	mov r10, r2
	mov r4, lr		@取出旋转因子自增变量
	adds r4, r4, # 1        @自增
	mov lr, r4              @保存回去
	mov r7, r12             @取出旋转因子总数量
	cmp r4, r7              @到没到数量
	bne _fftxunhuan         @没到继续循环
	movs  r4, # 0
	ldr r6, = xuanzhuanyinzi
	ldr r5, = 0x20000400
	ldr r6, [r6]
	mov r10, r6
	mov lr, r4
	mov r7, r11
	adds r0, r0, r7
	adds r1, r1, r7
	mov r9, r0
	mov r8, r1
	cmp r0, r5
	bne _fftxunhuan
	pop {pc}
	

	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
