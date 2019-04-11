	.equ STACKINIT, 	0x20005000
	.equ gpioddi,   	0x40011400
	.equ gpiododr,   	0x4001140C
	.equ RCC_APB2ENR,	0x40021018 @rccAPB2ENR
	.equ syskz,		0xE000E010 @ 控制寄存器
	.equ syscz,		0xE000E014 @systick定时器重载
	.equ syssz,		0xE000E018 @systick计数值查询
	.equ rcckz,		0x40021000 @rcc时钟控制寄存器
	.equ rccpz,		0x40021004 @时钟配置寄存器
	.equ flashacr,		0x40022000 @flash闪存访问寄存器
	.equ ledliang,		0x04
	.equ yanshishu,		200
	.equ lcdpianyi,	        240
	.equ lcdpy,		0x20000010
