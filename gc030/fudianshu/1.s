@ stm32f030f4p6 asm 
	 .thumb                 
         .syntax unified
.section .data
	.equ duizhanding,       0x20001000 @ 堆栈顶	
.section .text
vectors:          @向量表
        .word duizhanding                     
        .word _start + 1             @复位向量
        .word _nmi_handler + 1  
        .word _hard_fault  + 1  
_start:
	ldr r0, = 0xffffffff
	ldr r1, = 0xffffffff
	movs r5, # 0
	muls r0, r1
	adcs r5, r5, r5
bb:
	b bb




























	
	ldr r0, = 1234567890
	lsls r0, r0, # 1
	lsrs r0, r0, # 1
	movs r7, r0
	movs r5, # 0
_qiuweishu:
	adds r5, r5, # 1
	lsls r7, r7, # 1
	adcs r6, r6, r6
	cmp r6, # 1
	bne _qiuweishu
	movs r6, # 0x10
	subs r5, r6, r5
	subs r5, r5, # 1
	mov r6, r0
	lsrs r6, r6, r5
	
	
	
	

	
	ldr r0, = 1234567899
	lsls r0, r0, # 1
	ldr r1, = 1000000000
	movs r3, # 1
	lsls r3, r3, # 29
	movs r2, # 0
	movs r6, r2
_xiaoshuxunhuan:
	movs r4, r1
	lsrs r4, r2
	adds r2, r2, # 1
	cmp r4, r0
	bhi _xiaoshuyiwei
_xiaoshujian:	
	subs r0, r0, r4
	adds r6, r6, r3
_xiaoshuyiwei:
	lsrs r3, r3, # 1
	bne _xiaoshuxunhuan
	lsls r6, r6, # 3
	lsrs r0, r6, # 9
	
	
	
_tingxia:
	b _tingxia

	
_chufa64:		@64位除以32位软件除法
	@ r0-r1除以r2等于R0-R1余数R2
	push {r4-r7}
	mov r3, r0
	mov r6, r1
	movs r4, # 1
	mov r7, r4
	lsls r4, r4, # 31
	movs r0, # 0
	mov r5, r0
_chufaxunhuan64:
	lsls r3, r3, # 1
	adcs r5, r5, r5
	cmp r5, r2
	bcc _chufaweishubudao64
	adds r0, r0, r4
	subs r5, r5, r2
_chufaweishubudao64:
	lsrs r4, r4, # 1
	bne _chufaxunhuan64
	push {r0}
	lsls r7, r7, # 31
	bpl _chufafanhui64
	mov r4, r7
	mov r3, r6
	movs r0, # 0
	b _chufaxunhuan64
_chufafanhui64:
	mov r1, r0
	mov r2, r5
	pop {r0}
	pop {r0}
	pop {r4-r7}
	bx lr

_chufa:		@软件除法
	@ r0 除以 r1 等于 商(r0)余数(r1)
	push {r4}
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
	mov r1, r4
	pop {r4}
	bx lr

chengfa64:
	@入R2 乘以 R3
	@出 R11高32 ， R12低32
	@        FFFFFFFF × FFFFFFFF
	@        F F F E 0 0 0 1
	@                F F F E 0 0 0 1
	@                F F F E 0 0 0 1
	@                        F F F E0 0 0 1
	@        F F F F F F F E 0 0 0 0 0 0 0 1
	push {r0-r7,lr}
	mov r7, r1
	mov r12, sp
	bl _gaodi16
	push {r0-r1}  @ r0高R12  R1低R12-4
	
	mov r0, r7
	bl _gaodi16
	mov r4, r0    @ R4高
	mov r5, r1    @ R5低
	pop {r0-r1}   @ R0高 R1低 
	
	muls r5, r1   @R0低XR1低
	mov r0, r5
	bl _gaodi16
	push {r0,r1}  @R12高 R12+4低
	
	muls r5, r0   @ R0高XR1低
	mov r0, r5
	bl _gaodi16
	push {r0,r1}   @R12+8高 @R12+0X0C低
	
	muls r4, r1    @R0高XR1低
	mov r0, r4
	bl _gaodi16
	push {r0,r1}    @ R12+0X10高 @R12+0X14低
	
	muls r4, r0     @R0高XR1高
	mov r0, r4
	bl _gaodi16      
	push {r0,r1}     @ R12+0X18高 R12+0X1C低
	
	mov r7, r12
	ldr r0, [r7]
	ldr r1, [r7, # 0x0c]
	ldr r2, [r7, # 0x14]
	adds r0, r0, r1
	adds r0, r2, r2
	bl _gaodi16     @R0高  R1低
	mov r6, r1     @ 得到低16
	ldr r2, [r7, # 0x08]
	ldr r3, [r7, # 0x14]
	ldr r4, [r7, # 0x1c]
	adds r2, r2, r3
	adds r2, r2, r4
	adds r0, r0, r2
	
	
	
	
	

	mov sp, r12
	pop {r0-r7,pc}




_gaodi16:	 @ 高低16 ，R0人 出R0高，R1低
	lsls r1, r0, # 16
	lsrs r1, # 16
	lsrs r0, # 16
	bx lr

	
	
_nmi_handler:	
	bx lr
_hard_fault:
	bx lr 
