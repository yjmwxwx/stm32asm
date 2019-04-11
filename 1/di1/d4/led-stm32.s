
        .thumb                 
        .syntax unified
        .equ GPIOC_CRH,   0x40011004
        .equ GPIOC_ODR,   0x4001100C
        .equ RCC_APB2ENR, 0x40021018
        .equ STACKINIT,   0x20005000
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
_start:

	mov r0, #0
	mov r1, #0
	mov r2, #0
	mov r3, #0
	mov r4, #0
	mov r5, #0
	mov r6, #0
	mov r7, #0
shizhong:

	ldr r1, = 0xE000E010
	ldr r0, = 0xE000E014
	ldr r2, = 0xE000E018
	
	mov r3, #0
	str r3, [r1]

	ldr r3, = 0x00FFFFF
	str r3, [r0]
	str r3, [r2]

	mov r3, # 0x07
	str r3, [r1]


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
	cmp r5, #3
	bne yanshi
	mov r5, #0
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
         

