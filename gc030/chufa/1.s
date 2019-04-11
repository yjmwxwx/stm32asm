@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data
	.equ duizhanding,       0x20001000 @ 堆栈顶	
.section .text
vectors:          @向量表
        .word duizhanding                     
        .word _start + 1             @复位向量
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
_start:
	ldr r0, = 0xfedcba98
	ldr r1, = 0x123
	bl _chufa
	push {r0-r1}

	ldr r0, = 0xfedcba98
	ldr r1, = 0x76543210
	ldr r2, = 0x32104567
	bl _chufa64
	push {r0-r2}
	
_tingxia:
	movs r1, r1
	b _tingxia
	
_chufa64:		@64位除以32位软件除法
	@ r0-r1除以r2等于R0-R1余数R2
	push {r4-r7}
	mov r3, r0
	mov r6, r1
	movs r4, # 1
	mov r7, r4
	lsls r4, r4, # 31
	movs r0, # 0
	mov r5, r0
_chufaxunhuan64:
	lsls r3, r3, # 1
	adcs r5, r5, r5
	cmp r5, r2
	bcc _chufaweishubudao64
	adds r0, r0, r4
	subs r5, r5, r2
_chufaweishubudao64:
	lsrs r4, r4, # 1
	bne _chufaxunhuan64
	push {r0}
	lsls r7, r7, # 31
	bpl _chufafanhui64
	mov r4, r7
	mov r3, r6
	movs r0, # 0
	b _chufaxunhuan64
_chufafanhui64:
	mov r1, r0
	mov r2, r5
	pop {r0}
	pop {r0}
	pop {r4-r7}
	bx lr

_chufa:		@软件除法
	@ r0 除以 r1 等于 商(r0)余数(r1)
	push {r4}
	mov r2, r0
	movs r3, # 1
	lsls r3, r3, # 31
	movs r0, # 0
	mov r4, r0
_chufaxunhuan:
	lsls r2, r2, # 1
	adcs r4, r4, r4
	cmp r4, r1
	bcc _chufaweishubudao0
	adds r0, r0, r3
	subs r4, r4, r1
_chufaweishubudao0:
	lsrs r3, r3, # 1
	bne _chufaxunhuan
	mov r1, r4
	pop {r4}
	bx lr

_nmi_handler:	
	bx lr
_hard_fault:
	bx lr 
