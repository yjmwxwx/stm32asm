#if !defined  HAVE_BIT_DRAGON_R4_H__
#define       HAVE_BIT_DRAGON_R4_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline int bit_dragon_r4_turn(ulong &x)
// Increment the radix-4 word x and
// return (tr) as follows:
// +1 if lowest nonzero digit of the incremented word is 1,
//   0 if it is 2, otherwise -1 (when it is 3).
// tr determines whether to turn left(-1), right(+1), or not at all(0)
// (by 120 degrees) with the R4-dragon fractal.
//
// The sequence tr starts
//  +0-++0-0+0--+0-++0-++0-0+0--+0-0+0-++0-0+0--+0--+0-++0-0+0--+0-
//
// The sequence tr is the fixed point of morphism
//   + |--> +0-+,  0 |--> +0-0,  - |--> +0--
//
// Also fixed point of morphism
//   F |--> F+F0F-F,  0 |--> 0,  - |--> -,  + |--> +
//  (after omitting the symbols F)
//
// The OEIS sequence A035263 gives the absolute values,
// see also A029883 (different signs).
{
    ulong s = 0;
    while ( (x & 3) == 3 )  { x >>= 2;  ++s; }  // scan over nines
    ++x;  // increment next digit
    int tr = (int)( 2 - (x & 3) );
    x <<= (2*s);  // shift back
    return  tr;
}
// -------------------------


#endif  // !defined HAVE_BIT_DRAGON_R4_H__
