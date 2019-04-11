#if !defined  HAVE_OR_CONVOLUTION_H__
#define       HAVE_OR_CONVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "walsh/arithtransform.h"

#include "aux1/copy.h"
#include "fxtalloca.h"

#include "fxttypes.h"
#include "restrict.h"


template <typename Type>
inline void slow_or_convolution(const Type *f, const Type *g, ulong ldn, Type *h)
// Compute the OR-convolution h[] of f[] and g[]:
//  h[k] = sum(i | j == k,  f[i]*g[j])
// Result written to h[].
{
    const ulong n = 1UL << ldn;
    for (ulong j=0; j<n; ++j)  h[j] = 0;
    for (ulong i=0; i<n; ++i)
        for (ulong j=0; j<n; ++j)
            h[i|j] += f[i] * g[j];
}
// -------------------------

template <typename Type>
inline void slow_or_convolution(const Type *f, Type *g, ulong ldn)
// Result written to g[].
{
    const ulong n = 1UL << ldn;
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_or_convolution(f, g, ldn, h);
    acopy(h, g, n);
}
// -------------------------

template <typename Type>
inline void or_convolution(Type * restrict f, Type * restrict g, ulong ldn)
// Compute the OR-convolution h[] of f[] and g[]:
//  h[k] = sum(i | j == k,  f[i]*g[j])
// f[] and g[] must not overlap.
// Result written to g[].
{
    arith_transform_plus(f, ldn);
    arith_transform_plus(g, ldn);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)  g[k] *= f[k];
    arith_transform_minus(g, ldn);
}
// -------------------------

template <typename Type>
inline void or_auto_convolution(Type *f, ulong ldn)
// Compute the self- OR-convolution h[] of f[]:
//  h[k] = sum(i | j == k,  f[i]*f[j])
// Result written to f[].
{
    arith_transform_plus(f, ldn);
    const ulong n = (1UL<<ldn);
    for (ulong k=0; k<n; ++k)  f[k] *= f[k];
    arith_transform_minus(f, ldn);
}
// -------------------------



#endif  // !defined HAVE_OR_CONVOLUTION_H__
