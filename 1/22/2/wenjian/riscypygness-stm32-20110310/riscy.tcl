#!/usr/local/bin/tclkit

#  Riscy Pygness
#  Copyright (c) 2004-2011 Frank C. Sergeant
#  frank@pygmy.utoh.org
#  Freely available under a modified BSD/MIT/X license.
#  Details at http://pygmy.utoh.org/license20040130.txt.
#  See the files COPYING and license20040130.txt in the distribution.

# *****************************************************************
#                                                                 *
# See the Riscy Pygness User Manual for documentation, especially *
# about variables you may need to change for your environment.    *
#                                                                 *
# *****************************************************************



# ******************** user-editable items ************************
#                                                                 *
set isUnix1 1

set ::debug 0
#set ::debug 1

#set ::serialPort1 "/dev/ttyS0"
set ::serialPort1 "/dev/ttyS1"
# note, serial port can be overridden on the command line with the
# -port option (e.g., ./riscy.tcl ... -port /dev/ttyS0)

set ::baudrate 38400

proc filenameFromBlockNumber {num} {
    if {[between $num     0    999]}  {return kernel.fth}

    # Edit from here down to change which block numbers are mapped to
    # which filenames.
    if {[between $num  1000   1999]}  {return s1.fth}
    if {[between $num  2000   2999]}  {return s2.fth}

    abort "bad block number: $num"
}

# *                                                               *
# ***************** end of user-editable items ********************

# ************ following items might need changing ****************
#                                                                 *

# The following three switch statements set the flash size, the RAM
# base address, and the RAM size, based on the chip.  These switch 
# statements will need to be edited (expanded) when porting to 
# additional chips.

# The flash size setting is sometimes smaller than the chip's actual
# flash size (in order to reduce the size of the ::image list) but
# should still be large enough for the Forth image in "normal"
# situations.  If your application needs more flash space, and if your
# chip supports it, feel free to edit the switch statement.

# ** flash size **


proc setFlashSize {} {
    # Since we are creating a flash image, the ::image list represents
    # the target's flash memory.  The various LPC ARM chips have
    # anywhere from 8KB to 512KB of flash, starting at address zero.

    # We set the flash size based on the chip (see ::chip near the top
    # of this file).  Should we use that actual flash size or just a
    # reasonable amount that we might expect the Forth to take?  For
    # example, surely we will not need anywhere near the full 256KB
    # available on the LPC2294?  For now, just use 32KB for the
    # LPC2294.
    switch -- $::chip {
        #lpc2294  {set ::flashSize [expr 256 * 1024] }
        lpc2294  {set ::flashSize [expr  32 * 1024] }
        lpc2294  {set ::flashSize [expr   8  * 1024] }
        #lpc2106  {set ::flashSize [expr 128 * 1024] }
        lpc2106  {set ::flashSize [expr  32 * 1024] }
        lpc2103  {set ::flashSize [expr  32 * 1024] }
        #lpc23xx  {set ::flashSize [expr 512 * 1024] }
        lpc23xx  {set ::flashSize [expr  32 * 1024] }
        #stm32    {set ::flashSize [expr  128 * 1024] }
        stm32    {set ::flashSize [expr  32 * 1024] }
        lpc1769  {set ::flashSize [expr  32 * 1024] }
    }
    # Note, above limits flash size to be used for the lpc2106 and
    # lpc23xx and lpc2294 (and for some of the stm32) to much less
    # than is available on the chip, to reduce the size of the ::image
    # list.  Feel free to increase the size if your application really
    # needs more room.
}

# ** RAM size **


proc setRamSize {} {
    # Following sets the available RAM size.  On the LPC ARM chips,
    # on-chip RAM starts at 0x40000000, but at 0x1000000 for the LPC
    # Cortex chips, and at 0x2000000 for the STM32.  The following
    # switch statement sets the RAM size and the RAM origin.

    # If we decide to make use of the chip's IAP (in-application
    # programming) facility, we might skip over some at the beginning
    # to allow for the possibility of using the in-application
    # programming routines for programming flash.  For now, we do not
    # do this.  This would affect how we initialize ::HH and ::H but
    # not the ::imageBase.

    switch -- $::chip {
        lpc2294  {set ::ramSize [expr  16 * 1024] }
        lpc2106  {set ::ramSize [expr  64 * 1024] }
        lpc2103  {set ::ramSize [expr   8 * 1024] }
        lpc23xx  {set ::ramSize [expr  32 * 1024] }
        stm32    {set ::ramSize [expr  20 * 1024] }
        lpc1769  {set ::ramSize [expr  32 * 1024] }
    }
    # note, check above for LPC17xx.  Not all the RAM is contiguous, etc.
}

# ** RAM base address **

proc setRamBaseAddress {} {
    switch -- $::chip {
        lpc2294  {set ::imageBase 0x40000000 }
        lpc2106  {set ::imageBase 0x40000000 }
        lpc2103  {set ::imageBase 0x40000000 }
        lpc23xx  {set ::imageBase 0x40000000 }
        stm32    {set ::imageBase 0x20000000 }
        lpc1769  {set ::imageBase 0x10000000 }
    }

    dputs "imageBase is $::imageBase"
}

# *                                                               *
# ***************** end of user-editable items ********************



proc DEBUG {} {
    if {$::debug} {
        set ::debug 0
    } else {
        set ::debug 1
    }
}

## Source other Tcl files and discover platform

set scriptDir [file dirname [info script]]

# General utility functions
source [file join $scriptDir util.tcl]

proc aligned? {{divisor 4}} {
  # Answer true if ::HH is already on an address evenly divisible by DIVISOR
  expr ($::HH % $divisor) == 0
}

proc alignHalfWord {} {
    # If we are at an odd address, comma in a zero to skip one byte.  This
    #  is needed for strings.
    if {! [aligned? 2]} {
        ccomma 0
    }
}

proc align {} {
    # If we are not aligned on a full-word boundary, then compile a NOP
    # to use up 2 bytes so we will be aligned on a full-word boundary.
    # Caller should be sure we are compiling.
    if {! [aligned?]} {
        compile NOP
    }
}

proc misalign {} {
    # If we are aligned on a full-word boundary, then compile a NOP to
    # use up 2 bytes so we will no longer be aligned on a full-word
    # boundary.  This is needed when compiling a 32-bit literal.  By
    # making sure the lit32 token starts misaligned, the following
    # in-line 32 bit number will be on a full-word boundary.  Caller
    # should be sure we are compiling.
    dputs "misalign -- at start, ::HH is [asHex $::HH]"
    if {[aligned?]} {
        compile NOP
    }
    dputs "misalign -- afterwards, ::HH is [asHex $::HH]"
}

proc alignRam {} {
    # Increment ::ram, if necessary, so it lies on a full word boundary
    dputs "alignRam -- at start, ::ram is [asHex $::ram]"
    set mod4 [expr $::ram % 4]
    if {$mod4} {
        incr ::ram [expr 4 - $mod4]
    }
    dputs "alignRam -- afterwards, ::ram is [asHex $::ram]"
}


## TIB 

# ::TIB holds the remaining string (or block) currently being
# interpreted, as 'word' collects and removes a word from the
# beginning of the string.

set ::TIB ""

# Keep a target image on the host.  We compile into the target image
# and then send the new data to the target to extend its dictionary.
# Note, lines to be interpreted and lines to be compiled are both
# compiled.  The difference is that only the latter extends the
# dictionary permanently.  When interpreting, the top of the
# dictionary on up is used as a temporary buffer.  We need to keep
# *two* pointers to the top of dictionary.  The permanent one is ::H
# and the temporary one is ::HH.  'comma' uses ::HH, which advances
# :HH byte by byte.  If we are compiling rather interpreting, after
# the new part of the dictionary is sent to the target, ::H is set to
# ::HH to make the extension permanent.

proc interpreting? {} {
    return [string equal $::mode interpreting]
}

proc compiling? {} {
    return [expr ! [interpreting?]]
}

# push and pop are used for saving and restoring the string being
# interpreted (i.e., ::TIB) for LOAD, and also for storing numbers and
# strings sent to the host by the target.
proc push {val} {
    dputs "about to push '$val' to local stack"
    lappend ::stack $val
}
proc pop {} {
    set val [lindex $::stack end]
    set ::stack [lrange $::stack 0 end-1]
    return $val
}

proc popn {} {
    # Pop an item from the host's local stack and guarantee it is a integer.
    set val [pop]
    if {[string is integer -strict $val]} {
        return $val
    } else {
        abort "popn -- expected integer but got '$val'"
    }
}

proc swap {} {
    # Swap the top two values on the host's stack
    set tos [pop]
    set sos [pop]
    push $tos
    push $sos
}

proc word {{token " "}} {
    # Return first token remaining in the TIB string, set TIB to the
    # remaining string.  Eat leading tokens.
    while {[string index $::TIB 0] == $token} {
        set ::TIB [string range $::TIB 1 end]
    }
    set pos [string first $token $::TIB]
    if {$pos < 0} {
        set w $::TIB
        set ::TIB ""
        return $w
    } else {
        set w [string range $::TIB 0 [expr $pos - 1]]
        set ::TIB [string range $::TIB [expr $pos + 1] end]
        return $w
    }
}

proc quit {} {
    # This is the host's version of the typical 'get some input and
    # interpret it' loop which is common to Forths.
    set ::bye 0
    puts -nonewline "> "
    flush stdout
    fileevent stdin readable {
        if {[catch {
            processLine
        } result]} {
            puts $result
            puts -nonewline "> "
            flush stdout
        }
    }
    vwait ::bye
}

proc processLine {} {
    # This is one pass of the 'get some input and interpret it' loop.
    # It is invoked by the fileevent system when the user has
    # finished entering an entire line.  See the procedure 'quit'.
    flush stdout
    if {[eof stdin]} {
        # In normal use, this should not happen.
        # Do nothing for now.  Otherwise, should
        #  we set ::bye to 1?
    } elseif {[gets stdin line] < 0} {
        # Only a partial line was available, so do nothing yet
    } else {
        # We got a full line, so interpret it
        set ::mode interpreting
        interpret $line
        if {$::bye} {
            puts "Exiting Forth"
        } else {
            puts  " ok"
            puts -nonewline "> "
        }
    }
    flush stdout
}

