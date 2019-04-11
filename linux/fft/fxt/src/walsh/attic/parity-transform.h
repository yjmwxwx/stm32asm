#if !defined  HAVE_PARITY_TRANSFORM_H__
#define       HAVE_PARITY_TRANSFORM_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "walsh/bitcount-weight.h"

#include "fxttypes.h"
#include "restrict.h"


template <typename Type>
void parity_transform(Type *f, ulong ldn, Type w)
// Parity Transform.
// Radix-2 decimation In Frequency (DIF) algorithm.
{
    bit_count_weight(f, ldn, w);

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
//                f[t1] = u + w * v;
//                f[t2] = u;
                f[t1] = u + v;
                f[t2] = u;
            }
        }
    }
}
// -------------------------

template <typename Type>
void inverse_parity_transform(Type *f, ulong ldn, Type w)
// Inverse parity Transform.
// Radix-2 decimation In Frequency (DIF) algorithm.
{
//    const Type wi = 1/w;

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
//                f[t1] = v;
//                f[t2] = (u - v) * wi;
                f[t1] = v;
                f[t2] = u - v;
            }
        }
    }

    const Type wi = 1/w;
    bit_count_weight(f, ldn, wi);
}
// -------------------------


template <typename Type>
inline void parity_transform(Type *f, ulong ldn, int is, Type w)
{
    if ( is>0 )  parity_transform(f, ldn, w);
    else         inverse_parity_transform(f, ldn, w);
}
// -------------------------


//template <typename Type>
//void rev_parity_transform(Type *f, ulong ldn)
//// Reversed parity transform.
//// Radix-2 decimation In Frequency (DIF) algorithm.
//// { n=1UL<<ldn; reverse(f,n); parity_transform(f,ldn); reverse(f,n); }
//{
//    const ulong n = (1UL<<ldn);
//    for (ulong ldm=ldn; ldm>=1; --ldm)
//    {
//        const ulong m = (1UL<<ldm);
//        const ulong mh = (m>>1);
//        for (ulong r=0; r<n; r+=m)
//        {
//            ulong t1 = r;
//            ulong t2 = r+mh;
//            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
//            {
//                Type u = f[t1];
//                Type v = f[t2];
//                f[t1] = u + v;
//                f[t2] = v;
//            }
//        }
//    }
//}
//// -------------------------
//
//template <typename Type>
//void inverse_rev_parity_transform(Type *f, ulong ldn)
//// Inverse reversed parity transform.
//// Radix-2 decimation In Frequency (DIF) algorithm.
//// Inverse of rev_parity_transform().
//// Same as:
//// { n=1UL<<ldn; reverse(f,n); inverse_parity_transform(f,ldn); reverse(f,n); }
//{
//    const ulong n = (1UL<<ldn);
//    for (ulong ldm=ldn; ldm>=1; --ldm)
//    {
//        const ulong m = (1UL<<ldm);
//        const ulong mh = (m>>1);
//        for (ulong r=0; r<n; r+=m)
//        {
//            ulong t1 = r;
//            ulong t2 = r+mh;
//            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
//            {
//                Type u = f[t1];
//                Type v = f[t2];
//                f[t1] = u - v;
//                f[t2] = v;
//            }
//        }
//    }
//}
//// -------------------------
//
//template <typename Type>
//inline void rev_parity_transform(Type *f, ulong ldn, int is)
//{
//    if ( is>0 )  rev_parity_transform(f, ldn);
//    else         inverse_rev_parity_transform(f, ldn);
//}
//// -------------------------


#endif  // !defined HAVE_PARITY_TRANSFORM_H__
