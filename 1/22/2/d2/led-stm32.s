        .thumb                 
        .syntax unified
        .equ RAMBASE, 		  0x20000000
	.equ GPIOC_CRH,   0x40011004
        .equ GPIOC_ODR,   0x4001100C
        .equ RCC_APB2ENR,    	  0x40021018
	.equ STACKINIT,           0x20005000
	.equ SYSTICKCSR,          0xE000E010
	.equ SYSTICKRVR,          0xE000E014
	.equ SYSTICKCVR,          0xE000E018
	.equ SYSTICKCALVR,	  0xE000E01C
	.equ SCB_VTOR_TBLOFF,	  0x1FFFFF80	
        .equ SCB_VTOR_TBLBASE,    0x20000000	
	.equ VTOR,	          0xE000ED08


.section .text
	.global vectors
        .org 0
	.global _start
vectors:
        .word STACKINIT            
        .word _start 	      
        .word _nmi_handler 
        .word _hard_fault  
        .word _memory_fault 
        .word _bus_fault 
        .word _usage_fault
	.word 0
	.word 0
	.word 0
	.word 0
	.word _svc
	.word _debugmon
	.word 0
	.word _pendsv
	.word _systick

_start:
	@@set the preload value to the max (this is a 24-bit downcounting timer)
        ldr r2, = SYSTICKRVR
        mov r0, # 0x00FFFFFF
        str r0, [r2]

        @@set the clock source to SYSCLK (fastest) and enable the timer
        ldr r2, = SYSTICKCSR	
        mov r0, # 0x07
        str r0, [r2]
	@@
        ldr r2, = RCC_APB2ENR
        mov r0, 0x10
        str r0, [r2]
	@@
	ldr r2, = GPIOC_CRH
        ldr r0, = 0x44434444
        str r0, [r2]
	@@
	ldr r2, = GPIOC_ODR
	mov r0, 0
	str r0, [r2]


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
_svc:
	bx lr
_debugmon:
	bx lr 
_pendsv:
	bx lr
_systick:

	bx lr 	
	


 
