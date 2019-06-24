	@@单片机stm32f030f4p6
	@@  256点radix-2  fft
	@@ 结果左移6位或者乘64
	@作者：yjmwxwx
	@时间：2019-06-23
	@编译器：arm-none-eabi
	 .thumb                 
         .syntax unified
.section .data
shumaguanmabiao:
	.int 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6
shumaguanshuaxinbiao:
	.int 0xfe00,0xfd00,0xfb00,0xf700,0xef00,0xdf00,0xbf00,0x7f00,0
       	.equ STACKINIT,                 0x20001000
	.equ shumaguanma,	0x20000808
	.equ xuanzhuanyinzi,	0x20000800
	.equ dianyabiao,	0x20000850
	.equ lvbozhizhen,	0x20000c50
	.equ lvbohuanchong,	0x20000c54
dianyabiao11:
	.int 0x089,0x039,0x18C,0x63D,0xB84,0xECF,0xFBD,0xFBF,0xE3D,0x8F7,0x3EF,0x0E1,0x039,0x074,0x366,0x8E8,0xD91,0xF7F,0xFEC,0xF47,0xBC9,0x631,0x1D8,0x05C,0x056,0x187,0x6A1,0xB98,0xEF4,0xFC4,0xFAF,0xDF1,0x8AB,0x3AC,0x0D0,0x06F,0x0DE,0x40F,0x93C,0xDD7,0xF8D,0xFB0,0xEAB,0xB04, 0x5C3,0x187,0x05E,0x0D5, 0x246,0x767,0xBFF,0xF11, 0xFE1,0xEF4,0xD07,0x7C7, 0x330,0x0B5,0x06A,0x1CB, 0x4BF,0xA00,0xE21,0xF9C, 0xFC0,0xDCD,0xA30,0x4F7,0x15C,0x063,0x0BC,0x316, 0x823,0xC9C,0xF45,0xFCF, 0xEF0,0xC25,0x6EE,0x2D3, 0x09A,0x068,0x1FF,0x596,0xAC7,0xE5F,0xFB8,0xFAD, 0xD96,0x957,0x437,0x148, 0x040,0x097,0x401,0x8F7, 0xD18,0xF3F,0xFDD,0xF40, 0xB5F,0x61F,0x26F,0x084, 0x05B,0x1B7,0x670,0xB6F, 0xE94,0xFC6,0xFAF,0xDD5, 0x8A5,0x3BC,0x127,0x034, 0x092,0x3EF,0x994,0xD57, 0xF4F,0xFF0,0xF3F,0xB74, 0x59F,0x217,0x07E,0x045, 0x176,0x697,0xBAF,0xEB1, 0xFBF,0xFBD,0xE44,0x8CF, 0x3B0,0x0F7,0x032,0x090, 0x365,0x910,0xD7F,0xF84,0xFD7,0xF47,0xBD1,0x629,0x1DC,0x07A,0x03F,0x166, 0x663,0xB5C,0xED7,0xFCD,0xFD1,0xE3F,0x8DC,0x3DF,0x0CD,0x05A,0x0A5,0x3A4,0x907,0xDA5,0xF90,0xFBF, 0xF1C,0xB67,0x5ED,0x1B0, 0x065,0x098,0x1FB,0x6EF,0xBD0,0xF0B,0xFDC,0xF27, 0xD67,0x831,0x379,0x0B5, 0x083,0x14F,0x470,0x99B, 0xDF4,0xF97,0xF8F,0xE31, 0xAA3,0x554,0x17F,0x047,0x0D6,0x2B1,0x7B4,0xC47, 0xF2B,0xFE1,0xEF2,0xC9D, 0x757,0x2F9,0x0B0,0x075, 0x1FC,0x517,0xA4F,0xE31,0xFB2,0xFAC,0xD84,0x9CF, 0x495,0x159,0x03F,0x0BB,0x36F,0x890,0xCE3,0xF3C, 0xFD7,0xF07,0xBD0,0x699, 0x294,0x096,0x057,0x1F1, 0x608,0xB0C,0xE5F,0xFAF,0xFB5,0xDBA,0x8EC,0x3F6,0x11F,0x042,0x0A5,0x40C,0x957,0xD2F,0xF51,0xFEB,0xF34,0xB54,0x5AF,0x250,0x087,0x047,0x1B1,0x697 
