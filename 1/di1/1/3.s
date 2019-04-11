
docbuu:
	ldr r1, = 0x40000100
	mov r0, # 0x22
	str r0, [r1]

	ldr r1, = 0x40000110
	mov r0, # 0x33
	str r0, [r1]