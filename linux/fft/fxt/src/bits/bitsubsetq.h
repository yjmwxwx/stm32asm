#if !defined  HAVE_BITSUBSETQ_H__
#define       HAVE_BITSUBSETQ_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

static inline bool is_subset(ulong u, ulong e)
// Return whether the set bits of u are a subset of the set bits of e.
// That is, as bitsets, test whether u is a subset of e.
{
    return  ( (u & e)==u );
//    return  ( (u & ~e)==0 );
//    return  ( (~u | e)!=0 );
}
// -------------------------

static inline bool is_proper_subset(ulong u, ulong e)
// Return whether u (as bitset) is a proper subset of e.
{
//    return  ( (u<e) && ( (u & e)==u ) );
    return  ( (u<e) & ((u & e)==u) );  // avoid branch
}
// -------------------------

#endif  // !defined HAVE_BITSUBSETQ_H__
