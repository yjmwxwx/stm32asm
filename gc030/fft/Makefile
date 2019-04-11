LD      = arm-none-eabi-ld -v
AS      = arm-none-eabi-as
CP      = arm-none-eabi-objcopy
    
AFLAGS  = -ahls -mcpu=cortex-m0 -mthumb 
LFLAGS  = -Tstm32.ld -nostartfiles
CPFLAGS = -Obinary

all: test

test: 1.elf
	$(CP) $(CPFLAGS) 1.elf 1.bin
1.o: 1.s
	$(AS) $(AFLAGS) -o 1.o 1.s > 1.lst


1.elf: 1.o stm32.ld 
	$(LD) $(LFLAGS) -o 1.elf 1.o

	