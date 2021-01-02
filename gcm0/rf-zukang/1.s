	@@单片机stm32f030f4p6
	@@ 阻抗
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
xiao_shu_dian_wei_zhi:
	.int 0xff,1,1,0xff,3
	     .align 4
xuanzhuanyinzi:
	.int 0x8000,0x0000,0x7D8A,0xFFFFE708,0x7641,0xFFFFCF05,0x6A6D,0xFFFFB8E4,0x5A82,0xFFFFA57E,0x471C,0xFFFF9593,0x30FB,0xFFFF89BF,0x18F8,0xFFFF8276,0x0000,0xFFFF8000,0xFFFFE708,0xFFFF8276,0xFFFFCF05,0xFFFF89BF,0xFFFFB8E4,0xFFFF9593,0xFFFFA57E,0xFFFFA57E,0xFFFF9593,0xFFFFB8E4,0xFFFF89BF,0xFFFFCF05,0xFFFF8276,0xFFFFE708,0xFFFF8000,0x0000,0xFFFF8276,0x18F8,0xFFFF89BF,0x30FB,0xFFFF9593,0x471C,0xFFFFA57E,0x5A82,0xFFFFB8E4,0x6A6D,0xFFFFCF05,0x7641,0xFFFFE708,0x7D8A,0x0000,0x8000,0x18F8,0x7D8A,0x30FB,0x7641,0x471C,0x6A6D,0x5A82,0x5A82,0x6A6D,0x471C,0x7641,0x30FB,0x7D8A,0x18F8,0x8000,0x0000,0x7D8A,0xFFFFE708,0x7641,0xFFFFCF05,0x6A6D,0xFFFFB8E4,0x5A82,0xFFFFA57E,0x471C,0xFFFF9593,0x30FB,0xFFFF89BF,0x18F8,0xFFFF8276,0x0000,0xFFFF8000,0xFFFFE708,0xFFFF8276,0xFFFFCF05,0xFFFF89BF,0xFFFFB8E4,0xFFFF9593,0xFFFFA57E,0xFFFFA57E,0xFFFF9593,0xFFFFB8E4,0xFFFF89BF,0xFFFFCF05,0xFFFF8276,0xFFFFE708,0xFFFF8000,0x0000,0xFFFF8276,0x18F8,0xFFFF89BF,0x30FB,0xFFFF9593,0x471C,0xFFFFA57E,0x5A82,0xFFFFB8E4,0x6A6D,0xFFFFCF05,0x7641,0xFFFFE708,0x7D8A,0x0000,0x8000,0x18F8,0x7D8A,0x30FB,0x7641,0x471C,0x6A6D,0x5A82,0x5A82,0x6A6D,0x471C,0x7641,0x30FB,0x7D8A,0x18F8,0x8000,0x0000,0x7D8A,0xFFFFE708,0x7641,0xFFFFCF05,0x6A6D,0xFFFFB8E4,0x5A82,0xFFFFA57E,0x471C,0xFFFF9593,0x30FB,0xFFFF89BF,0x18F8,0xFFFF8276,0x0000,0xFFFF8000,0xFFFFE708,0xFFFF8276,0xFFFFCF05,0xFFFF89BF,0xFFFFB8E4,0xFFFF9593,0xFFFFA57E,0xFFFFA57E,0xFFFF9593,0xFFFFB8E3,0xFFFF89BF,0xFFFFCF05,0xFFFF8276,0xFFFFE708,0xFFFF8000,0x0000,0xFFFF8276,0x18F8,0xFFFF89BF,0x30FB,0xFFFF9593,0x471C,0xFFFFA57E,0x5A82,0xFFFFB8E3,0x6A6D,0xFFFFCF05,0x7641,0xFFFFE708,0x7D8A,0x0000,0x8000,0x18F8,0x7D8A,0x30FB,0x7641,0x471C,0x6A6D,0x5A82,0x5A82,0x6A6D,0x471D,0x7641,0x30FB,0x7D8A,0x18F8,0x8000,0x0000,0x7D8A,0xFFFFE708,0x7641,0xFFFFCF05,0x6A6D,0xFFFFB8E4,0x5A82,0xFFFFA57E,0x471D,0xFFFF9593,0x30FB,0xFFFF89BF,0x18F8,0xFFFF8276,0x0000,0xFFFF8000,0xFFFFE708,0xFFFF8276,0xFFFFCF05,0xFFFF89BF,0xFFFFB8E4,0xFFFF9593,0xFFFFA57E,0xFFFFA57E,0xFFFF9593,0xFFFFB8E3,0xFFFF89BF,0xFFFFCF05,0xFFFF8276,0xFFFFE708,0xFFFF8000,0x0000,0xFFFF8276,0x18F8,0xFFFF89BF,0x30FB,0xFFFF9593,0x471C,0xFFFFA57E,0x5A82,0xFFFFB8E3,0x6A6D,0xFFFFCF05,0x7641,0xFFFFE708,0x7D8A,0x0000,0x8000,0x18F8,0x7D8A,0x30FB,0x7641,0x471C,0x6A6D,0x5A82,0x5A82,0x6A6D,0x471D,0x7641,0x30FB,0x7D8A,0x18F8
	.align 4
