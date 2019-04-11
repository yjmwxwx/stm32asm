// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bmat/bitmat-inline.h"  // bitmat_get(), bitmat_set()
#include "fxttypes.h"
#include "restrict.h"
//#include "bits/bitsperlong.h"


void
bitmat_kronecker(const ulong *M1, ulong n1,
                 const ulong *M2, ulong n2,
                 ulong * restrict K)
// Set K = M1 (*) M2, where (*) denotes the Kronecker product.
// Must have n1*n2 <= BITS_PER_LONG.
//.
// Could be optimized.
{
    ulong r1, c1, r2, c2;
    r1 = c1 = n1;
    r2 = c2 = n2;

    ulong rk;
    rk = r1 * r2;

    for (ulong k=0; k<rk; ++k)  K[k] = 0;

    for (ulong i=0; i<r1; ++i)
    {
        ulong tr = i * r2;
        for (ulong j=0; j<c1; ++j)
        {
            ulong M1ij = bitmat_get(M1, i, j);
            if ( 0==M1ij )  continue;

            ulong tc = j * c2;
            for (ulong k=0; k<r2; ++k)
            {
                for (ulong l=0; l<c2; ++l)
                {
                    ulong M2kl = bitmat_get(M2, k, l);
                    if ( 0==M2kl )  continue;

                    //  K[k+tr, l+tc] = M1[i, j] * M2[k, l];
                    bitmat_set(K, k+tr, l+tc, 1UL);
                }
            }
        }
    }
}
// -------------------------
