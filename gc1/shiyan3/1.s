	 .thumb                 
         .syntax unified
.section .data
	.align 4
GPIO_int:  @ 入口R0=哪个IO
	   @R1=CLR IO模式设置
	   @R2= CLH IO模式设置
	   @R3低16位决定哪一位，高16位最高一位决定开和关
	push (r0-r6,lr)
	str r1, [r0]
	str r2, [r0, # 0x04]
	movs r3, r3
	ite pl
	strhpl r3, [r0, # 0x10]
	strhpl r3, [r0, # 0x14]
	pop (r0-r6,pc)
