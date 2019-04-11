#if !defined  HAVE_SLOWCNVL_H__
#define       HAVE_SLOWCNVL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "fxtalloca.h"

#include "aux1/copy.h"


template <typename Type>
void slow_convolution(const Type *f, const Type *g, Type *h, ulong n)
// (cyclic) convolution:  h[] :=  f[] (*) g[]
// n := array length
{
#if 0
    for (ulong tau=0;  tau<n;  ++tau)
    {
        Type s = 0;
        for (ulong k=0; k<n; ++k)
        {
            ulong k2 = tau - k;
            if ( (long)k2 < 0 )  k2 += n;  // modulo n
            s += (f[k]*g[k2]);
        }
        h[tau] = s;
    }
#else  // 0
    for (ulong tau=0;  tau<n;  ++tau)
    {
        Type s = 0;
        ulong k = 0;
        for (ulong k2=tau;  k<=tau;  ++k, --k2)  s += (f[k]*g[k2]);
        for (ulong k2=n-1;  k<n;     ++k, --k2)  s += (f[k]*g[k2]);  // wrapped around
        h[tau] = s;
    }
#endif  // 0
}
// -------------------------


template <typename Type>
void slow_auto_convolution(const Type *f, Type *g, ulong n)
// (cyclic) convolution:  g[] :=  f[] (*) g[]
// n := array length
{
    slow_convolution(f, f, g, n);
}
// -------------------------


template <typename Type>
void slow_convolution(const Type *f, Type *g, ulong n)
// (cyclic) convolution:  g[] :=  f[] (*) g[]
// n := array length
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_convolution(f, g, h, n);
    acopy(h, g, n);
}
// -------------------------


template <typename Type>
void slow_auto_convolution(Type *f, ulong n)
// (cyclic) self-convolution:  f[] :=  f[] (*) f[]
// n := array length
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_convolution(f, f, h, n);
    acopy(h, f, n);
}
// -------------------------


#endif  // !defined HAVE_SLOWCNVL_H__
