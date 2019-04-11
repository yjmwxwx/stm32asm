	 .thumb                 
         .syntax unified
.section .data
data1:
	.quad 0x3333333333333333
data2:	.float 3.1415926535
.section .text
tingzhu:
	ldr r0, = data1
	ldrd r1, r2, [r0]
	ldr r4, = data2
	b tingzhu
	


