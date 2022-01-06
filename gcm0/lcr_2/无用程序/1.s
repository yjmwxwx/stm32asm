__fu_shu_cheng_fa:
	push {r2-r7,lr}
	@r0=a,r1=b,r2=c,r3=d
	mov r4, r0      @a
	mov r5, r1      @b
	mov r6, r2	@c
	mov r7, r3	@d
	muls r0, r0, r2 @a*c
	muls r1, r1, r3 @b*d
	asrs r0, r0, # 15
	asrs r1, r1, # 15
	subs r0, r0, r1 @ac-bd
	muls r4, r4, r7 @a*d
	muls r5, r5, r6 @b*c
	asrs r4, r4, # 15
	asrs r5, r5, # 15
	adds r4, r4, r5 @ad+bc
	mov r1, r4
	pop {r2-r7,pc}
	
__jiaozhun_jiaodu:
	cpsid i
	push {r0-r7,lr}
	mov r0, r8
	mov r1, r9
	mov r2, r10
	mov r3, r11
	push {r0-r3}
	ldr r0, = 32768	@180度
	movs r1, # 0
	mov r8, r0
	mov r9, r1
	ldr r0, = z_r
	ldr r1, = z_i
	ldr r6, [r0]
	ldr r7, [r1]
	ldr r3, = jiaodu_jiaozhun_yong_cordic
	movs r2, # 0
__jiaodu_jiaozhun_xunhuan:	
	ldr r4, [r3, r2]
	adds r2, r2, # 4
	ldr r5, [r3, r2]
        mov r0, r6
	mov r1, r7
	bl __atan2_ji_suan
	ldr r1, = qiwang_jiaodu
	ldr r1, [r1]
	subs r0, r0, r1
	bmi __jiaodu_fanzhuan
	mov r10, r6
	mov r11, r7
	mov r6, r8
	mov r7, r9
        mov r0, r6
	mov r1, r7
	muls r6, r6, r4 @X*COS
	muls r1, r1, r5 @Y*SIN
	muls r0, r0, r5 @X*SIN
	muls r7, r7, r4 @Y*COS
	adds r6, r6, r1
	subs r7, r7, r0
	asrs r6, r6, # 15
	asrs r7, r7, # 15
	mov r8, r6
	mov r9, r7
        mov r6, r10
	mov r7, r11
	mov r0, r6
	mov r1, r7
	muls r6, r6, r4	@X*COS
	muls r1, r1, r5	@Y*SIN
	muls r0, r0, r5	@X*SIN
	muls r7, r7, r4	@Y*COS
	adds r6, r6, r1
	subs r7, r7, r0
	asrs r6, r6, # 15
	asrs r7, r7, # 15
	b __jiaodu_xuanzhuan
__jiaodu_fanzhuan:
	mov r10, r6
	mov r11, r7
	mov r6, r8
	mov r7, r9
	mov r0, r6
	mov r1, r7
        muls r6, r6, r4 @X*COS
	muls r1, r1, r5 @Y*SIN
	muls r0, r0, r5 @X*SIN
	muls r7, r7, r4 @Y*COS
	subs r6, r6, r1
	adds r7, r7, r0
	asrs r6, r6, # 15
	asrs r7, r7, # 15
	mov r8, r6
	mov r9, r7
	mov r6, r10
	mov r7, r11
	mov r0, r6
	mov r1, r7
	muls r6, r6, r4 @X*COS
	muls r1, r1, r5 @Y*SIN
	muls r0, r0, r5 @X*SIN
	muls r7, r7, r4 @Y*COS
	subs r6, r6, r1
	adds r7, r7, r0
	asrs r6, r6, # 15
	asrs r7, r7, # 15
__jiaodu_xuanzhuan:
	adds r2, r2, # 4
	cmp r2, # 240
	bne __jiaodu_jiaozhun_xunhuan
	ldr r2, = cos_jiaozheng
	ldr r3, = sin_jiaozheng
	mov r0, r8
	mov r1, r9
	str r0, [r2]
	str r1, [r3]
	pop {r4-r7}
	mov r8, r4
	mov r9, r5
	mov r10, r6
	mov r11, r7
	cpsie i
	pop {r0-r7,pc}

__jiaozhun_fudu:
	push {r0-r6,lr}
        ldr r0, = xiabi_r
	ldr r1, = xiabi_i
	ldr r0, [r0]
	ldr r1, [r1]
	bl __ji_suan_fu_du
	mov r2, r0
	ldr r0, = shangbi_r
	ldr r1, = shangbi_i
	ldr r0, [r0]
	ldr r1, [r1]
	bl __ji_suan_fu_du @r0=shangbi , r2= xiabi
	movs r1, # 0
	ldr r3, = jiaozhun_yong_cordic
	ldr r5, = 32768
	mov r6, r2
__fudu_jiaozhun_xunhuan:
	ldr r4, [r3, r1]
	cmp r0, r2
	bcc __fudu_jian
__fudu_jia:
	adds r5, r5, r4
	b __jiaozhun_xuanzhuan
__fudu_jian:
	subs r5, r5, r4
__jiaozhun_xuanzhuan:
	mov r2, r6
	muls r2, r2, r5
	lsrs r2, r2, # 15
	adds r1, r1, # 4
	cmp r1, # 120
	bne __fudu_jiaozhun_xunhuan
__baocun_fudu_jiaozhun:	
	ldr r0, = fudu_jiaozhun
	str r5, [r0]
	pop {r0-r6,pc}



