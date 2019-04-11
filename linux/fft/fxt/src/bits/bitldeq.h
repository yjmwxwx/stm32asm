#if !defined HAVE_BITLDEQ_H__
#define      HAVE_BITLDEQ_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


static inline bool ld_eq(ulong x, ulong y)
// Return whether floor(log2(x))==floor(log2(y)).
// For arguments 0 and 1 (either order)
// ld_eq(x,y) correctly returns false
// whereas ld(x) == ld(y) gives true
// (because ld(x) returns 0 for both x==1 and x==0).
{
    return  ( (x^y) <= (x&y) );
}
// -------------------------

static inline bool ld_neq(ulong x, ulong y)
// Return whether floor(log2(x))!=floor(log2(y))
{
    return  ( (x^y) > (x&y) );
}
// -------------------------


#endif  // !defined HAVE_BITLDEQ_H__
