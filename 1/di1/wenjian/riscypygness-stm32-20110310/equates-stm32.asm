        ;; skip the emacs mode line
;;; -*- Mode:Asm Mode:outline-minor-mode outline-regexp:";;;+" comment-start: "; " -*-
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; equates-stm32.asm
        
        ;; The purpose of this file (equates-stm32.asm) is to contain
        ;; all the code for Riscy Pygness that is specific to the
        ;; STM32 ARM M3 MCU.

        ;; This file (equates-stm32.asm) is included by the
	;; board-specific include file (such as
	;; olimex-stm32-p103.asm).

;;; NOTE
        ;; Four subroutines and 2 Forth primitives must be defined.

        ;; The following subroutines must be defined, even if they do nothing,
        ;; because riscy.asm will call them.
        ;; 
        ;;      setup_clocks
        ;;      setup_ports
        ;;      ledOnSub
        ;;      ledOffSub

        ;; Additional, application-specific CODE words can be defined in
        ;; this file.
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        .equ PLLCLKIN, 8000000
        ;;    Main crystal clock frequency
        ;;    above (8 MHz) is the speed of both the STM32 HSI (internal
        ;;    RC) oscillator and the HSE (external crystal) oscillator on
        ;;    the Olimex board.
        
        .equ PLL_MULTIPLIER, 1   ;  Multiplier must be 1 since we turn off PLL

        .equ CPUDIVISOR, 1       ;  (does the Cortex have a cpu clock divisor?)
        
        ;.equ PCLKDIVISOR, 4      ; must be 1, 2, or 4
        .equ PCLKDIVISOR, 1      ; must be 1, 2, or 4

        .equ TIMER0_PRESCALE_DIVISOR, 1

        .equ BAUDRATE, 38400
        .equ SPIDIVISOR, 128     ; slow it way down for testing


;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Equates that do calculations and so are not likely to change
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        ;; Frequency is given in number of clocks per second

        ;; The Cortex M3 has two PCLKs
        
        .equ PLLCLK, (PLLCLKIN * PLL_MULTIPLIER)
        .equ CCLK, (PLLCLK / CPUDIVISOR)

        ;; The Cortex M3 terms would be HSI or HSE (for the external
        ;; or internal high-speed oscillators).  After going through
        ;; (or bypassing) the PLL, we get a SYSCLK which I think is
        ;; the same thing as what we called the CCLK on the LPC chips.
        .equ SYSCLK, CCLK

        ;; After the SYSCLK goes through the AHB prescaler
        ;; (/ 1,2,...512) it is called the HCLK.  So, maybe HCLK is
        ;; the Cortex M3 term for what we had been calling CCLK?
        ;; Maybe not.

        ;; The Cortex M3 has PCLK1 and PCLK2.
        ;; 
        ;;    APB1 peripherals use PCLK1 (up to 36 MHz)
        ;;    APB2 peripherals use PCLK2 (up to 72 MHz)

        .equ  PCLK, CCLK / PCLKDIVISOR   ; most timing depends on PCLK

        ;; Cortex M3 has two peripheral clocks, PCLK1 and PCLK2.  Set
        ;; them to the same value (hopefully their defaults are divide by 1)
        .equ PCLK1, PCLK
        .equ PCLK2, PCLK

        ;; So, to begin with, all the clocks stay at 8 MHz.
        
        ;; Following needs to be converted for the Cortex M3
        .equ PCLK_TIMER0_DIVISOR, PCLKDIVISOR
        
        .equ TIMER0FREQ, ((CCLK / PCLK_TIMER0_DIVISOR) / TIMER0_PRESCALE_DIVISOR)
        
        .equ  SPICLK, PCLK / SPIDIVISOR

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Clocks
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
setup_clocks:


        ;; Initialize STM32 Clocks

        ;; Ideally, we would just take the defaults to begin with and
        ;; do nothing.  Because it is possible that HSI is not
        ;; accurate enough for the serial communication (USART2), we
        ;; will switch from the internal 8 MHz clock (HSI) to the
        ;; external 8 MHz clock (HSE).

        ldr r6, = RCC_CR
        mov r0, HSEON
        str r0, [r6]            ; turn on the external clock

