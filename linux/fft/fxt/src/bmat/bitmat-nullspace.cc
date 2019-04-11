// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bmat/bitmat-inline.h"

#include "fxtalloca.h"
#include "fxttypes.h"

ulong
bitmat_nullspace(const ulong *M, ulong n, ulong *Ns)
// Write basis of nullspace of M to Ns.
// M is a binary (n x n) matrix (elements over GF(2)).
// Return r, the number of vectors of the nullspace.
// 0<=r<=n  (r==n only for M==0)
// rank(M) = n-r
//.
// Implementation following Knuth.
{
    ALLOCA(ulong, C, n);
    for (ulong k=0; k<n; ++k)  C[k] = ~0UL;
    ulong c = ~0UL;  // bit(j)==0  iff  C[j]!=~0

    ALLOCA(ulong, T, n);
    for (ulong k=0; k<n; ++k)  T[k] = M[k];

    ulong r = 0;  // size of nullspace
    ulong bk = 1;  // bk == 1<<k
    for (ulong k=0;  k<n;  ++k, bk<<=1)
    {
        ulong bj = 1;  // bj == 1<<j
        ulong j = 0;
        for (  ;  j<n;  ++j, bj<<=1)  // scan column
        {
            if ( 0== (bj & c) )  continue;

            ulong mj = T[j];
            if ( mj & bk )
            {
                for (ulong i=0; i<n; ++i)
                {
                    if ( i==j )  continue;
                    if ( T[i] & bk )  T[i] ^= mj;
                }

                c ^= bj;
                C[j] = k;
                goto endscan;
            }
        }
    endscan:

        if ( j==n )  // output vector
        {
            ulong v = 0;
            for (ulong s=0; s<n; ++s)
            {
                ulong i = C[s];
                if ( i > n )  continue;
                if ( 0==( T[s] & (1UL<<k) ) )  continue;
                v |= (1UL<<i);
            }
            v |= (1UL<<k);
            Ns[r] = v;
            ++r;
        }
    }

    return  r;
}
// -------------------------


ulong
bitmat_test_nullspace(const ulong *M, ulong n, const ulong *Ns, ulong r)
// (print and) check nullspace as returned by bitmat_nullspace()
// Return k<r if vector k is not in nullspace.
{
    for (ulong k=0; k<r; ++k)
    {
        ulong v = Ns[k];
        ulong z = bitmat_mult_Mv(M, n, v);
        if ( 0!=z )  return k;
    }
    return  r;
}
// -------------------------
