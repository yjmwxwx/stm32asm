	 .thumb                 
         .syntax unified
.section .data
	.equ STACKINIT,         0x20005000
	.equ systickms, 	0x20000000
cordicbiao:
	.int 0x00003243, 0x00001DAC, 0x00000FAD, 0x000007F5, 0x000003FE, 0x000001FF, 0x000000FF, 0x0000007F, 0x0000003F, 0x0000001F, 0x0000000F, 0x00000007, 0x00000003, 0x00000001, 0x00000000, 0x0000000

zhengxianbiao:
	.short 0xe10,0xf0b,0x1005,0x10fc,0x11f0,0x12df,0x13c8,0x14aa,0x1584,0x1654,0x171a,0x17d5,0x1883,0x1925,0x19b9,0x1a3e,0x1ab4,0x1b1a,0x1b70,0x1bb5,0x1be9,0x1c0c,0x1c1e,0x1c1e,0x1c0c,0x1be9,0x1bb5,0x1b70,0x1b1a,0x1ab4,0x1a3e,0x19b9,0x1925,0x1883,0x17d5,0x171a,0x1654,0x1584,0x14aa,0x13c8,0x12df,0x11f0,0x10fc,0x1005,0xf0b,0xe10,0xd15,0xc1b,0xb24,0xa30,0x941,0x858,0x776,0x69c,0x5cc,0x506,0x44b,0x39d,0x2fb,0x267,0x1e2,0x16c,0x106,0xb0,0x6b,0x37,0x14,0x2,0x2,0x14,0x37,0x6b,0xb0,0x106,0x16c,0x1e2,0x267,0x2fb,0x39d,0x44b,0x506,0x5cc,0x69c,0x776,0x858,0x941,0xa30,0xb24,0xc1b,0xd15,0xe10
	
.section .text
_xiangliangbiao:
	.word STACKINIT
	.word _start + 1
	.word _nmi_handler + 1
	.word _hard_fault  + 1
	.word _memory_fault + 1
	.word _bus_fault + 1
	.word _usage_fault + 1
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word systickdingshiqi +1
	.word	0 @WWDG  	0
	.word	0 @PVD  	1
	.word	0 @TAMPER	2
	.word	0 @RTC		3
	.word	0 @FLASH	4
	.word	0 @RCC		5
	.word	0 @EXTI0	6
	.word	0 @EXTI1	7
	.word	0 @EXTI2	8
	.word	0 @EXTI3	9
	.word	0 @EXTI4	10
	.word	0 @DMA11	11
	.word	0 @DMA12	12
	.word	0 @DMA13	13
	.word	0 @DMA14	14
	.word	0 @DMA15	15
	.word	0 @DMA16	16
	.word	0 @DMA17	17
	.word	0 @ADC1_2 	18
	.word	0 @USB_HP_CAN1_TX 19
	.word	0 @USB_LP_CAN1_RX0 20
	.word	0 @CAN1_RX1	21
	.word	0 @CAN1_SCE	22
	.word	0 @EXTI9_5	23
	.word	0 @TIM1_BRK	24
	.word	0 @TIM1_UP	25
	.word	0 @TIM1_TRG_COM	26
	.word	0 @TIM1_CC	27
	.word	0 @tim2dingshiqi +1  @TIM2 28
	.word	0 @tim3dingshiqi +1  @TIM3		29
	.word	0 @TIM4		30
	.word	0 @I2C1_EV	31
	.word	0 @I2C1_ER	32
	.word	0 @I2C2_EV	33
	.word	0 @I2C2_ER	34
	.word	0 @SPI1		35
	.word	0 @SPI2		36
	.word	0 @USART1	37
	.word	0 @USART2	38
	.word	0 @USART3	39
	.word	0 @EXTI15_10	40
	.word	0 @RTCAlarm_IRQ	41
	.word	0 @USBWakeUp	42
	.word	0	
	.word	0	
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0 @BootRAM   
_start:
	ldr r0, = 0x40021000
	mov r1, # 1
	str r1, [r0]
