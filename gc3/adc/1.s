@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data	
        	.equ STACKINIT,          0x20000300

.section .text
vectors:        
        .word STACKINIT         
        .word _start + 1        
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
        .word _memory_fault + 1 
        .word _bus_fault + 1    
        .word _usage_fault + 1 

_start:
shizhong:
	ldr r0, = 0x40021000 @ rcc_cr
	ldr r1, = 0x15683     
	str r1, [r0]
gsszbz: 
	ldr r2, [r0]
	ldr r1, = 0x20000    
	tst r1, r2           @HSE时钟标志位           
	bne rccchushihua
	b gsszbz
rccchushihua: 
	ldr r0, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r0]           @FLASH缓冲 缓冲开启 
	ldr r0, = 0x40021004 
	ldr r1, = 0x110000    @ HSE-PLL-6倍频
	str r1, [r0]
	ldr r0, = 0x40021000
	ldr r1, = 0x1035683     @ PLL开
	str r1, [r0]
chaxun:
	ldr r2, [r0]
	ldr r1, = 0x2000000     @ PLL锁定标志位
	tst r1, r2              
	bne rccgg               @ 等待PLL锁定 
	b chaxun
rccgg:
	ldr r1, = 0x11000a      @ PLL作为系统时钟
	str r1, [r0, # 0x04]
	
	@0x34时钟控制寄存器 2 (RCC_CR2)
	movs r1, # 0x01
	str r1, [r0, # 0x34]  @ HSI开14M时钟
dengdai14mshizhongwending:
	ldr r1, [r0, # 0x34]
	lsls r1, r1, # 30     @ 左移30位
	bpl dengdai14mshizhongwending  @ 等待14M时钟稳定
	
waisheshizhong:	 @ 外设时钟              
	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@ （0）SYSCFGEN（9）ADC（11）TIM1（12）SPI（14）USART1
	@ （16）TIM15 （17）TIM6（18）TIM17 (22)DBGMCU
	ldr r1, = 0x200
	str r1, [r0, # 0x18]  
	
	ldr r0, = 0x40021014    @ AHB外部时钟
	ldr r1, = 0x60014       @ 开时钟
	str r1, [r0]
	@ DMA（0）SRAM（2）FLITF（4）CRC（6）PA（17）
	@PB（18）PC（19）PD（20）PF（22）TSCEN（24）
	ldr r0, = 0x4002101c
	ldr r1, = 0x132
	str r1, [r0]

adcchushihua:
	ldr r0, = 0x40012400  @ adc基地址
	ldr r1, = 0x80000000
	str r1, [r0, # 0x08]  @ ADC 控制寄存器 (ADC_CR)  @adc校准
dengadcjiaozhun:
	ldr r1, [r0, # 0x08]
	 movs r1, r1
	bmi dengadcjiaozhun   @ 等ADC校准
kaiadc:
	ldr r1, [r0, # 0x08]
	movs r2, # 0x01
	orrs r1, r1, r2
	str r1, [r0, # 0x08]
dengdaiadcwending:
	ldr r1, [r0]
	lsls r1, r1, # 31
	bpl dengdaiadcwending @ 等ADC稳定
tongdaoxuanze:
	ldr r1, = 0x20000  
	str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
	ldr r1, = 0x2000        @ 13 连续转换
	str r1, [r0, # 0x0c]    @ 配置寄存器 1 (ADC_CFGR1)
	movs r1, # 0x05         @ 
	str r1, [r0, # 0x14]    @ ADC 采样时间寄存器 (ADC_SMPR)
	ldr r1, = 0x400000      @ V REFINT 通道开启
	ldr r2, = 0x308
	str r1, [r0, r2]    @ 通用配置寄存器 (ADC_CCR)
	ldr r1, [r0, # 0x08]
	movs r2, # 0x04         @ 开始转换
	orrs r1, r1, r2
	str r1, [r0, # 0x08]    @ 控制寄存器 (ADC_CR)
	
	
io_she_zhi:
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@a(0x48000000)b(0x48000400)c(0x48000800)d(0x48000c00)f(0x48001400)
	@ 输入（00），通用输出（01），复用功能（10），模拟（11）
	@偏移0x4 = 端口输出类型 @ （0 推挽），（ 1 开漏）
	@偏移0x8 = 输出速度  00低速， 01中速， 11高速
	@偏移0xC = 上拉下拉 00无上下拉，  01 上拉， 10下拉
	@偏移0x10 = 输入数据寄存器
	@偏移0x14 = 输出数据寄存器
	@偏移0x18 = 端口开  0-15置位 
	@偏移0x28 = 端口关
	@0X20 = 复用低
	@GPIO口0（0-3位）每个IO口占用4位
	@ AF0 = 0X0000, AF1 = 0X0001, AF2 = 0X0010 AF3 = 0X0011, AF4 = 0X0100
	@ AF5 = 0X0101, AF6 = 0X0111, AF7 = 0X1000
	@0x24 = 复用高
	@GPIO口8 （0-3位）每个IO口占用4位
	@ AF0 = 0X0000, AF1 = 0X0001, AF2 = 0X0010 AF3 = 0X0011, AF4 = 0X0100
	@ AF5 = 0X0101, AF6 = 0X0111, AF7 = 0X1000
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	ldr r0, = 0x48000000   @ 端口模式
	ldr r1, = 0x28005400  @ PA4
	str r1, [r0]
ledkaiguan:

	ldr r3, = 0xffffff
	movs r4, # 0x20
	str r4, [r0, # 0x18]
ledxunhuan:
	subs r3, r3, # 1
	bne ledxunhuan
	str r4, [r0, # 0x28]
	ldr r3, = 0xffffff
ledxunhuan1:
	subs r3, r3, # 1
	bne ledxunhuan1
	b ledkaiguan
	
	
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
	
