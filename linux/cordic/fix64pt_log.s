				  									  							   ;******************** (C) COPYRIGHT 2013    ********************
;* File Name          : fix64pt_log .s
;* Author             : MCUKEY
;* Version            : V1.0.0
;* Date               : 10/21/2013
;* Description        : Optimized   for Cortex-M3
;********************************************************************************
;* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
;* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
;* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
;* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
;* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
;* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;*******************************************************************************/

	THUMB
  	REQUIRE8
    PRESERVE8

	AREA |.text|, CODE, READONLY, ALIGN=2
		        
	EXPORT fix64pt_log      

pssOUT    	RN R0
Nbr	    	RN R1
;pssX      	RN R1
pssIN     	RN R1
pssK      	RN R1

pssKP		RN R3
ZiH			RN R3
ZiL			RN R2

X        	RN R4
Y        	RN R5
Xi1H		RN R5
Xi1L		RN R4

Xi        	RN R6
Yi        	RN R7
Yi1H		RN R7
Yi1L		RN R6

Cr        	RN R8
Z        	RN R9
XiH			RN R9
XiL			RN R8

Dr        	RN R10
Di        	RN R11
YiH			RN R11
YiL			RN R10

cntrbitrev 	RN R12
index     	RN R12
tmp       	RN R12
pssIN2    	RN R14
tmp2      	RN R14

NPT EQU 256

;----------------------------- MACROS ----------------------------------------
	 
	 	MACRO
	 	DEC  $reg
     	SUB  $reg,$reg,#1
     	MEND

	 	MACRO
     	INC  $reg
     	ADD  $reg,$reg,#1
     	MEND


 	 	MACRO
	 	QUAD  $reg
     	MOV  $reg,$reg,LSL#2
     	MEND

		MACRO
		ASRW64		$sRdL,$sRdH,$sRnL,$sRnH,$offset,$tmp
		ASR.W		$sRdH,$sRnH,$offset
		LSR.W		$sRdL,$sRnL,$offset
		NEG			$tmp,$offset
		ADD			$tmp,#32
		LSL.W		$tmp,$sRnH,$tmp
		ORR			$sRdL,$tmp
		MEND


		MACRO
		ADD64S		$sRdL,$sRdH,$sRnL,$sRnH
		ADDS.W		$sRdL,$sRnL
		ADC.W		$sRdH,$sRnH
		MEND

		MACRO
		SUB64S		$sRdL,$sRdH,$sRnL,$sRnH
		SUBS.W		$sRdL,$sRnL
		SBC.W		$sRdH,$sRnH
		MEND

		MACRO
		LSLW64		$sRdL,$sRdH,$offset,$tmp
		LSL.W		$sRdH,$offset
		NEG			$tmp,$offset
		ADD			$tmp,#32
		LSR.W		$tmp,$sRdL,$tmp
		ORR.W		$sRdH,$tmp
		LSL.W		$sRdL,$offset
		MEND
;------------------- 			CODE 			--------------------------------
;===============================================================================
;*******************************************************************************
;* Function Name  : fix64pt_log
;* Description    : 64bit定点自然对数计算
;* Input          : - R0 = pssOUT:  参数指针 ,定标27
;*					www.mcukey.com
;*                
;* Output         : R0 返回值指针,	定标s58
;* Return         : R0

;* ln(x) = 2*tanh-1[(x-1)/(x+1)]
;*分两步，第一步计算负i迭代，第二步计算正i迭代
;* x(i+1) = x(i) - d(i)*2^(-i)*y(i) + d(i)*y(i)
;* y(i+1) = y(i) - d(i)*2^(-i)*x(i) + d(i)*x(i)
;* z(i+1) = z(i) + d(i)*tanh-1*(1-2^-i)

;* x(i+1) = x(i) + d(i)*2^(-i)*y(i)
;* y(i+1) = y(i) + d(i)*2^(-i)*x(i)
;* z(i+1) = z(i) - d(i)*tanh-1*2^-i
;*******************************************************************************
fix64pt_log

        STMFD   SP!, {R4-R12, LR}
		
		LDR		R4,=0X4001100c
	   	LDR		R5,=0X00000008
		STR		R5,[R4]
		;LDR		Xi1H,=0;0X1BA70EF;
		;LDR		Xi1L,=0x8100010;0x34F12CCB;
		;LDR		Yi1H,=0;0X1BA70EF;
		;LDR		Yi1L,=0x8100010;0x34F12CCB;
		;MOV		Nbr,#0