_gsszbz: 
	ldr r2, [r0]
	tst r1, r2           @HSI时钟标志位           
	bne _rccchushihua
	b _gsszbz
_rccchushihua: 
	ldr r4, = 0x40022000
	mov r1, # 0x00000032
	str r1, [r4]           @FLASH缓冲 缓冲开启 
	ldr r1, = 0x1c0000
	str r1, [r0, # 0x04]
	ldr r0, = 0x40021000
	ldr r1, = 0x1000001
	str r1, [r0]
_chaxun:
	ldr r2, [r0]
	ldr r1, = 0x2000000
	tst r1, r2
	bne _rccgg               @等待PLL稳定
	b _chaxun
_rccgg:
	ldr r0, = 0x40021004
	ldr r1, = 0x1c0002
	str r1, [r0]            @ PLL作为系统时钟

_neicunqingling:                  @ 无聊把内存清0
	ldr r0, = 0x20000000
	ldr r2, = 0x4fff         @ 区域是0X4FFF大的地方
	mov r1, # 0              @ 写0
_qingling_xunhuan:                
	str r1, [r0], 4         
	subs r2, # 1
	bne _qingling_xunhuan     @ 循环清0

	
systick:
	@0xe000e010 SYSTICK控制状态寄存器
	@0=定时器使能
	@1=（1倒数到0发出异常请，0无动作）
	@2=（0外部始终1内核时钟）
	@16= 如果赏赐读取本寄存器后SYSTICK已经数到0则该位为1如果读取该位则清0
	@0xe000e014 重载值寄存器 数到0将要被重载的值
	@0xe000e018 当前值，写清0
	@0e000e01c
	@0-23 10MS的时间内倒计数的格数
	@ 30=(1教准不是准确的10MS)（0教准是准确的10MS）
	ldr r0, = 0xe000e010
	mov r1, # 0               
	str r1, [r0]            @ 关掉SYSTICK
	ldr r1, = 9000      @ 重载数
	str r1, [r0, # 4]       @ 写进重载数
	str r1, [r0, # 8]       @ 清0当前数          
	ldr r3, = 0xe000ed23  @systick优先级
	mov r1, # 240
	str r1, [r3]
	mov r1, # 3
	str r1, [r0] @ 开定时器
	
_waisheshizhong:

	@AHBENR=0x40021014
	@0=DMA1,1=DMA2,2=SRAMEN,4=FLITFEN,6=CRCEN,8=FSMCEN,10=SDIOEN
	
	@APB2_ENR=0X40021018 0(AFIO)1(保留)2(PA)3(PB)4(PC)5(PD)6(PE)78(保留)
	@9(ADC1)10(ADC2)11(TIM1)12(SPI1)13(保留)14（USART1）15(保留)
	@APB1_ENR=0X4002101C
	@0=TIM2,1=TIM3,2=TIM4,3=TIM5,4=TIM6,5=TIM7,11=WWDG
	@14=SP12,15=SP13,17=UART3,19=UART4,20=UART5
	@21=I2C,22=I2C2,23=USB,25=CAN,27=BKPT,28=PWR,29=DACEN

	ldr r0, = 0x40021014
	mov r1, # 1
	str r1, [r0]
	
        ldr r0, = 0x40021018 @ APB2_ENR
        ldr r1, = 0x83c
        str r1, [r0]
	
_zhongduankongzhi:
	@SETENA0=0XE000E100,SETENA1=0XE000E104 @中断使能
	@CLRENA0=0XE000E180,CLRENA1=0XE000E184 @中断除能
	@SETPEND0=0XE000E200,SETPPEND1=0XE000E204 @中断悬起
	@CLRPEND0=0XE000E280,CLRPEND1=0XE000E284  @中断解悬
	@ACTIVE0=0XE000E300,ACTIVE1=0XE000E304   @ 中断活动状态
	@0XE000E400-0XE000E43C 中断优先级阵列每个占8位
	@0XE000ED00=CPUID，0XE000ED04=中断控制及状态寄存器
	@0xe000ed08=向量表偏移，0xe000ed0c=应用程序中断及复位
	@0xe000ed10=系统控制，0XE000ED14=配置与控制
	@0xe000ed18-0xe000ed23=系统异常优先级阵列
	ldr r0, = 0xe000ed0c
	ldr r1, = 0x5fa0500
	str r1, [r0]
	ldr r0, = 0xe000e400
	mov r1, # 200
	str r1, [r0, # 28] @ tim2优先级
	mov r1, # 200
	str r1, [r0, # 29] @ tim3 优先级
	
	
	ldr r0, = 0xe000e100 @ 中断使能
	@0-31号使能，0x300000000 = TIM2和TIM3
	ldr r1, = 0x30000000
	str r1, [r0]
	
_tim1chushihua:
	@tim1=0x40012c00
	@+0=CR1 控制寄存器
	@+4=CR2 控制寄存器2
	@+8=SMCR 从模式控制寄存器
	@+c=DIER 中断使能寄存器
	@+10=SR 状态寄存器
	@+14=EGR 事件产生寄存器
	@+18=CCMR1 捕获/比较模式寄存器1
	@+1C=CCMR2 捕获/比较模式寄存器2
	@+20=CCER 捕获/比较使能寄存器
	@+24=CNT 计数器
	@+28=PSC 预分频器
	@+2C=ARR 重载寄存器
	@+30=RCR 重复计数寄存器
	@+34=CCR1 捕获/比较寄存器1
	@+38=CCR2 捕获/比较寄存器2
	@+3C=CCR3 捕获/比较寄存器3
	@+40=CCR4 捕获/比较寄存器4
	@+44=BDTR 刹车/死区寄存器
	@+48=DCR DMA控制器
	@+4C=DMAR 连续模式的DMA地址
	@TIM2=0x40000000
	@18=CCMR1,18=OCMR1,1C=CCMR2,1C=OCMR2
	@CNT与CCR比较占空，ARR与PSC决定频率。主频除以PSC=计数频率

	ldr r0, = 0x40012c00 @ tim1
	ldr r1, = 0
	str r1, [r0, # 0x28] @ 分频
	ldr r1, = 7200
	str r1, [r0, # 0x2c] @ 重载
	ldr r1, =  0x6868
	str r1, [r0, # 0x18] @ 捕获/比较模式
	mov r1, # 0x68
	str r1, [r0, # 0x1c]
	ldr r1, =  0x555
	str r1, [r0, # 0x20]
	ldr r1, = 0x8077
	str r1, [r0, # 0x44]
	ldr r1, = 0
	str r1, [r0, # 0x0c]
	mov r1, # 0xe1
	str r1, [r0]
	
_ioshezhi:
	
	@PA=0x40010800 PB=0x40010c00 PC=0x40011000 
	@PD=0x40011400 PE=0x40011800 PF=0x40011c00 
	@ IO 1(通用推挽10M)2(通用推挽2M)3(通用推挽50M)
	@4(浮空输入)5(通用开漏输出10M)6(通用开漏输出2M)
	@7(通用开漏输出50M)8(上拉下拉输入)9(复用功能推挽输出10M)
	@A(复用功能推挽输出2M)B(复用功能推挽输出50M)C(保留)
	@D(复用功能开溜输出10M)E(复用功能开漏输出2M)F(复用功能开漏输出50M)
	@ 偏移0X8=IDR 输入数据寄存器
	@偏移0XC=ODR 输出数据寄存器
	@偏移0X10=BSRR IO开
	@偏移0X14=BRR  IO关
	ldr r0, = 0x40010800
	ldr r1, = 0x44444bbb
	str r1, [r0, # 0x04]
	ldr r0, = 0x40010c00
	ldr r1, = 0xbbb44444
	str r1, [r0, # 0x04]
	
_dmachushihua:
	DMA1= 0x40020000
	@+0=LSR,+4=IFCR,
	@+8=CCR1,+c=CNDTR1,+10=CPAR1+14=CMAR1,
	@+1c=CCR2,+20=CNDTR2,+24=CPAR2,+28=CMAR2
	@+30=CCR3,+34=CNDTR3,+38=CPAR2,+3c=CMAR3
	@+44=CCR4,+48=CNDTR4,+4c=CPAR4,+50=CMAR4
	@+58=CCR5,+5c=CNDTR5,+60=CPAR5,+64=CMAR5
	@+6C=CCR6,+70=CNDTR6,+74=CPAR6,+78=CMAR6
	@+80=CCR7,+84=CNDTR7,+88=CPAR7,+8c=CMAR7
	ldr r0, = 0x40020000
	ldr r1, = 0x40012c34 @ tim1_ch1
	str r1, [r0, # 0x24]
	ldr r1, = zhengxianbiao
	str r1, [r0, # 0x28]
	ldr r1, = 90
	str r1, [r0, # 0x20]
	ldr r1, = 0x25b1
	str r1, [r0, # 0x1c]
	
	ldr r1, = 0x40012c38 @ tim1_ch2
	str r1, [r0, # 0x38]
	ldr r1, = zhengxianbiao
	str r1, [r0, # 0x3c]
	ldr r1, = 90
	str r1, [r0, # 0x34]
	ldr r1, = 0x25b1
	str r1, [r0, # 0x30]

	ldr r1, = 0x40012c3c @ tim1_ch3
	str r1, [r0, # 0x74]
	ldr r1, = zhengxianbiao
	str r1, [r0, # 0x78]
	ldr r1, = 90
	str r1, [r0, # 0x70]
	ldr r1, = 0x25b1
	str r1, [r0, # 0x6c]
	
	
	ldr r0, = 0x40012c00
	ldr r1, = 0x200
	str r1, [r0, # 0x0c]

	ldr r5, = 60
	
_chaxunch1:
	ldr r6, = 0x40020000
	ldr r7, [r6, # 0x20]
	cmp r7, r5
	bhi _chaxunch1
	
	ldr r1, = 0x600
	str r1, [r0, # 0x0c]

	ldr r4, = 30
	
_chaxunch2:
	ldr r6, = 0x40020000
	ldr r7, [r6, # 0x20]
	cmp r7, r4
	bhi _chaxunch2
	
	ldr r1, = 0xe00
	str r1, [r0, # 0x0c]
	
_tingle:
	b _tingle

	
_cordic: @ 入 R0， 出R12
	@16384 ×3.1415927/2 = 25734
	@r0=x,r2=y,r0=z,r4=d,r5=k,r6=cordic_mabiao
	push {r0-r7,lr}
	mov r5, # 0
	mov r2, r5
	mov r4, r5
	ldr r1, = 0x26dd
_cordicxunhuan:
	asr r4, r0, # 15
	@ x
	mov r7, r2
	asr r2, r5
	eor r2, r4
	sub r2, r4
	sub r3, r1, r2
	@ y
	mov r6, r1
	asr r1, r5
	eor r1, r4
	sub r1, r4
	add r7, r1
	@ z
	ldr r6, = cordicbiao
	lsl r2, r5, # 2
	ldr r1, [r6, r2]
	eor r1, r4
	sub r1, r4
	sub r0, r1
	mov r12, r7 @ 正弦
	mov r1, r3
	mov r2, r7
	add r5, # 1
	cmp r5, # 16
	bne _cordicxunhuan
	pop {r0-r7,pc}
	
	
	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_memory_fault:
	bx lr
_bus_fault:
	bx lr
_usage_fault:
 	bx lr
systickdingshiqi:	              @ SYSTICK定时期中断服务函数
	bx lr
