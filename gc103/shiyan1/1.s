	 .thumb                 
         .syntax unified
.section .data
	.equ STACKINIT,         0x20005000
yjmwxwx: .ascii "jlink ob boot 2017-11-19 yjmwxwx"
.section .text
_xiangliangbiao:
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
	.word _systickdingshiqi +1
_start:
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
	ldr r0, = 0xe000e010
	ldr r1, = 0xffffff
	str r1, [r0, # 0x04]
	str r1, [r0, # 0x08]
	mov r1, # 0x07
	str r1, [r0]
	
	mov r1, # 0
d1:
	ldr r0, = yjmwxwx
	sub sp, sp, # 0x5000
	str r0, [sp]
	add sp, sp, # 0x5000
	add r1, r1, # 1
	b d1
	
tingting:
	b tingting
	
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
_systickdingshiqi:
	b tingting
