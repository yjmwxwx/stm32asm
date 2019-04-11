// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "bits/bitsperlong.h"

#include "fxttypes.h"
#include "fxtalloca.h"
#include "restrict.h"

//#include "jjassert.h"
//#include "fxtio.h"


bool
is_counting_sorted(const ulong *f, ulong n, ulong b0, ulong m)
// Whether f[] is sorted wrt. bits b0,...,b0+z-1
//  where z is the number of bits set in m.
// m must contain a single run of bits starting at bit zero.
{
    m <<= b0;
    for (ulong k=1; k<n; ++k)
    {
        ulong xm = (f[k-1] & m ) >> b0;
        ulong xp = (f[k] & m ) >> b0;
        if ( xm>xp )  return false;
    }
    return true;
}
// -------------------------

void
counting_sort_core(const ulong * restrict f, ulong n, ulong * restrict g, ulong b0, ulong m)
// Write to g[] the array f[] sorted wrt. bits b0,...,b0+z-1
//  where z is the number of bits set in m.
// m must contain a single run of bits starting at bit zero.
{
    ulong nb = m + 1;
    m <<= b0;
    ALLOCA(ulong, cv, nb);
    for (ulong k=0; k<nb; ++k)  cv[k] = 0;

    // --- count:
    for (ulong k=0; k<n; ++k)
    {
        ulong x = (f[k] & m ) >> b0;
        ++cv[ x ];
    }

#if 1
    // --- cumulative sums:
    for (ulong k=1; k<nb; ++k)  cv[k] += cv[k-1];

    // --- reorder:
    ulong k = n;
    while ( k-- )  // backwards ==> stable sort
    {
        ulong fk = f[k];
        ulong x = (fk & m) >> b0;
//        jjassert( x<nb );
        --cv[x];
        ulong i = cv[x];
//        jjassert( i<n );
        g[i] = fk;
    }

#else
#error "fails"
    // --- descending:
    { ulong k=nb-1;  while ( k-- )  cv[k] += cv[k+1]; }

    for (ulong k=0; k<n; ++k)
    {
        ulong fk = f[k];
        ulong x = (fk & m) >> b0;
//        jjassert( x<nb );
        --cv[x];
        ulong i = cv[x];
//        jjassert( i<n );
        g[i] = fk;
    }
#endif
}
// -------------------------


void
radix_sort(ulong *f, ulong n)
{
    ulong nb = 8;  // Number of bits sorted with each step
    ulong tnb = BITS_PER_LONG;  // Total number of bits

    ulong *fi = f;
    ulong *g = new ulong[n];

    ulong m = (1UL<<nb) - 1;
    for (ulong k=1, b0=0;  b0<tnb;  ++k, b0+=nb)
    {
        counting_sort_core(f, n, g, b0, m);
        swap2(f, g);
//        jjassert( is_counting_sorted(f, n, b0, m) );
    }

    if ( f!=fi )  // result is actually in g[]
    {
        swap2(f, g);
        for (ulong k=0; k<n; ++k)  f[k] = g[k];
    }

    delete [] g;
}
// -------------------------