;nextnbrloop

		LDRD	Xi1L,Xi1H,[pssOUT]			;Xi1H,Xi1L = x
		LDRD	Yi1L,Yi1H,[pssOUT],#8 		;Yi1H,Yi1L = y
		
		
	   	;STMFD   SP!, {R1}
		LDR		XiH,=0X0					;XiH,XiL = x(i+1)
		LDR		XiL,=0X0			
		LDR		YiH,=0X0					;YiH,YiL = y(i+1)
		LDR		YiL,=0X0
		ADD64S	Xi1L,Xi1H,#0x8000000,#0x0	;64位加1，x = x+1
		SUB64S	Yi1L,Yi1H,#0x8000000,#0x0	;64位减1, y = y-1
		CLZ.W	index,Xi1H					;计算Xi1H前面0的个数
		SUB		index,#1
		LSLW64  Xi1L,Xi1H,index,tmp2		;x与y左移填满最高位,提高计算精度
		LSLW64  Yi1L,Yi1H,index,tmp2
		MOV		ZiH,#0						;z=0,无符号数
		MOV		ZiL,#0


        ADRL    pssK, Table_atan2i_V7    ; Coeff in Flash
		MOV		index,#8
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
minusloop64											;增加i的负数迭代，扩大定义域范围
		ASRW64	XiL,XiH,Xi1L,Xi1H,index,tmp2		;(Xi1H,Xi1L)>>i
		ASRW64	YiL,YiH,Yi1L,Yi1H,index,tmp2

		SUB64S	YiL,YiH,Yi1L,Yi1H					;
		SUB64S	XiL,XiH,Xi1L,Xi1H
		
		TEQ		Xi1H,Yi1H							;sign(Xi1H)==sign(Yi1H),d=-1；否则d=1
		BMI		dminus								;d = -1跳转
		ADD64S	Xi1L,Xi1H,YiL,YiH					;d = +1; + d(i)*y(i)
		ADD64S	Yi1L,Yi1H,XiL,XiH
		;ADD		ZiH,tmp2
		LDR		tmp2,[pssK],#4
		ADDS.W	ZiL,tmp2							;计算z低32位
		LDR		tmp2,[pssK],#4						;计算z高32位
		ADC.W	ZiH,tmp2
		B		decindex
dminus												;d = -1
		SUB64S	Yi1L,Yi1H,XiL,XiH		
	   	SUB64S	Xi1L,Xi1H,YiL,YiH
		;SUB		ZiH,tmp2
		LDR		tmp2,[pssK],#4
		SUBS.W	ZiL,tmp2							;计算z低32位
		LDR		tmp2,[pssK],#4						;计算z高32位
		SBC.W	ZiH,tmp2
decindex
		DEC 	index
		CMP 	index,#1
        BNE  	minusloop64							;i的负数迭代结束
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
smallnum
		MOV 	index,#1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
plusloop64							   ;当i为正循环迭代
		;LDR		Cr,[pssK],#4			;theta_i
		ASRW64	XiL,XiH,Xi1L,Xi1H,index,tmp2
		ASRW64	YiL,YiH,Yi1L,Yi1H,index,tmp2
		;LDR		tmp2,[pssK],#4
		TEQ		Xi1H,Yi1H
		BMI		pminus
 		;SUBPL	X,X,Yi				;Zi>0,di=1, Xi+1=Xi-Yi>>(2^-i)
		SUB64S	Xi1L,Xi1H,YiL,YiH
		;SUBPL	Y,Y,Xi				;Zi<0,di=-1, Yi+1=Yi-Xi>>(2^-i)
		SUB64S	Yi1L,Yi1H,XiL,XiH
		;ADDPL	Z,Cr
		;ADD		ZiH,tmp2
		LDR		tmp2,[pssK],#4
		ADDS.W	ZiL,tmp2
		LDR		tmp2,[pssK],#4
		ADC.W	ZiH,tmp2
		B		pecindex
pminus
		;ADDMI	X,X,Yi				;Zi<0,di=-1,Xi+1=Xi+Yi>>(2^-i)
		ADD64S	Xi1L,Xi1H,YiL,YiH
		;ADDMI	Y,Y,Xi				;Zi>0,di=1, Yi+1=Yi+Xi>>(2^-i)
		ADD64S	Yi1L,Yi1H,XiL,XiH
		;SUB		ZiH,tmp2
		LDR		tmp2,[pssK],#4
		SUBS.W	ZiL,tmp2
		LDR		tmp2,[pssK],#4
		SBC.W	ZiH,tmp2
pecindex
		CMP		index,#4			;判断i是否等于4、13，用于重复迭代一次
		BEQ		k3loop64
		CMP		index,#13
		BEQ		k3loop64
k3loop64end
		INC 	index
		CMP 	index,#29
        BNE  	plusloop64			;当i为正循环迭代一次结束	
