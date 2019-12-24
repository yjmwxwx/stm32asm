	 .thumb
	         .syntax unified
        ldr r0, = 0x20000500
        movs r1, # 10
        bl __yi_wei
        bkpt # 2
__yi_wei:
        @ r0=地址 r1=长度
        push {r4-r7,lr}
        mov r12, sp
        lsls r1, r1, # 5
        adds r1, r1, r0
        mov r11, r1
__xun_huan:
        mov sp, r0
        pop {r0-r7}
        adcs r0, r0, r0
        adcs r1, r1, r1
        adcs r2, r2, r2
        adcs r3, r3, r3
        adcs r4, r4, r4
        adcs r5, r5, r5
        adcs r6, r6, r6
        adcs r7, r7, r7
	push {r0-r7}
        mov r0, sp
        adds r0, r0, # 0x20
        cmp r0, r11
        bne __xun_huan
        mov sp, r12
	pop {r4-r7,pc}
