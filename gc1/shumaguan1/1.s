	 .thumb                 
         .syntax unified
.section .data
shumaguanmabiao: .byte 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff,0xff,0xff,0xff
	
	
	        .equ yanshi1, 		0x80000
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
	
_start:
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

neicunqingling:                  @ 无聊把内存清0
	ldr r0, = 0x20000000
	ldr r2, = 0x4fff         @ 区域是0X4FFF大的地方
	mov r1, # 0              @ 写0
qingling_xunhuan:                
	str r1, [r0], 4         
	subs r2, # 1
	bne qingling_xunhuan     @ 循环清0

jicunqiqingling:
	mov r0, # 0
	mov r1, # 0
	mov r2, # 0
	mov r3, # 0
	mov r4, # 0
	mov r5, # 0
	mov r6, # 0
	mov r7, # 0
	mov r8, # 0
	mov r9, # 0
	mov r10, # 0
	mov r11, # 0
	mov r12, # 0
	
	
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
	str r1, [r0]
	str r1, [r0, # 0x04]

	ldr r0, = 0xe000e010
	mov r1, # 7
	str r1, [r0]
dd1:	
	ldr r1, = shumaguanmabiao
	ldr r0, = 0x20000000
	mov r3, # 100
zhuchengxu:
	ldrb r2, [r1, r3]
	str  r2, [r0]
	bl xie595
	sub r3, # 1
	cmp r3, # 0
	beq dd1
	ldr r4, = yanshi1
	
ys1:
	subs r4, # 1
	bne ys1
	b zhuchengxu
	

	
xie595:
	@74HC595 11=输入锁存 12=输出锁存 14=数据
	push {r0-r12,lr}
	mov r12, sp          @把SP指针保存到R12
	ldr r0, = 0x422181b0 @ 位带地址，595的11脚  
	mov r1, # 1          @ 1
	mov r2, # 0          @ 0
	ldr r3, = 0x22000000 @ 0x20000000的位带
	mov r4, # 8         @ 写两个8位
xunhuan595:
	str r2, [r0, # 0x08] @ 595_11 输入锁存
	ldr r5, [r3], # 4    @ 取出一位的数据
	str r5, [r0]         @14脚输出数据
	str r1, [r0, # 0x08] @ 锁存
	subs r4, # 1         
	bne xunhuan595       @循环16次
	str r2, [r0, # 0x04] @ 12输出锁存
	str r1, [r0, # 0x04] 
	ldr r5, = 0xffff     @ 延时数
xunhuan1_595:
	subs r5, # 1
	bne xunhuan1_595     @ 延时
	mov sp, r12          @ 恢复指针
	pop {r0-r12,pc}      @ 弹出各寄存器返回
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