proc cold {} {
    # COLD is immediate word and is run only when interpreting.  It
    # causes the host to reset its ::H and ::HH after asking the
    # target to run its COLD.

    # The result of running COLD is a complete reloading and rebooting
    # of the Forth kernel.  In the following, we ask the target to
    # reset first, then we reset the host.

    if {[compiling?]} {
        abort "attempting to run COLD in compile mode."
    }

    puts " restarting ..."
    compile COLD
    sendToTarget
    startUp
}

proc interpret {str} {
    # Process a string, one word at a time, until the string is empty.

    # For each word, if it is "immediate", process it on the
    # host.  Otherwise, see if it is defined as a Forth word on the
    # target, if so, compile it on the host (so it can be sent to the
    # target for either "interpreting" or "compiling").  Failing that,
    # see if we can treat it as a number of some sort and, if so,
    # compile it as a literal.

    dputs "Starting to interpret \[$str\]"

    # Replace any control character, including CR and LF with a space.
    # This lets an editor pass multiple lines to be interpreted.

    set fixedStr [regsub -all {[[:cntrl:]]} $str { }]
    dputs "Fixed string is |$fixedStr|"

    set ::TIB $fixedStr
    set ::mode interpreting
    while {1} {
        set w [word]
        if {[empty $w]} {
            # We reached the end of the string we were interpreting, so 
            #  send what we have compiled to the target
            sendToTarget
            break
        }
        if {[compiledByteCount] > 250} {
            # Packets have a 1-byte length field, so when we get close
            # to the maximum length, go ahead and send what we have
            # compiled so far.
            sendToTarget
        }
        if {! [immediate $w]} {
            # It was not immediate so try looking it up in the target
            # dictionary
            dputs "  --interpret - $w was not immediate"
            if {! [forth $w]} {
                # It was not in target dictionary so try looking it up
                # in the table of constants
                dputs "  --interpret - 'forth $w' returned false"
                if {! [constant $w]} {
                    # It was not a constant, so see if it is number in the current base
                    number $w
                    # Number will abort if it is not successful
                }
            }
        }
    }
}

## Immediate words

