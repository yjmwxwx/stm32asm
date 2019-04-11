	 .thumb                 
         .syntax unified
.section .data
         .equ STACKINIT, 0x20005000
	 .equ led1,	0x422101a0
	 .equ ledyanshi, 80000
	
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
	.word 0 @ exti
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
	.word _tim1 + 1
	.word _tim2 + 1
	
_start:
	ldr r0, = 0x20000200
	mov r1, # 0
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
        ldr r0, = 0x40021018 @ apb2enr
        ldr r1, = 0x805
        str r1, [r0]
	mov r1, # 0x01
	str r1, [r0, # 4] @ apb1enr
ioshezhi:
	ldr r0, = 0x40010800 @ gpioa
	ldr r1, = 0x44444484 
	str r1, [r0]
	ldr r1, = 0x4444444b
	str r1, [r0, # 4]
	
	ldr r0, = 0x4001080C
	mov r1, # 0x02
	str r1, [r0]

	@@AFIO-MAPR 开SWD模式
	ldr r0, = 0x40010004
	ldr r1, = 0x02000000
	str r1, [r0]
tim2dingshiqi:
	ldr r0, = 0x40000000
	ldr r1, = 0Xffff
	str r1, [r0, # 0x2c] @ arr
	ldr r1, = 72
	str r1, [r0, # 0x28] @ psc
	ldr r1, = 0x100
	str r1, [r0, # 0x18] @ ccmr1
	ldr r1, = 0x30
	str r1, [r0, # 0x20] @ ccer
	mov r1, # 1
	str r1, [r0, # 0x0c] @ dier
	mov r1, # 0
	str r1, [r0, # 0x10] @ sr
	mov r1, # 0x01
	str r1, [r0]
	ldr r0, = 0xe000e100
	ldr r1, = 0x18000000
	str r1, [r0] @ tim2zhongduan

tim1dingshiqi:	
	ldr r0, = 0x40012c00
	ldr r1, = 110
	str r1, [r0, # 0x2c] @ tim1-arr
	ldr r1, = 7200
	str r1, [r0, # 0x28] @ tim1-psc
	ldr r1, = 0x60
	str r1, [r0, # 0x18] @ tim1-ccmr1
	ldr r1, = 0x1
	str r1, [r0, # 0x20] @ tim1-ccer
	ldr r1, = 100
	str r1, [r0, # 0x34] @ tim1-ccr1
	ldr r1, = 0x8000
	str r1, [r0, # 0x44] @ tim1-BDTR
	ldr r1, = 0x2
	str r1, [r0, # 0x0c] @ dier
	mov r1, # 0x19
	str r1, [r0]
	ldr r5, = 0x20000200

kammengou:
	ldr r0, = 0x40003000
	ldr r1, = 0x5555
	str r1, [r0]
	mov r1, # 4
	str r1, [r0, # 4]
	ldr r1, = 0x28c
	str r1, [r0, # 8]
	ldr r1, = 0xaaaa
	str r1, [r0]
	ldr r1, = 0xcccc
	str r1, [r0]

zhuchengxu:
	ldr r0, = 0x40003000
	ldr r1, = 0xaaaa
	str r1, [r0]
	b zhuchengxu
	
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

_tim2:
	ldr r0, = 0x40000000
	ldr r1, [r0, # 0x10]
	tst r1, # 0x04
	beq tim2fanhui
	mov r1, # 0
	str r1, [r0, # 0x24]
	ldr r1, [r0, # 0x38]
	str r1, [r5], # 4
	ldr r0, = 0x40012c00
	mov r1, # 0x19
	str r1, [r0]
	
tim2fanhui:
	mov r1, # 0
	str r1, [r0, # 0x10]
	bx lr
_tim1:
	ldr r0, = 0x40012c00
	mov r1, # 0
	str r1, [r0]
	str r1, [r0, # 0x10]
	add r9, # 1
	bx lr
	
	

	
	
	
	
