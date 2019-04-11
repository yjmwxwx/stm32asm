	.data
nihao:
	.ascii      "你好\n"
	.text
	.globl _start
_start:
	mov x0, # 1
	ldr x1, = nihao
	ldr x2, [x1]
	mov x7, # 4