proc immediate {w} {
    # Check to see if the word w is immediate.  If so, execute it and
    # return true.  If not, return false.  An "immediate" word is a
    # word that is executed on the host rather than being compiled to
    # be sent to the target.  We might wish to change the 'switch' to
    # a separate array that maps the immediate word name to the
    # procedure.

    # Note we have made the "dot" words immediate so we can apply cut
    # to them.  Without that, we get an error illustrated by $200 ?
    # on a line by itself (which does not occur if ?  is on a line by
    # itself).  Maybe, though, we should just run 'cut' after any word
    # that is immediate.  It won't hurt anything where it isn't needed.
    # Put it at the end just before sending the result

    set result 1
    switch -- $w {
        BYE         {set ::bye 1}
        {(}         {comment}
        ":"         {colon}
        ALLOT       {ALLOT}
        VARIABLE    {VARIABLE}
        2VARIABLE   {2VARIABLE}
        CREATE      {CREATE}
        TABLE       {TABLE}
        HERE        {number $::H}
        ";"         {semicolon}
        ";;"        {doublesemi}
        {"}         quote 
        {."}        dotquote
        {ABORT"}    abortquote
        {'}         tick
        {C,}        C,
        {,}         ,
        PUSH        {compile PUSH}
        POP         {compile POP}
        R@          {compile R@}
        I           {compile I}
        IF      {doIF}
        THEN    {doTHEN}
        ELSE    {doELSE}
        BEGIN   {doBEGIN}
        AGAIN   {doAGAIN}
        UNTIL   {doUNTIL}
        WHILE   {doWHILE}
        REPEAT  {doREPEAT}
        FOR     {doFOR}
        NEXT    {doNEXT}
        LOAD    {LOAD}
        THRU    {thru}
        WORDS   {words}
        TCL     {puts [eval [word 0]]}
        COLD    {cold}
        RESET   {cold}
        SAVE-IMAGE  {SAVE-IMAGE}
        DEBUG   {DEBUG}
        {.}     {compile .}
        {.R}    {compile .R}
        {U.}    {compile U.}
        {U.R}   {compile U.R}
        default {
            set result 0
        }
    }
    if {$result} {
       dputs "running 'cut' after immediate word $w"
       cut
    }
    return $result
}

proc doBEGIN {} {
    # Mark the address of the following instruction by pushing the
    # address to the host's data stack.
    push $::HH
    cut
}

proc doIF {} {
    # Compile a zerobranch
    cut
    compile 0branch
    # Remember where the destination address will go, once we know it
    # (doTHEN fills it in).
    doBEGIN
    # Fill in a dummy destination address for now.
    comma 0
}

proc doTHEN {} {
    # Fill in the offset to the destination for a previous 0branch or
    # branch instruction.  The local stack holds the address of the
    # slot.  Note, this resolves a forward branch of some sort (either
    # 0branch or branch) where the destination is not known at the
    # time the forward branch is compiled.  See doAGAIN for a word
    # that compiles a backward branch (where the destination *is*
    # known).
    set slotAddr [popn]
    store [expr $::HH - (2 + $slotAddr)] $slotAddr
    cut
}

proc doELSE {} {
    cut
    # Compile a branch
    compile branch
    # Remember where the offset to the destination address will go,
    # once we know it (doTHEN fills it in).
    doBEGIN
    # Fill in a dummy 16-bit offset as a place holder.
    comma 0
    # Host stack contains address of 0branch slot followed by the
    # address of branch slot.  Swap them so that doTHEN can fill in
    # the 0branch destination.  Later, another doTHEN will fill in the
    # branch destination.
    swap
    doTHEN
}

proc doAGAIN {} {
    # Lay down the 2-byte token for an unconditional branch followed
    # by the 2-byte offset to be added to IP.  For example, in 
    #
    #      BEGIN  BLINK BLINK  AGAIN 
    #
    # when branch begins to execute, IP will be pointing just past the
    # two bytes holding the offset, so the offset will be -8.
    cut
    compile branch
    comma [expr [popn] - (2 + $::HH)]
    cut
}

proc doUNTIL {} {
    # Whenever we do something like 'compile 0branch' we cut first so
    # the 0branch will not merge with a previously compiled word and
    # then we cut again so whatever follows it will not be merged with
    # the 0branch.
    cut
    compile 0branch
    comma [expr [popn] - (2 + $::HH)]
    cut
}

proc doWHILE {} {
    doIF
    swap
}

proc doREPEAT {} {
    doAGAIN
    doTHEN
}


proc doFOR {} {
    cut
    compile for

    # Save address of following slot that will hold offset to 'next'.
    doBEGIN

    # Lay down a 16-bit place holder for the offset to 'next'.
    # It will be filled in by doNEXT.
    comma 0

    # Save address of loop body.  It will used by doNEXT.
    doBEGIN

    # the local stack now holds two address but the earlier one will
    # need to be resolved first, so swap them
    swap
}

proc doNEXT {} {
    # When 'next' executes, the loop count is on the return stack and
    # the 16-bit offset to the loop's body follows the call to 'next'
    # in line.  'next' first checks to see if the count is zero.  If
    # so, it cleans up and skips over the in-line address.  Else, it
    # decrements the loop count and jumps back to the body of the
    # loop.

    # First, fill in the 16-bit slot that holds the offset to 'next'
    doTHEN

    # Then, lay down a call to 'next'
    compile next
    cut

    # Finally, lay down the 16-bit offset back to the loop's body
    set bodyAddress [popn]
    comma [expr $bodyAddress - (2 + $::HH)]
}

proc semicolon {} {
    # When a semicolon is found, we would like to change the preceding
    # call into a jump (i.e., perform "tail-call optimization").
    # However, there are several circumstances where this must not be
    # done.  In those cases, we lay down an explicit exit.  We will
    # use the function 'cut' to mark those cases where we need an
    # explicit exit.  The variable ::last holds the address of that
    # last instruction.

    # The variable ::last holds the address where the previously
    # compiled instruction starts.  If 'cut' was used, then ::last
    # will be zero and so we will lay down an explicit exit instead.
    if {$::last == 0} {
        # Here we must not set the exit bit of the preceding
        # instruction, so just compile 'exit'
        dputs "Compiling semicolon as an explicit 'exit'"
        compile EXIT
    } else {
        dputs "Compiling semicolon by changing previous instruction to a jump, i.e., by setting its exit flag."

        # Here, ::last holds the address of the previous instruction.
        # We wish to set its 'exit' bit, bit0, (by ORing a 1).
        store [expr [fetch $::last] | 1] $::last
    }
    cut
}

proc compiledByteCount {} {
    # Answer the number of bytes that have been laid down so far into
    # the compile buffer.
    return [expr $::HH - $::H]
}

proc resetCompileBuffer {} {
    # Throw away whatever has been compiled into the current compile
    # buffer.
    set ::HH $::H
}

proc colon {} {
    # Start or continue the definition of a new word in the
    # dictionary.  If we had been interpreting, then first send
    # anything in the compile buffer to the target -- we must not mix
    # interpreting and compiling in the same packet.

    # Make a new entry in the ::labels array to associate the current
    # value of ::H with a label.

    # If we are in interactive mode, we send an interpreting message
    # to the target to cause it can add the new label entry to its RAM
    # token table (see addLabel).

    # Multiple labels are allowed within a definition.

    sendToTarget

    set name [word]
    if {[empty $name]} {
        abort "Missing label for colon."
    } 
    set lab [addLabel $name $::HH]

    # At this point, we have updated the host's table and, if running
    # interactively, the target's table.

    dputs "Switching to compiling mode"
    set ::mode compiling
    cut
} 

proc LOAD {} {
    # The procedure 'getblock' takes a block number and returns a
    # string with the contents of the requested block.  The block
    # comes from the file that the block number maps to.  See the
    # filenameFromBlockNumber procedure to adjust the mapping.  For
    # example,    1 LOAD   would use the file named kernel.fth.

    # We must be in interpret mode
    if {[compiling?]} {
        abort "attempting to LOAD while in compile mode."
    }

    # Before sending whatever is ready to be interpreted, we also
    # compile the word that makes the target send back a "number"
    # message, so we can find which block to load.
    compile number
    
    # Also reset base.  The interpreting of each block begins in
    # decimal, thus changing the base within a block (e.g., with HEX)
    # only affects the remainder of that one block, not following
    # blocks. 
    compile DECIMAL

    # Close out anything already in the buffer (so the number
    # preceding LOAD (e.g.  27 LOAD) will wind up on the target's data
    # stack).
    sendToTarget

    # Now, the block number is on the host's local data stack.
    if {[llength $::stack] < 1} {
        abort "LOAD block number is missing from host's stack."
    }
    set n [popn]
    dputs "LOAD just popped '$n' off the local stack" 
    dputs "LOAD is about to set newstring to block $n"
    set newstring [getblock $n]
    
    # Save on the host's stack the string we had been processing
    push $::TIB
    interpret $newstring

    # We may have been in compile mode but we switch back to interpret
    # mode so we can continue interpreting the interrupted block when
    # we restore the previous string
    set ::mode interpreting
    set ::TIB [pop]

    dputs "About to exit LOAD and continue with remainder of previous ::TIB = \{$::TIB\}"
}

proc thru {} {
    # Load a range of blocks.

    # We need two numbers from the target, so compile 'number' twice
    compile number 
    compile number
    
    # Close out any partial compilation (so the two numbers we need will
    # be on the target's data stack)
    sendToTarget

    if {[llength $::stack] < 2} {
        error "Host's stack has only [llength $::stack] item(s) but needs at least two items."
    }


    set endingBlock [popn]
    dputs "endingBlock is $endingBlock"

    set startingBlock [popn]
    dputs "startingBlock is $startingBlock"

    # Save on the host's stack the string we had been processing
    push $::TIB

    dputs "About to load blocks $startingBlock through $endingBlock"
    set b $startingBlock
    while {$b <= $endingBlock} {
        set newstring [getblock $b]
        dputs "   THRU is about to interpret block $b"
        # Note, we prepend DECIMAL so that loaded via LOAD or via
        # THRU, the block will start off in decimal.
        interpret "DECIMAL $newstring"
        incr b
    }
    # Restore previous string
    if {[llength $::stack] < 1} {
        error "Host's stack has only [llength $::stack] items but needs at least one item."
    }
    set ::TIB [pop]
}

proc vec {slot} {
    # return the address for the vector with the given zero-based slot number
    expr 4 * $slot
}

proc vectorChecksum {} {
    # Calculate the proper value of vector number 5 and store the value
    # into that vector is ::image.  This is not *really* necessary, since
    # the flash utilities usually do this automatically.  However, it makes
    # it more convenient for comparing a file on the host with the contents
    # of the target flash if the correct checksum is in the file on the host.
    set s 0
    foreach slot {0 1 2 3 4 6 7} {
        # read every slot except for slot 5
        incr s [lfetch [vec $slot]]
    }    
    # now take its two's complement
    set s [expr (0x100000000 - ($s & 0xFFFFFFFF)) & 0xFFFFFFFF]
    # and store the result into slot 5
    lstore $s [vec 5]
    dputs "the sum is $s"
    dputs "the sum in hex is [asHex $s]"
    dputs "the sum truncated to 32 bits in hex is [asHex [expr $s & 0xFFFFFFFF]]"
}


proc writeImageBinary {imageName} {
    # The imageName will be something like "kernel" or "myapp2".  We
    # convert that to the name of the binary file (suitable for
    # burning into the flash on the ARM chip) named something like
    # "kernel.bin" or "myapp2.bin".

    # Note, this will change if the image does not begin at address
    # zero (as would be the case if, for example, the ARM had a
    # monitor program or custom bootloader sitting at address zero).

    # fix up the bootloader checksum in the image
    vectorChecksum

    dputs "writeImageBinary for $imageName"
    set f [open $imageName.bin w]
    fconfigure $f -translation binary -encoding binary
    foreach b [lrange $::image [expr 0 - $::imageBase] [expr $::H - $::imageBase - 1]] {
        puts -nonewline $f [char $b]
    }

    close $f
    dputs "writeImageBinary finished for $imageName"
}

proc writeImageDictionary {imageName} {
    # The imageName will be something like "kernel" or "myapp2".  We
    # convert that to the name of the dictionary file named something
    # like "kernel.dictionary" or "myapp2.dictionary".

    dputs "writeImageDictionary for $imageName"
    set f [open $imageName.dictionary w]
    set ::ff $f
    fconfigure $f -translation auto

    dputs "  about to set timestamp"

    # The 'clock format' command seems to fail in Tcl 8.5, so we work
    # around it if necessary.
    set timestamp "<missing timestamp>"
    if {[catch {set timestamp [clock format [clock scan now]]}]} {
        dputs "The 'clock format' command failed"
        if {[catch {set timestamp [exec date]}]} {
            dputs "The 'exec date' command failed also"
        }
    }
    dputs "  the timestamp is $timestamp"
    dputs "  about to write header line 1"
    puts $f "# This file, $imageName.dictionary, was generated automatically"
    puts $f "# on $timestamp, by the writeImageDictionary"
    puts $f "# procedure in riscy.tcl when the image was saved with the"
    puts $f "# Forth command"
    puts $f "#       SAVE-IMAGE <imagename> <bootword>"

    puts $f "\n# It will be loaded when Riscy Pygness is started up in interactive"
    puts $f "# mode with a command such as"
    puts $f "#    tclkit riscy.tcl -image <imagename>"

    puts $f "\n# It maps the Forth word names to addresses in the target flash memory and"
    puts $f "# sets several other variables."

    puts $f "\n# Statistics:"
    puts $f "#      [llength $::forthnamelist] names in ::forthnamelist"
    puts $f "#      [llength $::ramLabels] names in ::ramLabels"
    puts $f "#      [llength $::flashLabels] names in ::flashLabels"
    puts $f "#      [llength [array names ::labels]] names in ::labels\n"

    # We dump the ::labels array (in token number order) so it can be reloaded.

    # Make a list of pairs where the first is the token number and the second is the key
    set pairsList {}
    foreach {k v} [array get ::labels] {
        lappend pairsList [list [labelTokenNumber $v] $k]
    }

    dputs "about to dump ::labels"
    puts $f "\narray unset ::labels"
    puts $f "\narray set ::labels {"

    foreach pair [lsort -integer -index 0 $pairsList] {
        set k [second $pair]
        set v $::labels($k)
        puts $f [format "%15s  {%s}"  $k [formatList "%15s  %10s %2s %2s %5s" $v]]
    }
    puts $f "}"

    # dump the ::constants array so it can be reloaded
    dputs "about to dump ::constants"
    puts $f "\narray unset ::constants"
    puts $f "\narray set ::constants {"

    foreach {k v} [array get ::constants] {
        puts $f [format "%25s  %s"  $k $v]
    }
    puts $f "}"

    # dump the ::label2address array so it can be reloaded
    dputs "about to dump ::label2address"
    puts $f "\narray unset ::label2address"
    puts $f "\narray set ::label2address {"

    foreach {k v} [array get ::label2address] {
        puts $f [format "%25s  %s"  $k $v]
    }
    puts $f "}"

    # set up ::ramTokenTableBase
    puts $f "set ::ramTokenTableBase $::label2address(RTOKENS)"

    puts $f "set ::H  $::ram"
    puts $f "set ::HH $::ram"

    puts $f "set ::ram $::ram"

    puts $f "set ::chip $::chip"

    puts $f "\n# end of $imageName.dictionary"
    close $f
    dputs "writeImageDictionary finished for $imageName"
}


proc SAVE-IMAGE {} {
    # This word is used in kernel.fth like this
    #    SAVE-IMAGE <image-name> <boot-word>
    # for example,
    #    SAVE-IMAGE kernel QUIT

    # Which indicates the image should be saved to the names
    #    kernel.bin and kernel.dictionary
    # and that when the kernel boots it will execute the word QUIT. 

    # This word is allowed only when flash? is true.  If we are
    # in compiling mode, we will switch to interpreting mode.

    # To save an image we have just created, we create 
    #   1. a *.bin file (to be burned into the flash)
    #   2. a matching *.dictionary file to be loaded on the host when
    #      starting to run interactively.

    # Saving a new image is allowed only when in flash
    # (non-interactive) mode.
    if {[interactive?]} {
        abort "attempting to SAVE-IMAGE while in interactive mode."
    }

    # If we had been in compiling mode, we should close it out first
    # then change to interpreting mode.
    dputs "We are about to SAVE-IMAGE.  The mode is $::mode."
    dputs "   The values of ::H and ::HH are $::H and $::HH"


    dputs "in SAVE-IMAGE, get the two following words"
    set imageName [word]
    set bootword  [word]
    dputs "The imageName is $imageName and the bootword is $bootword"

    # close out the current compile mode
    sendToTarget

    # Before we can write the ::image list, we must close it out by appending
    # the flash token table and storing the address of the flash token table at
    # the assembly label 'ptokens'.  Before we do that, we must align :H to
    # a full-word boundary.
    dputs "about to save ::H to ptokens"
    align
    set ::H $::HH
    lstore $::H $::label2address(ptokens)

    # build the flash token table.
    dputs "about to store flash token table to image"
    set lastAddress 0
    foreach lab $::flashLabels {
        # ::flashLabels is in address order, but we will verify that
        set newAddress [labelAddress $lab]
        if {$newAddress < $lastAddress} {
            puts "** flash table warning: (newAddress < lastAddress): ($newAddress < $lastAddress) **"
        }
        lcomma $newAddress
        set lastAddress $newAddress
    }

    # update ::H
    set ::H $::HH

    # Set up the 'prtokens:' parm that points to the beginning of the RAM token table.
    dputs "about to store value of ram token table to the prtokens parm"
    lstore $::label2address(RTOKENS) $::label2address(prtokens)

    # ::ram was advanced as VARIABLE etc allotted RAM.  We now store its value
    # into the 'pfreeram:' parm.
    # guarantee ::ram is full-word aligned
    alignRam
    dputs "about to store new value of free ram to the pfreeram parm"
    lstore $::ram $::label2address(pfreeram)

    # That is also the initial value for HERE when starting to run
    # interactively, (as we will then be compiling to RAM and not to
    # flash).  The RAM variable h will be initialized by riscy.asm.

    set bootlab $::labels($bootword)
    set bootaddr [labelAddress $bootlab]

    dputs "about to store $bootaddr (the address of bootword $bootword) into boot variable at $::label2address(boot) "
    lstore $bootaddr $::label2address(boot)

    puts "Saving new kernel image"

    writeImageBinary $imageName
    writeImageDictionary $imageName
    
    exit 0

    # The image file was written from the ::image array, with an
    # origin of zero.  This is what we want when Forth sits at address
    # zero in the target.  Be aware that we might want an alternative
    # version that sits above some sort of monitor on the target.  So,
    # we may to adjust for this later.
}


array unset ::labels
array set ::labels { }


## label object

# A label is a quintuple containing
#   name
#   address
#   primitiveFlag             (1=primitive, 0=high-level)
#   ramFlag                   (1=ram,       0=flash)
#   tokenNumber               

### Accessors for label object
proc labelName        {lab} { first  $lab }
proc labelAddress     {lab} { second $lab }
proc labelPrimitive   {lab} { third  $lab }
proc labelRAM         {lab} { fourth $lab }
proc labelTokenNumber {lab} { fifth  $lab }

set ::isPrimitive 1
set ::isRAM       0
set ::tokenNumber 0

set ::flashLabels ""
set ::ramLabels   ""

proc addLabel {name address} {
    # Note,
    #   ::ramLabels is a list
    #   ::flashLabels is a list
    #   ::labels is an array

    # For each primitive or colon or variable definition Forth word
    # label, we create an entry in the ::labels array.

    # Do we need to keep a separate list of flashLabels and ramLabels?
    # Let's do it for now.

    # The ::flashLabels list will be used in flash mode to generate
    # the flash token table.

    # In flash or interactive mode, the ::labels array is used to find
    # the token number when compiling a Forth word.

    # first, send any pending buffer to the target
    sendToTarget

    set lab [list $name $address $::isPrimitive $::isRAM $::tokenNumber]
    incr ::tokenNumber

    # If a word is being redefined, inform the user.
    if {[info exists ::labels($name)]} {
        puts " redefining $name"
    }

    array set ::labels [list $name $lab]

    if {$::isRAM} {
        dputs "addLabel -- Adding $name to the list of RAM labels"
        lappend ::ramLabels $lab
    } else {
        dputs "addLabel -- Adding $name to the list of Flash labels"
        lappend ::flashLabels $lab
    }
    dputs "addLabel -- finished adding $name to a list"
    
    if {[interactive?]} {
        # If we are in interactive mode, we must also update the
        # target's token table in RAM.  We compile the Forth code to
        # store the new word's address into the target's token table
        # and then let the target do the work, i.e.,
        # "<new-word's-address> <new-slot's-address> !"

        dputs "addLabel -- we are in interactive mode"

        set oldmode $::mode
        # save mode so we can restore it

        set ::mode interpreting
        dputs "the address of the new word is [labelAddress $lab]"
        lit [labelAddress $lab]

        # Each entry in the RAM token table on the target occupies 4 bytes.
        set slotAddress [expr $::ramTokenTableBase + (4 * [labelTokenNumber $lab])]
        dputs "addLabel -- token table slotAddress for the new word is $slotAddress"
        lit $slotAddress
        compile "!"
        sendToTarget
        set ::mode $oldmode
        # restore the mode
    }
    dputs "addLabel -- finished adding label, (name,addr) = ($name, [asHex $address])"

    return $lab
}

proc CREATE {} {
    # Define a word that returns an address in RAM.  It is used for
    # creating buffers and also used by VARIABLE.  Although we need
    # only align a label on a 2-byte boundary, the ram address must be
    # on a 4-byte boundary.  This word defines a constant that returns
    # an address in RAM.  That RAM address follows this word when
    # compiling to RAM.

    # Whether compiling to RAM or flash, we compile a 32-bit literal which
    # points to RAM and we also create a label.

    # CREATE could be used stand-alone or it could be called by ":" or VARIABLE.
    # So, we could be either compiling or interpreting, so we remember and 
    # restore the current mode.

    # Here is how a CREATE'd word looks in interactive (RAM) mode, where
    # the literal points to the address immediately after the literal's value.
    #  | 2-byte-lit32 | 4-byte-address |
    
    # Here is how a CREATE'd word looks in flash mode, where
    # the literal points to a free address in RAM.
    #  | 2-byte-lit32 | 4-byte-literal-address | 2-byte-exit | 2-byte-skip |
    # so, the value of the 4-byte-literal is 8 bytes beyond the slot where
    # the literal is stored.
    
    sendToTarget

    set oldmode $::mode
 
    set name [word]
    if {[empty $name]} {
        abort "CREATE must be followed by the new name to be defined."
    }
    set ::mode compiling

    misalign 
    # We 'misalign' first, so any NOP will be prior to the label
    # address.  

    dputs "CREATE -- about to add label for $name"
    addLabel $name $::HH

    # resetting mode to compiling should no longer be necessary now that
    # 'addLabel' saves and restores the mode
    #set ::mode compiling

    cut
    compile lit32

    if {[interactive?]} {
        # We are compiling to RAM.  Because lit32 lays down its literal
        # on a full word boundary, the value of the literal will also
        # be on a full word boundary.
        dputs "CREATE -- in interactive mode, lcomma [expr $::HH + 4]"
        lcomma [expr $::HH + 8]
        cut
        semicolon
        # fill skipped 2 bytes with an indentifiable number for testing
        comma 0xa55a
    } else {
        # We are compiling to flash.
        # First, make sure the RAM pointer is on a full word boundary.
        dputs "CREATE -- in flash mode, lcomma $::ram"
        alignRam
        lcomma $::ram
        cut
        semicolon
    }
    sendToTarget
    set ::mode $oldmode
}

proc TABLE {} {
    # Define a word that returns an address in flash, providing we are
    # compiling to flash.  This is similar to CREATE except that
    # CREATE's word returns an address in RAM.  TABLE is used
    # typcially to define a fixed table or structure of some sort,
    # e.g.,
    #    TABLE TERMINATORS  4 C,   ( length of string)
    #                       $0D C, $0A C, $xx C, $xx C,

    # TABLE can be used interactively (to build a table in RAM), but
    # with the restriction that you cannot use C, when compiling to
    # RAM.  Instead, use , (comma) to lay down 4 bytes at a time.

    sendToTarget
    if {[interactive?]} {
        # Since we are compiling to RAM, just use CREATE so the table gets
        # built in RAM.
        CREATE
    } else {
        # We are compiling to Flash, so this is the same as colon
        # if we then switch back to interpreting
        misalign
        colon
        compile lit32
        lcomma [expr $::HH + 8]
        cut
        semicolon
        # fill skipped 2 bytes with an indentifiable number for testing
        comma 0xa55a
    }
    sendToTarget
    set ::mode interpreting
}

proc VARIABLE {} {
    # This will switch back to interpreting mode if we had been compiling.
    CREATE
    allot 4
}

proc 2VARIABLE {} {
    VARIABLE
    allot 4
}

proc allot {n} {
    if {[compiling?]} {
        abort "attempting to allot while in compile mode."
    }
    if {[interactive?]} {
        # We are working in RAM, so bump ::HH and ::H on host and 'h' on target
        set ::mode compiling
        incr ::HH $n
        sendToTarget
        set ::mode interpreting
    } else {
        # We are working in flash, so bump ::ram
        incr ::ram $n
    }
}

proc ALLOT {} {
    # Stack holds number of bytes to allot in RAM.  It is always RAM, never
    # flash, that will be allotted.  Will we use a separate FALLOT to allot
    # flash?

    # We must be in interpret mode (else we could not get the number
    # of bytes to allot).
    if {[compiling?]} {
        abort "attempting to ALLOT while in compile mode."
    }
    compile number
    sendToTarget
    set n [popn]
    allot $n
}




proc doublesemi {} {
    # A double semicolon (";;") is a special word that marks the end of
    # compile mode.  We cannot use a single semicolon for this because
    # a Forth definition may have multiple semicolons (for example, the
    # end of the word plus an exit within an IF statement).
    # The doublesemi will switch back from compile mode to interpret mode.
    # Warn the user if ";;" was found while interpreting.
    puts "found double semicolon"
    if {[interpreting?]} {
        warn "Double semicolon used while interpreting"
    }
    sendToTarget
    puts "Switching to interpreting mode"
    set ::mode interpreting
}

## Messages

proc sendToTargetFlash {} {
    # This is the version of sendToTarget used when building a new
    # image (not running interactively).

    # In this mode, we do not actually send anything to the target.

    dputs "About to sendToTargetFlash with (::H, ::HH) = ([as4Hex $::H], [as4Hex $::HH])"
    if {$::H == $::HH} {
        # Nothing as been compiled, so there is nothing to do
        dputs "  -- since ::H ::HH are equal, there is nothing to send"
        return
    }
    if {[interpreting?]} {
        # 'cut' may not be needed.
        cut
        dputs "  -- we are interpreting but, since we are in flash mode,"
        dputs "  -- nothing is actually sent to target."
        dputs "  -- resetting ::HH back to ::H"
        set ::HH $::H
    } else {
        dputs "  -- we are compiling, so make the dictionary extension permanent"
        set ::H $::HH
    }
}

proc sendToTargetRAM {} {
    # This is the version of sendToTarget used when running
    # interactively.

    # 'interpret' has reached the end of a string it was compiling.
    # If our mode is "compiling", send a compile packet then advance our ::H.
    # If our mode is "interpreting", send an interpret packet then wait for
    #  the target to send back an "ok".  Probably a 'fileevent' routine will watch
    #  for the "ok" and set a global flag.

    dputs "About to sendToTargetRAM with (::H, ::HH) = ([as4Hex $::H], [as4Hex $::HH])"
    if {$::H == $::HH} {
        # Nothing as been compiled, so there is nothing to do
        dputs "  -- since ::H ::HH are equal, there is nothing to send"
        return
    }
    if {[interpreting?]} {
        dputs "Building an 'I' packet"
        # Add an ";" to the end of the dictionary to make the target code exit
        # in case the user's code does not cause it to exit.  The exit (the 'ret'
        # instruction, will cause the target to execute its "ok" routine to signal 
        # us when it has finished interpreting this packet.
        # We probably do not need 'cut' here, but start with it for testing.
        cut
        semicolon
        sendPacket I
        set ::gotOk 0
        dputs " waiting for 'ok' message"
        vwait ::gotOk
        dputs "in sendToTargetRAM, we got 'ok' message"
        # then throw away the temporary compilation.
        dputs "Resetting ::HH back to ::H"
        set ::HH $::H
    } else {
        dputs "Building a 'C' packet"
        sendPacket C
        # make the dictionary extension permanent
        set ::H $::HH
    }
}

proc sendToTarget {} {
    if {[flash?]} {
        sendToTargetFlash
    } else {
        sendToTargetRAM
    }
}


proc sendPacket {type} {
    # Send the type byte (either "I" or "C").
    # Send a 1-byte length.  This is the length of the data field
    # (thus it excludes the initial "I" or "C", the length field, and the checksum
    # byte.
    # Send the bytes between $::H and $::HH.
    # Send a one-byte checksum as the complement of the
    #  sum of the data bytes.

    set ::checksum 0
    # The sendByte routine will update ::checksum

    #set payload [lrange $::image $::H [expr $::HH - 1]]
    set payload [lrange $::image [expr $::H - $::imageBase] [expr $::HH - $::imageBase - 1]]
    dputs -nonewline "Send packet: \[ "
    sendByte [asc $type]
    set len [llength $payload]
    sendByte $len
    foreach b $payload {
        sendByte $b
    }
    # All the bytes in the packet have been added up.  The checksum is
    # the sum's two's complement
    sendByte [expr 256 - ($::checksum % 256)]

    dputs "\]"
    # *** later, put an 'after' timeout handler that also sets ::acked if
    # ***  a timeout occurs
    # after 
    #set id [after $serialTimeout {set ::acked timedout}]
    #after cancel $id
    #if {$::acked eq "timedout"} {
    #   # Utoh, a timeout.  Retry or just abort?
    #   error "\nTime out while waiting for an Ack or Nak.\n"
    #}
    dputs " waiting for ack"
    set ::acked 0
    vwait ::acked
    dputs " got ack"
}

proc sendByte {num} {
    # Send the number (as a character) out the serial port.
    incr ::checksum $num
    dputs -nonewline "[as2Hex $num] "
    #dputs -nonewline "press RET to sendByte [as2Hex $num] to serial port"
    #gets stdin
    puts -nonewline $::tty1 [char $num]
}

proc sumbytes {bytes} {
    set sum 0
    foreach b $bytes {
        incr sum $b
    }
    return [expr $sum % 256]
}

## Compiling

proc forth {w} {
    # Is this word in the target dictionary?  If so, compile and return true.
    # Else return false.
 
   dputs "About to 'forth $w'"
   if {[info exists ::labels($w)]} {
        # Yes, it is an ordinary Forth word in the target, so compile
        # it
        compile $w
        return 1
    }
    return 0
}

proc constant {w} {
    # Is this word in our constants table?  If so, compile it as a literal
    #  then return true.  Else return false.
    # However, if we are in flash mode, then do not compile a lit but,
    #  instead, push the number to the local stack. 
    if {[info exists ::constants($w)]} {
        dputs "We found a constant $w ... "
        set n $::constants($w)
        dputs "   whose value is $n"
        if {[flash?] && [interpreting?]} {
            # push the number directly to the local stack
            dputs "About to push literal [asHex $n] to the local stack"
            push $n
        } else {
            # compile the number so it will be sent to the target
            dputs "About to compile literal [asHex $n]"
            #compile lit
            #comma $n
            lit $n
        }
        return 1
    }
    return 0
}

proc cut {} {
    # Mark the last word that was compiled as not being eligible for
    #  having its 'call' instruction changed into a 'jump' instruction.
    set ::last 0
}


proc tick {} {
    # tick compiles the actual 32-bit address of the word rather than
    # compiling the 16-bit token.  EXECUTE takes this into account.
    set w [word]
    if {[info exists ::labels($w)]} {
        # Yes, it is an ordinary Forth word in the target, so compile
        # its address as a literal
        set addr [labelAddress $::labels($w)]
        lit $addr
        cut
    } else {
        abort "$w ?"
    }
}

proc compile {w} {
    # Compile Forth word W for a token-threaded ARM Forth.
    # Given a target word name, look it up in the ::labels array,
    # create a tokenized address, and comma that into the compile
    # buffer.  It is an error if the name is not found in the ::labels
    # array.

    dputs "About to compile $w"
    set tokenizedAddress [tokenizedAddressOf $w]
    dputs "About to alignHalfWord"
    alignHalfWord
    set ::last $::HH
    dputs "About to comma the tokenizedAddressOf"
    comma $tokenizedAddress
    dputs "About to exit 'compile'"
}

proc comment {} {
    # Eat everything up through a right parenthesis
    word ")"
}

### Strings

proc compileString {} {
    # This is used by quote and by abortquote
    set str [word \"]
    dputs "About to compile string |$str|"
    ccomma [string length $str]
    foreach c [split $str {}] {
        ccomma [asc $c]
    } 
    cut
    alignHalfWord

}

proc quote {} {
    # The user entered something like  {" hello"}.
    # Compile the string as a counted string.

    # Get the string up to the ending quote mark then comma it into
    #  the dictionary as a counted string (i.e., length byte first).
    compile quote
    compileString
}

proc dotquote {} { 
    # The user entered something like {." hello"}.
    # Compile the string as with quote, then compile a call to TYPE.
    quote
    compile COUNT
    compile TYPE
}

proc abortquote {} { 
    # The user entered something like {-1 ABORT" that was an error"}.
    # Compile the string as with quote, then compile a call to (ABORT.
    compile abortquote
    compileString
}


### Numbers

proc smallLit {n} {
    between $n -32768 32767
}

proc lit {n} {
    # Compile the number N as a literal.  If it will fit in 16 bits,
    # we use lit16, otherwise, we use lit32.
    if {[smallLit $n]} {
        compile lit16
        comma $n
    } else {
        misalign
        compile lit32
        lcomma $n
    }
}

proc number {w} {
    # Try to convert the string $w into a number in the current base.
    # If successful, compile lit and comma the number and return true.
    # Otherwise, abort.
    # However, if interpreting and flash, then just push the number to
    # the host's local stack.
    dputs "Entered 'number' with $w"
    set n [convertToNumber $w]
    if {[string equal $n bad]} {
        abort "$w ?"
    }

    if {[flash?] && [interpreting?]} {
        # push the number directly to the local stack
        dputs "About to push literal [asHex $n] to the local stack"
        push $n
    } else {
        # compile the number so it will be sent to the target
        dputs "About to compile literal [asHex $n]"
        #compile lit
        #comma $n
        lit $n
    }
    # If lit is laid down as a subroutine, then we must *not* change
    #  the call to a jump (e.g., in the case of  { ... 17  ; }
    cut
    return 1
}

proc convertToNumber {w} {
    # If the string $w can be interpreted as a number in the current base,
    #  return its converted value as a decimal number. 
    # Otherwise, return the string "bad".

    # This procedure first checks for any special leading symbols, such as
    # "$" to indicate hexadecimal or "'" to indicate a character.  Otherwise
    # it turns it over to convertToNumberInBase.

    # Note, if a minus sign is present, it comes before any special leading
    # symbols.  So, you might write {-$45} or {-'B} but never {$-45} or {'-B}
    set leadingSign ""

    if {[empty $w]} {
        return "bad"
    }
    set firstChar [string index $w 0]

    if {[string equal $firstChar "-"]} {
        set leadingSign "-"
        set w [string range $w 1 end]
        set firstChar [string index $w 0]
    }

    if {[string equal $firstChar "$"]} {
        # a leading dollar sign indicates hexadecimal
        return $leadingSign[convertToNumberInBase [string range $w 1 end] 16]
    }
    if {[string equal $firstChar "'"]} {
        # A leading apostrophe indicates a character literal.
        # Usually that would be something like 'A or 'z but the
        # remaining string could be longer with no error, e.g.
        # 'ABC or 'zqr.  In either case, the ascii value of the
        # single character following the "'" is the result.
        if {[string length $w] < 2} {
            return "bad"
        }
        return $leadingSign[asc [string index $w 1]]
    }
    dputs "About to call convertToNumberInBase with ::base = $::base"
    return $leadingSign[convertToNumberInBase $w $::base]
}


proc convertCharToNumber {c} {
    # Convert characters "0-9" to the numbers 0-9.
    # Convert "A" to 10, "B" to 11, etc. all the way up to "Z" to 35.
    # Other routines will worry about whether the result is valid in the 
    #  current base.
    set n [expr [asc $c] - 0x30]
    if {$n > 9} {
        set n [expr $n - 7]
    }
    return $n
}

proc convertToNumberInBase {w base} {
    if {[empty $w]} {
        return "bad"
    }
    dputs "convertToNumberInBase's base is $base"
    switch -- $base {
        10    {
            if {[string is integer $w]} {
                return $w
            } else {
                return "bad"
            }
        }
        16    {
            if {[string is xdigit $w]} {
                return [expr 0x$w]
            } else {
                return "bad"
            }
        }
        default {
            set result 0
            foreach c [split $w ""] {
                set n [convertCharToNumber $c]
                if {$n < 0} {
                    return "bad"
                }
                if {$n >= $base} {
                    return "bad"
                }
                set result [expr ($base * $result) + $n]
            }
            return $result
        }
    }
}

## Forth-style words for use on the host

proc cfetch {addr} {
    # Return the target image byte at the given address.
    # We must adjust the ADDR to account for the ::imageBase.
    #lindex $::image $addr
    lindex $::image [expr $addr - $::imageBase]
}

proc cfx {addr} {
    # for convenience, this is the same as cfetch except the
    #  result is converted to hexadecimal
    asHex [cfetch $addr]
}

proc fetch {addr} {
    # Return the 16-bit number from the target image at the given address.
    # Note, the ARM is little endian.
    set ls [cfetch $addr]
    set ms [cfetch [expr $addr + 1]]
    return [expr ($ms * 256) + $ls]
}

proc lfetch {addr} {
    # Return the 32-bit number from the target image at the given address.
    # The ARM is little endian.
    set lsw [fetch $addr]
    set msw [fetch [expr $addr + 2]]
    return [expr ($msw * 65536) + $lsw]
}

proc cstore {val addr} {
    # Store the byte value into the target image at the given address.
    # We must adjust the ADDR to account for the ::imageBase.
    #dputs "Entered 'cstore' with (addr, imageBase, val) = ($addr, $::imageBase, $val)"
    lset ::image [expr $addr - $::imageBase] [lsbyte $val]
}

proc store {val addr} {
    # Store the 16-bit value into the target image at the given address.
    if {! [expr ($addr % 2) == 0]} {
        abort "store cannot store into $addr because it is not half-word aligned"
    }
    dputs "Entered 'store' and address was even as we expected"
    dputs "'store' was called with (val, addr) = ($val, $addr)"
    cstore [lsbyte $val] $addr
    cstore [msbyte $val] [expr $addr + 1]
}

proc lstore {val addr} {
    # Store the 32-bit value into the target image at the given address.
    if {! [expr ($addr % 4) == 0]} {
        abort "lstore cannot store into $addr because it is not full-word aligned"
    }
    store [lsword $val] $addr
    store [msword $val] [expr $addr + 2]
}

proc ccomma {u} {
    # Extend internal dictionary image with an 8-bit number.
    # This is like the Forth word C, (C-comma).
    cstore $u $::HH
    incr ::HH
}

proc comma {u} {
    # Extend internal dictionary image with a 16-bit number.
    dputs "About to 'comma' $u"
    dputs "About to call 'store'"
    store $u $::HH
    dputs "Finished calling 'store'"
    incr ::HH 2
}

proc lcomma {u} {
    # Extend internal dictionary image with a 32-bit number.
    comma [lsword $u]
    comma [msword $u]
}

proc C, {} {
    # It appears we can use C, when generating a kernel but not
    # interactively.  Thus it might be useful in a TABLE in flash but
    # not so useful in RAM.
    if {[compiling?]} {
        abort "mode was compiling but 'C,' works only when interpreting."
    }
    if {[interactive?]} {
        abort "cannot use C, interactively.  Use , instead."
    }
    compile number
    sendToTarget
    set n [popn]
    set ::mode compiling
    # we switch temporarily to compiling mode so the dictionary
    # extension will be permanent
    ccomma $n
    sendToTarget
    set ::mode interpreting
    # At this point, :HH is likely to be at an odd address.
    # Fortunately, 'compile' will align to a half-word boundary if
    # necessary.
}

proc , {} {
    if {[compiling?]} {
        abort "mode was compiling but ',' works only when interpreting."
    }
    compile number
    sendToTarget
    set n [popn]
    set ::mode compiling
    # we switch temporarily to compiling mode so the dictionary
    # extension will be permanent
    lcomma $n
    sendToTarget
    set ::mode interpreting
}

proc warn {msg} {
    puts "Warning: $msg"
}

proc abort {msg} {
    # Display the message via 'error', which returns to the quit loop.
    set ::stack {}
    error $msg
}

proc words {} {
    # List the words in the target dictionary and their addresses, address first.
    # Collect a following string, which may be empty.  If present, use it as a
    # globbing pattern to limit the display to matching words.
    # Examples:
    #    WORDS              (list all words)
    #    WORDS *            (list all words)
    #    WORDS A*           (list all words starting with "A")
    #    WORDS *c*          (list all words containing a "c")
    #    WORDS ???          (list all 3-letter words)

    set pattern [word]
    if {[empty $pattern]} {
        set pattern *
    }
    foreach {k v} [array get ::labels] {
        if {[string match $pattern $k]} {
            #puts "[labelAddress $v]  $k"
            set addr [labelAddress $v]
            puts "[as8Hex $addr]  $k"
        }
    }
}

# just for testing
proc C {str} {
    # Compile the given string into a packet to send to the target 
    # to extend the target's dictionary

    puts "You typed ||$str||"
    puts "The tokens to be processed are:"
    foreach t $str {puts "||$t||"}

    return ""
}


## Communication
proc port1 {port} {
    # Provide a command so the serial port could be changed interactively
    global serialPort1
    set serialPort1 $port
    openSerialPort1
}

proc drain1 {} {
    # Empty the serial queue, returning all the characters that were
    # waiting as a string.  The caller can display the string or not
    # at its choice.
    read $::tty1
}

proc openSerialPort1 {} {
    global tty1 serialPort1 isUnix1
    # open a serial port to the target
    catch {close $tty1}
    if {$isUnix1} {
        # 'file exists' always returns false on W98, so
        # only run this test on unix
        if {! [file exists $serialPort1]} {
            error "serial port1 $serialPort1 does not exist"
        }
    }
    if {[catch {
        set tty1 [open $serialPort1 w+]
        fconfigure $tty1 -mode $::baudrate,n,8,2 -translation binary -buffering none \
            -blocking 1  -handshake none -timeout $::serialTimeout1
    }] != 0} {
        error "cannot open serial port1 $serialPort1"
    }
    drain1
    fileevent $tty1 readable [list collectMessage]
}

set ::messageState awaitingColon
set ::serialTimeout1 1000
# If more than the timeoutValue milliseconds pass after we receive
# the start of a message from the target, we give up on that message.

proc serin {} {
    # Wait for, and return, a serial character unless a timeout occurs.
    # Note, we could simplify serial port reading somewhat if we were
    # willing to set it to blocking mode.  However, that could tie up
    # the gui for the length of the timeout.  So, we use non-blocking mode.

    # The serial port is set to blocking mode but with a timeout.  If a
    # timeout occurs, we read an empty string.  
    set result [read $::tty1 1]
    if {$result eq ""} {
        error "Target Forth failed to complete a message before timing out"
    }
    return $result
}

proc getString {} {
    # From the serial port, get a length byte and then that many characters.
    dputs -nonewline "getting string with "
    set len [asc [serin]]
    dputs "length of $len "
    set result ""
    for {set i 0} {$i < $len} {incr i} {
        append result [serin]
    }
    return $result
}

proc collectMessage {} {
    if {[catch {
        collectMessage2
    }] != 0} {
        # Utoh, an message from the target timed out.
        # That's ok.  We will just ignore it.  However,
        # we will make sure we have re-armed the fileevent.

        # re-arm fileevent
        fileevent $::tty1 readable [list collectMessage]
     }
}

proc collectMessage2 {} {
    # This does the hard work for the collectMessage procedure.
    # Entry occurs when a serial character arrives from the target.

    # We collect the rest of the message and then act upon it.

    # Each message starts with a command code (a request from the target)
    # that consists of a ":" followed by exactly one more character.  Then, 
    # depending on the target's request, additional information may be 
    # collected.  For example, when the target wishes to send a string to
    # be put on the host's stack, it sends ":s" followed by a count byte
    # followed by the characters of the string.

    dputs "Entered collectMessage2"
    flush stdout

    set newByte [serin]
    if {$newByte != ":"} {
        dputs "collectMessage got the byte [asHex [asc $newByte]]."
        dputs "Since it is not a colon, we ignore it."
        return
    }

    # get the second (and final) byte of the command code
    set newByte [serin]

    # We received the message type byte.
    switch -- $newByte {
        "k"  {
            dputs "We got the 'ack' message"
            set ::acked acked
        }
        "o"  {
            dputs "We got the 'ok' message"
            set ::gotOk ok
        }

        "n"  {
            dputs "We got the 'number' message"
            set num [asc [serin]]
            set num [expr (256 * $num) + [asc [serin]]]
            set num [expr (256 * $num) + [asc [serin]]]
            set num [expr (256 * $num) + [asc [serin]]]
            dputs "  -- pushing $num to local stack"
            push $num
        }

        "s"  {
            dputs "We got the 'string' message"
            set msg [getString]
            dputs "  -- the string is |$msg|"
            push $msg
        }

        "."  {
            dputs "We got the 'dot' message"
            dot
        }

        "E"  {
            dputs "We got the 'EMIT' message"
            emit
        }

        "U"  {
            dputs "We got the 'U.' message"
            # treat the number as unsigned and print it
            udot
        }

        "r"  {
            dputs "We got the '.R' message"
            # print signed number in a fixed-width field
            dotR
        }

        "R"  {
            dputs "We got the 'U.R' message"
            # print unsigned number in a fixed-width field
            udotR
        }

        "T"  {
            dputs {We got the 'TYPE' message}
            # print the string
            type
        }
        "d"  {
            # DECIMAL
            set ::base 10
        }
        "h"  {
            # HEX
            set ::base 16
        }

        default {
        }
    }
    return
}


## I/O helper functions

# precalculate constants that depend upon the word size.
#  8051 uses 16, ARM uses 32
#set ::wordSizePowerOf2 16
set ::wordSizePowerOf2 32


set ::largestSignedNumber [expr (1 << ($::wordSizePowerOf2 - 1)) - 1]
set ::largestUnsignedNumber [expr (1 << $::wordSizePowerOf2) - 1]

proc dot {} {
    # Print a signed number the way the Forth word . would do it.
    # Note, this is done in response to a request from the target
    # following its having sent a 'number' message that caused the
    # number to be pushed to the host's local data stack.
    dputs "starting to process 'dot' message"
    set formatChar d
    if {$::base == 16} {
        set formatChar X
    }
    set n [popn]
    if {$n > $::largestSignedNumber} {
        set n [expr $n - ($::largestUnsignedNumber + 1)]
    }
    puts -nonewline [format " %$formatChar" $n]
    dputs "finished processing 'dot' message"
}

proc dotR {} {
    # Print a signed number the way the Forth word .R would do it,
    #  in a fixed width field.
    set formatChar d
    if {$::base == 16} {
        set formatChar X
    }
    set width [popn]
    set n [popn]
    if {$n > $::largestSignedNumber} {
        set n [expr $n - ($::largestUnsignedNumber + 1)]
    }
    puts -nonewline [format "%$width$formatChar" $n]
}

proc udot {} {
    # Print an unsigned number the way the Forth word U. would do it.
    set formatChar u
    if {$::base == 16} {
        set formatChar X
    }
    set u [popn]
    puts -nonewline [format " %$formatChar" $u]
}

proc udotR {} {
    # Print an unsigned number the way the Forth word U. would do it,
    #  in a fixed-width field.
    set formatChar u
    if {$::base == 16} {
        set formatChar X
    }
    set width [popn]
    set u [popn]
    puts -nonewline [format "%$width$formatChar" $u]
}

proc type {} {
    # The host's stack holds the string.  The address and count were
    # used by the target to send the string, but the host does not
    # need the address and count now that it has the string itself.
    puts -nonewline [pop]
}

proc emit {} {
    # The host's stack hold the ascii value of the character to be
    #  displayed
    puts -nonewline [char [popn]]
}

## Initialize Image

proc importBin {filename} {
    # As part of creating the host's image of the target's flash, we 
    # read in the primitives created by assembling riscy.asm.  Be
    # sure that riscy.bin is created when assembling riscy.asm.
    set f [open $filename r]
    fconfigure $f -translation binary -encoding binary

    set ::binary [read $f]
    close $f

    foreach b [split $::binary {}] {
        ccomma [asc $b]
    }    
}

proc parsePrimitives {} {
    dputs "Starting 'parsePrimitives'"
    # The goal of this procedure is to fill in the array ::labels with
    # the names and addresses of Forth primitives from the assembly of
    # riscy.asm.

    # We also build a ::constants table from riscy.lnkt.

    # Note, we do this only when building a new flash image.  In
    # interactive mode, we read the information from the
    # previously-built *.dictionary file.

    # We first parse riscy.asm to map the Forth primitive name to the
    # assembly language label where the primitive is defined.  This
    # creates the array ::forth2label.

    # Then, we parse the file riscy.lnkt (created by the linker) to
    # map .text labels to addresses.  This creates the array
    # ::label2address.

    # Finally, we use ::forth2label and ::label2address to add the
    # label entries to the ::labels array, mapping the Forth primitive
    # names to addresses.

    # Build a temporary array mapping the assembly label to the Forth name.
    #set f [open riscy.asm r]
    set f [open riscy.lst r]
    set lines [split [read $f] "\n"]
    close $f

    # Run through the lines looking for ones that look like 
    #
    #    ;;; label number is Forth word number
    #    ;;; label cfetch is Forth word C@
    #
    # There must be at least three semicolons starting at the beginning of a
    # line, there may be more than three semicolons.  If the anything follows
    # the name of the Forth word on the line, the name must be followed by
    # a space.  Multiple spaces are ok anywhere a single space may appear.

    set ::forthnamelist {}
    array unset ::forth2label
    array set ::forth2label {}

    # set exp {^;;;+\s+label\s+(\S+)\s+is Forth word\s+(\S+)}
    # # above regexp says:
    # #   at the beginning of the line, there must be 3 or more semicolons
    # #   one or more spaces
    # #   the literal "label"
    # #   one or more spaces
    # #   one or more non-spaces (this is the assembly label name)
    # #   one or more spaces 
    # #   the literal "is Forth word"
    # #   one or more spaces
    # #   one or more non-spaces (this is the Forth word name)

    #set exp {^\d+\s+@@@+\s+label\s+(\S+)\s+is Forth word\s+(\S+)}
    set exp {^[[:space:]]*[[:digit:]]+[[:space:]]+@@@+[[:space:]]+label[[:space:]]+(\S+)[[:space:]]+is Forth word[[:space:]]+(\S+)}
    # above regexp says:
    #   at the beginning of the line, zero or more white space
    #   one or more digits
    #   one or more spaces (and/or tabs)
    #   three or more at signs
    #   one or more spaces
    #   the literal "label"
    #   one or more spaces
    #   one or more non-spaces (this is the assembly label name)
    #   one or more spaces 
    #   the literal "is Forth word"
    #   one or more spaces
    #   one or more non-spaces (this is the Forth word name)


    #dputs "*** starting to process lines from riscy.asm ***"
    dputs "*** starting to process lines from riscy.lst ***"
    foreach line $lines {
        # Build array that maps the Forth name to the assembly label.
        # Also build the list that will keep the Forth names in address (and index) order.
        if {[regexp $exp $line match asmlabel forthname]} {
            dputs "About to set ::forth2label for $forthname to $asmlabel"
            set ::forth2label($forthname) $asmlabel
            lappend ::forthnamelist $forthname
        }
    }

    # Build a temporary array mapping .text labels to addresses
    set f [open riscy.lnkt r]
    set lines [split [read $f] "\n"]
    close $f

    # Run through riscy.lnkt looking for lines like
    #   "00000708 l       .text	00000000 oneMinus"

    # Also collect lines such as
    #   "4000122c l       .ram	00000000 RTOKENS"

    # The first column is the address in hexadecimal.  The third column must
    # be ".text".  The fifth column is the assembly label.
    # Build a temporary array mapping the label to the address 
    array unset ::label2address
    array set ::label2address {}

    # Also build the ::constants array
    array unset ::constants
    array set ::constants {}

    # following regexp finds the .text lines for labels
    set exp1 {^(\S+)\s+\S+\s+\.text\s+\S+\s+(\S+)$}

    # following regexp finds the *ABS* lines for constants
    set exp2 {^(\S+)\s+\S+\s+\*ABS\*\s+\S+\s+(\S+)$}

    # following regexp finds the .ram lines also for labels
    set exp3 {^(\S+)\s+\S+\s+\.ram\s+\S+\s+(\S+)$}

    dputs "*** starting to process lines from riscy.lnkt ***"
    foreach line $lines {
        # Build array that maps the assembly label to the address 
        if {[regexp $exp1 $line match address label]} {
            set ::label2address($label) 0x$address
        }
        # Build array that maps the assembly label to the value 
        if {[regexp $exp2 $line match value label]} {
            set ::constants($label) 0x$value
        }
        # Build array that maps the assembly label to the address, for RAM
        if {[regexp $exp3 $line match address label]} {
            set ::label2address($label) 0x$address
        }
    }

    # Finally, use the temporary arrays ::forth2label and
    # ::label2address to build the permanent array that maps a Forth
    # primitive name to its address.

    # Note, we parse riscy.asm to get a list of the Forth words and
    # matching labels.  We might switch to parsing the assembly
    # listing file instead (riscy.lst).  If we switch to parsing a
    # listing file, we would look for lines such as

    # "564 @@@@ label fourDROP is Forth word 4DROP ( a b c d -)" 

    # Doing this would allow primitives to be defined in the
    # custom-*.asm files.

    foreach forthname $::forthnamelist {
        # This processes the primitive names in address order
        set assemblyLabel $::forth2label($forthname)
        set primitiveAddress $::label2address($assemblyLabel)
        addLabel $forthname $primitiveAddress
    }

    dputs "Finished 'parsePrimitives'"
}

proc createImage {blk} {

    # This is the non-interactive procedure that must be performed in
    # order to build a target image (*.bin) to be burned into flash
    # and also to create the matching *.dictionary file that will be
    # needed later to run interactively.

    dputs "About to 'createImage'"
    set ::base 10

    array unset ::constants
    array set ::constants {}

    array unset ::labels
    array set ::labels {}

    set ::flashLabels ""
    set ::ramLabels   ""

    set ::tokenNumber 0

    setFlashSize

    set ::imageBase 0
    set ::image [string repeat "0xFF " $::flashSize]

    set ::H 0
    set ::HH 0

    parsePrimitives

    # Read the primitives from riscy.bin into the image 
    dputs "About to call 'importBin'"
    importBin riscy.bin
    dputs "Finished running 'importBin' -- value of ::HH is $::HH"

    # Be careful above.  What needs to change if riscy.asm is org'd
    # *above* a monitor rather than at address zero?  Note, above
    # increments ::HH as it fills in the ::image list.

    # now that the primitives are loaded, everything else loaded will
    # be high-level.
    set ::isPrimitive 0

    # loading the primitives used ::HH so now ::HH points to the next
    # free location in the target dictionary, which is where high-level
    # definitions will be added.
    set ::H $::HH

    # Initialize the host's local stack.
    set ::stack {}

    set ::mode interpreting

    # Since we are building a flash image, we must allot RAM space for
    # variables, etc.  The file riscy.asm has already allotted some
    # RAM, for example, for data, return, and hardware stacks and for a
    # RAM token table and for the foreground task control block.  The 
    # free RAM after that point (at the label freeRAM:) is where we
    # will begin allotting variables, additional task control blocks, etc. 
    set ::ram $::label2address(freeRAM)

    # As additional RAM is allotted, the ::ram pointer will be advanced.
    # SAVE-IMAGE will then save ::ram into the 'pfreeram:' parm in the flash.


    # save the block number on our local stack so LOAD can find it
    push $blk
    dputs "About to execute '$blk LOAD'"
    interpret "LOAD"
    # We should not reach the following line if the load block succeeded.
    puts "createImage load block failed to execute SAVE-IMAGE."
    exit 1
}

proc loadImage {} {
    # We are running interactively, so we load the *.dictionary file
    # (which, hopefully, matches the *.bin file that has been burned
    # into the target's flash). 

    # We do not load the *.bin file, just the *.dictionary file that
    # matches Forth word names to the addresses in the target.

    # We keep a RAM image, though, because it provides the buffer into
    # which we compile (and from which we copy to the target) during
    # interactive mode.

    set ::base 10

    set ::imageFile $::options(-image)
    set ::dictionaryFile "[file rootname $::imageFile].dictionary"

    puts "Loading the dictionary from $::dictionaryFile"
    source $::dictionaryFile

    # Sourcing the above dictionary file sets up the ::labels,
    # ::constants, and ::label2address arrays and also sets the
    # variables ::HH and ::H and ::ram.

    setRamSize
    setRamBaseAddress

    set ::image [string repeat "0 " $::ramSize]

    # No need to rebuild the ::flashLabels list when running
    # interactively
    set ::flashLabels ""

    # but we do use ::ramLabels
    set ::ramLabels   ""

    # any words compiled now will be high-level (not primitives) and
    # they will be compiled to RAM.  We start the RAM token table
    # tokens at zero.
    set ::isPrimitive 0
    set ::isRAM       1
    set ::tokenNumber 0
    set ::stack {}
    set ::rstack {}
    set ::mode interpreting
    openSerialPort1
}

## Blocks

# We read the entire file into memory, but only when the file changes.

# Search for starting line of the requested block
set blockBlockRe  {^\( (block) ([[:digit:]]+)}
set shadowBlockRe {^\( (shadow) ([[:digit:]]+)}
set anyBlockRe    {^\( (shadow|block) ([[:digit:]]+)}

proc reread {filename} {
    dputs "About to reread $filename"
    set f [open $filename r]
    array set ::filecache [list "$filename,lines" [split [read $f] "\n"]]
    close $f
    array set ::filecache [list "$filename,stamp" [file mtime $filename]]
}

proc getblock {num} {
    # Return the string starting at the special marker for block $num
    # and continuing up to just before the following block marker (or
    # the end of the file, whichever comes first).

    # Note, we could speed the search up by caching the line numbers
    # where each block begins.  So far, that has not been a problem.

    set filename [filenameFromBlockNumber $num]
    
    # If we have not yet cached this file, we must do so now.
    if {! [info exists ::filecache($filename,stamp)]} {
        reread $filename
    }

    # If the file has been changed since we last cached it, we must read it again.
    if {$::filecache($filename,stamp) != [file mtime $filename]} {
        reread $filename
    }

    set found 0
    set start 0
    set ::lines $::filecache($filename,lines)
    foreach i $::lines {
        if {[regexp $::blockBlockRe $i match kind number]} {
            if {$number == $num} {
                # puts " -- we found it at line $start: $i"
                set found 1
                break
            }
        }
        incr start
    }
    if {! $found} {
        error "Block $num not found"
    }

    # Search for the end of the block 
    set found 0
    set ending [expr $start + 1]
    foreach i [lrange $::lines [expr $start + 1] end] {
        if {[regexp $::anyBlockRe $i match kind number]} {
            # puts " -- we found the end at line $ending: $i"
            set found 1
            break
        }
        incr ending
    }
    if {$found} {
        set lastLine [expr $ending - 1]
    } else {
        set lastLine [expr [llength $::lines] - 1]
    }
    join [lrange $::lines $start $lastLine] "\n"
}

proc dputs {args} {
    if {$::debug} {
        eval "puts $args"
        flush stdout
    }
}

proc showArray {a} {
    # Quick utility function to dump the values of an array.
    # This is just for testing.
    foreach {k v} [array get $a] {
        puts "$k --> $v"
    }
}


proc dumpArray {arrName} {
    upvar $arrName arr
    foreach {k v} [array get arr] {
        puts "$k = $v"
    }
}

proc dumpDict {} {
    dumpArray ::labels
}

proc flash? {} {
    return [expr ! $::isRAM]
}

proc interactive? {} {
    return [expr ! [flash?]]
}

proc tokenizedAddressOf {name} {
    # Calculate the xt (execution token) for the given Forth word by
    # looking up the NAME in the ::labels array then converting it to
    # the shifted token number with the appropriate flag bits set.

    dputs "'tokenizedAddressOf' called with name = '$name'"

    # It is an error if the NAME is not present.  (The caller will
    # have checked already.)

    # Create and return a tokenized address.

    # Bits 15..13 are the entry number (i.e., table position or token number), 
    #             shifted left by 3 bits.
    # Bit 2 is the primitive flag -- OR with 4 if primitive
    # Bit 1 is the RAM table flag -- OR with 2 if RAM-based
    # Bit 0 is the Exit flag (i.e., jump/call flag) -- always zero here

    dputs "About to set lab"
    set lab $::labels($name)
    dputs "lab is $lab"

    # put the token number into bits 15..13 by shifting left 3 bits
    set tokenizedAddr [expr [labelTokenNumber $lab] << 3]

    # OR in the primitive flag at bit 2 
    set tokenizedAddr [expr $tokenizedAddr | [expr [labelPrimitive $lab] << 2]]

    # OR in the RAM flag at bit 1
    set tokenizedAddr [expr $tokenizedAddr | [expr [labelRAM $lab] << 1]]

    # leave the exit flag (i.e., jump/call flag) at bit 0 clear

    dputs "about to return tokenizedAddr"
    return $tokenizedAddr
}

proc usage {{msg}} {
    set executable $::argv0
    puts ""
    puts "Error: $executable was started with invalid options."
    puts ""
    puts "$msg"
    puts ""
    puts "There are two ways to start the program:"
    puts ""
    puts "  1. To run interactively with an existing Forth image, use"
    puts "       $executable -image <image file> \[-port <serial port>\]"
    puts "     Examples:"
    puts "       $executable -image kernel-lpc2106"
    puts "       $executable -image kernel-lpc2103.dictionary"
    puts "       $executable -image kernel-lpc2294 -port /dev/ttyS0"
    puts ""
    puts "  2. To create a new image to be burned into flash, see the"
    puts "     'Creating a new kernel image' section of the manual"
    puts ""
    exit
}


proc getOptions {image port chip allowed} {
    # This procedure is called from startUp.  startUp passes its
    # arguments to getOptions.  It the usual situation, these three
    # arguments default to None and and we look to the command line
    # for their values.

    # Each option passed to the program on the command line must
    # consist of an option name, beginning with a hyphen, followed by
    # the option's value.

    # For example:
    #    ./riscy.tcl -image kernel-lpc2106 -chip lpc2106 -port /dev/ttyS0
    # or
    #    ./riscy.tcl -flash 1 -chip lpc2106

    # It is an error if any option name is not in the allowed list.
    # Since each option must have a value, it is an error if there are
    # not an even number of arguments.

    # must be an even number of arguments
    if {[llength $::argv] % 2} {
        usage "Options need a name and a value."
        exit
    }

    array unset ::options
    array set ::options "
        -image  $image
        -port   $port
        -flash  None
        -chip   None
    "

    # run through the options, setting the values in the ::options
    # array
    foreach {k v} $::argv {
        dputs "the key $k has the value $v"
        if {[lsearch $allowed $k] == -1} {
            usage "$k is not a valid option name."
        }
        set ::options($k) $v
    }

    # Got to have one or the other
    if {[isNone $::options(-flash)] && [isNone $::options(-image)]} {
        usage "You must include either the -flash or -image option."
    }

    # Can't have both
    if {! [isNone $::options(-flash)] && ! [isNone $::options(-image)]} {
        usage "You must include either the -flash or -image option, but not both."
    }

    # Although the -port option is not needed with the -flash option,
    # it won't hurt anything, so we allow and ignore it.

    # The -port option overrides the default value for the serial port
    if {! [isNone $::options(-port)]} {
        set ::serialPort1 $::options(-port)
    }

    # If -flash option is present, we must also have the -chip option.
    # (But, when running interactively, we can pick up the chip from the
    # the constants in the dictionary file.)
    if {! [isNone $::options(-flash)] &&  [isNone $::options(-chip)]} {
        usage "When using the -flash option, you must also include the -chip option."
    }

    # If the -chip option is present, use it to set ::chip
    if {! [isNone $::options(-chip)]} {
        set ::chip $::options(-chip)
    }

    #setFlashSize
    #setRamSize
    #setRamBaseAddress
}

proc startUp {{image None} {port None} {chip None} {allowed "-image -port -flash -chip"}} {
    puts ""
    puts "Welcome to Riscy Pygness"

    # In the usual case we pass two None arguments to getOptions, then
    # getOptions extracts options from the command line.
    getOptions $image $port $chip $allowed

    # Decide whether we are building a new flash image
    # noninteractively or running interactively with an existing
    # image. 
    dputs "About to decide whether to run interactively or not"
    if {[notNone $::options(-image)] } {
        # We will run interactively with an existing image
        set ::imageFile $::options(-image)
        set ::dictionaryFile "[file rootname $::imageFile].dictionary"
        loadImage
        dputs "image file is $::imageFile and dictionary file is $::dictionaryFile"
        set ::isRAM 1
        # now start the interactive loop (named after the Forth word QUIT)
        quit
    } elseif {[notNone $::options(-flash)] } {
        # We will run non-interactively to create a new image
        set ::isRAM 0
        set loadblock $::options(-flash)
        puts "Creating a new flash image by loading block $::options(-flash)"

        if {[catch {
            # We run this within catch to prevent the backtrace when hitting an undefined word
            createImage $loadblock
        } result]} {
            puts $result
            flush stdout
            exit 1
        }
        # Note, high-level code must SAVE-IMAGE in order for the
        # results to be saved to the *.bin and *.dictionary files.
    }
}

proc setOptionsBuild {} {
    # For testing, set some options as if they had been
    # specified on the command line.
    set ::argv [list -flash 1]
    set ::argc 2
}

proc setOptionsRun {} {
    # For testing, set some options as if they had been
    # specified on the command line.  Or, instead of this,
    # just run 'startUp kernel-lpc2106 /dev/ttyS0'.
    set ::argv [list -image kernel -port /dev/ttyS0]
    set ::argc 4
}


startUp
