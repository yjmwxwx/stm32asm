	@ stm32f030f4p6 asm
	@fft 8点
	 .thumb                 
         .syntax unified
.section .data	
       	.equ STACKINIT,                 0x20001000
shuru:	.int 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.int 16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
hudie:	.int 0,64,32,96,16,80,48,112,8,72,40,104,24,88,56,120
	.int 4,68,36,100,20,84,52,116,12,76,44,108,28,92,60,124
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
	ldr r2, = 0x20000500
	msr psp, r2
	movs r0, # 0x03
	msr control, r0
	ldr r6, = shuru
	mov r11, r6
_fenjie:
	bkpt
	ldr r2, = 0x20000500
	mov r3, r2
	mov r4, r3
	subs r4, r4, # 64
	mov r8, r3
	mov r9, r4
	
	mov sp, r11
	pop {r0-r7}
	mov r11, sp
	mov sp, r8
	push {r0,r2,r4,r6}
	mov r8, sp
	mov sp, r9
	push {r1,r3,r5,r7}
	
	mov r9, sp
	mov sp, r11
	pop {r0-r7}
	mov r11, sp
        mov sp, r8
	push {r0,r2,r4,r6}
	mov r8, sp
	mov sp, r9
	push {r1,r3,r5,r7}
	mov r9, sp
	
	mov sp, r11
	pop {r0-r7}
	mov r11, sp
	mov sp, r8
	push {r0,r2,r4,r6}
	mov r8, sp
	mov sp, r9
	push {r1,r3,r5,r7}
	
	mov r9, sp
	mov sp, r11
	pop {r0-r7}
	mov r11, sp
	mov sp, r8
	push {r0,r2,r4,r6}
	mov r8, sp
	mov sp, r9
	push {r1,r3,r5,r7}

	bkpt
	
	mov r3, sp
	mov r4, r3
	subs r4, r4, # 64
	mov r8, r3
	mov r9, r4

	      
	pop {r0-r7}
	mov r11, sp
	mov sp, r8
	push {r0,r2,r4,r6}
	mov r8, sp
	mov sp, r9
	push {r1,r3,r5,r7}
	mov r9, sp
	
	mov sp, r11
	pop {r0-r7}
	mov r11, sp
	mov sp, r8
	push {r0,r2,r4,r6}
	mov r8, sp
	mov sp, r9
	push {r1,r3,r5,r7}
	mov r9, sp
	
	mov sp, r11
	pop {r0-r7}
	mov r11, sp
	mov sp, r8
	push {r0,r2,r4,r6}
	mov r8, sp
	mov sp, r9
	push {r1,r3,r5,r7}
	mov r9, sp
	
	mov sp, r11
	pop {r0-r7}
	mov r11, sp
	mov sp, r8
	push {r0,r2,r4,r6}
	mov r8, sp
	mov sp, r9
	push {r1,r3,r5,r7}
	mov r11, sp
	bkpt
	b _fenjie
	
	

	

	

	

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
