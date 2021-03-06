	@@ 单片机stm32f030f4p6						
	@作者：yjmwxwx
	@时间：2021-01-01
	@编译器：ARM-NONE-EABI
	.thumb
	.syntax unified
	.section .data
yjmwxwx:
	.ascii "yjmwxwx-20210101"
	
	.align 4
si5351:		@0=148999000,1=149000000,2=28000000
	.byte 0x00,17,0x80,26,0xFF,27,0xFF,28,0x00
	.byte 29,0x10,30,0x00,31,0xF0,32,0x00
	.byte 33,0x00,50,0xFF,51,0xFF,52,0x73
	.byte 53,0xFD,54,0x80,55,0xF7,56,0xBF
	.byte 57,0x80,177,0x20,17,0x4C
pll_a_biao:
	.byte 50,25,12,6,3,1,1,1,1,1,1
	.align 4
pll_b_biao:
	.int 1048575,524287,262143,131071,65535,32768,16383,8191,4095
	.int 2047,1023,511,255,127,63,31,15,7,3,1,1,1,1,1,1,1,1,1,1,1
	.int 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
r_fenpin:
	.int 585938,292969,146485,74243,36622,18311,9156,4578
	.equ STACKINIT,        	        0x20001000
	.equ asciimabiao,		0x20000000
        .equ liangcheng,                0x20000924
	.equ si5351_pll_pinlv,		0x20000928
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
	.word _systickzhongduan +1           @ 15
	.word aaa +1     @ _wwdg +1          @ 0
	.word aaa +1     @_pvd +1            @ 1
	.word aaa +1     @_rtc +1            @ 2
	.word aaa +1     @_flash +1          @ 3
	.word aaa +1	@ _rcc + 1           @ 4
	.word aaa +1      @_exti0_1  +1      @ 5
	.word aaa +1      @ _exti2_3 +1      @ 6
	.word aaa +1       @_exti4_15 +1     @ 7
	.word aaa +1                         @ 8
	.word aaa +1	@__dma_wan  +1	     @ 9
	.word aaa +1    @_dma1_2_3 +1        @ 10
	.word aaa +1       @_dma1_4_5 +1     @ 11
	.word aaa +1	 @_adc1 +1           @ 12
	.word aaa +1       @_tim1_brk_up +1  @ 13
	.word aaa +1        @ _tim1_cc +1    @ 14
	.word aaa +1         @_tim2 +1       @ 15
	.word aaa +1          @_tim3 +1      @ 16
	.word aaa +1                         @ 17
	.word aaa +1		             @ 18
	.word aaa +1	@_tim14 +1           @ 19
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
_waisheshizhong:                         @ 外设时钟
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

_neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
_neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan

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


