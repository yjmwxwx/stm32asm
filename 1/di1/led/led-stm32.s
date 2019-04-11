

@@@ Directives
        .thumb                  
        .syntax unified

@@@ Equates
        .equ RAMBASE, 0x20000000 
        .equ STACKINIT,   0x20005000
       
        .equ LEDDELAY,    800000
        
.section .text
        .org 0

@@@ Vectors
vectors:        
        .word STACKINIT         @ stack pointer value when stack is empty
        .word _start + 1        @ reset vector (manually adjust to odd for thumb)
        .word _nmi_handler + 1  @ 
        .word _hard_fault  + 1  @ 
        .word _memory_fault + 1 @ 
        .word _bus_fault + 1    @ 
        .word _usage_fault + 1  @ 

_start:

  	ldr r0, = 0x40021018 
	ldr r1, = 0x80C
	str r1, [r0]



	ldr r0, = 0x40010804
	ldr r1, = 0x44444333
	str r1, [r0]

	ldr r0, = 0x40010C04
	ldr r1, = 0x33344444
	str r1, [r0]

        mov r2, 0             
        mov r3, 0x700
	mov r4, 0xE000       
        ldr r6, = 0x4001080C 
	ldr r7, = 0x40010C0C  
        
loop:
        str r2, [r6] 
	str r2, [r7]          
        ldr r1, = LEDDELAY
delay1:
        subs r1, 1
        bne delay1
        
        str r3, [r6]
	str r4, [r7]          
        ldr r1, = LEDDELAY
delay2:
        subs r1, 1
        bne delay2

        b loop                
_dummy:                       
_nmi_handler:
_hard_fault:
_memory_fault:
_bus_fault:
_usage_fault:
        add r0, 1
        add r1, 1
        b _dummy    
