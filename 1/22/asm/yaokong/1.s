	 .thumb                 
         .syntax unified
.section .data
anjianmabiao:	.int 0x5f5914,0x5f5912,0x5f5911,0x5f5918
         .equ STACKINIT, 0x20005000
	 .equ yanshi,   0xffffffff
	 .equ ledkongzhi, 0x20000204
	 .equ diandeng,  0x422101b0
	
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
	ldr r0, = 0x20000000
	mov r1, # 0
	str r1, [r0]
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	str r1, [r0, # 0x0c]
	str r1, [r0, # 0x100]
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
        mov r1, # 0x05
        str r1, [r0]

systick:
	ldr r0, = 0xe000e010
	mov r1, # 0
	str r1, [r0]
	ldr r1, = 0xffffff
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	mov r1, # 0
	str r1, [r0]
	ldr r0, = 0xe000ed23  @systick优先级
	mov r1, # 240
	str r1, [r0]
ioshezhi:
	ldr r0, = 0x40010800 @ gpioa
	ldr r1, = 0x44444484 
	str r1, [r0]
	ldr r1, = 0x44424444
	str r1, [r0, # 4]
	
	ldr r0, = 0x4001080C
	mov r1, # 0x02
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
	ldr r0, = 0x4001040c @EXTI_FTSR下降沿触发
	str r1, [r0]
	ldr r0, = 0xE000E100 @NVIC_ISER0 SETENA0
	mov r1, # 0x80 @ exti1开中断
	str r1, [r0]
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
	bl yaokong315jiema
	bl nageanjian
	ldr r0, = diandeng
	ldr r1, = 0x20000100
	ldr r2, [r1]
	cmp r2, # 4
	bne diandengce
	mov r1, # 1
	str r1, [r0]
	
diandengce:
	cmp r2, # 8
	bne zhuchengxu
	mov r1, # 0
	str r1, [r0]
	b zhuchengxu
	
nageanjian:
	push {r0-r6, lr}
	ldr r0, = 0x20000000
	ldr r2, = anjianmabiao
	ldr r3, = 0x20000004
anjianpanduan:
	ldr r4, [r3]
	ldr r5, [r2, r4]
	add r4, # 4
	str r4, [r3]
	cmp r4, # 0x0c
	bhi anjianfanhui
	ldr r1, [r0]
	cmp r1, r5
	bne anjianpanduan
	ldr r0, = 0x20000100
	str r4, [r0]
anjianfanhui:
	mov r4, # 0
	str r4, [r3]
	pop {r0-r6, pc}
	
	
yaokong315jiema:
	push {r0-r6, lr}
	ldr r0, = 0x2000006c
	ldr r2, = 0x20000010
	ldr r3, = 0x7000
	ldr r4, = 0x12000
	ldr r5, = 0x10000
	ldr r6, = 0x22000180
yaokongce:
	ldr r1, [r0], # - 4
	cmp r1, r3
	bhi yaokongce1
	mov r1, # 1
	str r1, [r6], # 4
	b yaokongce3
yaokongce1:
	cmp r1, r4
	bls yaokongce2
	b yaokongce3
yaokongce2:
	cmp r1, r5
	bls yaokongce3
	mov r1, # 0
	str r1, [r6], # 4
yaokongce3:
	cmp r0, r2
	bne yaokongce
	ldr r0, = 0x2000000c
	ldr r1, [r0]
	str r1, [r0, # - 0x0c]
	pop {r0-r6, pc}
	
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
	push {r0-r12, lr}
	ldr r0, = 0xe000e010
	mov r1, # 0x07
	str r1, [r0]
chaxun315:
	ldr r1, = 0x42210104
	ldr r2, [r1]
	cmp r2, # 1
	bne chaxun315
	mov r1, # 0
	str r1, [r0]
	ldr r6, [r0, # 0x08]
	str r6, [r0, # 0x08]
	ldr r7, = 0xffffff
	sub r6, r7, r6
	ldr r2, = 0x5000
	cmp r6, r2
	bls yaokongfanhui
	ldr r2, = 0xa0000
	cmp r6, r2
	bhi yaokongfanhui1
	ldr r2, = 0x20000008
	ldr r3, [r2]
	add r3, # 4
	str r3, [r2]
	cmp r3, # 0x60
	bhi yaokongfanhui1
	ldr r0, = 0x2000000c
	str r6, [r0, r3]
	b yaokongfanhui
yaokongfanhui1:
	ldr r0, = 0x20000008
	mov r2, # 0
	str r2, [r0]
yaokongfanhui:
	ldr r0, = 0x40010414 @ exti_pr 
	mov r1, # 0x02
	str r1, [r0]
	pop {r0-r12, pc}
	
	
	
