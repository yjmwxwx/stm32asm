// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/perminvert.h"
#include "perm/permcompose.h"

#include "aux1/copy.h"
#include "bits/bit2pow.h"
#include "ds/bitarray.h"

#include "fxttypes.h"
#include "restrict.h"


void
make_square(const ulong *f, ulong * restrict g, ulong n)
// Set (as permutation) g = f * f
{
    for (ulong k=0; k<n; ++k)  g[k] = f[f[k]];
}
// -------------------------


void
make_square(ulong *f, ulong n, bitarray *bp/*=0*/)
// Set (as permutation) f = f * f
// In-place version.
{
    bitarray *tp = bp;
    if ( 0==bp )  tp = new bitarray(n);  // tags
    tp->clear_all();

    for (ulong k=0; k<n; ++k)
    {
        if ( tp->test_clear(k) )  continue;  // already processed
        tp->set(k);

        // square a cycle:
        ulong i = k;
        ulong t = f[i];  // save
        ulong g = f[i];  // next index
        while ( 0==(tp->test_set(g)) )
        {
            f[i] = f[g];
            i = g;
            g = f[g];
        }
        f[i] = t;
    }

    if ( 0==bp )  delete tp;
}
// -------------------------


void
compose(const ulong *f, const ulong *g, ulong * restrict h, ulong n)
// Set (as permutation) h = f * g
{
    for (ulong k=0; k<n; ++k)  h[k] = f[g[k]];
}
// -------------------------


void
compose(const ulong *f, ulong * restrict g, ulong n)
// Set (as permutation) g = f * g
{
    for (ulong k=0; k<n; ++k)  g[k] = f[g[k]];  // yes, this works
}
// -------------------------


void
power(const ulong *f, ulong * restrict g, ulong n,
      long e,
      ulong * restrict t/*=0*/)
// Set (as permutation) g = f ** e
{
    if ( e==0 )
    {
        for (ulong k=0; k<n; ++k)  g[k] = k;
        return;
    }

    if ( e==1 )
    {
        acopy(f, g, n);
        return;
    }

    if ( e==-1 )
    {
        make_inverse(f, g, n);
        return;
    }

    // here:  abs(e) > 1
    ulong x = (ulong)(e>0 ? e : -e);  // jjcast

    if ( is_pow_of_2(x) )  // special case x==2^n
    {
        make_square(f, g, n);
        // GCC 4.9.1 with -Wstrict-overflow=5 issues the warning
        // "assuming signed overflow does not occur when ..."
        // This is a false positive.
        while ( x > 2 )  { make_square(g, n);  x /= 2; }
    }
    else
    {
        ulong *tt = t;
        if ( 0==t )  { tt = new ulong[n]; }
        acopy(f, tt, n);

        int firstq = 1;
        while ( 1 )
        {
            if ( x&1 )  // odd
            {
                if ( firstq )  // avoid multiplication by 1
                {
                    acopy(tt, g, n);
                    firstq = 0;
                }
                else  compose(tt, g, n);

                if ( x==1 )   goto dort;
            }

            make_square(tt, n);
            x /= 2;
        }

    dort:
        if ( 0==t )  delete [] tt;
    }


    if ( e<0 )  make_inverse(g, n);
}
// -------------------------
