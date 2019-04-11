	 .thumb                 
         .syntax unified
.section .data
mingling:	.byte 0x02, 0x28, 0x0e, 0x06, 0x01
lcdshuju:	.ascii "4_LINE DRIVER"
	
        	.equ STACKINIT,          0x20005000
		.equ yanshius,           0x20000200
		.equ ledkongzhi,         0x20000204
		.equ lcdshu,		  0x20000208
	

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
	mov r10, # 0
	mov r11, # 0 
@@AFIO-MAPR 开SWD模式
	ldr r0, = 0x40010004
	ldr r1, = 0x02000000
	str r1, [r0]
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
        mov r1, # 0x3D
        str r1, [r0]
ioshezhi:
	ldr r0, = 0x40010804 @ gpioa
	ldr r1, = 0x34444444
	str r1, [r0]
        ldr r0, = 0x40010c00
        ldr r1, = 0x44443444
        str r1, [r0]
        ldr r0, = 0x40010c04
        ldr r1, = 0x33334444
        str r1, [r0]
zhuchengxu:
lcdchushihua:
	mov r3, # 0
	ldr r0, = 0x20000208
	ldr r1, = mingling
lcdchushihua1:
	add r3, # 1
	ldrb r2, [r1, r3]
	str r2, [r0]
	bl xielcd
	cmp r3, # 5
	bne lcdchushihua1
	mov r3, # 0
	b zhuchengxu


	
sysyanshi:
	push {r0-r5, lr}
	ldr r0, = 0xE000E010
	ldr r1, = yanshius
	ldr r1, [r1] 
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	ldr r4, = 0xFFFFF0
	cmp r1, r4
	bne kaidingshiqi
	mov r2, # 0x01
	str r2, [r0]
	pop {r0-r5, pc}
kaidingshiqi:
	mov r2, # 0x01
	str r2, [r0]
tingzaizhe:
	ldr r3, [r0, # 8]
	cmp r3, # 0 
	bne tingzaizhe
	pop {r0-r5, pc}
	

xielcd:
	push {r0-r9, lr}
	ldr r4, = 0x22004110
	ldmia r4!, {r0-r3}
	bl xielcd1
	ldr r4, = 0x22004100
	ldmia r4!, {r0-r3}
	bl xielcd1
	pop {r0-r9, pc}
	
xielcd1:
	ldr r10, = 0x40010c0c
	mov r9, # 0x00
	str r9, [r10]
	ldr r7, = 0x4001080c
	ldr r11, = 0x8000
	str r11, [r7]
	ldr r5, = 0x422181b0
	stmia r5!, {r0-r3}
	mov r8, r8
	mov r8, r8
	mov r8, r8
	mov r8, r8
	mov r8, r8
	mov r8, r8
	mov r8, r8
	mov r8, r8
	mov r11, # 0
	str r11, [r7]
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
_dingshiqi:
	bx lr
	
