	 .thumb                 
         .syntax unified
.section .data
shumaguanmabiao: .byte 0x88,0xbe,0xc4,0x94,0xb2,0x91,0x81,0xbc,0x80,0x90
hongwaimabiao: .int 0xffa25d,0xff629d,0xffe21d,0xff22dd,0xff02fd,0xffc23d,0xffe01f,0xffa857,0xff906f,0xff6897,0xff9867,0xffb04f,0xff30cf,0xff18e7,0xff7a85,0xff10ef,0xff38c7,0xff5aa5,0xff42bd,0xff52ad
	
        	.equ STACKINIT,          0x20005000
		.equ systickbiaozhi,     0x20000300
.section .text
xiangliangbiao:
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
	.word	tim2dingshiqi +1  @TIM2 28
	.word	0 @TIM3		29
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
	ldr r0, = 0x40010004
	ldr r1, = 0x02000000
	str r1, [r0]

	str r1, [r0, # 0x04]
	ldr r0, = 0x40021000
	ldr r1, = 0x14D83
	str r1, [r0]
gsszbz: 
	ldr r2, [r0]
	ldr r1, = 0x20000
	tst r1, r2           @HSE高速时钟标志位           
	bne rccchushihua
	b gsszbz
rccchushihua: 
	ldr r0, = 0x40022000
	mov r1, # 0x00000032
	str r1, [r0]           @FLASH缓冲 缓冲开启 
	ldr r0, = 0x40021004
	ldr r1, = 0x1D8400
	str r1, [r0]
	ldr r0, = 0x40021000
	ldr r1, = 0x1033D03
	str r1, [r0]
chaxun:
	ldr r2, [r0]
	ldr r1, = 0x2000000
	tst r1, r2
	bne rccgg               @等待PLL稳定
	b chaxun
rccgg:
	ldr r0, = 0x40021004
	ldr r1, = 0x1D8402
	str r1, [r0]            @ PLL作为系统时钟

	ldr r0, = 0x40010004
	ldr r1, = 0x02000000
	str r1, [r0]

neicunqingling:                  @ 无聊把内存清0
	ldr r0, = 0x20000000
	ldr r2, = 0x4fff         @ 区域是0X4FFF大的地方
	mov r1, # 0              @ 写0
qingling_xunhuan:                
	str r1, [r0], 4         
	subs r2, # 1
	bne qingling_xunhuan     @ 循环清0

chushihuayixieshuju:	 @初始化一些数据
	ldr r0, = 0x20000500
	str r0, [r0, -4]
	str r0, [r1]
	mov r0, # 0
	mov r1, r0
	mov r2, r0
	mov r3, r0
	mov r4, r0
	mov r5, r0
	mov r6, r0
	mov r7, r0
	mov r8, r0
	mov r9, r0
	mov r10, r0
	mov r11, r0
	mov r12, r0
	
	
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
	ldr r1, = 0xffffff      @ 重载数
	str r1, [r0, # 4]       @ 写进重载数
	str r1, [r0, # 8]       @ 清0当前数
	mov r1, # 0
	str r1, [r0]            @ 关定时器
	ldr r0, = 0xe000ed23  @systick优先级
	mov r1, # 240
	str r1, [r0]
waisheshizhong:


	@APB2_ENR=0X40021018 0(AFIO)1(保留)2(PA)3(PB)4(PC)5(PD)6(PE)78(保留)
	@9(ADC1)10(ADC2)11(TIM1)12(SPI1)13(保留)14（USART1）15(保留)
	        ldr r0, = 0x40021018 @ APB2_ENR
	        ldr r1, = 0x3c
	        str r1, [r0]
	@APB1_ENR=0X4002101C
	@0=TIM2,1=TIM3,2=TIM4,3=TIM5,4=TIM6,5=TIM7,11=WWDG
	@14=SP12,15=SP13,17=UART3,19=UART4,20=UART5
	@21=I2C,22=I2C2,23=USB,25=CAN,27=BKPT,28=PWR,29=DACEN
		ldr r0, = 0X4002101C @ APB1_ENR
		ldr r1, = 0x01
		str r1, [r0]
	
zhongduankongzhi:
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
	ldr r0, = 0xe000e100 @ 中断使能
	ldr r1, = 0x10000000
	str r1, [r0]
	
	
	
timdingshiqi:
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
	ldr r0, = 0x40000000 @ tim2
	ldr r1, = 7200
	str r1, [r0, # 0x28] @ 分频
	ldr r1, = 10000
	str r1, [r0, # 0x2c] @ 重载
	mov r1, # 2
	str r1, [r0, # 0x0c] @开中断
	mov r1, # 0x1
	str r1, [r0, # 0x18] @ 捕获/比较模式
	mov r1, # 1
	str r1, [r0, # 0x20] @ 下降沿捕获
	ldr r1, = 0x81
	str r1, [r0]
	
IOshezhi:
	
	ldr r0, = 0x40010c00
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
	ldr r1, = 0x55555555
	str r1, [r0, # 0x04]
	ldr r0, = 0xe000e010
	mov r1, # 7
	str r1, [r0]
	
zhuchengxu:
	mov r3, # 0x01
jiancedingshiqibiaozhi:
	ldr r0, = 0x40000000
	mov r1, # 0x81
	str r1, [r0]
	ldr r6, = systickbiaozhi
	ldr r7, [r6]         @ 取出计时标志位
	cmp r7, # 1          @ 查询是不是到了时间
	bne shumaguan        @ 没到条砖数码管显视
	mov r7, # 0         
	str r7, [r6]         @ 清除标志
	add r11, r11, # 1    @ 每次标志R11加1 
	cmp r11, # 100       @ 如果R11= 100 
	bne shumaguan        @ 不等于100调转shumaguan
	mov r11, # 0         @ 等于100 R11清0
shumaguan:
	mov r10, # 10        @ 被除数
	udiv r8, r11, r10    @ 取出十位数的个数
	mul  r6, r8, r10     @ 还原没有个位的十进制数
	sub r7, r11, r6      @ 求出个位数
	ldr r0, = shumaguanmabiao  @ 数码管码表
	ldrb r1, [r0, r8]    @ 取出十位对应的码
	ldrb r2, [r0, r7]    @ 取出个位对应的码
	ldr r0, = 0x20000000 @ 放结果的内存位置
	strb r1, [r0, # 1]   @ 储存数码管码
	strb r2, [r0, # 2]
	strb r3, [r0]
	bl xie595            @ 调用74HC595函数
	bl hongwaijiema
	bl anjianpanduan
	lsl r3, # 1
	cmp r3, # 0x80
	bhi zhuchengxu
	b jiancedingshiqibiaozhi

	
xie595:
	@74HC595 11=输入锁存 12=输出锁存 14=数据
	push {r0-r12,lr}
	mov r12, sp          @把SP指针保存到R12
	ldr r0, = 0x422181b0 @ 位带地址  
	mov r1, # 1          @ 1
	mov r2, # 0          @ 0
	ldr r3, = 0x22000000 @ 0x20000000的位带
	mov r4, # 24         @ 写两个8位
xunhuan595:
	str r2, [r0, # 0x08] @ 595_11 输入锁存
	ldr r5, [r3], # 4    @ 取出一位的数据
	str r5, [r0]         @14脚输出数据
	str r1, [r0, # 0x08] @ 锁存
	subs r4, # 1         
	bne xunhuan595       @循环16次
	str r2, [r0, # 0x04] @ 12输出锁存
	str r1, [r0, # 0x04] 
	mov sp, r12          @ 恢复指针
	pop {r0-r12,pc}      @ 弹出各寄存器返回
hongwaijiema:
	push {r0-r12,lr}
	mov r12, sp
	mov r11, # 32
	ldr r0, = 0x20000502 
	ldr r5, = 0x22009f7c
quchuhongwaima:
	ldrb r1, [r0], # 1
	mov r3, # 0x08
	cmp r1, r3
	bls hongwaifanhui
	mov r3, # 0x12
	cmp r1, r3
	bls hongwai_0
	mov r3, # 0x19
	cmp r1, r3
	bls hongwai_1
	mov r3, # 0x1f
	cmp r1, r3
	bls hongwai_jia
	b hongwaifanhui
hongwai_0:
	mov r4, # 0
	b hongwaichucun
hongwai_1:
	mov r4, # 1
	b hongwaichucun
hongwai_jia:
	ldr r0, = 0x200004f0
	ldr r1, [r0]
	add r1, # 1
	str r1, [r0]
	
hongwaichucun:
	str r4, [r5], # -4
	subs r11, # 1
	bne quchuhongwaima
hongwaifanhui:
	mov sp, r12
	pop {r0-r12,pc}
anjianpanduan:
	push {r0-r12,lr}
	mov r12, sp
	ldr r0, = 0x200004f8
	ldr r3, [r0]
	ldr r1, = hongwaimabiao
	mov r5, # 20
xunhuanpanduan:
	ldr r2, [r1], # 0x04
	cmp r3, r2
	beq baocunanjian
	subs r5, # 1
	bne xunhuanpanduan
	b anjianfanhui
baocunanjian:
	str r5, [r0, # - 4]
anjianfanhui:	
	mov sp, r12
	pop {r0-r12,pc}
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
systickdingshiqi:              @ SYSTICK定时期中断服务函数
	push {r0-r12,lr}
	mov r12, sp
	ldr r0, = 0xe00ed04
	ldr r1, = 0x2000000 
	str r1, [r0]         @ 挂起SYSTICK
	ldr r2, = systickbiaozhi @ 计数到标志
	ldr r1, [r2]             @ 取出标志
	orr r1, # 1            
	str r1, [r2]             @ 储存标志
	mov sp, r12              @恢复指针
	pop {r0-r12,pc}
tim2dingshiqi:
	push {r0-r12,lr}
	mov r12, sp
	ldr r4, = 0x20000578 @ 数据顶
	ldr r0, = 0x40000000 @ cr1
	ldr r1, = 0x20000500 @ 读取的红外码数据的指针
	ldr r2, [r0, # 0x34] @读取捕获到的时间
	ldr r3, [r1, # -4] @读取指针
	str r2, [r3], # 1  @写入捕获的时间
	cmp r3, r4
	it hi
	movhi r3, r1
	str r3, [r1, # -4] @保存指针
	mov r2, # 0
	str r2, [r0, # 0x24]
	mov sp, r12
	pop {r0-r12,pc}
	
