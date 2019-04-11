// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "dctdst/dctdst.h"
#include "fht/fht-default.h"
#include "aux0/sumdiff.h"

#include "perm/ziprev.h"
#include "fxttypes.h"  // ulong

#include <cmath>  // sqrt()

#define  SAVE_F0   1  // 0 or 1 (to keep the value f[0], else set to zero)
void
dst(double *f, ulong ldn, double *tmp/*=0*/)
// basis: sin(k*i*M_PI/n)
// almost self-inverse:  dst(dst(f[])) = 0.5*f[]
// ldn := base-2 logarithm of the array length
// tmp := (optional) pointer to scratch space
// the basis:
//  0: [*                                                              ] ( 1)
//  1: [  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *] ( 2)
//  2: [  * * * * * * * * * * * * * * *                                ] ( 3)
//  3: [  * * * * * * * * * *                       * * * * * * * * * *] ( 4)
//  4: [  * * * * * * *                   * * * * * * *                ] ( 5)
//  5: [  * * * * * *             * * * * * * *             * * * * * *] ( 6)
//  6: [  * * * * *           * * * * *             * * * * *          ] ( 7)
//  7: [  * * * *           * * * *           * * * *           * * * *] ( 8)
//  8: [  * * *           * * *           * * *           * * *        ] ( 9)
//  9: [  * * *         * * *         * * *         * * *         * * *] (10)
// 10: [  * * *       * * *       * * *         * * *       * * *      ] (11)
// 11: [  * *       * * *       * * *       * * *       * * *       * *] (12)
// 12: [  * *       * *       * * *       * *       * *       * * *    ] (13)
// 13: [  * *     * * *     * * *     * * *     * * *     * * *     * *] (14)
// 14: [  * *     * *       * *     * *       * *     * * *     * *    ] (15)
// 15: [  * *     * *     * *     * *       * *     * *     * *     * *] (16)
// 16: [  *       *       *       *       *       *       *       *    ] (17)
// 17: [  *     * *     * *     * *     *     * *     * *     * *     *] (18)
// 18: [  *     * *     *     * *     *     * *     * *   * *     * *  ] (19)
// 19: [  *     * *   * *     *     * *   * *     *     * *   * *     *] (20)
// 20: [  *     *     *     * *   * *     *     *     *     * *   * *  ] (21)
// 21: [  *     *     *     *     *     *     *     *     *     *     *] (22)
// 22: [  *   * *   * *   * *   * *   *     *     *     *     *     *  ] (23)
// 23: [  *   * *   *     *     *   * *   * *   *     *     *   * *   *] (24)
// 24: [  *   *     *     *   *     *     *   *     *     *   *     *  ] (25)
// 25: [  *   *     *   *     *   * *   *   * *   *     *   *     *   *] (26)
// 26: [  *   *   * *   *   * *   *   *     *   *     *   *     *   *  ] (27)
// 27: [  *   *   *     *   *   * *   *   *   * *   *   *     *   *   *] (28)
// 28: [  *   *   *   *     *   *   *     *   *   *   *     *   *   *  ] (29)
// 29: [  *   *   *   *   *     *   *   *   *   *     *   *   *   *   *] (30)
// 30: [  *   *   *   *   *   *   *   *     *   *   *   *   *   *   *  ] (31)
// 31: [  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *] (32)
//
{
    ulong n = (1UL<<ldn);

#if  ( SAVE_F0!=0 )
    double f0 = f[0] * sqrt(0.5*(double)n);
#endif

    f[0] = 0.0;
    f[n/2] *= 2.0;
    double phi = M_PI/(double)n;
    for (ulong i=1, j=n-1;  i<j;  ++i, --j)
    {
        double s, d;
        sumdiff(f[i], f[j], s, d);
        s *= sin(phi*(double)i);
        d *= 0.5;
        sumdiff(s, d, f[i], f[j]);
    }

    fht(f, ldn);
    for (ulong i=1, j=n-1;  i<j;  i++, j--)  sumdiff05(f[i], f[j]);

    f[0] *= 0.5;
    const ulong nh = (n>>1);
    f[nh] = 0.0;
    double s = 0;
    for (ulong i=0; i<nh; ++i)
    {
        s += f[i];
        f[i] = s;
    }

    if ( tmp )
    {
        zip_rev(f, tmp, n);
        for (ulong k=n-1; k!=0; --k)  f[k] = tmp[k-1];
        // =^= acopy(tmp, f, n);  shift_right(f, n, 1);
    }
    else
    {
        zip_rev(f, n);
        for (ulong k=n-1; k!=0; --k)  f[k] = f[k-1];
        // =^= shift_right(f, n, 1);
    }

#if  ( SAVE_F0!=0 )
    f[0] = f0;
#else
    f[0] = 0;
#endif
}
// -------------------------


void
dst_basis(double *f, ulong n, ulong k)
{
//    double vv = 1.0;
    const double ph = M_PI*(double)(k)/(double)(n);
    for (ulong i=0; i<n; ++i)
    {
        // f[i] = vv * cos( M_PI * k * i / n );
        f[i] = cos( (double)i * ph );
    }
}
// -------------------------

