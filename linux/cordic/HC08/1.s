	;; CORDIC 演示程序
	;; Written by Samuel Ginsberg
	;; January 2002
	TOPRAM       EQU  $0080	; RAM顶
	TOPROM       EQU  $F600	; ROM顶
	TOPVECTORS   EQU  $FFDE	; 中断向量顶
	$Include 'jl3regs.inc'
	;; ===================================================================
	org TOPRAM
	operand1 ds 2     	; 16位操作数由加法程序使用
	operand2 ds 2
	Avar ds 2         	;cordic 角变量
	Xvar ds 2         	;cordic x 坐标变量
	Yvar ds 2         	;cordic y 坐标变量
	dA ds 2           	;cordic 角度修正因子
	ier variable
	dX ds 2           	;cordic x 坐标修改量变量
	dY ds 2           	;cordic y 坐标修改量变量
	loopcnt ds 1      	;cordic 迭代次数计数器
	flags ds 1        	;各种标志变量
	Angle ds 2        	;用于演示不是CORDIC的一部分
	clockwise equ 0   	;rotation direction flag
	;; 标志字节中的位
	;; 用于演示不是CORDIC的一部分
	even_quad equ 1   	;
	neg_cycle_sin equ 2   	;
	;; ====================================================
	org TOPROM
Main:
	;; 这是代码复位后开始执行的点
	;; 这里插入您的代码以使用CORDIC算法
	;; ===================================================================
cordic:
	;;这是主要的CORDIC算法，输入要转换的角度
	;;通过16位变量Avar。角度弧度相乘
	;;小于2048 ， 最大输入范围-PI/2 小于 A 小于PI/2
	;;银子2048
	;;余弦输出 Xvar, 该变量放大2048
	;; 注意Avar , Xvar , Yvar 放在内存
	mov #$00,loopcnt        ; 从迭代零开始
	mov #$00,Yvar           ; 初始化Yvar变量
	mov #$00,(Yvar+1)
	mov #$04,Xvar           ;初始化Xvar变量 0X04DC
	mov #$DC,(Xvar+1)
	
iterate:                        ;迭代
	
	ldhx Xvar               ;dX=Xvar 右移i个地方
	lda loopcnt
	jsr shiftright
	sthx dX
	ldhx Yvar               ;dY=Yvar 右移动i个地方
	lda loopcnt
	jsr shiftright
	sthx dY
	lda loopcnt             ;dA=lookup (1/2^loopcnt)
	jsr lookup
	sthx dA
	bset clockwise,flags
	brclr 7,Avar,update_pos ;if Avar>=0 increase angle
	bclr clockwise,flags    ;else decrease angle
update_pos:
	ldhx Xvar            	;Xvar=Xvar-dY if clockwise=1. Xvar=Xvar+dy if clockwise=0
	sthx operand1
	ldhx dY
	brclr clockwise,flags,clockwise1
	jsr negate
clockwise1:
	sthx operand2
	jsr addition
	ldhx operand1
	sthx Xvar
	ldhx Yvar            	;Yvar=Yvar+dX if clockwise=1. Yvar=Yvar-dx if clockwise=0
	sthx operand1
	ldhx dX
	brset clockwise,flags,clockwise2
	jsr negate
clockwise2:
	sthx operand2
	jsr addition
	ldhx operand1
	sthx Yvar
	ldhx Avar            	;Avar=Avar-dA if clockwise=1. Avar=Avar+dA if clockwise=0
	sthx operand1
	ldhx dA
	brclr clockwise,flags,clockwise3
	jsr negate
clockwise3:
	sthx operand2
	jsr addition
	ldhx operand1
	sthx Avar
	bra next_iteration
next_iteration:
	inc loopcnt		;next iteration of the loop
	lda #$0B
	cmp loopcnt
	bne iterate
	rts
	;; ===================================================================
output:
	;; This function outputs data calculated by the CORDIC algorithm
	;; Data is input to DAC1 via the variable Xvar
	;; Data is input to DAC2 via the variable Yvar
	;; Implementation depends on the DAC being used and its configuration.
	rts
	;; ===================================================================
lookup:
	;; This routine looks a 16 bit number up from the lookup table.
	;; The lookup table index comes in via the accumulator and the looked
	;; up value comes out via H:X.
	lsla                	;needed because each lookup entry is 2 bytes
	tax
	clrh
	lda lookup_atan,X   	;retrieve upper byte from lookup table
	psha                	;H reg used for addressing so not accessible
	aix #1              	;move to next position in table
	ldx lookup_atan,X   	;retrieve lower byte from lookup table
	pulh
	rts
	;; ===================================================================
