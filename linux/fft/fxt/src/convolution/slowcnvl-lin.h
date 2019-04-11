#if !defined  HAVE_SLOWCNVL_LIN_H__
#define       HAVE_SLOWCNVL_LIN_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

template <typename Type>
void slow_linear_convolution(const Type *f, const Type *g, Type *h, ulong n)
// Linear (acyclic) convolution.
// n := array length of a[] and b[]
// The array h[] must have 2*n elements.
{
    // compute h0 (left half):
    for (ulong tau=0;  tau<n;  ++tau)
    {
        Type s0 = 0;
        for (ulong k=0, k2=tau;  k<=tau;  ++k, --k2)  s0 += (f[k]*g[k2]);
        h[tau] = s0;
    }

    // compute h1 (right half):
    for (ulong tau=0;  tau<n;  ++tau)
    {
        Type s1 = 0;
        for (ulong k2=n-1, k=tau+1;  k<n;  ++k, --k2)  s1 += (f[k]*g[k2]);
        h[n+tau] = s1;
    }
}
// -------------------------


#endif  // !defined HAVE_SLOWCNVL_LIN_H__
