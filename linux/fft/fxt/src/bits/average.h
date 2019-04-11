#if !defined HAVE_AVERAGE_H__
#define      HAVE_AVERAGE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


static inline ulong average(ulong x, ulong y)
// Return floor( (x+y)/2 )
// Result is correct even if (x+y) wouldn't fit into a ulong
// Use:      x+y == ((x&y)<<1) + (x^y)
// that is:  sum ==  carries   + sum_without_carries
{
    return  (x & y) + ((x ^ y) >> 1);
    // return  y + ((x-y)>>1);  // works if x>=y
}
// -------------------------

static inline ulong ceil_average(ulong x, ulong y)
// Return ceil( (x+y)/2 )
// Result is correct even if (x+y) wouldn't fit into a ulong
// Use:      x+y == ((x|y)<<1) - (x^y)
// ceil_average(x,y) == average(x,y) + ((x^y)&1))
{
    return  (x | y) - ((x ^ y) >> 1);
}
// -------------------------



#endif  // !defined HAVE_AVERAGE_H__
