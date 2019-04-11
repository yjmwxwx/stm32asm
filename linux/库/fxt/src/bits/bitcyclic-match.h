#if !defined HAVE_BITCYCLIC_MATCH_H__
#define      HAVE_BITCYCLIC_MATCH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitrotate.h"
#include "bits/bit2pow.h"  // one_bit_q()


static inline ulong bit_cyclic_match(ulong x, ulong y)
// Return  r if x==rotate_right(y, r) else return ~0UL.
// In other words: return
//   how often the right arg must be rotated right (to match the left)
// or, equivalently:
//   how often the left arg must be rotated left (to match the right)
{
    ulong r = 0;
    do
    {
        if ( x==y )  return r;
        y = bit_rotate_right(y, 1);
    }
    while ( ++r < BITS_PER_LONG );

    return ~0UL;
}
// -------------------------

static inline ulong bit_cyclic_match(ulong x, ulong y, ulong n)
// Return  r if x==rotate_right(y, r, n) else return ~0UL
//  (using n-bit words)
{
    ulong r = 0;
    do
    {
        if ( x==y )  return r;
        y = bit_rotate_right(y, 1, n);
    }
    while ( ++r < n );

    return ~0UL;
}
// -------------------------


static inline ulong bit_cyclic_dist1_match(ulong x, ulong y)
// Return  the minimal r so that
//   c = (x ^ rotate_right(y, r, n)) is a one-bit word.
// Return ~0UL if there is no such r.
{
    ulong r = 0;
    do
    {
        ulong c = x^y;
        if ( one_bit_q(c) )  return r;
        y = bit_rotate_right(y, 1);
    }
    while ( ++r < BITS_PER_LONG );

    return ~0UL;
}
// -------------------------

static inline ulong bit_cyclic_dist1_match(ulong x, ulong y, ulong n)
// Return  the minimal r so that
//   c = (x ^ rotate_right(y, r, n)) is a one-bit word.
// Return ~0UL if there is no such r.
//  (using n-bit words)
{
    ulong r = 0;
    do
    {
        ulong c = x^y;
        if ( one_bit_q(c) )  return r;
        y = bit_rotate_right(y, 1, n);  // could used optimized version
    }
    while ( ++r < n );

    return ~0UL;
}
// -------------------------


#endif  // !defined HAVE_BITCYCLIC_MATCH_H__
