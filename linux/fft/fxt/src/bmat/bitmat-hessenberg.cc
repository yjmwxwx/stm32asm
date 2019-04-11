// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bmat/bitmat-inline.h"  // bitmat_get()
#include "bits/bitswap.h"  // bit_swap()
#include "aux0/swap.h"  // swap2()
#include "fxttypes.h"  // ulong

bool
bitmat_is_hessenberg(const ulong *H, ulong n)
// Return true if H is in Hessenberg form, else false.
{
    for (ulong k=2, m=1;  k<n;  ++k, m<<=1, m^=1)
    {
        if ( H[k] & m )  return false;
    }
    return true;
}
// -------------------------


static inline ulong bit_xor(ulong a, ulong k1, ulong k2)
// Return a with bit k1 XOR-ed to position k2.
// Used for adding columns in bit-matrices.
{
    const ulong b = (a >> k1) & 1;
    return  a  ^ (b<<k2);
}
// -------------------------

void
bitmat_hessenberg(const ulong *M, ulong n, ulong *H)
// Set H to the Hessenberg form of M.
//.
// cf. Cohen p.55
{
    bitmat_copy(M, n, H);  // H=M

    for (ulong m=1; m<n-1; ++m)
    {
        // 2 [Search non-zero]:
        ulong i;
        for (i=m+1; i<n; ++i)  if ( bitmat_get(H, i, m-1) )  break;
        if ( i==n )  continue;

        // t == 1;
        if ( i>m )
        {
            swap2(H[i], H[m]);
            for (ulong c=0; c<n; ++c)  H[c] = bit_swap(H[c], i, m);
        }

        // 3 [Eliminate]:
        for (i=m+1; i<n; ++i)
        {
            ulong q = bitmat_get(H, i, m-1);
            if ( q )
            {
                // u = bitmat_get(H, i, m-1)/t  == 1
                H[i] ^= H[m];
                for (ulong c=0; c<n; ++c)  H[c] = bit_xor(H[c], i, m);
            }
        }
    }
}
// -------------------------
