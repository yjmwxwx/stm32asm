
led-stm32.bin:     file format binary


Disassembly of section .data:

00000000 <.data>:
   0:	20005000 	andcs	r5, r0, r0
   4:	04b8709c 	ldrteq	r7, [r8], #156	; 0x9c
   8:	00004098 	muleq	r0, r8, r0
   c:	000001bb 			; <UNDEFINED> instruction: 0x000001bb
	...
  2c:	000001c3 	andeq	r0, r0, r3, asr #3
	...
  a4:	000001c5 	andeq	r0, r0, r5, asr #3
  a8:	0000f04f 	andeq	pc, r0, pc, asr #32
  ac:	0100f04f 	tsteq	r0, pc, asr #32
  b0:	0200f04f 	andeq	pc, r0, #79	; 0x4f
  b4:	0300f04f 	movweq	pc, #79	; 0x4f	; <UNPREDICTABLE>
  b8:	0400f04f 	streq	pc, [r0], #-79	; 0x4f
  bc:	0500f04f 	streq	pc, [r0, #-79]	; 0x4f
  c0:	0600f04f 	streq	pc, [r0], -pc, asr #32
  c4:	0700f04f 	streq	pc, [r0, -pc, asr #32]
  c8:	0800f04f 	stmdaeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
  cc:	0900f04f 	stmdbeq	r0, {r0, r1, r2, r3, r6, ip, sp, lr, pc}
  d0:	0a00f04f 	beq	0x3c214
  d4:	0b00f04f 	bleq	0x3c218
  d8:	49384837 	ldmdbmi	r8!, {r0, r1, r2, r4, r5, fp, lr}
  dc:	48386001 	ldmdami	r8!, {r0, sp, lr}
  e0:	60014938 	andvs	r4, r1, r8, lsr r9
  e4:	49386802 	ldmdbmi	r8!, {r1, fp, sp, lr}
  e8:	f0404211 			; <UNDEFINED> instruction: 0xf0404211
  ec:	f7ff8002 			; <UNDEFINED> instruction: 0xf7ff8002
  f0:	4836bff9 	ldmdami	r6!, {r0, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, sp, pc}
  f4:	0132f04f 	teqeq	r2, pc, asr #32
  f8:	0000cb07 	andeq	ip, r0, r7, lsl #22
  fc:	6001f027 	andvs	pc, r1, r7, lsr #32
 100:	49b9f9f9 	ldmibmi	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 104:	c9d95919 	ldmibgt	r9, {r0, r3, r4, r8, fp, ip, lr}^
 108:	598949e9 	stmibpl	r9, {r0, r3, r5, r6, r7, r8, fp, lr}
 10c:	c9c9e9d9 	stmibgt	r9, {r0, r3, r4, r6, r7, r8, fp, sp, lr, pc}^
 110:	39b9f9f9 	ldmibcc	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 114:	49a9b959 	stmibmi	r9!, {r0, r3, r4, r6, r8, fp, ip, sp, pc}
 118:	c9d959d9 	ldmibgt	r9, {r0, r3, r4, r6, r7, r8, fp, ip, lr}^
 11c:	c9b949d9 	ldmibgt	r9!, {r0, r3, r4, r6, r7, r8, fp, lr}
 120:	c9d9f9f9 	ldmibgt	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 124:	59c949c9 	stmibpl	r9, {r0, r3, r6, r7, r8, fp, lr}^
 128:	49c9c9d9 	stmibmi	r9, {r0, r3, r4, r6, r7, r8, fp, lr, pc}^
 12c:	d9c9c9b9 	stmible	r9, {r0, r3, r4, r5, r7, r8, fp, lr, pc}^
 130:	49b9f9f9 	ldmibmi	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 134:	c9d959c9 	ldmibgt	r9, {r0, r3, r6, r7, r8, fp, ip, lr}^
 138:	59c949c9 	stmibpl	r9, {r0, r3, r6, r7, r8, fp, lr}^
 13c:	c9c9c9d9 	stmibgt	r9, {r0, r3, r4, r6, r7, r8, fp, lr, pc}^
 140:	39b9f9f9 	ldmibcc	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 144:	19b9b9a9 	ldmibne	r9!, {r0, r3, r5, r7, r8, fp, ip, sp, pc}
 148:	59a949a9 	stmibpl	r9!, {r0, r3, r5, r7, r8, fp, lr}
 14c:	c9d94959 	ldmibgt	r9, {r0, r3, r4, r6, r8, fp, lr}^
 150:	8999f9f9 	ldmibhi	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 154:	c9c9e9d9 	stmibgt	r9, {r0, r3, r4, r6, r7, r8, fp, sp, lr, pc}^
 158:	c9b9c909 	ldmibgt	r9!, {r0, r3, r8, fp, lr, pc}
 15c:	c9e9e9d9 	stmibgt	r9!, {r0, r3, r4, r6, r7, r8, fp, sp, lr, pc}^
 160:	c9b9f9f9 	ldmibgt	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 164:	c9e9e9d9 	stmibgt	r9!, {r0, r3, r4, r6, r7, r8, fp, sp, lr, pc}^
 168:	79c949f9 	stmibvc	r9, {r0, r3, r4, r5, r6, r7, r8, fp, lr}^
 16c:	b98909b9 	stmiblt	r9, {r0, r3, r4, r5, r7, r8, fp}
 170:	19b9f9f9 	ldmibne	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 174:	c9b94929 	ldmibgt	r9!, {r0, r3, r5, r8, fp, lr}
 178:	c9d9d9e9 	ldmibgt	r9, {r0, r3, r5, r6, r7, r8, fp, ip, lr, pc}^
 17c:	59894919 	stmibpl	r9, {r0, r3, r4, r8, fp, lr}
 180:	c9d9f9f9 	ldmibgt	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 184:	c9b94909 	ldmibgt	r9!, {r0, r3, r8, fp, lr}
 188:	c9d9d989 	ldmibgt	r9, {r0, r3, r7, r8, fp, ip, lr, pc}^
 18c:	59f949f9 	ldmibpl	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, lr}^
 190:	49f9f9f9 	ldmibmi	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 194:	c9d95909 	ldmibgt	r9, {r0, r3, r8, fp, ip, lr}^
 198:	c9b94909 	ldmibgt	r9!, {r0, r3, r8, fp, lr}
 19c:	c9d9d9d9 	ldmibgt	r9, {r0, r3, r4, r6, r7, r8, fp, ip, lr, pc}^
 1a0:	5919f9f9 	ldmdbpl	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 1a4:	c9d94959 	ldmibgt	r9, {r0, r3, r4, r6, r8, fp, lr}^
 1a8:	39c999b9 	stmibcc	r9, {r0, r3, r4, r5, r7, r8, fp, ip, pc}^
 1ac:	39c939c9 	stmibcc	r9, {r0, r3, r6, r7, r8, fp, ip, sp}^
 1b0:	39c9f9f9 	stmibcc	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 1b4:	39c939c9 	stmibcc	r9, {r0, r3, r6, r7, r8, fp, ip, sp}^
 1b8:	c909c9c9 	stmdbgt	r9, {r0, r3, r6, r7, r8, fp, lr, pc}
 1bc:	c9c9c9d9 	stmibgt	r9, {r0, r3, r4, r6, r7, r8, fp, lr, pc}^
 1c0:	c9c9f9f9 	stmibgt	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 1c4:	99f9c9e9 	ldmibls	r9!, {r0, r3, r5, r6, r7, r8, fp, lr, pc}^
 1c8:	c9c9c9d9 	stmibgt	r9, {r0, r3, r4, r6, r7, r8, fp, lr, pc}^
 1cc:	c9c9c9e9 	stmibgt	r9, {r0, r3, r5, r6, r7, r8, fp, lr, pc}^
 1d0:	c909f9f9 	stmdbgt	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 1d4:	09c9c9e9 	stmibeq	r9, {r0, r3, r5, r6, r7, r8, fp, lr, pc}^
 1d8:	99f9c999 	ldmibls	r9!, {r0, r3, r4, r7, r8, fp, lr, pc}^
 1dc:	09e9d9f9 	stmibeq	r9!, {r0, r3, r4, r5, r6, r7, r8, fp, ip, lr, pc}^
 1e0:	c949f9f9 	stmdbgt	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 1e4:	49c9c9e9 	stmibmi	r9, {r0, r3, r5, r6, r7, r8, fp, lr, pc}^
 1e8:	0909c9d9 	stmdbeq	r9, {r0, r3, r4, r6, r7, r8, fp, lr, pc}
 1ec:	49897909 	stmibmi	r9, {r0, r3, r8, fp, ip, sp, lr}
 1f0:	e949f9f9 	stmdb	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 1f4:	b9c9c9c9 	stmiblt	r9, {r0, r3, r6, r7, r8, fp, lr, pc}^
 1f8:	e989c9c9 	stmib	r9, {r0, r3, r6, r7, r8, fp, lr, pc}
 1fc:	b9b9c9c9 	ldmiblt	r9!, {r0, r3, r6, r7, r8, fp, lr, pc}
 200:	c9c9f9f9 	stmibgt	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 204:	e9c9c9c9 	stmib	r9, {r0, r3, r6, r7, r8, fp, lr, pc}^
 208:	b9c9c9c9 	stmiblt	r9, {r0, r3, r6, r7, r8, fp, lr, pc}^
 20c:	c989c9b9 	stmibgt	r9, {r0, r3, r4, r5, r7, r8, fp, lr, pc}
 210:	0989f9f9 	stmibeq	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}
 214:	0949c9c9 	stmdbeq	r9, {r0, r3, r6, r7, r8, fp, lr, pc}^
 218:	0949c9c9 	stmdbeq	r9, {r0, r3, r6, r7, r8, fp, lr, pc}^
 21c:	c949c9c9 	stmdbgt	r9, {r0, r3, r6, r7, r8, fp, lr, pc}^
 220:	09c9f9f9 	stmibeq	r9, {r0, r3, r4, r5, r6, r7, r8, fp, ip, sp, lr, pc}^
 224:	c9d9c9c9 	ldmibgt	r9, {r0, r3, r6, r7, r8, fp, lr, pc}^
 228:	09c9c9c9 	stmibeq	r9, {r0, r3, r6, r7, r8, fp, lr, pc}^
 22c:	0909c9c9 	stmdbeq	r9, {r0, r3, r6, r7, r8, fp, lr, pc}
