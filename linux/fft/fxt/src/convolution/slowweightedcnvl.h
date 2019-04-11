#if !defined  HAVE_SLOWWEIGHTEDCNVL_H__
#define       HAVE_SLOWWEIGHTEDCNVL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "fxtalloca.h"

#include "aux1/copy.h"


template <typename Type>
void slow_weighted_convolution(const Type *f, const Type *g, Type *h, ulong n, Type w)
// Weighted (cyclic) convolution:  h[] :=  f[] (*)_w g[]
// n := array length
{
    for (ulong tau=0;  tau<n;  ++tau)
    {
        ulong k = 0;
        Type s0 = 0;
        for (ulong k2=tau;  k<=tau;  ++k, --k2)  s0 += (f[k]*g[k2]);
        Type s1 = 0;
        for (ulong k2=n-1;  k<n;     ++k, --k2)  s1 += (f[k]*g[k2]);  // wrapped around
        h[tau] = s0 + s1*w;
    }
}
// -------------------------

template <typename Type>
void slow_weighted_auto_convolution(const Type *f, Type *g, ulong n)
// Weighted (cyclic) convolution:  g[] :=  f[] (*)_w g[]
// n := array length
{
    slow_weighted_convolution(f, f, g, n);
}
// -------------------------

template <typename Type>
void slow_weighted_convolution(const Type *f, Type *g, ulong n)
// Weighted (cyclic) convolution:  g[] :=  f[] (*)_w g[]
// n := array length
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_weighted_convolution(f, g, h, n);
    acopy(h, g, n);
}
// -------------------------

template <typename Type>
void slow_weighted_auto_convolution(Type *f, ulong n)
// Weighted (cyclic) self-convolution:  f[] :=  f[] (*)_w f[]
// n := array length
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_weighted_convolution(f, f, h, n);
    acopy(h, f, n);
}
// -------------------------


#endif  // !defined HAVE_SLOWWEIGHTEDCNVL_H__
