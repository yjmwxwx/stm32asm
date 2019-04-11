#if !defined  HAVE_ARITHTRANSFORM_H__
#define       HAVE_ARITHTRANSFORM_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
void arith_transform_plus(Type *f, ulong ldn)
// Arithmetic transform (positive sign).
// Radix-2 decimation In Frequency (DIF) algorithm.
// Inverse of arith_transform_minus().
{
    const ulong n = (1UL<<ldn);
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong t1 = r;
            ulong t2 = r+mh;
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                Type u = f[t1];
                Type v = f[t2];
                f[t1] = u;
                f[t2] = u + v;
            }
        }
    }
}
// -------------------------

template <typename Type>
void arith_transform_minus(Type *f, ulong ldn)
// Arithmetic transform (negative sign).
// Radix-2 decimation In Frequency (DIF) algorithm.
// Inverse of arith_transform_plus().
{
    const ulong n = (1UL<<ldn);
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong t1 = r;
            ulong t2 = r+mh;
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                Type u = f[t1];
                Type v = f[t2];
                f[t1] = u;
                f[t2] = v - u;
            }
        }
    }
}
// -------------------------


template <typename Type>
void rev_arith_transform_plus(Type *f, ulong ldn)
// Reversed arithmetic transform (positive sign).
// Radix-2 decimation In Frequency (DIF) algorithm.
// Inverse of rev_arith_transform_minus().
// Same as:
// { n=1UL<<ldn; reverse(f,n); arith_transform_plus(f,ldn); reverse(f,n); }
{
    const ulong n = (1UL<<ldn);
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong t1 = r;
            ulong t2 = r+mh;
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                Type u = f[t1];
                Type v = f[t2];
                f[t1] = u + v;
                f[t2] = v;
            }
        }
    }
}
// -------------------------

template <typename Type>
void rev_arith_transform_minus(Type *f, ulong ldn)
// Reversed arithmetic transform (negative sign).
// Radix-2 decimation In Frequency (DIF) algorithm.
// Inverse of rev_arith_transform_plus().
// Same as:
// { n=1UL<<ldn; reverse(f,n); arith_transform_minus(f,ldn); reverse(f,n); }
{
    const ulong n = (1UL<<ldn);
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong t1 = r;
            ulong t2 = r+mh;
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                Type u = f[t1];
                Type v = f[t2];
                f[t1] = u - v;
                f[t2] = v;
            }
        }
    }
}
// -------------------------


#endif  // !defined HAVE_ARITHTRANSFORM_H__
