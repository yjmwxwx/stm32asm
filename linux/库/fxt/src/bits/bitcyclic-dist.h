#if !defined HAVE_BITCYCLIC_DIST_H__
#define      HAVE_BITCYCLIC_DIST_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitcount.h"
#include "bits/bitrotate.h"


static inline ulong bit_cyclic_dist(ulong a, ulong b)
// Return minimal bitcount of (t ^ b)
// where t runs through the cyclic rotations of a.
{
    ulong d = ~0UL;
    ulong t = a;
    do
    {
        ulong z = t ^ b;
        ulong e = bit_count( z );
        if ( e < d )  d = e;
        t = bit_rotate_right(t, 1);
    }
    while ( t!=a );
    return  d;
}
// -------------------------

static inline ulong bit_cyclic_dist(ulong a, ulong b, ulong n)
// Return minimal bitcount of (t ^ b)
// where t runs through the cyclic rotations of a.
// Using n-bit words.
{
    ulong d = ~0UL;
    const ulong m = ~0UL >> (BITS_PER_LONG - n);
    b &= m;
    a &= m;
    ulong t = a;
    do
    {
        ulong z = t ^ b;
        ulong e = bit_count( z );
        if ( e < d )  d = e;
        t = bit_rotate_right(t, 1, n);
    }
    while ( t!=a );
    return  d;
}
// -------------------------


#endif  // !defined HAVE_BITCYCLIC_DIST_H__
