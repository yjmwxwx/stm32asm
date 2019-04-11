kb-10:	@ 0xeac
	push {r7, lr}
	bl kb-11 @ 181c

kb-22:	@ 0xeb2
	ldr r1, = 0x20001ca6
	strb r0, [r1]
	pop {r0, pc}
	b ls-13 @ 2210

kb-22:	@ 0xf2e
	push {r4, lr}
	ldr r0, = 0x08004000
	ldr r1, = 0x20001ca6
	ldr r4, = 0x20001c88
	str r1, [r4]
	str r1, [r4, # 0x04]
	ldr r0, [r0]
	sub r0, # 8
	bl kv-23 @ 23c4
	
	
	




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
kb-11:	@ 181c
	push {r4, r5, r6, lr}
	mov r5, r0
	movw r6, # 0xfff
	mov r0, r6
	bl kv-1934 @ 1960

kb-13:	@ 182a
	cmp r0, # 4
	bne kb-14 @ 1852
	ldr r4, = 0x40022010
	ldr r0, [r4]
	orr r0, r0, # 0x02
	str r0, [r4]
	str r5, [r4, 0x04]
	ldr r0, [r4]
	orr r0, r0, # 0x40
	str r0, [r4]
	mov r0, r6
	bl kv-1935 @ 0x1960

kb-20:	@ 1848
	cmp r0, # 1
	beq kb-21 @ 1856
	ldr r1, [r4]
	movw r2, # 0x1ffd
	and r1, r2
	str r1, [r4]
	pop {r4, r5, r6, pc}
	
	
	

	
kv-1955:	@ 0x18fc
	cmp r0, # 1
	beq kv-1956 @ 0x1900
kv-1956:	@ 0x1900
	ldr r1, [r6, # 0x08]
	movw r2, # 0x1fef
	b kv-1957 @ 0x1912
kv-1957:	@ 0x1912
	and r1, r2
	str r1, [r6, # 0x08]
	pop {r4, r5, r6, pc}
	



	





	

kv-1926:	@ 18a4
	push {r4, r5, r6, lr}
	mov r4, r0
	movw r5, # 0xfff
	mov r0, r5
	bl kv-1927 @@@  0x1918

kv-1934:	@ 18b0
	cmp r0, # 4
	bne kv-1935 @0x1c16
	ldr r6, = 0x40022008
	str r0, [r6]
	ldr r0, = 0xcdef89ab
	str r0, [r6]
	ldr r0, [r6, # 0x08]
	orr r0, r0, # 0x20
	str r0, [r6, # 0x08]
	ldr r0, [r6, # 0x08]
	orr r0, r0, # 0x40
	str r0, [r6, # 0x08]
	mov r0, r5
	bl kv-1935 @ 1969

kv-1950: @ 18d4
	cmp r0, # 4
	bne kv-1951 @ 1908
	ldr r0, [r6, # 0x08]
	movw r1, 0x1fdf
	and r0, r1
	str r0, [r6, # 0x08]
	ldr r0, [r6, # 0x08]
	orr r0, r0, # 0x10
	str r0, [r6, # 0x08]
	ldr r0, = 0x1ffff800
	cmp r4, # 0
	.word 0xbf14
	mov r1, # 0
	mov r1, # 165
	strh r1, [r0]
	mov r0, r5
	bl kv-1952 @ 1960
	

	
	

	








	

kv-1927:	@ 0x1918
	ldr r0, = 0x4002200c
	ldr r1, [r0]
	lsl r1, r1, # 31
	bpl kv-1928 @ 0x1924
kv-1928:
	ldr r1, [r0]
	lsl r1, r1, # 29
	bpl kv-1929 @ 0x192e
	ldr r0, [r0]
	lsl r0, r0, # 27
	bpl kv-1930 @ 1938
	mov r0, # 4
	bx lr

	

kv-1931:	@ 1968
	mov r4, # 255
	b kv-1932@ 197e
kv-1933:	@ 197e
	cmp r0, # 1
	cbnz r5, # 0x00
	pop {r1, r4, r5, pc}


kv-1936:	@ 1968
	mov r4, # 255
	b kv-1937 @ 197e
kv-1937:	@ 197e
	cmp r0, # 1
	bne kv-1938 @ 198c
kv-1939:	@ 0x198c
	cbnz r5, # 0x00
	pop {r1, r4, r5, pc}

kv-1952:	@ 0x1960
	push {r3, r4, r5, lr}
	mov r5, r0
	bl kv-1927
kv-1953:	@ 1968
	mov r4, @ 255
	b kv-1954 @ 0x197e
kv-1954:	@ 0x197e
	cmp r0, # 1
	bne kv-1955 @ 198c
	cbnz r5, # 0x00
	pop {r1, r4, r5, pc}

kb-14:	@ 0x1968
	mov r4, # 255
	b kb-15 @ 0x197e
kb-15:	@ 0x197e
	cmp r0, # 1
	bne kb-16 @ 198c

kb-16:	@ 198c
	cbnz r5, # 0x00
	pop {r1, r4, r5, pc}
	
	
	
	

	

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

kv-58:	@ 1ab2
	ldr r2, = 0x4002100c
	cmp r1, # 0
	ldr r1, [r2]
	.word 0xbf14
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

kv-50: @@ 1bde
	b kv-51 @@ 1e14

kv-85:	@ 1bfc
	mov r0, # 20
	strb r0, [sp, # 0x00]
	mov r0, # 1
	strb r0, [sp, # 0x01]
	mov r0, # 0
	strb r0, [sp, # 0x02]
	mov r0, # 1
	strb r0, [sp, # 0x03]
	add r0, sp, # 0
	bl kv-86 @ 20f6


kv-87:	@ 1c1a
	mov r0, # 19
	strb r0, [sp, # 0x00]
	mov r0, # 0
	strb r0, [sp, # 0x01]
	mov r0, # 1
	strb r0, [sp, # 0x03]
	add r0, sp, # 0
	bl kv-86 @ 20f6

kv-89:	@ 1c36
	mov r0, # 27
	strb r0, [sp, # 0x00]
	mov r0, # 0
	strb r0, [sp, # 0x01]
	strb r0, [sp, # 0x02]
	mov r0, # 1
	strb r0, [sp, # 0x03]
	add r0, sp, # 0
	bl kv-86 @ 20f6

kv90:	@ 0x1c52
	pop {r0, pc}
	
	
	
	


	
	
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
kv-51:	@ 1e14
	push {lr}
	mov r1, #1
	mov r0, # 0x800
	bl kv-25 @ 1a8e
kv-81:	@1be2
	push {r7, lr}
	mov r1, # 0
	mov r0, # 0x8000000
	bl kv-82 @ 2170

kv-83:	@ 1bee
	ldr r0, = 0x40005c44
	mov r1, # 0
	str r1, [r0]
	mov r0, # 0x500
	bl kv-84 @ 0x20e8
	
	

	



	

kv-55: @ 1e22
	mov r1, # 1
	mov r0, # 4
	bl kv-25 @ 1a8e



	
kv-56: @ 1e2a
	bl kv-57 @ 2024

kv-60:	@ 1e2e
	ldr r0, = 0x40012c00
	mov r1, # 2
	strh r1, [r0, # 0x30]
	ldrh r1, [r0]
	and r1, r1, # 0x9f
	strh r1, [r0]
	ldrh r1, [r0]
	mov r0, # 96
	strh r0, [sp, # 0x00]
	mov r0, # 2
	strh r0, [sp, # 0x08]
	mov r0, # 1
	strh r0, [sp, # 0x02]
	add r0, sp, # 0
	bl kv-61 @ 203e


kv-72:	@ 1e58
	mov r0, # 1
	bl kv-73 @ 20b2

kv-75:	@ 1e5e
	bl kv-76 @ 20ac

kv-77:	@ 1e64
	mov r0, # 1
	bl kv-78 @ 2086

kv-79:	@ 1e6a
	add sp, sp, # 5
	pop {pc}


kv-92:	@ 1e70
	push {r4, r5, r6, lr}
	mov r4, r0
	mov r5, r1
	ldr r6, = 0x20001c78
	ldrb r0, [r6]
	cmp r4, r0
	beq kv-93 @ 1e90
	mov r1, # 0
	mov r0, # 4
	bl kv-94 @ @ 208e

kv-95:	@@ 1e88
	mov r0, # 0
	bl kv-96 @ 207e

kv-97:	@ 1e8e
	b kv-98 @ 1e96
kv-98:	@ 1e96
	cmp r4, # 6
	bhi kv-99 @ 1ec6

ls-2:	@ 1eba
	mov r0, # 80
	bl kv-100 @@ 20a2
ls-3:	@ 1ec0
	b kv-1920 @ 1f16
	
	

kv-99:	@ 1ec6
	mov r0, # 80
	bl kv-100 @ 20a2

kv-1918:	@ 1ecc
	ldr r0, = 0x40012c18
	strh r5, [r0, # 0x14]
	movw r1, # 0x8ca0
	strh r1, [r0, # 0x10]
	mov r1, # 1
	mov r0, # 4
	bl kv-94 @ 208e

kv-1919:	@ 1ede
	b  kv-1920 @1f16
kv-1920:	@ 1f16
	ldr r0, = 0x42258280
	mov r1, # 1
	str r1, [r0]
	ldrb r0, [r6]
	cbz r0, # 0x06
	cmp r0, # 4
	beq kv-1921 @ 1f3c
kv-1921:	@ 1f24
	cmp r0, # 5
	bne kv-1922 @ 1f3c
kv-1922:	@ 1f3c
	strb r4, [r6]
	str r5, [r6, # 0x04]
	mov r0, # 1
	bl kv-1923 @ 207e

kv-1924:	@ 1f46
	pop {r0, r1, r4, r5, r6, pc}

ls-4:	 @ 1f40
	mov r0, # 1
	bl kv-1932 @ 207e

ls-5:	@ 1f46
	pop {r0, r1, r4, r5, r6, pc}
	
	
	
	
	

	

	
	
	

	
	
	
	

		
	
	

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


kv-57:	@ 2024
	push {r7, lr}
	mov r1, # 1
	mov r0, #0x800
	bl kv-58 @ 1ab2

kv-59:	 @@ 2030
	mov r1, # 0
	mov r0, # 0x800
	b kv-58  @@1ab2

kv-61: @ 203e
	push {r4}
	ldr r1, = 0x40012c18
	ldrh r2, [r1]
	ldr r3, = 0x4225841
	mov r4 # 0
	str r4, [r3]
	uxtb r2, r2
	ldrh r4, [r0]
	strh r2, [r1]
	ldrh r2, [r0, # 0x02]
	str r2, [r3]
	ldrh r2, [r0, # 0x04]
	str r2, [r3, # 0x08]
	ldrh r2, [r0, # 0x08]
	str r2, [r3, # 0x04]
	ldrh r2, [r0, # 0x0a]
	str r2, [r3, # 0x0c]
	ldr r2, = 0x422580a8
	b kv-70 @ 206e

kv-70:	 @ 206e
	ldrh r3, [r0, # 0x0c]
	str r3, [r2]
	ldrh r3, [r0, # 0x0e]
	str r3, [r2, # 0x04]
	ldrh r0, [r0, # 0x06]
	strh r0, [r1, # 0x20]
	pop {r4}

kv-96:	@ 207e
	ldr r1, = 0x42258000
	str r0, [r1]
	bx lr
	


	

kv-71:	@@ 207c
	bx lr

ls-1:	@207e
	ldr r1, = 0x42258000
	str r0, [r1]
	bx lr


	

kv-78:
	ldr r1, = 0x422580a8
	str r0, [r1]
	bx lr

kv-1923:	@ 207e
	ldr r1, = 0x42258000
	str r0, [r1]
	bx lr
	

kv94:	@ 208e
	ldr r2, = 0x40012c0c
	cmp r1, # 1
	ldrh r1, [r2]
	.word 0xbf0c
	orr r0, r1
	strh r0, [r2]
	bx lr
	
	
kv-100 @ 20a2
	ldr r1, = 0x40012c18
	ldrh r2, [r1]
	movw r3, # 0xf7f
	b kv-1918  @ 20be
	

	
	
	
kv-76: @20ac
	ldr r1, = 0x4225801c
	str r0, [r1]
	bx lr
	
	

kv-73:	 @20b2
	ldr r1, = 0x4225832c
	str r0, [r1]
	bx lr

kv-1918:	@ 20be
	and r2, r3
	strh r0, [r1]
	bx lr
	

kv-84:	@ 20e8
	ldr r1, = 05fa0000
	orr r0, r1
	ldr r1, = 0xe000ed0c
	str r0, [r1]
	bx lr

kv-86:	@ 20f6
	ldrb r5, [r0]
	mov r1, # 1
	ldrb r2, [r0, # 0x03]
	cbz r2, # 0x5e
	ldr r2, = 0xe000ed0c
	ldr r2, [r2]
	and r2, r2, # 0x700
	rsb r2, r2, # 0x700
	asr r3, r5, # 2
	ldr r8, = 0xe000e400
	ldr r7, [r8, r3, lsl # 2]
	and r5, r5, # 0x03
	lsl r5, r5, # 3
	mov r6, # 255
	lsl r6, r5
	bic r7, r6
	ldrb r4, [r0, # 0x01]
	rsb lr, r2, # 0x04
	ldrb lr, [r0, # 0x02]
	mov r4, # 15
	lsl r2, r2, # 4
	lsl r2, r5
	and r2, r6
	orr r2, r7
	str r2, [r8, r3, lsl #2]
	ldrb r0, [r0]
	asr r2, r0, # 5
	ldr r3, = 0xe000e100
	and r0, r0, # 0x1f
	str r0, [r3, r2, lsl # 2]
	b kv-87 @ 1c1a



	
	
	


	
kv-82:	@ 2170 @  xiangliangbiao 1fffff80
	ldr r2, = 0x1fffff80
	and r1, r2
	orr r0, r1
	ldr r1, = 0xe000ed08
	str r0, [r1]
	bx lr


	
	
bt-2:	@@2198
	push {r4, r5, r6, lr}
	bl t-26 @@ 219a>1b46

kv-41: @ 219e
	bl kv-42 @ 1bd4


	

kv-80:	 @ 21a2
	bl kv-81 @ 1be2

kv-91:	@ 21a6
	mov r1, @ 0x7d0
	mov r0, # 4
	bl kv-92 @ 1e70

kv-1925:	@ 21b0
	mov r0, # 1
	bl kv-1926 @ 18a2

kv-1960:	@ 0x21b6
	bl kv-1961 @ 2560
	
	mov r1, # 0
	mov r0, # 1
	bl kv-92 @ 1e70

ls-6:	@ 0x21c2
	ldr r0, = 0x40000001
	mov r1, # 2
	strb r1, [r0, # 0x0a]
	mov r1, # 0
	strb r1, [r0, # 0x0b]
	ldr r0, = 20001c65
	strb r1, [r0]
	bx lr

ls-7:	@ 0x21c6
	ldr r0, = 0x20001ca8
	ldr r4, = 0x20000b20
	ldr r5, = 0x20000b21
	ldr r6, = 0x20000b30
ls-8:	@ 21ce
	ldrb r1, [r0]
	cmp r1, # 5
	bne ls-8 @ 21ce
kb:	@ 21d4
	ldrb r0, [r5]
	lsl r0, r0, # 30
	bpl ls-9 @ 221c
	ldrb r0, [r4]
	cmp r0, #33
	beq ls-10 @ 21f4
	cmp r0, # 65
	beq ls-11 @ 21ea
	cmp r0, # 81
	beq ls-12 @ 21fa
	b ls-13 @ 2210

ls-11:	@ 21ea
	ldr r0, = 0xea870707
	ldr r0, [r0]
	bl kb-10 @ 0xeac
	

kb-3:	@ 21f4
	mov r0, # 81
	strb r0, [r4]
	b ls-13 @ 2210


ls-13:	@ 2210
	ldrb r0, [r5]
	and r0, r0, # 0xfd
	orr r0, r0, # 0x01
	strb r0, [r5]
ls-9:	@ 221c
	ldrb r0, [r4]
	cmp r0, # 7
	bne kb @ 21d4
	bl kb-22 @ 0xf2e

kb-25:	@ 2226
	b kb @ 21d4


kb-23:	@ 23c4
	bx lr
	
	
	
	
	




	

	

kv-1961:	@ 0x2560
	push {r4, lr}
	ldr r4, = 0x20001c30
	str r4, [r4, 0x1c]
	mov r0, # 2
	strb r0, [r4, # 0x08]
	ldr r0, = 0x20000a00
	str r0, [r4, # 0x20]
	ldr r1, [pc, # 0x24]
	str r1, [r4, # 0x24]
	ldr r0, [r0]
	blx r0  @@ r0 = 0xf81c6c1c
	mov r0, # 0x200
	str r0, [r4, # 0x2c]
	mov r0, # 0x100000
	str r0, [r4, # 0x28]
	mov r0, # 0x800
	str r0, [r4, # 0x30]
	pop {r4, pc}
	
	
	
	
	


	
	


		
ms-1:	@@2710
	mov r0, # 0
	bl bt-2 @@ 2712>2198
	

	

	
	
	
	
	
	

	
	
	
	
	
	
	
	

	