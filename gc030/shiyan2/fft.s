	.syntax unified
	.align 2
	.globl fft
	.thumb

.section .data	
       	.equ STACKINIT,                 0x20001000
shuru:	.int 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.int 16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
hudie:	.int 0,64,32,96,16,80,48,112,8,72,40,104,24,88,56,120
	.int 4,68,36,100,20,84,52,116,12,76,44,108,28,92,60,124	
.section .text
_fftjisuan:
	mov r1, r1

