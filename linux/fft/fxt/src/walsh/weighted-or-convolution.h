#if !defined  HAVE_WEIGHTED_OR_CONVOLUTION_H__
#define       HAVE_WEIGHTED_OR_CONVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitcount.h"
#include "aux1/copy.h"
#include "fxtalloca.h"

#include "walsh/arithtransform.h"
//#include "walsh/parity-transform.h"
#include "walsh/weighted-arithtransform.h"

#include "fxttypes.h"
#include "restrict.h"


template <typename Type>
inline void slow_weighted_or_convolution(const Type *f, const Type *g, ulong ldn, Type *h, Type w)
// Compute the weighted OR-convolution h[] of f[] and g[]:
//  h[k] = sum(i | j == k,  f[i]*g[j] * (w)**bitcount(i&j))
// Result written to h[].
{
    ALLOCA(Type, pw, ldn+1);  // powers of w, tiny table
    pw[0] = (Type)1;
    for (ulong j=1; j<=ldn; ++j)  pw[j] = w * pw[j-1];

    const ulong n = 1UL << ldn;
    for (ulong j=0; j<n; ++j)  h[j] = 0;
    for (ulong i=0; i<n; ++i)
        for (ulong j=0; j<n; ++j)
            h[i|j] += f[i] * g[j] * pw[ bit_count( i & j ) ];
}
// -------------------------

template <typename Type>
inline void slow_weighted_or_convolution(const Type *f, Type *g, ulong ldn, Type w)
// Result written to g[].
{
    const ulong n = 1UL << ldn;
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_weighted_or_convolution(f, g, ldn, h, w);
    acopy(h, g, n);
}
// -------------------------

template <typename Type>
inline void weighted_or_convolution(Type * restrict f, Type * restrict g, ulong ldn, Type w)
// Compute the weighted OR-convolution h[] of f[] and g[]:
//  h[k] = sum(i | j == k,  f[i]*g[j] * (w)**bitcount(i&j))
// f[] and g[] must not overlap.
// Result written to g[].
{
//    parity_transform(f, ldn, w);
//    parity_transform(g, ldn, w);
    arith_transform_plus(f, ldn, w);
    arith_transform_plus(g, ldn, w);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)  g[k] *= f[k];
//    inverse_parity_transform(g, ldn, w);
    arith_transform_minus(g, ldn, w);
}
// -------------------------


template <typename Type>
inline void weighted_or_auto_convolution(Type * restrict f, ulong ldn, Type w)
// Compute the weighted self- OR-convolution h[] of f[]:
//  h[k] = sum(i | j == k,  f[i]*f[j] * (w)**bitcount(i&j))
// Result written to f[].
{
//    parity_transform(f, ldn, w);
    arith_transform_plus(f, ldn, w);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)  f[k] *= f[k];
//    inverse_parity_transform(f, ldn, w);
    arith_transform_minus(f, ldn, w);
}
// -------------------------



#endif  // !defined HAVE_WEIGHTED_OR_CONVOLUTION_H__
