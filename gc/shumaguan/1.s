	 .thumb                 
         .syntax unified
.section .data
shumaguanmabiao: .byte 0x88,0xbe,0xc4,0x94,0xb2,0x91,0x81,0xbc,0x80,0x90,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf
	
	
	
        	.equ STACKINIT,          0x20005000
.section .text
xiangliangbiao:
	                .word STACKINIT
	                .word _start + 1
	                .word _nmi_handler + 1
	                .word _hard_fault  + 1
	                .word _memory_fault + 1
	                .word _bus_fault + 1
	                .word _usage_fault + 1
	
_start:


	ldr r0, = 16
	ldr r1, = 4
	ldr r2, = 15
	udiv r3, r0, r1
	udiv r4, r2, r1
	b _start

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
	
