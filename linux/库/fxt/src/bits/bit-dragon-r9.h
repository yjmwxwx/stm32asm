#if !defined  HAVE_BIT_DRAGON_R9_H__
#define       HAVE_BIT_DRAGON_R9_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline bool bit_dragon_r9_turn(ulong &x)
// Increment the radix-9 word x and
// return (tr) whether the lowest nonzero digit
// of the incremented word is either 2, 3, 5, or 8.
// tr determines whether to turn left or right (by 120 degrees)
// with the R9-dragon fractal.
//
// Starting with x==0:
//      x      tr
//  .........  0
//  ........1  1
//  .......1.  1
//  .......11  0
//  ......1..  1
//  ......1.1  0
//  ......11.  0
//  ......111  1
//  .....1...  0
//  ....1....  0
//  ....1...1  1
//  ....1..1.  1
//  ....1..11  0
//  ....1.1..  1
//  ....1.1.1  0
//  ....1.11.  0
//  ....1.111  1
//  ....11...  1
//  ...1.....  0
//  ...1....1  1
//  ...1...1.  1
//  ...1...11  0
//  ...1..1..  1
//  ...1..1.1  0
//  ...1..11.  0
//  ...1..111  1
//  ...1.1...  1
//  ...11....  0
//  ...11...1  1
//  ...11..1.  1
//
// The sequence tr is the fixed point
// of the morphism  0 |--> 011010010,  1 |--> 011010011.
// Also fixed point of 0 |--> 011, 1 |--> 010, because
//   0 |--> 011 |--> 011010010
//   1 |--> 010 |--> 011010011
// See OEIS sequence A156595.
//
// Also fixed point of morphism (identify + with 0 and - with 1)
//  F |--> F+F-F-F+F-F+F+F-F,  + |--> +,  - |--> -
//
// Also fixed point of morphism
//  F |--> G+G-G,  G |--> F-F+F,  + |--> +,  - |--> -
{
    ulong s = 0;
    while ( (x & 15) == 8 )  { x >>= 4;  ++s; }  // scan over nines
    ++x;  // increment next digit

    //                  876543210
    // echo $(( [#16] 2#100101100 ))  # zsh (==> 16#12C)
    bool tr = ( (0x12c >> (x&15)) & 1 );  // whether digit is either 2, 3, 5, or 8
    x <<= (4*s);  // shift back
    return  tr;
}
// -------------------------


#endif  // !defined HAVE_BIT_DRAGON_R9_H__
