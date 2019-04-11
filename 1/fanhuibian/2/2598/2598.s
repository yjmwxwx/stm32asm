a1:	@@ 2598
	push {r7, lr}
	bl a2
	lsl r2, r0, # 0
	mov r3, # 0
	mvn r3, r3
	ldr r0, [r2]
	cmp r0, r3
	beq a3
	lsl r1, r0, # 0
	mov r0, # 2
	bkpt # 171
	mov r0, # 0
	str r0, [r2]
a3:  @@ 25b4
	ldr r0, [r2, # 0x04]
	cmp r0, r3
	beq a4
	add r1, r2, # 4
	mov r2, # 0
	bkpt # 171
	mov r0, # 0
	str r0, [r2, # 0x04]
	
a4: @@ 25c4
	pop {r0, pc}
a2:	@@ 277c
	ldr r0, = 0x20000b08
	bx lr
	
