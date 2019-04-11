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
	ldr r0, = 0x20000000
	ldr r1, = 0x20000100
	ldr r2, = 0x20000300
tingzhu:
	ldrb r0, [r1, r2]!
	b tingzhu
	
	
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
	ldr r0, = 0x8001000
	bl yecachu
	bl shancunmang
	ldr r0, = 0x40022010
	mov r1, # 0x01
	str r1, [r0]
	ldr r5, = 0x20000000
	ldr r2, = 0x8001000
	mov r6, # 200
xieflash:
	bl shancunmang
	ldrh r3, [r5], # 0x02
	bl shancunmang
	strh r3, [r2], # 0x02
	bl shancunmang
	subs r6, # 1
	bne xieflash
	ldr r0, = 0x40022010
	mov r1, # 0
	str r1, [r0]
	b ledled
cunchushuju:
yecachu:
	push {r0-r4,lr}
	mov r3, r0
	bl flashkey
	bl shancunmang
	ldr r2, = 0x40022000
	movs r0, # 2
	str r0, [r2, # 0x10]
	str r3, [r2, # 0x14]
	movs r0, # 0x42
	str r0, [r2, # 0x10]
	bl shancunmang
	movs r0, # 0
	str r0, [r2, # 0x10]
	pop {r0-r4,pc}
flashkey:
	push {r0-r1,lr}
	ldr r0, = 0x40022000
	ldr r1, = 0x45670123
	str r1, [r0, # 0x04]
	ldr r1, = 0xcdef89ab
	str r1, [r0, # 0x04]
	pop {r0-r1,pc}
shancunmang:
	push {r0-r1,lr}
	ldr r0, = 0x40022000
flashmang:
	ldr r1, [r0, # 0x0c]
	lsls r1, r1, # 0x1f
	bne flashmang
	pop {r0-r1,pc}
ledled:
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
