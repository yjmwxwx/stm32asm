	@ stm32f030f4p6 asm
	@fft 8点
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000
	.equ fftzhongjian,		0x20000100
	.equ fftxuanzhuanyinzi,		0x20000104
	.equ hudiezizeng,		0x20000108
shuru:
	.int 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.int 16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
hudie: .int 0,64,32,96,16,80,48,112,8,72,40,104,24,88,56,120,4,68,36,100,20,84,52,116,12,76,44,108,28,92,60,124
fft3xuanzhuanyinzi: .int 32768,0,23170,-23170,0,-32768,-23170,-23170
fft4xuanzhuanyinzi: .int 32768,0,30274,-12540,23170,-23170,12540,-30274,0,32768,-12540,-30274,-23170,-23170,-30274,-12540
fft5xuanzhuanyinzi: .int 32768,0, 32138,-6393, 30274,-12540, 27246,-18205,23170,-23170,18205,-27246, 12540,-30274,6393,-32138,0,-32768,-6393,-32138,-12540,-30274,-18205,-27246,-23170,-23170,-27246,-18205,-30274,-12540,-321938,-6393
	           
	
.section .text
vectors:        
        .word STACKINIT         
        .word _start + 1        
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
        .word 0 
        .word 0    
        .word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word _svc_handler +1
	.word 0 
	.word 0
	.word _pendsv_handler +1
	
