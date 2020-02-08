	@@单片机stm32f030f4p6
	@@ 驻波表
	@作者：yjmwxwx
	@时间：2020-01-01
	@编译器：ARM-NONE-EABI
	 .thumb
	         .syntax unified
	.section .data
	.align 4
shumaguanmabiao:
	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6
shumaguanshuaxinbiao:
	.int 0xfe00,0xfd00,0xfb00,0xf700,0xef00,0xdf00,0xbf00,0x7f00,0
xuanzhuanyinzi:
	.int 0x8000,0x0000,0x5ED7,0xFFFFAA0B,0x0C8B,0xFFFF809E,0xFFFFB3C1,0xFFFF9931,0xFFFF8276,0xFFFFE708,0xFFFF9236,0x41CE,0xFFFFDAD8,0x7A7D,0x36BA,0x73B5,0x7641,0x30FB,0x7884,0xFFFFD4E1,0x3C56,0xFFFF8F1E,0xFFFFE0E7,0xFFFF83D7,0xFFFF9593,0xFFFFB8E4,0xFFFF8163,0x12C8,0xFFFFAECD,0x62F1,0x0647,0x7FD8,0x5A82,0x5A82,0x7FD8,0x0647,0x62F2,0xFFFFAECD,0x12C8,0xFFFF8163,0xFFFFB8E4,0xFFFF9593,0xFFFF83D7,0xFFFFE0E6,0xFFFF8F1E,0x3C56,0xFFFFD4E1,0x7884,0x30FB,0x7641,0x73B5,0x36BA,0x7A7D,0xFFFFDAD9,0x41CE,0xFFFF9237,0xFFFFE708,0xFFFF8276,0xFFFF9931,0xFFFFB3C1,0xFFFF809E,0x0C8B,0xFFFFAA0B,0x5ED7,0x0000,0x8000,0x55F5,0x5ED7,0x7F62,0x0C8B,0x66CF,0xFFFFB3C1,0x18F8,0xFFFF8276,0xFFFFBE33,0xFFFF9236,0xFFFF8584,0xFFFFDAD8,0xFFFF8C4A,0x36B9,0xFFFFCF05,0x7641,0x2B1E,0x7884,0x70E2,0x3C56,0x7C2A,0xFFFFE0E7,0x471D,0xFFFF9593,0xFFFFED39,0xFFFF8163,0xFFFF9D0F,0xFFFFAECD,0xFFFF8028,0x0647,0xFFFFA57E,0x5A82,0xFFFFF9B8,0x7FD8,0x5133,0x62F2,0x7E9D,0x12C8,0x6A6D,0xFFFFB8E4,0x1F1A,0xFFFF83D7,0xFFFFC3AA,0xFFFF8F1E,0xFFFF877C,0xFFFFD4E1,0xFFFF89BF,0x30FB,0xFFFFC946,0x73B5,0x2527,0x7A7D,0x6DC9,0x41CE,0x7D8A,0xFFFFE708,0x4C40,0xFFFF9931,0xFFFFF375,0xFFFF809E,0xFFFFA129,0xFFFFAA0B,0xFFFF8000,0x0000,0xFFFFA129,0x55F5,0xFFFFF374,0x7F62,0x4C3F,0x66CF,0x7D8A,0x18F8,0x6DCA,0xFFFFBE33,0x2528,0xFFFF8584,0xFFFFC947,0xFFFF8C4A,0xFFFF89BF,0xFFFFCF04,0xFFFF877C,0x2B1E,0xFFFFC3A9,0x70E2,0x1F19,0x7C2A,0x6A6D,0x471D,0x7E9D,0xFFFFED39,0x5134,0xFFFF9D0F,0xFFFFF9B9,0xFFFF8028,0xFFFFA57E,0xFFFFA57E,0xFFFF8028,0xFFFFF9B8,0xFFFF9D0E,0x5133,0xFFFFED38,0x7E9D,0x471C,0x6A6D,0x7C29,0x1F1A,0x70E3,0xFFFFC3AA,0x2B1F,0xFFFF877C,0xFFFFCF05,0xFFFF89BF,0xFFFF8C4B,0xFFFFC946,0xFFFF8583,0x2527,0xFFFFBE32,0x6DC9,0x18F8,0x7D8A,0x66CF,0x4C40,0x7F62,0xFFFFF375,0x55F6,0xFFFFA129,0x0000,0xFFFF8000,0xFFFFAA0B,0xFFFFA129,0xFFFF809E,0xFFFFF374,0xFFFF9931,0x4C3F,0xFFFFE707,0x7D8A,0x41CD,0x6DCA,0x7A7C,0x2528,0x73B6,0xFFFFC947,0x30FC,0xFFFF89BF,0xFFFFD4E2,0xFFFF877C,0xFFFF8F1E,0xFFFFC3A9,0xFFFF83D6,0x1F19,0xFFFFB8E3,0x6A6D,0x12C7,0x7E9D,0x62F1,0x5134,0x7FD8,0xFFFFF9B9,0x5A82,0xFFFFA57E,0x0648,0xFFFF8028,0xFFFFAECD,0xFFFF9D0E,0xFFFF8163,0xFFFFED38,0xFFFF9593,0x471C,0xFFFFE0E6,0x7C29,0x3C56,0x70E3,0x7884,0x2B1F,0x7641,0xFFFFCF05,0x36BA,0xFFFF8C4B,0xFFFFDAD9,0xFFFF8583,0xFFFF9237,0xFFFFBE32,0xFFFF8276,0x18F7,0xFFFFB3C0,0x66CF,0x0C8B,0x7F62,0x5ED6,0x55F6
