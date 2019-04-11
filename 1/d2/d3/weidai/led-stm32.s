        .thumb                  
        .syntax unified
        .equ STACKINIT,   0x20005000      
        .equ LEDDELAY,    800000      
.section .text
vectors:       
        .word STACKINIT        
        .word _start + 1        
        .word _nmi_handler + 1 
        .word _hard_fault  + 1  
        .word _memory_fault + 1 
        .word _bus_fault + 1    
        .word _usage_fault + 1 
_start:
        ldr r0, = 0x40021018
        mov r1, # 0x39
        str r1, [r0]
        ldr r0, = 0x40011400
        ldr r1, = 0x44444344
        str r1, [r0]
	mov r2, # 1
	mov r3, # 0 
	ldr r6, = 0x42228188       
loop:
        str r2, [r6]           
        ldr r1, = LEDDELAY
delay1:
        subs r1, 1
        bne delay1       
        str r3, [r6]         
        ldr r1, = LEDDELAY
delay2:
        subs r1, 1
        bne delay2
        b loop                                     
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
