__chengfa:
        @入R0 乘以 R1
        @出 R0高32 ， R1低32
        @0xffffffff*0xffffffff
        @4        F F F E 0 0 0 1
        @3                F F F E 0 0 0 1
        @2                F F F E 0 0 0 1
        @1                        F F F E 0 0 0 1
        @         F F F F F F F E 0 0 0 0 0 0 0 1
        push {r2-r7,lr}
        mov r2, r0
        mov r3, r1
        lsrs r0, r0, # 16       @高16
        lsls r2, r2, # 16       @ 低16
        lsrs r2, r2, # 16
	lsrs r1, r1, # 16       @高16
	lsls r3, r3, # 16       @低16
	lsrs r3, r3, # 16
	mov r4, r2
        mov r5, r0
        muls r2, r2, r3         @1
        muls r0, r0, r3         @2
        muls r4, r4, r1         @3
        muls r5, r5, r1         @4
        mov r6, r0              @2
        mov r7, r4              @3
        lsls r0, r0, # 16       @2低
        lsls r4, r4, # 16       @3低
        lsrs r6, r6, # 16       @2高
        lsrs r7, r7, # 16       @3高
        adds r2, r2, r0
        adcs r2, r2, r4
        adcs r5, r5, r6
        adcs r5, r5, r7
        mov r0, r5
        mov r1, r2
        pop {r2-r7,pc}

__chufa64:
        @64位除32位
        @ （R0=高32位R1=低32位）除（R2)= （R0高32）（R1低32）
        push {r3-r7,lr}
        cmp r2, # 0
        beq __chu_fa64_fan_hui0
        cmp r1, # 0
        bne __chu_fa64_ji_suan
        cmp r0, # 0
        beq __chu_fa64_fan_hui0
__chu_fa64_ji_suan:
        movs r4, # 0
        mov r7, r4
        mov r3, r4
        mov r5, r4
	movs r6, # 1
        lsls r6, r6, # 31
__chu_fa64_xun_huan:
        lsls r1, r1, # 1
        adcs r0, r0, r0
        adcs r4, r4, r4
        cmp r4, r2
        bcc __chu_fa_yi_wei
        adds r3, r3, r6
        adcs r5, r5, r7
        subs r4, r4, r2
__chu_fa_yi_wei:
        movs r6, r6
        beq __di_yi_wei
        lsrs r6, r6, # 1        @高32位移位
        bne __chu_fa64_xun_huan
        movs r7, # 1
        lsls r7, r7, # 31
        b __chu_fa64_xun_huan
__di_yi_wei:            @低32位移位
        lsrs r7, r7, # 1
        bne __chu_fa64_xun_huan
        mov r0, r3
        mov r1, r5
        pop {r3-r7,pc}
__chu_fa64_fan_hui0:
        movs r0, # 0
        movs r1, # 0
        pop {r3-r7,pc}
