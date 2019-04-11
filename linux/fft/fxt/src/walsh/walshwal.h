#if !defined  HAVE_WALSHWAL_H__
#define       HAVE_WALSHWAL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "perm/revbinpermute.h"
//#include "perm/graypermute.h"
//#include "walsh/walshwak.h"


template <typename Type>
void walsh_wal_dif2_core(Type *f, ulong ldn)
// Core routine for sequency-ordered Walsh transform.
// Radix-2 decimation in frequency (DIF) algorithm.
//.
// walsh_wal(f, ldn)
//   =^=
// revbin_permute(f, n);  walsh_wal_dif2_core(f, ldn);
// The routine gray_permute() is absorbed.
{
    const ulong n = (1UL<<ldn);
    for (ulong ldm=ldn; ldm>=2; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        const ulong m4 = (mh>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong j;
            for (j=0; j<m4; ++j)
            {
                ulong t1 = r+j;
                ulong t2 = t1+mh;
                double u = f[t1];
                double v = f[t2];
                f[t1] = u + v;
                f[t2] = u - v;
            }

            for (  ; j<mh; ++j)
            {
                ulong t1 = r+j;
                ulong t2 = t1+mh;
                double u = f[t1];
                double v = f[t2];
                f[t1] = u + v;
                f[t2] = v - u;  // reversed
            }
        }
    }

    if ( ldn )
    {
        // ulong ldm=1;
        const ulong m = 2;  // (1UL<<ldm);
        const ulong mh = 1;  // (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong j = 0;
//            for (ulong j=0; j<mh; ++j)
            {
                ulong t1 = r+j;
                ulong t2 = t1+mh;
                double u = f[t1];
                double v = f[t2];
                f[t1] = u + v;
                f[t2] = u - v;
            }
        }
    }
}
// -------------------------


template <typename Type>
void walsh_wal_dit2_core(Type *f, ulong ldn)
// core routine for sequency-ordered Walsh transform.
// Radix-2 decimation in time (DIT) algorithm.
//.
// walsh_wal(f, ldn)
//   =^=
//   walsh_wal_dit2_core(f, ldn);  revbin_permute(f, n);
// The routine gray_permute() is absorbed
{
    const ulong n = (1UL<<ldn);

    if ( ldn )
    {
        // ulong ldm=1;
        const ulong m = 2;  // (1UL<<ldm);
        const ulong mh = 1;  // (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong j = 0;
//            for (ulong j=0; j<mh; ++j)
            {
                ulong t1 = r+j;
                ulong t2 = t1+mh;
                double u = f[t1];
                double v = f[t2];
                f[t1] = u + v;
                f[t2] = u - v;
            }
        }
    }

    for (ulong ldm=2; ldm<=ldn; ++ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        const ulong m4 = (mh>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong j;
            for (j=0; j<m4; ++j)
            {
                ulong t1 = r+j;
                ulong t2 = t1+mh;
                double u = f[t1];
                double v = f[t2];
                f[t1] = u + v;
                f[t2] = u - v;
            }

            for (  ; j<mh; ++j)
            {
                ulong t1 = r+j;
                ulong t2 = t1+mh;
                double u = f[t1];
                double v = f[t2];
                f[t1] = u - v;
                f[t2] = v + u;
            }
        }
    }
}
// -------------------------



template <typename Type>
inline void walsh_wal(Type *f, ulong ldn)
// Sequency-ordered Walsh transform.
// Transform wrt. to Walsh-Kaczmarz basis (wal-functions)
// The wal functions are sequency-ordered.
//.
// The basis: (sequency at end of lines, '*':=1, ' ':=-1)
//  0: [* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *] ( 0)
//  1: [* * * * * * * * * * * * * * * *                                ] ( 1)
//  2: [* * * * * * * *                                 * * * * * * * *] ( 2)
//  3: [* * * * * * * *                 * * * * * * * *                ] ( 3)
//  4: [* * * *                 * * * * * * * *                 * * * *] ( 4)
//  5: [* * * *                 * * * *         * * * * * * * *        ] ( 5)
//  6: [* * * *         * * * *                 * * * *         * * * *] ( 6)
//  7: [* * * *         * * * *         * * * *         * * * *        ] ( 7)
//  8: [* *         * * * *         * * * *         * * * *         * *] ( 8)
//  9: [* *         * * * *         * *     * * * *         * * * *    ] ( 9)
// 10: [* *         * *     * * * *         * * * *     * *         * *] (10)
// 11: [* *         * *     * * * *     * *         * *     * * * *    ] (11)
// 12: [* *     * *         * *     * * * *     * *         * *     * *] (12)
// 13: [* *     * *         * *     * *     * *     * * * *     * *    ] (13)
// 14: [* *     * *     * *     * *         * *     * *     * *     * *] (14)
// 15: [* *     * *     * *     * *     * *     * *     * *     * *    ] (15)
// 16: [*     * *     * *     * *     * *     * *     * *     * *     *] (16)
// 17: [*     * *     * *     * *     *   * *     * *     * *     * *  ] (17)
// 18: [*     * *     *   * *     * *     * *     * *   *     * *     *] (18)
// 19: [*     * *     *   * *     * *   *     * *     *   * *     * *  ] (19)
// 20: [*     *   * *     * *   *     * *     *   * *     * *   *     *] (20)
// 21: [*     *   * *     * *   *     *   * *   *     * *     *   * *  ] (21)
// 22: [*     *   * *   *     *   * *     * *   *     *   * *   *     *] (22)
// 23: [*     *   * *   *     *   * *   *     *   * *   *     *   * *  ] (23)
// 24: [*   *     *   * *   *     *   * *   *     *   * *   *     *   *] (24)
// 25: [*   *     *   * *   *     *   *   *   * *   *     *   * *   *  ] (25)
// 26: [*   *     *   *   *   * *   *     *   * *   *   *   *     *   *] (26)
// 27: [*   *     *   *   *   * *   *   *   *     *   *   *   * *   *  ] (27)
// 28: [*   *   *   *     *   *   *   * *   *   *   *     *   *   *   *] (28)
// 29: [*   *   *   *     *   *   *   *   *   *   *   * *   *   *   *  ] (29)
// 30: [*   *   *   *   *   *   *   *     *   *   *   *   *   *   *   *] (30)
// 31: [*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  ] (31)
{
    revbin_permute(f, (1UL<<ldn));
    walsh_wal_dif2_core(f, ldn);
//  =^=
//    walsh_wal_dit2_core(f, ldn);
//    revbin_permute(f, (1UL<<ldn));
//  =^=
//    gray_permute(f, n);
//    revbin_permute(f, n);
//    walsh_wak(f, ldn);
//  =^=
//    walsh_wak(f, ldn);
//    revbin_permute(f, n);
//    inverse_gray_permute(f, n);
}
// -------------------------



#endif  // !defined HAVE_WALSHWAL_H__
