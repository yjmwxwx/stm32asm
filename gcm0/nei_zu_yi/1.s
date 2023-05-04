	@@ 单片机stm32f030f4p6
	@电池内阻仪正负电源版
	@作者：yjmwxwx
	@时间：2023-03-22
	@编译器：ARM-NONE-EABI
	.thumb
	.syntax unified
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
	.word aaa +1    @ _rcc + 1           @ 4
	.word aaa +1      @_exti0_1  +1      @ 5
	.word aaa +1      @ _exti2_3 +1      @ 6
	.word aaa +1       @_exti4_15 +1     @ 7
	.word aaa +1                         @ 8
	.word aaa +1    @__dma_wan  +1       @ 9
	.word aaa +1    @_dma1_2_3 +1        @ 10
	.word aaa +1       @_dma1_4_5 +1     @ 11
	.word aaa +1     @_adc1 +1           @ 12
	.word aaa +1       @_tim1_brk_up +1  @ 13
	.word aaa +1        @ _tim1_cc +1    @ 14
	.word aaa +1         @_tim2 +1       @ 15
	.word aaa +1          @_tim3 +1      @ 16
	.word aaa +1                         @ 17
	.word aaa +1                         @ 18
	.word aaa +1    @_tim14 +1           @ 19
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
	ldr r1, = 0x154002	@0x150002	@0x150002
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
	