negate:
	;; This routine calculates the 2's compliment negative of a 16 bit number.
	;; The input comes in via H:X and output is returned via H:X
	pshh
	pula
	coma     		;Acc now holds 1's complimented high byte
	comx     		;X reg holds 1's complimented low byte
	psha
	pulh     		;H reg holds 1's complimented high byte
	aix #1   		;Add 1 to H:X to form 2's compliment from 1's compliment
	rts
	;; ===================================================================
addition:
	;; This routine adds two 16 bit numbers. The overflow bit is discarded,
	;; as this routine is meant for two's compliment numbers.
	;; The inputs are in the variables operand1 and operand2 and the output is
	;; in operand1. Operand1 and operand2 are packed in memory with the more
	;; significant byte in the lower address.
	lda (operand1+1)
	add (operand2+1)
	sta (operand1+1)
	lda operand1
	adc operand2
	sta operand1
	rts
	;; ===================================================================
lookup_atan:
	;; This is the arctangent lookup table. Each entry is 16 bits wide. There
	;; are 12 entries to give 12 bit resolution.
	db $06,$48,$03,$B5,$01,$F5,$00,$FE,$00,$7F,$00,$3F
	db $00,$1F,$00,$0F,$00,$07,$00,$03,$00,$01,$00,$00
	;; ===================================================================
No_irq:
	;; This interrupt handler catches interrupts that happened when no
	;; interrupt should have occurred. For this reason the processor is halted
	;; and user intervention is required. This routine is only called under severe
	;; fault conditions.
	stop          		; Stop the processor and wait for a reset.
	rti           		; return
	;; ===================================================================
	org  TOPVECTORS
	dw  No_irq    		; ADC Conversion Complete interrupt
	dw  No_irq    		; Keyboard interrupt
	dw  No_irq    		; Unused
	dw  No_irq    		; Unused
	dw  No_irq    		; Unused
	dw  No_irq    		; Unused
	dw  No_irq    		; Unused
	dw  No_irq    		; Unused
	dw  No_irq    		; Unused
	dw  No_irq    		; Unused
	dw  No_irq    		; TIM1 Overflow interrupt
	dw  No_irq    		; TIM1 Channel 1 interrupt
	dw  No_irq    		; TIM1 Channel 0 interrupt
	dw  No_irq    		; Unused
	dw  No_irq    		; interrupt line
	dw  No_irq    		; Software interrupt
	dw  main      		; Reset Vector
	;; ===================================================================
main:
	;; This example of a main function puts a full sine wave into a 12 bit DAC.
	mov #$03,CONFIG1  	;Disable the watchdog timer, enable the stop instruction
	mov #$FF,DDRB     	;ports output for DAC connection
	mov #$FC,DDRD
	mov #$00,flags    	;start status flags in known state
	mov #$00,Angle    	;start angle in known state
	mov #$00,(Angle+1)
	mov #$00,Xvar
	mov #$00,(Xvar+1)
	mov #$00,Yvar
	mov #$00,(Yvar+1)
	;; This section of code generates a full sine wave from four quarter waves. The
	;; CORDIC system is used to generate sinusiods between 0deg and 90deg. The angle
	;; that is put into the algorithm is ramped up and then down to get each half cycle.
	;; Every second half cycle is inverted to create negative half cycles.
	;; There are 12868 points per cycle.
loop:
	ldhx Angle
	brset even_quad,flags,dec_angle ;decide whether to ramp the angle up or down
	aix #1                          ;ramp angle up
	sthx Avar                       ;unless at the peak of the waveform
	lda #$0C                        ;which is at (pi/2)*2048=3216decimal=$0C90
	cmp Avar                        ;if we are at the peak then at the next
	bne load_angle                  ;point we must start ramping the angle down.
	lda #$90
	cmp (Avar+1)
	bne load_angle
	bset even_quad,flags
	bra load_angle
dec_angle:
	aix #-1			;ramp the angle down
	sthx Avar
	clra
	cmp Avar		;unless the angle is zero, in which case
	bne load_angle		;prepare to start ramping the angle up.
	cmp (Avar+1)		;in addition when we reach zero we must
	bne load_angle		;change from a positive half cycle to a
	bclr even_quad,flags	;negative half, or visa versa
	brset neg_cycle_sin,flags,negative_half
	bset neg_cycle_sin,flags
	bra load_angle
negative_half:
	bclr neg_cycle_sin,flags
load_angle:
	sthx Angle		;load the updated angle into the angle
	sthx Avar		;variable and feed it into CORDIC
	jsr cordic
	mov #$07,operand2	;add a DC offset to the output because our
	mov #$FF,(operand2+1)	;DAC is unipolar.
	ldhx Yvar
	brclr neg_cycle_sin,flags,no_bias_negative_sin ;if the current half cycle
	aix #-1					       ;is negative then we need
	jsr negate				       ;to invert it to produce a
no_bias_negative_sin:				       ;full wave.
	sthx operand1
	jsr addition
	ldhx operand1
	sthx Yvar
	jsr output		;send the output to the DAC
	jmp loop