nbrloopend
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		;LDMFD   SP!, {R1}	 		
		
		STRD	ZiL,ZiH,[pssOUT,#-8]

		LDR		R1,=0X4001100c
	   	LDR		R2,=0X00000000
		STR		R2,[R1]		
        LDMFD   SP!, {R4-R12, PC}
;........................................................................................

k3loop64							;当i=4、13时重复迭代一次
		ASRW64	XiL,XiH,Xi1L,Xi1H,index,tmp2
		ASRW64	YiL,YiH,Yi1L,Yi1H,index,tmp2
		;LDR		tmp2,[pssK,#-4]
		TEQ		Xi1H,Yi1H
		BMI		pminuss

 		;SUBPL	X,X,Yi				;Zi>0,di=1, Xi+1=Xi-Yi>>2i
		SUB64S	Xi1L,Xi1H,YiL,YiH
		;SUBPL	Y,Y,Xi				;Zi<0,di=-1, Yi+1=Yi-Xi>>2i
		SUB64S	Yi1L,Yi1H,XiL,XiH
		;ADDPL	Z,Cr
		;ADD		ZiH,tmp2
		LDR		tmp2,[pssK,#-8]
		ADDS.W	ZiL,tmp2
		LDR		tmp2,[pssK,#-4]
		ADC.W	ZiH,tmp2
		B		k3loop64end
pminuss
		;ADDMI	X,X,Yi				;Zi<0,di=-1,Xi+1=Xi+Yi>>2i
		ADD64S	Xi1L,Xi1H,YiL,YiH
		;ADDMI	Y,Y,Xi				;Zi>0,di=1, Yi+1=Yi+Xi>>2i
		ADD64S	Yi1L,Yi1H,XiL,XiH
		;SUB		ZiH,tmp2
		LDR		tmp2,[pssK,#-8]
		SUBS.W	ZiL,tmp2
		LDR		tmp2,[pssK,#-4]
		SBC.W	ZiH,tmp2
		B		k3loop64end			;当i=4、13时重复迭代一次结束

;=============================================================================
		NOP
Table_atan2i_V7
;MINUSLOOP
        ;DCD 0x2b120400,0x5067b2dc,0x2bcac400,0x4da1ea7c,0x0c838800,0x4adc221c,0xad3c4800,0x481659bb;
        ;DCD 0xcdf50c00,0x4550915a,0xeeadcc00,0x428ac8f8,0x0f668800,0x3fc50095,0x301f3200,0x3cff382d;
        ;DCD 0x50d79400,0x3a396fbd,0x718ed600,0x3773a73d,0x92419800,0x34adde9d,0xb2e25a00,0x31e815bd;
        ;DCD 0xd33b1c00,0x2f224c5d,0xf273de00,0x2c5c81fd,0x0d2c9600,0x2996b59e,0x15e50e00,0x26d0e53e;
        ;DCD 0xd69b7a00,0x240b0cdd,0x77419000,0x2145247c,0x9764ee00,0x1e7f1c16,0xb3721500,0x1bb8d39e;
		;atan-1(1-2^-i),64bit,s59
        DCD 0xaec67c00,0x18f20ade,0xa3e3cc00,0x162a40fd,0x602e4200,0x13607294,0xe3181b00,0x109291e8;
        DCD 0x4895ad00,0x0dbc6724,0xa6a40f80,0x0ad50b1c,0x8c9695c0,0x07c89cab;
;PLUSLOOP,atan-1(2^-i),64bit,s59
        DCD 0xab40c2c0,0x0464fa9e,0x50228a40,0x020b15df,0xc9eaef70,0x01015891,0x569bad68,0x00802ac4;
        DCD 0x2246bb8c,0x00400556,0xb1115a3a,0x002000aa,0x5588891b,0x00100015,0xaaac4446,0x00080002;
        DCD 0x55556222,0x00040000,0x0aaaab11,0x00020000,0x01555559,0x00010000,0x002aaaab,0x00008000;
        DCD 0x00055555,0x00004000,0x0000aaab,0x00002000,0x00001555,0x00001000,0x000002ab,0x00000800;
        DCD 0x00000055,0x00000400,0x0000000b,0x00000200,0x00000001,0x00000100,0x00000000,0x00000080;
        DCD 0x00000000,0x00000040,0x00000000,0x00000020,0x00000000,0x00000010,0x00000000,0x00000008;
        DCD 0x00000000,0x00000004,0x00000000,0x00000002,0x00000000,0x00000001,0x80000000,0x00000000;
        ;DCD 0x40000000,0x00000000,0x20000000,0x00000000,0x10000000,0x00000000,0x08000000,0x00000000;
        ;DCD 0x04000000,0x00000000,0x02000000,0x00000000,0x01000000,0x00000000,0x00800000,0x00000000;	
        END
;******************* (C) COPYRIGHT 2014  mcukey *****END OF FILE****
