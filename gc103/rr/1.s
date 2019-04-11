	 .thumb                 
         .syntax unified
.section .data
	.equ STACKINIT,         0x20005000
yjmwxwx: .ascii "jlink ob boot 2017-11-19 yjmwxwx"
.section .text
_xiangliangbiao:
	.word STACKINIT
	.word _start + 1
	.word _nmi_handler + 1
	.word _hard_fault  + 1
	.word _memory_fault + 1
	.word _bus_fault + 1
	.word _usage_fault + 1

_start:
tingting:

	mov r1, r1

	b tingting	
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
