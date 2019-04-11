#if !defined  HAVE_SLOWCNVLHALF_H__
#define       HAVE_SLOWCNVLHALF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "fxtalloca.h"

#include "aux1/copy.h"


template <typename Type>
void slow_half_convolution(const Type *f, const Type *g, Type *h, ulong n, int h01)
// Half cyclic convolution.
// Part determined by h01 which must be 0 or 1.
// n := array length
{
    if ( 0==h01 )  // compute h0:
    {
        for (ulong tau=0;  tau<n;  ++tau)
        {
            Type s0 = 0;
            for (ulong k=0, k2=tau;  k<=tau;  ++k, --k2)  s0 += (f[k]*g[k2]);
            h[tau] = s0;
        }
    }
    else  // compute h1 (wrapped part):
    {
        for (ulong tau=0;  tau<n;  ++tau)
        {
            Type s1 = 0;
            for (ulong k2=n-1, k=tau+1;  k<n;  ++k, --k2)  s1 += (f[k]*g[k2]);
            h[tau] = s1;
        }
    }
}
// -------------------------


template <typename Type>
void slow_half_auto_convolution(const Type *f, Type *g, ulong n, int h01)
// Half cyclic self-convolution.
// Part determined by h01 which must be 0 or 1.
// n := array length
// (cyclic) convolution:  g[] :=  f[] (*) g[]
// n := array length
{
    slow_half_convolution(f, f, g, n, h01);
}
// -------------------------


template <typename Type>
void slow_half_convolution(const Type *f, Type *g, ulong n, int h01)
// Half cyclic convolution.
// Part determined by h01 which must be 0 or 1.
// n := array length
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_half_convolution(f, g, h, n, h01);
    acopy(h, g, n);
}
// -------------------------


template <typename Type>
void slow_half_auto_convolution(Type *f, ulong n, int h01)
// Half cyclic self-convolution.
// Part determined by h01 which must be 0 or 1.
// n := array length
{
    ALLOCA(Type, h, n);  // slow algorithm ==> rather small table
    slow_half_convolution(f, f, h, n, h01);
    acopy(h, f, n);
}
// -------------------------


#endif  // !defined HAVE_SLOWCNVLHALF_H__
