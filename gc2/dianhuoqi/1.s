	 .thumb                 
         .syntax unified
.section .data
	.align 4
hongwaimabiao:	 .int 0xe240e240,0xe25ce25c,0xe2e8e2e8,0xe200e200,0xe210e210,0xe208e208,0xe218e218,0xe204e204,0xe214e214,0xe20ce20c,0xe21ce21c,0xe280e280,0xe290e290,0xe288e288,0xe298e298,0xe248e248,0xe250e250,0xe244e244,0xe2d8e2d8,0xe254e254,0xe24ce24c,0xe2d0e2d0,0xe2ece2ec,0xe2e4e2e4,0xe2cce2cc,0xe2c4e2c4,0xe2f4e2f4,0xe2f8e2f8,0xe2dce2dc,0xe2d4e2d4
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
	ldr r1, = 0x400
	movs r0, # 0
	ldr r2, = 0x20000000
neicunqingling:
	str r0, [r2]
	adds r2, # 0x04
	subs r1, # 1
	bne neicunqingling
quanjubianliang:
	ldr r0, = 0x200004fc
	ldr r1, = 0x20000500
	str r1, [r0]
	ldr r0, = 0x200007fc
	ldr r1, = 0x20000800
	str r1, [r0]
	ldr r0, = 0x200007f4
	movs r1, # 24
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
	ldr r1, = 0x1000
	str r1, [r0, # 0x20]
	movs r1, # 0x01
	str r1, [r0, # 0x14]
	ldr r1, = 0x201
	str r1, [r0]
tim14chushihua:
	        ldr r0, = 0x40002000
	        ldr r1, = 480
	        str r1, [r0, # 0x28]
	        ldr r1, = 0x70
	        str r1, [r0, # 0x18]
	        ldr r1, = 0x01
	        str r1, [r0, # 0x20]
	        movs r1, # 9
	        str r1, [r0]
io_she_zhi:
	@a(0x48000000)b(0x48000400)c(0x48000800)d(0x48000c00)f(0x48001400)
	ldr r0, = 0x48000000   @ 端口模式
	@ 输入（00）通用输出（01）复用功能（10）模拟（11）
	ldr r1, = 0x28000200  
	str r1, [r0]
	ldr r1, = 0x40000
	str r1, [r0, # 0x20]
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
	ldr r0, = 0x40002000
	ldr r1, = 0x48000000
	ldr r4, = 0x40000400
panduan:
	ldr r2, [r1, # 0x10]
	lsls r2, r2, # 22
	bpl panduan
	ldr r3, [r4, # 0x40]
	str r3, [r0, # 0x2c]
	lsrs r3, r3, # 2
	str r3, [r0, # 0x34]
	movs r3, # 9
	str r3, [r0]
	b panduan
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
	ldr r0, = 0x40000400
	ldr r1, [r0, # 0x40]
	mov r11, r1
	movs r1, # 0x01
	str r0, [r0, # 0x14]
	pop {r0-r6,pc}
