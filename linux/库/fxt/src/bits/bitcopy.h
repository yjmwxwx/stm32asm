#if !defined  HAVE_BITCOPY_H__
#define       HAVE_BITCOPY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"



static inline ulong copy_bit(ulong a, ulong isrc, ulong idst)
// Copy bit at [isrc] to position [idst].
// Return the modified word.
{
#if 1  // Branch free:
    ulong x = ((a>>isrc) ^ (a>>idst)) & 1;  // one if bits differ
    a ^= (x<<idst);  // change if bits differ
    return  a;
#else
    ulong v = a & (1UL << isrc);
    ulong b = 1UL << idst;
    if ( 0==v )  a &= ~b;
    else         a |=  b;
    return  a;
#endif
}
// -------------------------


static inline ulong mask_copy_bit(ulong a, ulong msrc, ulong mdst)
// Copy bit according at src-mask (msrc)
//  to the bit according to the dest-mask (mdst).
// Both msrc and mdst must have exactly one bit set.
// Return the modified word.
{
#if 1  // Branch free:
    ulong x = mdst;
    if ( msrc & a )  x = 0;  // zero if source bit set (compiled to cmov)
    x ^= mdst;  // ==mdst if source bit set, else zero
    a &= ~mdst;  // clear dest bit
    a |= x;
    return  a;
#else
    ulong v = a & msrc;
    ulong b = mdst;
    if ( 0==v )  a &= ~b;
    else         a |=  b;
    return  a;
#endif
}
// -------------------------

static inline ulong mask_or_bit(ulong a, ulong msrc, ulong mdst)
// Or bit according to src-mask (msrc)
//  to the bit according to the dest-mask (mdst).
// Both msrc and mdst must have exactly one bit set.
// If the mdst-position is known to be zero this function
//  is equivalent to mask_copy_bit().
// Return the modified word.
{
#if 1  // Branch free:
    if ( msrc & a )  mdst = 0;  // zero if source bit set (compiled to cmov)
    a |= mdst;
    return  a;
#else
    if ( a & msrc )  a |= mdst;
    return  a;
#endif
}
// -------------------------


#endif  // !defined HAVE_BITCOPY_H__
