        ;; skip the emacs mode line
;;; -*- Mode:Asm Mode:outline-minor-mode outline-regexp:";;;+" comment-start: "; " -*-

;;; Frank Sergeant  frank@pygmy.utoh.org
        
;;; olimex-stm32-p103.asm
;;; Equates specific to the Olimex STM32-P103 ARM Cortex M3 board

        ;; It will be preprocessed into olimex-stm32-p103.s by
        ;; the preprocessor that converts semicolons to at-signs so
        ;; it can be included in various assembly programs for the
        ;; Olimex board.

;;; Board equates

        ;; The STAT LED is on Port C, bit 12
        ;; Note, Port C0.26 is in position 26 (dec) or 0x1A (hex)
        ;; in decimal

        ;;  3322 2222 2222 1111 1111 1100 0000 0000
        ;;  1098 7654 3210 9876 5432 1098 7654 3210
        ;;  xxxx xxxx xxxx xxxx xxxY xxxx xxxx xxxx
        ;;  0000 0000 0000 0000 0000 0000 0000 0000  in binary
        ;;     0    0    0    0    1    0    0    0  is 0x00001000 in hex

        ;; So an orr or bic(and) mask is 0x00001000
        
        .equ STAT_LED_MASK, 0x00001000
        .equ LED_MASK, STAT_LED_MASK

        ;; note, this board has an 8 MHz external crystal

