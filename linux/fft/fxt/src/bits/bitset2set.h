#if !defined  HAVE_BITSET2SET_H__
#define       HAVE_BITSET2SET_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


static inline ulong bitset2set(ulong b, ulong *f, ulong n, ulong off=0)
// b=[1...1.11] ==> f[] = [0,1,3,7], return=4
// with off=1   ==> f[] = [1,2,4,8], return=4
{
    ulong i = 0;
    for (ulong k=0; k<n; ++k)
    {
        if ( b&1 )  f[i++] = k+off;
        b >>= 1;
    }
    return i;  // number of elements
}
// -------------------------

static inline ulong set2bitset(const ulong *f, ulong n, ulong off=0)
// f[] = [0,1,3,7] ==>  return=[1...1.11]
// Same return with f[] = [1,2,4,8] and off=1
{
    ulong b = 0;
    for (ulong k=0; k<n; ++k)  b |= (1UL<<(f[k]-off));
    return b;
}
// -------------------------


static inline ulong bitset2deltaset(ulong b, ulong *f, ulong n)
// b=[1...1.11] ==> f[] = [1,1,0,1,0,0,0,1], return=4
{
    ulong i = 0;
    for (ulong k=0; k<n; ++k)
    {
        f[i++] = b & 1;
        b >>= 1;
    }
    return i;
}
// -------------------------


static inline ulong deltaset2bitset(const ulong *f, ulong n)
// f[] = [1,1,0,1,0,0,0,1] ==> return=[1...1.11]
{
    ulong b = 0;
    for (ulong k=0; k<n; ++k)
    {
        if ( f[k] )  b |= (1UL<<k);
    }
    return b;
}
// -------------------------



#endif  // !defined HAVE_BITSET2SET_H__