hudieweifanzhuan:
	.int 0x0000,0x0200,0x0100,0x0300,0x0080,0x0280,0x0180,0x0380,0x0040,0x0240,0x0140,0x0340,0x00C0,0x02C0,0x01C0,0x03C0,0x0020,0x0220,0x0120,0x0320,0x00A0,0x02A0,0x01A0,0x03A0,0x0060,0x0260,0x0160,0x0360,0x00E0,0x02E0,0x01E0,0x03E0,0x0010,0x0210,0x0110,0x0310,0x0090,0x0290,0x0190,0x0390,0x0050,0x0250,0x0150,0x0350,0x00D0,0x02D0,0x01D0,0x03D0,0x0030,0x0230,0x0130,0x0330,0x00B0,0x02B0,0x01B0,0x03B0,0x0070,0x0270,0x0170,0x0370,0x00F0,0x02F0,0x01F0,0x03F0,0x0008,0x0208,0x0108,0x0308,0x0088,0x0288,0x0188,0x0388,0x0048,0x0248,0x0148,0x0348,0x00C8,0x02C8,0x01C8,0x03C8,0x0028,0x0228,0x0128,0x0328,0x00A8,0x02A8,0x01A8,0x03A8,0x0068,0x0268,0x0168,0x0368,0x00E8,0x02E8,0x01E8,0x03E8,0x0018,0x0218,0x0118,0x0318,0x0098,0x0298,0x0198,0x0398,0x0058,0x0258,0x0158,0x0358,0x00D8,0x02D8,0x01D8,0x03D8,0x0038,0x0238,0x0138,0x0338,0x00B8,0x02B8,0x01B8,0x03B8,0x0078,0x0278,0x0178,0x0378,0x00F8,0x02F8,0x01F8,0x03F8,0x0004,0x0204,0x0104,0x0304,0x0084,0x0284,0x0184,0x0384,0x0044,0x0244,0x0144,0x0344,0x00C4,0x02C4,0x01C4,0x03C4,0x0024,0x0224,0x0124,0x0324,0x00A4,0x02A4,0x01A4,0x03A4,0x0064,0x0264,0x0164,0x0364,0x00E4,0x02E4,0x01E4,0x03E4,0x0014,0x0214,0x0114,0x0314,0x0094,0x0294,0x0194,0x0394,0x0054,0x0254,0x0154,0x0354,0x00D4,0x02D4,0x01D4,0x03D4,0x0034,0x0234,0x0134,0x0334,0x00B4,0x02B4,0x01B4,0x03B4,0x0074,0x0274,0x0174,0x0374,0x00F4,0x02F4,0x01F4,0x03F4,0x000C,0x020C,0x010C,0x030C,0x008C,0x028C,0x018C,0x038C,0x004C,0x024C,0x014C,0x034C,0x00CC,0x02CC,0x01CC,0x03CC,0x002C,0x022C,0x012C,0x032C,0x00AC,0x02AC,0x01AC,0x03AC,0x006C,0x026C,0x016C,0x036C,0x00EC,0x02EC,0x01EC,0x03EC,0x001C,0x021C,0x011C,0x031C,0x009C,0x029C,0x019C,0x039C,0x005C,0x025C,0x015C,0x035C,0x00DC,0x02DC,0x01DC,0x03DC,0x003C,0x023C,0x013C,0x033C,0x00BC,0x02BC,0x01BC,0x03BC,0x007C,0x027C,0x017C,0x037C,0x00FC,0x02FC,0x01FC,0x03FC

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

