

@@@ Directives
        .thumb                
        .syntax unified
	.global _start




@@@ Equates
        .equ RAMBASE, 0x20000000 

	.equ GPIOC_CRH,   0x40011004
        .equ GPIOC_ODR,   0x4001100C
        .equ RCC_APB2ENR, 0x40021018
        .equ STACKINIT,   0x20005000
	.equ systkkz, 	  0xE000E010
	.equ systkcz,	  0xE000E014
	.equ syst1,       0xE000E014
	.equ syst2,       0xE000E018
      
	
	


        
.section .text
        .org 0

vectors:        
        .word STACKINIT            
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
	.word 0
	.word 0
	.word 0
	.word 0
	.word _systick + 1

.type start, function


_start:
	

	

 

loop:
	

        b      loop

	
	

	   

	

	

                       
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_systick:
	bx lr






    
