        ;; skip the emacs mode line
;;; -*- Mode:Asm Mode:outline-minor-mode outline-regexp:";;;+" comment-start: "; " -*-
;;; Riscy Pygness -- Pygmy Forth for the ARM


;;;; Copyright
        
        ;;   Copyright (c) 2004-2011 Frank C. Sergeant
        ;;   Freely available under a modified BSD/MIT/X license.
        ;;   Details at http://pygmy.utoh.org/license20040130.txt.

;;;; Introduction

        ;; This file (riscy-stm32.asm) defines the assembly routines
        ;; (i.e., the primitives) for the STM32 ARM Cortex M3 version
        ;; of Riscy Pygness.  The result of assembling the primitives
        ;; is not quite enough to produce the Forth kernel.  The
        ;; program riscy.tcl loads some high-level Forth on top of the
        ;; primitives to make a kernel image that can be burned into
        ;; the flash on the ARM chip.

;;;; Pre-processing step
        
        ;; This file uses the semicolon as the comment character.  The
        ;; *.asm files are preprocessed (via the makefile) by
        ;; preasm.tcl to change all semicolons to at-signs so that the
        ;; GNU ARM assembler will be happy.

;;;; CPU and board variants

        .equ stm32, 1

;;;; Mapping assembler label names to Forth names

        ;; Because of assembler naming conventions, we cannot always
        ;; label the code that implements a Forth primitive with the
        ;; Forth name for that primitive.

        ;; Because of this, and because the program riscy.tcl needs a
        ;; list of all the primitives, the code for every primitive
        ;; must be preceded with a comment, in a special format, that
        ;; maps the assembly label to the Forth name.
        
        ;; For example, to map the label "cfetch:" to the Forth name
        ;; "C@", we use the following comment:

        ;; ";;; label cfetch is Forth word C@ ( a - c)"

        ;; There must be at least three semicolons but there may be
        ;; more.  The program riscy.tcl parses the assembly listing
        ;; file to collect the Forth word names and map them to the
        ;; associated assembly language labels.

;;;; Forth virtual machine

        ;; Register usage:
        ;;   r0  caches TOS (top of stack)
        ;;   r2  is TEMPREG, scratch -- used within the nxt routine 
        ;;   r3  scratch -- often used to hold an address
        ;;   r4  scratch
        ;;   r5  scratch
        ;;   r6  is a scratch register for holding base addresses such as IOBASE
        ;;   r7  UP, User Pointer, holds address of current task control block
        ;;   r8  Forth W
        ;;         holds xt address, in the form used by our
        ;;         particular threading model.  The left 13 bits hold
        ;;         the token number and the rightmost 3 bits hold
        ;;         flags.  See the code at nxtTab for details.
        ;;   r9  Forth IP (instruction pointer) (holds address of next 16-bit xt)
        ;;   r10 Forth data stack pointer
        ;;   r11 Forth return stack pointer
        ;;   r12 Loop counter
        ;;   sp, i.e., the hardware stack pointer, is r13 by default
        ;;       we don't use it for the Forth, although actual nested
        ;;       subroutine calls may use it.

TOS        .req r0
TEMPREG    .req r2        
UP         .req r7 
W          .req r8
IPTR       .req r9   ; "Instruction Pointer" can't use "IP" because gas hardcodes "IP" as reg 12
DSTK       .req r10
RSTK       .req r11
RLOOP      .req r12

        .equ RAMBASE, 0x20000000 

;;; Macros
;;;; nxt -- move from one word to the next, following IPTR
        .macro nxt      ; jump to the inner interpreter
           b nxtTab
        .endm

