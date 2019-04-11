#if !defined HAVE_BITLOW_EDGE_H__
#define      HAVE_BITLOW_EDGE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


static inline ulong lowest_one_10edge(ulong x)
// Return word where all bits from (including) the
//   lowest set bit to most significant bit are set.
// Return 0 if no bit is set.
// Example:  00110100 --> 11111100
{
    return  ( x | -x );

//    if ( 0==x )  return 0;
//    x ^= (x-1);
//    // here  x == lowest_one_01edge(x);
//    return  ~(x>>1);
}
// -------------------------

static inline ulong lowest_one_01edge(ulong x)
// Return word where all bits from  (including) the
//   lowest set bit to the least significant bit are set.
// Return 0 if no bit is set.
// Example:  00110100 --> 00000111
{
    if ( 0==x )  return 0;
    return  x^(x-1);

//    return ~( x ^ -x );
}
// -------------------------




#endif  // !defined HAVE_BITLOW_EDGE_H__
