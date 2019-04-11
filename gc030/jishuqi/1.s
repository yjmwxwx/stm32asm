	@ stm32f030f4p6 asm
	@计数器
	@100小时，没测试
	@到时间GPIOA0-GPIOA7=高， 没测试。
	@ 没测试
	 .thumb
	.syntax unified
	.section .data
	.equ STACKINIT,         0x20001000
	.equ jishu,		0x20000000
	.equ yaoxiedeflash,	0x20000004
.section .text
xiangliangbiao:        
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
	.word _systickzhongduan + 1
_start:
	ldr r0, = 0x40022000
	ldr r1, = 0x45670123
	str r1, [r0, # 0x04]
	ldr r1, = 0xcdef89ab
	str r1, [r0, # 0x04]
	
	ldr r0, = 0x8000800
	ldr r2, = 0xa55a
	ldrh r1, [r0]
	cmp r1, r2
	beq _zhaozuidadeshu
	
	ldr r2, = yaoxiedeflash
	ldr r0, = jishu
	ldr r1, = 0x8000c00
	movs r3, # 0
	
	str r3, [r0]
	str r1, [r2]
	
	ldr r0, = 0x40022000
	ldr r4, = 0xa55a
	ldr r7, = 0x8000800
_xieflashmang:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _xieflashmang
	movs r1, # 1
	str r1, [r0, # 0x10]
	strh r4, [r7]
	
_xieflashmang1:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _xieflashmang1
	
_zhaozuidadeshu:	
	ldr r0, = 0x8000c00
	ldr r1, = 0x3400
	ldr r6, = 0xffffffff
	movs r2, # 0
	mov r3, r2
_zhaozuidade:
	ldr r4, [r0, r2]
	cmp r4, r3
	bls _zhaozuidade1
	mov r5, r2
	mov r3, r4
_zhaozuidade1:
	adds r2, r2, # 4
	cmp r2, r1
	bne _zhaozuidade
	cmp r3, r6
	bne _bushiffff
	subs r5, r5, # 4
	mov r7, r5
	lsls r7, r7,  # 31
	bpl _bushiffff
	movs r5, # 0
_bushiffff:	
	ldr r2, = yaoxiedeflash
	ldr r1, = jishu
	add r0, r0, r5
	str r0, [r2]
	ldr r3, [r0]
	str r3, [r1]
_systick:			@ systick定时器初始化
	
	ldr r0, = 0xe000e010
	ldr r1, = 10000000
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	movs r1, # 0x07
	str r1, [r0]

_waisheshizhong:	                         @ 外设时钟
	ldr r0, = 0x40021000
	ldr r1, = 0x460005
	str r1, [r0, # 0x14]
	ldr r0, = 0x48000000
	ldr r1, = 0x28005555
	str r1, [r0]
tingting:
	ldr r6, = 0xffffffff
	ldr r0, = jishu
	ldr r1, = 360000
	ldr r2, [r0]
	cmp r2, r6
	beq tingting
	cmp r2, r1
	bls tingting
	ldr r2, = 0x48000018
	ldr r3, = 0xe000e010
	movs r4, # 0
	movs r1, # 0xff
	str r1, [r2]
	str r4, [r3]
	b tingting
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
_systickzhongduan:
	ldr r0, = 0xe0000d04
	ldr r1, = 0x02000000
	str r1, [r0]                 @ 清除SYSTICK中断
	cpsid i
	 ldr r0, = 0x40022000
	ldr r1, = jishu
	ldr r2, [r1]
	adds r2, r2, # 1
	str r2, [r1]
	ldr r7, = yaoxiedeflash
	ldr r6, = 0x8004000
	ldr r3, [r7]
	adds r3, r3, # 4
	cmp r3, r6
	bne _meichaochu
	ldr r4, = 0x8000c00
	mov r3, r4
	
	movs r5, # 14
	ldr r6, = 0x400
_caflashmang:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _caflashmang
	movs r1, # 2
	str r1, [r0, # 0x10]
	str r4, [r0, # 0x14]
	movs r1, # 0x42
	str r1, [r0, # 0x10]
	add r4, r4, r6
	subs r5, # 1
	bne _caflashmang
	
_meichaochu:	
	str r3, [r7]
	mov r7, r3
	mov r3, r2
	

_flashmang1:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang1
	
	movs r1, # 1
	str r1, [r0, # 0x10]
	strh r3, [r7]
	lsrs r3, r3, # 16
	
_flashmang2:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang2
	
	strh r3, [r7, # 0x02]
_flashmang3:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang3
	cpsie i
	bx lr
