@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data	
        	.equ STACKINIT,          0x20000300

.section .text
vectors:        
        .word STACKINIT         
        .word _start + 1        
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
        .word _memory_fault + 1 
        .word _bus_fault + 1    
        .word _usage_fault + 1
_start:
chufa:
	movs r1, # 0x8
	mov r10, r1
	bl jianceweishu
	mov r8, r12
	movs r1, # 0x02
	mov r11, r1
	bl jianceweishu
	mov r9, r12
	mov r0, r9
	mov r2, r8
	subs r2, r2, r0
	mov r0, r11
chufa1:
	mov r1, r10
	lsrs r1, r2
	subs r1, r1, r0
	bpl shang1
	subs r2, r2, # 1
	b chufa1
shang1:
	movs r4, # 1
	lsls r4, r2
	movs r5, # 32
	subs r5, r5, r2
	mov r1, r8
	lsls r1, r5
ddd:
	b ddd
	
tingzhu:
	b tingzhu
	
jianceweishu:
	push {r0-r7,lr}
	movs r0, # 0
	movs r2, # 32
jianceweishu1:
	adds r0, r0, # 1
	lsls r1, # 1
	bpl jianceweishu1
	subs r2, r2, r0
	mov r12, r2
	pop {r0-r7,pc}
	
_nmi_handler:
	bx lr
_hard_fault:
	bx lr
_memory_fault:
	bx lr
_bus_fault:
	bx lr
_usage_fault:
 	bx lr
	
