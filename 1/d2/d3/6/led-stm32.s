        .thumb                 
        .syntax unified
.section .data		
         .equ STACKINIT, 	0x20005000
	 .equ yanshius, 	0x20000200	
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
@nvicchushihua:
	@ldr r0, = 0xE000ED0C @中断复位控制寄存器
	@ldr r1, = 0x05FA0500
	@str r1, [r0]
	@ldr r0, = 0xE000e180 @NVIC_ICER0 CLRENA0
	@ldr r1, = 0x00000000
	@str r1, [r0]
	@ldr r0, = 0xE000E200 @NVIC_ISPR0 SETPEND0
	@ldr r1, = 0x00000000
	@str r1, [r0]
	@ldr r0, = 0xE000E280 @NVIC_ICPR0 CLRPEND0
	@ldr r1, = 0x00000000
	@str r1, [r0]
	@ldr r0, = 0xE000E300 @NVIC_IABR0 ACTIVE0
	@ldr r0, = 0xE000E41C @NVIC_IPR0 IP0
	@mov r1, # 0xC0
	@strb r1, [r0, # 29]
	@ldr r0, = 0xE000E100 @NVIC_ISER0 SETENA0
	@ldr r1, = 0x20000000 @ tim3中断开
	@str r1, [r0]
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
	ldr r1, = 0xfffeee
	str r1, [r2]	
	bl sysyanshi
	mov r1, # 0
	str r1, [r0]
	ldr r2, = yanshius
	ldr r1, = 0xfffeee
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
