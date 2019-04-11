  	.thumb                 
        .syntax unified

.section .data
anjianmabiao:	.int anjianfanhui+1,anjian1+1,anjian2+1,anjianfanhui+1,anjian4+1,anjianfanhui+1,anjianfanhui+1,anjianfanhui+1,anjian8+1
	
        .equ STACKINIT, 	0x20005000
	.equ lcdyanshia, 	40000
	.equ anjianyanshi,	40000
	.equ led1,		0x42228188
	
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
	mov r1, # 0x32
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
	ldr r1, = 0x1d8402
	str r1, [r0]

	ldr r0, = 0x40021018 @rcc_apb2_enr
	ldr r1, = 0x83d
	str r1, [r0]
	
ioshezhi:
	@@AFIO-MAPR 开SWD
	ldr r0, = 0x40010004
	ldr r1, = 0x02000000
	str r1, [r0]
	ldr r0, = 0x40010800
	ldr r1, = 0x44448888 
	str r1, [r0]
	ldr r1, = 0x44444bbb
	str r1, [r0, # 4]
	mov r1, # 0xf
	str r1, [r0, # 0x0c]

	ldr r0, = 0x40011400
	ldr r1, = 0x44444344
	str r1, [r0]
	
	
tim1chushihua:
	ldr r0, = 0x40012c00
	ldr r1, = 5000
	str r1, [r0, # 0x2c] @ tim1_arr 
	ldr r1, = 7200
	str r1, [r0, # 0x28] @ tim1_psc
	ldr r1, = 0x78
	str r1, [r0, # 0x18] @ tim1_ccmr1
	ldr r1, = 0x1
	str r1, [r0, # 0x20] @ tim1_ccer
	ldr r1, =  2500
	str r1, [r0, # 0x34] @ tim1_ccr1
	ldr r1, = 0x8000
	str r1, [r0, # 0x44] @ tim1_BDTR
	ldr r1, = 0x81
	str r1, [r0]

	ldr r1, = 0x20000304
	ldr r2, = 5000
	str r2, [r1]
	ldr r2, = 2500
	str r2, [r1, # 4]
	ldr r2, = 7200
	str r2, [r1, # 8]
	mov r2, # 0
	str r2, [r1, # 12]
	str r2, [r1, # 16]
	

tingzhuba:
	ldr r0, = 0x40012c00
	ldr r1, = 0x20000304
	ldr r2, [r1]
	str r2, [r0, # 0x2c]
	add r12, r1, # 4
	bl anjianpanduan
	ldr r3, [r1, # 4]
	cmp r3, r2
	bls zhankongpanduan
	mov r3, r2
zhankongpanduan:	
	str r3, [r0, # 0x34]
	add r11, r1, # 8
	bl anjianpanduan
	ldr r4, [r1, # 8]
	ldr r5, = 0xffff
	cmp r4, r5
	bls pinlvpanduan
	mov r4, r5
pinlvpanduan:
	str r4, [r0, # 0x28]
	b tingzhuba
	

anjianpanduan:
	push {r0-r5, lr}
	ldr r0, = 0x20000300
	mov r1, # 0
	str r1, [r0]
	ldr r4, = 0x42210100
	ldmia r4!, {r0-r3}
	ldr r4, = 0x22006000
	stmia r4!, {r0-r3}
	ldr r4, = 0x20000300
	ldr r0, = anjianmabiao
	ldr r3, [r4]
	cmp r3, # 0xf
	beq anjianfanhui
	mov r5, # 0xf
	sub r3, r5, r3
	lsl r3, # 2
	add r3, r0, r3
	ldr r3, [r3]
	mov pc, r3	
anjian1:
	ldr r0, = led1
	mov r1, # 0
	str r1, [r0]
	ldr r0, = 0x20000310
	ldr r1, [r0]
	add r1, # 1
	str r1, [r0]
	ldr r3, = 0xfff
	cmp r1, r3
	bne anjianfanhui
	ldr r0, = 0x20000310
	mov r1, # 0
	str r1, [r0]
	ldr r1, [r12]
	add r1, # 1
	str r1, [r12]

anjianfanhui:
	pop {r0-r5, pc}
anjian2:
	ldr r0, = led1
	mov r1, # 1
	str r1, [r0]
	ldr r0, = 0x20000310
	ldr r1, [r0]
	add r1, # 1
	str r1, [r0]
	ldr r3, = 0xfff
	cmp r1, r3
	bne anjianfanhui
	ldr r0, = 0x20000310
	mov r1, # 0
	str r1, [r0]
	ldr r1, [r12]
	sub r1, # 1
	cmp r1, # 2
	bhi anjiantaixiao
	mov r1, # 2
anjiantaixiao:
	str r1, [r12]
	pop {r0-r5, pc}
anjian4:
	ldr r0, = led1
	mov r1, # 0
	str r1, [r0]
	ldr r0, = 0x20000310
	ldr r1, [r0]
	add r1, # 1
	str r1, [r0]
	ldr r3, = 0xfff
	cmp r1, r3
	bne anjianfanhui
	ldr r0, = 0x20000310
	mov r1, # 0
	str r1, [r0]
	ldr r1, [r11]
	add r1, # 1
	str r1, [r11]
	pop {r0-r5, pc}
anjian8:
	ldr r0, = led1
	mov r1, # 1
	str r1, [r0]
	ldr r0, = 0x20000310
	ldr r1, [r0]
	add r1, # 1
	str r1, [r0]
	ldr r3, = 0xfff
	cmp r1, r3
	bne anjianfanhui
	ldr r0, = 0x20000310
	mov r1, # 0
	str r1, [r0]
	ldr r1, [r11]
	sub r1, # 1
	cmp r1, # 2
	bhi anjiantaixiao1
	mov r1, # 2
anjiantaixiao1:
	str r1, [r11]
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

	
	
