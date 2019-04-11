	.thumb
         .syntax unified
.section .data
	.equ STACKINIT,        	  0x20001000
	.section .text
vectors:
	.word STACKINIT
	.word _start + 1
_start:
	movs r0, # 2
	movs r1, # 2
	movs r2, # 2
	movs r3, # 2
	bl __shiyan
	movs r5, # 1
	movs r5, # 1
ting:
	b ting
__shiyan:
	push {r4-r5}
	mov r4, lr
	subs r4, r4, # 1
	ldrb r5, [r4]
	adds r4, r4, # 1
	cmp r3, r5
	bcs __fanhui
	mov r5, r3
__fanhui:
	ldrb r3, [r4, r5]
	lsls r3, r3, # 1
	adds r3, r4, r3
	pop {r4,r5}
	bx r3
