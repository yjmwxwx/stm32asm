#if !defined HAVE_RADIXPERMUTE_H__
#define      HAVE_RADIXPERMUTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"


template <typename Type>
void radix_permute(Type *f, ulong n, ulong r)
//
// Swap all pairs of elements with index pairs i, j where the
// radix-r representation of i and j are mutually
// digit-reversed (e.g. 436 <--> 634)
//
// Radix-r generalization of revbin_permute():
// revbin_permute(f, n) does the same as radix_permute(f, n, 2)
//
// Must have:  n == r**x for some x>=1  and  r >= 2
//
// Original by Andre Piotrowski.
// This optimized version avoids the (n*log(n)) divisions
// by using two size-BITS_PER_LONG tables NT[], KT[]
//
{
    ulong NT[BITS_PER_LONG];  // == 9, 90, 900, ...  for r=10
    ulong KT[BITS_PER_LONG];  // == 1, 10, 100, ...  for r=10
    NT[0] = r-1;
    KT[0] = 1;

    ulong x = 0;
    while ( 1 )
    {
        ulong z = KT[x] * r;
        if ( z>n )  break;
        ++x;
        KT[x] = z;

        NT[x] = NT[x-1] * r;
    }
    // here: n == r**x

    for (ulong i=0, j=0;  i < n-1;  i++)
    {
        if ( i<j )  swap2(f[i], f[j]);

        ulong t = x - 1;
        ulong k = NT[t];  // k = (r-1) * n / r;

        while ( k<=j )
        {
            j -= k;
            k = NT[--t];  // k /= r;
        }

        j += KT[t];  // j += (k/(r-1));
    }
}
// -------------------------


#endif  // !defined HAVE_RADIXPERMUTE_H__
