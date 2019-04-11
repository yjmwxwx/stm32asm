#!/usr/local/bin/tclkit

# Some utility functions.

proc msbyte {n} {
    # answer the upper byte of a 16-bit number
    expr ($n & 0xFFFF) >> 8
}

proc lsbyte {n} {
    # answer the lower byte of a 16-bit number
    expr $n & 0xFF
}

proc msword {n} {
    # answer the upper 16-bit number of a 32-bit number
    expr ($n & 0xFFFFFFFF) >> 16
}

proc lsword {n} {
    # answer the lower 16-bit number of a 32-bit number
    expr $n & 0xFFFF
}


proc hex {hexnum} {
    # Append the '0x' prefix to a string that is otherwise
    # already a valid hexadecimal number.
    format "0x%s" $hexnum
}

proc asc {char} {
    # Answer the ascii code of the character CHAR.
    binary scan $char c* asciivalue
    return [expr $asciivalue & 0xff]
}

proc char {asciiCode} {
    # Answer the character represented by the integer asciiCode.
    return [format "%c" $asciiCode]
}

# These three functions convert a number (hex or decimal) into
# a C-style hex format, e.g. 0xF3
proc asHex {num} {
    # Format the number as hexadecimal but without leading "0x".
    # For example,  'asHex 32' returns  '20'
    format "0x%X" $num
}
proc as2Hex {num} {
    format "0x%02X" $num
}
proc as4Hex {num} {
    format "0x%04X" $num
}
proc as8Hex {num} {
    format "0x%08X" $num
}


# These three functions convert a number (hex or decimal) into an 8051
# assembler style hex format, e.g. 0F3H.  This suits the Heinz
# assembler.  For other assemblers, perhaps these will need to call
# as2Hex etc instead.
proc asH {num} {
    # Format the number as hexadecimal but with a leading "0" and an
    # ending "H", e.g., 0F3H.  For example, 'asH 32' returns '020H'
    format "0%XH" $num
}

proc ph {num} {
    # "Put Hex"
    # Print NUM in hexadecimal
    puts [asHex $num]
}

# Some convenience functions for lists
proc first {lst} {
    lindex $lst 0
}
proc second {lst} {
    lindex $lst 1
}
proc third {lst} {
    lindex $lst 2
}
proc fourth {lst} {
    lindex $lst 3
}
proc fifth {lst} {
    lindex $lst 4
}
proc sixth {lst} {
    lindex $lst 5
}

proc listequal {list1 list2} {
    # This is a limited list comparison function, checking only for an
    # exact string match of corresponding elements, but it should be
    # sufficient for the tests in this file.  If we wished to use
    # numeric comparisons for elements with the same value but
    # different representations, this would need to be change.
    return [string equal [join $list1] [join $list2]]
}


# listequal {1 2 3} {1 2 3}
# listequal {1   2 3} {1 2   3}
# listequal {1 3 2} {1 2 3}
# listequal {0x45 3 2} {0x45 3 2}

proc isNone {x} {
    string equal $x None
}

proc notNone {x} {
   expr ! [isNone $x]
}

proc empty {str} {
    # Answer true if str is the empty string 
    return [string equal $str ""]
}

proc within {n lower upper} {
    # Return true if n is greater than or equal to lower and strictly
    # less than upper.
    if {$n < $lower} {
        return 0
    }
    if {$n < $upper} {
        return 1
    }
    return 0
}

# proc between {n lower upper} {
#     # Return true if n is greater than or equal to lower and
#     # less than or equal to upper.
#     if {$n < $lower} {
#         return 0
#     }
#     if {$n <= $upper} {
#         return 1
#     }
#     return 0
# }

proc between {n low high} {
    # answer true if in is between low and high (inclusive)
    expr ($n >= $low) && ($n <= $high)
}



proc formatList {formatString listOfValues} {
    # This is like format except the values are passed as a list
    # of values rather than as individual values.
    # Example:
    #   puts [formatList " %02x  %02x  %02x " {0x45 0x46 0x47}]
    eval format [format "{%s} %s" $formatString $listOfValues]
}

proc isValidHexString {str} {
    # Should we instead use the following?
    #   'string is int 0x$str'
    return [regexp {^[0-9a-fA-F]+$} [string trim $str]]
}

proc +wrap {value {increment 1} {high 65535}  {low 0}} {
    # Add increment to value but wrap around if it exceeds the limits.
    set result [expr $value + $increment]
    if {$result < $low} {
        set result [expr $result + $high + 1]
    } elseif {$result > $high} {
        set result [expr ($result - $high - 1) + $low]
    }
    return $result
}

# set abc 7
# +wrap $abc 1  -->  8

proc listAsHex {list} {
    # Return a string representing the numbers in 'list' in
    # hexadecimal.  E.g., [listAsHex {10 11 12 13}] --> "0x0a 0x0b 0x0c 0x0d"
    set result {}
    foreach n $list {
        append result [format "0x%02X " $n]
    }
    return $result
}
# listAsHex {10 11 12 13}
# listAsHex {254 255 256 257 258 259 0xff 0x100 0x101}


proc isPrintable {char} {
    # Answer true if the character is printable.  0x20 through 0x7E
    # answer true and everything else false.
    set asciivalue [asc $char]
    if {$asciivalue < 0x20} {
        return 0
    } elseif {$asciivalue > 0x7E} {
        return 0
    } else {
        return 1
    }
}

proc isPrintableOrCRLF {char} {
    # Answer true if the character is printable or if it is a CR or a
    # LF.
    set asciivalue [asc $char]
    if {$asciivalue == 0x0D || $asciivalue == 0x0A} {
        return 1
    } else {
        isPrintable $char
    }
}

proc printableOrDot {asciivalue} {
    # Answer the character if it is printable, else answer a dot
    set c [char $asciivalue]
    if {[isPrintable $c]} {
        return $c
    } else {
        return "."
    }
}


## fcs  I am adding this to convert ::labels to a list in order of index number
##  just for testing
proc labelsList {} {
    set ::lst ""
    foreach i [array names ::labels] {
        set item $::labels($i)
        set idx [lindex $item 4]
        set formattedIndex [format "%4d" $idx]
        set newitem "$formattedIndex | $item"
        lappend ::lst $newitem
    }
}

proc showList {lst} {
    # Show list sorted
    foreach i [lsort $lst] {
        puts $i
    }    
}
