// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/parity.h"
#include "bmat/bitmat-funcs.h"  // bitmat_transpose()

#include "fxtalloca.h"
#include "fxttypes.h"


void
bitmat_mult_MM(const ulong *M1, const ulong *M2, ulong n, ulong *P)
// Multiply binary (n x n) matrices:  P = M1 * M2.
{
    ALLOCA(ulong, T, n);
    ALLOCA(ulong, T2, n);
    bitmat_transpose(M2, n, T2);
    for (ulong i=0; i<n; ++i)
    {
        ulong v1 = M1[i];
        ulong pi = 0;
        for (ulong j=0; j<n; ++j)
        {
            ulong v2 = T2[j];
            ulong p = parity( v2 & v1 );
            pi |= (p << j);
        }
        T[i] = pi;
    }
    for (ulong k=0; k<n; ++k)  P[k] = T[k];
}
// -------------------------
