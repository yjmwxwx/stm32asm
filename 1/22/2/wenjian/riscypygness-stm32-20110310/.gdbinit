
# Note, start this within Emacs as
#  M-x arm-elf-gdb --annotate=3

# This .gdbinit file is in the working directory for the STM32 ARM
# Cortex work.  It handles settings specific to this project and is
# read by GDB after reading the .gdbinit in the home directory (which
# sets common options such as the radix).

#set complaints 1

# for the serial connection to the serial port at 38400
# set remotebaud 38400
# target remote /dev/ttyS0

# Set up for JTAG and OpenOCD  (see later in file)
#target remote localhost:3333

#set output-radix 0x10
#set input-radix 0x10

# Following reverts GDB to older behavior allowing access to all
# of target memory.  This should not be necessary once I figure out
# how to tell GDB what memory regions the target has.
#set mem inaccessible-by-default off

# All the LPC ARM chips are little endian
# The STM32 chip is little endian
#set endian little



cd ~/riscy/cortex/stm32
#file ~/riscy/cortex/stm32/led-stm32.elf
#file ~/riscy/cortex/led-stm32.elf
file ~/riscy/cortex/stm32/riscy.elf

dir .
set prompt (stm32-gdb) 

# connect to the simulator
#target sim

# connect to openOCD running on gdb port 3333
target remote localhost:3333

# Set a breakpoint
b _start

