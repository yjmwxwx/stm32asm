        .thumb                 
        .syntax unified
.section .data
yjm:	 .short 0x001f, 0xf81f, 0xffe0, 0x07ff, 0xf800
wxwx:	 .byte 0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00		
         .equ STACKINIT, 	0x20005000
	 .equ yanshius, 	0x20000200	
.section .text
vectors:        
        .word STACKINIT         
        .word _start        
        .word _nmi_handler  
        .word _hard_fault 
        .word _memory_fault 
        .word _bus_fault    
        .word _usage_fault    
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
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word _tim3dingshiqi 
_start:
	mov r0, # 0
	mov r1, # 0
	mov r2, # 0
	mov r3, # 0
	mov r4, # 0
	mov r5, # 0 
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
ledled:
        ldr r0, = 0x40021018
        mov r1, # 0x39
        str r1, [r0]
        ldr r0, = 0x40011400
        ldr r1, = 0x44444344
        str r1, [r0]
ledhanshu:	
	ldr r0, = 0x4001140C
	mov r1, # 0x04
	str r1, [r0]
	ldr r2, = yanshius
	ldr r1, = 0xffffff
	str r1, [r2]	
	bl sysyanshi
	mov r1, # 0
	str r1, [r0]
	ldr r2, = yanshius
	ldr r1, = 0xffffff
	str r1, [r2]	
	bl sysyanshi
	b ledhanshu
sysyanshi:
	push {r0-r5, lr}
	ldr r0, = 0xE000E010
	ldr r1, = yanshius
	ldr r1, [r1] 
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	mov r1, # 0x01
	str r1, [r0]
dingshiqi3:
    ldr r0, = 0xE000E100
    ldr r1, = 0x20000000
    str r1, [r0]
    
    ldr r0, = 0x4002101C
    mov r1, # 0x02 
    str r1, [r0] @ 开TIM3时钟

    ldr r0, = 0x4000042C @TIM ARR自动重载寄存器
    ldr r1, = 0x1388
    str r1, [r0]

    ldr r0, = 0x40000428 @psc预分频器
    ldr r1, = 0x1C1F
    str r1, [r0]

    ldr r0, = 0x4000040C @tim dier 允许更新中断
    mov r1, # 0x41
    str r1, [r0] 

    ldr r0, = 0x40000400 @使能定时器3
    mov r1, #0x81
    str r1, [r0]

        
tingzaizhe:
	ldr r3, [r0, # 8]
	cmp r3, # 0 
	bne tingzaizhe
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
_tim3dingshiqi:
    adds r6, 1
    adds r7, 1
    bx lr