awaitHSE:
        ldr r0, [r6]
        and r0, # HSERDY
        beq awaitHSE            ; hang here until external clock is stable

        ;; at this point, the HSE is running and stable but I suppose we have not yet
        ;; switched Sysclk to use it.

        ldr r6, = RCC_CFGR
        mov r0, # 1
        str r0, [r6]            ; switch to the external clock
        
        
        ;; Should we now turn off the HSION bit?
        
        mov pc, lr              ; rts
        

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; I/O Ports and Peripherals
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
setup_ports:
        ;; STM32
        
;;;; Set up LED pin (this assumes the Olimex STM32-P103 board).
        ;; Enable the Port C peripheral clock by setting bit 4 and Port A peripheral clock by setting bit 2
        ldr r6, = RCC_APB2ENR
        mov r0, 0x14
        str r0, [r6]

        ;; Set the config and mode bits for Port C bit 12 so it will
        ;; be a push-pull output (up to 50 MHz) by setting bits 19-16
        ;; to '0011'.

        ldr r6, = GPIOC_CRH
        ldr r0, = 0x44434444
        str r0, [r6]

        ;; to turn on the LED, clear bit 12 of Port C
        ;; to turn off the LED,  set bit 12 of Port C
        ;; by writing 0 or 0x1000 to GPIOC_ODR 
        ;; (later, use bit banding)

;;;; UART2 Initialization
setup_uarts:    
        
        ;; On the Olimex STM32-P103 board, UART2 is connected to the
        ;; RS232 connector.  UART2 uses Port A (PA2 for TX and PA3 for RX)

        ;; Enable the Port A peripheral clock by setting bit 2
        ;; See above where we enabled both Port C and Port A

        ;; PA2 is TX so it needs to be configured as 0b1010 (push-pull alternate function low frequency)
        ;; PA3 is RX and its default state of 0x0100 (floating) should
        ;; work.  We could change it to a pull-up or pull-down?

        ;; bit3|bit2|bit1|bit0
        ;; 0100|1010|xxxx|xxxx
        ldr r6, = GPIOA_CRL
        ldr r0, [r6]
        and r0, # 0xFFFFF0FF    ; clear nibble for PA2
        orr r0, # 0x00000A00    ; OR in new value for PA2 nibble to
                                ; configure as push-pull alternate function low frequency
        str r0, [r6]

        ;; enable clock for USART2
        ldr r6, = RCC_APB1ENR
        mov r0, BIT17
        str r0, [r6]

        ;; It appears that the actual formula for the USART2 baudrate
        ;; register value is BRRVALUE = (PCLK1 / BAUDRATE)

        ;; For example, with an 8 MHz SYSCLK (either from HSI or HSE)
        ;; and not turning on any clock dividers, the PCLK1 would also
        ;; be 8 MHz.  If the desired baudrate is 38400 bps, then
        ;; BRRVALUE = 8000000 / 38400 = 0xD0.
        
setbaud:
        .equ BRRVALUE, (PCLK1 / BAUDRATE)
        ldr r6, = USART2_BRR
        ;ldr r0, = 0x00D0          ; 38400 bps
        ldr r0, = BRRVALUE         ; BAUDRATE bps
        str r0, [r6]

enableuart:
        ;; set UE (usart enable) (bit 13), TE (transmit enable) (bit 3), and RE (receiver enable) (bit 2) 
        ldr r6, = USART2_CR1
        .equ  USART_UE_TE_RE, (BIT13 + BIT3 + BIT2)
        ldr r0, = USART_UE_TE_RE
        str r0, [r6]

        mov pc, lr
        
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; LED Subroutines
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        ;;  Note, these routines are specific to a board which has
        ;;  which has an LED on Port C,
        ;;  (PC12 in the case of the Olimex STM32-P103 board).
        ;;  Consider changing over to bit banding.
ledOnSub:     
        ldr r6, = GPIOC_ODR
        mov r1, # 0
        str r1, [r6]      ; clear LED bit (bit 12) to turn on the LED
        mov pc, lr
ledOffSub:     
        ldr r6, = GPIOC_ODR
        ldr r1, = LED_MASK      ; LED bit 
        str r1, [r6]            ; set LED bit (bit 12) to turn off the LED
        mov pc, lr

        
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Additional application-specific Forth Primitives could go here.
;;;
