

@@@ Directives
        .thumb                 
        .syntax unified

.section .data

wxwx:	 .ascii "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz" 

        .equ STACKINIT,   0x20005000        
        
.section .text
        .org 0

@@@ Vectors
vectors:        
        .word STACKINIT         @ stack pointer value when stack is empty
        .word _start + 1        @ reset vector (manually adjust to odd for thumb)
        .word _nmi_handler + 1  @ 
        .word _hard_fault  + 1  @ 
        .word _memory_fault + 1 @ 
        .word _bus_fault + 1    @ 
        .word _usage_fault + 1  @ 

_start:
	mov r10, # 6

diyi:	

	ldr r8, = 0x30000000
	ldr r9, = wxwx

	ldmia r9!, {r0-r7}

	stmia r8!, {r0-r7}
	

	


_dummy:                        @ if any int gets triggered, just hang in a loop
_nmi_handler:
_hard_fault:
_memory_fault:
_bus_fault:
_usage_fault:
	bx lr 
