#if !defined HAVE_BITMROTATE_H__
#define      HAVE_BITMROTATE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong bit_mrotate(const ulong f, ulong r, ulong n=BITS_PER_LONG)
// Return g where for all bits i, 0<i<n:  g[(i*r)%n] = f[i]
// Must have:  gcd(n,r)==1
{
//    if ( r>=n )  r %= n;

//    g[0] = f[0];
    ulong g = f & 1;
    for (ulong i=1, j=r;  i<n;  ++i)
    {
//        g[j] = f[i];
        g |= (((f>>i) & 1)<<j);
        j += r;
        if ( j>=n )  j -= n;
    }
    return g;
}
// -------------------------


static inline ulong bit_inverse_mrotate(const ulong f, ulong r, ulong n=BITS_PER_LONG)
// Return g where for all bits i, 0<i<n:  g[i] = f[(i*r)%n]
// Must have:  gcd(n,r)==1
{
//    if ( r>=n )  r %= n;

//    g[0] = f[0];
    ulong g = f & 1;
    for (ulong i=1, j=r;  i<n;  ++i)
    {
//        g[i] = f[j];
         g |= (((f>>j) & 1)<<i);
         j += r;
        if ( j>=n )  j -= n;
    }

    return g;
}
// -------------------------


#endif  // !defined HAVE_BITMROTATE_H__