cai_dan_biao:
	.word __cai_dan_0
	.word __cai_dan_1
	.word __cai_dan_2
	.word __cai_dan_3
	.word __cai_dan_4
	.word __cai_dan_5
	.word __cai_dan_6
yjmwxwx:
	.equ STACKINIT,        	        0x20001000
	.equ shumaguanma,		0x20000000
	.equ fuhao,			0x20000010
	.equ dmawan,			0x200000f4
	.equ jishu2,			0x200000f8
	.equ jishu,			0x200000fc
	.equ dianzu,			0x20000100
	.equ p_shibu,			0x20000104
	.equ swr_shibu,			0x20000108
	.equ bingliandianzu,		0x2000010c
	.equ jiedianchangshushibu,	0x20000110
	.equ diankang,			0x20000114
	.equ p_xubu,			0x20000118
	.equ swr_xubu,			0x2000011c
	.equ bingliandiankang,		0x20000120
	.equ jiedianchangshuxubu,	0x20000124
	.equ fan_she_shi_bu,		0x20000128
	.equ fan_she_xu_bu,		0x20000130
	.equ ru_she_shi_bu,		0x20000138
	.equ ru_she_xu_bu,		0x2000013c
        .equ zukangqiehuan,             0x20000140
        .equ caidan,                    0x20000144
        .equ an_jian_yan_shi,           0x20000148
        .equ tou_fan_qie_huan,          0x2000014c
	.equ dianrongzhi,		0x20000150
	.equ kai_lu_r,			0x20000154
	.equ kai_lu_i,			0x20000158
	.equ duan_lu_r,			0x2000015c
	.equ duan_lu_i,			0x20000160
	.equ pi_pei_r,			0x20000164
	.equ pi_pei_i,			0x20000168
	.equ anjianma,			0x2000016c
	.equ caidanzhizhen,		0x20000170
	.equ caidanyanshi,		0x20000174

	.equ pm1,			0x20000178
	.equ pm1i,			0x2000017c
	.equ pm2,			0x20000180
	.equ pm2i,			0x20000184
	.equ pm3,			0x20000188
	.equ pm3i,			0x2000018c
	.equ kailu_r,			0x20000190
	.equ kailu_i,			0x20000194
	.equ duanlu_r,			0x20000198
	.equ duanlu_i,			0x2000019c
	.equ pipei_r,			0x200001a0
	.equ pipei_i,			0x200001a4
	.equ caidanzhizhen,		0x200001a8
	.equ jiaozhunkaiguan,		0x200001ac


	
        .equ dianyabiaozhizhen,         0x200001f8
        .equ dianyabiaoman,             0x200001fc
	.equ dianyabiao,		0x20000200
        .equ lvboqizhizhen,             0x20000a00
        .equ lvboqihuanchong,           0x20000a04
        .equ lvboqizhizhen1,            0x20000b30
        .equ lvboqihuanchong1,          0x20000b34
        .equ lvboqizhizhen2,             0x20000c60
        .equ lvboqihuanchong2,           0x20000c64
	.equ lvboqizhizhen3,            0x20000d90
        .equ lvboqihuanchong3,          0x20000d94
	.equ kai_lu_r,			0x08002000
	.equ kai_lu_i,			0x08002004
	.equ duan_lu_r,			0x08002008
	.equ duan_lu_i,			0x0800200c
	.equ pi_pei_r,			0x08002010
	.equ pi_pei_i,			0x08002014
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
	ldr r3, = 0x1000
	movs r1, # 0
	mov r4, r1
