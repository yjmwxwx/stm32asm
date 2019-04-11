	 .thumb                 
         .syntax unified
.section .data
	.align 4
hongwaimabiao:	 .int 0x2f472f47,0x1f471f47,0x3b473b47,0x2b472b47,0x37473747,0x27472747,0x33473347,0x23472347,0x2a472a47,0x32473247,0x0b470b47,0x22472247,0x1b471b47,0x12471247,0x0a470a47,0x01470147,0x09470947,0x11471147,0x19471947,0x20472047,0x28472847,0x30473047,0x38473847,0x00470047,0x08470847,0x10471047,0x18471847,0x3a473a47,0x17471747,0x02470247
        	.equ zhanding,          0x20000300
	.section .text
zhongduanxiangliangbiao:
	.word zhanding +1
	.word fuwei +1
	.word nmi +1
	.word hardf +1
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word svc +1
	.word 0
	.word 0
	.word pendsv +1
	.word systick +1
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
	.word tim3 +1
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
fuwei:	
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
	ldr r0, = 0x40021004
	ldr r1, = 0x11000a      @ PLL作为系统时钟
	str r1, [r0]
quanjubianliang:
	ldr r0, = 0x200004fc
	ldr r1, = 0
	str r1, [r0]
	ldr r0, = 0x200004f8
	movs r1, # 0
	str r1, [r0]
	ldr r0, = 0x20000500
	str r1, [r0]
	ldr r0, = 0x20000504
	str r1, [r0]
	
shi_zhong_she_zhi:
	ldr r0, = 0x40021014    @ AHB外部时钟
	ldr r1, = 0x60014       @ 开时钟
	str r1, [r0]
	@ DMA（0）SRAM（2）FLITF（4）CRC（6）PA（17）
	@PB（18）PC（19）PD（20）PF（22）TSCEN（24）
	ldr r0, = 0x4002101c
	ldr r1, = 0x132
	str r1, [r0]
zhongduanshezhi:
	ldr r0, = 0xe000e100
	ldr r1, = 0x10000
	str r1, [r0]
tim3chushihua:
	ldr r0, = 0x40000400
	ldr r1, = 0x10
	str r1, [r0, # 0x0c]     
	ldr r1, = 480
	str r1, [r0, # 0x28]
	ldr r1, = 0xffff
	str r1, [r0, # 0x2c]
	ldr r1, = 0xf100
	str r1, [r0, # 0x1c]
	ldr r1, = 0x3000
	str r1, [r0, # 0x20]
	movs r1, # 0x01
	str r1, [r0, # 0x14]
	ldr r1, = 0x201
	str r1, [r0]
	
io_she_zhi:
	@a(0x48000000)b(0x48000400)c(0x48000800)d(0x48000c00)f(0x48001400)
	ldr r0, = 0x48000000   @ 端口模式
	@ 输入（00）通用输出（01）复用功能（10）模拟（11）
	ldr r1, = 0x28000200  @ PA4
	str r1, [r0]
	@偏移0x4 = 端口输出类型 @ （0 推挽）（ 1 开漏）
	@偏移0x8 = 输出速度  00低速 01中速 11高速
	@偏移0xC = 上拉下拉 00无上下拉  01 上拉 10下拉
	@偏移0x10 = 输入数据寄存器
	@偏移0x14 = 输出数据寄存器
	@偏移0x18 = 端口开  0-15置位 
	@偏移0x28 = 端口关
	@0X20 = 复用低
	@0x24 = 复用高
	ldr r0, = 0x48000400
	movs r1, # 0x08
	str r1, [r0]
	movs r1, # 0x10
	str r1, [r0, # 0x20]
tingzhu:
	b tingzhu
anjian:
	push {r0-r7,lr}
	ldr r7, = 0x200004f8
	ldr r3, = 0x20000500
	ldr r5, = hongwaimabiao
	movs r6, # 30        @ 按键数量
panduananjian:
	ldr r4, [r5]
	adds r5, r5, # 4
	ldr r2, [r3]          @ 取出解码后的码
	cmp r2, r4           @ 比较两个码
	beq anjianfanhui
	subs r6, r6, # 1
	bne panduananjian
	pop {r0-r7,pc}
anjianfanhui:
	str r6, [r7]
	movs r1, # 0
	str r1, [r3]
	pop {r0-r7,pc}
	
nmi:
	bx lr
hardf:
	bx lr
svc:
	bx lr
pendsv:
	bx lr
systick:
	bx lr
tim3:
	push {r0-r6,lr}
	ldr r2, = 0x40000400
	ldr r3, [r2, # 0x40]
	cmp r3, # 0xd0
	bhi tim3fanhui
	cmp r3, # 0x60
	bls tim3fanhui
	cmp r3, # 0xa0
	bcs dengyu1
	movs r3, # 0
	b tim3chucun
dengyu1:
	movs r3, # 1
tim3chucun:
	ldr r0, = 0x20000500
	ldr r1, [r0]
	strb r3, [r0]
	movs r4, # 1
	rors r1, r4
	str r1, [r0]
tim3fanhui:
	movs r1, # 0x01
	str r1, [r2, # 0x14]
	pop {r0-r6,pc}
	
