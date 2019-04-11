#if !defined  HAVE_BIT_DRAGON_R13_H__
#define       HAVE_BIT_DRAGON_R13_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline bool bit_dragon_r13_turn(ulong &x)
// Increment the radix-13 word x and
// return (tr) whether the lowest nonzero digit
// of the incremented word is either 3, 6, 8, 9, 11, or 12.
// tr determines whether to turn left or right (by 90 degrees)
// with the R13-dragon fractal.
//
// Starting with x==0:
//      x      tr
//  .........  0
//  ........1  0
//  .......1.  1
//  .......11  0
//  ......1..  0
//  ......1.1  1
//  ......11.  0
//  ......111  1
//  .....1...  1
//  .....1..1  0
//  .....1.1.  1
//  .....1.11  1
//  .....11..  0
//  ....1....  0
//  ....1...1  0
//  ....1..1.  1
//  ....1..11  0
//  ....1.1..  0
//  ....1.1.1  1
//  ....1.11.  0
//  ....1.111  1
//  ....11...  1
//  ....11..1  0
//  ....11.1.  1
//  ....11.11  1
//  ....111..  0
//  ...1.....  0
//  ...1....1  0
//  ...1...1.  1
//
// The sequence tr is the fixed point
// of the morphism  0 |--> 0010010110110,  1 |--> 0010010110111.
//
// Also fixed point of morphism (identify + with 0 and - with 1)
//  F |--> F+F+F-F+F+F-F+F-F-F+F-F-F,  + |--> +,  - |--> -
{
    ulong s = 0;
    while ( (x & 15) == 12 )  { x >>= 4;  ++s; }  // scan over nines
    ++x;  // increment next digit

    //                  1100000000000
    //                  2109876543210
    // echo $(( [#16] 2#1101101001000 ))  # zsh (==> 16#1B48)
    bool tr = ( (0x1b48 >> (x&15)) & 1 );  // whether digit is either 3, 6, 8, 9, 11, or 12
    x <<= (4*s);  // shift back
    return  tr;
}
// -------------------------


#endif  // !defined HAVE_BIT_DRAGON_R13_H__
