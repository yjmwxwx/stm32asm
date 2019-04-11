#if !defined HAVE_XORPERMUTE_H__
#define      HAVE_XORPERMUTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "aux0/swap.h"


template <typename Type>
inline void xor_permute(Type *f, ulong n, ulong x)
// Self-inverse.
// n must be divisible by the smallest power of 2
//   that is greater than x
// e.g. x=1  --> n must be even
// e.g. x=2,3  --> n must be divisible by four
// With n a power of 2 and x<n one is on the safe side
{
    if ( 0==x )  return;
    for (ulong k=0; k<n; ++k)
    {
        ulong r = k^x;
        if ( r>k )  swap2(f[r], f[k]);
    }
}
// -------------------------


#endif  // !defined HAVE_XORPERMUTE_H__
