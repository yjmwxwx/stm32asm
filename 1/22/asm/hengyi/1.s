	 .thumb                 
         .syntax unified
.section .data
lcdchushihuamabiao: .byte 0x00,0x00,0x01,0x00,0x03,0x00,0x0f,0x00,0x10,0x00,0x11,0x00,0x12,0x11,0x20,0x27,0x21,0x27,0x30,0xef,0x31,0xef,0x40,0x00,0x50,0x00,0x60,0x00,0x61,0x00,0x62,0x00,0x70,0x00,0x71,0x00,0x72,0x00,0x80,0x00,0x90,0x00,0xa0,0x00,0xa1,0x00,0xa2,0x00,0xa3,0x00,0xa3,0x00,0xb0,0x00,0xb1,0x00,0xc1,0x00,0xc2,0x00,0xc3,0x00,0xd0,0x00,0xd1,0x00,0xe0,0x00,0xf0,0x00,0xf1,0x00
	
	
	
         .equ STACKINIT, 0x20005000
	.equ lcdyanshi,    10000
	.equ lcdwr,      0x422201a8
	.equ lcdrd,      0x422201ac
	.equ lcdcs,      0x422201b0
	.equ lcda0,      0x4221818c
	.equ lcdrst,     0x42218190
	.equ fengmingqi, 0x422201a0
	.equ lcddx,      0x422181a0
	.equ lcdshuju,   0x22006000
.section .text
vectors:        
        .word STACKINIT         
        .word _start + 1        
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
        .word _memory_fault + 1 
        .word _bus_fault + 1    
        .word _usage_fault + 1 
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0 
	.word 0
	.word _dingshiqi + 1
_start:
	mov r0, # 0
	mov r1, # 0
	mov r2, # 0
	mov r3, # 0
	mov r4, # 0
	mov r5, # 0
	mov r6, # 0 
	mov r7, # 0
	mov r8, # 0
	mov r9, # 0
shizhong:
	ldr r0, = 0x40021000
	ldr r1, = 0x14D83
	str r1, [r0]
gsszbz: 
	ldr r2, [r0]
	ldr r1, = 0x20000
	tst r1, r2           @高速时钟标志位           
	bne rccchushihua
	b gsszbz
rccchushihua: 
	ldr r0, = 0x40022000
	mov r1, # 0x00000032
	str r1, [r0]           @FLASH缓冲 缓冲开启 
	ldr r0, = 0x40021004
	ldr r1, = 0x1D8400
	str r1, [r0]
	ldr r0, = 0x40021000
	ldr r1, = 0x1033D03
	str r1, [r0]
chaxun:
	ldr r2, [r0]
	ldr r1, = 0x2000000
	tst r1, r2
	bne rccgg
	b chaxun
rccgg:
	ldr r0, = 0x40021004
	ldr r1, = 0x1D8402
	str r1, [r0]
rccapb2enr:
	ldr r0, = 0x40021018
	mov r1, # 0x3d
	str r1, [r0]
	
        ldr r0, = 0x40010004 @ AFIO_MAPR
	ldr r1, = 0x02000000
	str r1, [r0]
ioshezhi:
	ldr r0, = 0x40010800
	ldr r1, = 0x24444444
	str r1, [r0, # 4]
	ldr r0, = 0x40010c00
	ldr r1, = 0x44455444
	str r1, [r0]
	ldr r1, = 0x55555555
	str r1, [r0, # 4]
	ldr r0, = 0x40011004
	ldr r1, = 0x44455555
	str r1, [r0]

lcdfuwei:
	ldr r5, = lcdyanshi
lcdfuwei1:
	subs r5, # 1
	bne lcdfuwei1
	ldr r0, = fengmingqi
	ldr r1, = lcdrst
	mov r3, # 0
	str r3, [r1]
	ldr r5, = lcdyanshi
lcdfuwei2:
	subs r5, # 1
	bne lcdfuwei2
	mov r2, # 1
	str r2, [r1]
	str r2, [r0]
lcdchushihua:
	ldr r2, = 0x20000300
	ldr r0, = lcdchushihuamabiao
lcdchushihua1:
	ldrb r1, [r0], # 1
	cmp r1, # 0xff
	beq tiaochulcdchushihua
	str r1, [r2]
	bl lcdxiemingling
	ldrb r1, [r0], # 1
	cmp r1, # 0xff
	beq tiaochulcdchushihua
	str r1, [r2]
	bl lcdxieshuju
	b lcdchushihua1
	
	
lcdxiemingling:
	push {r0-r9, lr}
	ldr r8, = lcdcs
	mov r9, # 0
	str r9, [r8]
	ldr r8, = lcda0
	mov r9, # 1
	str r9, [r8]
	ldr r8, = lcdwr
	mov r9, # 0
	str r9, [r8]
	ldr r8, = lcdrd
	mov r9, # 1
	str r9, [r8]
	ldr r8, = lcdshuju
	ldmia r8!, {r0-r7}
	ldr r8, = lcddx  @ gpioc_odr
	stmia r8!, {r0-r7}
	ldr r5, = lcdyanshi
dd1:
	subs r5, # 1
	bne dd1
	ldr r8, = lcdwr
	mov r9, # 1
	str r9, [r8]
	ldr r8, = lcdcs
	str r9, [r8]
	pop {r0-r9, pc}

lcdxieshuju:
	push {r0-r9, lr}
	ldr r8, = lcdcs
	mov r9, # 0
	str r9, [r8]
	ldr r8, = lcda0
	str r9, [r8]
	ldr r8, = lcdwr
	str r9, [r8]
	ldr r8, = lcdrd
	mov r9, # 1
	str r9, [r8]
	ldr r8, = lcdshuju
	ldmia r8!, {r0-r7}
	ldr r8, = lcddx
	stmia r8!, {r0-r7}
	ldr r5, = lcdyanshi
dd2:
	subs r5, # 1
	bne dd2
	ldr r8, = lcdwr
	mov r9, # 1
	str r9, [r8]
	ldr r8, = lcdcs
	str r9, [r8]
	pop {r0-r9, pc}
	
	
tiaochulcdchushihua:
	ldr r0, = 0x20000300
	mov r1, # 0
	str r1, [r0]
	bl lcdxiemingling
	mov r1, # 0x08
	str r1, [r0]
	bl lcdxieshuju
	mov r1, # 0xb0
	str r1, [r0]
	bl lcdxiemingling
	mov r1, # 0x41
	str r1, [r0]
	bl lcdxiemingling
	
	b tiaochulcdchushihua
	
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
_dingshiqi:
	bx lr

	
	
	
