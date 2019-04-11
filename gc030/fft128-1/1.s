	@ stm32f030f4p6 asm
	@fft 128点
	@2018-01-05
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000
	.equ xuanzhuanyinzi,		0x20000404
	.align 4
shuru:
	.int 0,4539,-1374,3185,-5935,1471,2148,1201,3899,-5842,2413,-498,3925,3547,-4170,2482,-2634,6066,2481,-1268,1639,-3687,6998,1237,2166,172,-3437,6391,343,5275,-1388,-2063,4328,137,7282,-2446,-67,1298,658,7704,-2537,1890,-1933,1635,6484,-1493,3207,-4536,2591,3991,477,3517,-5847,3008,906,2841,2796,-5562,2521,-1981,4878,1351,-3818,1059,-3999,5901,-294,-1155,-1107,-4777,5468,-1583,1648,-3430,-4326,3532,-2114,3796,-5243,-3012,470,-1770,4706,-5970,-1409,-3003,-761,4167,-5308,-108,-6030,454,2389,-3347,478,-7847,1328,-70,-555,241,-7998,1414,-2490,2336,-605,-6463,534,-4194,4544,-1611,-3655,-1145,-4756,5457,-2255,-305,-3141,-4107,4818,-2136,2751,-4798,-2540,2808,-1120,4811,-5487,-596
	
hudieweifanzhuan:
	.int 0,256,128,384,64,320,192,448,32,288,160,416,96,352,224,480,16,272,144,400,80,336,208,464,48,304,176,432,112,368,240,496,8,264,136,392,72,328,200,456,40,296,168,424,104,360,232,488,24,280,152,408,88,344,216,472,56,312,184,440,120,376,248,504,4,260,132,388,68,324,196,452,36,292,164,420,100,356,228,484,20,276,148,404,84,340,212,468,52,308,180,436,116,372,244,500,12,268,140,396,76,332,204,460,44,300,172,428,108,364,236,492,28,284,156,412,92,348,220,476,60,316,188,444,124,380,252,508
fft3xuanzhuanyinzi:
	.int 0x8000,0x0000,0x5A82,0xFFFFA57E,0x0000,0xFFFF8000,0xFFFFA57E,0xFFFFA57E
fft4xuanzhuanyinzi:
	.int 0x8000,0x0000,0x7641,0xFFFFCF05,0x5A82,0xFFFFA57E,0x30FB,0xFFFF89BF,0x0000,0xFFFF8000,0xFFFFCF05,0xFFFF89BF,0xFFFFA57E,0xFFFFA57E,0xFFFF89BF,0xFFFFCF05
fft5xuanzhuanyinzi:
	.int 0x8000,0x0000,0x7D8A,0xFFFFE708,0x7641,0xFFFFCF05,0x6A6D,0xFFFFB8E4,0x5A82,0xFFFFA57E,0x471C,0xFFFF9593,0x30FB,0xFFFF89BF,0x18F8,0xFFFF8276,0x0000,0xFFFF8000,0xFFFFE708,0xFFFF8276,0xFFFFCF05,0xFFFF89BF,0xFFFFB8E4,0xFFFF9593,0xFFFFA57E,0xFFFFA57E,0xFFFF9593,0xFFFFB8E4,0xFFFF89BF,0xFFFFCF05,0xFFFF8276,0xFFFFE708
fft6xuanzhuanyinzi:
	.int 0x8000,0x0000,0x7F62,0xFFFFF375,0x7D8A,0xFFFFE708,0x7A7D,0xFFFFDAD8,0x7641,0xFFFFCF05,0x70E2,0xFFFFC3AA,0x6A6D,0xFFFFB8E4,0x62F2,0xFFFFAECD,0x5A82,0xFFFFA57E,0x5133,0xFFFF9D0E,0x471C,0xFFFF9593,0x3C56,0xFFFF8F1E,0x30FB,0xFFFF89BF,0x2528,0xFFFF8583,0x18F8,0xFFFF8276,0x0C8B,0xFFFF809E,0x0000,0xFFFF8000,0xFFFFF375,0xFFFF809E,0xFFFFE708,0xFFFF8276,0xFFFFDAD8,0xFFFF8583,0xFFFFCF05,0xFFFF89BF,0xFFFFC3AA,0xFFFF8F1E,0xFFFFB8E4,0xFFFF9593,0xFFFFAECD,0xFFFF9D0E,0xFFFFA57E,0xFFFFA57E,0xFFFF9D0E,0xFFFFAECD,0xFFFF9593,0xFFFFB8E4,0xFFFF8F1E,0xFFFFC3AA,0xFFFF89BF,0xFFFFCF05,0xFFFF8583,0xFFFFDAD8,0xFFFF8276,0xFFFFE708,0xFFFF809E,0xFFFFF375
