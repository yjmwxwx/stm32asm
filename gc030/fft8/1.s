        .thumb                 
        .syntax unified      
	.align 2
        .global _start
.section .data
	.equ duizhanding, 0x20001000
.section .text
vectors:        
        .word duizhanding        
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
_start:
	b fftjisuan

_tingting:
	b _tingting

_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr


	
	