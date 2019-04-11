	 .thumb                 
         .syntax unified
.section .data
         .equ STACKINIT,          0x20005000
	 .equ yanshius,           0x20000200
	 .equ ledkongzhi,         0x20000204
	 .equ hongwaikuandu,      0x20000208
	.equ hongwaikuandu1,      0x2000020c
	.equ hongwaikuanduhe,     0x20000210
	.equ hongwaipianyi,	  0x20000214
	.equ hongwaijiema, 	  0x20000218
	.equ hongwaishu,	  0x20000220
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
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word _tim3dingshiqi +1
 	
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
rccapb1enr:
	ldr r0, = 0x4002101c
	ldr r1, = 0x02
	str r1, [r0]
rccapb2enr:
        ldr r0, = 0x40021018
        mov r1, # 0x2d
        str r1, [r0]
ioshezhi:
	ldr r0, = 0x40010C00
	ldr r1, = 0x4444444B
	str r1, [r0]
	ldr r0, = 0x40010c0c
	mov r1, # 0x01
	str r1, [r0]
	bl tim3dingshiqi
zhuchengxu:
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
tim3dingshiqi:
	push {r0-r5, lr}
        ldr r0, = 0x4000042C 
        mov r1, # 900
        str r1, [r0]
        ldr r0, = 0x40000428 @psc
        mov r1, # 0
        str r1, [r0]
	ldr r0, = 0x4000041C  @ccmr2
        ldr r1, = 0x78     
        str r1, [r0]
        ldr r0, = 0x40000420  @ccer
        ldr r1, = 0x100        
        str r1, [r0] 
        ldr r0, = 0x40000400  @ cr1
        mov r1, #0x81
        str r1, [r0]
        ldr r0, = 0x40000434 @ccr3
	mov r1, # 10
	pop {r0-r5, pc}

	
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
_tim3dingshiqi:
	ldr r8, = 0xffaabbcc
	bx lr

	

	
	
	
	
