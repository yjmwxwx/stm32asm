#if !defined  HAVE_MAX_CONVOLUTION_H__
#define       HAVE_MAX_CONVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "sort/minmaxmed23.h"

#include "fxttypes.h"
#include "restrict.h"


template <typename Type>
inline void slow_max_convolution(const Type *f, const Type *g, ulong n, Type *h)
// Compute the MAX-convolution h[] of f[] and g[]:
//  h[k] = sum( max(i,j) == k,  f[i]*g[j])
// Result written to h[].
{
    for (ulong j=0; j<n; ++j)  h[j] = 0;
    for (ulong i=0; i<n; ++i)
        for (ulong j=0; j<n; ++j)
            h[ max2(i, j) ] += f[i] * g[j];
}
// -------------------------

template <typename Type>
inline void max_convolution(const Type *f, const Type *g, ulong n, Type *h)
// Compute the MAX-convolution h[] of f[] and g[]:
//  h[k] = sum( max(i,j) == k,  f[i]*g[j])
// Result written to h[].
{
    Type sf=0,  sg=0;  // cumulative sums
    for (ulong k=0; k<n; ++k)
    {
        h[k] = f[k]*g[k] + sf*g[k] + sg*f[k];
        sf += f[k];
        sg += g[k];
    }
}
// -------------------------


#endif  // !defined HAVE_MAX_CONVOLUTION_H__
