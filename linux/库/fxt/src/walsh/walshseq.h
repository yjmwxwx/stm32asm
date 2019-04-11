#if !defined  HAVE_WALSHSEQ_H__
#define       HAVE_WALSHSEQ_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "perm/reverse.h"
#include "perm/revbinpermute.h"
#include "walsh/walshgray.h"


template <typename Type>
void walsh_seq1(Type *f, ulong ldn)
// Sequency-ordered Walsh transform.
// Radix-2 decimation in frequency (DIF) algorithm
//.
// The basis (sequency at end of lines, '*':=1, ' ':=-1):
//  0: [* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *] ( 0)
//  1: [* * * * * * * * * * * * * * * *                                ] ( 1)
//  2: [                * * * * * * * * * * * * * * * *                ] ( 2)
//  3: [* * * * * * * *                 * * * * * * * *                ] ( 3)
//  4: [        * * * * * * * *                 * * * * * * * *        ] ( 4)
//  5: [        * * * * * * * *         * * * *                 * * * *] ( 5)
//  6: [        * * * *         * * * * * * * *         * * * *        ] ( 6)
//  7: [* * * *         * * * *         * * * *         * * * *        ] ( 7)
//  8: [    * * * *         * * * *         * * * *         * * * *    ] ( 8)
//  9: [    * * * *         * * * *     * *         * * * *         * *] ( 9)
// 10: [* *         * *     * * * *         * * * *     * *         * *] (10)
// 11: [    * * * *     * *         * *     * * * *     * *         * *] (11)
// 12: [    * *     * * * *     * *         * *     * * * *     * *    ] (12)
// 13: [    * *     * * * *     * *     * *     * *         * *     * *] (13)
// 14: [    * *     * *     * *     * * * *     * *     * *     * *    ] (14)
// 15: [* *     * *     * *     * *     * *     * *     * *     * *    ] (15)
// 16: [  * *     * *     * *     * *     * *     * *     * *     * *  ] (16)
// 17: [  * *     * *     * *     * *   *     * *     * *     * *     *] (17)
// 18: [*     * *     *   * *     * *     * *     * *   *     * *     *] (18)
// 19: [  * *     * *   *     * *     *   * *     * *   *     * *     *] (19)
// 20: [*     *   * *     * *   *     * *     *   * *     * *   *     *] (20)
// 21: [*     *   * *     * *   *     *   * *   *     * *     *   * *  ] (21)
// 22: [*     *   * *   *     *   * *     * *   *     *   * *   *     *] (22)
// 23: [  * *   *     *   * *   *     *   * *   *     *   * *   *     *] (23)
// 24: [  *   * *   *     *   * *   *     *   * *   *     *   * *   *  ] (24)
// 25: [  *   * *   *     *   * *   *   *   *     *   * *   *     *   *] (25)
// 26: [*   *     *   *   *   * *   *     *   * *   *   *   *     *   *] (26)
// 27: [  *   * *   *   *   *     *   *   *   * *   *   *   *     *   *] (27)
// 28: [  *   *   *   * *   *   *   *     *   *   *   * *   *   *   *  ] (28)
// 29: [  *   *   *   * *   *   *   *   *   *   *   *     *   *   *   *] (29)
// 30: [  *   *   *   *   *   *   *   * *   *   *   *   *   *   *   *  ] (30)
// 31: [*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  ] (31)
{
    const ulong n = (1UL<<ldn);

    for (ulong ldm=ldn; ldm>=1; --ldm)  // DIF
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong t1 = r;
            ulong t2 = t1+mh;
            Type *f1 = f+t1, *f2 = f+t2;
            reverse(f2, mh);
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                Type u = f[t1];
                Type v = f[t2];
                f[t1] = u + v;
                f[t2] = u - v;
            }
            reverse(f1, mh);
        }
    }
    revbin_permute(f, n);
}
// -------------------------

