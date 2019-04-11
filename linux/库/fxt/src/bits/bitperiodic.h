#if !defined  HAVE_BITPERIODIC_H__
#define       HAVE_BITPERIODIC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"

static inline ulong bit_copy_periodic(ulong a, ulong p)
// Return word that consists of the lowest p bits of a repeated.
// E.g.: if p==3 and a=*****xyz (8-bit), the return yzxyzxyz.
// Must have p>0.
{
    a &= ( ~0UL >> (BITS_PER_LONG-p) );
    for (ulong s=p; s<BITS_PER_LONG; s<<=1)  { a |= (a<<s); }
    return a;
}
// -------------------------

static inline ulong bit_copy_periodic(ulong a, ulong p, ulong ldn)
// Return word that consists of the lowest p bits of a repeated
// in the lowest ldn bits (upper bits are zero).
// E.g.: if p==3, ldn=7 and a=*****xyz (8-bit), the return 0zxyzxyz.
// Must have p>0 and ldn>0.
{
    a &= ( ~0UL >> (BITS_PER_LONG-p) );
    for (ulong s=p; s<ldn; s<<=1)  { a |= (a<<s); }
    a &= ( ~0UL >> (BITS_PER_LONG-ldn) );
    return a;
}
// -------------------------


#endif  // !defined HAVE_BITPERIODIC_H__
