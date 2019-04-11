@ stm32f030f4p6 asm 
@ 温度控制
	 .thumb                 
         .syntax unified
.section .data
	.equ duizhanding,       0x20001000
	.equ dqrwyxj,           0x20000044 @ 当前任务优先级
	.equ xtzgyxj,           0x20000048 @ 系统里最高优先级
	.equ dangqian,          0x2000004c @  当前TCB任务控制块指针
	.equ dengyunxing,       0x20000050 @ 待运行TCB任务控制块指针
	.equ jiuxubiao,         0x20000054 @ 就绪查找表8个任务
	 @ 保留0X20
	.equ renwubiao,         0x20000074 @ 任务控制块指针表
	@保留0x20
	.equ renwukongzhikuai,  0x20000094 @ 任务控制块起始地址
	@每个控制块4个数据，+0堆栈顶，+4任务时间,+8优先级，+C
	
	.equ renwuduizhan,	0x20000500 @ 任务堆栈
	
	
	
.section .text
vectors:          @向量表
        .word duizhanding                     
        .word _start + 1             @复位向量
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
        .word 0 
        .word 0    
        .word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word _svc + 1
	.word 0
	.word 0
	.word _pendsvzhongduan + 1
	.word _systickzhongduan + 1
	
	

_start:
_shizhong:                     @时钟设置
	ldr r2, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r2]
	ldr r0, = 0x40021000 @ rcc
	@0x34时钟控制寄存器 2 (RCC_CR2)
	movs r1, # 0x01
	str r1, [r0, # 0x34]  @ HSI开14M时钟
_dengdai14mshizhongwending:    @等14M时钟稳定
	ldr r1, [r0, # 0x34]
	lsls r1, r1, # 30     @ 左移30位
	bpl _dengdai14mshizhongwending  @ 等待14M时钟稳定

_neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
_neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan

_systick:
	@ 0xe000ed20 30-31 youxianji
	@ 22-23 PENDSV
	ldr r0, = 0xe000ed20
	ldr r1, = 0x00c00000
	str r1, [r0]
	
	ldr r0, = 0xe000e010
	ldr r1, = 100    
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	movs r1, # 0x07
	str r1, [r0]

	movs r0, # 0
	msr psp, r0

	ldr r0, = renwuduizhan
	ldr r1, = _kongxianrenwu
	adds r1, r1, # 1
	ldr r2, = 0x01000000
	movs r3, # 0
	mov r7, r2
	mov r6, r1
	mov r5, r3
	mov r4, r3
	mov r12, sp
	mov sp, r0
	push {r0-r7}
	push {r4-r7}
	ldr r0, = renwukongzhikuai
	ldr r1, = renwuduizhan
	str r1, [r0]

	
	ldr r1, = renwubiao
	
	str r0, [r1]

	
_renwu1chushihua:
	ldr r0, = renwuduizhan
	ldr r1, = 0x100
	subs r0, r0, r1         
	ldr r1, = _renwu1
	adds r1, r1, # 1
	ldr r2, = 0x01000000
	movs r3, # 0
	mov r7, r2
	mov r6, r1
	mov r5, r3
	mov r4, r3
	mov sp, r0
	push {r0-r7}	
	push {r0-r3}
	ldr r0, = renwukongzhikuai
	ldr r1, = renwuduizhan
	ldr r2, = 0x100
	subs r1, r2
	adds r0, # 0x10
	str r1, [r0]
	
	ldr r1, = renwubiao
        str r0, [r1, # 0x04]
	

	ldr r0, = jiuxubiao
	movs r1, # 1
	str r1, [r0]
	str r1, [r0, # 0x04]

	mov sp, r12

	bl _diaodu
	

_dddd:
	b _dddd

_kongxianrenwu:
	ldr r0, = jiuxubiao
	movs r1, # 1
	str r1, [r0, # 0x04]
	bl _ccc
	bl _diaodu
	b _kongxianrenwu
	
_renwu1:
	ldr r0, = jiuxubiao
	movs r1, # 0
	str r1, [r0, # 0x04]
	bl _ccc
	bl _diaodu
	b _renwu1

_ccc:
	push {r0-r7,lr}
	pop {r0-r7,pc}
_diaodu:
        ldr r0, = jiuxubiao
	movs r1, # 0x08
	lsls r1, # 2
_zhaozuigao:
        subs r1, r1, # 4
        ldr r2, [r0, r1]
        cmp r2, # 1
        bne _zhaozuigao
_zhaodaozuigao:
	ldr r0, = renwubiao
	adds r0, r1
	ldr r2, = dengyunxing
        str r0, [r2]
	ldr r0, = 0xe000ed04
	ldr r1, = 0x10000000
	str r1, [r0]
	bx lr
	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc:
	bx lr
_pendsvzhongduan:             @PENDSV中断
	cpsid i               @ 关中断
	mrs r0, psp           @ 读PSP当前地址到R0
	cmp r0, # 0
	beq _qiehuanrenwu
	mov r12, sp
	mov sp, r0
	push {r4-r7}
_qiehuanrenwu:                @ 切换任务
	ldr r0, = dangqian    @ 当前任务指针
	ldr r1, = dengyunxing @ 等待运行指针
	ldr r2, [r1]          @ 取出任务表里的指针
	str r2, [r0]          @ 任务表里的指针写到待运行指针
	ldr r0, [r2]          @ R0等于任务控制块表
	ldr r0, [r0]          @ 取出任务堆栈底
	subs r0, # 0x30
	mov sp, r0
	pop {r4-r7}
	mov r1, lr
	movs r2, # 0x04
	orrs r1, r2
	mov lr, r1
	mov r0, sp
	msr psp, r0
	mov sp, r12
	cpsie i               @ 开中断
	bx lr
_systickzhongduan:
	ldr r0, = 0xe0000d04
	ldr r1, = 0x02000000
	str r1, [r0]
	ldr r0, = renwukongzhikuai
	ldr r1, [r0, # 0x14]
	adds r1, r1, # 1
	str r1, [r0, # 0x14]
	bx lr
