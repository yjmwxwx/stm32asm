	.macro  空操作
        .short   0x0000
        .endm

        .macro  A到B
        .short   0x2100
        .endm

        .macro 立即数到A t:vararg
        .short   0x100\t
        .endm

        .macro  A加B
        .short   0x1700
        .endm
	
        .macro  A减B
        .short   0x1800
        .endm
	
        .macro  无条件转移
        .short   0x0b00
        .endm
	
        .macro  为零转移
        .short   0x0c00
        .endm
	
        .macro  不为零转移
        .short   0x0d00
        .endm
	
        .macro  A到RAM
        .short   0x7100
        .endm
        .macro  RAM到A
        .short   0x1a00
        .endm

.section .text               
	立即数到A t=5
	A到B
	A到RAM
	A减B
	不为零转移
	





	
