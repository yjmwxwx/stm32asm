#if !defined HAVE_BITCYCLIC_MINMAX_H__
#define      HAVE_BITCYCLIC_MINMAX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitrotate.h"

static inline ulong bit_cyclic_min(ulong x)
// Return minimum of all rotations of x
{
    ulong r = 1;
    ulong m = x;
    do
    {
        x = bit_rotate_right(x, 1);
        if ( x<m )  m = x;
    }
    while ( ++r < BITS_PER_LONG );

    return  m;
}
// -------------------------

static inline ulong bit_cyclic_min(ulong x, ulong n)
// Return minimum of all rotations of x using n-bit words
{
    ulong r = 1;
    ulong m = x;
    do
    {
        x = bit_rotate_right(x, 1, n);
        if ( x<m )  m = x;
    }
    while ( ++r < n );

    return  m;
}
// -------------------------


static inline ulong bit_cyclic_max(ulong x)
// Return maximum of all rotations of x
{
    ulong r = 1;
    ulong m = x;
    do
    {
        x = bit_rotate_right(x, 1);
        if ( x>m )  m = x;
    }
    while ( ++r < BITS_PER_LONG );

    return  m;
}
// -------------------------

static inline ulong bit_cyclic_max(ulong x, ulong n)
// Return maximum of all rotations of x using n-bit words
{
    ulong r = 1;
    ulong m = x;
    do
    {
        x = bit_rotate_right(x, 1, n);
        if ( x>m )  m = x;
    }
    while ( ++r < n );

    return  m;
}
// -------------------------


static inline bool is_bit_cyclic_min(ulong x)
// Return whether x is the minimum of all rotations of x
{ return  ( x == bit_cyclic_min(x) ); }

static inline bool is_bit_cyclic_min(ulong x, ulong n)
// Return whether x is the minimum of all rotations of x as n-bit word
{ return  ( x == bit_cyclic_min(x, n) ); }


static inline bool is_bit_cyclic_max(ulong x)
// Return whether x is the maximum of all rotations of x
{ return  ( x == bit_cyclic_max(x) ); }

static inline bool is_bit_cyclic_max(ulong x, ulong n)
// Return whether x is the maximum of all rotations of x as n-bit word
{ return  ( x == bit_cyclic_max(x, n) ); }


#endif  // !defined HAVE_BITCYCLIC_MINMAX_H__
