#if !defined  HAVE_BIT_DRAGON_R5_H__
#define       HAVE_BIT_DRAGON_R5_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline bool bit_dragon_r5_turn(ulong &x)
// Increment the radix-5 word x and
// return (tr) whether the lowest nonzero digit
// of the incremented word is > 2.
// tr determines whether to turn left or right (by 90 degrees)
// with the R5-dragon fractal.
//
// Starting with x==0:
//      x      tr
//  .........  0
//  ........1  0
//  .......1.  1
//  .......11  1
//  ......1..  0
//  .....1...  0
//  .....1..1  0
//  .....1.1.  1
//  .....1.11  1
//  .....11..  0
//  ....1....  0
//  ....1...1  0
//  ....1..1.  1
//  ....1..11  1
//  ....1.1..  1
//  ....11...  0
//
// The sequence tr is the fixed point
// of the morphism  0 |--> 00110,  1 |--> 00111.
// Cf. OEIS sequence A175337.
//
// Also fixed point of morphism (identify + with 0 and - with 1)
// F |--> F+F+F-F-F,  + |--> +,  - |--> -
{
    ulong s = 0;
    while ( (x & 7) == 4 )  { x >>= 3;  ++s; }  // scan over nines
    bool tr = ( (x & 7) >= 2 );  // whether digit will be > 2
    ++x;  // increment next digit
    x <<= (3*s);  // shift back
    return  tr;
}
// -------------------------


#endif  // !defined HAVE_BIT_DRAGON_R5_H__
