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
	.word _extizhongduan + 1
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
	ldr r0, = 0x40010800 @ gpioa
	ldr r1, = 0x44444484 
	str r1, [r0]
	ldr r0, = 0x4001080C
	mov r1, # 0x02
	str r1, [r0]
        ldr r0, = 0x40011400
        ldr r1, = 0x44444344
        str r1, [r0]
extiexti:
	ldr r0, = 0x40010008 @AFIO_EXTICR1
	mov r1, # 0
	str r1, [r0] @PA1外部中断
	mov r1, # 0x02
	ldr r0, = 0x40010400 @EXTI_IMR中断屏蔽寄存器
	str r1, [r0]
	ldr r0, = 0x40010404 @EXTI_EMR事件屏蔽
	str r1, [r0]
	ldr r0, = 0x4001040C @EXTI_FTSR下降沿触发
	str r1, [r0]
	ldr r0, = 0xE000E100 @NVIC_ISER0 SETENA0
	mov r1, # 0x80 @ exti1开中断
	str r1, [r0]
ledhanshu:
	ldr r0, = 0x4001140C
	mov r1, # 0x04
	str r1, [r0]
	ldr r2, = yanshius
	ldr r1, = 0x186a00
	str r1, [r2]
	bl sysyanshi
	mov r1, # 0
	str r1, [r0]
	ldr r2, = yanshius
	ldr r1, = 0x186a00
	str r1, [r2]
	bl sysyanshi
	ldr r0, = 0x20000228
	ldr r1, = 0x22004400
	str r1, [r0]
	ldr r0, = 0x2000021c
	ldr r1, = 0x22004c18
	str r1, [r0]
	b ledhanshu
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
_extizhongduan:
	push {r0-r7, lr}
	ldr r0, = hongwaipianyi
	ldr r1, = 0x22004c00
	str r1, [r0]
kaishile:
	ldr r4, = 0xFFFFF0
	ldr r5, = yanshius
	str r4, [r5]
	bl sysyanshi
dengdaigaomaichong:
	ldr r0, = 0xE000E018
	ldr r0, [r0]
	ldr r1, = 0xF00000
	cmp r0, r1
	bls fanhuizhuchengxu
	ldr r0, = 0x42210104
	ldr r0, [r0]
	cmp r0, # 1
	bne dengdaigaomaichong
	ldr r2, = hongwaikuandu
	ldr r1, = 0xE000E018
	ldr r1, [r1]
	ldr r3, = 0xFFFFF0
	subs r3, r1
	str r3, [r2]
	ldr r4, = 0xFFFFF0
	ldr r5, = yanshius
	str r4, [r5]
	bl sysyanshi
dengdaidimaichong:
	ldr r0, = 0xE000E018
	ldr r0, [r0]
	ldr r1, = 0xF00000
	cmp r0, r1
	bls fanhuizhuchengxu
	ldr r0, = 0x42210104
	ldr r0, [r0]
	cmp r0, # 0
	bne dengdaidimaichong
	ldr r3, = hongwaikuandu1
	ldr r1, = 0xE000E018
	ldr r1, [r1]
	ldr r2, = 0xFFFFF0
	subs r2, r1
	str r2, [r3]
panduan:
	ldr r1, = hongwaikuandu
	ldr r1, [r1]
	ldr r2, = hongwaikuandu1
	ldr r2, [r2]
	adds r2, r1
	ands r2, # 0x1E000
	cmp r2, # 0x2000
	beq dd1
	cmp r2, # 0x4000
	beq dd2
	b dd5
dd1:
	mov r2, # 0
	b dd3
dd2:
	mov r2, # 1
dd3:
	ldr r0, = hongwaipianyi
	ldr r1, [r0]
	stmia r1!, {r2}
	str r1, [r0]
dd5:
	ldr r2, = 0x22004c80
	cmp r1, r2
	bne kaishile
fanhuizhuchengxu:
	ldr r0, = 0x40010414 @挂起寄存器EXTI_PR
	mov r1, # 0x02
	str r1, [r0]
	pop {r0-r7, pc}
	

	
	
	
	