fft8xuanzhuanyinzi:
	.int 0x8000,0x0000,0x7FF6,0xFFFFFCDC,0x7FD8,0xFFFFF9B9,0x7FA7,0xFFFFF696,0x7F62,0xFFFFF375,0x7F09,0xFFFFF055,0x7E9D,0xFFFFED38,0x7E1D,0xFFFFEA1E,0x7D8A,0xFFFFE708,0x7CE3,0xFFFFE3F5,0x7C29,0xFFFFE0E7,0x7B5D,0xFFFFDDDD,0x7A7D,0xFFFFDAD8,0x798A,0xFFFFD7DA,0x7884,0xFFFFD4E1,0x776C,0xFFFFD1EF,0x7641,0xFFFFCF05,0x7504,0xFFFFCC22,0x73B5,0xFFFFC946,0x7255,0xFFFFC674,0x70E2,0xFFFFC3AA,0x6F5F,0xFFFFC0E9,0x6DCA,0xFFFFBE32,0x6C24,0xFFFFBB86,0x6A6D,0xFFFFB8E4,0x68A6,0xFFFFB64C,0x66CF,0xFFFFB3C1,0x64E8,0xFFFFB141,0x62F2,0xFFFFAECD,0x60EC,0xFFFFAC65,0x5ED7,0xFFFFAA0B,0x5CB4,0xFFFFA7BE,0x5A82,0xFFFFA57E,0x5842,0xFFFFA34C,0x55F5,0xFFFFA129,0x539B,0xFFFF9F14,0x5133,0xFFFF9D0E,0x4EBF,0xFFFF9B18,0x4C3F,0xFFFF9931,0x49B4,0xFFFF975A,0x471C,0xFFFF9593,0x447A,0xFFFF93DC,0x41CE,0xFFFF9236,0x3F17,0xFFFF90A1,0x3C56,0xFFFF8F1E,0x398C,0xFFFF8DAB,0x36BA,0xFFFF8C4B,0x33DE,0xFFFF8AFC,0x30FB,0xFFFF89BF,0x2E11,0xFFFF8894,0x2B1F,0xFFFF877C,0x2826,0xFFFF8676,0x2528,0xFFFF8583,0x2223,0xFFFF84A3,0x1F19,0xFFFF83D7,0x1C0B,0xFFFF831D,0x18F8,0xFFFF8276,0x15E2,0xFFFF81E3,0x12C8,0xFFFF8163,0x0FAB,0xFFFF80F7,0x0C8B,0xFFFF809E,0x096A,0xFFFF8059,0x0647,0xFFFF8028,0x0324,0xFFFF800A,0x0000,0xFFFF8000,0xFFFFFCDC,0xFFFF800A,0xFFFFF9B9,0xFFFF8028,0xFFFFF696,0xFFFF8059,0xFFFFF375,0xFFFF809E,0xFFFFF055,0xFFFF80F7,0xFFFFED38,0xFFFF8163,0xFFFFEA1E,0xFFFF81E3,0xFFFFE708,0xFFFF8276,0xFFFFE3F5,0xFFFF831D,0xFFFFE0E7,0xFFFF83D7,0xFFFFDDDD,0xFFFF84A3,0xFFFFDAD8,0xFFFF8583,0xFFFFD7DA,0xFFFF8676,0xFFFFD4E1,0xFFFF877C,0xFFFFD1EF,0xFFFF8894,0xFFFFCF05,0xFFFF89BF,0xFFFFCC22,0xFFFF8AFC,0xFFFFC946,0xFFFF8C4B,0xFFFFC674,0xFFFF8DAB,0xFFFFC3AA,0xFFFF8F1E,0xFFFFC0E9,0xFFFF90A1,0xFFFFBE32,0xFFFF9236,0xFFFFBB86,0xFFFF93DC,0xFFFFB8E4,0xFFFF9593,0xFFFFB64C,0xFFFF975A,0xFFFFB3C1,0xFFFF9931,0xFFFFB141,0xFFFF9B18,0xFFFFAECD,0xFFFF9D0E,0xFFFFAC65,0xFFFF9F14,0xFFFFAA0B,0xFFFFA129,0xFFFFA7BE,0xFFFFA34C,0xFFFFA57E,0xFFFFA57E,0xFFFFA34C,0xFFFFA7BE,0xFFFFA129,0xFFFFAA0B,0xFFFF9F14,0xFFFFAC65,0xFFFF9D0E,0xFFFFAECD,0xFFFF9B18,0xFFFFB141,0xFFFF9931,0xFFFFB3C1,0xFFFF975A,0xFFFFB64C,0xFFFF9593,0xFFFFB8E4,0xFFFF93DC,0xFFFFBB86,0xFFFF9236,0xFFFFBE32,0xFFFF90A1,0xFFFFC0E9,0xFFFF8F1E,0xFFFFC3AA,0xFFFF8DAB,0xFFFFC674,0xFFFF8C4B,0xFFFFC946,0xFFFF8AFC,0xFFFFCC22,0xFFFF89BF,0xFFFFCF05,0xFFFF8894,0xFFFFD1EF,0xFFFF877C,0xFFFFD4E1,0xFFFF8676,0xFFFFD7DA,0xFFFF8583,0xFFFFDAD8,0xFFFF84A3,0xFFFFDDDD,0xFFFF83D7,0xFFFFE0E7,0xFFFF831D,0xFFFFE3F5,0xFFFF8276,0xFFFFE708,0xFFFF81E3,0xFFFFEA1E,0xFFFF8163,0xFFFFED38,0xFFFF80F7,0xFFFFF055,0xFFFF809E,0xFFFFF375,0xFFFF8059,0xFFFFF696,0xFFFF8028,0xFFFFF9B9,0xFFFF800A,0xFFFFFCDC
	
	

	
		
	
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
	.word _systickzhongduan +1               @ 15
	.word aaa +1     @ _wwdg +1          @ 0
	.word aaa +1     @_pvd +1            @ 1
	.word aaa +1     @_rtc +1            @ 2
	.word aaa +1     @_flash +1          @ 3
	.word aaa +1	@ _rcc + 1          @ 4
	.word aaa +1      @_exti0_1  +1      @ 5
	.word aaa +1      @ _exti2_3 +1      @ 6
	.word aaa +1       @_exti4_15 +1     @ 7
	.word aaa +1                         @ 8
	.word aaa +1 	@_dma1_1  +1    @ 9
	.word aaa +1    @_dma1_2_3 +1        @ 10
	.word aaa +1       @_dma1_4_5 +1     @ 11
	.word aaa +1	 @_adc1 +1          @ 12
	.word aaa +1       @_tim1_brk_up +1  @ 13
	.word aaa +1        @ _tim1_cc +1    @ 14
	.word aaa +1         @_tim2 +1       @ 15
	.word aaa +1          @_tim3 +1      @ 16
	.word aaa +1                         @ 17
	.word aaa +1		                @ 18
	.word aaa +1	@_tim14 +1    @ 19
	.word aaa +1                         @ 20
	.word aaa +1         @_tim16 +1      @ 21
	.word aaa +1         @_tim17 +1      @ 22
	.word aaa +1          @_i2c   +1     @ 23
	.word aaa +1                         @ 24
	.word aaa +1           @_spi   +1    @ 25
	.word aaa +1                         @ 26
	.word aaa +1         @_usart1 +1     @ 27
