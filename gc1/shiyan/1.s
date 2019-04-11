	 .thumb                 
         .syntax unified
.section .data
.section .text
func:
	lsl r1, r0, # 16
        lsr r2, r0, # 16
        orr r1, r1, r2
        eor r2, r0, r1
        ldr r3, = 0xff0000
        bic r2, r2, r3
        lsl r1, r0, # 24
        lsr r3, r0, # 8
        orr r0, r1, r3
       lsr r3, r3, # 8
       eor r0, r0, r3
       bx lr 


