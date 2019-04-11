        .thumb                 
        .syntax unified
 
	.equ STACKINIT,           0x20005000	


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
	.word	0
	.word	0
	.word	0	
        .word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word   0
	.word	0
	.word 	0
	.word	0





_start:
	ldr r0, = STACKINIT    

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
	


