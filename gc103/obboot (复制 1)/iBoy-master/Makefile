#
prefix = /usr/local
bindir = ${exec_prefix}/bin

# If PC_RUN = "GCC", iBoy is compiled for iPod Linux
# If PC_RUN = "YES", iBoy is compiled for a PC Linux <-- this doesn't work, though.
PC_RUN = GCC

SYS_DEFS = -DHAVE_CONFIG_H -DIS_LITTLE_ENDIAN -DIS_LINUX -DHAVE_USLEEP 
#SYS_DEFS += -DOLD_KERNEL
#SYS_DEFS += -DUSE_TEXTMENU
#SYS_DEFS += -DMEASUREMENT 
OUTPUT = iboy

ifeq ("$(PC_RUN)", "YES")
	CC = gcc
	LD = $(CC)
	AS = $(CC)
	CFLAGS_NOO =  -Wall  -g3
	CFLAGS_O =  
	CFLAGS = $(CFLAGS_NOO) $(CFLAGS_O)
	LDFLAGS = $(CFLAGS)
	ASFLAGS = -Wa,--warn -O3 
	SYS_DEFS += -DPORTABLE 
endif

ifeq ("$(PC_RUN)", "GCC")
	CC = arm-none-eabi-gcc
	LD = $(CC)
	AS = $(CC)
	CFLAGS_NOO = -mlittle-endian -elf2flt -Wall 
	CFLAGS_O = -mcpu=arm7tdmi -mtune=arm7tdmi -O3 -fomit-frame-pointer 
	CFLAGS = $(CFLAGS_NOO) $(CFLAGS_O)
	LDFLAGS = $(CFLAGS) -elf2flt 
	#-static-libgcc 
	#ASFLAGS = -Wa,--warn -O3 
	#-Wa,-mcpu=arm7tdmi
	SYS_DEFS += -DUSE_ASM -DUSE_COP 
	#-DOLD_KERNEL
	#-DKB_NO_WHEEL
	ASM_OBJS = asm/arm7tdmi/cpu.o 
endif

ifeq ("$(PC_RUN)", "NO")
	CC = arm-none-eabi-gcc
	LD = $(CC)
	AS = $(CC)
	CFLAGS_NOO = -mlittle-endian -elf2flt -Wall 
	CFLAGS_O = -mcpu=arm7tdmi -mtune=arm7tdmi -O3  
	CFLAGS = $(CFLAGS_NOO) $(CFLAGS_O)
	LDFLAGS = $(CFLAGS) -elf2flt 
	ASFLAGS = -Wa,--warn -O3 
	#-Wa,-mcpu=arm7tdmi
	SYS_DEFS += -DUSE_ASM -DUSE_COP
	#-DKB_NO_WHEEL
	ASM_OBJS = asm/arm7tdmi/cpu.o 
endif

ifeq ("$(PC_RUN)", "LINKI")
	CC = arm-none-eabi-gcc
	LD = $(CC)
	AS = $(CC)
	CFLAGS_NOO = -mlittle-endian -Wall -g3
	CFLAGS_O = -mcpu=arm7tdmi
	#-mtune=arm7tdmi
	CFLAGS = $(CFLAGS_NOO) $(CFLAGS_O)
	LDFLAGS = $(CFLAGS) 
	ASFLAGS = $(CFLAGS)
	#-Wa,--warn -O3 
	SYS_DEFS += -DPORTABLE -DKB_PORTABLE
	#-Wa,-mcpu=arm7tdmi
	SYS_DEFS += -DUSE_ASM 
	ASM_OBJS = asm/arm7tdmi/cpu.o 
	OUTPUT = linkboy
endif


TARGETS =  begin iboy end

SYS_INCS = -I/usr/local/include  -I./sys/ipod

SYS_OBJS = cop.o sys/nix.o sys/oss.o
SYS_OBJS += sys/config.o

SP_VERSION = 1
SYS_KBOBJS = sys/kb.o
SYS_LCDOBJS = sys/lcdll.o sys/graphics.o

targets: $(TARGETS)
infiles:
	cp ../Generator/in.txt /tmp/tmp_in.txt;
	cp ../Generator/cb_in.txt /tmp/tmp_cb_in.txt;
	../Generator/Debug/Generator 0 /tmp/tmp_in.txt > /tmp/op_generators.c;
	../Generator/Debug/Generator 0 /tmp/tmp_cb_in.txt cb >> /tmp/op_generators.c; 
	cp /tmp/op_generators.c dyntrans/


all:	infiles targets

include Rules

begin:
	$(PRINT) "GCC" `which $(CC)`
	$(PRINT) "CFLAGS" "$(CFLAGS)"
	@printf "\n"

iboy: 	$(SYS_LCDOBJS) $(ASM_OBJS) $(OBJS) $(SYS_OBJS) $(SYS_KBOBJS)
	$(PRINTNOR) "Linking"
	@$(LD) $(LDFLAGS) $(SYS_LCDOBJS) $(ASM_OBJS) $(OBJS) $(SYS_OBJS) $(SYS_KBOBJS)  -o $(OUTPUT)
	@du -h $(OUTPUT)
end:
	@printf '\n'

abort:
	@printf $(ABORT_MSG)


clean:
	rm -f iboy *.gdb *~ gmon.out *.o menu/*.o menu/*~ sys/*.o sys/*~ asm/*/*.o dyntrans/*.o

nearlyclean:
	rm -f iboy *.gdb *~ gmon.out *.o menu/*.o menu/*~ sys/*.o sys/*~  dyntrans/*.o
