#if !defined  HAVE_REEDMULLER_H__
#define       HAVE_REEDMULLER_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bittransforms.h"


template <typename Type>
void word_reed_muller_dif2(Type *f, ulong ldn)
// Reed-Muller Transform.
// Radix-2 decimation in frequency (DIF) algorithm.
// Self-inverse.
// Type must have the XOR operator.
//.
// Transform wrt. to the basis: (sequency at end of lines, '*':=1, ' ':=-1)
//  0: [* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *] ( 0)
//  1: [  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *] (32)
//  2: [    * *     * *     * *     * *     * *     * *     * *     * *] (16)
//  3: [      *       *       *       *       *       *       *       *] (16)
//  4: [        * * * *         * * * *         * * * *         * * * *] ( 8)
//  5: [          *   *           *   *           *   *           *   *] (16)
//  6: [            * *             * *             * *             * *] ( 8)
//  7: [              *               *               *               *] ( 8)
//  8: [                * * * * * * * *                 * * * * * * * *] ( 4)
//  9: [                  *   *   *   *                   *   *   *   *] (16)
// 10: [                    * *     * *                     * *     * *] ( 8)
// 11: [                      *       *                       *       *] ( 8)
// 12: [                        * * * *                         * * * *] ( 4)
// 13: [                          *   *                           *   *] ( 8)
// 14: [                            * *                             * *] ( 4)
// 15: [                              *                               *] ( 4)
// 16: [                                * * * * * * * * * * * * * * * *] ( 2)
// 17: [                                  *   *   *   *   *   *   *   *] (16)
// 18: [                                    * *     * *     * *     * *] ( 8)
// 19: [                                      *       *       *       *] ( 8)
// 20: [                                        * * * *         * * * *] ( 4)
// 21: [                                          *   *           *   *] ( 8)
// 22: [                                            * *             * *] ( 4)
// 23: [                                              *               *] ( 4)
// 24: [                                                * * * * * * * *] ( 2)
// 25: [                                                  *   *   *   *] ( 8)
// 26: [                                                    * *     * *] ( 4)
// 27: [                                                      *       *] ( 4)
// 28: [                                                        * * * *] ( 2)
// 29: [                                                          *   *] ( 4)
// 30: [                                                            * *] ( 2)
// 31: [                                                              *] ( 2)
//
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
                f[t2] = u ^ v;
            }
        }
    }
}
// -------------------------


template <typename Type>
void word_reed_muller_dit2(Type *f, ulong ldn)
// Reed-Muller Transform.
// Radix-2 decimation in time (DIT) algorithm.
// Self-inverse.
// Type must have the XOR operator.
{
    ulong n = (1UL<<ldn);
    for (ulong ldm=1; ldm<=ldn; ++ldm)
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
                f[t2] = u ^ v;
            }
        }
    }
}
// -------------------------


template <typename Type>
inline void word_reed_muller(Type *f, ulong ldn)
{
    word_reed_muller_dif2(f, ldn);
}
// -------------------------


template <typename Type>
inline void reed_muller_basis(Type *f, ulong n, ulong k)
// Basis function of the Reed-Muller transform
{
    for (ulong i=0; i<n; ++i)
    {
//        ulong x = (n-1-i) & (k);
//        f[i] = ( 0==x ? +1 : 0 );
        f[i] = ( (i & k)==k ? +1 : 0 );  // is k a subset of i (as bitsets)?
    }
}
// -------------------------


template <typename Type>
inline void bit_reed_muller(Type *f, ulong ldn)
{
    word_reed_muller_dif2(f, ldn);
    ulong n = 1UL << ldn;
    for (ulong k=0; k<n; ++k)  f[k] = yellow_code(f[k]);
}
// -------------------------



#endif  // !defined HAVE_REEDMULLER_H__
