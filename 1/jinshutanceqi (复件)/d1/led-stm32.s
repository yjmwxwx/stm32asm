	 .thumb                 
         .syntax unified
.section .data
mingling:	.byte 0x02, 0x28, 0x0e, 0x06, 0x01
lcdshuju:	.byte 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66
	@.ascii "4_LINE DRIVER"
	
        	.equ STACKINIT,          0x20005000
		.equ yanshius,           0x20000200
		.equ ledkongzhi,         0x20000204
		.equ lcdshu,		  0x20000208
		.equ lcdyanshi,		80000

	

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
	ldr r0, = yanshius
	ldr r1, = 0xfffe
	str r1, [r0]
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


rccapb2enr:
        ldr r0, = 0x40021018
        mov r1, # 0x3D
        str r1, [r0]
ioshezhi:
	ldr r0, = 0x40010800 @ gpioa
	ldr r1, = 0x44443443
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
	ldrb r2, [r1, r3]
	str r2, [r0]
	add r3, # 1
	ldr r10, = 0x42210180
	mov r9,  # 0
	str r9, [r10]
	bl xielcd
	cmp r3, # 4
	bne lcdchushihua1

lcdis7:

	mov r4, # 0

lcdchengxu:
	mov r3, # 0
	mov r2, # 0x80
	ldr r0, = 0x20000208
lcdzl:
	add r2, r2, r4
	str r2, [r0]
	ldr r10, = 0x42210180
	mov r9,  # 0
	str r9, [r10]
	bl xielcd
	mov r3, # 0
	ldr r0, = 0x20000208
	ldr r1, = lcdshuju
lcdsj:
	ldrb r2, [r1, r3]
	str r2, [r0]
	add r3, # 1
	ldr r10, = 0x42210180
	mov r9,  # 1
	str r9, [r10]

	bl xielcd
	cmp r3, # 16
	bne lcdsj
	cmp r4, # 0x40
	beq tinglea
	mov r4, # 0x40
	b lcdchengxu

tinglea:
	b lcdis7


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
	push {lr}
	ldr r7,  = 0x4221018c
	mov r11, # 1
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
	pop {pc}
	
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
	
