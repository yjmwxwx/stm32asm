( block 0  )

This block file, kernel.fth, is used to create a target image when
starting riscy.tcl this way:

    ./riscy.tcl -flash 1

(normally, though, that would be done by the makefile)

It will then load block 1 (in this file), which is the load 
block that will load other blocks.

Finally, at some point, SAVE-IMAGE must be executed in order
to save the results to the *.bin and *.dictionary files, 
e.g.,

    SAVE-IMAGE kernel INIT

would save the results to the files kernel.bin and 
kernel.dictionary and set the boot word to INIT

Take a close look at block 1.  It may need editing for your
particular ARM variant.  For example, for the LPC series of
chips, block 8 is loaded and block 7 is commented out, and 
vice versa for the STM32 Cortex chips.


( shadow 0 )

( block 1  load block to create the kernel image  )

2 LOAD   ( QUIT (ABORT INIT  )

3 LOAD   ( S .CR .H etc )

4 LOAD   ( comparisons)
5 LOAD   ( math)
6 LOAD   ( CMOVE etc)

7 LOAD   ( Timing for STM32 Cortex )
( 8 LOAD   ( Timing for LPCxxxx - including Cortex )

9 LOAD   ( DUMP DU)

10 11 THRU   ( multitasker)

SAVE-IMAGE kernel INIT

( shadow 1 )

( block 2   QUIT  (ABORT  INIT )

: QUIT ( -) RP! BEGIN PAUSE (SERIN? UNTIL  queryinterpret ( f) ?ok  QUIT ;

: (ABORT ( a -)  COUNT TYPE  SP!  ?ok  QUIT  ;

: INIT ( -) ' (ABORT  'ABORT  !  QUIT  ;

( shadow 2 )

load block for creating the flash image for Riscy Pygness

The ";;" after QUIT is defined switches back to interpret mode so the
additional blocks can be loaded.

The last line on the block saves the image to the names kernel.bin and
kernel.dictionary, while setting that the "boot" or startup word will be
QUIT. 

When controlled by the makefile, the image files will be renamed
appropriately for the specific ARM variant, such as kernel-lpc2106.bin
and kernel-lpc2106.dictionary.


( block 3  miscellaneous)

: .S ( -)  ROT DUP . ROT DUP . ROT DUP .  ;
: CR ( -)   $0D EMIT  $0A EMIT  ;

: .H  ( u -)  HEX U. DECIMAL  ;

: ?  ( a -)  @ . ;


: BL ( - c)  $20  ;
: SPACE ( -)  BL EMIT  ;
: SPACES ( # -)  FOR  SPACE  NEXT  ;

: BYTES ( aabb - bb aa)  DUP $FF AND  SWAP 256/  ;

( : CMOVE ( fr to # -)
(  BYTES ( fr to ls# ms#)    ( SWAP PUSH )
  ( fr to ms#)    ( FOR  2DUP 256 (CMOVE  256 +  256 +UNDER  NEXT )
  ( fr to)   ( POP ?DUP IF (CMOVE ; THEN  2DROP  ;  )



( shadow 3 )
CMOVE ( fr to # -)

 Split the count into ms# full 256-byte moves then a final ls# byte move
 if ls# is not zero.

( block 4   comparisons )

: 0<> ( n - f)   0= NOT  ;

( n is BETWEEN low and high iff y is WITHIN low and high+1 )
: BETWEEN ( n l h - f) 1+  ( fall through )                     
: WITHIN ( n l h - f) OVER - PUSH - POP U< ;

( shadow 4 )

( block 5   math )

: ABS DUP 0< IF NEGATE ; THEN ;                                 
: MAX 2DUP < IF SWAP THEN DROP ;                                
: MIN 2DUP > IF SWAP THEN DROP ;

( Note that MOD is really UMOD )
: MOD  ( a b - r)  U/MOD DROP  ;
 
: U/ ( a b - q)  U/MOD NIP   ; 

( Signed division.  Remember the sign, do an unsigned divide, )
(  finally, apply the correct sign to the result.             )
: /  ( n n - n) 
  SWAP DUP 0< PUSH ABS   
  SWAP DUP 0< PUSH ABS  ( u u) 
  U/   POP POP XOR IF NEGATE THEN  ; 

( shadow 5   math )


( block 6  CMOVE  FILL etc)

( CMOVE>  move bytes from high end of buffer so buffers can overlap.)
(         This needs to be rewritten as a primitive. )
: CMOVE> ( fr to #)  ( PAUSE )
  PUSH R@ +UNDER  R@ + 
  POP FOR ( fr to)  -1 +UNDER 1-  OVER C@ OVER C! NEXT 
  2DROP  ;

: CMOVE ( fr to # -)  ( PAUSE)
  ( Later, rewrite as a fast primitive based on ARM's load and )
  ( store multiple instructions.)
  FOR ( from to) OVER C@  OVER C!  1 +UNDER 1+  NEXT  2DROP  ;


: FILL ( a # c -) SWAP DUP 0= IF 3DROP ;  THEN 
  PUSH ( a c) OVER C! DUP 1+ POP 1- CMOVE  ; 
: BLANK ( a # -) BL FILL  ; 
: ERASE ( a # -)  0 FILL  ;


( shadow 6 )

( block 7  Timing for STM32 Cortex M3 )

: 1ms ( -) 
  STK_VAL @  TICKS/MS  ( init delay) 2DUP ( curr delay) U< 
  IF ( current count is already U< than desired delay)
     ( wait for current count to become not U< than desired delay)
    BEGIN ( init delay) PAUSE STK_VAL @ OVER U< NOT UNTIL
  THEN
  ( init delay) - $FFFFFF AND ( goal)
  BEGIN ( goal) PAUSE DUP STK_VAL @ U> UNTIL DROP  ;

: MS ( # -) FOR  1ms  NEXT  ;

( shadow 7  Timing for LPCxxx -- including Cortex )

1ms ( -)
  Kill one milliseconds (while running PAUSE so the other
  tasks can continue to run.

MS ( # -)
  Kill the requested number of milliseconds.


( block 8  Timing for LPCxxxx - including Cortex M3 )

: T1@ ( - u)  T1TC @  ;  ( read the timer )

: MS ( # -)
  ( This is very accurate but is only good to about
    1165000 milliseconds, when PCLK is 3,686,400 Hz,
    i.e. about 19 minutes. )
  T1@ ( originalTimer)
  SWAP TICKS/MS * +  ( goal) 
  BEGIN PAUSE T1@ OVER U> UNTIL DROP  ;

( shadow 8  Timing for STM32 Cortex M3 )

MS ( # -)
  Kill the requested number of milliseconds.


( block 9   DUMP )

: DUMP ( a - a') 
  HEX  CR   DUP 5 U.R  ( 2 SPACES) 
  DUP  2 FOR ( a a) 2 SPACES  8 FOR DUP C@ 3 U.R  1+ NEXT  SPACE  NEXT DROP 
  ( a) 2 FOR 2 SPACES  8 FOR 
        DUP C@  DUP 32 127 WITHIN NOT IF DROP 46 THEN EMIT 1+ 
        NEXT  SPACE 
  NEXT   DECIMAL ; 
 
: DU ( a n -) FOR DUMP ( ?SCROLL)  NEXT  DROP ; 
                                                                

( shadow 9   DUMP )

Unlike the usual Pygmy version of DUMP, Riscy Pygness does not save and
restore the base.  It always leaves the base set to DECIMAL.


( block 10  Multitasker   )

: LOCAL ( task a - a')  LINK - +  ;

: AWAKE? ( task - a | 0)
  PUSH (   ) LINK DUP ( start current) 
  BEGIN 
    ( start current) DUP @ ( start current candidate) R@ =
    ( start current flag) IF POP DROP NIP ( a) ; THEN
    ( start current) @ ( start newcurrent)  2DUP = 
  UNTIL 2DROP POP DROP 0  ;
  
: SLEEP ( task -)  
  DUP TERMINAL = IF DROP ; THEN
  DUP AWAKE? ?DUP IF ( task prevTask) 
    OVER @ SWAP ! ( ie unlink) 
  THEN ( task) DROP PAUSE ;
  
: STOP ( -) LINK SLEEP  ;

: WAKE ( newtask -) DUP AWAKE? IF DROP ; THEN
  DUP LINK ( new new curr )
  DUP @ PUSH ( new new curr -- next)
  ! ( ie new is now successor to curr)  ( new)
  POP SWAP ! ( ie next is now successor to new)   ;
  



( shadow 10  Multitasking )

LOCAL ( task a - a')

 Convert an address A local to the current task to an equivalent address
 local to the given task.  E.g.,   TASK1 RP0 LOCAL  answers the RP0 slot
 in TASK1's TCB.

AWAKE? ( task - a | 0)

 The LINK fields form a circular list which is, in effect, the active
 task list.  AWAKE?  checks to see if a given task is in the active task
 list.  If not, a zero is returned.  If it is, the address of the task
 that points to the given task is returned.  This is the link field that
 points to the task we were asking about.  Thus it is the field we need
 to alter if we wish to remove the task from the active list.

 The active task list is circular.  It is never empty, as the foreground
 task should never be put to sleep.  With a single task, the LINK field
 of that task contains the address of itself.

 Executing a task name returns the address of that task, which is the
 start of its user variables (i.e., the address of its LINK field).

 AWAKE? works by running through the LINKs to see if any of them contain
 an address that matches the given task.  We don't really need to know
 how many tasks are present in the LINKs as long as we know when to stop
 looking (when we get back to the one we started with).

SLEEP ( task -)

 Remove TASK from the active task list (if it is not the foreground task).

STOP ( -)

 Put the current task to sleep (if it is not the foreground task).


WAKE ( newtask -)

 Insert NEWTASK into the active task list.


( block 11  Multitasker   )

: TASK! ( word task -)
  PUSH ( word)
  R@ 8 + ( word IPslot) !  (   )
  R@ SP0 LOCAL @   R@ $0C +  ( sp0 dstkSlot) !
  R@ RP0 LOCAL @   POP $10 + ( rp0 rstkSlot) !  ;


( shadow 11  Multitasking )

TASK! ( word task -)

  Set (or reset) TASK so it will run the Forth WORD when it gets
  control.  The LINK, SP0, and RP0 slot have already been initialized.
  The TOS and RLOOP slots are "don't care".  We store the Forth WORD
  into the saved IP slot.  Then we set the saved DSTK and RSTK slots
  from the SP0 and RP0 slots.

  Note that TASK1 LINK $XX + LOCAL  is the same as  TASK1 $XX +


( block 12  Multitasker  Examples )

VARIABLE V1
VARIABLE V2

: TST1 ( -) BEGIN 1500 MS  1 V1 +!  AGAIN  ;  

: TST2 ( -) BEGIN  300 MS  1 V2 +!  AGAIN  ;  

(  ' TST1  TASK1 TASK!   )
(  ' TST2  TASK2 TASK!   )
(  TASK1 WAKE   TASK2 WAKE )

( shadow 12  Multitasking  Examples )

