#if !defined HAVE_BIT_ISOLATE_H__
#define      HAVE_BIT_ISOLATE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//<<
// Extraction of ones, zeros, or blocks near transitions.
// Here we assume that the outside bits are all zero.
// Therefore we have
//   interior_values(v) != ( interior_ones(v) | interior_ones(~v) )
// Functions ignoring outside values have names ending in _xi
//>>


static inline ulong single_ones(ulong x)
// Return word with only the isolated ones of x set.
// Assume outside values are 0.
{
    return  x & ~( (x<<1) | (x>>1) );
}
// -------------------------

static inline ulong single_ones_xi(ulong x)
// Return word with only the isolated ones of x set.
// Ignore outside values.
{
    return  single_ones(x);  // (identical function)
}
// -------------------------

static inline ulong single_zeros(ulong x)
// Return word with only the isolated zeros of x set.
// Assume outside values are 0.
{
    return  ~x & ( (x<<1) & (x>>1) );
}
// -------------------------

static inline ulong single_zeros_xi(ulong x)
// Return word with only the isolated zeros of x set.
// Ignore outside values.
{
    return  single_ones( ~x );
}
// -------------------------


static inline ulong single_values(ulong x)
// Return word where only the isolated ones and zeros of x are set.
// Assume outside values are 0.
{
    return  (x ^ (x<<1)) & (x ^ (x>>1));
}
// -------------------------

static inline ulong single_values_xi(ulong x)
// Return word where only the isolated ones and zeros of x are set.
// Ignore outside values.
{
    return  single_ones_xi(x) | single_zeros_xi(x);
}
// -------------------------


static inline ulong border_ones(ulong x)
// Return word where only those ones of x are set that lie next to a zero.
{
//    ulong t = x & (x>>1) & (x<<1);  // interior_ones(x)
//    return  x ^ t;
    return  x & ~( (x<<1) & (x>>1) );
}
// -------------------------

static inline ulong border_values(ulong x)
// Return word where those bits of x are set that lie on a transition.
// Assume outside values are 0.
{
    return  (x ^ (x<<1)) | (x ^ (x>>1));
}
// -------------------------

static inline ulong high_border_ones(ulong x)
// Return word where only those ones of x are set
//   that lie right to (i.e. in the next lower bin of) a zero.
{
    return  x & ( x ^ (x>>1) );
}
// -------------------------

static inline ulong low_border_ones(ulong x)
// Return word where only those ones of x are set
//   that lie left to (i.e. in the next higher bin of) a zero.
{
    return  x & ( x ^ (x<<1) );
}
// -------------------------


static inline ulong block_border_ones(ulong x)
// Return word where only those ones of x are set
//   that are at the border of a block of at least 2 ones.
{
    return  x & ( (x<<1) ^ (x>>1) );
}
// -------------------------

static inline ulong low_block_border_ones(ulong x)
// Return word where only those ones of x are set
//   that are at left of a border of a block of at least 2 ones.
{
    ulong t = x & ( (x<<1) ^ (x>>1) );  // block_border_ones()
    return  t & (x>>1);
}
// -------------------------

static inline ulong high_block_border_ones(ulong x)
// Return word where only those ones of x are set
//   that are at right of a border of a block of at least 2 ones.
{
    ulong t = x & ( (x<<1) ^ (x>>1) );  // block_border_ones()
    return  t & (x<<1);
}
// -------------------------


static inline ulong block_ones(ulong x)
// Return word where only those ones of x are set
//   that are part of a block of at least 2 ones.
{
    return  x & ( (x<<1) | (x>>1) );
}
// -------------------------

static inline ulong block_values(ulong x)
// Return word where only those bits of x are set
// that do not lie next to an opposite value.
{
    return  ~single_values(x);
}
// -------------------------


static inline ulong interior_ones(ulong x)
// Return word where only those ones of x are set
//   that do not have a zero to their left or right.
{
    return  x & ( (x<<1) & (x>>1) );
}
// -------------------------

static inline ulong interior_values(ulong x)
// Return word where only those values of x are set
//   that do have a transitions on both sides.
{
    return  ~border_values(x);
}
// -------------------------


#endif  // !defined HAVE_BIT_ISOLATE_H__
