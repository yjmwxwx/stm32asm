	@led闪烁
	.thumb
	.syntax unified
	.equ GPIOC_CRH,		0x40011004
	.equ GPIOC_ODR,		0x4001100C
	.equ RCC_APB2ENR,	0x40021018	
	.equ STACHINIT,		0x20005000	@堆栈顶
	.equ LEDDELAY,		800000		@LED延时
vectors:					@向量表
	.word STACHINIT	
	.word _start + 1			@复位向量，+1 表示thumb
        .word _nmi_handler + 1 
        .word _hard_fault + 1 
        .word _memory_fault + 1 
        .word _bus_fault + 1
        .word _usage_fault + 1
_start:
	mov r0, r0
	mov r0, r0
_nmi_handler:	
_hard_fault:	
_memory_fault:	
_bus_fault:	
_usage_fault:
	bx lr