@_systick:				@ systick定时器初始化
@
@	ldr r0, = 0xe000e010
@	ldr r1, = 0xffffff
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
	ldr r1, = 0x281454ff
	str r1, [r0]
	ldr r1, =  0x6f0
	str r1, [r0, # 0x04]
	ldr r1, = 0x0c3c0000
	str r1, [r0, # 0x08]
	ldr r1, = 0x100
	str r1, [r0, # 0x0c]
	
	ldr r0, = 0x48000400
	movs r1, # 0x02
	str r1, [r0, # 0x04]
	movs r1, # 0x04
	str r1, [r0, # 0x0c]

__si5351_chu_shi_hua:
	movs r3, # 0
	ldr r4, = si5351
	ldr r5, = 38           @76
__xie_si5351_xun_huan:
	cmp r3, r5
	beq __xie_wan_si5351
	movs r0, # 0xc0
	adds r3, r3, # 1
	ldrb r1, [r4, r3]
	adds r3, r3, # 1
	ldrb r2, [r4, r3]
	bl __xie_i2c_8_wei
	cmp r1, # 0xf0
	beq __si5351_mang
	b __xie_si5351_xun_huan
__si5351_mang:
	subs r3, r3, # 2
	b __xie_si5351_xun_huan
__xie_wan_si5351:
	
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

        movs r0, # 0x80
        ldr r1, = yjmwxwx
	movs r2, # 16
        bl _lcdxianshi
	ldr r0, = 0xffff
yjmwxwx_yanshi:
	subs r0, r0, # 1
	bne yjmwxwx_yanshi
	movs r7, # 0
	subs r7, r7, # 23
	ldr r6, = 1023
ting:
	bkpt # 1
	ldr r0, = 585937
	bl __si5351_ji_suan










	
	ldr r1, = si5351_pll_pinlv
	ldr r2, = 1200000000
	str r2, [r1]
	ldr r0, = 585937
	bl __si5351_fenshu_fenpin
	

	
	adds r7, r7, r6
	ldr r0, = 600000000
	adds r0, r0, r7
	bl __si5351_pll_she_zhi
	movs r1, # 9
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0xc0
	ldr r1, = asciimabiao
	movs r2, # 9
	bl _lcdxianshi
	b ting

	
__si5351_ji_suan:
	@入口：r0=频率
	ldr r1, = 150000000
	cmp r0, r1
	bls __fenshu_fenpin
__fenshu_fenpin:
	movs r3, # 0
	subs r3, r3, # 1
	ldr r2, = r_fenpin
__zhao_r:
	adds r3, r3, # 1
	cmp r3, # 8
	beq __cheng_r
	mov r4, r3
	lsls r4, r4, # 2
	ldr r1, [r2, r4]
	cmp r0, r1
	bcc __zhao_r
__cheng_r:	
	lsrs r4, r4, # 2
	movs r1, # 1
	lsls r1, r1, r4
	muls r0, r0, r1
	bkpt # 2
	bl __si5351_fenshu_fenpin
	



	
__si5351_fenshu_fenpin:
	@入口r0=分数分频后频率
	@返回R0=a,R1=b,R2=b/c(9位小数)
	mov r2, r0
	ldr r1, = si5351_pll_pinlv
	ldr r0, = 1000000000
	ldr r1, [r1]
	bl __chengfa
	bl __chufa64
	mov r3, r1
	ldr r2, = 1000000000
	mov r4, r0
	bl __chufa64
	mov r5, r1		@ a
	ldr r0, = 1000000000
	bl __chengfa
	ldr r0, = 1048575
	subs r1, r3, r1		@b/c
	mov r3, r1
	bl __chengfa
	ldr r2, = 1000000000
	bl __chufa64		@r1=b
	mov r0, r5
	mov r2, r3
	pop {r2-r5,pc}
__si5351_pll_she_zhi:
	@入口R0=pll频率@返回R0=实际频率
	push {r1-r7,lr}
	mov r2, r8
	mov r3, r9
	push {r2-r3}
__zhao_a:	
	mov r8, r0
	ldr r5, = pll_a_biao
	movs r6, # 50
	movs r4, # 0
	ldr r1, = 1048575
__zhao_a_xunhuan:
	mov r3, r6
	bl __si5351_pll_ji_suan
	mov r9, r0
	mov r3, r8
	ldr r7, = 25000000
	subs r0, r0, r3
	beq __si5351_pll_she_zhi_fanhui
	bmi __pll_a_xiaole
	cmp r0, r7
	bls __zhao_b
__pll_a_dale:	
	adds r4, r4, # 1
	ldrb r3, [r5, r4]
	subs r6, r6, r3
	b __zhao_a_xunhuan
__pll_a_xiaole:
	adds r4, r4, # 1
	ldrb r3, [r5, r4]
	adds r6, r6, r3
	b __zhao_a_xunhuan
__zhao_b:
	mov r0, r8
	mov r3, r6
	ldr r5, = pll_b_biao
	ldr r6, = 1048575
	movs r4, # 0
__zhao_b_xunhuan:
	mov r1, r6
	bl __si5351_pll_ji_suan
	mov r9, r0
	mov r1, r8
	movs r7, # 23
	subs r0, r0, r1
	beq __si5351_pll_she_zhi_fanhui
	bmi __pll_b_xiaole
	cmp r0, r7
	bls __si5351_pll_she_zhi_fanhui
__pll_b_dale:
	adds r4, r4, # 4
	ldr r1, [r5, r4]
	subs r6, r6, r1
	b __zhao_b_xunhuan
__pll_b_xiaole:
	adds r4, r4, # 4
	ldr r1, [r5, r4]
	adds r6, r6, r1
	b __zhao_b_xunhuan
__si5351_pll_she_zhi_fanhui:
	mov r0, r9
	pop {r2-r3}
	mov r8, r2
	mov r9, r3
	pop {r1-r7,pc}
__si5351_pll_ji_suan:
	@入口R1=b,R3=a,返回R0=PLL频率,r2=b/c
	push {r1,r3,lr}
	ldr r2, = 1048575
	ldr r0, = 100000000
	bl __chengfa
	bl __chufa64
	mov r2, r1
	movs r0, # 25
	muls r0, r0, r1
	movs r1, # 100
	bl _chufa
	ldr r1, = 25000000
	muls r1, r1, r3
	adds r0, r0, r1 	@PLL频率
	pop {r1,r3,pc}
__si5351_xiaoshu_fenpin:
	@入口R1=b,R3=a,返回r0=分频比，r2=b/c
	push {r1,r3,lr}
	ldr r2, = 1048575
	ldr r0, = 100000000
	muls r3, r3, r0
	bl __chengfa
	bl __chufa64
	mov r2, r1
	adds r3, r3, r1
	mov r0, r3
	pop {r1,r3,pc}
	
	



	.ltorg
__xie_i2c_8_wei:
	push {r3-r7,lr}
	@r0=从地址，r1=数据地址，r2=数据
	ldr r7, = 0x48000000
	ldr r3, = 0x200 	@pa9=SDA
	ldr r4, = 0x400		@pa10=SCL
__i2c_qi_8:
	str r3, [r7, # 0x18]	@ SDA=1
	str r4, [r7, # 0x18]	@ SCL=1
	bl __i2c_yan_shi
	str r3, [r7, # 0x28]	@ SDA=0
	bl __i2c_yan_shi
	str r4, [r7, # 0x28]	@ SCL=0
	bl __i2c_yan_shi
	movs r6, # 0
__xie_cong_di_zhi_8:
	movs r5, # 8
	lsls r0, r0, # 23
	b __xie_shu_ju_8
__xie_cong_ji_di_zhi:
	mov r0, r1
	movs r5, # 8
	lsls r0, r0, # 23
	b __xie_shu_ju_8
__xie_cong_ji_shu_ju:
	mov r0, r2
	movs r5, # 8
	lsls r0, r0, # 23
__xie_shu_ju_8:
	lsls r0, r0, # 1
	bpl __SDA_8_deng_yu_0
	str r3, [r7, # 0x18]	@SDA=1
	b __SCL_8_gao
__SDA_8_deng_yu_0:
	str r3, [r7, # 0x28]	@SDA=0
__SCL_8_gao:
	str r4, [r7, # 0x18]	@SCL=1
	bl __i2c_yan_shi
	str r4, [r7, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	subs r5, r5, # 1
	bne __xie_shu_ju_8
	str r3, [r7, # 0x18]	@SDA=1
	bl __i2c_yan_shi
	str r4, [r7, # 0x18]	@SCL=1
	bl __i2c_yan_shi
__du_apk_8:
	ldr r5, [r7, # 0x10]	@读APK
	lsls r5, r5, # 22
	bpl __apk_di_8
__apk_gao_8:
	movs r1, # 0xf0
	b __i2c_ting_8
__apk_di_8:
	str r4, [r7, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	adds r6, r6, # 1
	cmp r6, # 1
	beq __xie_cong_ji_di_zhi
	cmp r6, # 2
	beq __xie_cong_ji_shu_ju
__i2c_ting_8:
	str r3, [r7, # 0x28]	@SDA=0
	bl __i2c_yan_shi
	str r4, [r7, # 0x18]	@SCL=1
	bl __i2c_yan_shi
	str r3, [r7, # 0x18]	@SDA=1
	pop {r3-r7,pc}
__xie_i2c:
	push {r2-r7,lr}
	adds r1, r1, # 2
	ldr r2, = 0x48000000
	ldr r3, = 0x200 	@pa9=SDA
	ldr r4, = 0x400		@pa10=SCL
__i2c_qi:
	str r3, [r2, # 0x18]	@ SDA=1
	str r4, [r2, # 0x18]	@ SCL=1
	bl __i2c_yan_shi
	str r3, [r2, # 0x28]	@ SDA=0
	bl __i2c_yan_shi
	str r4, [r2, # 0x28]	@ SCL=0
	bl __i2c_yan_shi
	movs r7, # 0
__xie_shu_ju_xun_huan:
	movs r5, # 8
	ldrb r6, [r0, r7]
	lsls r6, r6, # 23
__xie_shu_ju:
	lsls r6, r6, # 1
	bpl __SDA_deng_yu_0
	str r3, [r2, # 0x18]	@SDA=1
	b __SCL_gao
__SDA_deng_yu_0:
	str r3, [r2, # 0x28]	@SDA=0
__SCL_gao:
	str r4, [r2, # 0x18]	@SCL=1
	bl __i2c_yan_shi
	str r4, [r2, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	subs r5, r5, # 1
	bne __xie_shu_ju
	str r3, [r2, # 0x18]	@SDA=1
	bl __i2c_yan_shi
	str r4, [r2, # 0x18]	@SCL=1
	bl __i2c_yan_shi
__du_apk:
	ldr r5, [r2, # 0x10]	@读APK
	lsls r5, r5, # 22
	bpl __apk_di
__apk_gao:
	b __apk_gao
__apk_di:
	str r4, [r2, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	adds r7, r7, # 1
	subs r1, r1, # 1
	bne __xie_shu_ju_xun_huan
__i2c_ting:
	str r3, [r2, # 0x28]	@SDA=0
	bl __i2c_yan_shi
	str r4, [r2, # 0x18]	@SCL=1
	bl __i2c_yan_shi
	str r3, [r2, # 0x18]	@SDA=1
	pop {r2-r7,pc}
__du_i2c:
	push {r2-r7,lr}
	mov r8, r1
	movs r1, # 0
	ldr r2, = 0x48000000
	ldr r3, = 0x200 	@pa9=SDA
	ldr r4, = 0x400		@pa10=SCL
__i2c_qi1:
	str r3, [r2, # 0x18]	@ SDA=1
	str r4, [r2, # 0x18]	@ SCL=1
	bl __i2c_yan_shi
	str r3, [r2, # 0x28]	@ SDA=0
	bl __i2c_yan_shi
	str r4, [r2, # 0x28]	@ SCL=0
	bl __i2c_yan_shi
	movs r5, # 8
	movs r7, # 2
	movs r6, # 0xc0
	lsls r6, r6, # 23
	b __xie_shu_ju1
__yao_du_de_di_zhi:
	movs r6, # 0xb7
	lsls r6, r6, # 23
	movs r5, # 8
__xie_shu_ju1:
	lsls r6, r6, # 1
	bpl __SDA_deng_yu0_1
	str r3, [r2, # 0x18]	@SDA=1
	b __SCL_gao1
__SDA_deng_yu0_1:
	str r3, [r2, # 0x28]	@SDA=0
__SCL_gao1:
	str r4, [r2, # 0x18]	@SCL=1
	bl __i2c_yan_shi
	str r4, [r2, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	subs r5, r5, # 1
	bne __xie_shu_ju1
	str r3, [r2, # 0x18]	@SDA=1
	bl __i2c_yan_shi
	str r4, [r2, # 0x18]	@SCL=1
	bl __i2c_yan_shi
__du_apk1:
	ldr r5, [r2, # 0x10]	@读APK
	lsls r5, r5, # 22
	bpl __apk_di1
__apk_gao1:
	b __apk_gao1
__apk_di1:
	str r4, [r2, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	cmp r7, # 0xff
	beq __du_shu_ju
	subs r7, r7, # 1
	bne __yao_du_de_di_zhi
__i2c_qi2:
	str r3, [r2, # 0x18]    @ SDA=1
	str r4, [r2, # 0x18]    @ SCL=1
	bl __i2c_yan_shi
	str r3, [r2, # 0x28]    @ SDA=0
	bl __i2c_yan_shi
	str r4, [r2, # 0x28]    @ SCL=0
	bl __i2c_yan_shi
	movs r6, # 0xc1		@读
	lsls r6, r6, # 23
	movs r5, # 8
	movs r7, # 0xff
	b __xie_shu_ju1
__du_shu_ju:
	movs r5, # 8
	movs r7, # 0
	str r3, [r2, # 0x18]	@ SDA=1
__du_shu_ju_xun_huan:
	bl __i2c_yan_shi
	str r4, [r2, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	str r4, [r2, # 0x18]	@SCL=1
	bl __i2c_yan_shi
	ldr r6, [r2, # 0x10]	@读SDA
	lsls r6, r6, # 22
	lsrs r6, r6, # 31
	lsls r7, r7, # 1
	orrs r7, r7, r6
	subs r5, r5, # 1
	bne __du_shu_ju_xun_huan
	str r4, [r2, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	strb r7, [r0, r1]
	adds r1, r1, # 1
	cmp r1, r8
	bne __ying_da
__fei_ying_da:
	str r3, [r2, # 0x18]	@SDA=0
	bl __i2c_yan_shi
	str r4, [r2, # 0x18]    @SCL=1
	bl __i2c_yan_shi
	str r4, [r2, # 0x28]    @SCL=0
	bl __i2c_yan_shi
	b __i2c_ting1
__ying_da:
	str r3, [r2, # 0x28]	@SDA=0
	bl __i2c_yan_shi
	str r4, [r2, # 0x18]	@SCL=1
	bl __i2c_yan_shi
	str r4, [r2, # 0x28]	@SCL=0
	bl __i2c_yan_shi
	b  __du_shu_ju
__i2c_ting1:
	str r3, [r2, # 0x28]	@SDA=0
	bl __i2c_yan_shi
	str r4, [r2, # 0x18]	@SCL=1
	bl __i2c_yan_shi
	str r3, [r2, # 0x18]	@SDA=1
	pop {r2-r7,pc}	
__i2c_yan_shi:
	push {r3, lr}
	ldr r3, = 0x500
__i2c_yan_shi_xun_huan:
	subs r3, r3, # 1
	bne __i2c_yan_shi_xun_huan
	pop {r3, pc}
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
_lcdxianshi:	  		@r0=LCD位置，r1=数据地址，r2=长度
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
	ldr r5, = 0x1000
_lcdyanshixunhuan:
	subs r5, r5, # 1
	bne _lcdyanshixunhuan
	pop {r5,pc}

_xielcd:			@入R0=8位,r1=0命令,r1=1数据
	push {r0-r5,lr}
	ldr r4, = liangcheng  @ 量程开关 (第6位和第7位)
	mov r2, r0
	ldr r5, [r4]
	lsrs r2, r2, # 4
	lsls r2, r2, # 2	@ 高四位
	lsls r0, r0, # 28
	lsrs r0, r0, # 26	@ 低四位
	lsls r1, r1, # 31
	bpl __lcd_ming_ling
__lcd_shu_ju:
	movs r3, # 0x03		@ RS = 1 E = 1
	b __xie_lcd_shu_ju
__lcd_ming_ling:
	movs r3, # 0x02		@ RS = 0 E = 1
__xie_lcd_shu_ju:
	adds r3, r3, r5
	mov r1, r0
	adds r2, r2, r3
	movs r0, r2
	bl __74hc595
	subs r0, r0, # 0x02
	bl __74hc595
	mov r0, r1
	adds r0, r0, r3
	bl __74hc595
	subs r0, r0, # 0x02
	bl __74hc595
	pop {r0-r5,pc}
	
__74hc595:			@ 入R0=8位
	push {r0-r7,lr}
	ldr r6, = 0x48000000
	movs r5, # 0x20		@ SRCLK
	movs r2, # 0x40		@ RCLK
	movs r3, # 0x80		@ SER
	movs r4, # 24
__595_yiweixunhuan:
	str r2, [r6, # 0x28]	@ rclk=0
	str r5, [r6, # 0x28]	@ srclk=0
	@ovs r7, # 0xff
	ldr r7, = 0x1ff
__595_yanshi:
	subs r7, r7, # 1
	bne __595_yanshi
	mov r1, r0
	lsls r1, r1, r4
	bpl __ser_0
__ser_1:
	str r3, [r6, # 0x18]	@ ser=1
	b __595_yiwei
__ser_0:
	str r3, [r6, # 0x28]	@ ser=0
__595_yiwei:
	str r5, [r6, # 0x18]
	@movs r7, # 0xff
	ldr r7, = 0x1ff
__595_yanshi1:
	subs r7, r7, # 1
	bne __595_yanshi1
	adds r4, r4, # 1
	cmp r4, # 32
	bne __595_yiweixunhuan
	str r2, [r6, # 0x18]	@ rclk=1
	@movs r7, # 0xff
	ldr r7, = 0x1ff
__595_yanshi2:
	subs r7, r7, # 1
	bne __595_yanshi2
	str r2, [r6, # 0x28]	@ rclk = 0
	pop {r0-r7,pc}



_zhuanascii:					@ 16进制转ASCII
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
__di_yi_wei:	            @低32位移位
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
	@4        F F F E 0 0 0 1			@4
	@3                F F F E 0 0 0 1		@3
	@2                F F F E 0 0 0 1		@2
	@1                        F F F E 0 0 0 1	@1
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
	mov r6, r0
	mov r7, r4
	lsls r0, r0, # 16	@2低32
	lsls r4, r4, # 16	@3低32
	lsrs r6, r6, # 16	@2高32
	lsrs r7, r7, # 16	@3高32
	movs r1, # 0
	adds r2, r2, r0		@低32
	adcs r6, r6, r1		@高32
	adds r2, r2, r4
	adcs r6, r6, r7
	adds r6, r6, r5
	mov r0, r6
	mov r1, r2
	pop {r2-r7,pc}
__cheng_fa_fan_hui:
	movs r0, # 0
	movs r1, # 0
	pop {r2-r7,pc}
__dai_yu_shu_chufa:	                         @软件除法
	@ r0 除以 r1 等于 商(r0)余R1
	push {r2-r4,lr}
	cmp r0, # 0
	beq __dai_yu_shu_chufafanhui
	cmp r1, # 0
	beq __dai_yu_shu_chufafanhui
	mov r2, r0
	movs r3, # 1
	lsls r3, r3, # 31
	movs r0, # 0
	mov r4, r0
__dai_yu_shu_chufaxunhuan:
	lsls r2, r2, # 1
	adcs r4, r4, r4
	cmp r4, r1
	bcc __dai_yu_shu_chufaweishubudao0
	adds r0, r0, r3
	subs r4, r4, r1
__dai_yu_shu_chufaweishubudao0:
	lsrs r3, r3, # 1
	bne __dai_yu_shu_chufaxunhuan
__dai_yu_shu_chufafanhui:
	        pop {r2-r4,pc}
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
	.ltorg
	.end
