	@ stm32f030f4p6 asm
	 .thumb
	.syntax unified
	.section .data
	.equ STACKINIT,                 0x20001000
	.equ cishu,			0x20000000
	.equ flashdizhi,		0x20000004
	.equ flashdizhi1,		0x20000008
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
_jianceflash:
	ldr r0, = 0x8000800
	ldr r2, = 0xffffffff
	ldr r1, [r0]
	cmp r1, r2
	bne _zhaozuidade
	ldr r3, = cishu
	movs r4, # 0
	str r4, [r3]
	str r4, [r3, # 0x04]
	bl _xieflash

_zhaozuidade:
	bkpt 1
	ldr r0, = 0x8000800
	ldr r1, = 0x400
	ldr r2, = 0xc00
	movs r5, # 0
	mov r6, r5
_zhaozuidadexunhuan:
	ldr r3, [r0, r5]
	cmp r3, r6
	bls _xiaoyu
	mov r6, r3
	mov r4, r5               
_xiaoyu:	
	adds r5, r5, r1
	cmp r5, r2
	bne _zhaozuidadexunhuan
	mov r3, r0
	mov r5, r0
	add r3, r3, r2
	add r0, r0, r4
	cmp r0, r3
	bne _meichaochufanwei
	ldr r0, = 0x8000800
_meichaochufanwei:
	ldr r4, = flashdizhi
	str r0, [r4]
	subs r5, r5, r1
	subs r0, r0, r1
	cmp r0, r5
	bne _meichaochufanwei1
	ldr r0, = 0x8001000
_meichaochufanwei1:
	ldr r4, = flashdizhi1
	ldr r1, = cishu
	str r0, [r4]
	ldr r2, [r0]
	str r2, [r1]
_systick:	                                  @ systick定时器初始化
	ldr r0, = 0xe000e010
	ldr r1, = 10000000
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	movs r1, # 0x07
	str r1, [r0]
tingxiale:
	b tingxiale
_xieflash:				@ flsh解锁
	mov r6, r0
	ldr r0, = 0x40022000
	ldr r1, = 0x45670123
	str r1, [r0, # 0x04]
	ldr r1, = 0xcdef89ab
	str r1, [r0, # 0x04]
	
	mov r4, r6
_flashmang:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang
	movs r1, # 2
	str r1, [r0, # 0x10]
	str r4, [r0, # 0x14]
	movs r1, # 0x42
	str r1, [r0, # 0x10]
						@写FLASH
	mov r7, r6
	ldr r4, = cishu
_flashmang1:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang1
	movs r1, # 1
	str r1, [r0, # 0x10]
	ldrh r3, [r4]
	strh r3, [r7]
_flashmang2:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang2
	ldrh r3, [r4, # 0x02]
	strh r3, [r7, # 0x02]
_flashmang3:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang3
	@movs r1, # 0x80
	@str r1, [r0]          		@flsh上锁
	ldr r0, = 0xe000ed0c
	ldr r1, = 0x05fa0004
	@str r1, [r0]          		@复位
ddd:
	b ddd
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
	ldr r1, = flashdizhi
	ldr r2, = flashdizhi1
	ldr r6, = cishu
	ldr r3, [r1]
	ldr r4, [r2]
	ldr r5, [r3]
	adds r5, r5, # 1
	str r5, [r6]
	mov r0, r4
	b _xieflash
