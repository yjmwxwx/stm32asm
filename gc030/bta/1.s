@ stm32f030f4p6 asm 
@ ADC测量热敏电阻
	 .thumb                 
         .syntax unified
.section .data	
        	.equ STACKINIT,         0x20001000
		.equ shumaguanma,	0x20000000
		.equ anjianma,		0x20000020
		.equ mubiaowendu,	0x20000024
		.equ dangqianwendu,	0x20000028
		.equ bili,		0x2000002c
	
shumaguanmabiao:	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6
wendubiao:     .int 2520,2500,2460,2430,2410,2370,2340,2310,2260,2230,2200,2160,2130,2090,2050,2010,1980,1940,1910,1860,1830,1790,1760,1720,1680,1650,1614,1578,1542,1514,1472,1438,1403,1369,1336,1303,1271,1239,1208,1177,1146,1117,1087,1059,1031,1003,976,949,923,898,873,849,826,803,780,758,737,716,696,676,657,638,620,602,585,568,552,536,521,506,491,477,464,450,437,425,413,401,390,379,368,357,347,337,328,319,310,301,293,284,276,269,251,247,240,234,227,221,215,209,204,198,193,188,183,178,173,169,164,160,156,152,148,144,140,137,133,130,126,123
	.align 2
anjian:	.word _anjian1 + 1,_anjian2 + 1, _anjian3 + 1, shiyan + 1 
.section .text
vectors:        
        .word STACKINIT         
        .word _start + 1        
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
        .word _memory_fault + 1 
        .word _bus_fault + 1    
        .word _usage_fault + 1 

_start:
shizhong:
	ldr r2, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r2]
	ldr r0, = 0x40021000 @ rcc
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
	
