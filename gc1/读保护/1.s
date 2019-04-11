	 .thumb                 
         .syntax unified
	.section .data
	.equ zhanding, 0x20000100
	.equ ledyanshi, 8000000
	.section .text
xiangliangbiao:
	                .word zhanding
	                .word _start + 1
	                .word _nmi_handler + 1
	                .word _hard_fault  + 1
	                .word _memory_fault + 1
	                .word _bus_fault + 1
	                .word _usage_fault + 1
_start:
	ldr r0, = 0x40022000
	mov r1, # 0x00000032
	str r1, [r0]           @FLASH缓冲 缓冲开启
	ldr r0, = 0x40021000
	ldr r1, = 0x100000
	str r1, [r0, # 0x04]
	ldr r4, = 0x42420000
	mov r1, # 1
	str r1, [r4, # 0x60]
ceshi:
	ldr r1, [r0]
	lsls r1, r1, # 0x06
	bpl ceshi
	ldr r1, = 0x100002
	str r1, [r0, # 0x04]
	cpsid i
shiyan:	
	ldr r0, = 0x40022000
	ldr r1, = 0x45670123
	ldr r2, = 0xcdef89ab
	str r1, [r0, # 0x04]
	str r2, [r0, # 0x04]
	str r1, [r0, # 0x08]
	str r2, [r0, # 0x08]
	bl shancunmang
	ldr r1, [r0, # 0x10]
	orr r1, r1, # 0x20
	str r1, [r0, # 0x10]
	ldr r1, [r0, # 0x10]
	orr r1, r1, # 0x40
	str r1, [r0, # 0x10]
	bl shancunmang
	ldr r1, [r0, # 0x10]
	bic r1, r1, # 0x20
	str r1, [r0, 0x10]
	bl shancunmang
	ldr r1, [r0, # 0x10]
	orr r1, r1, # 0x10
	str r1, [r0, # 0x10]
	ldr r2, = 0x1ffff800
	mov r3, # 0xff
	strh r3, [r2]
	bl shancunmang
	strh r3, [r2, # 0x02]
	bl shancunmang
	strh r3, [r2, # 0x04]
	bl shancunmang
	strh r3, [r2, # 0x06]
	bl shancunmang
	strh r3, [r2, # 0x08]
	bl shancunmang
	strh r3, [r2, # 0x0a]
	bl shancunmang
	strh r3, [r2, # 0x0c]
	bl shancunmang
	mov r1, # 0
	str r1, [r0, # 0x10]
	
	b ting
	
shancunmang:
	ldr r1, [r0, # 0x0c]
	tst r1, # 0x01
	bne shancunmang
	bx lr
ting:
	ldr r0, = 0x40021018
	ldr r1, = 0x04
	str r1, [r0]

	ldr r0, = 0x40010800
	ldr r1, = 0x33333333
	str r1, [r0]
	ldr r1, = 0x33333333
	str r1, [r0, # 0x04]
xunhuan:
	ldr r2, = ledyanshi
	ldr r1, = 0xffff
	str r1, [r0, # 0x0c]
	
dd1:
	subs r2, # 1
	bne dd1
	mov r1, # 0
	str r1, [r0, # 0x0c]
	ldr r2, = ledyanshi
dd2:	
	subs r2, # 1
	bne dd2
	b xunhuan
	
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
