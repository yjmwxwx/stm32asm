	 .thumb
	.syntax unified
.section .data
	.section .text
_ting:
	ldr r0, = 0x20000000
	ldr r1, = 0x20000100
	bl _neicunqingling
	b _ting

_neicunqingling:
	b _neicun0
	pld byte1
	.word 0xffffffff
_neicun0:	
	movs r2, # 0
_qinglingxunhuan:
	str r2, [r0]
	adds r0, r0, # 4
	cmp r0, r1
	bne _qinglingxunhuan
	bx lr
	
	

	