_start:
_shizhong:	                     @时钟设置
	ldr r2, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r2]
	ldr r0, = 0x40021000 @ rcc
	@0x34时钟控制寄存器 2 (RCC_CR2)
	movs r1, # 0x01
	str r1, [r0, # 0x34]  @ HSI开14M时钟
_dengdai14mshizhongwending:	    @等14M时钟稳定
	ldr r1, [r0, # 0x34]
	lsls r1, r1, # 30     @ 左移30位
	bpl _dengdai14mshizhongwending  @ 等待14M时钟稳定

_neicunqingling:	                         @ 0x1000的内存清零
	                                 @ 1K=1024BIT=0X400
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
_neicunqinglingxunhuan:	                   @ 内存清零循环
	subs r3, # 4
	str r1, [r0, r3]
	bne _neicunqinglingxunhuan                @



	
_fftjisuan:
_fft1:	
	ldr r0, = shuru
	ldr r1, = 0x20000000
	movs r2, # 16
	ldr r3, = hudie
_fft1xunhuan:
	ldr r6, [r3]
	ldr r7, [r3, # 0x04]
	ldr r6, [r0, r6]
	ldr r7, [r0, r7]
	adds r4, r6, r7
	subs r5, r6, r7
	str r4, [r1]
	str r5, [r1, # 0x04]
	adds r1, r1, # 0x08
	adds r3, r3, # 0x08
	subs r2, r2, # 1
	bne _fft1xunhuan
	
_fft2:
	ldr r0, = 0x20000000
	mov r4, r0
	adds r4, r4, # 0x80
	mov r8, r4
_fft2xunhuan:
	ldr r4, [r0]
	ldr r5, [r0, # 0x08]
	ldr r6, [r0, # 0x04]
	ldr r7, [r0, # 0x0c]
	adds r1, r4, r5
	subs r2, r4, r5
	mov r3, r6		@0r
	movs r4, # 0	
	subs r4, r4, r7		@0i
	mov r5, r6		@3r
	mov r6, r7		@3i
	mov r7, r0
	adds r7, r7, # 0x80
	str r1, [r0]
	str r2, [r0, # 0x08]
	str r3, [r0, # 0x04]
	str r4, [r7, # 0x04]
	str r5, [r0, # 0x0c]
	str r6, [r7, # 0x0c]
	adds r0, r0, # 0x10
	cmp r0, r8
	bne _fft2xunhuan
	
_fft3:
	ldr r6, = hudiezizeng			   @蝴蝶自增变量
	ldr r5, = 0x20000080                       @内存实和虚的中间
	ldr r2, = fft3xuanzhuanyinzi               @第三步的旋转因子表地址
	ldr r1, = fftxuanzhuanyinzi                @保存旋转因子表地址的全局变量
	ldr r4, = fftzhongjian			   @保存中间的全局变量
	ldr r0, = 0x20000000                       @输出地址
	str r2, [r1]                                 
	str r5, [r4]
	movs r1, r0
	adds r1, r1, # 0x80
	mov r8, r1                                 @R8虚部
	mov r9, r0                                 @R9实部
	mov r10, r2                                @R10旋转因子
	movs r5, # 0x10                            
	mov r11, r5                                @输出和读取内存的偏移
						   @用来不同步设置不同的偏移
	movs r5, # 4                               
	mov r12, r5                                @蝴蝶执行次数
	bl _fftggg

_fft4:
	ldr r6, = hudiezizeng                      @蝴蝶自增变量
	ldr r5, = 0x20000080                       @内存实和虚的中间
	ldr r2, = fft4xuanzhuanyinzi               @第三步的旋转因子表地址
	ldr r1, = fftxuanzhuanyinzi                @保存旋转因子表地址的全局变量
	ldr r4, = fftzhongjian                     @保存中间的全局变量
	ldr r0, = 0x20000000                       @输出地址
	str r2, [r1]
	str r5, [r4]
	movs r1, r0
	adds r1, r1, # 0x80
	mov r8, r1                                 @R8虚部
	mov r9, r0                                 @R9实部
	mov r10, r2                                @R10旋转因子
	movs r5, # 0x20
	mov r11, r5                                @输出和读取内存的偏移
							@用来不同步设置不同的偏移
	movs r5, # 8						
	mov r12, r5                                @蝴蝶执行次数
	bl _fftggg

_fft5:
	ldr r6, = hudiezizeng                      @蝴蝶自增变量
	ldr r5, = 0x20000080                       @内存实和虚的中间
	ldr r2, = fft5xuanzhuanyinzi               @第三步的旋转因子表地址
	ldr r1, = fftxuanzhuanyinzi                @保存旋转因子表地址的全局变量
	ldr r4, = fftzhongjian                     @保存中间的全局变量
	ldr r0, = 0x20000000                       @输出地址
	str r2, [r1]
	str r5, [r4]
	movs r1, r0
	adds r1, r1, # 0x80
	mov r8, r1                                 @R8虚部
	mov r9, r0                                 @R9实部
	mov r10, r2                                @R10旋转因子
	movs r5, # 0x40
	mov r11, r5                                @输出和读取内存的偏移
	                                                        @用来不同步设置不同的偏移
	movs r5, # 16
	mov r12, r5				@蝴蝶执行次数
	bl _fftggg
	
	
tingting:
	b tingting
	
_fftggg:
_fftxunhuan :
	mov r0, r9				@实部内存地址
	mov r1, r8                              @虚部内存地址
	mov r2, r10                             @旋转因子偏移
	mov r3, r11                             @蝴蝶地址偏移
	ldr r4, [r0]                            @读出实部
	ldr r5, [r1]                            @读出虚部
	ldr r6, [r0, r3]                        @读出实部
	ldr r7, [r1, r3]                        @读出虚部
	ldr r3, [r2]		@sr             @读出COS
	ldr r2, [r2, # 0x04]	@si             @读出SIN
	push {r4,r5}                            @保存第一个实部和虚部到堆栈
	mov r4, r6                              @第二个的实部放到R4
	muls r4, r4, r3                         @R4乘COS
	mov r5, r7                              @第二个的虚部读到R5
	muls r5, r5, r2                         @R5乘SIN
	subs r4, r4, r5		@r	        @第二个乘旋转因子后的实部
	asrs r4, r4, # 15                       @缩小回去，所有小数都是左移15位后运算的
	mov r5, r6                              @第二个的实部放到R5
	muls r5, r5, r2                         @R5乘SIN
	muls r7, r7, r3                         @第二个的虚部R7乘COS
	adds r7, r7, r5		@i              @相加得到第二个数乘旋转因子后的虚部
	asrs r7, r7, # 15                       @缩小回去
	pop {r2,r5}                             @弹出刚才保存在堆栈里的第一个的实部和虚部
	adds r3, r2, r4                         @计算一的实部
	adds r6, r5, r7                         @计算一的虚部
	subs r2, r2, r4                         @计算二的实部
	subs r7, r5, r7                         @计算二的虚部
	mov r6, r11				@取出地址偏移
	str r3, [r0]                            @保存一的实部
	str r6, [r1]                            @保存一的虚部
	str r2, [r0, r6]                        @保存二的实部
	str r7, [r1, r6]                        @保存二的虚部
	adds r0, r0, # 0x04                     @实部地址向下移动一
	adds r1, r1, # 0x04                     @虚部地址向下移动一
	mov r9, r0                              @实部地址保存到R9
	mov r8, r1                              @虚部地址保存到R8
	mov r2, r10                             @取出旋转因子偏移
	adds r2, r2, # 0x08                     @旋转因子自增
	mov r10, r2                             @保存回去
	ldr r5, = hudiezizeng			@蝴蝶自曾变量
	ldr r4, [r5]                            @读出来
	adds r4, r4, # 1                        @蝴蝶自曾加1
	str r4, [r5]                            @保存回去
	mov r7, r12                             @读出蝴蝶要执行多少次
	cmp r4, r7                              @检查蝴蝶执行次数
	bne _fftxunhuan                         @不到次数继续循环
	movs  r4, # 0
	ldr r7, = hudiezizeng                  @蝴蝶自曾
	ldr r5, = fftzhongjian                 @内存实和虚中间
	ldr r6, = fftxuanzhuanyinzi            @旋转因子保存的地址
	ldr r5, [r5]                           @读出来
	ldr r6, [r6]                           @读出来
	str r4, [r7]                           @蝴蝶自曾清0
	
	mov r10, r6                            @旋转因子表地址放到R10
	mov r7, r11                            @读出下组蝴蝶偏移
	adds r0, r0, r7                        @加实部的地址   
	adds r1, r1, r7                        @加虚部的地址
	mov r9, r0                             @实部地址保存到R9
	mov r8, r1                             @虚部地址保存到R8
	cmp r0, r5                            @检查执行完了没有
	bne _fftxunhuan                       @继续执行下一组循环
	bx lr				     @执行完了返回
	.ltorg				     @文字池
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
