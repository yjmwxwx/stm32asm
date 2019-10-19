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
_io_she_zhi:				@io设置	
	ldr r6, = RCC_APB2ENR
	mov r0, # 0x10
	str r0, [r6]		@开IO时钟
	ldr r6, = GPIOC_CRH	
	ldr r0, = 0x44434444	
	str r0, [r6]		@GPIOC_12模式推挽输出
	mov r2, # 0		
	mov r3, # 0x1000	@ IO 12
	ldr r6, = GPIOC_ODR
led_xun_huan:			@LED循环
	str r2, [r6]		@LED低
	ldr r1, = LEDDELAY	@r1=LED延时数
yan_shi1:			@延时1
	subs r1, r1, # 1	@延时数减1
	bne yan_shi1		@不到0跳到延时1
	str r3, [r6]		@LED高
	ldr r1, = LEDDELAY	@r1=LED延时数
yan_shi2:			@延时2
	subs r1, r1, # 1	@延时书减1
	bne yan_shi2		@不到0跳转延时2
	b led_xun_huan		@ 跳到LED循环
_nmi_handler:	
_hard_fault:	
_memory_fault:	
_bus_fault:	
_usage_fault:
	bx lr