_waisheshizhong:		                         @ 外设时钟
	@+0x14=RCC_AHBENR
	@ 0=DMA @ 2=SRAM @ 4=FLITF@ 6=CRC @ 17=PA @ 18=PB @ 19=PC @ 20=PD @ 22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x60001
	str r1, [r0, # 0x14]

	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
	ldr r1, = 0x1a00
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@ 1=TIM3 @ 4=TIM6 @ 5=TIM7 @ 8=TIM14 @ 11=WWDG @ 14=SPI @ 17=USRT2 @ 18=USART3 @ 20=USART5 @ 21=I2C1
	@ 22=I2C2 @ 23=USB @ 28=PWR
	ldr r2, = 0x902
	str r2, [r0, # 0x1c]
	
_neicunqingling:
	ldr r0, = 0x20001000
	ldr r2, = 0x20000000
	movs r1, # 0
_neicunqinglingxunhuan:
        subs r0, r0, # 4
	str r1, [r0]
	cmp r0, r2
	bne _neicunqinglingxunhuan


_waishezhongduan:		@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效
@	ldr r0, =  0xe000e100
@	ldr r1, = 0x200 @0x10200  @ 0x10000
@	str r1, [r0]
	
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
	ldr r1, = 0x28208a57
	str r1, [r0]
	movs r1, # 0xb0
	str r1, [r0, # 0x04]
	ldr r1, = 0x30cffc
	str r1, [r0, # 0x08]
	ldr r1, = 0x200
	str r1, [r0, # 0x24]
	ldr r1, = 0x41000
	str r1, [r0, # 0x0c]

	ldr r0, = 0x48000400
	movs r1, # 0x04
	str r1, [r0]
	movs r1, # 0x0c
	str r1, [r0, # 0x08]

spi_chushihua:
	ldr r0, = 0x40013000
	ldr  r1, = 0x708
	str r1, [r0, # 0x04]
	ldr r1, = 0x7c
	str r1, [r0]



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
	ldr r0, = 0xffffff
yjmwxwx_yanshi:
	subs r0, r0, # 1
	bne yjmwxwx_yanshi

	ldr r0, = 0x8003c00
	ldr r1, = 0xffffffff
	ldr r0, [r0]
	cmp r0, r1
	bne __tiaoguo_chuchang_shezhi
	bl __du_chuchang	@恢复出厂设置
	bl __xie_flash
	
__tiaoguo_chuchang_shezhi:	
	ldr r0, = liangcheng
	movs r1, # 4
	str r1, [r0]
	bl __pinlv_shezhi



__anjian0:
	b ting
__anjian1:
        movs r0, # 0x80
	ldr r1, = duanlu
	movs r2, # 16
	bl _lcdxianshi
_MEGANMEOW_:
	bl __du_duanlu_biao
	bl __du_jiaozhun_biao
	
	ldr r0, = liangcheng
	movs r1, # 0
	str r1, [r0]
__duanlu_qingling:
	bl __duanlu_qingling_xianshi
	bl __an_jian
	cmp r0, # 1
	beq __qingling_jia
	cmp r0, # 2
	beq __qingling_jian
	b __duanlu_qingling
__qingling_jia:
	bl __an_jian
	cmp r0, # 3
	beq __qingling_baocun
	cmp r0, # 0
	beq __qingling_jiale
	bl __duanlu_qingling_xianshi
	b __qingling_jia
__qingling_jiale:
	ldr r0, = liangcheng
	ldr r0, [r0]
	lsls r0, r0, # 2
	ldr r1, = mr10_0
	ldr r2, [r1, r0]
	adds r2, r2, # 1
	str r2, [r1, r0]
	b __duanlu_qingling
__qingling_jian:
	bl __an_jian
	cmp r0, # 3
	beq __qingling_baocun
	cmp r0, # 0
	beq __qingling_jianle
	bl __duanlu_qingling_xianshi
	b __qingling_jian
__qingling_jianle:
	ldr r0, = liangcheng
	ldr r0, [r0]
	lsls r0, r0, # 2
	ldr r1, = mr10_0
	ldr r2, [r1, r0]
	subs r2, r2, # 1
	str r2, [r1, r0]
	b __duanlu_qingling
	
__qingling_baocun:	
	ldr r0, = liangcheng
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	cmp r1, # 5
	bne __duanlu_qingling
__duanlu_qingling_wan:
	movs r1, # 4
	str r1, [r0]
        movs r0, # 0x80
	ldr r1, = duanlu_wancheng
	movs r2, # 16
	bl _lcdxianshi
	ldr r0, = 0xffffff
__yy:
	subs r0, r0, # 1
	bne __yy
	bl __xie_flash
	bkpt # 1
	
__duanlu_qingling_xianshi:
	push {r0-r1,lr}
	bl __xianshi_dangwei
	bl __xianshi_zukang_danwei
	ldr r0, = liangcheng
	ldr r1, = mr10_0
	ldr r0, [r0]
	lsls r0, r0, # 2
	ldr r1, [r1, r0]
	ldr r0, = z
	ldr r0, [r0]
	subs r0, r0, r1
	bl __xianshi_zukang
	pop {r0-r1,pc}
__anjian2:	
__dangwei_jia_deng_songshou:
	bl __an_jian
	cmp r0, # 3
	beq __anjian3
	cmp r0, # 0
	beq __dangwei_jia_le
	bl __xianshi_dianzu
	b __dangwei_jia_deng_songshou
@	bl __an_jian
@	b __ren_wu_diao_du
__dangwei_jia_le:
	ldr r0, = liangcheng
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	cmp r1, # 5
	bne __anjian8_fanhui
	movs r1, # 0
	str r1, [r0]

__anjian8_fanhui:
	bl __xianshi_dangwei
	b __ren_wu_diao_du
	.ltorg
	
__anjian3:	
	movs r0, # 0x80
	ldr r1, = jiaozhun
	movs r2, # 16
	bl _lcdxianshi
	
	bl __du_duanlu_biao
	bl __du_jiaozhun_biao
	ldr r0, = jiaozhun_kaiguan
	movs r1, # 1
	str r1, [r0]
	ldr r0, = liangcheng
	movs r1, # 0
	str r1, [r0]
__jiaozhun_dianzu:
	bl __jiaozhun_moshi_xianshi
	bl __an_jian
	cmp r0, # 1
	beq __jiaozhun_jia
	cmp r0, # 2
	beq __jiaozhun_jian
	b __jiaozhun_dianzu
__jiaozhun_jia:
	bl __an_jian
	cmp r0, # 3
	beq __jiaozhun_baocun
	cmp r0, # 0
	beq __jiaozhun_jiale
	bl __jiaozhun_moshi_xianshi
	b __jiaozhun_jia
__jiaozhun_jiale:
	ldr r0, = liangcheng
	ldr r0, [r0]
	lsls r0, r0, # 2
	ldr r1, = mr10_jz
	ldr r2, [r1, r0]
	adds r2, r2, # 1
	str r2, [r1, r0]
	b __jiaozhun_dianzu
__jiaozhun_jian:
	bl __an_jian
	cmp r0, # 3
	beq __jiaozhun_baocun
	cmp r0, # 0
	beq __jiaozhun_jianle
	bl __jiaozhun_moshi_xianshi
	b __jiaozhun_jian
__jiaozhun_jianle:
	ldr r0, = liangcheng
	ldr r0, [r0]
	lsls r0, r0, # 2
	ldr r1, = mr10_jz
	ldr r2, [r1, r0]
	subs r2, r2, # 1
	str r2, [r1, r0]
	b __jiaozhun_dianzu
	
__jiaozhun_baocun:	
	ldr r0, = liangcheng
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	cmp r1, # 5
	bne __jiaozhun_dianzu
__jiaozhun_wan:
	movs r1, # 4
	str r1, [r0]
        movs r0, # 0x80
	ldr r1, = jiaozhun_wan
	movs r2, # 16
	bl _lcdxianshi
	ldr r0, = 0xffffff
__yy1:
	subs r0, r0, # 1
	bne __yy1
	bl __xie_flash
	bkpt # 1
	
__jiaozhun_moshi_xianshi:
	push {r0-r1,lr}
	bl __xianshi_dangwei
	bl __xianshi_zukang_danwei
	ldr r0, = liangcheng
	ldr r1, = mr10_0
	ldr r0, [r0]
	lsls r0, r0, # 2
	ldr r1, [r1, r0]
	ldr r0, = z
	ldr r0, [r0]
	subs r0, r0, r1
	bl __xianshi_zukang
	pop {r0-r1,pc}	






__ren_wu_diao_du:
	bl __an_jian

	ldr r1, = anjian_hao
	str r0, [r1]
	lsls r0, r0, # 2
	ldr r1, = an_jian_biao
	ldr r2, [r1, r0]
	mov pc, r2



	
ting:
	bl __xianshi_dianzu
	b __ren_wu_diao_du
	
__xianshi_dianzu:
	push {r0-r1,lr}
@	bl __xianshi_shangxia_bi
@	b ting
	bl __xianshi_dangwei
	bl __xianshi_zukang_danwei
	ldr r0, = liangcheng
	ldr r1, = f_mr10_0
	ldr r0, [r0]
	lsls r0, r0, # 2
	ldr r1, [r1, r0]
	ldr r0, = z
	ldr r0, [r0]
	subs r0, r0, r1
	bl __xianshi_zukang
	pop {r0-r1,pc}
	
__xianshi_ceshi:	
	movs r1, # 1	
	ldr r2, = asciimabiao
	movs r3, # 0xff		@小数点位置
	bl _zhuanascii
	movs r0, # 0xc4
	ldr r1, = asciimabiao
	movs r2, # 1
	bl _lcdxianshi

	
	b ting


__du_chuchang:	
	push {r0-r6}
	ldr r0, = chuchang_dianzu_biao 
	ldr r2, = mr10_jz
	movs r5, # 0
__du_chuchang_xunhuan:
	mov r6, r5
	lsls r6, r6, # 2
	ldr r3, [r0, r6]
	str r3, [r2, r6]
	adds r5, r5, # 1
	cmp r5, # 5
	bne __du_chuchang_xunhuan
	pop {r0-r6}
	bx lr
	


	
__du_jiaozhun_biao:
	push {r0-r6}
	ldr r0, = f_mr10_jz
	ldr r2, = mr10_jz
	movs r5, # 0
__du_jiaozhun_xunhuan:
	mov r6, r5
	lsls r6, r6, # 2
	ldr r3, [r0, r6]
	str r3, [r2, r6]
	adds r5, r5, # 1
	cmp r5, # 5
	bne __du_jiaozhun_xunhuan
	pop {r0-r6}
	bx lr

	
__du_duanlu_biao:
	push {r0-r6}
	ldr r0, = f_mr10_0
	ldr r2, = mr10_0
	movs r5, # 0
__du_duanlu_xunhuan:
	mov r6, r5
	lsls r6, r6, # 2
	ldr r3, [r0, r6]
	str r3, [r2, r6]
	adds r5, r5, # 1
	cmp r5, # 5
	bne __du_duanlu_xunhuan
	pop {r0-r6}
	bx lr
	
__xie_flash:
	ldr r0, = 0x40022000
	ldr r1, = 0x45670123
	str r1, [r0, # 0x04]
	ldr r1, = 0xcdef89ab
	str r1, [r0, # 0x04]
	@擦除2页
	movs r5, # 1
	ldr r4, = 0x8003c00
_flashmang:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang
	movs r1, # 2
	str r1, [r0, # 0x10]
	str r4, [r0, # 0x14]
	movs r1, # 0x42
	str r1, [r0, # 0x10]
	subs r5, # 1
	bne _flashmang
	@写FLASH
	ldr r7, = 0x8003c00
	ldr r4, = mr10_0
	movs r5, # 0
	movs r6, # 10
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
@	movs r1, # 0x80
@	str r1, [r0]          		@flsh上锁
	ldr r0, = 0xe000ed0c
	ldr r1, = 0x05fa0004
	str r1, [r0]          		@复位
	
__an_jian:
	@入口PA6=按键1，PA9=按键2
	@出口R0
	push {r1}
	ldr r1, = 0x48000010
	ldr r0, [r1]	@pa6 pa9
	mvns r0, r0
	mov r1, r0
	lsrs r0, r0, # 9
	lsls r0, r0, # 31
	lsrs r0, r0, # 30
	lsls r1, r1, # 25
	lsrs r1, r1, # 31
	orrs r0, r0, r1
	pop {r1}
	bx lr
	
__xianshi_zukang_danwei:
	push {r0-r3,lr}
	ldr r3, = liangcheng
	ldr r3, [r3]
	lsls r3, r3, # 2
	movs r0, # 0xce
	ldr r1, = zukang_danwei
	adds r1, r1, r3
	movs r2, # 2
	bl _lcdxianshi
	bl _lcdyanshi
	pop {r0-r3,pc}
	
__xianshi_dangwei:
	push {r0-r2,lr}
	ldr r0, = liangcheng
	ldr r0, [r0]
	lsls r0, r0, # 2
	ldr r1, = dangwei_biao
	ldr r1, [r1, r0]
        movs r0, # 0xc0
	movs r2, # 5
	bl _lcdxianshi
	pop {r0-r2,pc}
	
__xianshi_zukang:
	push {r1-r5,lr}
	movs r4, r0
	bpl aaa1
	movs r0, # 0xc7
	ldr r1, = _fu
	movs r2, # 1
	bl _lcdxianshi
	mvns r4, r4
	adds r4, r4, # 1
	b aaa2
aaa1:
	movs r0, # 0xc7
	ldr r1, = kong
	movs r2, # 1
	bl _lcdxianshi
aaa2:
	mov r0, r4
	movs r1, # 6
	ldr r2, = asciimabiao
	ldr r4, = zukang_xiaoshu_dian
	ldr r3, = liangcheng
	ldr r3, [r3]
	ldrb r3, [r4, r3]
	bl _zhuanascii
	movs r0, # 0xc8
	ldr r1, = asciimabiao
	movs r2, # 6
	bl _lcdxianshi
	pop {r1-r5,pc}




	

__ji_suan_fu_du:	    @ 计算幅度
	@ 入r0= 实部，r1= 虚部
	@ 出r0 = 幅度
	@ Mag ~=Alpha * max(|I|, |Q|) + Beta * min(|I|, |Q|)
	@ Alpha * Max + Beta * Min
	push {r1-r3,lr}
	movs r0, r0
	bpl _shibubushifushu
	mvns r0, r0                             @ 是负数转成正数
	adds r0, r0, # 1
_shibubushifushu:	                               @ 实部不是负数
	movs r1, r1
	bpl _xububushifushu
	mvns r1, r1                             @ 是负数转成正数
	adds r1, r1, # 1
_xububushifushu:	                                @ 虚部不是负数
	cmp r0, # 0
	bne _panduanxubushibushi0
	mov r0, r1
	pop {r1-r3,pc}
_panduanxubushibushi0:
	cmp r1, # 0
	bne _jisuanfudu1
	pop {r1-r3,pc}
_jisuanfudu1:
	ldr r2, = 31066		@ Alpha q15 0.948059448969
	ldr r3, = 12867		@ Beta q15 0.392699081699
	cmp r1, r0
	bhi _alpha_min_beta_max
_alpha_max_beta_min:
	muls r0, r0, r2
	muls r1, r1, r3
	asrs r0, r0, # 15
	asrs r1, r1, # 15
	adds r0, r0, r1
	movs r1, # 1
	pop {r1-r3,pc}
_alpha_min_beta_max:
	muls r0, r0, r3
	muls r1, r1, r2
	asrs r0, r0, # 15
	asrs r1, r1, # 15
	adds r0, r0, r1
	movs r1, # 0
	pop {r1-r3,pc}

__xianshi_shangxia_bi:
	push {r0-r7,lr}
	ldr r0, = shangbi_r
	ldr r2, = shangbi_i
	ldr r1, [r0]
	ldr r7, [r2]
	movs r4, r1
	bpl aa1
	movs r0, # 0xc0
	ldr r1, = _fu
	movs r2, # 1
	bl _lcdxianshi
	mvns r4, r4
	adds r4, r4, # 1
	b aa2
aa1:
	movs r0, # 0xc0
	ldr r1, = kong
	movs r2, # 1
	bl _lcdxianshi
aa2:
	mov r0, r4
	movs r1, # 6
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0xc1
	ldr r1, = asciimabiao
	movs r2, # 6
	bl _lcdxianshi


	movs r4, r7
	bpl bb1
	movs r0, # 0xc9
	ldr r1, = _fu
	movs r2, # 1
	bl _lcdxianshi
	mvns r4, r4
	adds r4, r4, # 1
	b bb2
bb1:
	movs r0, # 0xc9
	ldr r1, = kong
	movs r2, # 1
	bl _lcdxianshi
bb2:
	mov r0, r4
	movs r1, # 6
	ldr r2, = asciimabiao
	movs r3, # 0xff
	bl _zhuanascii
	movs r0, # 0xca
	ldr r1, = asciimabiao
	movs r2, # 6
	bl _lcdxianshi
	pop {r0-r7,pc}
	.ltorg

	
__dft:		
	push {r2-r7,lr}
	mov r5, r10
	mov r6, r11
	mov r7, r12
	push {r5-r7}
	ldr r0, = cossin
	ldr r1, = dianyabiao
	ldr r0, [r0]
	movs r6, # 0
	mov r7, r6
	mov r12, sp
	mov r11, r0
	mov r10, r1
	b __dft_xunhuan
	.ltorg
__dft_xunhuan:
	@0
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@1
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@2
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@3
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@4
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@5
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@6
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@7
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@8
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@9
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@10
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@11
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4		@R
	muls r1, r1, r4		@I
	muls r2, r2, r5		@R
	muls r3, r3, r5		@I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2	 @r
	adds r1, r1, r3	 @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	@12
	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4         @R
	muls r1, r1, r4         @I
	muls r2, r2, r5         @R
	muls r3, r3, r5         @I
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2  @r
	adds r1, r1, r3  @i
	adds r6, r6, r0
	adds r7, r7, r1

	mov sp, r11
	pop {r0-r3}
	mov r11, sp
	mov sp, r10
	pop {r4}
	mov r10, sp
	mov r5, r4
	lsls r4, r4, # 16
	lsrs r4, r4, # 16
	lsrs r5, r5, # 16
	muls r0, r0, r4
	muls r1, r1, r4
	muls r2, r2, r5
	muls r3, r3, r5
	asrs r0, r0, # 6
	asrs r1, r1, # 6
	asrs r2, r2, # 6
	asrs r3, r3, # 6
	adds r0, r0, r2         @r
	adds r1, r1, r3         @i
	adds r6, r6, r0
	adds r7, r7, r1

	
@	bkpt # 1
	ldr r0, = 0x200008d0
	cmp r10, r0
	beq __dft_fanhuile
	ldr r0, = cossin
	ldr r0, [r0]
	mov r11, r0
	ldr r0, = __dft_xunhuan
	adds r0, r0, # 1
	mov pc, r0
@	b __dft_xunhuan
__dft_fanhuile:
	mov r0, r6
	mov r1, r7
	asrs r0, r0, # 9	@dfdf
	asrs r1, r1, # 9
	mov sp, r12
	pop {r2-r4}
	mov r10, r2
	mov r11, r3
	mov r12, r4
	pop {r2-r7,pc}
	.ltorg	

__lv_bo_qi:
	@地址顺序：指针，累加值，缓冲区
	@入口R0=缓冲区，R1=数据, r2,=指针
	@出口R0
	push {r3-r7,lr}
	ldr r4, = lvbo_changdu
	ldr r7, = lvbo_youyi
	ldr r4, [r4]
	ldr r7, [r7]
	ldr r5, [r2]
	mov r3, r5
	lsls r3, r5, # 2
	ldr r6, [r0, r3]
	str r1, [r0, r3]
	adds r5, r5, # 1
	str r5, [r2]
	cmp r5, r4
	bne __huanchong_leijia
	movs r5, # 0
	str r5, [r2]
__huanchong_leijia:
	subs r0, r0, # 4
	ldr r5, [r0]
	adds r1, r1, r5
	subs r1, r1, r6
	str r1, [r0]
	asrs r1, r1, r7	 @# 12 @12 @  7	@128
	mov r0, r1
	pop {r3-r7,pc}
	.ltorg
	
	
__pinlv_shezhi:
	@入口R0
	@0=1KHZ
	push {r0-r3,lr}
	ldr r1, = shezhi_pinlv
	movs r2, # 1
	str r2, [r1]
	ldr r2, = pinlv
	ldr r1, = pinlv_biao
	ldr r2, [r2]
	lsls r2, r2, # 2
	ldr r2, [r1, r2]
	mov pc, r2

__pinlv_1K:
	bl _adcchushihua
	@tim1ch3DMA
	ldr r0, = 0x40020000
	movs r1, # 0
	str r1, [r0, # 0x58]
	str r1, [r0, # 0x08]
	ldr r1, = 0x40012c3c @ 外设地址
	str r1, [r0, # 0x60]
	ldr r1, = zheng_xian_1khz @ 储存器地址
	str r1, [r0, # 0x64]
	ldr r1, = 250             @点数
	str r1, [r0, # 0x5c]
	ldr r1, = 0x31b1         @ 储存到外设
	str r1, [r0, # 0x58]
	@ adc dma
	ldr r1, = 0x40012440
	str r1, [r0, # 0x10]
	ldr r1, = dianyabiao
	str r1, [r0, # 0x14]
	ldr r1, = 1000
	str r1, [r0, # 0x0c]
	ldr r1, = 0x35a1 @  0x583        @ 5a1
	str r1, [r0, # 0x08]

        ldr r4, = 0xe000e010
	ldr r3, = 559999
	str r3, [r4, # 4]
	str r3, [r4, # 8]
	movs r3, # 0x07
	@str r3, [r4]    @systick 开
	

	@tim3chushihua:
	ldr r3, = 0x40000400 @ tim3_cr1
	ldr r2, = 0
	str r2, [r3, # 0x28] @ psc
	ldr r2, = 559
	str r2, [r3, # 0x2c] @ ARR
	movs r2, # 0x20
	str r2, [r3, # 0x04] @ TRGO
	movs r2, # 0x06
	str r2, [r3, # 0x08]
	movs r2, # 0x80
	@tim1chushiha:
	ldr r0, = 0x40012c00 @ tim1_cr1
	movs r1, # 0
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 223
	str r1, [r0, # 0x2c] @ ARR
	movs r1, # 0x20
	str r1, [r0, # 0x04] @ TRGO
	ldr r1, = 0x68
	str r1, [r0, # 0x1c] @ ccmr2  CC3
	ldr r1, = 0x100    @  CC3
	str r1, [r0, # 0x20] @ ccer
	ldr r1, = 0x8000
	str r1, [r0, # 0x44] @ BDTR
	ldr r1, = 0x800 @ CC3 DMA
	str r1, [r0, # 0x0c] @ DIER
	ldr r1, = 0x81
	str r1, [r0]
	str r2, [r3]
	ldr r0, = 0xe000e010
	ldr r1, = 559999
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	movs r1, # 0x07
	str r1, [r0]    @systick 开
	
	ldr r0, = lvbo_changdu
	ldr r1, = lvbo_youyi
	movs r2, # 200
	str r2, [r0]
	movs r2, # 12
	str r2, [r1]

	ldr r0, = cossin
	ldr r1, = cos_sin_biao_1k
	str r1, [r0]
	
	pop {r0-r3,pc}
	

	.ltorg


__pinlv_yanshi:
	push {lr}
	ldr r0, = 0xffffff
__pinlv_yanshi_xunhuan:
	subs r0, r0, # 1
	bne __pinlv_yanshi_xunhuan
	pop {pc}

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
	ldr r4, = 0x80008000
	str r4, [r0, # 0x10]
	ldr r1, = 0x01
	str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
	ldr r1, = 0x8c3         @连续0x2003 @触发0x8c3 @ 0xc43         @TIM3 0x8c3 @0x2003 @0x8c3
	str r1, [r0, # 0x0c]    @ 配置寄存器 1 (ADC_CFGR1)
	movs r1, # 0
	str r1, [r0, # 0x14]    @ ADC 采样时间寄存器 (ADC_SMPR)
	ldr r1, [r0, # 0x08]
	ldr r2, = 0x04         @ 开始转换
	orrs r1, r1, r2
	str r1, [r0, # 0x08]    @ 控制寄存器 (ADC_CR)
	mov pc, lr








	



_lcdxianshi:		  		@r0=LCD位置，r1=数据地址，r2=长度
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
_xielcd:					@入R0=8位,r1=0命令,r1=1数据
	push {r0-r5,lr}
	ldr r4, = lcd_beiguang  @ 量程开关 (第6位和第7位)
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
	ldr r5, = 0x4001300c
	movs r0, r2
	strb r0, [r5]
	bl __spi_mang
	bl __yanshi_595
	subs r0, r0, # 0x02
	strb r0, [r5]
	bl __spi_mang
	bl __yanshi_595
	mov r0, r1
	adds r0, r0, r3
	strb r0, [r5]
	bl __spi_mang
	bl __yanshi_595
	subs r0, r0, # 0x02
	strb r0, [r5]
	bl __spi_mang
	bl __yanshi_595
	pop {r0-r5,pc}
__spi_mang:
	push {lr}
	ldr r2, [r5, # 0x08]
	lsls r2, r2, # 24
	bmi __spi_mang
	pop {pc}
__yanshi_595:
	push {lr}
	ldr r2, = 0x2000
__yanshi__595:
	subs r2, r2, # 1
	bne __yanshi__595
	pop {pc}
	.ltorg

_zhuanascii:						@ 16进制转ASCII
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





	
_chufa:					@软件除法
	@ r0 除以 r1 等于 商(r0)
	push {r2-r4,lr}
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
	pop {r2-r4,pc}
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
_systickzhongduan:	@syzd
	push {r0-r4,lr}
__suan_dft:
	bl __dft
	ldr r2, = shangbi_rr
	ldr r3, = shangbi_ii
	str r0, [r2]
	str r1, [r3]
	mov r4, r0
	ldr r2, = lvboqizhizhen1
	ldr r0, =lvboqihuanchong1
	bl __lv_bo_qi
	ldr r1, = shangbi_i
	str r0, [r1]
	mov r1, r4
	ldr r2, = lvboqizhizhen
	ldr r0, =lvboqihuanchong
	bl __lv_bo_qi
	ldr r1, = shangbi_r
	str r0, [r1]

@	b __systick_fanhui

@	bkpt # 1
	ldr r0, = liangcheng
	ldr r1, = shangbi_liangcheng
	ldr r0, [r0]
	ldr r2, = 0x48000000
	ldrb r3, [r1, r0]
	ldrh r1, [r2, # 0x14]
	lsrs r1, r1, # 4
	lsls r1, r1, # 4
	ldr r0, = 0x48000400
	mov r4, r3
	lsrs r3, r3, # 1
	lsls r3, r3, # 1
	lsls r4, r4, # 31
	lsrs r4, r4, # 30
	orrs r3, r3, r1
	str r4, [r0, 0x14]
	str r3, [r2, # 0x14]

        ldr r0, = shangbi_r
	ldr r1, = shangbi_i
	ldr r0, [r0]
	ldr r1, [r1]
	bl __ji_suan_fu_du

	ldr r2, = liangcheng
	ldr r2, [r2]
	lsls r2, r2, # 2
	ldr r1, = jiaozhun_kaiguan
	ldr r1, [r1]
	cmp r1, # 1
	beq __jiao_zhun_mo_shi
__zheng_chang_mo_shi:	
	ldr r1, = f_mr10_jz
	b __du_dian_zu_biao
__jiao_zhun_mo_shi:
	ldr r1, = mr10_jz
__du_dian_zu_biao:	
	ldr r1, [r1, r2]
@	ldr r1, = 8849
	muls r0, r0, r1
	asrs r0, r0, # 15

	ldr r1, = z
	str r0, [r1]
	
__systick_fanhui:	
	ldr r0, = 0xe0000d04
	ldr r1, = 0x02000000
	str r1, [r0]                 @ 清除SYSTICK中断
	pop {r0-r4,pc}
aaa:
	bx lr
	.ltorg
@	sj
	.section .data
	.align 4
        .equ f_mr10_0,		0x8003c00
	.equ f_mr100_0,		0x8003c04
	.equ f_r1_0,		0x8003c08
	.equ f_r10_0,		0x8003c0c
	.equ f_r100_0,		0x8003c10
	.equ f_mr10_jz,		0x8003c14
	.equ f_mr100_jz,	0x8003c18
	.equ f_r1_jz,		0x8003c1c
	.equ f_r10_jz,		0x8003c20
	.equ f_r100_jz,		0x8003c24
	.equ fjiesuo, 	                0x1fffef62
	.equ ojiesuo,                   0x1fffef6e
	.equ quanca,                    0x1fffeff8
	.equ yeca,                      0x1fffefda
	.equ zica,                      0x1ffff020
	.equ xieflash,                  0x1fffef9a
	.equ zixie,                     0x1ffff048
	.equ xiebaohu,                  0x1ffff0a6
	.equ jiancedubaohu,             0x1ffff124
	.equ flashmang,                 0x1fffef7a
	
	.equ STACKINIT,		0x20001000
	.equ asciimabiao,	0x20000000
	.equ pinlv, 		0x20000020
	.equ shezhi_pinlv,	0x20000024
	.equ liangcheng,	0x20000038
	.equ jiaozhun_kaiguan,	0x200000ac
	.equ mr10_0,		0x200000b0
	.equ mr100_0,		0x200000b4
	.equ r1_0,		0x200000b8
	.equ r10_0,		0x200000bc
	.equ r100_0,		0x200000c0
	.equ mr10_jz,		0x200000c4
	.equ mr100_jz,		0x200000c8
	.equ r1_jz,		0x200000cc
	.equ r10_jz,		0x200000d0
	.equ r100_jz,		0x200000d4
	.equ anjian_hao,	0x200000d8
	.equ z,			0x200000dc
	.equ shangbi_rr,	0x200000e0
	.equ shangbi_ii,	0x200000e4
	.equ shangbi_r,		0x200000e8
	.equ shangbi_i,		0x200000ec
	.equ cossin,		0x200000f0
	.equ lvbo_changdu,	0x200000f4
	.equ lvbo_youyi,	0x200000f8
	.equ lcd_beiguang,  	0x200000fc
	.equ dianyabiao,	0x20000100

	.equ lvboqizhizhen,		0x200008d0
	.equ lvboqihuanchong,		0x200008d8
	.equ lvboqizhizhen1,            0x20000c00 
	.equ lvboqihuanchong1,          0x20000c08 
pinlv_biao:
	.word	__pinlv_1K +1 

an_jian_biao:
	.word __anjian0	+1
	.word __anjian1	+1
	.word __anjian2	+1
	.word __anjian3	+1
shangbi_liangcheng:
	@1毫欧-10毫欧
	@10毫欧-100毫欧
	@100毫欧-1欧
	@1欧-10欧
	@10欧-100欧
	.byte	0x0e, 0x06, 0x02, 0x03, 0x01
zukang_xiaoshu_dian:			
	.byte 2,3,4,2,3
zukang_dianzu_biao:
	.int 0,1,2,3,4
	.align 4
chuchang_dianzu_biao:
	.int 8849,8849,8849,8849,8849
zukang_danwei:
	@毫欧=0XF46D，欧=0XF420
	.int 0xf46d,0xf46d,0xf46d,0xf420,0xf420
dangwei_biao:
	.word haoou10
	.word haoou100
	.word ou1
	.word ou10
	.word ou100
jiaozhun:
	.ascii "jiao zhun mo shi"
jiaozhun_wan:
	.ascii "jiao zhun wan le"
duanlu:
	.ascii "duanlu qing ling"
duanlu_wancheng:
	.ascii "duanlu wan cheng"
yjmwxwx:
	.ascii "yjmwxwx-20230322"
kong:
	.int 0x20202020
_fu:
	.ascii "-"
haoou10:
	.ascii " 10mR"
haoou100:
	.ascii "100mR"
ou1:
	.ascii "   1R"
ou10:
	.ascii "  10R"
ou100:
	.ascii " 100R"
	.align 4
zheng_xian_1khz:
	.byte 112,114,117,120,123,125,128,131,134,137,139,142,145,147,150,153,155,158,160,163,165,168,170,172,175,177,179,181,184,186,188,190,192,194,196,197,199,201,203,204,206,207,209,210,211,212,214,215,216,217,218,218,219,220,220,221,222,222,222,223,223,223,223,223,223,223,223,222,222,222,221,220,220,219,218,218,217,216,215,214,212,211,210,209,207,206,204,203,201,199,197,196,194,192,190,188,186,184,181,179,177,175,172,170,168,165,163,160,158,155,153,150,147,145,142,139,137,134,131,128,125,123,120,117,114,112,109,106,103,100,98,95,92,89,86,84,81,78,76,73,70,68,65,63,60,58,55,53,51,48,46,44,42,39,37,35,33,31,29,27,26,24,22,20,19,17,16,14,13,12,11,9,8,7,6,5,5,4,3,3,2,1,1,1,0,0,0,0,0,0,0,0,1,1,1,2,3,3,4,5,5,6,7,8,9,11,12,13,14,16,17,19,20,22,24,26,27,29,31,33,35,37,39,42,44,46,48,51,53,55,58,60,63,65,68,70,73,76,78,81,84,86,89,92,95,98,100,103,106,109
	.align 4

cos_sin_biao_1k:	
	.int 0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC981,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6B,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93EE,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC981,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6B,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02B,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x367F,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4495,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02B,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x367F,0x73D1,0x3DAA,0x702A,0x4495,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD5,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC981,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6B,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93EE,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC981,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6B,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02B,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x367F,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4495,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02B,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x367F,0x73D1,0x3DAA,0x702A,0x4495,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD5,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC981,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6B,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93EE,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC981,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6B,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02B,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x367F,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4495,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02B,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x367F,0x73D1,0x3DAA,0x702A,0x4495,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD5,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC981,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6B,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93EE,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC981,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6B,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02B,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x367F,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4496,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C13,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02B,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x367F,0x73D1,0x3DAA,0x702A,0x4495,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD5,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC980,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6B,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93EE,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC981,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6A,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02B,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x3680,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4496,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02C,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100B,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x367F,0x73D1,0x3DAA,0x702A,0x4495,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD5,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC981,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6A,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93EE,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC980,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6A,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02C,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x3680,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4496,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02B,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x3680,0x73D1,0x3DAA,0x702A,0x4496,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD5,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02C,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC980,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6A,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93EE,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC981,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6A,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02B,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD4,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x367F,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4496,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02B,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x3680,0x73D1,0x3DAA,0x702A,0x4496,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD4,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF5,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC981,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6B,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93EE,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC980,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6B,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02B,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x367F,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4496,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02B,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x367F,0x73D1,0x3DAA,0x702A,0x4496,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD5,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC981,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6A,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5196,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93ED,0x3DAA,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD5,0xFFFF8406,0x17FC,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF6,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02B,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC981,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6B,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE6A,0xFFFF9873,0xFFFFB4C4,0xFFFF93ED,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC256,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02B,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100A,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x367F,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4495,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02C,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x367F,0x73D1,0x3DAA,0x702A,0x4495,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C13,0x4495,0x702A,0x3DA9,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD4,0x7DBB,0x17FB,0x7EFD,0x100A,0x7FBF,0x0809,0x8000,0x0000,0x7FBF,0xFFFFF7F7,0x7EFD,0xFFFFEFF6,0x7DBB,0xFFFFE804,0x7BFA,0xFFFFE02B,0x79BC,0xFFFFD873,0x7702,0xFFFFD0E2,0x73D1,0xFFFFC981,0x702A,0xFFFFC256,0x6C12,0xFFFFBB6B,0x678D,0xFFFFB4C4,0x62A0,0xFFFFAE69,0x5D4E,0xFFFFA861,0x579F,0xFFFFA2B2,0x5197,0xFFFF9D60,0x4B3C,0xFFFF9873,0x4495,0xFFFF93ED,0x3DA9,0xFFFF8FD6,0x367F,0xFFFF8C2F,0x2F1E,0xFFFF88FE,0x278D,0xFFFF8644,0x1FD4,0xFFFF8406,0x17FB,0xFFFF8245,0x100A,0xFFFF8103,0x0809,0xFFFF8041,0x0000,0xFFFF8000,0xFFFFF7F7,0xFFFF8041,0xFFFFEFF5,0xFFFF8103,0xFFFFE804,0xFFFF8245,0xFFFFE02C,0xFFFF8406,0xFFFFD873,0xFFFF8644,0xFFFFD0E2,0xFFFF88FE,0xFFFFC981,0xFFFF8C2F,0xFFFFC256,0xFFFF8FD6,0xFFFFBB6A,0xFFFF93EE,0xFFFFB4C4,0xFFFF9873,0xFFFFAE69,0xFFFF9D60,0xFFFFA861,0xFFFFA2B2,0xFFFFA2B2,0xFFFFA861,0xFFFF9D60,0xFFFFAE69,0xFFFF9873,0xFFFFB4C4,0xFFFF93EE,0xFFFFBB6B,0xFFFF8FD6,0xFFFFC257,0xFFFF8C2F,0xFFFFC981,0xFFFF88FE,0xFFFFD0E2,0xFFFF8644,0xFFFFD873,0xFFFF8406,0xFFFFE02C,0xFFFF8245,0xFFFFE804,0xFFFF8103,0xFFFFEFF6,0xFFFF8041,0xFFFFF7F7,0xFFFF8000,0x0000,0xFFFF8041,0x0809,0xFFFF8103,0x100B,0xFFFF8245,0x17FC,0xFFFF8406,0x1FD5,0xFFFF8644,0x278D,0xFFFF88FE,0x2F1E,0xFFFF8C2F,0x367F,0xFFFF8FD6,0x3DAA,0xFFFF93EE,0x4495,0xFFFF9873,0x4B3C,0xFFFF9D60,0x5197,0xFFFFA2B2,0x579F,0xFFFFA861,0x5D4E,0xFFFFAE69,0x62A0,0xFFFFB4C4,0x678D,0xFFFFBB6B,0x6C12,0xFFFFC256,0x702A,0xFFFFC981,0x73D1,0xFFFFD0E2,0x7702,0xFFFFD873,0x79BC,0xFFFFE02B,0x7BFA,0xFFFFE804,0x7DBB,0xFFFFEFF6,0x7EFD,0xFFFFF7F7,0x7FBF,0x0000,0x8000,0x0809,0x7FBF,0x100A,0x7EFD,0x17FC,0x7DBB,0x1FD5,0x7BFA,0x278D,0x79BC,0x2F1E,0x7702,0x3680,0x73D1,0x3DAA,0x702A,0x4495,0x6C12,0x4B3C,0x678D,0x5197,0x62A0,0x579F,0x5D4E,0x5D4E,0x579F,0x62A0,0x5197,0x678D,0x4B3C,0x6C12,0x4495,0x702A,0x3DAA,0x73D1,0x367F,0x7702,0x2F1E,0x79BC,0x278D,0x7BFA,0x1FD4,0x7DBB,0x17FC,0x7EFD,0x100A,0x7FBF,0x0809


	.end
