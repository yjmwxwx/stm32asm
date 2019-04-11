#if !defined  HAVE_SLOWCNVLA_H__
#define       HAVE_SLOWCNVLA_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "fxtalloca.h"

#include "aux1/copy.h"


template <typename Type>
void slow_convolution0(const Type *f, const Type *g, Type *h, ulong n)
// (linear) convolution:  h[] :=  f[] (*0) g[]
// n := array length
// Input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
{
    const ulong nh = n/2;
    for (ulong tau=0; tau<nh; ++tau)
    {
        Type s = 0;
        for (ulong k=0, k2=tau;  (long)k2>=0;  ++k, --k2)  s += (f[k]*g[k2]);
        h[tau] = s;
    }

    for (ulong tau=nh; tau<n; ++tau)
    {
        Type s = 0;
        for (ulong k=tau-nh, k2=nh;  (long)k2>=0;  ++k, --k2)  s += (f[k]*g[k2]);
        h[tau] = s;
    }
}
// -------------------------


template <typename Type>
void slow_auto_convolution0(const Type *f, Type *g, ulong n)
// (linear) self-convolution:  g[] :=  f[] (*0) g[]
// n := array length
// Input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// n  must be >=2
{
    slow_convolution0(f, f, g, n);
}
// -------------------------


template <typename Type>
void slow_convolution0(const Type *f, Type *g, ulong n)
// (linear) convolution:  g[] :=  f[] (*0) g[]
// n := array length
//
// input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// n  must be >=2
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_convolution0(f, g, h, n);
    acopy(h, g, n);
}
// -------------------------


template <typename Type>
void slow_auto_convolution0(Type *f, ulong n)
// (linear) self-convolution:  g[] :=  f[] (*0) g[]
// n := array length
// Input data must be zero padded:
//   f[n/2] .. f[n-1] == 0
// n  must be >=2
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_convolution0(f, f, h, n);
    acopy(h, f, n);
}
// -------------------------


#endif  // !defined HAVE_SLOWCNVLA_H__
