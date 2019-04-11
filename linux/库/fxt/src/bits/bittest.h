#if !defined  HAVE_BITTEST_H__
#define       HAVE_BITTEST_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

static inline ulong test_bit(ulong a, ulong i)
// Return zero if bit[i] is zero,
//  else return one-bit word with bit[i] set.
{
    return  (a & (1UL << i));
}
// -------------------------

static inline bool test_bit01(ulong a, ulong i)
// Return whether bit[i] is set.
{
    return ( 0 != test_bit(a, i) );
}
// -------------------------


static inline ulong set_bit(ulong a, ulong i)
// Return a with bit[i] set.
{
    return  (a | (1UL << i));
}
// -------------------------

static inline ulong clear_bit(ulong a, ulong i)
// Return a with bit[i] cleared.
{
    return  (a & ~(1UL << i));
}
// -------------------------

static inline ulong change_bit(ulong a, ulong i)
// Return a with bit[i] changed.
{
    return  (a ^ (1UL << i));
}
// -------------------------

#endif  // !defined HAVE_BITTEST_H__