;;; STM32 processor equates

        .equ GPIOA_BASE, 0x40010800
        .equ GPIOA_CRL, GPIOA_BASE + 0
        .equ GPIOA_CRH, GPIOA_BASE + 4

        .equ GPIOB_BASE, 0x40010C00

        .equ GPIOC_CRL,  0x40011000
        .equ GPIOC_CRH,  0x40011004
        .equ GPIOC_IDR,  0x40011008
        .equ GPIOC_ODR,  0x4001100C
        .equ GPIOC_BSRR, 0x40011010
        .equ GPIOC_BRR,  0x40011014
        .equ GPIOC_LCKR, 0x40011018

        .equ GPIOD_BASE, 0x40011400
        .equ GPIOE_BASE, 0x40011800
        .equ GPIOF_BASE, 0x40011C00
        .equ GPIOG_BASE, 0x40012000


        ;; RCC registers, section 6.3, page 89, reference manual

        .equ RCC_BASE, 0x40021000
        .equ RCC_CR,      RCC_BASE + 0x00 ; clock control register, reset value 0x0000 XX83
          .equ PLLRDY, BIT25   ; hardware sets it to 1 when PLL is locked
          .equ PLLON,  BIT24   ; set to enable PLL
          .equ CSSON,  BIT19
          .equ HSEBYP, BIT18
          .equ HSERDY, BIT17   ; hardware sets it to 1 when external clock is stable
          .equ HSEON,  BIT16
                       ;;    bit 15:8 HSICAL
                       ;;    bit  7:3 HSITRIM
          .equ HSIRDY, BIT1
          .equ HSION,  BIT0

        ;; RCC map on page 111, section 6.3.11 of reference manual
        .equ RCC_CFGR,      RCC_BASE + 0x04 ; clock configuration register, reset value 0x0000 0000
        ;;    bit 21:18  PLLMUL   ; 0 = input clock * 2,  1 = input clock * 3, etc.
        ;;    bit 17     PLLXTPRE ; HSE divider for PLL entry, 0 = not divided,  1 = divided by 2
        ;;    bit 16     PLLSRC   ; 0 = HSI/2,  1 = HSE
        ;;    bit 15:14  ADCPRE   ; set ADC clock frequency
        ;;    bit 13:11  PPRE2    ; APB high-speed prescaler (APB2) (division factor for PCLK2)
        ;;                          0xx = HCLK not divided, 100 = /2, 101 = /4, 110= /8, 111 = /16
        ;;    bit 10:8   PPRE1    ; APB low-speed prescaler (APB1) (division factor for PCLK1)
        ;;                          0xx = HCLK not divided, 100 = /2, 101 = /4, 110= /8, 111 = /16
        ;;    bit  7:4   HPRE     ; AHB prescaler (division factor for AHB clock)
        ;;                          0xxx SYSCLK not divided, 1000 /2, 1001 /4 (etc see page 94 referenc manual)
        ;;    bit  3:2   SWS      ; system clock switch status (set by hardware)
        ;;                          00 = HSI, 01 = HSE, 10 = PLL, 11 = N/A
        ;;    bit  1:0   SW       ; system clock switch (software selects SYSCLK source)
        ;;                          00 = HSI, 01 = HSE, 10 = PLL, 11 = N/A

        .equ RCC_CIR,       RCC_BASE + 0x08 ; clock interrupt register, reset value 0x0000 0000

        .equ RCC_APB2RSTR,  RCC_BASE + 0x0C ; APB2 peripheral reset register, reset value 0x0000 0000

        .equ RCC_APB1RSTR,  RCC_BASE + 0x10 ; APB1 peripheral reset register, reset value 0x0000 0000
        ;;    bit 17     USART2 RST    0 = no effect,  1 = reset USART2
        
        .equ RCC_AHBENR,    RCC_BASE + 0x14 ; AHB peripheral clock enable register, reset value 0x0000 0014

        .equ RCC_APB2ENR,   RCC_BASE + 0x18 ; APB2 peripheral clock enable register, reset value 0x0000 0000
        ;;    bit 21     TIM11 EN
        ;;    bit 20     TIM10 EN
        ;;    bit 19     TIM9 EN
        ;;    bit 15     ADC3 EN
        ;;    bit 14     USART1 EN
        ;;    bit 13     TIM8 EN
        ;;    bit 12     SPI1 EN
        ;;    bit 11     TIM1 EN
        ;;    bit 10     ADC2 EN
        ;;    bit  9     ADC1 EN
        ;;    bit  8     IOPG EN
        ;;    bit  7     IOPF EN
        ;;    bit  6     IOPE EN
        ;;    bit  5     IOPD EN
        ;;    bit  4     IOPC EN
        ;;    bit  3     IOPB EN
        ;;    bit  2     IOPA EN
        ;;    bit  0     AFIO EN
        
        .equ RCC_APB1ENR,   RCC_BASE + 0x1C ; APB1 peripheral clock enable register, reset value 0x0000 0000
        ;;    bit 17     USART2 EN

        .equ RCC_BDCR,   RCC_BASE + 0x20 ; Backup domain control register, reset value 0x0000 0000
        .equ RCC_CSR,    RCC_BASE + 0x24 ; control/status register, reset value 0x0000 0000


        ;; STK (SysTick timer)
        ;; see STK register map in section 4.5.6 (page 152) of programming manual
        .equ STK_BASE, 0xE000E010
        .equ STK_CTRL ,   STK_BASE +    0 ;  SysTick control and status register
                                          ;    uses processor clock (AHB) by default.
                                          ;    Set bit 0 to enable.  reset value 0x0000 0004
        ;; I do not seeing a reset value of 0x0000 0004.  I see 0x0000 0000.  So, be sure
        ;; to set the bits explicitly.
          .equ STK_COUNTFLAG, BIT16  ; hardware sets it to '1' if timer counted to zero since the
                                     ; last time this bit was read.
          .equ STK_CLKSOURCE, BIT2   ; 0 = AHB/8,  1 = processor clock (AHB)
          .equ STK_TICKINT,   BIT1   ; 1 = enable interrupt flag
          .equ STK_ENABLE,    BIT0   ; 1 = enable timer 

        
        .equ STK_LOAD ,   STK_BASE +    4 ;  SysTick reload value register (24 bits)
        .equ STK_VAL ,    STK_BASE +    8 ;  SysTick current value register (24 bits)
        .equ STK_CALIB ,  STK_BASE + 0x0C ;  SysTick calibration value register

        ;; set following define at least temporarily so kernel.fth can continue to
        ;;  use T1TC to refer to read the counter value
        .equ T1TC, STK_VAL

        ;; table on page 129 the base addresses on page 106 seem inconsistent?
        ;.equ NVIC_BASE, 0xE000E100
        ;.equ NVIC_BASE, 0xE000EF00

        ;; SCB (System Control Block)
        ;; see SCB register map in section 4.4.14 (page 147) of programming manual
        .equ SCB_BASE, 0xE000ED00
        .equ SCB_CPUID,   SCB_BASE +    0
        .equ SCB_ICSR,    SCB_BASE +    4 ; interrupt control and state register
        .equ SCB_VTOR,    SCB_BASE +    8 ; vector table offset register
        .equ SCB_AIRCR,   SCB_BASE + 0x0C ; application interrupt and reset control register
        .equ SCB_SCR,     SCB_BASE + 0x10 ; system control register
        .equ SCB_CCR,     SCB_BASE + 0x14 ; configuration and control register
        ;; skip the SCB_SHPR* etc for now


        ;; Memory protection unit table on page 118
        ;.equ MEM_BASE, 0xE000E100

        ;; USART2 (serial port) (use either half or full-word access)
        ;; see USART register map in section 26.6.8 (page 776) of reference manual
        .equ USART2_BASE, 0x40004400
        .equ USART2_SR,   USART2_BASE +    0 ;  status register
        ;;     TXE   (transmit data register empty)            bit 7
        ;;           it is cleared by a write to USART2_DR
        ;;     TC    (transmission complete)                   bit 6
        ;;     RXNE  (read data register not empty)            bit 5
        ;;           it is cleared by reading USART2_DR
        ;;     IDLE                                            bit 4
        ;;     bits 3-0 for various errors

        .equ USART2_DR,   USART2_BASE +    4 ;  data register (ls byte)
        .equ USART2_BRR,  USART2_BASE +    8 ;  baud rate register
        ;;     bits 15:4 DIV_Mantissa[11:0] is mantissa of USARTDIV
        ;;     bits  3:0 DIV_Fraction[3:0] is fraction of USARTDIV
        
        .equ USART2_CR1,  USART2_BASE + 0x0C ;  control register 1, default 0x0000 0000
        ;;     bit 13    UE     USART enable
        ;;     bit 12     M     word length (0 = 8 bits, 1 = 9 bits)
        ;;     bit 11    WAKE   (0 = idle line, 1 = address mark)
        ;;     bit 10    PCE    parity control enable
        ;;     bit  9    PS     parity selection (0 = even, 1 = odd)
        ;;     bit  8    PEIE   parity interrupt enable
        ;;     bit  7    TXEIE  TXE interrupt enable
        ;;     bit  6    TCIE   transmission complete interrupt enable
        ;;     bit  5    RXNEIE RXNE interrupt enable
        ;;     bit  4    IDLEIE IDLE interrupt enable
        ;;     bit  3    TE     transmission enable
        ;;     bit  2    RE     receiver enable
        ;;     bit  1    RWU    receiver wakeup
        ;;     bit  0    SBK    send break

        .equ USART2_CR2,  USART2_BASE + 0x10 ;  control register 2, default 0x0000 0000
        ;;     bit 14    LINEN  LIN mode enable
        ;;     bit 13:12 STOP   (00 = 1 stop bit, 10 = 2 stop bits)
        ;;     bit 11    CLKEN  clock enable  (0 = CK pin disabled)
        ;;     bit 10    CPOL   CK pin polarity
        ;;     bit  9    CPHA   clock phase in synchronous mode
        ;;     bit 8:0   other bits we don't need for simple RS232
        
        .equ USART2_CR3,  USART2_BASE + 0x14 ;  control register 3, reset value 0x0000 0000

        .equ USART2_GTPR, USART2_BASE + 0x18 ;  guard time and prescaler, reset value 0x0000 0000

        .equ AFIO_BASE, 0x40010000
        
        
        ;; TIM2 registers, section 14, page 335, reference manual.
        ;; For register and bit descriptions, see section 14.4, page 371

        .equ TIM2_BASE, 0x40000000
        .equ TIM2_CR1,      TIM2_BASE + 0x00 ; control register 1, reset value 0x0000
           ;; bits 9:8 CKD clock division
          .equ TIMx_ARPE, BIT7   ; auto-reload preload enable
           ;; bits 6:5 CMS center-aligned mode selection
          .equ TIMx_DIR,  BIT4   ; 0 = upcounter,  1 = downcounter
                                 ;  this bit is read only in center-aligned or encoder mode
          .equ TIMx_OPM,  BIT3   ; one-pulse mode, 0 = not stopped at update event
          .equ TIMx_URS,  BIT2   ; update request source
          .equ TIMx_UDIS, BIT1   ; update disable, 0 = UEV enabled
          .equ TIMx_CEN,  BIT0   ; counter enable

        .equ TIM2_CR2,      TIM2_BASE + 0x04 ; control register 2, reset value 0x0000
          .equ TIMx_TI1S, BIT7   ; TI1 selection (which pin is connected)
           ;; bits 6:4 MMS master mode selection
          .equ TIMx_CCDS, BIT3   ; capture/compare DMA selection

        ;; lots of other timer registers we probably do not need to touch at this time
        
        .equ TIM2_CNT,      TIM2_BASE + 0x24 ; counter register
        .equ TIM2_PSC,      TIM2_BASE + 0x28 ; prescaler register (set to zero to prescale by 1)
        .equ TIM2_ARR,      TIM2_BASE + 0x2C ; auto-reload register
        