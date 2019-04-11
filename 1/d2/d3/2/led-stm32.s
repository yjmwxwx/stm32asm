        .thumb                 
        .syntax unified
.section .data
yjm:	 .short 0x001f, 0xf81f, 0xffe0, 0x07ff, 0xf800
wxwx:	 .byte 0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00		
        .equ STACKINIT, 	0x20005000
	.equ yanshius,	        0x20000000 @延时us
	.equ yanshims,		0x20000004 @延时ms
        .equ STACKINIT, 	0x20005000
	.equ gpioddi,   	0x40011400
        .equ gpiododr,   	0x4001140C
        .equ RCC_APB2ENR,	0x40021018 @rccAPB2ENR
	.equ ledliang,		0x04
.section .text
vectors:        
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
	.word _dingshiqi + 1
_start:
	@@AFIO-MAPR 开SWD模式
	ldr r0, = 0x40010004
	ldr r1, = 0x02000000
	str r1, [r0]
shizhong:
	ldr r0, = 0x40021000
	ldr r1, = 0x14D83
	str r1, [r0]
gsszbz: 
	ldr r2, [r0]
	ldr r1, = 0x20000
	tst r1, r2           @高速时钟标志位           
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
	bne rccgg
	b chaxun
rccgg:
	ldr r0, = 0x40021004
	ldr r1, = 0x1D8402
	str r1, [r0]
sytickchushihua:

	ldr r0, = 0xE000E010
	mov r1, # 0
	str r1, [r0]
	ldr r1, = 0x3ff
	str r1, [r0,  # 4]
	str r1, [r0,  # 8]
	mov r1, # 0x07
	str r1, [r0]
ledled:

        ldr r0, = RCC_APB2ENR
        mov r1, 0x39
        str r1, [r0]

        ldr r0, = gpioddi
        ldr r1, = 0x44444344
        str r1, [r0]

ledhanshu:
	ldr r0, = gpiododr
	ldr r1, = ledliang
	str r1, [r0]




	b ledhanshu
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
_dingshiqi:	
	bx lr
         

