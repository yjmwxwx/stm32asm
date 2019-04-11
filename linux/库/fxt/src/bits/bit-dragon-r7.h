#if !defined  HAVE_BIT_DRAGON_R7_H__
#define       HAVE_BIT_DRAGON_R7_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline bool bit_dragon_r7_turn(ulong &x)
// Increment the radix-7 word x and
// return (tr) whether the lowest nonzero digit
// of the incremented word is either 2, 3, or 6.
// tr determines whether to turn left or right (by 120 degrees)
// with the R7-dragon fractal.
//
// Starting with x==0:
//      x      tr
//  .........  0
//  ........1  1
//  .......1.  1
//  .......11  0
//  ......1..  0
//  ......1.1  1
//  ......11.  0
//  .....1...  0
//  .....1..1  1
//  .....1.1.  1
//  .....1.11  0
//  .....11..  0
//  .....11.1  1
//  .....111.  1
//  ....1....  0
//  ....1...1  1
//  ....1..1.  1
//  ....1..11  0
//  ....1.1..  0
//
// The sequence tr is the fixed point
// of the morphism  0 |--> 0100110,  1 |--> 0110110.
// Cf. OEIS sequence A176405.
//
// Also fixed point of morphism (identify + with 0 and - with 1)
// F |--> F+F-F-F+F+F-F,  + |--> +,  - |--> -
{
    ulong s = 0;
    while ( (x & 7) == 6 )  { x >>= 3;  ++s; }  // scan over nines
    ++x;  // increment next digit
//    bool tr = ( (x & 7) & 2 );  // whether digit is either 2, 3, or 6
    bool tr = ( x & 2 );  // whether digit is either 2, 3, or 6
    x <<= (3*s);  // shift back
    return  tr;
}
// -------------------------


static inline int bit_dragon_r7_2_turn(ulong &x)
// Increment the radix-7 word x and
// return (tr) according to the lowest nonzero digit d
// of the incremented word:
//  d==[1,2,3,4,5,6]  ==>  rt:=[0,+1,+1,-1,-1,0]
// (tr * 120deg) is the turn with the second R7-dragon.
//
// Starting with x==0:
//      x      tr
//  .........  0
//  ........1  +
//  .......1.  +
//  .......11  -
//  ......1..  -
//  ......1.1  0
//  ......11.  0
//  .....1...  0
//  .....1..1  +
//  .....1.1.  +
//  .....1.11  -
//  .....11..  -
//  .....11.1  0
//  .....111.  +
//  ....1....  0
//  ....1...1  +
//  ....1..1.  +
//  ....1..11  -
//  ....1.1..  -
//  ....1.1.1  0
//  ....1.11.  +
//  ....11...  0
//  ....11..1  +
//
// The sequence tr is the fixed point of the morphism
//   0 |--> 0++--00,  + |--> 0++--0+,  - |--> 0++--0-
// Cf. OEIS sequence A176416.
//
// Also fixed point of morphism
// F |--> F0F+F+F-F-F0F,   + |--> +,  - |--> -,  0 |--> 0
{
    ulong s = 0;
    while ( (x & 7) == 6 )  { x >>= 3;  ++s; }  // scan over nines
    ++x;  // increment next digit
    int tr = 2 - ( (0x2f58 >> (2*(x&7)) ) & 3 );
    x <<= (3*s);  // shift back
    return  tr;
}
// -------------------------


#endif  // !defined HAVE_BIT_DRAGON_R7_H__
