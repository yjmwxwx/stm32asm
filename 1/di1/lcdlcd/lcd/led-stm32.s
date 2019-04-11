@@@
        .thumb                 
        .syntax unified

.section .data

yjm:	 .short 0x001f, 0xf81f, 0xffe0, 0x07ff, 0xf800
wxwx:	 .byte 0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00


        .equ STACKINIT, 	0x20005000
	.equ gpioddi,   	0x40011400
        .equ gpiododr,   	0x4001140C
        .equ RCC_APB2ENR,	0x40021018
	.equ syskz,		0xE000E010 @ 控制寄存器
	.equ syscz,		0xE000E014 @systick定时器重载
	.equ syssz,		0xE000E018 @systick计数值查询
	.equ rcckz,		0x40021000 @rcc时钟控制寄存器
	.equ rccpz,		0x40021004 @时钟配置寄存器
	.equ flashacr,		0x40022000 @flash闪存访问寄存器
	.equ lcdyanshi,		80000
	.equ lcdid,		0x20000100

	
.section .text

vectors_table:
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

	mov r5, # 0


shizhong:
	ldr r0, = rcckz
	ldr r1, = 0x14D83
	str r1, [r0]
gsszbz: @高速时钟标志位
	ldr r1, [r0]
	ldr r2, = 0x34D83
	cmp r2, r1 
	bne	gsszbz

	@FLASH缓冲 缓冲开启 
	ldr r0, = flashacr
	mov r1, # 0x00000032
	str r1, [r0]
	@设置
	ldr r0, = rccpz
	ldr r1, = 0x1D8400
	str r1, [r0]
	
	ldr r0, = rcckz
	ldr r1, = 0x1033D03
	str r1, [r0]
chaxun:
	ldr r1, [r0]
	ldr r2, = 0x03033D03
	cmp r1, r2
	bne chaxun

	ldr r0, = rccpz
	ldr r1, = 0x1D8402
	str r1, [r0]

	
	
systick:

	ldr r1, = syskz
	ldr r0, = syscz
	ldr r2, = syssz
	
	mov r3, #0
	str r3, [r1]

	ldr r3, = 0x2328
	str r3, [r0]
	str r3, [r2]

	mov r3, # 0x03
	str r3, [r1]


ledled:

        ldr r6, = RCC_APB2ENR
        mov r0, 0x39
        str r0, [r6]

        ldr r6, = gpioddi
        ldr r0, = 0x44444344
        str r0, [r6]

        mov r2, 0            
        mov r3, 0x04        
        ldr r6, = gpiododr 
