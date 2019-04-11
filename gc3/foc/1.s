	@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20000300	
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
	.word 0     @_systick +1               @ 15   
	.word 0     @ _wwdg +1          @ 0
	.word 0     @_pvd +1            @ 1
	.word 0     @_rtc +1            @ 2
	.word 0     @_flash +1          @ 3
	.word 0     @ _rcc + 1          @ 4
	.word 0      @_exti0_1  +1      @ 5
	.word 0      @ _exti2_3 +1      @ 6
	.word 0       @_exti4_15 +1     @ 7
	.word 0                         @ 8
	.word 0         @_dma1_1  +1    @ 9
	.word 0    @_dma1_2_3 +1        @ 10
	.word 0       @_dma1_4_5 +1     @ 11
	.word 0      @_adc1 +1          @ 12
	.word 0       @_tim1_brk_up +1  @ 13
	.word 0        @ _tim1_cc +1    @ 14
	.word 0         @_tim2 +1       @ 15
	.word 0          @_tim3 +1      @ 16
	.word 0                         @ 17
	.word 0		                @ 18
	.word 0    @_tim14 +1    @ 19
	.word 0                         @ 20
	.word 0         @_tim16 +1      @ 21
	.word 0         @_tim17 +1      @ 22
	.word 0          @_i2c   +1     @ 23
	.word 0                         @ 24
	.word 0           @_spi   +1    @ 25
	.word 0                         @ 26
	.word 0         @_usart1 +1     @ 27
	
_start:
	movs r1, # 2
	movs r2, # 1
	bl cordic
ting:
	b ting
cordic:
	.word 0x0fc8b430,0x10431840,0x18800fd0,0x29001040,0x2a00d50a,0x2180d504,0x424201c9,0xe0050018,0x00024941,0xe0014208,0x001a2100,0x28000013,0x2480d505,0x190901a4,0x18c31a12,0x4c3be003,0x18121909,0x0fd01ac3,0x10441880,0x18c00fd8,0x2b001045,0x4836d504,0x1b511808,0xe003191a,0x18084834,0x1b1a1951,0x0f9b104b,0x109b185b,0x0fa41054,0x10a418a4,0xd5042a00,0x19404d2e,0x18d21b09,0x4d2de003,0x19091940,0x108b1ad2,0x185b0e5b,0x109410db,0x18a40f64,0x2a0010e4,0x4d27d504,0x1b091940,0xe00318d2,0x19404d25,0x1ad21909,0x0f1b10cb,0x111b185b,0x0f2410d4,0x1124a418,0xd5042a00,0x19404d1f,0x18d21b0c,0x4d1ee003,0x190c1940,0x11211ad2,0x19090ec9,0x1111114b,0x18890ec9,0x2a00114d,0x21a3d505,0x18410049,0x18d21b60,0x4915e003,0x19601841,0x11431ad2,0x18180e9b,0x2a001180,0x31a3d502,0xe0011810,0x1a1039a3,0xd5012800,0xe0003151,0x42483951,0xbc30b200,0xc0004770,0xe000ffff,0x12e4ffff,0xed1c0000,0x09fbffff,0xf6050000,0x0511ffff,0xfaef0000,0x028bffff,0xfd750000,0xfebaffff,0xb4f0ffff
	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr

