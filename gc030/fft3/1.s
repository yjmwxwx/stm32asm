	@ stm32f030f4p6 asm
	@fft 8点
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000
shuru:	  .int 3535,3535,6464,10607,3535,-10607,-13535,-3535
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
	
_start:
	

_fftjisuan:
	mov r12, sp     
	@一
	ldr r0, = shuru	@实
	ldr r1, [r0]                @0
	ldr r2, [r0, # 0x10]	    @4
	adds r4, r1, r2
	subs r5, r1, r2
	ldr r1, [r0, # 0x08]	    @2
	ldr r2, [r0, # 0x18]	    @6
	adds r6, r1, r2
	subs r7, r1, r2
	push {r4-r7}	
	
	ldr r1, [r0, # 0x04]	   @1
	ldr r2, [r0, # 0x14]	   @5
	adds r4, r1, r2
	subs r5, r1, r2
	ldr r1, [r0, # 0x0c]       @3
	ldr r2, [r0, # 0x1c]	   @7
	adds r6, r1, r2
	subs r7, r1, r2
	
	@二			@r4=1,r5=5,r6=3,r7=7

        
				
	adds r0, r4, r6
	subs r1, r4, r6
	movs r2, # 0
	movs r3, # 0
	subs r6, r3, # 1
	muls r6, r7, r6
	mov r4, r5         @实
	movs r5, # 0
	adds r6, r5, r6
	subs r7, r5, r6
	mov r5, r4
	mov r11, sp
	push {r4-r7}
	push {r0-r7}
	mov r10, sp
			 
	mov sp, r11
	pop {r4-r7}	               @r4=0,r5=4,r6=2,r7=6
	adds r0, r4, r6
	subs r1, r4, r6
	movs r2, # 0
	movs r3, # 0
	subs r6, r3, # 1
	muls r6, r7, r6
	mov r4, r5          @实
	movs r5, # 0
	adds r6, r5, r6
	subs r7, r5, r6
	mov r5, r4
	
	push {r0-r7}      	@r0=0r,r1=2r,r2=0i,r3=2i
				@r4=4r,r5=6r,r6=4i,r7=6i

	
	pop {r0-r3}
	mov r8, sp
	mov sp, r10
	pop {r4-r7}
	mov r9, sp
        			@r0=0r,r1=2r,r2=0i,r3=2i
	mov sp, r10		@r4=1r,r5=3r,r6=1i,r7=3i
	push {r0,r2,r4,r6}
	push {r1,r3,r5,r7}
	mov r10, sp

	
	mov sp, r8
	pop {r4-r7}
	mov sp, r9
	pop {r0-r3}
				@r0=4r,r1=6r,r2=4i,r3=6i
				@r4=5r,r5=7r,r6=5i,r7=7i
	mov sp, r10
	push {r0,r2,r4,r6}
	push {r1,r3,r5,r7}
	
	@三

	
	pop {r4-r7}		@r4=7r,r5=7i,r6=6r,r7=6i
	mov r11, sp
	movs r2, # 0
	subs r2, r2, # 7
	
	mov r0, r4
	muls r0, r0, r2
	mov r1, r5
	muls r1, r1, r2
	subs r0, r0, r1         @ac-bd=dr
 	mov r8, r0
	mov r0, r4
	muls r0, r0, r2         @ad
	mov r1, r5
	muls r1, r1, r2         @bc
	adds r1, r1, r0         @ad+br=di
	mov r0, r8
	movs r2, # 10
	muls r6, r6, r2
	muls r7, r7, r2
	adds r2, r6, r0
	adds r3, r7, r1
	subs r6, r6, r0
	subs r7, r7, r1
	push {r2,r3,r6,r7}	@r2=3r,@r3=3i,@r6=7r,r7=7i
	mov r10, sp

	mov sp, r11
	pop {r4-r7}            
	mov r11, sp
	movs r2, # 7
	movs r3, # 0
	subs r3, r3, # 7

	mov r0, r4
	muls r0, r0, r2
	mov r1, r5
	muls r1, r1, r3
	subs r0, r0, r1         @ac-bd=dr
	mov r8, r0
	mov r0, r4
	muls r0, r0, r3         @ad
	mov r1, r5
	muls r1, r1, r2         @bc
	adds r1, r1, r0         @ad+br=di
	mov r0, r8
	movs r2, # 10
	muls r6, r6, r2
	muls r7, r7, r2
	adds r2, r6, r0
	adds r3, r7, r1
	subs r6, r6, r0
	subs r7, r7, r1
	mov sp, r10
	push {r2,r3,r6,r7}       @r2=4r,r3=4i,r6=5r,r7=5i
	mov r10, sp
	
	
        mov sp, r11
	pop {r4-r7}		@r4=2r,r5=2i,r6=3r,r7=3i
	mov r11, sp
	movs r2, # 0
	movs r3, # 10
	subs r3, r2, r3
	mov r0, r6
	muls r0, r0, r2         @ac
	mov r1, r7
	muls r1, r1, r3         @bd
	subs r0, r0, r1         @ac-bd=dr
	mov r8, r0
	mov r0, r6
	muls r0, r0, r3         @ad
	mov r1, r7
	muls r1, r1, r2         @bc
	adds r1, r0, r1         @ad+br=di
	mov r0, r8
	movs r2, # 10
	muls r4, r4, r2
	muls r5, r5, r2
	adds r2, r4, r0
	adds r3, r5, r1
	subs r6, r4, r0
	subs r7, r5, r1
	mov sp, r10
	push {r2,r3,r6,r7}   @r2=2r,r3=2i,r6=3r,r7=3i
	mov r10, sp
	
	mov sp, r11
	pop {r4-r7}		@r4=0r,r5=0i,r6=1r,r7=1i
	movs r2, # 10
	muls r4, r4, r2
	muls r5, r5, r2
	muls r6, r6, r2
	muls r7, r7, r2
	adds r0, r4, r6
	adds r1, r5, r7
	subs r2, r4, r6
	subs r3, r5, r7
	push {r0-r3}
	

_tingting:
	b _tingting
		
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_svc_handler:
	bx lr
_pendsv_handler:
	bx lr