_start:
shizhong:
	ldr r2, = 0x40022000   @FLASH访问控制
	movs r1, # 0x32
	str r1, [r2]           @FLASH缓冲 缓冲开启
        ldr r0, = 0x40021000 @ rcc
        ldr r1, = 0x10001
        str r1, [r0]
denghse:
        ldr r1, [r0]
        lsls r1, r1, # 14
        bpl denghse
dengpllguan:
        ldr r1, [r0]
        lsls r1, r1, # 6
        bmi dengpllguan
        ldr r1, = 0x110002
        str r1, [r0, # 0x04]
        ldr r1, = 0x1010000
	movs r0, r0
        str r1, [r0]
	
dengpll:
	ldr r1, [r0]
	lsls r1, # 6
	bpl dengpll
	@0x34时钟控制寄存器 2 (RCC_CR2)
	movs r1, # 0x01
	str r1, [r0, # 0x34]  @ HSI开14M时钟
dengdai14mshizhongwending:
	ldr r1, [r0, # 0x34]
	lsls r1, r1, # 30     @ 左移30位
	bpl dengdai14mshizhongwending  @ 等待14M时钟稳定

neicunqingling:
	ldr r0, = 0x20000000
	movs r1, # 0
	ldr r3, = 0x1000
neicunqinglingxunhuan:
	subs r3, # 4
	str r1, [r0, r3]
	bne neicunqinglingxunhuan

@_systick:				@ systick定时器初始化
@
@	ldr r0, = 0xe000e010
@	ldr r1, = 0xffff
@	str r1, [r0, # 4]
@	str r1, [r0, # 8]
@	movs r1, # 0x07
@	str r1, [r0]
_waisheshizhong:		 @ 外设时钟
	@+0x14=RCC_AHBENR
	@0=DMA @2=SRAM @4=FLITF@6=CRC @17=PA @18=PB @19=PC @20=PD @22=PF
	ldr r0, = 0x40021000
	ldr r1, = 0x460005
	str r1, [r0, # 0x14]

	@+0x18外设时钟使能寄存器 (RCC_APB2ENR)
	@0=SYSCFG @5=USART6EN @9=ADC @11=TIM1 @12=SPI1 @14=USART1 @16=TIM15 @17=TIM16 @18=TIM17 @22=DBGMCU
	ldr r1, = 0xa00
	str r1, [r0, # 0x18]
	@+0X1C=RCC_APB1ENR
	@ 1=TIM3 @ 4=TIM6 @5=TIM7 @8=TIM14 @11=WWDG @14=SPI @17=USRT2 @18=USART3 @20=USART5 @21=I2C1 @22=I2C2 @23=USB @28=PWR
@	movs r1, # 0x02
@	str r1, [r0, # 0x1c]
io_she_zhi:
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@a(0x48000000)b(0x48000400)c(0x48000800)d(0x48000c00)f(0x48001400)
	@ 输入（00），通用输出（01），复用功能（10），模拟（11）
	@偏移0x4 = 端口输出类型 @ （0 推挽），（ 1 开漏）
	@偏移0x8 = 输出速度  00低速， 01中速， 11高速
	@偏移0xC = 上拉下拉 (00无上下拉，  01 上拉， 10下拉)
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

	ldr r0, = 0x48000000
	ldr r1, = 0x28005403
	str r1, [r0]

	ldr r1, = 0x200
	str r1, [r0, # 0x24]
@tim3chushihua:				@ 24M
@	ldr r0, = 0x40000400 @ tim3_cr1
@	ldr r1, =  0
@	str r1, [r0, # 0x28] @ psc
@	ldr r1, = 9
@	str r1, [r0, # 0x2c] @ ARR
@	ldr r1, =   0x3800
@	str r1, [r0, # 0x1c] @ ccmr2
@	ldr r1, = 9999
@	str r1, [r0, # 0x20] @ ccer
@	ldr r1, = 10
@	str r1, [r0, # 0x40] @ ccr4
@	movs r1, # 0x70
@	str r1, [r0, # 0x04]
@	movs r1, # 0x81
@	str r1, [r0]
dmachushihua:
	@+0=LSR,+4=IFCR,
	@+8=CCR1,+c=CNDTR1,+10=CPAR1+14=CMAR1,
	@+1c=CCR2,+20=CNDTR2,+24=CPAR2,+28=CMAR2
	@+30=CCR3,+34=CNDTR3,+38=CPAR2,+3c=CMAR3
	@+44=CCR4,+48=CNDTR4,+4c=CPAR4,+50=CMAR4
	@+58=CCR5,+5c=CNDTR5,+60=CPAR5,+64=CMAR5
	@+6C=CCR6,+70=CNDTR6,+74=CPAR6,+78=CMAR6
	@+80=CCR7,+84=CNDTR7,+88=CPAR7,+8c=CMAR7
	@ tim1DMA
	@ adc dma
	ldr r0, = 0x40020000
	ldr r1, = 0x40012440
	str r1, [r0, # 0x10]
	ldr r1, = dianyabiao
	str r1, [r0, # 0x14]
	ldr r1, =  256
	str r1, [r0, # 0x0c]
	ldr r1, = 0xa81
	str r1, [r0, # 0x08]
	


_adcchushihua:
	ldr r0, = 0x40012400  @ adc基地址
	ldr r1, = 0x80000000
	str r1, [r0, # 0x08]  @ ADC 控制寄存器 (ADC_CR)  @adc校准
_dengadcjiaozhun:
	ldr r1, [r0, # 0x08]
	 movs r1, r1
	bmi _dengadcjiaozhun   @ 等ADC校准
_kaiadc:
	ldr r1, [r0, # 0x08]
	movs r2, # 0x01
	orrs r1, r1, r2
	str r1, [r0, # 0x08]
_dengdaiadcwending:
	ldr r1, [r0]
	lsls r1, r1, # 31
	bpl _dengdaiadcwending @ 等ADC稳定
_tongdaoxuanze:
	ldr r1, = 0x01
	str r1, [r0, # 0x28]    @ 通道选择寄存器 (ADC_CHSELR)
@	ldr r1, = 0xcC3         @ tim3触发ADC
	ldr r1, = 0x3003
	str r1, [r0, # 0x0c]    @ 配置寄存器 1 (ADC_CFGR1)
	movs r1, # 0        
	str r1, [r0, # 0x14]    @ ADC 采样时间寄存器 (ADC_SMPR)
	ldr r1, [r0, # 0x08]
	ldr r2, = 0x04         @ 开始转换
	orrs r1, r1, r2
	str r1, [r0, # 0x08]    @ 控制寄存器 (ADC_CR)


	
_waishezhongduan:		@外设中断
	@0xE000E100    0-31  写1开，写0没效
	@0XE000E180    0-31 写1关，写0没效
	@0XE000E200    0-31 挂起，写0没效
	@0XE000E280    0-31 清除， 写0没效




ting:
	
	ldr r0, = dianyabiao
	bl _fftjisuan
	ldr r0, = 0x20000058
	movs r1, # 0x01
	lsls r1, r1, # 10
	adds r1, r1, r0
	ldr r0, [r0]
	ldr r1, [r1]
	bl _jisuanfudu
	mov r3, r0
	ldr r0, = lvbohuanchong
	ldr r1, = 256
	ldr r2, = lvbozhizhen
	bl _lvboqi
	ldr r2, = shumaguanma
	movs r1, # 8
	bl _zhuanshumaguanma
	movs r0, # 8
	bl _xieshumaguan
neicunqingling1:
        ldr r0, = 0x20000000
        movs r1, # 0
        ldr r3, = 0x850
neicunqinglingxunhuan1:
        subs r3, # 4
        str r1, [r0, r3]
        bne neicunqinglingxunhuan1
	ldr r0, = 0x40020000
	ldr r1, [r0, # 0x0c]
	cmp r1, # 0
	bne ting
	str r1, [r0, # 0x08]
	movs r1, # 0xff
	ldr r2, = 0xa81
	str r1, [r0, # 0x0c]
	str r2, [r0, # 0x08]
	b ting
	

	
	
_maopaopaixu:
	push {r0-r7,lr}
	@ r0= 表地址, r1= 长度
	mov r7, r1
_paixu:
	lsls r1, r7, # 2
_paixuxunhuan:	
	ldrh r2, [r0, r1]
	subs r1, r1, # 2
	bmi _paixu1
	ldrh r4, [r0, r1]
	cmp r2, r4
	bls _paixuxunhuan
	strh r2, [r0, r1]
	adds r3, r1, # 2
	strh r4, [r0, r3]
	b _paixuxunhuan
_paixu1:
	adds r0, r0, # 2
	subs r7, r7, # 1
	bne _paixu
	pop {r0-r7,pc}

_zhuanshumaguanma:@ 16进制转数码管码
		@ R0要转的数据， R1长度，R2结果表首地址
	push {r0-r7,lr}
	ldr r7, = shumaguanmabiao
	mov r5, r0
	mov r6, r1
	movs r1, # 10
_xunhuanqiuma:
	bl _chufa
	mov r4, r0
	muls r4, r1
	subs r3, r5, r4
	lsls r3, # 2
	ldr r4, [r7, r3]
	str r4, [r2]
	mov r5, r0
	adds r2, r2, # 4
	subs r6, # 1
	bne _xunhuanqiuma
	pop {r0-r7,pc}
_xieshumaguan: @ r0=位数 @数码管码
	push {r0-r7,lr}
	lsls r0, r0, # 2
	movs r7, # 0
	mov r6, r0
	ldr r5, = shumaguanma
	ldr r2, = shumaguanshuaxinbiao
_shumaguanshuaxin:
	ldr r3, [r5, r7]
	ldr r4, [r2, r7]
	orrs r4, r4, r3
	mov r0, r4
	bl _xie595
	adds  r7, r7, # 4
	cmp r7, r6
	bls _shumaguanshuaxin
	pop {r0-r7,pc}
	
_xie595: @ R0=要写的数据
	push {r0-r7,lr}
	mov r5, r0
	movs r0, # 0x40
	movs r7, # 0x80 
	movs r6, # 0x20 
	movs r3, # 16   @16位
	ldr r2, = 0x48000000 @ gpioa
	movs r1, # 0x01
_xunhuan595:
	str r7, [r2, # 0x18]
	bl _yanshi
	tst r5, r1
	bne _xie595_0
	str r0, [r2, # 0x28]
	b _suocun595
_xie595_0:
	str r0, [r2, # 0x18]
_suocun595:
	bl _yanshi
	lsrs r5, # 1
	str r7, [r2, # 0x28]
	bl _yanshi
	subs r3, r3, # 1
	bne _xunhuan595
	str r6, [r2, # 0x18]
	bl _yanshi
	str r6, [r2, # 0x28]
	bl _yanshi
	pop {r0-r7,pc}


_yanshi:
	push {r7}
	ldr r7, = 30
_yanshi11:
	subs r7, # 1
	bne _yanshi11
	pop {r7}
	bx lr
_chufa:			@软件除法
	@ r0 除以 r1 等于 商(r0)余数R1
	push {r1-r4,lr}
	cmp r0, # 0
	beq _chufafanhui
	cmp r1, # 0
	beq _chufafanhui
	mov r2, r0
	movs r3, # 1
	lsls r3, r3, # 31
	movs r0, # 0
	mov r4, r0
_chufaxunhuan:
	lsls r2, r2, # 1
	adcs r4, r4, r4
	cmp r4, r1
	bcc _chufaweishubudao0
	adds r0, r0, r3
	subs r4, r4, r1
_chufaweishubudao0:
	lsrs r3, r3, # 1
	bne _chufaxunhuan
_chufafanhui:
	pop {r1-r4,pc}
	.ltorg

_jisuanfudu:	@ 计算幅度
		@ 入r0= 实部，r1= 虚部
	        @ 出r0 = 幅度
		@ Mag ~=Alpha * max(|I|, |Q|) + Beta * min(|I|, |Q|)
		@ Alpha * Max + Beta * Min
	push {r1-r3,lr}
	movs r0, r0
	bpl _shibubushifushu
	mvns r0, r0				@ 是负数转成正数
	adds r0, r0, # 1	
_shibubushifushu:				@ 实部不是负数
	movs r1, r1
	bpl _xububushifushu
	mvns r1, r1				@ 是负数转成正数
	adds r1, r1, # 1
_xububushifushu:				@ 虚部不是负数
	cmp r0, # 0
	bne _panduanxubushibushi0		
	mov r0, r1				
	pop {r1-r3,pc}
_panduanxubushibushi0:	
	cmp r1, # 0
	bne _jisuanfudu1
	pop {r1-r3,pc}
_jisuanfudu1:
	ldr r2, = 31066		@ Alpha q15 0.948059448969
	ldr r3, = 12867		@ Beta q15 0.392699081699
	cmp r1, r0
	bhi _alpha_min_beta_max
_alpha_max_beta_min:
	muls r0, r0, r2
	muls r1, r1, r3
	asrs r0, r0, # 15
	asrs r1, r1, # 15
	adds r0, r0, r1
	movs r1, # 1
	pop {r1-r3,pc}
_alpha_min_beta_max:
	muls r0, r0, r3
	muls r1, r1, r2
	asrs r0, r0, # 15
	asrs r1, r1, # 15
	adds r0, r0, r1
	movs r1, # 0
	pop {r1-r3,pc}

_lvboqi:
			@滤波器
			@R0=地址，R1=长度,r2=表指针地址,r3=ADC数值
			@出R0=结果
	push {r1-r7,lr}	
	ldr r5, [r2]		@读出表指针
	lsls r6, r1, # 1	
	strh r3, [r0, r5]	@数值写到滤波器缓冲区
	adds r5, r5, # 2
	cmp r5, r6
	bne _lvboqimeidaohuanchongquding
	movs r5, # 0
_lvboqimeidaohuanchongquding:
	str r5, [r2]
	movs r7, # 0
_lvboqixunhuan:
	cmp r5, r6
	bne _lvbozonghe
	movs r5, # 0
_lvbozonghe:
	ldrh r4, [r0, r5]
	adds r5, r5, # 2
	adds r7, r7, r4
	subs r1, r1, # 1
	bne _lvboqixunhuan
	asrs r0, r7, # 8	@修改
	pop {r1-r7,pc}

	
_fftjisuan:
				@ 入口 R0=数据地址
				@ 输出实部=0X20000000-0X20000400
				@ 输出虚部=0X20000400-0X20000800
				@ 结果左移6位（乘64）
	push {r0-r7,lr}
_fft1:
	ldr r1, = 0x20000000       @ 输出地址
	movs r2, # 128             @ 蝴蝶数量
	ldr r3, = hudieweifanzhuan @ 蝴蝶位反转表
_fft1xunhuan:
	ldr r6, [r3]               @ 取出位反转表里的地一个数据
	ldr r7, [r3, # 0x04]       @ 取出第二个
	ldr r6, [r0, r6]           @ 根据位反转表找到对应的输入数据  
	ldr r7, [r0, r7]           @ 第二个
	adds r4, r6, r7            @ 求出蝴蝶上
	subs r5, r6, r7            @ 求出蝴蝶下
	str r4, [r1]
	str r5, [r1, # 0x04]       @ 把反过来的顺序排列
	adds r1, r1, # 0x08        @ 输出的地址自增
	adds r3, r3, # 0x08        @ 反转表自增
	subs r2, r2, # 1           @ 蝴蝶数减1
	bne _fft1xunhuan           @ 蝴蝶数不到

_fft2:
	ldr r0, = 0x20000000       @ 实部输出地址0x20000000
	movs r4, # 1               
	lsls r4, r4, # 10          
	adds r4, r4, r0            @ 虚部输出地址 0x20000400
	mov r8, r4                 @ 实部和虚部中间
_fft2xunhuan:
	ldr r4, [r0]               @ 取出数据0
	ldr r5, [r0, # 0x08]       @ 取出数据2
	ldr r6, [r0, # 0x04]       @ 取出数据1
	ldr r7, [r0, # 0x0c]       @ 取出数据3
	adds r1, r4, r5            @ 计算蝴蝶上
	subs r2, r4, r5            @ 计算蝴蝶下
	mov r3, r6		@ 0 r 蝴蝶上实部
	movs r4, # 0
	subs r4, r4, r7		@ 0i 蝴蝶上虚部
	mov r5, r6		@ 3r 蝴蝶下实部
	mov r6, r7		@ 3i 蝴蝶下虚部
	movs r7, # 1
	lsls r7, r7, # 10       @ 内存实部和虚部中间
	adds r7, r7, r0         @ R7等于虚部首地址  
	str r1, [r0]            @ 蝴蝶上保存实部
	str r2, [r0, # 0x08]    @ 蝴蝶下实部
	str r3, [r0, # 0x04]    @ 第二组蝴蝶上实部
	str r4, [r7, # 0x04]    @ 第二组蝴蝶上虚部
	str r5, [r0, # 0x0c]	@ 第二组蝴蝶下实部
	str r6, [r7, # 0x0c]    @ 第二组下虚部
	adds r0, r0, # 0x10     @ 蝴蝶组自增
	cmp r0, r8     
	bne _fft2xunhuan        @ 地址不到循环
_fft3:
	ldr r6, = xuanzhuanyinzi       @ 旋转因子自增变量
	ldr r2, = fft3xuanzhuanyinzi   @ 旋转因子第三步的表
	ldr r0, = 0x20000000           @ 实部输出地址
	str r2, [r6]                   @ 旋转因子表首地址写到变量
	movs r1, # 1
	lsls r1, r1, # 10             
	adds r1, r1, r0                @ 虚部输出地址
	mov r8, r1		       @ R8虚部地址自增变量
	mov r9, r0                     @ R9实部地址自增变量
	mov r10, r2		       @ 旋转因子地址写到R10
	movs r5, # 0x10		       @ 两组蝴蝶的距离	
	mov r11, r5                    @ 写到R11
	movs r5, # 4                   @ 旋转因子数量
	mov r12, r5		       @ 旋转因子数量写到R12
	bl _fftg

_fft4:
	ldr r6, = xuanzhuanyinzi	@ 旋转因子自增变量
	ldr r2, = fft4xuanzhuanyinzi	@ 旋转因子第四步表
	ldr r0, = 0x20000000		@ 实部地址
	str r2, [r6]			@ 第四步旋转因子表写到自增变量
	movs r1, # 1
	lsls r1, r1, # 10
	adds r1, r1, r0			@ r1 = 虚部地址
	mov r8, r1			@ 
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
	lsls r1, r1, # 10
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
	lsls r1, r1, # 10
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
	lsls r1, r1, # 10
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

_fft8:
	ldr r6, = xuanzhuanyinzi
	ldr r2, = fft8xuanzhuanyinzi
	ldr r0, = 0x20000000
	str r2, [r6]
	movs r1, # 1
	lsls r1, r1, # 10
	adds r1, r1, r0
	mov r8, r1
	mov r9, r0
	mov r10, r2
	movs r5, # 1
	lsls r5, r5, # 9
	mov r11, r5
	movs r5, # 128
	mov r12, r5
	bl _fftg
	pop {r0-r7,pc}
_fftg:
	push {lr}		@ LR保存到堆栈
	movs r4, # 0
	mov lr, r4
_fftxunhuan:
	mov r0, r9		@ R0实部地址自增变量地址
	mov r1, r8		@ R1虚部地址自增变量地址	
	mov r2, r10		@ 旋转因子表地址地址
	mov r3, r11		@ 两组蝴蝶的距离
	ldr r4, [r0]		@ r4=蝴蝶上实部
	ldr r5, [r1]		@ r5=蝴蝶上虚部
	ldr r6, [r0, r3]	@ r6=蝴蝶下实部
	ldr r7, [r1, r3]	@ r7=蝴蝶下虚部
	ldr r3, [r2]		@ SR 
	ldr r2, [r2, # 0x04]	@ SI 
	push {r4,r5}		@ R4 R5保存到堆栈
				@ （a+bi）(c+di)=(ac-bd)+(ad+bc)i
	mov r4, r6		@ r4=蝴蝶下实部
	muls r4, r4, r3		@ 乘旋转因子	ac
	mov r5, r7		@ R5=蝴蝶下虚部
	muls r5, r5, r2		@ 乘旋转因子	bd
	subs r4, r4, r5		@ ac-bd
	asrs r4, r4, # 15	@ 截断Q15
	mov r5, r6
	muls r5, r5, r2		@ ad
	muls r7, r7, r3		@ bc
	adds r7, r7, r5         @ ad+bc
	asrs r7, r7, # 15	@ 截断Q15
	pop {r2,r5}		@ R2= 蝴蝶上实部
				@ r5= 蝴蝶上虚部
	adds r3, r2, r4    	@ 上实部加下实部=结果上实部
	subs r2, r2, r4    	@ 下实部减上实部=结果下实部
	adds r4, r5, r7		@ 上虚部加下虚部=结果上虚部
	subs r5, r5, r7		@ 上虚部减下虚部=结果下虚部
	mov r6, r11		@ r6=蝴蝶距离
	asrs r3, r3, # 1	@ 右移一位防止溢出
	asrs r4, r4, # 1	@ 右移一位防止溢出
	asrs r2, r2, # 1	@ 右移一位防止溢出
	asrs r5, r5, # 1	@ 右移一位防止溢出
	str r3, [r0]		@ 保存上实部
	str r4, [r1]		@ 保存上虚部
	str r2, [r0, r6]	@ 保存下实部
	str r5, [r1, r6]	@ 保存下虚部
	adds r0, r0, # 0x04	@ 实部地址加4
	adds r1, r1, # 0x04	@ 虚部地址加4
	mov r9, r0		@ r9=当前实部地址
	mov r8, r1		@ R8=当前虚部地址
	mov r2, r10		@ r2= 当前旋转因子地址
	adds r2, r2, # 0x08	@ R2 = 旋转因子地址加8
        mov r10, r2             @ 保存回去
	mov r4, lr		@ 一个蝴蝶旋转因子变量
	adds r4, r4, # 1        @ 自增
	mov lr, r4 		@ 保存回去
	mov r7, r12             @ 取出旋转因子总数量
	cmp r4, r7              @ 到没到数量
	bne _fftxunhuan         @ 没到继续循环
	movs  r4, # 0		@ 到了R4=0
	mov lr, r4		@ 一个蝴蝶旋转因子变量清0
	ldr r6, = xuanzhuanyinzi @ R6=旋转因子自增变量地址	
	ldr r5, = 0x20000400	 @ R5=虚部地址
	ldr r6, [r6]		 @ 取出旋转因子自增变量
	mov r7, r11		@ R7= 蝴蝶距离
        mov r10, r6              @ R10 = 旋转因子自增变量
	adds r0, r0, r7		@ 实部地址加蝴蝶距离
	adds r1, r1, r7		@ 虚部地址加蝴蝶距离
	mov r9, r0		@ R9等于当前实部地址
	mov r8, r1		@ R8等于当前虚部地址
	cmp r0, r5		@ 实部到没到虚部边界
	bne _fftxunhuan		@ 没到循环计算
	pop {pc}		@ 返回
	.ltorg			@ 文字池
	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
_systickzhongduan:
	ldr r0, = 0xe000ed04
	movs r1, # 1
	lsls r1, r1, # 25
	str r1, [r0]                 @ 清除SYSTICK中断
aaa:
	bx lr
