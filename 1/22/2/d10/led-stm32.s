@@@
        .thumb                 
        .syntax unified
@@@
        .equ STACKINIT, 	0x20005000
	.equ rcckz,		0x40021000 @rcc时钟控制寄存器
	.equ rccpz,		0x40021004 @时钟配置寄存器
	.equ flashacr,		0x40022000 @flash闪存访问寄存器 
   	.equ syskz,       	0xE000E010 @ 控制寄存器
    	.equ syscz,        	0xE000E014 @systick定时器重载
    	.equ syssz,        	0xE000E018 @systick计数值查询
		 		   	
.section .text

vectors_table:
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
chushihua:
	mov r0, #0
	mov r1, #0
	mov r2, #0
	mov r3, #0
	mov r4, #0
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0

shizhong:
	ldr r0, = rcckz
	ldr r1, = 0x14D83
	str r1, [r0]
gsszbz: @高速时钟标志位
	ldr r1, [r0]
	ldr r2, = 0x34D83
	cmp r2, r1 
	bne	gsszbz

	@FLASH缓冲 缓冲开启 
	ldr r0, = flashacr
	mov r1, # 0x00000032
	str r1, [r0]
	@设置
	ldr r0, = rccpz
	ldr r1, = 0x1D8400
	str r1, [r0]
	
	ldr r0, = rcckz
	ldr r1, = 0x1033D03
	str r1, [r0]
chaxun:
	ldr r1, [r0]
	ldr r2, = 0x03033D03
	cmp r1, r2
	bne chaxun

	ldr r0, = rccpz
	ldr r1, = 0x1D8402
	str r1, [r0]

gpioakou:
	ldr r0, = 0x40021018 
	ldr r1, = 0x805
	str r1, [r0]

	ldr r0, = 0x40010804
	ldr r1, = 0x4444444B
	str r1, [r0]

	ldr r0, = 0x4001080C
	ldr r1, = 0x100
	str r1, [r0]

systick:

	ldr r1, = syskz
	ldr r0, = syscz
	ldr r2, = syssz
	
	mov r3, #0
	str r3, [r1]

	ldr r3, = 0x2328
	str r3, [r0]
	str r3, [r2]

	mov r3, # 0x03
	str r3, [r1]

dingshiqi3:
	ldr r0, = 0xE000E100
	ldr r1, = 0x20000000
	str r1, [r0]
	
	ldr r0, = 0x4002101C
	mov r1, # 0x02 
	str r1, [r0] 

	ldr r0, = 0x4000042C 
	ldr r1, = 0xFFFF
	str r1, [r0]

	ldr r0, = 0x40000428 
	ldr r1, = 0x44C
	str r1, [r0]

	ldr r0, = 0x40000418  
	ldr r1, = 0x78     
	str r1, [r0]
	
	ldr r0, = 0x40000404 
	mov r1, #0x40
	str r1, [r0]

	ldr r0, = 0x4000040C 
	ldr r1, = 0x02	     
	str r1, [r0] 

	ldr r0, = 0x40000414 
	mov r1, #0x03
	str r1, [r0]

	ldr r0, = 0x40000420
	mov r1, #0x01
	str r1, [r0]


dingshiqi1:

	ldr r0, = 0x40021018 
	ldr r1, = 0x805
	str r1, [r0]

	ldr r0, = 0x40012C2C
	ldr r1, = 0xFFFF
	str r1, [r0]

	ldr r0, = 0x40012C28
	mov r1, # 10
	str r1, [r0]

	ldr r0, = 0x40012C08
	ldr r1, = 0xD5
	str r1, [r0]

        ldr r0, = 0x40012C44
	ldr r1, = 0x807F
	str r1, [r0]
	
	ldr r0, = 0x40012C20
	ldr r1, = 0x05
	str r1, [r0]

	ldr r0, = 0x40012C18
	ldr r1, = 0x78
	str r1, [r0]

	ldr r0, = 0x40012C04 
	ldr r1, = 0x05
	str r1, [r0]

	ldr r0, = 0x40000400 
	ldr r1, = 0x81
	str r1, [r0]

	ldr r0, = 0x40012C00
	ldr r1, = 0x81
	str r1, [r0]





	

	
 
main: 
    ldr r0, = 0x40012C34
    ldr r1, = 0xFF
    str r1, [r0]

    ldr r0, = 0x40000434
    ldr r1, = 0xFF
    str r1, [r0]
    bl yanshi
    b main

yanshi:    
    cmp r5, #2
    bne yanshi
    mov r5, #0
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
  	adds r5, 1
        bx lr  
_tim3dingshiqi:
	adds r7, 1
	cmp r7, # 3
	bne qingchu
	mov r7, # 0
	ldr r0, = 0x40012C20
	ldr r1, = 0x00
	str r1, [r0] 
	
	
qingchu:	
	ldr r0, = 0x40000410
	mov r1, # 0 
	str r1, [r0]
	bx lr	
         

