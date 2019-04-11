

@@@ Directives
        .thumb                 
        .syntax unified

.section .data

yjm:	 .short 0x001f, 0xf81f, 0xffe0, 0x07ff, 0xf800

wxwx:	 .ascii "JNZ" 




        .equ GPIOD_CRL,   0x40011400
        .equ GPIOD_ODR,   0x4001140C
        .equ RCC_APB2ENR, 0x40021018
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


	ldr r5, = wxwx

        @@ Enable the Port C peripheral clock by setting bit 4
        ldr r6, = RCC_APB2ENR
        mov r0, 0x20
        str r0, [r6]
        

        ldr r6, = GPIOD_CRL
        ldr r0, = 0x44444344
        str r0, [r6]


        mov r2, 0              @ value to turn on LED
        mov r3, 0x04
        ldr r6, = GPIOD_ODR    @  point to Port C output data register

        
loop:
        str r2, [r6]           @ clear Port C, pin 12, turning on LED
        ldr r1, = LEDDELAY
delay1:
        subs r1, 1
        bne delay1
        
        str r3, [r6] 
        ldr r1, = LEDDELAY
delay2:
        subs r1, 1
        bne delay2
        b loop                 @ continue forever

_dummy:                        @ if any int gets triggered, just hang in a loop
_nmi_handler:
_hard_fault:
_memory_fault:
_bus_fault:
_usage_fault:
	bx lr 
