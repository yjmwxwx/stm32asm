	 .thumb                 
         .syntax unified
.section .data
        	.equ STACKINIT,          0x20005000
		.equ yanshius,           0x20000200
		.equ ledkongzhi,         0x20000204
		.equ lcdshu,		  0x20000208
		.equ lcdyanshi,		800000
		.equ lcdyanshi1, 	2000
		.equ lcdyanshi3, 	8000000
.section .text
vectors:        
        .word STACKINIT         
        .word _start + 1        
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
        .word _memory_fault + 1 
        .word _bus_fault + 1    
        .word _usage_fault + 1 

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
	str r1, [r0] @@ 

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
lcdchushihua:
	ldr r0, = 0x20000208
	ldr r10, = 0x4221818c
	mov r9,  # 0
	str r9, [r10]
	MOV R1, # 0x33
	str r1, [r0]
	bl xielcd
	ldr r6, = lcdyanshi
yanshila3:
	subs r6, # 1
	bne yanshila3

	MOV R1, # 0x32
	str r1, [r0]
	bl xielcd
	ldr r6, = lcdyanshi
yanshila5:
	subs r6, # 1
	bne yanshila5
	MOV R1, # 0x28
	str r1, [r0]
	bl xielcd
	MOV R1, # 0x0c
	str r1, [r0]
	bl xielcd
	MOV R1, # 0x01
	str r1, [r0]
	bl xielcd
	ldr r6, = lcdyanshi
yanshila6:
	subs r6, # 1
	bne yanshila6
	

xielcd:
	push {r0-r9, lr}
	ldr r4, = 0x22004100
	ldmia r4!, {r0-r3}
	bl xielcd1
	ldr r4, = 0x22004110
	ldmia r4!, {r0-r3}
	bl xielcd1
	pop {r0-r9, pc}
	
xielcd1:
	push {r0-r10, lr}
	ldr r7,  = 0x422101bc
	mov r11, # 1
	str r11, [r7]
	ldr r5, = 0x422181b0
	stmia r5!, {r0-r3}
	ldr r6, = lcdyanshi1
yanshila:
	subs r6, # 1
	bne yanshila
	mov r11, # 0
	str r11, [r7]
	pop {r0-r10, pc}
	
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
	
