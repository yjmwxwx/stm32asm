ms-1:	@@2710
	mov r0, # 0
	bl bt-2 @@ 2712>2198
bt-2:	@@2198
	push {r4, r5, r6, lr}
	bl t-26 @@ 219a>1b46
416gongcheng: @ 17e8
	ldr r1, = 40022000
	ldr r2, [r1]
	and r2, r2, # 0x38
	b t-44 @@17f4
t-44: @ 17f4
	str r2, [r1]
	ldr r2, [r1]
	orr r0, r2
	str r0, [r1]
	bx lr
	

	
kv-13: @17f4
	str r2, [r1]
	ldr r2, [r1]
	orr r0, r2
	str r0, [r1]
	bx lr
	
	
a-44:	@ 17fe
	ldr r1, [pc, # 0x140]
	ldr r2, [r1]
	bic r2, r2, # 0x10
	b kv-13 @ 17f4

kv-23:	@ 180a
	ldr r0, = 0x40022004
	ldr r1, 0x45670123
	str r1, [r0]
	ldr r1, 0xcdef89ab
	str r1, [r0]
	bx lr
	

	

mkvii:	@@1994
	ldr r0, = 0x20000824
	mov r1, # 0
	str r1, [r0, # 0x0c]
	str r1, [r0, # 0x10]
	mov r1, # 20
	str r1, [r0, # 0x14]
	mov r1, # 0
	str r1, [r0, # 0x18]
	str r1, [r0, # 0x1c]
	ldr r1, [r0]
	orr r1, r1, # 0x01
	str r1, [r0]
	ldr r1, [r0, # 0x04]
	ldr r2, [pc, # 0x148] @@ 19b2 + 0x148
	and r1, r2
	str r1, [r0, # 0x04]
	ldr r1, [r0]
	ldr r2, = 0xfef6ffff
	and r1, r2
	str r1, [r0]
	ldr r1, [r0]
	bic r1, r1, # 0x40000
	str r1, [r0]
	ldr r1, [r0, # 0x04]
	bic r1, r1, # 0x7f0000
	str r1, [r0, # 0x04]
	mov r1, # 0
	str r1, [r0, # 0x08]
	bx lr

m3-situyate-l: @@ 19d4
	ldr r1, = 0x40021000
	ldr r2, [r1]
	bic r2, r2, # 0x10000
	str r2, [r1]
	ldr r2, [r1]
	bic r2, r2, # 0x40000
	str r2, [r1]
	cmp r0, # 0x10000
	beq walunding-l @@19f4
walunding-l:	@@ 19f4
	ldr r0, [r1]
	orr r0, r0, # 0x10000
	b t46 @@ 1a02




t46:	@@ 1a02
	str r0, [r1]
	bx lr
bt-sv: @@ 1a06
	push {r4, lr}
	ldr r4, = 0x2001c80
	mov r0, # 49
	bl bt-7 @ 1a0c

t-50: @@ 1a10
	strb r0, [r4]
	ldr r0, [r4, # 0x04]
	add r0, r0, # 1
	str r0, [r4, # 0x04]
	ldrb r0, [r4]
	cbnz r0, # 0x04
	mov r0, # 49
	bl mt-25 @ 1aca

t-28:@@ 1a28
	sbc r0, r0
	mvn r0, r0
	lsr r0, r0, # 31
	pop {r4, pc}

kv-5:	 @ 1a32
	ldr r2, = 0x40021004
	ldr r3, [r2]
	bic r3, r3, # 0x3f0000
	orr r0, r3
	orr r0, r1
	str r0, [r2]
	bx lr

kv-7: @@ 1a42
	ldr r1, = 0x42420060
	str r0, [r1]
	bx lr

kv-10: @ 1a48
	ldr r1, = 0x40021004
	ldr r2, [r1]
	lsr r2, r2, # 2
	str r0, [r1]
	bx lr

kv-11:	@ 1a56
	ldr r0, = 0x40021004
	ldr r0, [r0]
	and r0, r0, # 0x0c
	bx lr
	
	
	
	
	

140gongcheng:	@@ 1a60
	ldr r1, = 0x40021004
	ldr r2, [r1]
	bic r2, r2, # 0xf0
	b t-62a @ 1a72

kv-1s:	 @@ 1a6a
	ldr r1, = 0x40021004
	ldr r2, [r1]
	bic r2, r2, # 0x700
	orr r0, r2
	str r0, [r1]
	bx lr
	


	
t-62a: @ 1a72
	orr r0, r2
	str r0, [r1]
	bx lr
kv-1:	 @@ 1a78
	ldr r1, = 40021004
	bic r2, r2, # 0x3800
	str r0, [r1]
	bx lr

kv-3: @ 1a88
	ldr r1, = 0x424200d8
	str r0, [r1]
	bx lr

kv-25:	@@ 1a8e
	ldr r2, = 0x40021018
	cmp r1, # 0
	ldr r1, [r2]
	.word 0xbf14
	orr r0, r1
	str r0, [r2]
	bx lr

kv-27:	@ 1aa0
	ldr r2, = 0x4002101c
	cmp r1, # 0
	ldr r1, [r2]
	.word 0xbf14
	orr r0, r1
	str r0, [r2]
	bx lr
	
	
	

kv-32:	@ 1ac4
	ldr r1, = 0x40021007
	strb r0, [r1]
	bx lr
	
	
	
	
	
	
mt-25:	@@ 1aca
	lsr r1, r0, #5
	ldr r2, = 40021000
	cmp r1, # 1
	.word 0xbf08
	ldr r1, [r2]
	beq t-50-2 @@ 1ade

	
t-50-2: @ 1ade
	mov r2, # 1
	and r0, r0, # 0x1f
	and r0, r1
	sub r0, r0, #1
	b a-32 @ 1aee
a-32: @@ 1aee
	sbc r0, r0
	mvn r0, r0
	ldr r0, r0, # 31
	bx lr



	
bt-7: @@ 1aca
	lsr r1, r0, # 5
	ldr r2, = 40021000
	cmp r1, # 1
	.word 0xbf08
	ldr r1, [r2]
	beq t-70 @@ 1ade

t-70: @@ 1ade
	mov r2, # 1
	and r0, r0, # 0x1f
	and r0, r1
	sub r0, r0, # 1
	b t-80 @ 1aee
t-80:
	sbc r0, r0
	mvn r0, r0
	lsr r0, r0, # 31
	bx lr 
	
	
	


t31:	@ 1b24
	push {r7, lr}
	mov r0, # 6
	bl kv-32 @ 1ac4

kv-33:	@ 1b2c
	mov r0, # 0x100
	strh r0, [sp, # 0x00]
	mov r0, # 24
	strb r0, [sp, # 0x03]
	mov r0, # 3
	strb r0, [sp, # 0x02]
	add r1, sp, # 0
	ldr r0, = 0x40010800
	b kv-34 @ 1c94
	
	



t-26:	@@ 1b46
	push {r7, lr}
	bl mkvii @@ 1b48>1994

t-60: @@ 1b4c
	mov r0, # 0x10000
	bl m3-situyate-l @@ 1b50>19d4

t-127:	@ 1b54
	bl bt-sv @ 1a06

t-34: @@ 1b58
	cmp r0, # 1
	bne t34-85 @@ 1bac
	mov r0, # 16
	bl a-43 @ 17fe

t-43:	@@ 1b62
	mov r0, # 2
	bl 416gongcheng @@ 17e8

t-54:	@ 1b68
	mov r0, # 0
	bl 140gongcheng @ 1a60

kv-220: @@ 1b76
	mov r0, # 0x400
	bl kv-1s @1a6a
	

kv:	@@ 1b6e
	mov r0, # 0x400
	bl kv-1 @@ 1a78

kv-2:	@ 1b7e
	mov r0, # 0
	bl kv-3 @ 1a88

kv-4:	@1b84
	mov r1, # 0x1c0000
	mov r0, # 0x10000
	bl kv-5 @ 1a32

kv-6: @@ 1b90
	mov r0, # 1
	bl kv-7 @ 1a42

kv-8:	@ 1b96
	mov r0, # 57
	bl mt-25 @ 1aca

kv-9:	@1b9c
	cmp r0, r0
	beq kv-10 @ 1ba0

kv-10:	@ 1ba0
	mov r0, # 2
	bl kv-11 @ 1a48
kv-20: @ 1ba6
	bl kv-21 @ 1a56
kv-22: @ 1baa
	cmp r0, # 8
	bne kv-23 @  @@ 1bac -0x0a  ?? tiao dao 1ba6 kv-20
	bl kv-23 @ 180a

kv-24:	@ 1bb2
	mov r1, # 1
	mov r0, # 32
	bl kv-25 @ 1a8e

kv-26: @ 1bba
	mov r1, # 1
	mov r0, # 0x800000
	bl kv-27 @ 1aa0

kv-28:	 @ 1bc4
	mov r1, # 1
	mov r0, # 0x204
	bl kv-25 @ 1a8e

kv-30:	@ 1bd2
	b kv-31 @ 1b24

kv-42:	@1bd4
	push {r7, lr}
	bl kv-43 @ 1c74
kv-43:	@ 1c74
	push {r7, lr}
	mov r0, # 0x100
	strh r0, [sp, 0x00]
	mov r0, # 20
	strb r0, [r1, r3]
	

kv-34:	@ 1c94
	bl kv-35 @ 1f60

kv-40:	@ 1c98
	pop {r0, pc}
	

kv-35:	@ 1f60
	ldrb r3, [r1, # 0x03]
	orr r2, r3
	ldrh r3, [r1]
	uxtb r4, r3
	cbz r4, #0x4a
	mov r4, # 0x100
	cmp r3, r4
	bcc # 0x4e
	ldr r12, [r0, # 0x04]
	mov r4, # 0
	mov r5, # 1
	mov r6, # 15
	add r7, r4, # 0x08
	cmp r8, r7
	bne kv-36 @ 1ff6
kv-37:	@ 1fd2
	add r7, r4, # 0x08
	cmp r8, r7
	bne kv-38 @ 200e
	
	
	
	

kv-36:	@ 1ff6
	ldrb lr [r1, # 0x03]
	cmp lr # 0x28
	.word 0xbf08
	str r7, [r0, # 0x14]
	ldrb lr [r1, # 0x03]
	cmp lr # 0x048
	.word 0xbf08
	str r7, [r0, # 10]
	add r4, r4, # 1
	cmp r4, # 8
	bcc kv-37 @ 1fd2

kv-39:	@ 200e
	add r4, r4, # 1
	cmp r4, # 8
	bcc kv-37 @ 1fd2
	str r12, [r0, # 0x04] @@ 1c98 

kv-41: @ 219e
	bl kv-42 @ 1bd4
	
	
	

	
	
	
	
	
	
	
	

	