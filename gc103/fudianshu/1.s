	 .thumb                 
         .syntax unified
.section .data
xiaoshu:	.float 3.1415927
xiaoshu1:	.float 2.55
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
	ldr r0, = xiaoshu
	bl _fudianzhuandingdian
	mov r8, r0
	ldr r0, = xiaoshu1
	bl _fudianzhuandingdian
	mov r9, r0
	mov r0, r8
	mov r1, r9
	adds r0, r0, r1
	mov r10, r0
	bl _dingdianzhuanfudian
	mov r11, r0
tingting:
	b tingting
	
_fudianzhuandingdian:
	ldr r1, [r0]
	lsrs r2, r1, # 23
	lsls r3, r1, # 9
	lsrs r3, r3, # 9
	
	subs r2, r2, # 127
	movs r1, # 1
	lsls r2, r1, r2
_weishu:
	ldr r7, = 10000000
	movs r5, # 24
	movs r0, # 0
_weishuxunhuan:
	subs r5, r5, # 1
	bmi _tiaochuweishu
	lsls r6, r3, # 8
	lsls r6, r6, r5
	bpl _weishuxunhuan
	lsrs r4, r7, r5
	adds r0, r0, r4
	b _weishuxunhuan
_tiaochuweishu:
	adds r0, r0, r7
	muls r0, r0, r2
	bx lr
	
	
_dingdianzhuanfudian:
	movs r7, # 0
_panduanweishu:
	adds r7, r7, # 1
	lsls r6, r0, r7
	bpl _panduanweishu
	lsls r6, r6, # 1
	lsrs r6, r6, # 8

	movs r5, # 31
	subs r7, r5, r7
	adds r7, r7, # 127
	lsls r7, r7, # 23
	orrs r6, r7
	movs r0, r6
	bx lr
	
	
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
