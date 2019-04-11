	@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000

	.equ shumaguanma,	0x20000000
	.equ chengxubiao,	0x20000100
	.equ chengxuzhizhen,	0x200000fc
	.equ jianpanzhizhen,	0x200000f8
	.equ anjianhao,		0x200000f4
	.equ anjiancishu,	0x200000f0
	.equ anjian32weipianyi,	0x200000ec
shumaguanmabiao:	
	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e
shumaguanshuaxinbiao:
	.int 0xfe00,0xfd00,0xfb00,0xf700,0xef00,0xdf00,0xbf00,0x7f00,0
jianpansaomiaoma:
	.int 0x80,0x40,0x20,0x10
anjianma:
	.byte 0x18,0x28,0x48,0x88,0x14,0x24,0x44,0x84,0x12,0x22,0x42,0x82,0x11,0x21,0x41,0x81
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
	.word 0 @_adc1 +1          @ 12
	.word 0       @_tim1_brk_up +1  @ 13
	.word 0        @ _tim1_cc +1    @ 14
	.word 0         @_tim2 +1       @ 15
	.word 0          @_tim3 +1      @ 16
	.word 0                         @ 17
	.word 0		                @ 18
	.word @_tim14 +1    @ 19
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
	@1=TIM3 @4=TIM6 @5=TIM7 @8=TIM14 @11=WWDG @14=SPI @17=USRT2 @18=USART3 @20=USART5 @21=I2C1 @22=I2C2 @23=USB @28=PWR
		
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
	ldr r1, = 0x28045500
	str r1, [r0]
	ldr r2, = 0x240000aa
	str r2, [r0, # 0x0c]
	
	
	ldr r0, = 0x48001400
	movs r1, # 0x05
	str r1, [r0]

	ldr r0, = anjian32weipianyi
	movs r1, # 28
	str r1, [r0]
	
	
_shiyan111:
	bl _juzhenjianpan
	ldr r6, = anjiancishu
	ldr r7, [r6]
	cmp r7, # 16
	bls _tiaoguoanjianzizeng
	movs r7, # 0
	str r7, [r6]
	ldr r0, = chengxubiao
	ldr r1, = chengxuzhizhen
	ldr r2, [r1]
	ldr r4, = anjian32weipianyi
	ldr r5, [r4]
	ldr r3, = anjianhao
	ldr r3, [r3]
	ldr r6, [r0, r2]
	lsls r3, r3, r5
	orrs r3, r3, r6
	str r3, [r0, r2]
	subs r5, r5, # 0x04
	bpl _anjianyiwei
	movs r5, # 28
	adds r2, r2, # 0x04
	str r2, [r1]
_anjianyiwei:	
	str r5, [r4]
	
_tiaoguoanjianzizeng:	
	ldr r3, = chengxubiao
	ldr r2, = chengxuzhizhen
	ldr r2, [r2]
	ldr r0, [r3, r2]
	ldr r2, = shumaguanma
	bl _zhuanshumaguanma
	movs r0, # 8
	lsls r0, r0, # 2
	bl _xieshumaguan
	b _shiyan111

_juzhenjianpan:
	push {r0-r5}
	ldr r0, = jianpansaomiaoma
	ldr r1, = jianpanzhizhen
	ldr r3, = anjianhao
	ldr r4, = 0x48000000
	ldr r2, [r1]
	adds r2, r2, # 4
	cmp r2, # 16
	bne _tiaochuanjiansaomiao
	movs r2, # 0
_tiaochuanjiansaomiao:
	str r2, [r1]
	ldrb r1, [r0, r2]
	strb r1, [r4, # 0x14]

	ldrb r1, [r4, # 0x10]
	lsls r2, r1, # 28
	lsrs r2, r2, # 28
	movs r2, r2
	beq _meianjian
	ldr r0, = anjianma
	movs r6, # 0
_zhaoanjianma:	
	ldrb r2, [r0, r6]
	cmp r1, r2
	beq _youanjian
	adds r6, r6, # 1
	cmp r6, # 16
	beq _meianjian
	b _zhaoanjianma
_youanjian:
	ldr r0, = anjiancishu
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	str r6, [r3]
	
_meianjian:	
	pop {r0-r5}
	bx lr
	
_zhuanshumaguanma:			@ 转数码管码
		@ R0要转的数据,R2结果表首地址
	push {r0-r7,lr}
	ldr r7, = shumaguanmabiao
	movs r1, # 0
_xunhuanqiuma:
	movs r4, # 28
	subs r4, r4,  r1
	mov r5, r0
	lsls r5, r5, r4
	lsrs r5, r5, # 28
	lsls r5, r5, # 2
	ldr r6, [r7, r5]
	str r6, [r2, r1]
	adds r1, r1, # 0x04
	cmp r1, # 32
	bne _xunhuanqiuma
	
	
	pop {r0-r7,pc}
_xieshumaguan:			 @ r0=位数 @数码管码
	push {r0-r7,lr}
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

_xie595:	 @ R0=要写的数据
	push {r0-r7,lr}
	mov r5, r0
	ldr r0, =  0x200
	movs r6, # 0x02
	movs r7, # 0x01
	movs r3, # 16   @16位
	movs r1, # 0x01
_xunhuan595:
	ldr r2, = 0x48001400
	str r7, [r2, # 0x18]
	bl _yanshi
	tst r5, r1
	bne _xie595_0
	ldr r2, = 0x48000000
	str r0, [r2, # 0x28]
	b _suocun595
_xie595_0:
	ldr r2, = 0x48000000
	str r0, [r2, # 0x18]
_suocun595:
	bl _yanshi
	lsrs r5, # 1
	ldr r2, = 0x48001400
	str r7, [r2, # 0x28]
	bl _yanshi
	subs r3, r3, # 1
	bne _xunhuan595
	ldr r2, = 0x48001400
	str r6, [r2, # 0x18]
	bl _yanshi
	ldr r2, = 0x48001400
	str r6, [r2, # 0x28]
	bl _yanshi
	pop {r0-r7,pc}
	

_yanshi:
	push {r7,lr}
	ldr r7, = 30
_yanshi11:
	subs r7, # 1
	bne _yanshi11
	pop {r7,pc}

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
	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
