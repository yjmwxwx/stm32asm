@ stm32f030f4p6 asm 
@ 温度控制
	 .thumb                 
         .syntax unified
.section .data
	.equ duizhanding,       0x20001000 @ 堆栈顶
	.equ dqrwyxj,           0x20000044 @ 当前任务优先级
	.equ xtzgyxj,           0x20000048 @ 系统里最高优先级
	.equ dangqian,          0x2000004c @ 当前任务指向控制块里指针
	.equ dengyunxing,       0x20000050 @ 待运行任务指向控制块里指针
	.equ jiuxubiao,         0x20000054 @ 就绪查找表8个任务
	 @ 保留0X20
	.equ renwubiao,         0x20000074 @ 指向任务控制块地址的指针表
	@保留0x20
	.equ renwukongzhikuai,  0x20000094 @ 任务控制块地址
	@每个控制块4个数据，+0堆栈顶，+4任务时间,+8优先级，+C
	
	.equ renwuduizhan,	0x20000500 @ 任务堆栈顶
	
	
	
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

_neicunqingling:                         @ 0x1000的内存清零
	                                 @ 1K=1024BIT=0X400
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000                  
_neicunqinglingxunhuan:                   @ 内存清零循环
	subs r3, # 4                    
	str r1, [r0, r3]                  
	bne _neicunqinglingxunhuan                @

_systick:                                  @ systick定时器初始化
	@ 0xe000ed20 30-31 youxianji
	@ 22-23 PENDSV
	ldr r0, = 0xe000ed20
	ldr r1, = 0x00c00000
	str r1, [r0]                      @设置优先级
	
	ldr r0, = 0xe000e010
	ldr r1, = 100    
	str r1, [r0, # 4]
	str r1, [r0, # 8]
	movs r1, # 0x07
	str r1, [r0]

_renwuchushihua1:                       @ 空闲任务初始化
	ldr r0, = renwuduizhan          @ 任务堆栈顶             
	ldr r1, = _kongxianrenwu        @ 空闲任务地址 
	adds r1, r1, # 1                @ +1进入thumb 
	ldr r2, = 0x01000000            @ xpsr
	movs r3, # 0                    
	mov r7, r2                      @ pc
	mov r6, r1                     
	mov r5, r3                       
	mov r4, r3
	mov r12, sp                     @ 当前堆栈指针放到R12 
	mov sp, r0                      @ 当前堆栈指针等于任务堆栈顶
	push {r0-r7}                    @ 把刚才数据保存到任务堆栈
	push {r4-r7}                    
	ldr r0, = renwukongzhikuai      @ 任务控制块地址
	ldr r1, = renwuduizhan          @ 任务堆栈顶
	str r1, [r0]                    @ 空闲任务的堆栈顶写到任务控制块

	
	ldr r1, = renwubiao             @ 任务表
	 
	str r0, [r1]                    @ 把任务控制块地址写到任务表

	
_renwu1chushihua:                     @ 同上面一样，只是地址偏移
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
	

	ldr r0, = jiuxubiao           @ 就绪表
	movs r1, # 1                  
	str r1, [r0]                  @ 空闲任务一直就绪
	str r1, [r0, # 0x04]          @ 任务1就绪

	mov sp, r12                   @ 恢复堆栈指针

	movs r0, # 0
	msr psp, r0               @ PSP清零

	bl _diaodu                    @ 自动调度

_dddd:
	b _dddd

_kongxianrenwu:                        @ 空闲任务
	ldr r0, = 0x100                @ 任务1延时时间
	bl _renwushijian               @ 判断任务1到没到，到了执行调度
	ldr r0, = 0x20000704           @ 空闲任务执行次数
	ldr r1, [r0]
	adds r1, r1, # 4
	str r1, [r0]
	b _kongxianrenwu
	
_renwu1:
	ldr r0, = jiuxubiao           @ 就绪表
	movs r1, # 0
	str r1, [r0, # 0x04]          @ 任务1放开CPU
	ldr r0, = 0x20000700          @ 任务1执行次数
	ldr r1, [r0]
	adds r1, r1, # 1
	str r1, [r0]
	bl _diaodu                    @ 调度
	b _renwu1

_renwushijian:                        @ 任务多长时间执行一次
	ldr r2, = renwukongzhikuai    @ 任务控制块
	ldr r1, [r2, # 0x14]          @ 读出任务1时间
	cmp r1, r0                    @ 等不等于R0
	bls _renwushijianfanhui       @ 小于返回
	ldr r0, = jiuxubiao           @ 大于执行我
	movs r1, # 1                 
	str r1, [r0, # 0x04]          @ 就绪表里面任务1写1表示就绪
	movs r1, # 0
	str r1, [r2, # 0x14]          @ 清零任务1时间
	b _diaodu                    @ 调度
_renwushijianfanhui:
	bx lr
_diaodu:
        ldr r0, = jiuxubiao          @就绪表
	movs r1, # 0x08              @ 8个任务， 每个任务用32位表示 
	lsls r1, # 2                 @ R1等于32 
_zhaozuigao:                         @ 从高开始减，找最高优先级任务
        subs r1, r1, # 4              
        ldr r2, [r0, r1]
        cmp r2, # 1
        bne _zhaozuigao              @循环找，由于空闲任务一直就绪
	                             @没有别的任务就执行空闲的
_zhaodaozuigao:                      @ 找到了最高优先级的了
	ldr r0, = renwubiao          @ 任务表
	adds r0, r1                  @ 任务表指针偏移
	ldr r2, = dengyunxing        @ 等运行
        str r0, [r2]                 @ 任务表偏移指针写道等运行
	ldr r0, = 0xe000ed04         @ 触发pendsv中断
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
	cmp r0, # 0           @ r0和0比较
	beq _qiehuanrenwu     @ 等于0执行任务切换
	mov r12, sp           @ 堆栈指针保存到R12
	mov sp, r0            @ SP等于r0
	push {r4-r7}          @ 把R4-R7保存到堆栈最低四个32位
_qiehuanrenwu:                @ 切换任务
	ldr r0, = dangqian    @ 当前任务指针
	ldr r1, = dengyunxing @ 等待运行指针
	ldr r2, [r1]          @ 取出任务表里的指针
	str r2, [r0]          @ 任务表里的指针写到待运行指针
	ldr r0, [r2]          @ R0等于任务控制块地址表
	ldr r0, [r0]          @ 取出任务堆栈顶
	subs r0, # 0x30       @ R0等于堆栈底
	mov sp, r0            @ SP等于R0
	pop {r4-r7}           @ 弹出R4-R7
	mov r1, lr            @ lr写到R1
	movs r2, # 0x04       @ R2等于0X04 选择LR第2位
	orrs r1, r2           @ R1或R2
	mov lr, r1            @ 写回到LR
	mov r0, sp            @ R0等于堆栈底加0X10
	msr psp, r0           @ 写到PSP
	mov sp, r12           @ 恢复SP
	cpsie i               @ 开中断
	bx lr                 @ 返回
_systickzhongduan:
	ldr r0, = 0xe0000d04
	ldr r1, = 0x02000000
	str r1, [r0]                 @ 清除SYSTICK中断
	ldr r0, = renwukongzhikuai   @ 任务控制块
	ldr r1, [r0, # 0x14]         @ 任务1的任务时间
	adds r1, r1, # 1             @ 加1
	str r1, [r0, # 0x14]         @ 写回去
	bx lr                        @ 返回
