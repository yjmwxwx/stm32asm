@@开启SWD
ldr r0, = 0x40010004
ldr r1, = 0x02000000
str r1, [r0]
