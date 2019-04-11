#if !defined HAVE_BITCYCLIC_PERIOD_H__
#define      HAVE_BITCYCLIC_PERIOD_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitrotate.h"
#include "bits/bitsperlong.h"
#include "bits/tinyfactors.h"  // tiny_factors_tab[]



static inline ulong bit_cyclic_period(ulong x)
// Return minimal positive bit-rotation that transforms x into itself.
// (same as bit_cyclic_period(x, BITS_PER_LONG) )
//
// The returned value is a divisor of the word length,
//   i.e. 1,2,4,8,...,BITS_PER_LONG.
{
    ulong r = 1;
    do
    {
        ulong y = bit_rotate_right(x, r);
        if ( x==y )  return r;
        r <<= 1;
    }
    while ( r < BITS_PER_LONG );

    return  r;  // == BITS_PER_LONG
}
// -------------------------

static inline ulong bit_cyclic_period(ulong x, ulong n)
// Return minimal positive bit-rotation that transforms x into itself.
//  (using n-bit words)
// The returned value is a divisor of n.
//
// Examples for n=6:
//   word   period
//  ......  1
//  .....1  6
//  ....11  6
//  ...1.1  6
//  ...111  6
//  ..1..1  3
//  ..1.11  6
//  ..11.1  6
//  ..1111  6
//  .1.1.1  2
//  .1.111  6
//  .11.11  3
//  .11111  6
//  111111  1
{
    // Simple minded implementation:
//    ulong y = bit_rotate_right(x, 1, n);
//    return  bit_cyclic_match(x, y, n) + 1;

    // Optimized, could further test divisors of n only
//    ulong sl = BITS_PER_LONG-n;
//    for (ulong s=1; s<n; ++s)
//    {
//        ++sl;
//        if ( 0==( (x^(x>>s)) << sl ) )  return s;
//    }
//    return n;

    // Optimized, by testing divisors of n only
    ulong f = tiny_factors_tab[n];
    ulong sl = BITS_PER_LONG - n;
    for (ulong s=1; s<n; ++s)
    {
        ++sl;
        f >>= 1;
        if ( 0==(f&1) )  continue;
        if ( 0==( (x^(x>>s)) << sl ) )  return s;
    }
    return n;
}
// -------------------------


#endif  // !defined HAVE_BITCYCLIC_PERIOD_H__
