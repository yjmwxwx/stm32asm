# ######################################################################
#    Riscy Pygness makefile for STM32                                  #
#     (especially the Olimex STM32-P103 board)                         #
#                                                                      #
#    See the Riscy Pygness User Manual for instructions.               # 
#                                                                      #
# ######################################################################


# ######################################################################
# Set especially these variables for your environment
# ######################################################################

PORT = /dev/ttyS1
BIN = /usr/local/arm/bin
PREASM = /usr/local/bin/preasm.tcl
CCLK = 8000
DLBAUD = 38400

ASMFLAGS = -mcpu=cortex-m3 -mthumb -mapcs-32 -gstabs
LNKFLAGS =  -v -T stm32.ld -nostartfiles

INCLUDEFILES = equates-bits.asm equates-stm32.asm olimex-stm32-p103.asm 


ZIPFILES = README COPYING license20040130.txt makefile    \
   riscy-stm32.asm $(INCLUDEFILES) riscy.tcl util.tcl preasm.tcl \
   kernel-*.bin kernel-*.dictionary kernel.fth forthblocks.el \
   stm32.ld openocdstm32.cfg .gdbinit .gdbinit-home \
   riscy.sh r burn  $(EXAMPLEFILES)

#  LED blinking example for the Olimex-Stm32-P103 board
EXAMPLEFILES = led-stm32.html openocdstm32.cfg stm32.ld led-stm32.asm led-stm32.s led-stm32.elf led-stm32.bin

.PRECIOUS: %.o %.hex %.bin %.srec %.elf %.s

all: kernel-stm32.bin kernel-stm32.dictionary

clean:
	@ echo "...cleaning"
	rm -f *.o *.elf *.hex led*.s *.bin *.lst *.lnkh *.lnkt

#zipdate =  `date +%Y%m%d-%H%M`
zipdate =  `date +%Y%m%d`

zipex:
	zip led-stm32.zip $(EXAMPLEFILES)

zip:
	zip riscypygness-stm32-$(zipdate).zip $(ZIPFILES)

riscy.o : riscy.s equates-bits.s olimex-stm32-p103.s equates-stm32.s

riscy.s : riscy-stm32.s
	cp riscy-stm32.s riscy.s

kernel.bin : riscy.bin
	./riscy.tcl -flash 1 -chip stm32

kernel-stm32.bin : kernel.bin
	cp kernel.bin kernel-stm32.bin
	cp kernel.dictionary kernel-stm32.dictionary

%.s: %.asm
	$(PREASM) $*.asm $@ 

%.o: %.s 
	$(BIN)/arm-elf-as $(ASMFLAGS) -ahls=$*.lst  -o $@ $*.s

%.dis: %.elf
	$(BIN)/arm-elf-objdump  -d --source $<  > $@

%.hex: %.bin
	$(BIN)/arm-elf-objcopy --input-target binary  --output-target ihex  $<  $*.hex

%.srec: %.bin
	$(BIN)/arm-elf-objcopy --input-target binary  --output-target srec  $<  $*.srec

%.bin: %.elf
	$(BIN)/arm-elf-objcopy -O binary $<  $*.bin

%.elf: %.o
	@ echo "...linking $@"
	$(BIN)/arm-elf-ld $(LNKFLAGS) -o $@ $<
	$(BIN)/arm-elf-objdump -h $@ > $*.lnkh
	$(BIN)/arm-elf-objdump -t $@ > $*.lnkt

%.dl: %.bin
	@ echo " about to down load with CCLK = $(CCLK)"
	lpc21isp -donotstart -verify -bin $*.bin  $(PORT) $(DLBAUD) $(CCLK)

