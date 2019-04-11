
		sub		r9, r9, #2
		mov		r0, r9, lsl #20
		cmn		r0, #0x100000
						
		mov		r0, r9, lsr #12
		add		r2, r11, #64
		ldr		r0, [r2,r0,lsl #2]
		cmp		r0, #0
					
		strb	r10, [r0, r9]		
		add		r2, r9, #1
		mov		r3, r10, lsr #8	
		strb	r3, [r0, r2]		
