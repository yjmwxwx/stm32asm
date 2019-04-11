	 .thumb                 
         .syntax unified
.section .data
	.equ STACKINIT,         0x20005000
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
	
_bijiaodaxiao:
	push {r4-r6,lr}
	ldr r6, = 0x20000030  @ x
	ldrb r5, [r6]
	cmp r5, # 105
	bcc _bijiao
	mov r4, # 3
	strb r4, [r6, # 0x01]
	b _bijiaowanle
_bijiao:	
	cmp r5, # 95
	bhi _dayu
	mov r4, # 1
	strb r4, [r6, # 0x01]
	b _bijiaowanle
_dayu:
	mov r4, # 2
	strb r4, [r6, # 0x01]
_bijiaowanle:
	pop {r4-r6,pc}
	
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