lcdchushihua1:
	@@AFIO-MAPR 开SWD
	ldr r0, = 0x40010004
	ldr r1, = 0x02000000
	str r1, [r0]
	
	ldr r0, = 0x40011000
	ldr r1, = 0x33444444 
	str r1, [r0]

	ldr r0, = 0x40011004
	ldr r1, = 0x44444333
	str r1, [r0]

	ldr r0, = 0x4001100C
	ldr r1, = 0x7c0
	str r1, [r0]

	ldr r0, = 0x40010C00
	ldr r1, = 0x33333333
	str r1, [r0]

	ldr r0, = 0x40010C04
	ldr r1, = 0x33333333
	str r1, [r0]

	ldr r0, = 0x40010C0C
	ldr r1, = 0xffff
	str r1, [r0]

	mov r4, # 0x0000
	mov r7, # 0x0001
	bl lcdchushihua2
	bl yanshi


	mov r4, # 0x0015
	mov r7, # 0x0030
	bl lcdchushihua2

	mov r4, # 0x009a
	mov r7, # 0x0010
	bl lcdchushihua2

	mov r4, # 0x0011
	mov r7, # 0x0020
	bl lcdchushihua2

	mov r4, # 0x0010
	movw r7, # 0x3428
	bl lcdchushihua2

	mov r4, # 0x0012
	mov r7, # 0x0002
	bl lcdchushihua2

	mov r4, # 0x0013
	movw r7, # 0x1038
	bl lcdchushihua2

	bl yanshi

	@@@@

	

	mov r4, # 0x0012
	mov r7, # 0x0012
	bl lcdchushihua2

	bl yanshi

	mov r4, # 0x0010
	movw r7, # 0x3420
	bl lcdchushihua2

	mov r4, # 0x0013
	movw r7, # 0x3038
	bl lcdchushihua2

	bl yanshi

	mov r4, # 0x0030
	mov r7, # 0x0000
	bl lcdchushihua2

	mov r4, # 0x0031
	movw r7,# 0x0402
	bl lcdchushihua2

	mov r4, # 0x0032
	movw r7, # 0x0307
	bl lcdchushihua2

	@@@@@@

	mov r4, # 0x0033
	movw r7, # 0x0304
	bl lcdchushihua2

	mov r4, # 0x0034
	mov r7, # 0x0004
	bl lcdchushihua2

	mov r4, # 0x0035
	movw r7, # 0x0401
	bl lcdchushihua2



	mov r4, # 0x0036
	movw r7, # 0x0707
	bl lcdchushihua2

	mov r4, # 0x0037
	movw r7, #0x0305
	bl lcdchushihua2

	mov r4, # 0x0038
	movw r7, # 0x0610
	bl lcdchushihua2

	@@@@@

	mov r4, # 0x0039
	movw r7, # 0x0610
	bl lcdchushihua2

	mov r4, # 0x0001
	movw r7, # 0x0100
	bl lcdchushihua2

	mov r4, # 0x0002
	movw r7, # 0x0300
	bl lcdchushihua2

	mov r4, # 0x0003
	movw r7, #0x1030
	bl lcdchushihua2

	mov r4, # 0x0008
	movw r7, # 0x0808
	bl lcdchushihua2

	mov r4, # 0x000a
	mov r7, # 0x0008
	bl lcdchushihua2

	@@@@@

	mov r4, # 0x0060
	movw r7, #0x2700
	bl lcdchushihua2

	mov r4, # 0x0061
	mov r7, # 0x0001
	bl lcdchushihua2

	mov r4, # 0x0090
	movw r7, # 0x013e
	bl lcdchushihua2

	mov r4, # 0x0092
	movw r7, # 0x0100
	bl lcdchushihua2

	mov r4, # 0x0093
	movt r7, #0x0100
	bl lcdchushihua2

	mov r4, # 0x00a0
	movw r7, #0x3000
	bl lcdchushihua2

	@@@@@@

	mov r4, # 0x00a3
	mov r7, # 0x0010
	bl lcdchushihua2

	mov r4, # 0x0007
	mov r7, # 0x0001
	bl lcdchushihua2

	mov r4, # 0x0007
	mov r7, # 0x0021
	bl lcdchushihua2

	mov r4, # 0x0007
	mov r7, # 0x0023
	bl lcdchushihua2

	mov r4, # 0x0007
	mov r7, # 0x0033
	bl lcdchushihua2

	mov r4, # 0x0007
	movw r7, # 0x0133
	bl lcdchushihua2


	mov r9, # 0

	mov r8, # 0

	ldr r11, = wxwx

	mov r10, #0x1f
	mov r2, # 16
	mov r3, # 8
	mov r6, # 0x3c


		
main:


		
lcdyy:
	ldrb r6, [r11, r2]
	subs r2, 1 
	bne lcdxx
	mov r2, # 16
	ldr r11, = wxwx
	b main
lcdxx:
	subs r3, 1
	bne lcdyu
	mov r3, # 8
	b main
lcdyu:	

        tst r6, #0x01
	bne lcdxy
	b lcdxy1 
	


lcdxy:
	adds r8, r3
	adds r9, r2
	mov r10, # 0x1f
	ror r6, 1
	b lcdhuadian

lcdxy1:
	adds r8, r3
	adds r9, r2
	movw r10, # 0xf800
	ror r6, 1
	b lcdhuadian
	

	


lcdhuadian:
	bl yanshi
	mov r4, # 0x0020
	mov r7, r8
	bl lcdchushihua2
 	
	mov r4, # 0x0021
	mov r7, r9
	bl lcdchushihua2

	mov r4, # 0x0022
	mov r7, r10
	bl lcdchushihua2
	
	mov r9, # 0

	mov r8, # 0
	b lcdxx



lcdchushihua2:

	push {r4-r11, lr}
	ldr r0, = 0x4001100C
	mov r1, # 0x4c0
	str r1, [r0]
	
	ldr r0, = 0x40010C0C
	str r4, [r0]

	ldr r0, = 0x4001100C
	mov r1, # 0x440
	str r1, [r0]

	ldr r0, = 0x4001100C
	mov r1, # 0x7c0
	str r1, [r0]

	ldr r0, = 0x4001100C
	mov r1, # 0x5c0
	str r1, [r0]

	ldr r0, = 0x40010C0C
	str r7, [r0]

	ldr r0, = 0x4001100C
	mov r1, # 0x540
	str r1, [r0]

	ldr r0, = 0x4001100C
	mov r1, # 0x7c0
	str r1, [r0]
	pop {r4-r11, pc}
			
	

yanshi:	
	cmp r5, #500
	bne yanshi
	mov r5, #0
	bx lr

	
		


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
	adds r5, 1	
	bx lr
         