template <typename Type>
void inverse_walsh_seq1(Type *f, ulong ldn)
// Inverse of walsh_seq1().
// radix-2 decimation in time (DIT) algorithm.
{
    const ulong n = (1UL<<ldn);

    revbin_permute(f, n);
    for (ulong ldm=1; ldm<=ldn; ++ldm)  // DIT
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        for (ulong r=0; r<n; r+=m)
        {
            ulong t1 = r;
            ulong t2 = t1+mh;
            Type *f1 = f+t1, *f2 = f+t2;
            reverse(f2, mh);
            for (ulong j=0;  j<mh;  ++j, ++t1, ++t2)
            {
                Type u = f[t1];
                Type v = f[t2];
                f[t1] = u + v;
                f[t2] = u - v;
            }
            reverse(f1, mh);
        }
    }
}
// -------------------------


template <typename Type>
void walsh_seq2(Type *f, ulong ldn)
// Sequency-ordered Walsh transform.
//.
// The basis (sequency at end of lines, '*':=1, ' ':=-1):
//  0: [* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *] ( 0)
//  1: [* * * * * * * * * * * * * * * *                                ] ( 1)
//  2: [* * * * * * * *                                 * * * * * * * *] ( 2)
//  3: [                * * * * * * * *                 * * * * * * * *] ( 3)
//  4: [* * * *                 * * * * * * * *                 * * * *] ( 4)
//  5: [* * * *                 * * * *         * * * * * * * *        ] ( 5)
//  6: [        * * * *         * * * * * * * *         * * * *        ] ( 6)
//  7: [* * * *         * * * *         * * * *         * * * *        ] ( 7)
//  8: [* *         * * * *         * * * *         * * * *         * *] ( 8)
//  9: [* *         * * * *         * *     * * * *         * * * *    ] ( 9)
// 10: [* *         * *     * * * *         * * * *     * *         * *] (10)
// 11: [    * * * *     * *         * *     * * * *     * *         * *] (11)
// 12: [    * *     * * * *     * *         * *     * * * *     * *    ] (12)
// 13: [    * *     * * * *     * *     * *     * *         * *     * *] (13)
// 14: [* *     * *     * *     * *         * *     * *     * *     * *] (14)
// 15: [    * *     * *     * *     * *     * *     * *     * *     * *] (15)
// 16: [*     * *     * *     * *     * *     * *     * *     * *     *] (16)
// 17: [*     * *     * *     * *     *   * *     * *     * *     * *  ] (17)
// 18: [*     * *     *   * *     * *     * *     * *   *     * *     *] (18)
// 19: [  * *     * *   *     * *     *   * *     * *   *     * *     *] (19)
// 20: [*     *   * *     * *   *     * *     *   * *     * *   *     *] (20)
// 21: [*     *   * *     * *   *     *   * *   *     * *     *   * *  ] (21)
// 22: [  * *   *     *   * *   *     * *     *   * *   *     *   * *  ] (22)
// 23: [*     *   * *   *     *   * *   *     *   * *   *     *   * *  ] (23)
// 24: [  *   * *   *     *   * *   *     *   * *   *     *   * *   *  ] (24)
// 25: [  *   * *   *     *   * *   *   *   *     *   * *   *     *   *] (25)
// 26: [  *   * *   *   *   *     *   * *   *     *   *   *   * *   *  ] (26)
// 27: [*   *     *   *   *   * *   *   *   *     *   *   *   * *   *  ] (27)
// 28: [*   *   *   *     *   *   *   * *   *   *   *     *   *   *   *] (28)
// 29: [*   *   *   *     *   *   *   *   *   *   *   * *   *   *   *  ] (29)
// 30: [  *   *   *   *   *   *   *   * *   *   *   *   *   *   *   *  ] (30)
// 31: [*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  ] (31)
{
    walsh_gray(f, ldn);
    revbin_permute(f, 1UL<<ldn);
}
// -------------------------

template <typename Type>
void inverse_walsh_seq2(Type *f, ulong ldn)
// Inverse walsh_seq2().
{
    revbin_permute(f, 1UL<<ldn);
    inverse_walsh_gray(f, ldn);
//  =^=
//   for (ulong k=0; k<n; ++k)  if ( grs_negative_q(k) )  f[k] = -f[k];
//   walsh_wal(f,ldn);
}
// -------------------------

#endif  // !defined HAVE_WALSHSEQ_H__
