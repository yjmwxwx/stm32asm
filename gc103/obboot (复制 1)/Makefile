LD      = arm-none-eabi-ld -v
AS      = arm-none-eabi-as
CP      = arm-none-eabi-objcopy
    
AFLAGS  = -mcpu=arm7tdmi -mtune=arm7tdmi
LFLAGS  = -Tstm32.ld
CPFLAGS = -Obinary

all: test

test: 1.elf
	$(CP) $(CPFLAGS) 1.elf 1.bin
1.o: 1.s
	$(AS) $(AFLAGS) -o 1.o 1.s > 1.lst


1.elf: 1.o stm32.ld 
	$(LD) $(LFLAGS) -o 1.elf 1.o

	
