#!/bin/sh

# This is an example shell script for starting Riscy Pygness for a
# specific board and image.  The point is to have a very short name
# and to avoid the typing.

# (You might prefer to use a shell alias instead.)

# Be sure to set the path to Tcl correctly.

/usr/local/bin/tclkit riscy.tcl -image kernel-stm32  -port /dev/ttyS0