;;;; dpush -- push a register to the data stack
        .macro dpush reg
           str \reg, [DSTK, #-4]!
        .endm

;;;; rpush -- push a register to the return stack
        .macro rpush reg
           str \reg, [RSTK, #-4]!
        .endm

;;;; dpop -- pop data stack into a register
        .macro dpop reg
           ldr \reg, [DSTK], #4
        .endm

;;;; rpop -- pop return stack into a register
        .macro rpop reg
           ldr \reg, [RSTK], #4
        .endm

;;;; dup 
        ; -- we keep tos in a register
        .macro dup
           dpush TOS
        .endm

;;;; drop
        .macro drop
           dpop TOS
        .endm

;;;; nip -- Pop a 32-bit data element from the data stack into r1
        .macro nip
           dpop  r1
        .endm

;;;; push -- Pop a 32-bit data element from the data stack and 
;               push it to the return stack.
        .macro push
           rpush TOS
           drop         ; refill TOS
        .endm
        
;;;; pop -- Pop a 32-bit data element from the return stack and 
;               push it to the data stack.
        .macro pop
           dup          ; make room on data stack
           rpop TOS     ; pop return stack into TOS
        .endm

;;;; lit -- push literal to data stack
        .macro lit num
           dup             ; make room on data stack
           ldr TOS, = \num   ; copy literal into TOS
        .endm

;;;; Multiple registers to/from stack
; The stm and ldm instructions let us move several items to or
; from the data or return stack in one instruction.

;;;; dpop2 -- pop 2 items from the in-memory data stack into r1 and r2

        ; The lowest-numbered register gets the value from the lowest
        ;  address.  b is on top of the in-memory data stack (because
        ;  c is cached in the register TOS) so b is at the lowest
        ;  address and so gets loaded into r1.  ( ... a b c - ... c)
        ;  so afterwards, r2=a, r1=b, r0=c Considering removing this
        ;  macro since it is used in only one place (the definition of
        ;  -ROT).

        .macro dpop2
           ldmfd DSTK!, {r1, r2}
        .endm

;;; Directives
        .thumb                  ; (same as saying '.code 16')
        .syntax unified

.section .text
        .global vectors
        .org 0

        .global _start

;;; Vectors
vectors:
        ;; b _start                ; reset                    (0x00)
        ;; b .                     ; undefined instruction    (0x04)
        ;; b .                     ; software interrupt (SWI) (0x08)
        ;; b .                     ; prefetch abort           (0x0C)
        ;; b .                     ; data abort               (0x10)
        ;; b .                     ; checksum                 (0x14)
        ;; b .                     ; IRQ                      (0x18)
        ;; b .                     ; FIRQ                     (0x1C)

        ;.word STACKINIT         ; stack pointer value when stack is empty
        .word mstk              ; stack pointer value when stack is empty
        .word _start + 1        ; reset vector (manually adjust to odd for thumb)
        .word _nmi_handler + 1  ;
        .word _hard_fault  + 1  ;
        .word _memory_fault + 1 ;
        .word _bus_fault + 1    ;
        .word _usage_fault + 1  ;


        
.section .text        
_start:
        b init                  ; jump around system parameter area


        .align                  ; following must be on a full-word boundary
parms:          
        ;; These system parameters are filled in by the compiler
        ;; so the '.word n' is just a place holder for now, showing
        ;; its entry number.  Compiler will replace it with actual value.
ptokens: .word 0     ; holds address of flash token table
                     ; If a hard-coded token table is defined in this
                     ;  assembly file (rather than generated by the
                     ;  compiler later) (i.e., for testing), then
                     ;  be sure to plug in the start of the token table
                     ;  here.  Otherwise, the compiler will fill it in.

prtokens: .word 1     ; holds address of RAM token table
pfreeram: .word 2     ; holds address of start of free RAM, used for initializing 'h'
        
;;; Include the processor-specific (and perhaps board-specific) equates
  ; and subroutines.  Note, code at _start: above jumps around whatever
  ; is included here (_start: jumps to 'init:').  This means that
  ; executable code in the included file must be in subroutines that will
  ; be called from the main file.
        
        .ifdef lpc2106
          .include "custom-lpc2106.s"
        .endif
        .ifdef lpc23xx
          .include "custom-lpc23xx.s"
        .endif
        .ifdef lpc2103
          .include "custom-lpc2103.s"
        .endif
        .ifdef lpc2294
          .include "custom-lpc2294.s"
        .endif
        .ifdef stm32
          .include "equates-bits.s"
          .include "equates-stm32.s"
          .include "olimex-stm32-p103.s"
        .endif

;;; init
init:   
        ; set up various stacks
        ; do any special register customizations
        
;;;; Initialize Clocks, PLL, Clock Dividers, etc
        bl setup_clocks
        
;;;; SysTick timer
        ; Start the timer needed for MS
        ;; ** this probably should be done in an include file **

        ;; set the preload value to the max (this is a 24-bit downcounting timer)
        ldr r6, = STK_LOAD
        mov r0, # 0x00FFFFFF
        str r0, [r6]

        ;; set the clock source to SYSCLK (fastest) and enable the timer
        ldr r6, = STK_CTRL
        mov r0, # STK_CLKSOURCE + STK_ENABLE
        str r0, [r6]
                
;;;; Set up I/O ports and peripherals
        bl setup_ports

;;;; Initialize the Forth data and return stacks and TCBs for all the tasks
  ;; Fill in LINK field for foreground task so it links to itself.  Thus,
  ;; the other two tasks are not in the active task list.
initTasks:

        ;; background task1
        ldr     DSTK, = dstk1
        ldr     RSTK, = rstk1
        ldr     UP, = task1       ; User Pointer holds address of task control block
        str     DSTK, [UP, #0x18] ; Initialize SP0 slot in TCB
        str     RSTK, [UP, #0x1c] ; Initialize RP0 slot in TCB

        ;; background task2
        ldr     DSTK, = dstk2
        ldr     RSTK, = rstk2
        ldr     UP, = task2       ; User Pointer holds address of task control block
        str     DSTK, [UP, #0x18] ; Initialize SP0 slot in TCB
        str     RSTK, [UP, #0x1c] ; Initialize RP0 slot in TCB

        ;; foreground task
        ldr     DSTK, = dstk
        ldr     RSTK, = rstk
        ldr     UP, = foreground  ; User Pointer holds address of task control block
        str     UP, [UP]          ; Initial LINK slot in TCB so the active task list contains
                                  ;   just the foreground task.  The foreground task jumps back
                                  ;   to itself when PAUSE executes.
        str     DSTK, [UP, #0x18] ; Initialize SP0 slot in TCB
        str     RSTK, [UP, #0x1c] ; Initialize RP0 slot in TCB
        

;;;; Example 
;; ;;; For testing, make it hang until the button is pressed.  This gives
;;  ;; us a chance to start the JTAG and OpenOCD.  This is for the LPC2103.
;;  ;; be sure to remove it for real use or adjust for testing other variants.
;; button:
;;         ldr r1, = FIO0PIN
;; 1:
;;         ldr r2, [r1]        ; read the Port 0
;;         tst r2, #0x8000     ; Wait for button to be pressed.
;;         bne 1b              ; (pin P0.15 is low when button is pressed)

;;;; Now blink LED several times

     ;; If you have one of the supported boards:

        ;  Olimex LPC2106 board with the LED connected to GPIO pin 7,
        ;  Olimex LPC P-2378 board with an LED connected to PORT1 pin 19,
        ;  Olimex LPC P-2103 board with an LED connected to PORT0 pin 26,
        ;  Olimex LPC L-2294 board with an LED connected to PORT1 pin 23,
        ;  Olimex STM32-P103 board with an LED connected to PORTC pin 12,

     ;; Then the following blinks the LED.  This can be a comfort when
     ;; you are bringing up a board or to remind you about opening the
     ;; BSL jumper (on LPC boards with a serial bootloader) after
     ;; programming the flash.  Comment it out if you prefer.

     ;; If you have a different board with an LED on a different pin,
     ;; change the custom include files and edit ledOnSub and
     ;; ledOffSub appropriately.

blink:
        mov r3, #6      ; how many times to blink the LED
1:              
        bl ledOnSub
        bl delayQ
        bl ledOffSub
        bl delayQ
        subs r3, r3, #1
        bne 1b
        
;;;; Send greeting out the serial port for testing.  Note, when 
  ;; running riscy.tcl, these characters are silently thrown away
  ;; (because it is waiting for a properly formatted message).
  ;; To test your serial port, start a serial terminal program
  ;; such as minicom, reset the target board, see if "hi" shows
  ;; up in the terminal.
greet:  
        ; Write several characters to the serial port
        bl crlf
        mov r1, #'h
        bl tx
        mov r1, #'i
        bl tx
        bl crlf
        
        b runboot

;;; label EXECUTE is Forth word EXECUTE ( a -)
EXECUTE:
        ;; This takes the full 32-bit address of a Forth word to be executed.
        ;; This is the same form of address that ' (tick) returns.
        mov r1, TOS
        drop           ; (refill TOS)

        ;; Handle Primitive
        ;;   if the address in TOS is less than # prim_cutoff, then the word
        ;;   is a primitive, so we just jump to it.
        ldr TEMPREG, = prim_cutoff
        cmp r1, TEMPREG        ; low address means this is a primitive, so 
        it lo
        bxlo r1

        ; Otherwise, handle nesting down to called high-level word
        str IPTR, [RSTK, #-4]!  ; push IPTR to return stack
        mov IPTR, r1            ; load IPTR with address of word to be executed
        ;; fall through to nxtTab
;;; Virtual machine primitives
nxtTab:    

        ; High-level Forth words use 16-bit tokens to represent calls
	; to subwords.  The token is comprised of several flags plus a
	; table entry number.

        ;    (bits 15..3) Entry number (index)
        ;          multiply it by the item width in bytes then
        ;          add it to the start of the table.
        ;
        ;    Flags:
        ;       bit2 Primitive/high-level flag.
        ;            If true, this token represents a primitive, so
        ;            jump to it.  Otherwise, it represents a high-level
        ;            Forth word, so do the work to nest down (sometimes
        ;            called "docol"), then jump back to nxtTab.
        ;
        ;       bit1 RAM/flash flag
        ;            If true, use RAM table.  Else use flash table.
        ;
        ;       bit0 Exit flag.  
        ;            If true, pop rstk into IPTR to effect a jump instead 
        ;            of a call, thus merging an exit (";") into the word.

        ; Since we look up the full 32-bit address, we do not need to
        ; align high-level Forth words to a 32-bit boundary.  A 16-bit
        ; boundary suffices.
        
        ; We store the 13 bits representing the token table entry
        ; number in the most significant 13 bits of an unsigned
        ; half-word.

        ; We also need one bit of information to tell whether the
        ; destination Forth word is a primitive (in which case we wish
        ; to jump to it) or a high-level word (in which case we wish
        ; to save the current value of IPTR and reload IPTR with the
        ; address of the destination word).
        
        ldrh W, [IPTR], #2      ; read unsigned half-word then bump IPTR by 2

nxtexec:            ; convenient entry point for use by EXECUTE
                    ; 16-bit token is now is W

        ;; handle Exit flag
        movs W, W, lsr #1        ; set C flag from original bit0 (i.e., the jump flag)
        it cs
        ldrcs IPTR, [RSTK], #4   ; pop rstack into IPTR ("unnest") only if jump=1

        ;; handle RAM/flash table flag
        movs W, W, lsr #1      ; set C flag from original bit1

        ;; Then load the address of the correct token table into TEMPREG
        ite cc
        ldrcc TEMPREG, ptokens    ; Load temporary register with base 
        ldrcs TEMPREG, prtokens   ;  address of the chosen token table.
                                  ;  If RAM flag was set, use the RAM
                                  ;  table.  Otherwise, use the flash table.

        ;; Remember the Primitive flag in C
        movs W, W, lsr #1      ; set C flag from original bit2
                               ; we will test this flag after looking up
                               ; the token's address in the token table.

        ;; Look up word's address in token table.  The 13 bits of the
        ;;  token number were originally in bits 15..3 of W but are
        ;;  now in bits 12..0 because we shifted W right 3 bits.  Now,
        ;;  shift W left 2 bits to convert to a byte offset then add
        ;;  offset to start of table, leaving address of entry table
        ;;  item in TEMPREG.

        add TEMPREG, TEMPREG, W, lsl #2

        ;; Handle Primitive
        ldr TEMPREG, [TEMPREG]  ; now TEMPREG holds destination address

        itt cs                  ; if carry is set, then make the address odd and take the jump
        orrcs TEMPREG, # 1      ; make it odd
        movcs pc, TEMPREG       ; force it into PC to effect a jump

        ;; An alternative to the above would be to build the token
        ;; table so the primitive addresses are odd.

        ; Otherwise, handle nesting down to called high-level word
        str IPTR, [RSTK, #-4]!  ; push IPTR to return stack
        mov IPTR, TEMPREG       ; load IPTR with address of new word
        b nxtTab                ; jump back to nxt to begin handling new word.

        .ltorg  ; force dumping of literal pool
        
;;; label EXIT is Forth word EXIT (  -)
EXIT:   
        ;; unnest by popping return stack into IPTR
        ldr IPTR, [RSTK], #4       ; pop rstack into IPTR
        nxt

;;; label NOP is Forth word NOP (  -)
;;; NOP ( -)  This serves mainly the purpose of safely occupying
;             16-bits in a high-level word list, e.g., for aligning a
;             label onto a 4-byte boundary.
NOP:
        nxt

;;; In Application Programming

;; Currently, we do not do in-application programming (IAP) of the Flash.
;; If you wish to activate IAP, following is an example for the LPC2106.
;; ;;; label IAP is Forth word IAP ( a -)
;; ; "In Application Programming"
;; ; a is the address of the 5-word table in RAM used both for
;; ; passing parameters to the In Application Programming routine
;; ; and for receiving the result.  See the Philips LPC2106 manual
;; ; for values for parameters and results.
;; ; WARNING: Interrupts should be disabled by caller.
;; ; WARNING: Do not use this if RAM is started at 0x40000000 rather than
;; ;          at 0x40000200.
;; IAP:
;;         mov r1, TOS   ; 5-word table address used for both in and out
;;         bl jump_to_IAP
;;         drop
;;         nxt
;; jump_to_IAP:        
;;         ldr r2, = 0x7ffffff1   ; entry point (odd because it is Thumb code)
;;         bx r2                  ; call IAP
        
;;; Stack primitives
;;;; label DUP is Forth word DUP ( x - x x)
DUP:
        dup
        nxt
 
;;;; label SWAP is Forth word SWAP ( a b - b a)
SWAP:
        ldr TEMPREG, [DSTK]
        str TOS, [DSTK]
        mov TOS, TEMPREG
        nxt

;;;; label DROP is Forth word DROP ( a -)
DROP:
        drop
        nxt
        
;;;; label twoDROP is Forth word 2DROP ( a b -)
twoDROP:
        add DSTK, DSTK, #4
        drop
        nxt

;;;; label threeDROP is Forth word 3DROP ( a b c -)
threeDROP:
        add DSTK, DSTK, #8
        drop
        nxt
        
;;;; label fourDROP is Forth word 4DROP ( a b c d -)
fourDROP:
        add DSTK, DSTK, #12
        drop
        nxt
        
;;;; label NIP is Forth word NIP ( a b - b)
NIP:       ; ( a b - b)
        nip
        nxt

;;;; label PUSH is Forth word PUSH ( n -)
PUSH:   
        push
        nxt
        
;;;; label twoPUSH is Forth word 2PUSH ( n n -)
twoPUSH:   
        push
        push
        nxt
        
;;;; label POP is Forth word POP ( - n)
POP:
        pop
        nxt
        
;;;; label twoPOP is Forth word 2POP ( - n n)
twoPOP:
        pop
        pop
        nxt
        
;;;; label Rfetch is Forth word R@  ( - a)
; In this implementation, because we use a dedicated loop count register,
;   R@ and I are not the same word.  R@ accesses the return stack but
;   I accesses the loop count register.
Rfetch:
        dup
        ldr TOS, [RSTK]
        nxt
 
;;;; label twoRfetch is Forth word 2R@  ( - a b)
twoRfetch:
        dup
        ldr TOS, [RSTK]
        dup
        ldr TOS, [RSTK, #4]
        nxt
        
;;;; label I is Forth word I  ( - a)
; In this implementation, because we use a dedicated loop count register,
;   R@ and I are not the same word.  R@ accesses the return stack but
;   I accesses the loop count register.
I:
        dup
        mov TOS, RLOOP
        nxt

;;;; label ROT is Forth word ROT  ( a b c - b c a)
ROT:
        ldmfd DSTK!, {r1, r2}  ; copy a to r2,  copy b to r1,  tos has c
        stmfd DSTK!, {r0, r1}  ; copy b and c back to physical stack
        mov TOS, r2            ; copy a to TOS
        nxt

;;;; label SPfetch is Forth word SP@  ( - dataStkPtr)
SPfetch:
        mov r1, DSTK
        dup
        mov TOS, r1
        nxt

;;;; label RPfetch is Forth word RP@  ( - returnStkPtr)
RPfetch:
        dup
        mov TOS, RSTK
        nxt

;;;; label OVER is Forth word OVER ( a b - a b a)
OVER:
        dup
        ldr TOS, [DSTK, #4]   ; r0 := a
        nxt

;;;; label twoOVER is Forth word 2OVER ( a b c d - a b c d a b)
twoOVER:
        dup                   ; ( a b c d d)
        ldr TOS, [DSTK, #12]  ; r0 := a,  ( a b c d a )
        dup                   ;           ( a b c d a a)
        ldr TOS, [DSTK, #12]  ; r0 := b   ( a b c d a b)
        nxt

;;;; label minusROT is Forth word -ROT ( a b c - c a b)
minusROT:
        dpop2           ; r2=a, r1=b, r0=c
        dup             ; push c to physical stack
        dpush r2        ;  then push a to physical stack
        mov TOS, r1     ;  and put b into TOS
        nxt

;;;; label twoSWAP is Forth word 2SWAP ( a b c d - c d a b)
twoSWAP:
        ldmfd DSTK!, {r1-r3}    ; r3=a, r2=b, r1=c, r0=d
        stmfd DSTK!, {r0-r1}    ; push c, push d
        dpush r3                ; push a
        mov TOS, r2             ; put b into TOS
        nxt

;;;; label twoDUP is Forth word 2DUP  ( a b - a b a b)
twoDUP:
        ldr r1, [DSTK]  ; r1 := a,  TOS (i.e., R0) holds b
        dpush TOS
        dpush r1
        nxt  

;;;; label threeDUP is Forth word 3DUP  ( a b c - a b c a b c)
threeDUP:
        ldr r1, [DSTK]  ; r1 := b,  TOS holds c
        ldr r2, [DSTK, #4]  ; r2 := a
        dpush TOS
        dpush r2
        dpush r1
        nxt  

;;;; label fourDUP is Forth word 4DUP  ( a b c d - a b c d a b c d)
fourDUP:
        ldr r1, [DSTK]  ; r1 := c,  TOS holds d
        ldr r2, [DSTK, #4]  ; r2 := b
        ldr r3, [DSTK, #8]  ; r3 := a
        dpush TOS
        dpush r3
        dpush r2
        dpush r1
        nxt  
                                                   
;;;; label qDUP is Forth word ?DUP  ( 0 - 0)  or  ( nonZero - nonZero nonZero)
qDUP:
        tst TOS, TOS
        it ne
        strne TOS, [DSTK, #-4]!  ; only if TOS is non-zero do we dup it
        nxt

;;; Data access

;;;; label Cfetch is Forth word C@  ( a - c)
Cfetch:     
        ldrb TOS, [TOS]
        nxt

;;;; label fetch is Forth word @   ( a - u)
fetch:      
        ldr TOS, [TOS]
        nxt

;;;; label twoFetch is Forth word 2@  ( a - low32bits high32bits)
twoFetch:
        mov r1, TOS             ; put a into r1
        ldr TOS, [r1, #4]       ; get low32 bits
        dup
        ldr TOS, [r1]           ; get high32 bits
        nxt
        
;;;; label Cstore is Forth word C!   ( c a -)
Cstore:
        dpop r1
        strb r1, [TOS]
        drop            ; refill TOS
        nxt

;;;; label store is Forth word !   ( u a -)
store:
        dpop r1
        str  r1, [TOS]
        drop            ; refill TOS
        nxt

;;;; label twoStore is Forth word 2!   ( low32 high32 a -)
twoStore:
        dpop r1
        str  r1, [TOS]
        dpop r1
        str  r1, [TOS, #4]
        drop            ; refill TOS
        nxt

;;;; label Wfetch is Forth word W@  ( a - unsigned16bits)   (little endian)
Wfetch:     
        ldrh TOS, [TOS]
        nxt

;;;; label Wstore is Forth word W!   ( unsigned16bits a -)   (little endian)
Wstore:
        dpop r1
        strh r1, [TOS]
        drop            ; refill TOS
        nxt

;;; I/O
   
;;;; Note this section contains SUBROUTINES rather than
;;    Forth primitives, i.e., these end with  'mov pc, lr' rather
;;    than with 'nxt'.

;;;; LED

  ;; LED on and off SUBROUTINES reside in the custom-*.asm files.
  ;;   They must be defined there even if defined as no-ops.

;; Subroutine to kill around one second
;;   Used just for blinking the LED.
delay:  
        ldr r1, = 0x00100000    ; delay for about one second at 8 MHz
delay1:
        subs r1, r1, #1
        bne delay1
        mov pc, lr

;; Subroutine to kill around one 1/3 second with an 8 MHz clock
;; Used just for blinking the LED at startup.
delayQ:  
        ldr r1, = 0x00080000
        b delay1

fast:   
        ; flash LED once              
        str lr, [sp, #-4]!  ; push return address onto machine stack
        bl ledOnSub
        bl delayQ
        bl ledOffSub
        bl delayQ
        ldr pc, [sp], #4    ; rts
                  
slow:   
        ; flash LED once              
        str lr, [sp, #-4]!  ; push return address onto machine stack
        bl ledOnSub
        bl delay
        bl ledOffSub
        bl delay
        ldr pc, [sp], #4    ; rts


;;;; Serial port subroutines

;; Since these subroutines are specific to the board and/or mcu
;; family, they should be moved to an include file.

;; To read and write the serial port on the Olimex STM32-P103 board,
;; read status register USART2_SR.  Wait for TXE (bit 7) to go true
;; before writing the new byte, wait for RXNE (bit 5) to go true
;; before reading a new byte.
        
; Subroutine to send the character in r1 to the serial port (usart2).
; Character is still in r1 upon return.  Note, we could load the base
; USART2 address and use [r6, # <offset>] instead to avoid loading r6
; twice (once with the status register and once with the data
; register).

tx:
        ldr r6, = USART2_SR
tdre:   
        ldrb r2, [r6]     ; read status register
        tst r2, # BIT7    ; Wait for transmit data register empty flag TXE (bit 7)
        beq tdre          ;   to go true.
        ldr r6, = USART2_DR
        strb r1, [r6]     ; Write to serial port
        mov pc, lr

; Subroutine to read one character from the second serial port (usart2).
; See earlier comment about loading the base USART2 address.
rx:
        ldr r6, = USART2_SR
rdr:   
        ldrb r1, [r6]
        tst r1, # BIT5      ; Wait for receive data ready flag RXNE (bit 5)
        beq rdr             ;   to go true.
        ldr r6, = USART2_DR
        ldrb r1, [r6]       ; Read character from serial port into r1
        mov pc, lr          ; no, don't echo it, just return
        
        .ltorg  ; force dumping of literal pool


; Subroutine to send CRLF to serial port -- used only by 'greet'
crlf:   
        str lr, [sp, #-4]!  ; push return address onto machine stack
        mov r1, #0x0d   ; carriage return
        bl tx
        mov r1, #0x0a   ; line feed
        bl tx
        ldr pc, [sp], #4    ; rts


        .ltorg  ; force dumping of literal pool

;;;; Serial port Forth words

;;;; label parenSEROUT is Forth word (SEROUT  ( c -)
parenSEROUT:         
        mov r1, r0
        bl tx
        drop
        nxt

;;;; label parenSERINQ is Forth word (SERIN?  ( - f)
; Answer true if a character is waiting in the serial port
parenSERINQ:
        dup
        ldr r6, = USART2_SR
        ldrb TOS, [r6]
        and TOS, BIT5           ; caution, not a canonical flag
        ;; We might use bit-banding instead.  This would would leave
        ;; the flag in bit0, then we could do 'sbc TOS, # 0' to
        ;; produce a canonical flag.  Or, we could shift TOS 4 bits to
        ;; the right, etc.
        nxt
        
;;;; label parenSERIN is Forth word (SERIN  ( - c)
parenSERIN:
        dup
        bl rx
        mov r0, r1
        nxt

;;; Constants

    ;; We should not define constants that might be needed by LOAD
    ;; when building a kernel image.  -1 and -2 should be safe,
    ;; though.

;;;; label minus1 is Forth word -1 ( - -1)
minus1:    
        dup
        mov TOS, # -1
        nxt
;;;; label minus2 is Forth word -2 ( - -2)
minus2:    
        dup
        mov TOS, # -2
        nxt

;;; System parameters

 ;; These words return certain clock-related settings.  They come
 ;; directly or indirectly from equates in the custom-*.asm file.
 ;; Note that they are constants.  If you change the CPU on the fly,
 ;; the values these words return will no longer be correct.

        .equ MSTICKS, (PCLK / 1000) - 10
        ;; adjust it downward slightly to account for loop overhead
;;;; label ticksPerMS is Forth word TICKS/MS ( - u)        
ticksPerMS:     
        ; This depends on PCLK which depends on PCLKDIVISOR and CCLK
        ; Beware that if PCLK is changed on the fly, this will
        ; no longer answer the correct value.
        dup
        ldr TOS, = MSTICKS
        nxt
;;;; label peripheralClock is Forth word PCLK ( - u)        
peripheralClock:     
        dup
        ldr TOS, = PCLK
        nxt
;;;; label cpuClock is Forth word CCLK ( - u)        
cpuClock:     
        dup
        ldr TOS, = CCLK
        nxt
;;;; label busDivisor is Forth word BUS-DIVISOR ( - u)
; ratio of CCLK to PCLK so must be either 1, 2, or 4
busDivisor:     
        dup
        ;ldr TOS, = VPBDIVISOR
        ldr TOS, = PCLKDIVISOR
        nxt
;;;; label spiDivisor is Forth word SPIDIVISOR ( - u)
spiDivisor:     
        dup
        ldr TOS, = SPIDIVISOR
        nxt
;;;; label spiClock is Forth word SPICLK ( - u)
spiClock:     
        dup
        ldr TOS, = SPICLK
        nxt
                
        .ltorg  ; force dumping of literal pool

;;; Math
        
;;;; label Mplus is Forth word M+  ( a b - a+b c)
; Probably no use for this since D+ is in code, but keep it for now.  I
; got the idea for this word from Bill Muench.
Mplus:
        ldr r1, [DSTK]       ; r1 is a,  r0 is b
        adds TOS, TOS, r1    ; Add a and b and set carry flag if carry out
        str  TOS, [DSTK]     ; SOS gets a+b
        eor TOS, TOS, TOS    ; Clear r0
        adc TOS, TOS, TOS    ; Set r0 to 1 if there was a carry.   Is
                             ;  there a way to do above two
                             ;  instructions in one?
        nxt

;;;; label plus is Forth word +  ( a b - a+b)
plus:      
        dpop r1
        add TOS, TOS, r1
        nxt
        
;;;; label Dplus is Forth word D+ ( a b c d - a+c b+d+carry) PUSH SWAP PUSH M+ POP + POP + ; ")
Dplus:
        ldmfd DSTK!, {r1, r2, r3}
               ; r1=a, r2=b, r3=c, TOS=d
        adds r1, r1, r3                 ; r1=a+c
        dpush r1                        ; push lsword
        adc  TOS, TOS, r2               ; TOS=b+d+c  (msword)
        nxt

;;;; label minus is Forth word -  ( a b - a-b)
minus:      
        dpop r1                 ; r1=a, TOS=b
        sub TOS, r1, TOS        ; TOS=a-b
        nxt

;;;; label twoTimes is Forth word 2*  ( a - 2a)
twoTimes:     
        mov TOS, TOS, lsl #1
        nxt

;;;; label twoSlash is Forth word 2/  (a - a/2)  shift right one place, signed
twoSlash:
        mov TOS, TOS, asr #1
        nxt
        
;;;; label U2slash is Forth word U2/  ( a - a/2) shift right one place, unsigned
U2slash:
        mov TOS, TOS, lsr #1
        nxt

;;;; label twofiftysixslash is Forth word 256/  ( u - u/256)
twofiftysixslash:
        ;; unsigned division by 256
        mov TOS, TOS, lsr #8
        nxt
        
;;;; label SPLIT is Forth word SPLIT ( aaaabbbb - 0000bbbb 0000aaaa)  convert 32bit word to two half words
SPLIT:
        mov r1, TOS
        ldr r2, = 0xffff
        and r1, r1, r2
        dpush r1
        mov TOS, TOS, lsr #16
        nxt

;;;; label plusStore is Forth word +! ( n a -)
plusStore:
        dpop r1
        ldr r2, [TOS]
        add r1, r1, r2
        str r1, [TOS]
        drop
        nxt
        
;;;; label plusUNDER is Forth word +UNDER  ( a b n - a+n b)
plusUNDER:
        ldr r1, [DSTK, #4]      ; r1=a,  TOS=n
        add r1, r1, TOS         ; r1=a+n
        dpop TOS                ; TOS=b
        str r1, [DSTK]          ; push a+n
        nxt
                                                                
;;;; label NEGATE is Forth word NEGATE ( n - -n)
NEGATE:
        rsb TOS, TOS, #0    ; TOS := 0 - TOS (i.e., two's complement)
        nxt

;;;; label onePlus is Forth word 1+ ( n - n+1)
onePlus:
        add TOS, TOS, #1
        nxt

;;;; label twoPlus is Forth word 2+ ( n - n+2)
twoPlus:
        add TOS, TOS, #2
        nxt
                                                                
;;;; label oneMinus is Forth word 1- ( n - n-1)
oneMinus:
        sub TOS, TOS, #1
        nxt

;;;; label twoMinus is Forth word 2-  ( n - n-2)
twoMinus:
        sub TOS, TOS, #2
        nxt
                                                                
;;;; label DNEGATE is Forth word DNEGATE  ( d - -d) 
;  ie  ( ls32bits ms32bits -  resultls32bits resultms32bits)
DNEGATE:
  ; TOS contains ms32bits
        ldr r1, [DSTK]          ; r1 := ls32bits
        rsbs r1, r1, #0         ; reverse subtract, i.e., r1 := 0 - r1, setting carry
        ;rsc TOS, TOS, #0        ; reverse subtract with carry
        ;; Thumb-2 does not have an RSC instruction.
        ;; Replace it with the following sbc instruction (from a note on the web)
        sbc TOS, TOS, TOS, lsl #1
        str r1, [DSTK]          ; put ls32bits back on stack
        nxt
        
;;;; label sixtyFourKTimes is Forth word 64K*   ( aaaabbbb - bbbb0000)  -- shift left 16 bits
sixtyFourKTimes:   
        mov TOS, TOS, lsl #16
        nxt

;;;; label sixtyFourKSlash is Forth word 64K/  ( aaaabbbb - 0000aaaa)  -- unsigned shift right 16 bits
sixtyFourKSlash:   
        mov TOS, TOS, lsr #16
        nxt

        .ltorg  ; force dumping of literal pool
        
;;;; label times is Forth word *  ( a b - a*b)
; This is a signed multiply
times:              
        dpop r1
        mov  r2, TOS
        mul TOS, r1, r2
        nxt

;;;; *warning* about umull and smull 
; Per ARM Instruction Set Quick Reference Card,
;        umull r2, r3, TOS, r1
; should put the most significant bits of the product into r2 and 
; the least into r3.  However, what it actually does is put 
; least significant bits into r2 and the most into r3.  Is this
; an error on the reference card or in the assembler?
        
;;;; label UMtimes is Forth word UM*  ( u1 u2 - ud)
UMtimes:
        ldr r1, [DSTK]
        umull r2, r3, TOS, r1   ;  r3:r2 := TOS * r1
        str r2, [DSTK]  ; store ls32bits on stack
        mov TOS, r3     ; TOS := ms32bits
        nxt

;;;; label Mtimes is Forth word M*  ( n1 n2 - d)
Mtimes:
        ldr r1, [DSTK]
        smull r2, r3, TOS, r1   ;  r3:r2 := TOS * r1
        str r2, [DSTK]  ; store ls32bits on stack
        mov TOS, r3     ; TOS := ms32bits
        nxt

;;;; label UslashMOD is Forth word U/MOD ( dividend divisor - uR uQ) 
; Divide 32bits by 32bits with 32bit remainder and 32bit quotient.
; See Patterson & Hennessy, Computer Organization & Design, around
;  pp. 219-221.  This algorithm is a cross between the book's
;  second and third versions.

; Note about how we do a 64-bit shift left.  Is there a better way?
      ; shift dividend (r1:r2) left by one bit
      ; what we would like to do is to shift r2 left then
      ; shift r1 left with carry.  I guess we cannot do
      ; that directly.  So, instead of
      ;       movs r2, r2, lsl #1   ; shift lower 32 bits left
      ;       mov  r1, r1. rolc #1  ;  or whatever
      ; we could use the three-instruction sequence
      ;       movs r2, r2, lsl #1   ; shift lower 32 bits left, remember carry
      ;       mov  r1, r1, lsl #1   ; shift upper 32 bits left
      ;       adc r1, r1, #0        ;  then add in the carry
      ; With a suggestion from Peter on the lpc mailing list on 7 Sep
      ; 2004, we can accomplish it in two instructions if we can also
      ; dedicate a register to holding a zero (in this case r4 holds zero).
      ;       movs r2, r2, lsl #1     ; shift lower 32 bits left, remember carry
      ;       adc  r1, r4, r1, lsl #1 ; shift r1 left then add it with
      ;                               ;  carry to r4, storing into r1

; summary of the algorithm:
         ; Divide   r1:r2  by  r0
         ; For each of the 32 bits,
         ;   shift r1:r2 left
         ;   subtract r0 from r1
         ;   if it "won't go" (i.e., r0 was greater than r1) undo subtraction
         ;      and new quotient bit (lsbit of r2) gets 0
         ;   otherwise
         ;      new quotient bit (lsbit of r2) gets 1
         ; Remainder is in r1 and quotient is in r2
         ; Use r3 to count the iterations
UslashMOD:
     mov r4, #0          ; dedicated zero stays in r4
     ldr r2, [DSTK]      ; dividend goes into r1:r2
     mov r1, #0          ;   (upper 32 bits start off zero)
     mov r3, #32         ; count
1:
      movs r2, r2, lsl #1     ; shift 64-bit 
      adc r1, r4, r1, lsl #1  ;  dividend left 1 bit
      subs r1, r1, TOS   ; trial subtraction to see if divisor "will go" 
      ite hs
      addhs r2, r2, #1   ; (same as addcs) if yes, new quotient bit is '1'
      addlo r1, r1, TOS  ; (same as addcc) if no, leave new quotient bit '0' and undo subtraction
       
      subs r3, r3, #1    ; decrement loop counter
     bne 1b
     str r1, [DSTK]             ; push remainder to stack
     mov TOS, r2                ; store quotient to TOS
     nxt   

;;; Logic
;;;; label AND is Forth word AND ( a b - u)
AND:
        dpop r1
        and TOS, TOS, r1
        nxt

;;;; label OR is Forth word OR ( a b - u)
OR:
        dpop r1
        orr TOS, TOS, r1
        nxt

;;;; label XOR is Forth word XOR ( a b - u)
XOR:
        dpop r1
        eor TOS, TOS, r1
        nxt

;;;; label equal is Forth word =  ( a b - f)
equal:      
        dpop r1
        sub TOS, TOS, r1        ; TOS is zero if a=b
        ; now fall through to NOT to invert the flag
;;;; label NOT is Forth word NOT
;;;; label zeroEqual is Forth word 0=
NOT:    
zeroEqual:
        subs TOS, TOS, #1       ; if zero, carry is set, else carry is clear
        sbc TOS, TOS, TOS       ; subtracting r0 from itself leaves zero if
                                ; carry was clear or -1 if carry was set.
        nxt                     ; U< also uses this trick. 

;;;; label ROR24 is Forth word ROR24  ( abcd - bcda)  rotate right 24 bits, putting msbyte into lsbyte
ROR24:  
        mov TOS, TOS, ror #24      ; put msbyte into lsbyte
        nxt

;;;; label greaterThan is Forth word >  ( a b - f)
greaterThan:
        ldr TEMPREG, [DSTK]
        str TOS, [DSTK]
        mov TOS, TEMPREG
                                ; fall through to lessThan
;;;; label lessThan is Forth word <  ( a b - f)
lessThan:
        dpop r1
        subs TOS, r1, TOS        ; TOS = a-b  -- msbit set if a is less than b
        mov TOS, TOS, asr #31    ; turn msbit into 0xffff or 0x0000
        nxt
        ldr TEMPREG, [DSTK]
        str TOS, [DSTK]
        mov TOS, TEMPREG

;;;; label zeroGreaterThan is Forth word 0>  ( n - f)        
zeroGreaterThan:
        ldr TEMPREG, [DSTK]
        str TOS, [DSTK]
        mov TOS, TEMPREG

        ; fall through to zeroLessThan
;;;; label zeroLessThan is Forth word 0<  ( n - f)        
zeroLessThan:
        mov TOS, TOS, asr #31    ; turn msbit into 0xffff or 0x0000
        nxt

;;;; label UgreaterThan is Forth word U>  ( a b - f)
UgreaterThan:
        ldr TEMPREG, [DSTK]
        str TOS, [DSTK]
        mov TOS, TEMPREG
        
        ; fall through to UlessThan
;;;; label UlessThan is Forth word U<  ( a b - f)   ** like <  but we use carry rather than msbit for flag
UlessThan:
    ; U<  uses the Robert Berkey trick whereby subtracting sets the  
    ;   carry and then subtracting the difference from itself leaves
    ;   zero if carry was clear or -1 if carry was set.
        dpop r1
        subs TOS, r1, TOS      ; TOS = a-b  -- carry set if a is less than b
        sbc TOS, TOS, TOS
        nxt
        
;;; Control Flow primitives
        
;;;; FOR ... NEXT
;  This begins with a 2-byte xt for 'for' followed by the 2-byte offset
;  (at A) of the location of the terminating 'next'.  This is followed
;  by the body of the loop (at B).  It ends with the 2-byte
;  xt for 'next' followed by the 2-byte offset (at C) of the beginning
;  of the body of the loop.
; 
;       [for][A ][B .....][next][C ]
;        
;  We cache the loop counter into the RLOOP register to make 'I' and
;  decrementing/testing the loop counter faster.  Note, this means
;  that 'I' and 'R@' are not the same word in this implementation.
                
;;;; for/next runtimes  FOR ... NEXT loop   ( # -)
;;;;; label for is Forth word for ( # -)
for:
    rpush RLOOP         ; save previous loop count onto return stack
    mov RLOOP, TOS      ; put loop count into RLOOP
    drop                ; refill TOS
    ldrh r1, [IPTR], #2   ; put 16-bit offset into r1 and bump IPTR
    add IPTR, IPTR, r1    ;  advance IPTR to skip over the body of the loop
                          ;  and go to the xt of 'next'
    nxt

;;;;; label next is Forth word next
next:
        ; Decrement loop counter.  If it doesn't go negative, then
        ;   stuff IPTR with address of loop body (so we'll repeat the loop).
        ;   If it does go negative then we have finished, so clean up.
        ldrsh r1, [IPTR], #2  ; get signed 16-bit offset back to start of loop
                            ;  and advance IPTR past the offset.  If loop is
                            ;  finished, we leave IPTR pointing to the xt 
                            ;  following 'next'.  If loop is not finished, we
                            ;  add the offset to IPTR to cause a jump back to
                            ;  the beginning of the loop body.
        subs RLOOP, RLOOP, #1   ; decrement loop counter
        ite pl
        addpl IPTR, IPTR, r1    ; if loop count is not negative, bump IPTR, 
                                ; and add offset to IPTR to go back
                                ; to beginning of loop body.
        ldrmi RLOOP, [RSTK], #4   ; if loop count is negative, rpop RLOOP
        
        nxt

;;;; label zeroBranch is Forth word 0branch        
zeroBranch:     
; An IF lays down the 16-bit xt for 0branch followed by a 16-bit signed
;  offset that should be added to IPTR if TOS is zero.
        tst TOS, TOS
        drop
        ldrsh r1, [IPTR], #2  ; always get signed 16-bit offset and bump IPTR past it
        ; execute next instruction only if TOS was zero
        it eq
        addeq IPTR, IPTR, r1    ; but also add offset to IPTR only if Z flag is true
        nxt

;;;; label branch is Forth word branch        
branch:     
; The branch 16-bit xt is followed by a 16-bit signed
;  offset that should be added to IPTR
        ldrsh r1, [IPTR], #2  ; get signed 16-bit offset and bump IPTR past it
        add IPTR, IPTR, r1      ;   add offset to IPTR
        nxt
        
;;; Strings, Variables, Literals

;;;; label lit16 is Forth word lit16 ( - n)
; An in-line 16-bit literal takes 2 bytes for the lit16 xt followed
; by a signed half word, for a total of 4 bytes.
lit16:  
        dup                     ; make room on the stack
        ldrsh TOS, [IPTR], #2   ; get signed 16-bit literal and bump IPTR
        nxt
        
;;;; label lit32 is Forth word lit32 ( - n)
lit32:
        ;; Here is a version of lit32 that requires the 32-bit data to
        ;;  be aligned on a 32-bit boundary (which may require that the
        ;;  compiler insert a NOP)
        dup                        ; make room on the stack
        ldr TOS, [IPTR], #4
        nxt

;;; quoting strings

; The 16-bit xt for quote is followed by a one-byte length followed by
; the string.  When the compiler lays down the string, it adds a
; padding byte if necessary to leave the next address aligned to a
; two-byte boundary.  'quote' pushes the address of the count byte
; onto the data stack and advances IPTR past the string.  quote1 is a
; subroutine used by quote and by abortquote.

;;;; quote1 is a helper subroutine.
quote1:
     ;; Push address of string (address of string's count byte) to data stack
     ;; and move IPTR past the string.  Also skip past an extra byte if 
     ;; necessary, so that IPTR is aligned to a half-word (an even address)
        dup                ; make room on the data stack
        ldrb r1, [IPTR]    ; pick up the count byte
        mov TOS, IPTR      ; address of count byte to TOS
        add IPTR, TOS, r1  ; bump IPTR past the string
        add IPTR, IPTR, #2 ; bump IPTR past the count byte and one more in case it was odd
        bic IPTR, IPTR, #1 ;   then optionally round back to an even address.
        mov PC, lr

;;;; label quote is Forth word quote ( - a)   in-line string
quote:  
        bl quote1       ; get address of string on the stack and bump IPTR past string
        nxt
        
;;;; label abortquote is Forth word abortquote ( f -)  in-line string
abortquote:  
        ; If flag is false, skip past string and do not call ABORT.
        ; Else, put address of string on stack and call ABORT.
        tst TOS, TOS
        drop
        bl quote1  ; skip past string and put its address on stack in case we need it
        bne 1f     ; 
        ; Flag was zero, so no error.  Drop string address and continue after string.
        drop
        nxt
1:      ; Flag was not zero, so handle the error, passing string address on data stack.
        ldr IPTR, = abortSlot
        ldr IPTR, [IPTR]
        nxt

;;; Multitasking -- task and TCB accessing words

;;;; label TERMINAL is Forth word TERMINAL ( - a)
;;;; label TERMINAL is Forth word FOREGROUND ( - a)
TERMINAL:
        ; return the address of the TERMINAL's task control block
        dup
        ldr TOS, = foreground
        nxt

;;;; label bg1 is Forth word TASK1 ( - a)
bg1:
        ; return the address of the task1's task control block
        dup
        ldr TOS, = task1
        nxt

;;;; label bg2 is Forth word TASK2 ( - a)
bg2:
        ; return the address of the task2's task control block
        dup
        ldr TOS, = task2
        nxt

;;; Following words return addresses relative to the current task.
    ;; register UP holds the address of the task control block (TCB)
    ;; for the currently active task.

;;;; label SP0 is Forth word SP0 ( - a)  
;    Answer address of current task initial data stack pointer
SP0:
        dup
        mov TOS, UP
        add TOS, TOS, # 0x18
        nxt

;;;; label RP0 is Forth word RP0 ( - a)  
;    Answer address of current task initial return stack pointer
RP0:
        dup
        mov TOS, UP
        add TOS, TOS, # 0x1C
        nxt

;;;; label LINK is Forth word LINK ( - a)  
;    Answer address of current task's task control block, i.e., this
;    task's address.  The value stored at this address is the address
;    of the next task's task control block.  This is where we link to
;    the next task.
LINK:
        dup
        mov TOS, UP
        nxt

;;;; label PAUSE is Forth word PAUSE ( -)
PAUSE:

        ;; UP points to the start of the current task's task control block,
        ;; i.e., it points to the current task's LINK field.  The LINK
        ;; field holds the address of the next task to be given control
        ;; when the current task PAUSEs.
        
        ;; In the ARM instruction set, we used stmfa/stmib and ldmfa/ldmda
        ;; to save and restore the task's context.
        
        ;; Thumb-2 does not support those stm/ldm instructions so we
        ;; use stmia and ldmdb plus some extra add and sub
        ;; instructions.
        
        ;; These are the registers that are saved and restored.
        ;;    TOS    == r0
        ;;    IPTR   == r9
        ;;    DSTK   == r10
        ;;    RSTK   == r11
        ;;    RLOOP  == r12

        ;; Save the current task's context immediately after the LINK field
        ;; UP currently points to the LINK field
        add UP, # 4                ; advance UP to point just past the LINK field
        stmia UP, {TOS, IPTR, DSTK, RSTK, RLOOP}   ; save current context

        ;; point UP to the new task
        ldr UP, [UP, # -4]                         ; load UP with next task's TCB

        ;; restore the new task's context
        add UP, # 24           ; point UP to just past the top of save area
        ldmdb UP, {TOS, IPTR, DSTK, RSTK, RLOOP}  ; restore new task's context, do not update UP
        sub UP, # 24                              ; point UP at the new task's LINK field

        nxt

;;; Application start up

        .align                  ; boot must be on a full-word boundary
boot:   .word 0                 ; compiler will fill this in


runboot:   
        ;; set up HERE to original kernel location
        ldr r1, pfreeram
        ldr r2, = h
        str r1, [r2]
        ; The location 'boot' above is in flash and was set when the kernel
        ; was generated.
        ldr     IPTR, boot
        
        nxt
        
;;; The purpose of COLD is to allow the user on the host to
;;; interactively restart as much of the target as possible without
;;; actually pressing (or being able to press) a reset button.  If we
;;; later add a monitor or loader below the Forth, then we would jump
;;; to the start of the monitor.  Note that since the user on the host
;;; has requested the COLD restart, it is likely expecting an ok
;;; message so the target should send that first.  The word COLD is
;;; not intended to be compiled or used in an application.


;;; label COLD is Forth word COLD ( -)
;;; label RESET is Forth word RESET ( -)
 ;; (use whichever command you prefer)
COLD:   
RESET:
        ;; We are connected to the host and the user has typed COLD
        ;; interactively.  We send back the expected ok message then
        ;; restart.  This trims back the dictionary to the original
        ;; kernel.
        ldr r3, = okMsg
        bl sendCommandCode
        b _start


;;; ;;;;;;;;;;;;;;;;;;;;;;;;; System ;;;;;;;;;;;;;;;;;;;;;;
;; System words
        
;;; label dp is Forth word H  ( - a)
dp:
        ;; Return the address where the dictionary pointer is stored.
        ;; The Forth user probably should not use this word ( H ), but
	;; the host-side needs it so the value of H can be altered,
	;; e.g., when RELOADing.
        dup
        ldr     TOS, = h
        nxt

;;; label tickAbort is Forth word 'ABORT  ( - a)
tickAbort:
        ;; ABORT is a deferred word.  The word 'ABORT holds the address of the
        ;; word that ABORT will execute.  This address is in RAM to make it
        ;; easy for testing.
        dup
        ldr     TOS, = abortSlot
        nxt

;;; label RPstore is Forth word RP! ( -)  reload the return stack pointer
RPstore: 
        ldr     RSTK, [UP, #0x1C]
        nxt
;;; label SPstore is Forth word SP! ( -)  reload the data stack pointer
SPstore: 
        ldr     DSTK, [UP, #0x18]
        nxt


;;; ;;;;;;;;;;;;;;; Compiler/Interpreter Main Loop ;;;;;;;;;;;;;;;;;;;

    ;; Well, not exactly the main loop.  The main loop is the
    ;; high-level word QUIT, which calls queryinterpret.
       
;;;; label queryinterpret is Forth word queryinterpret ( -)
queryinterpret:
        ;; This word does more or less what a separate QUERY INTERPRET
        ;; would have done in a monolithic Forth.  Since the "query"
        ;; part sets some flags in registers (e.g., I versus C) that
        ;; are used by the "interpret" part, we probably should not
        ;; break them into separate words.

        ;; Collect a message from the host then process it.

        ;; We might wish to add a timeout a mechanism so that if we
        ;; are in the middle of receiving a packet and the packet
        ;; stops arriving, we can start over waiting for the start of
        ;; the next packet.  The lack of ack will signal the host that
        ;; we did not get the packet.

        ;; The top of the dictionary (at HERE) provides the buffer
        ;; where the incoming compiled code is placed.  As the message
        ;; is received and stored at HERE, we accumulate the checksum
        ;; and remember whether this is an 'I' or a 'C' message.

        ;;  ARM register usage within queryinterpret:
        ;;   R0 caches TOS (as always)
        ;;   R1 used by 'rx'
        ;;   R2 accumulates checksum
        ;;   R3 holds count of remaining bytes to receive
        ;;   R4 pointer to buffer
        ;;   R5 message type (0 == 'I', 1 == 'C')
        ;;   R6 used by 'rx'
        
        ldr r4, = h             ; initial buffer pointer for receiving message from host
        ldr r4, [r4]

        ldr r2, = 0             ; initialize checksum
        ldr r5, = 0             ; assume message will be an 'I' packet
        
getPacketStart:
        bl rx
        add r2, r2, r1          ; update checksum
checkForC:      
        cmp r1, # 'C
        bne checkForI
        ldr r5, = 1             ; note we have a 'C' packet
        b collectPacket
        
checkForI:
        cmp r1, # 'I
        bne queryinterpret      ; If we got an 'I' packet, fall through to collectPacket,
                                ;  otherwise ignore the character and keep looking for
                                ;  the beginning of a packet.
        
collectPacket:
        ;; At this point, we have received a valid start-of-packet
	;; character, either an I or a C.  We have set R5 to 0 if it
	;; is I and to 1 if it is C.  Next we receive a byte to
	;; represent the length of the data field of the packet.
        bl rx                   ; get length byte
        add r2, r2, r1          ; update checksum
        movs r3, r1             ; initialize count register R3 and set flags
        beq queryinterpret      ; do not allow a zero-length data field

collectData:
        ;; Then we receive length (R3) bytes of data to put in the
        ;; dictionary, then the checksum byte.
        bl rx                   ; get data byte
        add r2, r2, r1          ; update checksum
        strb r1, [r4], # 1      ; store it in the dictionary and advance pointer
        subs r3, r3, # 1        ; decrement count to see if we are finished yet
        bne collectData

checkCheckSum:  
        ;; finally, collect the checksum byte
        bl rx 
        add r2, r2, r1         ; update checksum and set flags
        ands r2, r2, # 0xFF    ; isolate the lsbyte
        bne queryinterpret     ; if checksum is not zero, then drop packet silently

processPacket:  
        ;; At this, we have received the packet successfully (thus freeing R3).
        ;; (As with the USB protocol, if we did not get a good packet, we stay
        ;;  silent and wait for the host to send it again.)
        ldr r3, = ackMsg
        bl sendCommandCode

        ;; What we do next depends upon whether this is an I packet or a C packet.
        ;; R5 is zero if this is an I packet
        subs r5, r5, # 1        ; if R5 is zero, it was a C packet
        bne processI

processC:
        ;; We are compiling.  The data field has already been stored
        ;; into the dictionary, extending it.  R4 now points just past
        ;; this new data.  Update H and we are done.  'nxt' returns to
        ;; the high-level QUIT which will once again call
        ;; 'queryinterpret'.
        ldr r3, = h
        str r4, [r3]  ; update h to point just past the new end of dictionary
        ldr r2, = 0          ; false flag means we should not send an 'ok' message.
        str r2, [sp, #-4]!   ; push false flag to hw stack
        nxt

processI:       
        ;; We are interpreting.  'h' points to the start of the code
        ;; to be executed.  We do not need to change H as this is just
        ;; a temporary extension of the dictionary.

        ;; Load 'h' into IPTR and start executing the temporary code
        ;; as if it were a Forth word.  Because we are about to
        ;; interpret the buffer as a high-level word, we must nest
        ;; down by pushing the current IPTR before loading it from
        ;; 'h'.  See nxttab

        str IPTR, [RSTK, #-4]!    ; push IPTR to return stack
        ldr IPTR, = h
        ldr IPTR, [IPTR]

        ldr r2, = -1         ; true flag means we must send an 'ok' message.
        str r2, [sp, #-4]!   ; push true flag to hw stack
        nxt
        
;;; label qOK is Forth word ?ok  ( -)
qOK:
        ;; This form of ok expects a flag on the *hardware* stack.  If
        ;; the flag is true, send an 'ok' message back to the host.
        ;; This is used in high-level QUIT to signal the end of
        ;; interpreting a string.
 
        ;; If the flag is true, send a message to the host letting it
        ;; know we have finished.  This is used for pacing (plus
        ;; providing a comforting message to the user).
        ldr r2, [sp], #4         ; retrieve flag from hw stack
        tst r2, r2               ; set CPSR based on the flag
        beq 1f                   ; if flag was zero, skip the 'ok' message
        ldr r3, = okMsg
        bl sendCommandCode      ; send 'ok' message
1:
        nxt

        
;;; ;;;;;;;;;;;;;;;;;;;;;;;;; I/O ;;;;;;;;;;;;;;;;;;;;;;
;; I/O words that offload most of the work to the host


;;; Two-byte command codes
        ;; The first byte is always a colon so we only
        ;; define the second byte.  See the subroutine 'sendCommandCode'.

        .equ ackMsg,     'k
        .equ okMsg,      'o
        .equ numberMsg,  'n
        .equ dotMsg,     '.
        .equ dotrMsg,    'r
        .equ udotMsg,    'U
        .equ udotrMsg,   'R
        .equ typeMsg,    'T
        .equ emitMsg,    'E
        .equ decimalMsg, 'd
        .equ hexMsg,     'h
        .equ stringMsg,  's
        
;;; sendCommandCode is a subroutine
sendCommandCode:
        ;; Transmit a two-byte command code to the host.  The first byte
        ;; is always a colon, so it is hard coded.  The second byte arrives
        ;; from the caller in R3.
        str lr, [sp, #-4]! ; push return address onto machine stack
        mov r1, # ':       ; put first character (always a colon) into R1
        bl tx              ; transmit first character to the host
        mov r1, r3         ; get second character into R1
        bl tx              ; transmit second character to the host
        ldr pc, [sp], #4   ; rts

;;; sendString
sendString:

        ;; 'sendString' is a subroutine.  It sends a string to the
        ;; host.  It expects an address and count on the data stack and it
        ;; removes them.

        str lr, [sp, #-4]!    ; push return address onto machine stack

        ldr r3, = stringMsg
        bl sendCommandCode    ; tell the host we are going to send it a string

        mov r1, TOS
        bl tx             ; send the length byte

        dpop r3           ; get the address into R3, count is still in TOS
        tst TOS, TOS
        beq ssexit        ; if count is zero, then get out

        ;; Otherwise, send the string to the host.
        ;; Count is in TOS, string address is in R3.
ssloop: 
        ldr r1, [r3], #1   ; get next character into R1 and advance R3
        bl tx              ; transmit character to the host
        subs TOS, TOS, #1  ; decrement count to see if we are finished
        bne ssloop         ; if TOS is now zero, we are finished
ssexit: 
        drop               ; refill TOS to leave stack clean
        ldr pc, [sp], #4   ; rts
        

;;; numbersub is a subroutine
        ;; It is also called by the primitive at numberw: (the Forth word number).
numbersub:
        ;; This subroutine pops a number from the data stack and sends it
        ;; to the host, msbyte first.
        str lr, [sp, #-4]!  ; push return address onto machine stack

        ldr r3, = numberMsg
        bl sendCommandCode
        
        mov r1, TOS
        mov r3, #4
1:
        mov r1, r1, ror #24      ; put msbyte into lsbyte
        bl tx
        subs r3, r3, #1
        bne 1b
        drop
        ldr pc, [sp], #4    ; rts

;;; label number is Forth word number ( n -)
number:
        bl numbersub
        nxt
        
;;; label dot is Forth word .   ( n -)
dot:
        ;; print a signed number
        bl numbersub            ; send the number to the host (with a number message)
        ldr r3, = dotMsg
        bl sendCommandCode
        nxt
        

;;; label dotR is Forth word .R   ( n # - )
dotR:
        ;; print a signed number right-justified in a fixed width field
        ldr TEMPREG, [DSTK]
        str TOS, [DSTK]
        mov TOS, TEMPREG
        
        bl numbersub            ; send the number
        bl numbersub            ; send the field width
        ldr r3, = dotrMsg
        bl sendCommandCode
        nxt
        
;;; label Udot is Forth word U.   ( u - )
Udot:
        ;; print an unsigned number
        bl numbersub
        ldr r3, = udotMsg
        bl sendCommandCode
        nxt
        
;;; label UdotR is Forth word U.R   ( u # - )
UdotR:
        ;; print an unsigned number right-justified in a fixed width field
        ldr TEMPREG, [DSTK]
        str TOS, [DSTK]
        mov TOS, TEMPREG
        
        bl numbersub            ; send the number
        bl numbersub            ; send the field width
        ldr r3, = udotrMsg
        bl sendCommandCode
        nxt

;;; label COUNT is Forth word COUNT ( a - a+1 c)
COUNT:  
        mov r1, TOS             
        ldrb TOS, [r1], #1      ; read byte into TOS and bump address in r1
        dpush r1                ; push incremented address to SOS
        nxt
        
;;; label TYPE is Forth word TYPE   ( a c - )
        ;; Given an address and count of a string, send the string to the
        ;;  host (with a "string" message) (the host pushes the string to
        ;;  the host's data stack).  Then send a command code to the host
        ;;  to ask it to TYPE the string.
TYPE:
        bl sendString           ; stack is now  (  - )
        ldr r3, = typeMsg
        bl sendCommandCode
        nxt
        
;;; label EMIT is Forth word EMIT   ( c - )
EMIT:
        ;; Send character to host to be displayed
        bl numbersub
        ldr r3, = emitMsg
        bl sendCommandCode
        nxt
        
;;; label DECIMAL is Forth word DECIMAL   ( - )
DECIMAL:
        ldr r3, = decimalMsg
        bl sendCommandCode
        nxt
        
;;; label HEX is Forth word HEX   ( - )
HEX:
        ldr r3, = hexMsg
        bl sendCommandCode
        nxt

;;; LED on and off
        ;; The custom-*.asm file (e.g., custom-lpc2294.asm) is
        ;; responsible for defining subroutines named ledOnSub and
        ;; ledOffSub, even if they do nothing.

        
;;;; label ledOn is Forth word ledOn ( -)
ledOn:
        bl ledOnSub
        nxt
;;;; label ledOff is Forth word ledOff ( -)
ledOff:
        bl ledOffSub
        nxt

        
prim_cutoff:       
        ; Any Forth words before this point must be primitives.
        ; Any Forth words after this point must be high-level.
        ; This is used by EXECUTE.

        .ltorg  ; force dumping of literal pool

_dummy:                        ; if any int gets triggered, just hang in a loop
_nmi_handler:
_hard_fault:
_memory_fault:
_bus_fault:
_usage_fault:
        add r0, 1
        add r1, 1
        b _dummy
        
        .align
endOfDictionary: .word . + 4

;;; Stacks
.section .ram
        ;  We place the stacks in low RAM so we don't need to adjust
        ;  this part for chips with different amounts of RAM.  On the
        ;  other hand, perhaps we should use a variable defined in
        ;  the link file.

        ;  'dstk' stands for "data stack".  'rstk' stands for "return
        ;  stack".  'mstk' stands for "machine stack".

;;; Variables
        ;; These are the variables that the primitives need to know
        ;; about.  Other variables can be declared in the high-level
        ;; Forth with VARIABLE.
        
h:          .skip 4     ; dictionary pointer is stored here
abortSlot:  .skip 4     ; vector for ABORT (i.e., the word that abortquote executes for ABORT)

        
;;;; RTOKENS is the lookup table for Forth words defined in RAM
        ;; the address of this label is also stored at prtokens (in the parms
        ;; table near the beginning of Flash).  By default, we allow for up
        ;; to 64 entries.
RTOKENS:
              .skip (4 * 64)   ; allow up to 64 entries in RAM token table

;;; Multitasking (tasks, i.e., TCBs, reside in RAM)

        ;; A task is represented by an 8-slot task control
        ;; block (TCB) in RAM.
        
        ;; UP (User Pointer) holds the address of the current task's
        ;; TCB, which is also the address of the task's link field.
        ;; The link field contains the address of the next task to
        ;; run.

        ;; Rather than saving most of the context to either the data
        ;; or return stack and then saving just that one register, we
        ;; take advantage of the ARM's store multiple instruction.
        ;; Note that the fields in the save area must correspond to
        ;; the order of the registers from low to high.  E.g., TOS
        ;; (which saves R0) must come before IPTR (which saves R9).

        ;; Each TCB contains 8 slots (32 bytes).  The addresses
        ;; relative to the start of the TCB (and thus relative to the
        ;; value in UP) are

        ;;    +    0     LINK   holds the address of the next task to execute
        ;;    +    4            holds saved TOS
        ;;    +    8            holds saved IP
        ;;    + 0x0C          holds saved DSTK
        ;;    + 0x10          holds saved RSTK
        ;;    + 0x14          holds saved RLOOP
        ;;    + 0x18   SP0    holds address of start of data stack
        ;;    + 0x1C   RP0    holds address of start of return stack
        ;;  the task's return stack goes here (at offset 0x20)
        ;;  the task's data stack goes here (just above the return stack)

foreground:    .skip 32        ; Task control block (i.e., save area)
                               ;  for foreground task.  Room for the 8 slots.
rstklimit:     .skip 0x80      ; $80 bytes (32 items) for return stack
rstk: 
dstklimit:     .skip 0x80      ; $80 bytes (32 items) for data stack
dstk:
               .skip 8         ; firebreak against stack underflow

task1:         .skip 32        ; Task control block (i.e., save area)
                               ;  for background task1.  Room for the 8 slots.
rstklimit1:    .skip 0x80      ; $20 bytes (8 items) for return stack
rstk1: 
dstklimit1:    .skip 0x80      ; $40 bytes (16 items) for data stack
dstk1:
               .skip 8         ; firebreak against stack underflow

task2:         .skip 32        ; Task control block (i.e., save area)
                               ;  for background task1.  Room for the 8 slots.
rstklimit2:    .skip 0x80      ; $20 bytes (8 items) for return stack
rstk2: 
dstklimit2:    .skip 0x80      ; $40 bytes (16 items) for data stack
dstk2:

; We might prefer to set up linker variables for mstklimit and mstk
; and place the hardware stack at top of RAM (which will vary from one
; chip to another).  For now, put the hardware stack here.
mstklimit:    .skip 0x100     ; $100 bytes (64 items) for hardware stack
mstk:
freeRAM:                
                        
        .end
