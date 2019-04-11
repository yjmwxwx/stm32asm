	mov r8, r8
	mov r8, r8
	mov r8, r8
	mov r8, r8
	bl dd1 @@2704
dd1:
	bl dd2  @@ 2798
	cmp r0, # 0
	beq dd3
dd3:
	bl dd5 @@2624
dd2:
	mov r0, # 1
	bx lr
dd5:
	push {r4, lr}
	ldr r1, = 0x7c
	add r1, pc
	add r1, # 28
	ldr r1, = 0x9c
	add r4, pc
	add r4, # 26
	cmp r1, r4
	beq dd6 @@2644
da1:	
	add r0, r1, # 4
	ldr r2, [r1]
	add r1, r2, r1
	blx r1 @@ 26b2 @@ cc1 @ 25c8
	@@ 263e
	mov r1, r4
	bne da1 @@ 2636
dd6:
	pop {r4, pc}
dd9:
	ldr r1, [r0, # 0x04]
	lsl r3, r1, # 31
	.word 0xbf44
	.word 0xf1a9
	.word 0x0301
	.word 0x1859
	
dd8:
	mov r3, # 0
	
dd7:
	str r3, [r1, # 0x04]
	sub r2, r2, # 4
	bne dd8@@ 26b0
	ldr r2, [r0, # 0x04]
	cmp r2, # 0
	bne dd9 @@26a2
	bx lr
	
cc1:
	push {r4}
	b cc2 @ 25ec
cc2:
	ldr r3, [r0, # 0x04]
	cmp r3, # 0
	bne cc3 @ 25cc
cc3:
	ldr r1, [r0]
	add r1, r1, r0
	add r0, r0, # 4
	ldr r2, [r0, # 0x04]
	lsl r4, r2, # 31
	.word 0xbf44
	.word 0xf1a9
	.word 0x0401
	.word 0x18a2
cc5:
	ldr r4, [r1, # 0x04]
	str r4, [r2, # 0x04]
	sub r3, r3, #4
	bne cc5
	pop {r4}
	bx lr @ 263e
	