fft7xuanzhuanyinzi:
	.int 0x8000,0x0000,0x7FD8,0xFFFFF9B9,0x7F62,0xFFFFF375,0x7E9D,0xFFFFED38,0x7D8A,0xFFFFE708,0x7C29,0xFFFFE0E7,0x7A7D,0xFFFFDAD8,0x7884,0xFFFFD4E1,0x7641,0xFFFFCF05,0x73B5,0xFFFFC946,0x70E2,0xFFFFC3AA,0x6DCA,0xFFFFBE32,0x6A6D,0xFFFFB8E4,0x66CF,0xFFFFB3C1,0x62F2,0xFFFFAECD,0x5ED7,0xFFFFAA0B,0x5A82,0xFFFFA57E,0x55F5,0xFFFFA129,0x5133,0xFFFF9D0E,0x4C3F,0xFFFF9931,0x471C,0xFFFF9593,0x41CE,0xFFFF9236,0x3C56,0xFFFF8F1E,0x36BA,0xFFFF8C4B,0x30FB,0xFFFF89BF,0x2B1F,0xFFFF877C,0x2528,0xFFFF8583,0x1F19,0xFFFF83D7,0x18F8,0xFFFF8276,0x12C8,0xFFFF8163,0x0C8B,0xFFFF809E,0x0647,0xFFFF8028,0x0000,0xFFFF8000,0xFFFFF9B9,0xFFFF8028,0xFFFFF375,0xFFFF809E,0xFFFFED38,0xFFFF8163,0xFFFFE708,0xFFFF8276,0xFFFFE0E7,0xFFFF83D7,0xFFFFDAD8,0xFFFF8583,0xFFFFD4E1,0xFFFF877C,0xFFFFCF05,0xFFFF89BF,0xFFFFC946,0xFFFF8C4B,0xFFFFC3AA,0xFFFF8F1E,0xFFFFBE32,0xFFFF9236,0xFFFFB8E4,0xFFFF9593,0xFFFFB3C1,0xFFFF9931,0xFFFFAECD,0xFFFF9D0E,0xFFFFAA0B,0xFFFFA129,0xFFFFA57E,0xFFFFA57E,0xFFFFA129,0xFFFFAA0B,0xFFFF9D0E,0xFFFFAECD,0xFFFF9931,0xFFFFB3C1,0xFFFF9593,0xFFFFB8E4,0xFFFF9236,0xFFFFBE32,0xFFFF8F1E,0xFFFFC3AA,0xFFFF8C4B,0xFFFFC946,0xFFFF89BF,0xFFFFCF05,0xFFFF877C,0xFFFFD4E1,0xFFFF8583,0xFFFFDAD8,0xFFFF83D7,0xFFFFE0E7,0xFFFF8276,0xFFFFE708,0xFFFF8163,0xFFFFED38,0xFFFF809E,0xFFFFF375,0xFFFF8028,0xFFFFF9B9
	           
	           
	
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
	.align 2
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
	movs r2, # 64
	ldr r3, = hudieweifanzhuan
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
	movs r4, # 1
	lsls r4, r4, # 9
	adds r4, r4, r0
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
	movs r7, # 1
	lsls r7, r7, # 9
	adds r7, r7, r0
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
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft3xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, # 1
	lsls r1, r1, # 9
	adds r1, r1, r0
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x10
	mov r11, r5
	movs r5, # 4
	mov r12, r5
	bl _fftg
_fft4:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft4xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, # 1
	lsls r1, r1, # 9
	adds r1, r1, r0
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x20
	mov r11, r5
	movs r5, # 8
	mov r12, r5
	bl _fftg
_fft5:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft5xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, # 1
	lsls r1, r1, # 9
	adds r1, r1, r0
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x40
	mov r11, r5
	movs r5, # 16
	mov r12, r5
	bl _fftg

_fft6:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft6xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, # 1
	lsls r1, r1, # 9
	adds r1, r1, r0
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 0x80
	mov r11, r5
	movs r5, # 32
	mov r12, r5
	bl _fftg
	
_fft7:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft7xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, # 1
	lsls r1, r1, # 9
	adds r1, r1, r0
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 1
	lsls r5, r5, # 8
	mov r11, r5
	movs r5, # 64
	mov r12, r5
	bl _fftg
	
tingting:
	b tingting
_fftg:
	push {lr}
	movs r4, # 0
	mov lr, r4
_fftxunhuan:
	mov r0, r9
	mov r1, r8
	mov r2, r10
	mov r3, r11
	ldr r4, [r0]
	ldr r5, [r1]
	ldr r6, [r0, r3]
	ldr r7, [r1, r3]
	ldr r3, [r2]		@sr
	ldr r2, [r2, # 0x04]	@si
	push {r4,r5}
	mov r4, r6
	muls r4, r4, r3
	mov r5, r7
	muls r5, r5, r2
	subs r4, r4, r5		@r
	asrs r4, r4, # 15
	mov r5, r6
	muls r5, r5, r2
	muls r7, r7, r3
	adds r7, r7, r5    @i
	asrs r7, r7, # 15
	pop {r2,r5}
	adds r3, r2, r4    @0r
	subs r2, r2, r4    @1r
	adds r4, r5, r7
	subs r5, r5, r7
	mov r6, r11
	str r3, [r0]
	str r4, [r1]
	str r2, [r0, r6]
	str r5, [r1, r6]
	adds r0, r0, # 0x04
	adds r1, r1, # 0x04
	mov r9, r0
	mov r8, r1
	mov r2, r10
	adds r2, r2, # 0x08
	mov r10, r2
	mov r4, lr
	adds r4, r4, # 1
	mov lr, r4
	mov r7, r12
	cmp r4, r7
	bne _fftxunhuan
	movs  r4, # 0
	ldr r6, = xuanzhuanyinzi
	ldr r5, = 0x20000200
	ldr r6, [r6]
	mov r10, r6
	mov lr, r4
	mov r7, r11
	adds r0, r0, r7
	adds r1, r1, r7
	mov r9, r0
	mov r8, r1
	cmp r0, r5
	bne _fftxunhuan
	pop {pc}
		
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
