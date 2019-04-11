// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtalloca.h"
#include "fxttypes.h"


void
bitmat_transpose(const ulong *M, ulong n, ulong *T)
// Transpose binary (n x n) matrix M:  T = transpose(M).
{
    ALLOCA(ulong, A, n);
    for (ulong i=0; i<n; ++i)  A[i] = 0;
    for (ulong i=0; i<n; ++i)
    {
        ulong z = M[i];
        for (ulong j=0; j<n; ++j)
        {
            ulong u = z & 1UL;
            z >>= 1;
            A[j] |= (u << i);
        }
    }
    for (ulong k=0; k<n; ++k)  T[k] = A[k];
}
// -------------------------
