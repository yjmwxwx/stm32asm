#!/usr/local/bin/tclkit

# preasm.tcl

# Preprocess ARM assembly language file to replace each occurrence of
# ";" (my preferred comment character) with "@" (the GNU ARM
# assembler's preferred comment character).


# We expect exactly two arguments: an input file name and an output file
# name, e.g.
#    ./preasm.tcl  xyz.asm  xyz.s

if {$argc != 2} {
    puts "
Usage:

    ./preasm.tcl <input-file-name> <output-file-name>

e.g.,

    ./preasm.tcl xyz.asm xyz.s
"
    error "Wrong number of arguments"
}

set inname [lindex $argv 0]
set outname [lindex $argv 1]

set infile [open $inname r]
set text [read $infile]
close $infile

# change all semicolons into at-signs
regsub -all {;} $text {@} text

# write result to output file
set outfile [open $outname w]
puts -nonewline $outfile $text
close $outfile

