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
	cpsid i
	sub sp, sp, # 0x5000
	ldr r0, = yjmwxwx
	str r0, [sp]
	add sp, sp, # 0x5000
	
	ldr r0, = 0xffffffff
	ldr r1, = 0x8009c00
	ldr r1, [r1]
	cmp r1, r0
	bne _crcjisuan
_daogujian:	
	ldr r0, = 0xe000ed08
	ldr r1, = 0x8004000
	str r1, [r0]
	add r1, r1, # 4
	ldr r1, [r1]
	cpsie i
	bx r1
_crcjisuan:
	ldr r0, = 0x8009c00
	ldr r1, = 0x5bfe
	mov r6, # 0
	movw r4, # 0x8408
	
_crcxunhuan:
	ldrb r5, [r0], # 1
	eor r6, r6, r5
	mov r2, # 8
_crcxunhuan1:
	mov r5, r6
	lsrs r6, r6, # 1
	tst r5, # 1
	it ne
	eorne r6, r6, r4
	
	subs r2, r2, # 1
	bne _crcxunhuan1
	
	subs r1, r1, # 1
	bne _crcxunhuan
	ldr r0, = 0x800f7fe
	ldr r1, [r0]
	cmp r6, r1
	bne _daogujian
					@ flsh解锁
	ldr r0, = 0x40022000
	ldr r1, = 0x45670123
	str r1, [r0, # 0x04]
	ldr r1, = 0xcdef89ab
	str r1, [r0, # 0x04]
					@擦除23页
	mov r5, # 23
	ldr r4, = 0x8004000
	movw r8, # 0x400
_flashmang:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang
	mov r1, # 2
	str r1, [r0, # 0x10]
	str r4, [r0, # 0x14]
	mov r1, # 0x42
	str r1, [r0, # 0x10]
	add r4, r4, r8
	subs r5, # 1
	bne _flashmang
						@写FLASH
	ldr r8, = 0x8004000
	ldr r4, = 0x8009c00
	mov r5, # 0
	movw r6, # 0x1700
_flashmang1:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang1
	mov r1, # 1
	str r1, [r0, # 0x10]
	ldrh r3, [r4, r5]
	strh r3, [r8, r5]
	add r5, r5, # 2
_flashmang2:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang2
	ldrh r3, [r4, r5]
	strh r3, [r8, r5]
	add r5, r5, # 2
	subs r6, r6, # 1
	bne _flashmang1
_flashmang3:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang3
	mov r1, # 2
	str r1, [r0, # 0x10]
	ldr r3, = 0x8009c00           @ 擦去更新的一页
	str r3, [r0, # 0x14]
	mov r1, # 0x42
	str r1, [r0, # 0x10]
_flashmang4:
	ldr r2, [r0, # 0x0c]
	lsls r2, r2, # 31
	bmi _flashmang4
	mov r1, # 0x80
	str r1, [r0]          		@flsh上锁
	ldr r0, = 0xe000ed0c
	ldr r1, = 0x05fa0004
	str r1, [r0]          		@复位
	
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