neicunqinglingxunhuan:
	str r1, [r0, r4]
	adds r4, r4, # 4
	cmp r4, r3
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
	ldr r2, = 0x902
	str r2, [r0, # 0x1c]

_waishezhongduan:				@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效

	ldr r0, =  0xe000e100
	ldr r1, = 0x200 @0x10200  @ 0x10000
	str r1, [r0]
	
@_kanmengou:
@	ldr r0, = 0x40003000
@	ldr r1, = 0x5555
@	str r1, [r0]
@	movs r1, # 7
@	str r1, [r0, # 4]
@	ldr r1, = 0xfff
@	str r1, [r0, # 8]
@	ldr r1, = 0xaaaa
@	str r1, [r0]
@	ldr r1, = 0xcccc
@	str r1, [r0]

_adcchushihua:
        ldr r0, = 0x40012400  @ adc基地址
        ldr r1, = 0x80000000
        str r1, [r0, # 0x08]  @ ADC 控制寄存器 (ADC_CR)  @adc校准
_dengadcjiaozhun:
        ldr r1, [r0, # 0x08]
        movs r1, r1
        bmi _dengadcjiaozhun   @ 等ADC校准
	movs r1, # 1
	str r1, [r0]
_kaiadc:
        ldr r1, [r0, # 0x08]
        movs r2, # 0x01
        orrs r1, r1, r2
        str r1, [r0, # 0x08]
_deng_adc_wen_ding:
        ldr r1, [r0]
        lsls r1, r1, # 31
        bpl _deng_adc_wen_ding @ 等ADC稳定
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
	ldr r1, = 699		@2.5k 11199
	str r1, [r0, # 0x2c] @ ARR
	ldr r1, =  0x3800 @ 0x3800
	str r1, [r0, # 0x1c] @ ccmr2
	ldr r1, =  0x1000
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 699
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
	       ldr r0, = 0x40000400@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	ldr r0, = 0x48000000
	ldr r1, = 0x28203d5f
	str r1, [r0]
	ldr r1, = 0x200
	str r1, [r0, # 0x24]
	ldr r1, = 0x44000
	str r1, [r0, # 0x0c]

	ldr r0, = tou_fan_qie_huan
	ldr r1, = 0xffff      @反射=0xffff 透射=0x7fff
	str r1, [r0]

	
	
	ldr r0, = 0xffff
__deng_dma_man:
	subs r0, r0, # 1
	bne __deng_dma_man
ting:
	ldr r0, = anjianma
	movs r1, # 1
	str r1, [r0]

__cai_dan_0:
	bl __d_m_a
	bl __an_jian
	cmp r0, # 0
	bne __zu_kang_xian_shi
	bl __cai_dan_diao_du
__zu_kang_xian_shi:	
	bl __cai_dan_anjian
	cmp r0, # 1
	beq __xian_shi_r
	cmp r0, # 2
	beq __xian_shi_i
	b __cai_dan_0
__xian_shi_r:
	ldr r0, =  dianzu
	movs r3, # 0xff
	b __xian_shi_zu_kang
__xian_shi_i:
	ldr r0, = diankang
	movs r3, # 0xff
__xian_shi_zu_kang:	
	bl __led_xian_shi
	b __cai_dan_0
__cai_dan_1:
        bl __d_m_a
	bl __an_jian
	cmp r0, # 0
        bne __fan_she_xian_shi
        bl __cai_dan_diao_du
__fan_she_xian_shi:
        bl __cai_dan_anjian
        cmp r0, # 1
        beq __xian_shi_fan_she_r
        cmp r0, # 2
        beq __xian_shi_fan_she_i
        b __cai_dan_1
__xian_shi_fan_she_r:
	ldr r0, = p_shibu
        movs r3, # 1
        b __xian_shi_fan_she
__xian_shi_fan_she_i:
	ldr r0, = p_xubu
	movs r3, # 1
__xian_shi_fan_she:
        bl __led_xian_shi
        b __cai_dan_1

__cai_dan_2:
	movs r6, # 0
	ldr r7, = 3000
__jiao_zhun_kai_lu:	
	ldr r0, = jiaozhunkaiguan
	movs r1, # 1
	str r1, [r0]
	bl __d_m_a
        ldr r0, = p_shibu
        movs r3, # 1
        bl __led_xian_shi
	bl __an_jian
	cmp r0, # 2
	bne __bao_cun_kai_lu_jian_ce
	adds r6, r6, # 1
	cmp r6, r7
	bls __bao_cun_kai_lu_jian_ce
	ldr r0, = caidanzhizhen
        ldr r2, = jiaozhunkaiguan
  	movs r1, # 0
	str r1, [r0]
	str r1, [r2]
	b __cai_dan_0
__bao_cun_kai_lu_jian_ce:	
	cmp r0, # 0
	bne __jiao_zhun_kai_lu
	ldr r0, = p_shibu
	ldr r1, = p_xubu
	ldr r2, = pm1
	ldr r3, = pm1i
	ldr r0, [r0]
	ldr r1, [r1]
	str r0, [r2]
	str r1, [r3]
	bl __cai_dan_diao_du
	b __jiao_zhun_kai_lu
__cai_dan_3:
        ldr r0, = p_shibu
        movs r3, # 1
        bl __led_xian_shi
	bl __d_m_a
	bl __an_jian
	cmp r0, # 0
	bne __cai_dan_3
        ldr r0, = p_shibu
        ldr r1, = p_xubu
        ldr r2, = pm2
        ldr r3, = pm2i
        ldr r0, [r0]
        ldr r1, [r1]
        str r0, [r2]
        str r1, [r3]
	bl __cai_dan_diao_du
	b __cai_dan_3
__cai_dan_4:
	ldr r0, = 0xffffff
__cai_dan_3_yanshi:
	subs r0, r0, # 1
	bne __cai_dan_3_yanshi
__cai_dan_3_xun_huan:
        ldr r0, = p_shibu
        movs r3, # 1
        bl __led_xian_shi
	bl __d_m_a
        bl __an_jian
        cmp r0, # 0
        bne __cai_dan_3_xun_huan
        ldr r0, = p_shibu
        ldr r1, = p_xubu
        ldr r2, = pm3
        ldr r3, = pm3i
        ldr r0, [r0]
        ldr r1, [r1]
        str r0, [r2]
        str r1, [r3]
	bl __jiaozhun
	ldr r0, = jiaozhunkaiguan
	movs r1, # 0
	str r1, [r0]
	ldr r0, = 0x3ffffff
__xie_flash_yan_shi:
	subs r0, r0, # 1
	bne __xie_flash_yan_shi
	b _xieflash
__cai_dan_5:
__cai_dan_6:
	b __cai_dan_2
	
__cai_dan_anjian:
	push {r1,lr}
	ldr r1, = anjianma
        bl __an_jian
	cmp r0, # 1
	beq __r_bao_cun
	cmp r0, # 2
	beq __i_bao_cun
	b __an_jian_fan_hui
__r_bao_cun:
	movs r0, # 1
	b __bao_cun_anjian
__i_bao_cun:
	movs r0, # 2
__bao_cun_anjian:
	str r0, [r1]
__an_jian_fan_hui:
	ldr r0, [r1]
	pop {r1,pc}
	

__cai_dan_diao_du:
        mov r12, lr
        ldr r1, = caidanzhizhen
        ldr r0, = caidanyanshi
        ldr r2, [r1]
        ldr r3, [r0]
        adds r3, r3, #1
	cmp r3, # 10	@菜单切换延时
        bhi __cai_dan_zhi_zhen_jia
        str r3, [r0]
        mov pc, r12
__cai_dan_zhi_zhen_jia:
        movs r3, # 0
        str r3, [r0]
        adds r2, r2, # 4
	cmp r2, # 0x14
        bls __cai_dan_qie_huan
        movs r2, # 0
__cai_dan_qie_huan:
        str r2, [r1]
	mov r4, r2
        mov r0, r2
	lsrs r0, r0, # 2
	movs r3, # 0xff
	movs r1, # 5
	ldr r2, = shumaguanma
	bl _zhuanshumaguanma
__cai_dan_xian_shi:	
        movs r0, # 5
	bl _xieshumaguan
	bl __an_jian
	cmp r0, # 1
	bne __cai_dan_xian_shi
	mov r2, r4
        ldr r0, = cai_dan_biao
        ldr r1, [r0, r2]
	mov pc, r1
	.ltorg
__led_xian_shi:
	@入口R0=显示数据地址 R3=小数点位置
	push {r0-r5,lr}
	ldr r0, [r0]
	movs r0, r0
	bpl __zheng_led_xian_shi
	mvns r0, r0
	adds r0, r0, # 1
	ldr r4, = fuhao
	movs r5, # 0x02
	str r5, [r4]
	b __fu_led_xian_shi
__zheng_led_xian_shi:
	ldr r4, = fuhao
	movs r5, # 0
	str r5, [r4]
__fu_led_xian_shi:	
	movs r1, # 4
        ldr r2, = shumaguanma
        bl _zhuanshumaguanma
	movs r0, # 5
        bl _xieshumaguan
	pop {r0-r5,pc}
__d_m_a:
	push {r0-r2,lr}
        ldr r0, = jishu
        ldr r1, = 0x60
        ldr r2, [r0]
        adds r2, r2, # 1
        str r2, [r0]
        cmp r2, r1
        bne __d_m_a_fanhui
        movs r2, # 0
        str r2, [r0]
        bl __kai_dma
__d_m_a_fanhui:
	pop {r0-r2,pc}

__dma:
	push {r0-r1,lr}
        ldr r5, = 0x200008c0
	cpsid i
__deng_dma_wan:
       movs r0, # 5
       bl _xieshumaguan
        ldr r1, [r5]
        cmp r1, # 0
        beq __deng_dma_wan
	cpsie i
        ldr r2, = 0x40000400
        movs r1, # 0
        str r1, [r2]
        bl __dma_wan
        ldr r0, = 0x200008c0
        movs r1, # 0
        str r1, [r0]
        movs r1, # 0xe1
	str r1, [r2]
	pop {r0-r1,pc}
_xieflash:			@ flsh解锁
	ldr r0, = 0x40022000
	ldr r1, = 0x45670123
	str r1, [r0, # 0x04]
	ldr r1, = 0xcdef89ab
	str r1, [r0, # 0x04]
					@擦除2页
	movs r5, # 1
	ldr r4, = 0x8002000
	movs r7, # 1
	lsls r7, r7, # 10
_flashmang:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang
	movs r1, # 2
	str r1, [r0, # 0x10]
	str r4, [r0, # 0x14]
	movs r1, # 0x42
	str r1, [r0, # 0x10]
	add r4, r4, r7
	subs r5, # 1
	bne _flashmang
						@写FLASH
	ldr r7, = 0x8002000
	ldr r4, = kailu_r
	movs r5, # 0
	movs r6, # 0x06
_flashmang1:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang1
	movs r1, # 1
	str r1, [r0, # 0x10]
	ldrh r3, [r4, r5]
	strh r3, [r7, r5]
	adds r5, r5, # 2
_flashmang2:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang2
	ldrh r3, [r4, r5]
	strh r3, [r7, r5]
	adds r5, r5, # 2
	subs r6, r6, # 1
	bne _flashmang1
_flashmang4:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang4
	movs r1, # 0x80
	@str r1, [r0]          		@flsh上锁
	ldr r0, = 0xe000ed0c
	ldr r1, = 0x05fa0004
	str r1, [r0]          		@复位
__jiaozhun:	@校准开路短路匹配误差
	push {r0-r7,lr}
	bl __det
	mov r2, r0
	mov r3, r1
	mov r6, r2
	mov r7, r3
	bl __det1
	mov r3, r1
	ldr r1, = 1000
	bl __chu_fa
	mov r4, r0
	mov r0, r3
	bl __chu_fa
	mov r1, r0
	mov r0, r4
	mov r2, r6
	mov r3, r7
	bl __fu_shu_chu_fa
	ldr r4, = kailu_r
	ldr r5, = kailu_i
	str r2, [r4]
	str r1, [r5]
	bl __det2
	mov r2, r6
	mov r3, r7
	bl __fu_shu_chu_fa
	ldr r4, = duanlu_r
	ldr r5, = duanlu_i
	str r2, [r4]
	str r1, [r5]
	bl __det3
	mov r4, r1
	ldr r1, = 1000
	bl __chu_fa
	mov r3, r0
	mov r0, r4
	bl __chu_fa
	mov r1, r0
	mov r0, r3
	mov r2, r6
	mov r3, r7
	bl __fu_shu_chu_fa
	ldr r4, = pipei_r
	ldr r5, = pipei_i
	str r2, [r4]
	str r1, [r5]
	pop {r0-r7,pc}
__det:
	push {r2-r7,lr}
	@a b c
	@d e f
	@g h i
	@a*e
	@ae*i=0
	@b*f
	ldr r0, = pm1
	ldr r1, = pm1i
	ldr r0, [r0]
	ldr r1, [r1]
	@bf*g
	@d*h=0
	@dh*c=0
	@g*e
	ldr r2, = pm2
	ldr r3, = pm2i
	ldr r2, [r2]
	ldr r3, [r3]
	@ge*c
	@h*f=0
	@hf*a=0
	@d*b
	@db*i=0
	@a*e*i+b*f*g+d*h*c-g*e*c-h*f*a-d*b*i
	subs r0, r0, r2
	subs r1, r1, r3
	pop {r2-r7,pc}
__det1:
        push {r2-r7,lr}
        @a b c
        @d e f
        @g h i
        @a*e
        @ae*i=0
        @b*f
        ldr r0, = pm1
        ldr r1, = pm1i
        ldr r0, [r0]
        ldr r1, [r1]
        @bf*g
	ldr r2, = pm3
	ldr r3, = pm3i
	ldr r2, [r2]
	ldr r3, [r3]
	mov r4, r2
	mov r5, r3
	bl __fu_shu_cheng_fa
	mov r6, r0
	mov r7, r1
        @d*h=0
        @dh*c=0
        @g*e
        ldr r0, = pm2
        ldr r1, = pm2i
        ldr r0, [r0]
        ldr r1, [r1]
	mov r2, r4
	mov r3, r5
	bl __fu_shu_cheng_fa
        @ge*c
        @h*f=0
        @hf*a=0
        @d*b
        @db*i=0
        @a*e*i+b*f*g+d*h*c-g*e*c-h*f*a-d*b*i
        subs r6, r6, r0
        subs r7, r7, r1
	mov r0, r6
	mov r1, r7
        pop {r2-r7,pc}
__det2:	
        push {r2-r7,lr}
        @a b c
        @d e f
        @g h i
        @a*e
        @ae*i=0
        @b*f
        ldr r0, = pm1
        ldr r1, = pm1i
        ldr r0, [r0]
        ldr r1, [r1]
        @bf*g
        @d*h
	ldr r4, = pm3
	ldr r5, = pm3i
	ldr r4, [r4]
	ldr r5, [r5]
        @dh*c
	mvns r4, r4
	adds r4, r4, # 1
	mvns r5, r5
	adds r5, r5, # 1
        @g*e
        ldr r2, = pm2
        ldr r3, = pm2i
        ldr r2, [r2]
        ldr r3, [r3]
        @ge*c
	mvns r2, r2
	adds r2, r2, # 1
	mvns r3, r3
	adds r3, r3, # 1
	@h*f
	ldr r6, = pm3
	ldr r7, = pm3i
	ldr r6, [r6]
	ldr r7, [r7]
        @hf*a
        @d*b
	@db*i=0
	@a*e*i+b*f*g+d*h*c-g*e*c-h*f*a-d*b*i
	adds r0, r0, r4
	adds r1, r1, r5
	subs r0, r0, r2
	subs r1, r1, r3
	subs r0, r0, r6
	subs r1, r1, r7
	pop {r2-r7,pc}
__det3:
        push {r2-r7,lr}
        @a b c
        @d e f
        @g h i
        @a*e
	ldr r0, = pm2
	ldr r1, = pm2i
	ldr r0, [r0]
	ldr r1, [r1]
	mov r4, r0
	mov r5, r1
	mvns r0, r0
	adds r0, r0, # 1
	mvns r1, r1
	adds r1, r1, # 1
        @ae*i
	ldr r2, = pm3
	ldr r3, = pm3i
	ldr r2, [r2]
	ldr r3, [r3]
	bl __fu_shu_cheng_fa
	push {r0-r1}
        @b*f
        ldr r0, = pm1
        ldr r1, = pm1i
        ldr r0, [r0]
        ldr r1, [r1]
	mov r6, r0
	mov r7, r1
	mov r2, r4
	mov r3, r5
	bl __fu_shu_cheng_fa
	push {r0-r1}
        @bf*g
        @d*h=0
        @dh*c=0
        @g*e
	mov r0, r6
	mov r1, r7
	mvns r2, r4
	adds r2, r2, # 1
	mvns r3, r5
	adds r3, r3, # 1
        @ge*c
	bl __fu_shu_cheng_fa
	push {r0-r1}
	@h*f=0
        @hf*a=0
        @d*b
	mov r2, r6
	mov r3, r7
	@db*i
	ldr r0, = pm3
	ldr r1, = pm3i
	ldr r0, [r0]
	ldr r1, [r1]
	bl __fu_shu_cheng_fa
	mov r6, r0
	mov r7, r1
	pop {r4-r5}
	pop {r2-r3}
	pop {r0-r1}
	@a*e*i+b*f*g+d*h*c-g*e*c-h*f*a-d*b*i
	adds r0, r0, r2
	adds r1, r1, r3
	subs r0, r0, r4
	subs r1, r1, r5
	subs r0, r0, r6
	subs r1, r1, r7
	pop {r2-r7,pc}
__fu_shu_cheng_fa:
	push {r2-r7,lr}
	@r0=a,r1=b,r2=c,r3=d
        mov r4, r0      @a
        mov r5, r1      @b
	mov r6, r2	@c
	mov r7, r3	@d
        muls r0, r0, r2 @a*c
	muls r1, r1, r3 @b*d
        subs r0, r0, r1 @ac-bd
        muls r4, r4, r7 @a*d
        muls r5, r5, r6 @b*c
        adds r4, r4, r5 @ad+bc
	mov r1, r4
	pop {r2-r7,pc}
	.ltorg
__osm_jiao_zhun:
	push {r0,r3-r7,lr}
	ldr r0, = p_shibu
	ldr r1, = p_xubu
	ldr r0, [r0]
	ldr r1, [r1]
@	ldr r0, = -188
@	ldr r1, = 247
	mov r4, r0	@a
	mov r5, r1	@b
	ldr r2, = kai_lu_r 	@开路R
	ldr r3, = kai_lu_i	@开路I
	ldr r2, [r2]
	ldr r3, [r3]
	ldr r6, = duan_lu_r	@c	@短路R
	ldr r7, = duan_lu_i	@d	@短路I
	ldr r6, [r6]
	ldr r7, [r7]
	subs r0, r0, r2
	subs r1, r1, r3
	mov r2, r4	@a
	mov r3, r5	@b
	muls r4, r4, r6	@a*c
	muls r5, r5, r7	@b*d
	subs r4, r4, r5	@ac-bd
	muls r2, r2, r7	@a*d
	muls r3, r3, r6	@b*c
	adds r2, r2, r3	@ad+bc
	mov r7, r0
	mov r3, r1
	mov r0, r4
	ldr r1, = 1000
	bl __chu_fa
	mov r4, r0
	mov r0, r2
	ldr r1, = 1000
	bl __chu_fa
	mov r2, r0
	ldr r5, = pi_pei_r		@50欧姆R
	ldr r6, = pi_pei_i		@50欧姆I
	ldr r5, [r5]
	ldr r6, [r6]
	subs r4, r4, r5
	subs r2, r2, r6
	mov r0, r7
	mov r1, r3
	mov r3, r2
	mov r2, r4
	bl __fu_shu_chu_fa
	ldr r4, = p_shibu
	ldr r5, = p_xubu
	str r1, [r5]
	str r2, [r4]
	pop {r0,r3-r7,pc}
	.ltorg
__fu_jie_dian_chang_shu:	@复介电常数
	@阻抗计算介电常数
	@r=串联电阻
	@x=串联电抗
	@jx=并联电抗
	@rp=并联电阻
	@cp=并联电容
	@a=电容面积
	@t=电容板距离
	@eo=自由空间的介电常数
	@er1=介电常数虚部
	@er=介电常数实部

	@r=880
	@x=-700
	@jx=(r^2*x)/(r^2+x^2)
	@w=1.7592918860102842*10^8
	@cp=1/(w*jx)
	@rp=(r*x^2)/(r^2+x^2)
	@a=1
	@t=1
	@eo=8.85*10^-12
	@er=t/(w*rp*a*eo)
	@er1=(t*cp)/(a*eo)
	push {r0-r5,lr}
	ldr r0, = bingliandianzu
	ldr r1, = bingliandiankang
	ldr r3, [r0]
	ldr r4, [r1]
	ldr r0, = 5242880	@q19 1*100
	ldr r1, = 816		@q19 w*eo
	muls r1, r1, r3
	ldr r2, = jiedianchangshushibu
	bl _chufa		@er=t/(w*rp*eo)
	str r0, [r2]
	ldr r2, = 1759291
	muls r2, r2, r4
	ldr r0, = 0x918
	ldr r1, = 0x4e72a000	@1
	bl __chufa64		@cp=1/(w*jx)
	ldr r0, = dianrongzhi
	str r1, [r0]
	mov r0, r1
	ldr r1, = 885		@eo
	bl _chufa		@er1=(t*cp)/(a*eo)
	ldr r1, = jiedianchangshuxubu
	str r0, [r1]
	pop {r0-r5,pc}

__chuan_lian_zhuan_bing_lian:   @串联转并联
        push {r0-r5,lr}
        ldr r0, = dianzu
        ldr r1, = diankang
        ldr r0, [r0]            @r
	ldr r1, [r1]            @i=x
	mov r4, r0
	muls r0, r0, r0		@r^2
	mov r5, r0
	mvns r1, r1
	adds r1, r1, # 1
	muls r0, r0, r1		@r^2*x
	muls r1, r1, r1		@x^2
	mov r3, r1
	add r1, r1, r5
	ldr r2, = bingliandiankang
	bl _chufa		@jx=(r^2*x)/(r^2+x^2)
	str r0, [r2]
	mov r0, r4
	muls r0, r0, r3		@r*x^2
	ldr r2, = bingliandianzu
	bl _chufa
	str r0, [r2]
        pop {r0-r5,pc}
	
__an_jian:
	push {r1,lr}
	ldr r0, = 0x48000010
	ldr r2, [r0]
	mov r0, r2
	lsls r2, r2, # 24
	lsrs r2, r2, # 31
	lsls r0, r0, # 22
	lsrs r0, r0, # 30
	orrs r0, r0, r2
	pop {r1,pc}
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
	ldrh r3, [r0, # 0x06]
	subs r3, r3, r2
        bmi __zhao_shang_sheng2
        ldrh r2, [r0, # 0x0c]
	ldrh r3, [r0, # 0x0e]
        subs r3, r3, r2
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
	ldr r2, [r1, r3]	@i
	adds r3, r3, # 4
	mov r6, r4
	mov r7, r5
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r6, r6, # 16
	lsls r5, r5, # 16
	lsrs r5, r5, # 16
	lsrs r7, r7, # 16

@	push {r3}
@	ldr r3, = 40747  @35181   @振幅矫正
	subs r4, r4, r6
@	muls r4, r4, r3
@	asrs r4, r4, # 15
@	pop {r3}
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
	asrs r6, r6, # 15
	asrs r7, r7, # 15
	mov r2, r11		@r
	adds r2, r2, r6
	mov r11, r2
	mov r2, r12
	adds r2, r2, r7
	mov r12, r2
	cmp r3, r8
	bne __dft_xun_huan
	mov r2, r9
	mov r3, r10
	mov r4, r11
	mov r5, r12
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	asrs r4, r4, # 6
	asrs r5, r5, # 6
	ldr r0, = fan_she_shi_bu
	ldr r1, = ru_she_shi_bu
	ldr r6, = fan_she_xu_bu
	ldr r7, = ru_she_xu_bu
	str r2, [r6]		@i
	str r3, [r7]	@i
	str r4, [r0]		@r
	str r5, [r1]	@r
__dft_fan_hui:	
	pop {r0-r4}
	mov r8, r0
	mov r9, r1
	mov r10, r2
	mov r11, r3
	mov r12, r4
	pop {r0-r7,pc}
	.ltorg
__fu_shu_chu_fa:
	push {r4-r7,lr}
	@入口R0=a R1=b,R2=c R3=d
	@出口R1=虚部 R2=实部
	mov r4, r8
	push {r4}
__ji_suan_chu_fa:
	@ Z=50*[(a+bi)/(c+di)]=50*[(ac+bd)/(c*c+d*d)+(bc-ad)/(c*c+d*d)]
	mov r4, r0
	mov r5, r1
	mov r6, r2
	@mov r7, r3
	mov r8, r3
	movs r7,  # 0
        movs r0, r0
        bpl b1
        mvns r0, r0
        adds r0, r0, # 1
        adds r7, r7, # 1

b1:
        movs r2, r2
        bpl b2
	mvns r2, r2
        adds r2, r2, # 1
        adds r7, r7, # 1
b2:
	muls r0, r0, r2
        cmp r7, # 1
        bne b3
        mvns r0, r0
        adds r0, r0, # 1
b3:
	@muls r0, r0, r2		@ac
        movs r7,  # 0
        movs r1, r1
        bpl b4
        mvns r1, r1
        adds r1, r1, # 1
        adds r7, r7, # 1

b4:
        movs r3, r3
        bpl b5
        mvns r3, r3
        adds r3, r3, # 1
        adds r7, r7, # 1
b5:
        muls r1, r1, r3
        cmp r7, # 1
        bne b6
        mvns r1, r1
        adds r1, r1, # 1
b6:

@	muls r1, r1, r3		@bd
	adds r0, r0, r1		@ac+bd
	movs r2, r2
	bpl b7
	mvns r2, r2
	adds r2, r2, # 1
	muls r2, r2, r2
	mvns r2, r2
	adds r2, r2, # 1
	b b8
b7:	
        muls r2, r2, r2         @c*c
b8:
	movs r3, r3
	bpl b9
	mvns r3, r3
	adds r3, r3, # 1
	muls r3, r3, r3
	mvns r3, r3
	adds r3, r3, # 1
	b b10
b9:	
	muls r3, r3, r3		@d*d
b10:	
	adds r2, r2, r3		@c*c+d*d
	ldr r1, = 1000
	movs r3, # 0
	movs r0, r0
	bpl a1
	mvns r0, r0
	adds r0, r0, # 1
	adds r3, r3, # 1
a1:
	movs r2, r2
	bpl a2
	mvns r2, r2
	adds r2, r2, # 1
	adds r3, r3, # 1
a2:
	bl __chengfa
	bl __chufa64		@(ac+bd)/(c*c+d*d)
	cmp r3, # 1
	bne a3
	mvns r1, r1
	adds r1, r1, # 1
a3:	
	push {r1}
	mov r7, r8
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
	adds r1, r1, # 1	@虚部
__a6:	
	pop {r2}		@实
	pop {r4}
	mov r8, r4
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
	ldr r1, = tou_fan_qie_huan
	ldr r5, = shumaguanma
	ldr r1, [r1]
	ldr r2, = shumaguanshuaxinbiao
_shumaguanshuaxin:
	ldr r3, [r5, r7]
	ldr r4, [r2, r7]
	orrs r4, r4, r3
	ands r4, r4, r1
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
	@ r0 除以 r1 等于 商(r0)
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
        ldrh r3, [r0, # 0x06]
        subs r3, r3, r2
        bmi __zhao_shang_sheng
        ldrh r2, [r0, # 0x0c]
        ldrh r3, [r0, # 0x0e]
        subs r3, r3, r2
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
        ldrh r3, [r0, # 0x06]
        subs r3, r3, r2
	bmi __zhao_shang_sheng1
        ldrh r2, [r0, # 0x0c]
        ldrh r3, [r0, # 0x0e]
        subs r3, r3, r2
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
@	bl __he_cheng_dian_ya_biao
@	bkpt # 22
	push {r0-r7,lr}
	bl __dft
	ldr r0, = fan_she_shi_bu
	ldr r1, = fan_she_xu_bu
	ldr r2, = ru_she_shi_bu
	ldr r3, = ru_she_xu_bu
	ldr r0, [r0]
	ldr r1, [r1]
	ldr r2, [r2]
	ldr r3, [r3]
	bl __fu_shu_chu_fa

	mov r3, r2
	mov r7, r1
        ldr r0, = lvboqihuanchong
        ldr r1, = 128
        ldr r2, = lvboqizhizhen
        bl _lvboqi

	mov r3, r7
	mov r7, r0

        ldr r0, = lvboqihuanchong2
        ldr r1, = 128
        ldr r2, = lvboqizhizhen2
        bl _lvboqi
	mov r1, r0
	mov r2, r7

	
	ldr r0, = p_shibu
	ldr r3, = p_xubu
	str r2, [r0]
	str r1, [r3]
	
	ldr r4, = jiaozhunkaiguan
	ldr r5, [r4]
	cmp r5, # 0
	bne  __jiao_zhun_kai
	bl __osm_jiao_zhun

__jiao_zhun_kai:
	ldr r1, = p_xubu
	ldr r2, = p_shibu
	ldr r5, [r1]
	ldr r4, [r2]
	ldr r0, = 1000
	movs r1, # 0
	mov r2, r0
	movs r3, # 0
	adds r0, r0, r4
	adds r1, r1, r5
	subs r2, r2, r4
	subs r3, r3, r5
	bl __fu_shu_chu_fa
	ldr r6, = swr_shibu
	ldr r5, = swr_xubu
	str r2, [r6]
	str r1, [r5]
	ldr r3, = 1638	@Q15 0.05
	muls r1, r1, r3
	muls r3, r3, r2
	asrs r1, r1, # 15
	asrs r3, r3, # 15
	ldr r2, = dianzu
        str r3, [r2]
        ldr r2, = diankang
        str r1, [r2]
	@bl __chuan_lian_zhuan_bing_lian
	@bl __fu_jie_dian_chang_shu
__dma_fan_hui:	
	ldr r0, = 0x40020000
        movs r2, # 2
	str r2, [r0, # 0x04]
	pop {r0-r7,pc}