waisheshizhong:	 @ 外设时钟  
	@+0x14=RCC_AHBENR
	@0=DMA @2=SRAM @4=FLITF @6=CRC @17=PA @18=PB @19=PC @20=PD @22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x460005
	str r1, [r0, # 0x14]
           
	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
	ldr r1, = 0x200
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@1=TIM3 @4=TIM6 @5=TIM7 @8=TIM14 @11=WWDG @14=SPI @17=USRT2 @18=USART3 @20=USART5 @21=I2C1 @22=I2C2 @23=USB @28=PWR
	ldr r1, = 0x100
	str r1, [r0, # 0x1c]
	
adcchushihua:
	ldr r0, = 0x40012400  @ adc基地址
	ldr r1, = 0x80000000
	str r1, [r0, # 0x08]  @ ADC 控制寄存器 (ADC_CR)  @adc校准
dengadcjiaozhun:
	ldr r1, [r0, # 0x08]
	 movs r1, r1
	bmi dengadcjiaozhun   @ 等ADC校准
kaiadc:
	ldr r1, [r0, # 0x08]
	movs r2, # 0x01
	orrs r1, r1, r2
	str r1, [r0, # 0x08]
dengdaiadcwending:
	ldr r1, [r0]
	lsls r1, r1, # 31
	bpl dengdaiadcwending @ 等ADC稳定
tongdaoxuanze:
	ldr r1, = 0x01
	str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
	ldr r1, = 0x2000        @ 13 连续转换
	str r1, [r0, # 0x0c]    @ 配置寄存器 1 (ADC_CFGR1)
	movs r1, # 0x05         @ 
	str r1, [r0, # 0x14]    @ ADC 采样时间寄存器 (ADC_SMPR)
	ldr r1, [r0, # 0x08]
	movs r2, # 0x04         @ 开始转换
	orrs r1, r1, r2
	str r1, [r0, # 0x08]    @ 控制寄存器 (ADC_CR)


	
io_she_zhi:
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@a(0x48000000)b(0x48000400)c(0x48000800)d(0x48000c00)f(0x48001400)
	@ 输入（00），通用输出（01），复用功能（10），模拟（11）
	@偏移0x4 = 端口输出类型 @ （0 推挽），（ 1 开漏）
	@偏移0x8 = 输出速度  00低速， 01中速， 11高速
	@偏移0xC = 上拉下拉 00无上下拉，  01 上拉， 10下拉
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

	ldr r0, = 0x48000400
	movs r1, # 0x08
	str r1, [r0]
	
	
	ldr r0, = 0x48001400
	movs r1, # 0
	str r1, [r0]
	movs r1, # 0x05
	str r1, [r0, # 0x0c]

_tim14chushihua:
	ldr r0, = 0x40002000
	ldr r1, = 16000
	str r1, [r0, # 0x28]  @psc
	ldr r1, = 500
	str r1, [r0, # 0x2c]  @arr
	ldr r1, = 0x60
	str r1, [r0, # 0x18]
	ldr r1, = 0x01
	str r1, [r0, # 0x20]
	ldr r1, = 0
	str r1, [r0, # 0x34]
	ldr r1, = 0x81
	str r1, [r0]
	
	

	
shiyan:
	ldr r7, = 0xff
	movs r2, # 0
adcpingjun:
	
	ldr r0, = 0x40012440
	ldr r1, [r0]
	adds r2, r2, r1
	subs r7, # 1
	bne adcpingjun
	lsrs r0, r2, # 8
	ldr r1, = 3300
	muls r0, r1
	ldr r1, = 4096
	mov r12, r0
	mov r11, r1
	bl chufa
	mov r0, r12
	ldr r2, = wendubiao
	movs r4, # 0
panduanwendu:
	ldr r3, [r2, r4]
	cmp r3, r0
	bls dedaowendu
	adds r4, r4, # 4
	b panduanwendu
dedaowendu:
	lsrs r4, # 2
	ldr r0, = dangqianwendu
	str r4, [r0]
	ldr r0, = mubiaowendu
	ldr r1, [r0]
	ldr r2, = 100000
	muls r2, r1
	adds r2, r4
	mov r0, r2
	ldr r1, = 8
	ldr r2, = shumaguanma
	bl zhuanshumaguanma
	movs r6, # 8
	lsls r6, # 2
	bl xieshumaguan
	bl _pid
        ldr r0, = 0x48001410
	ldr r1, [r0]
	ldr r2, = anjian
	ldr r0, [r2, # 0x0c]
	mov lr, r0
	lsls r1, # 2
	ldr r0, [r2, r1]
	mov pc, r0
	
_anjian1:
	bx lr
_anjian2:
	push {r0-r1,lr}
	ldr r0, = mubiaowendu
	ldr r1, [r0]
	adds r1, # 1
	cmp r1, # 100
	bls _anjianfanhui
	movs r1, # 100
_anjianfanhui:	
	str r1, [r0]
	pop {r0-r1,pc}
_anjian3:
	push {r0-r1,lr}
	ldr r0, = mubiaowendu
        ldr r1, [r0]
        subs r1, # 1
        cmp r1, # 100
        bls _anjianfanhui1
        movs r1, # 0
_anjianfanhui1:
        str r1, [r0]
	pop {r0-r1,pc}
_pid:
	push {r0-r7,lr}
	ldr r0, = 0x20000024
	ldr r1, [r0]
	ldr r2, [r0, # 0x04]
	subs r1, r2
	bpl _mubiaoxiaoyudangqian
	movs r1, # 0
_mubiaoxiaoyudangqian:
	movs r3, # 5
	muls r1, r3
	ldr r0, = 0x40002034 @ tim14cr1
	str r1, [r0]
	pop {r0-r7,pc}
	
zhuanshumaguanma:@ 16进制转数码管码
		@ R0要转的数据， R1长度，R2结果表首地址
	push {r0-r7,lr}
	ldr r7, = shumaguanmabiao
	movs r5, # 10
	mov r11, r5
xunhuanqiuma:
	mov r12, r0
	bl chufa
	mov r4, r12
	muls r4, r5
	mov r6, r4
	subs r3, r0, r6
	lsls r3, # 2
	ldr r6, [r7, r3]
	str r6, [r2]
	adds r2, r2, # 4
	mov r0, r12
	subs r1, # 1
	bne xunhuanqiuma
	pop {r0-r7,pc}
	
xieshumaguan: @ r6=位数 @数码管码
	push {r0-r7,lr}
	movs r7, # 0
	mov r0, r7
	ldr r5, = shumaguanma
	ldr r2, = 0xfefefefe
shumaguanshuaxin:
	mov r1, r2
	ldr r3, [r5, r7]
	lsrs r4, r1, # 24
	lsls r4, r4, # 8
	orrs r4, r4, r3
	mov r12, r4
	bl xie595
	adds r0, # 1
	cmp r0, # 8
	bne _shumaguanyiwei
	movs r0, # 0
_shumaguanyiwei:
	ldr r2, = 0xfefefefe
	lsls r2, r0
	adds  r7, r7, # 4
	cmp r7, r6
	bcc shumaguanshuaxin
	pop {r0-r7,pc}
	
xie595: @ R12=要写的数据
	push {r0-r7,lr}
	movs r0, # 0x40
	movs r7, # 0x80 
	movs r6, # 0x20 
	mov r5, r12
	movs r3, # 16   @16位
	ldr r2, = 0x48000000 @ gpioa
	movs r1, # 0x01
xunhuan595:
	str r7, [r2, # 0x18]
	bl yanshi
	tst r5, r1
	bne xie595_0
	str r0, [r2, # 0x28]
	b suocun595
xie595_0:
	str r0, [r2, # 0x18]
suocun595:
	bl yanshi
	lsrs r5, # 1
	str r7, [r2, # 0x28]
	bl yanshi
	subs r3, r3, # 1
	bne xunhuan595
	str r6, [r2, # 0x18]
	bl yanshi
	str r6, [r2, # 0x28]
	bl yanshi
	pop {r0-r7,pc}

yanshi:
	push {r0-r7,lr}
	ldr r0, = 100
_yanshi11:
	subs r0, # 1
	bne _yanshi11
	pop {r0-r7,pc}
	
chufa:	@软件除法
	@ r12 除以 R11
	push {r0-r7,lr}
	mov r6, r12
	cmp r6, # 0
	beq chufafanhui
	mov r7, r11
	cmp r7, # 0
	beq chufafanhui
	movs r0, # 0
chufaxunhuan:
	mov r12, r6
	bl jianceweishu
	mov r2, r12
	mov r12, r7
	bl jianceweishu
	mov r3, r12
	subs r2, r3, r2
	mov r4, r7
	lsls r4, r2
	mov r3, r4
	cmp r6, r3
	bcc dd1
	b dd2
dd1:
	subs r2, r2, # 1
	lsrs r3, # 1
dd2:
	subs r6, r6, r3
	movs r3, # 1
	lsls r3, r2
	orrs  r0, r3
	cmp r6, r7
	bcs chufaxunhuan
	mov r12, r0
chufafanhui:
	pop {r0-r7,pc}

jianceweishu:
	push {r0-r7,lr}
	movs r0, # 0
	mov r1, r12
jianceweishu1:
	bmi weishufanhui
	adds r0, r0, # 1
	lsls r1, # 1
	b jianceweishu1
weishufanhui:
	mov r12, r0
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
	
