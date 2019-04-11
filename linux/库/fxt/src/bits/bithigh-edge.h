#if !defined HAVE_BITHIGH_EDGE_H__
#define      HAVE_BITHIGH_EDGE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitasm.h"


static inline ulong highest_one_01edge(ulong x)
// Return word where all bits from (including) the
//   highest set bit to bit 0 are set.
// Return 0 if no bit is set.
//
// Feed the result into bit_count() to get
//   the index of the highest bit set.
{
#if defined  BITS_USE_ASM

    if ( 0==x )  return 0;
    x = asm_bsr(x);
    return  (2UL<<x) - 1;

#else  // BITS_USE_ASM

    x |= x>>1;
    x |= x>>2;
    x |= x>>4;
    x |= x>>8;
    x |= x>>16;
#if  BITS_PER_LONG >= 64
    x |= x>>32;
#endif
    return  x;
#endif  // BITS_USE_ASM
}
// -------------------------

static inline ulong highest_one_10edge(ulong x)
// Return word where all bits from  (including) the
//   highest set bit to most significant bit are set.
// Return 0 if no bit is set.
{
    if ( 0==x )  return 0;
    x = highest_one_01edge(x);
    return  ~(x>>1);
}
// -------------------------


#endif  // !defined HAVE_BITHIGH_EDGE_H__
