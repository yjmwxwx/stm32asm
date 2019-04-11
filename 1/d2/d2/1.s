@@@
        .thumb                 
        .syntax unified

.section .data

yjm:	 .short 0x001f, 0xf81f, 0xffe0, 0x07ff, 0xf800
wxwx:	 .byte 0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00		
 




        .equ STACKINIT, 	0x20005000
	.equ gpioddi,   	0x40011400
        .equ gpiododr,   	0x4001140C
        .equ RCC_APB2ENR,	0x40021018 @rccAPB2ENR
	.equ syskz,		0xE000E010 @ 控制寄存器
	.equ syscz,		0xE000E014 @systick定时器重载
	.equ syssz,		0xE000E018 @systick计数值查询
	.equ rcckz,		0x40021000 @rcc时钟控制寄存器
	.equ rccpz,		0x40021004 @时钟配置寄存器
	.equ flashacr,		0x40022000 @flash闪存访问寄存器
	.equ ledliang,		0x04
	.equ yanshishu,		200
	.equ lcdpianyi,	        240

	.equ lcdpy,		0x20000010
	
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
  
          .include "2.s"
   

bl pllshizhong

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
	
	bl yanshi 

	ldr r0, = gpiododr
	mov r1, # 0
	str r1, [r0]
	bl yanshi

	b ledhanshu



yanshi:
	ldr r0, = yanshishu
	cmp r5, r0
	bne yanshi
	mov r5, 0
	bx lr

	

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
	adds r5, 1	
	bx lr
         

