#if !defined  HAVE_BIT_DRAGON3_H__
#define       HAVE_BIT_DRAGON3_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline bool bit_dragon3_turn(ulong &x)
// Increment the radix-3 word x and return (tr)
//   whether the number of ones in x is decreased.
// tr determines whether to turn left or right (by 120 degrees)
//   with the terdragon fractal.
//
// Starting with x==0:
//  x (binary) tr   x (ternary)
//  ........   0    0 0 0
//  .......1   0    0 0 1
//  ......1.   1    0 0 2
//  .....1..   0    0 1 0
//  .....1.1   0    0 1 1
//  .....11.   1    0 1 2
//  ....1...   1    0 2 0
//  ....1..1   0    0 2 1
//  ....1.1.   1    0 2 2
//  ...1....   0    1 0 0
// The sequence tr (for x>=1) is entry A080846 in the OEIS,
// the fixed point of the morphism  0 |--> 010,  1 |--> 011.
// See also A060236 (== 1,2,1,1,2,2,1,2,1,1,2,1,1,2,2,1,2,2,1,2, ...).
// Also fixed point of morphism (for k>0, identify + with 0 and - with 1)
// F |--> F+F-F,  + |--> +,  - |--> -
{
    ulong s = 0;
    while ( (x & 3) == 2 )  { x >>= 2;  ++s; }  // scan over nines
//    if ( (x & 3) == 0 )  ==> incremented word will have one more 1
//    if ( (x & 3) == 1 )  ==> incremented word will have one less 1
    bool tr = ( (x & 3) != 0 );  // incremented word will have one less 1
    ++x;  // increment next digit
    x <<= (s<<1);  // shift back
    return  tr;
}
// -------------------------


#endif  // !defined HAVE_BIT_DRAGON3_H__
