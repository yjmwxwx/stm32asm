@@@
        .thumb                 
        .syntax unified
@@@
        .equ STACKINIT, 	0x20005000
	.equ GPIOC_CRH,   	0x40011004
        .equ GPIOC_ODR,   	0x4001100C
        .equ RCC_APB2ENR,	0x40021018
	.equ syskz,		0xE000E010 @ 控制寄存器
	.equ syscz,		0xE000E014 @systick定时器重载
	.equ syssz,		0xE000E018 @systick计数值查询
	.equ rcckz,		0x40021000 @rcc时钟控制寄存器
	.equ rccpz,		0x40021004 @时钟配置寄存器
	.equ flashacr,		0x40022000 @flash闪存访问寄存器 		 		   

	
.section .text

vectors_table:
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
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word _tim3dingshiqi +1 

_start:
chushihua:
	mov r0, #0
	mov r1, #0
	mov r2, #0
	mov r3, #0
	mov r4, #0
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0
shizhong:
	ldr r0, = rcckz
	ldr r1, = 0x14D83
	str r1, [r0]
gsszbz: @高速时钟标志位
	ldr r1, [r0]
	ldr r2, = 0x34D83
	cmp r2, r1 
	bne	gsszbz

	@FLASH缓冲 缓冲开启 
	ldr r0, = flashacr
	mov r1, # 0x00000032
	str r1, [r0]
	@设置
	ldr r0, = rccpz
	ldr r1, = 0x1D8400
	str r1, [r0]
	
	ldr r0, = rcckz
	ldr r1, = 0x1033D03
	str r1, [r0]
chaxun:
	ldr r1, [r0]
	ldr r2, = 0x03033D03
	cmp r1, r2
	bne chaxun

	ldr r0, = rccpz
	ldr r1, = 0x1D8402
	str r1, [r0]

	
	
systick:

	ldr r1, = syskz
	ldr r0, = syscz
	ldr r2, = syssz
	
	mov r3, #0
	str r3, [r1]

	ldr r3, = 0x2328
	str r3, [r0]
	str r3, [r2]

	mov r3, # 0x03
	str r3, [r1]

timdingshiqi:

	ldr r0, = 0xE000E100
	ldr r1, = 0x20000000
	str r1, [r0]
	
	ldr r0, = 0x4002101C
	mov r1, # 0x02 
	str r1, [r0] @ 开TIM3时钟

	ldr r0, = 0x4000042C @TIM ARR自动重载寄存器
	ldr r1, = 0x1388
	str r1, [r0]

	ldr r0, = 0x40000428 @psc预分频器
	ldr r1, = 0x1C1F
	str r1, [r0]

	ldr r0, = 0x4000040C @tim dier 允许更新中断
	mov r1, # 0x41
	str r1, [r0] 

	ldr r0, = 0x40000400 @使能定时器3
	mov r1, #0x81
	str r1, [r0]

		
	


ledled:

        ldr r6, = RCC_APB2ENR
        mov r0, 0x10
        str r0, [r6]


        ldr r6, = GPIOC_CRH
        ldr r0, = 0x44434444
        str r0, [r6]

        mov r2, 0            
        mov r3, 0x1000        
        ldr r6, = GPIOC_ODR  
main: 
                     
	str r3, [r6]
	bl yanshi
	str r2, [r6]
	bl yanshi
	b main

yanshi:	
	cmp r5, #2
	bne yanshi
	mov r5, # 0
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
	
	bx lr 
_tim3dingshiqi:
	adds r5, 1
	ldr r0, = 0x40000410
	mov r1, #0
	str r1, [r0]
	bx lr	
         