yjmwxwx:
	.equ STACKINIT,        	        0x20001000
	.equ shumaguanma,		0x20000000
	.equ fuhao,			0x20000010
	.equ dmawan,			0x200000f4
	.equ jishu2,			0x200000f8
	.equ jishu,			0x200000fc
	.equ fan_she_shi_bu,		0x20000120
	.equ ru_she_shi_bu,		0x20000124
	.equ fan_she_xu_bu,		0x20000128
	.equ ru_she_xu_bu,		0x2000012c
	.equ shibuhuanchong,		0x20000140
	.equ lvboqizhizhen,		0x20000a00
	.equ lvboqihuanchong,		0x20000a04
	.equ dianyabiaozhizhen,		0x200001f8
	.equ dianyabiaoman,		0x200001fc
	.equ dianyabiao,		0x20000200
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
	.word aaa +1           @ _wwdg +1          	@ 0
	.word aaa +1           @_pvd +1            	@ 1
	.word aaa +1           @_rtc +1            	@ 2
	.word aaa +1           @_flash +1          	@ 3
	.word aaa +1	       @ _rcc + 1          	@ 4
	.word aaa +1           @_exti0_1  +1      	@ 5
	.word aaa +1           @ _exti2_3 +1      	@ 6
	.word aaa +1           @_exti4_15 +1     	@ 7
	.word aaa +1                         		@ 8
	.word __dma_wan  +1  		      		@ 9
	.word aaa +1	       @_dma1_2_3 +1        	@ 10
	.word aaa +1	       @ _dma1_4_5 +1	        @ 11
	.word aaa +1	       @_adc1 +1          	@ 12
	.word aaa +1           @_tim1_brk_up +1  	@ 13
	.word aaa +1           @ _tim1_cc +1            @ 14
	.word aaa +1           @_tim2 +1      	        @ 15
	.word _tim3 +1                             	@ 16
	.word aaa +1                                    @ 17
	.word aaa +1		                	@ 18
	.word aaa +1	       @_tim14 +1   	        @ 19
	.word aaa +1                         		@ 20
	.word aaa +1           @_tim16 +1      		@ 21
	.word aaa +1           @_tim17 +1      		@ 22
	.word aaa +1           @_i2c   +1     		@ 23
	.word aaa +1                         		@ 24
	.word aaa +1           @_spi   +1    		@ 25
	.word aaa +1                         		@ 26
	.word aaa +1           @_usart1 +1     		@ 27
	.align 2

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
	ldr r1, = 0x150002
	mov r0, r0
	str r1, [r0, # 0x04]
	mov r0, r0
	ldr r1, = 0x1010000
	mov r0, r0
	str r1, [r0]

dengpll:
        ldr r1, [r0]
	lsls r1, # 6
	bpl dengpll

	ldr r1, = 100
	str r1, [r0, # 0x30]

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
	@ 0=DMA @ 2=SRAM @ 4=FLITF@ 6=CRC @ 17=PA @ 18=PB @ 19=PC @ 20=PD @ 22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x60001
	str r1, [r0, # 0x14]

	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
	ldr r1, = 0xa00
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@ 1=TIM3 @ 4=TIM6 @ 5=TIM7 @ 8=TIM14 @ 11=WWDG @ 14=SPI @ 17=USRT2 @ 18=USART3 @ 20=USART5 @ 21=I2C1
	@ 22=I2C2 @ 23=USB @ 28=PWR
	ldr r2, = 0x102
	str r2, [r0, # 0x1c]

_waishezhongduan:				@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效

	ldr r0, =  0xe000e100
	ldr r1, = 0x200 @0x10200  @ 0x10000
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
       @ ldr r1, [r0]
       @ lsls r1, r1, # 31
        @ bpl _dengdaiadcwending @ 等ADC稳定
_tongdaoxuanze:
        ldr r1, = 0x80000000
        str r1, [r0, # 0x10]
        ldr r1, = 0x63
        str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
        ldr r1, = 0x8c3 @0x2003 @0x8c3
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

	@ adc dma
	ldr r0, = 0x40020000
	ldr r1, = 0x40012440
	str r1, [r0, # 0x10]
	ldr r1, = dianyabiao
	str r1, [r0, # 0x14]
	ldr r1, = 912
	str r1, [r0, # 0x0c]
	ldr r1, = 0x583 @  0x583 	@ 5a1
	str r1, [r0, # 0x08]


tim1chushiha:				
	ldr r5, = 0x40012c00 @ tim1_cr1
	ldr r1, = 0
	str r1, [r5, # 0x28] @ psc
	ldr r1, = 1
	str r1, [r5, # 0x2c] @ ARR
	ldr r1, = 0x38
	str r1, [r5, # 0x1c] @ ccmr2  CC3
	ldr r1, = 0x100    @  CC3
	str r1, [r5, # 0x20] @ ccer
	ldr r1, = 0x8000
	str r1, [r5, # 0x44] @ BDTR
	ldr r1, = 1
	str r1, [r5, # 0x3c]
	movs r4, # 0xe1
tim3chushihua:				
	ldr r0, = 0x40000400 @ tim3_cr1
	ldr r1, = 0
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 2799
	str r1, [r0, # 0x2c] @ ARR
	ldr r1, =  0x3800 @ 0x3800
	str r1, [r0, # 0x1c] @ ccmr2
	ldr r1, =  0x1000
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 2799
	str r1, [r0, # 0x40] @ ccr4
	movs r1, # 0x70
	str r1, [r0, # 0x04]
	@movs r1, # 0x01
	@str r1, [r0, # 0x0c]
	movs r1, # 0xe1
	str r1, [r0]
	str r4, [r5]
@_systick:				@ systick定时器初始化
@
@	ldr r0, = 0xe000e010
@	ldr r1, = 4800000
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
	ldr r1, = 0x28203d5f
	str r1, [r0]
	ldr r1, = 0x200
	str r1, [r0, # 0x24]
	
ting:
	ldr r0, = jishu
	ldr r1, = 0x800
	ldr r2, [r0]
	adds r2, r2, # 1
	str r2, [r0]
	cmp r2, r1
	bne __xianshi
	movs r2, # 0
	str r2, [r0]
	bl __kai_dma
__xianshi:
	ldr r0, = fan_she_shi_bu
	ldr r0, [r0, # 0x04]
	movs r0, r0
	bpl __shu_ma_guan_xian_shi
	mvns r0, r0
	adds r0, r0, # 1
	ldr r2, = fuhao
	movs r3, # 0
	str r3, [r2]
	b __led_xian_shi
__shu_ma_guan_xian_shi:
	ldr r3, = fuhao
	movs r2, # 0x02
	str r2, [r3]
__led_xian_shi:	
	movs r1, # 4
        ldr r2, = shumaguanma
	movs r3, # 0xff		@小数点位置
        bl _zhuanshumaguanma
	movs r0, # 5
        bl _xieshumaguan
	b ting
__kai_dma:
	push {r0-r2,lr}
	ldr r2, = 0x40012400
	movs r1, # 0x11
	str r1, [r2, # 0x08]
__deng_adc_wan:
	ldr r1, [r2, # 0x08]
	cmp r1, # 1
	bne __deng_adc_wan
	ldr r0, = 0x40020000
	movs r1, # 0
	str r1, [r0, # 0x08]
	ldr r1, = 912
	str r1, [r0, # 0x0c]
	ldr r1, = 0x583
	str r1, [r0, # 0x08]
	movs r1, # 0x05
	str r1, [r2, # 0x08]
	pop {r0-r2,pc}
	

__dft:
	push {r0-r7,lr}
	mov r0, r8
	mov r1, r9
	mov r2, r10
	mov r3, r11
	mov r4, r12
	push {r0-r4}
        ldr r0, = dianyabiao
        subs r0, r0, # 0x08
__zhao_shang_sheng2:
        adds r0, r0, # 0x08
        ldrh r2, [r0, # 0x04]
        cmp r2, # 0
        bne __zhao_shang_sheng2
        ldrh r3, [r0, # 0x0c]
        subs r2, r2, r3
	bpl __zhao_shang_sheng2
	ldr r1, = xuanzhuanyinzi
	movs r2, # 1
	lsls r2, r2, # 10
	mov r8, r2
	movs r3, # 0
	mov r11, r3	
	mov r12, r3
	mov r10, r3
	mov r9, r3
__dft_xun_huan:
	ldr r4, [r0, r3]
	ldr r2, [r1, r3]	@r
	push {r2}
	adds r3, r3, # 4
	ldr r5, [r0, r3]
	ldr r2, [r1, r3]
	adds r3, r3, # 4
	mov r6, r4
	mov r7, r5
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r6, r6, # 16
	lsls r5, r5, # 16
	lsrs r5, r5, # 16
	lsrs r7, r7, # 16
	subs r4, r4, r6
	subs r5, r5, r7
	mov r6, r4
	mov r7, r5
	muls r4, r4, r2		@i
	muls r5, r5, r2		@i
	asrs r4, r4, # 15
	asrs r5, r5, # 15
	mov r2, r9
	adds r2, r2, r4
	mov r9, r2
	mov r2, r10
	adds r2, r2, r5
	mov r10, r2
	pop {r2}
	muls r6, r6, r2		@r
	muls r7, r7, r2		@r
	mov r2, r11		@r
	adds r2, r2, r6
	mov r11, r2
	mov r2, r12
	adds r2, r2, r7
	mov r12, r2
	cmp r3, r8
	bne __dft_xun_huan
	ldr r0, = fan_she_shi_bu
	ldr r1, = fan_she_xu_bu
	mov r2, r9
	mov r3, r10
	mov r4, r11
	mov r5, r12
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	asrs r4, r4, # 6
	asrs r5, r5, # 6
	str r2, [r0]		@r
	str r3, [r0, # 0x04]	@r
	str r4, [r1]		@i
	str r5, [r1, # 0x04]	@i
	pop {r0-r4}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
	mov r12, r4
	pop {r0-r7,pc}
	.ltorg
__zu_kang_ji_suan:
	push {r4-r7,lr}
	@入口R0=反射实部 R1=反射虚部,R2=入射实部 R3=入射虚部
	@出口R1=电抗 R2=电阻
__ji_suan_zu_kang:
	@ Z=50*[(a+bi)/(c+di)]=50*[(ac+bd)/(c*c+d*d)+(bc-ad)/(c*c+d*d)]
	ldr r4, = 1000
	movs r0, r0
	bpl __fansheshibubushifushu
	mvns r0, r0
	adds r0, r0, # 1
	muls r0, r0, r4
	mvns r0, r0
	b __xubupanduan
__fansheshibubushifushu:
	muls r0, r0, r4
__xubupanduan:
	movs r1, r1
	bpl __fanshexububushifushu
	mvns r1, r1
	adds r1, r1, # 1
	muls r1, r1, r4
	mvns r1, r1
	b __ji_suan_fu_shu
__fanshexububushifushu:
	muls r1, r1, r4
	
__ji_suan_fu_shu:
	mov r4, r0
	mov r5, r1
	mov r6, r2
	mov r7, r3

	mov r1, r2
	bl __chengfa	  @ac
	mov r2, r0
	mov r3, r1
	
	mov r0, r5
	mov r1, r7
	bl __chengfa	    @ bd
	
	adds r0, r0, r2	     @ac+bd
	adcs r1, r1, r3
	mov r8, r0
	mov r9, r0
	
	mov r0, r6
	mov r1, r6
	bl __chengfa	    @c*c
	mov r2, r0
	mov r3, r1

	mov r0, r7
	mov r1, r7
	bl __chengfa	      @d*d
	
	adds r0, r0, r2	
	adds r1, r1, r3		@c*c+d*d

	
	
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
	adds r1, r1, # 1	@虚
__a6:	
	pop {r2}		@实
	pop {r4-r7,pc}
	
	
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

_zhuanshumaguanma:@ 16进制转数码管码
	@ R0要转的数据， R1长度，R2结果表首地址
	@ r3 小数点位置
	push {r4-r7,lr}
	ldr r7, = shumaguanmabiao
	mov r5, r0
	mov r6, r1
	movs r1, # 10
	mov r8, r3
_xunhuanqiuma:
	bl _chufa
	mov r4, r0
	muls r4, r1
	subs r3, r5, r4
	lsls r3, # 2
	ldr r4, [r7, r3]
	cmp r6, r8
	beq __tian_jia_xiao_shu_dian
	b __bao_cun_shu_ma_guan_ma
__tian_jia_xiao_shu_dian:
	adds r4, r4, # 1
__bao_cun_shu_ma_guan_ma:	
	str r4, [r2]
	mov r5, r0
	adds r2, r2, # 4
	subs r6, # 1
	bne _xunhuanqiuma
	pop {r4-r7,pc}
_xieshumaguan: @ r0=位数 @数码管码
	push {r1-r7,lr}
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
	pop {r1-r7,pc}
	
_xie595: @ R0=要写的数据
	push {r1-r7,lr}
	mov r5, r0
	movs r0, # 0x08      @pa6
	movs r7, # 0x10      @pa7
	movs r6, # 0x04      @pa5 
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
	pop {r1-r7,pc}


_yanshi:
	push {r7}
	ldr r7, = 30
_yanshi11:
	subs r7, # 1
	bne _yanshi11
	pop {r7}
	bx lr

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
__chu_fa:	@带符号
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
__he_cheng_dian_ya_biao:
	push {r0-r5,lr}
        ldr r0, = dianyabiao
	subs r0, r0, # 0x08
__zhao_shang_sheng:
	adds r0, r0, # 0x08
	ldrh r2, [r0, # 0x04]
	cmp r2, # 0
	bne __zhao_shang_sheng
	ldrh r3, [r0, # 0x0c]
	subs r2, r2, r3
	bpl __zhao_shang_sheng
	ldr r1, = dianyabiaozhizhen
	str r0, [r1]
        ldr r1, = 256
        lsls r1, r1, # 2
        movs r2, # 0
__fu_zhi_xun_huan:
        ldr r3, [r0, r2]
        mov r4, r3
        lsls r3, r3, # 16
        lsrs r3, r3, # 16
        lsrs r4, r4, # 16
	subs r3, r3, r4
        bpl __bao_cun
        mvns r3, r3
        adds r3, r3, # 1
        bl __zhuan_bcd
        ldr r4, = 0x80000000
        orrs r3, r3, r4
        b __fu_shu_bao_cun
__bao_cun:
	bl __zhuan_bcd
__fu_shu_bao_cun:
        str r3, [r0, r2]
	adds r2, r2, # 4
	cmp r2, r1
        bne __fu_zhi_xun_huan
	pop {r0-r5,pc}
__jian_bo:
       push {r0-r5,lr}
        ldr r0, = dianyabiao
        subs r0, r0, # 0x08
__zhao_shang_sheng1:
        adds r0, r0, # 0x08
	ldrh r2, [r0, # 0x04]
	cmp r2, # 0
        bne __zhao_shang_sheng1
	ldrh r3, [r0, # 0x0c]
        subs r2, r2, r3
        bpl __zhao_shang_sheng1
        ldr r1, = dianyabiaozhizhen
        str r0, [r1]
        ldr r1, = 256
        lsls r1, r1, # 2
        movs r2, # 0
__fu_zhi_xun_huan1:
        ldr r3, [r0, r2]
        mov r4, r3
        lsls r3, r3, # 16
        lsrs r3, r3, # 16
        lsrs r4, r4, # 16
        subs r3, r3, r4
        str r3, [r0, r2]
	adds r2, r2, # 4
	cmp r2, r1
        bne __fu_zhi_xun_huan1
	pop {r0-r5,pc}

__zhuan_bcd:
	push {r0-r2,r4-r7,lr}
	movs r1, # 10
	mov r0, r3
	mov r5, r3
	movs r6, # 8
__bcd_xun_huan:
	bl _chufa
	mov r4, r0
	muls r4, r4, r1
	subs r5, r5, r4
	push {r5}
	mov r5, r0
	subs r6, r6, # 1
	bne __bcd_xun_huan
	pop {r0-r7}
	lsls r6, r6, # 4
	lsls r5, r5, # 8
	lsls r4, r4, # 12
	lsls r3, r3, # 16
	lsls r2, r2, # 20
	lsls r1, r1, # 24
	lsls r0, r0, # 28
	orrs r3, r3, r0
	orrs r3, r3, r1
	orrs r3, r3, r2
	orrs r3, r3, r4
	orrs r3, r3, r5
	orrs r3, r3, r6
	orrs r3, r3, r7
	pop {r0-r2,r4-r7,pc}
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
_tim3:
	ldr r0, = jishu2
	ldr r1, [r0]
	adds r1, r1, #1
	str r1, [r0]
_tim3fanhui:
	ldr r0, = 0x40000400
	movs r1, # 0
	str r1, [r0, # 0x10]
	bx lr
_systickzhongduan:
	ldr r0, = 0x40020000
        ldr r1, =  86
        str r1, [r0, # 0x0c]
        ldr r1, = 0xa83 @ 0xaa3 @ 5a1
        str r1, [r0, # 0x08]

	
	ldr r0, = 0xe0000d04
	ldr r1, = 0x02000000
	str r1, [r0]                 @ 清除SYSTICK中断
	bx lr
__dma_wan:
	push {lr}
	bl __dft
	ldr r0, = fan_she_shi_bu
	ldr r1, = fan_she_xu_bu
	ldr r2, = ru_she_shi_bu
	ldr r3, = ru_she_xu_bu
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	ldr r3, [r3]
	bkpt # 1
	bl __zu_kang_ji_suan
	bkpt # 1
	ldr r0, = 0x40020000
        movs r2, # 2
	str r2, [r0, # 0x04]
	ldr r0, = dianyabiaoman
	movs r1, # 1
	str r1, [r0]
__dma_fan_hui:
	pop {pc}
