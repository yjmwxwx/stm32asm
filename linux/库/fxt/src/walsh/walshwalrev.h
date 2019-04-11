#if !defined  HAVE_WALSHWALREV_H__
#define       HAVE_WALSHWALREV_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "perm/revbinpermute.h"
#include "walsh/walshwal.h"
//#include "perm/reverse.h"  // reverse()
//#include "aux0/sumdiff.h"



template <typename Type>
inline void walsh_wal_rev(Type *f, ulong ldn)
// Reversed sequency-ordered walsh transform.
// Self-inverse.
//.
// == void walsh_z1(Type *f, ulong ldn)
// The basis (sequency at end of lines), '*':=1, ' ':=-1:
// 0: [* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *] ( 0)
// 1: [* * * * * * * *                                 * * * * * * * *] ( 2)
// 2: [* * * *                 * * * * * * * *                 * * * *] ( 4)
// 3: [* * * *         * * * *                 * * * *         * * * *] ( 6)
// 4: [* *         * * * *         * * * *         * * * *         * *] ( 8)
// 5: [* *         * *     * * * *         * * * *     * *         * *] (10)
// 6: [* *     * *         * *     * * * *     * *         * *     * *] (12)
// 7: [* *     * *     * *     * *         * *     * *     * *     * *] (14)
// 8: [*     * *     * *     * *     * *     * *     * *     * *     *] (16)
// 9: [*     * *     *   * *     * *     * *     * *   *     * *     *] (18)
//10: [*     *   * *     * *   *     * *     *   * *     * *   *     *] (20)
//11: [*     *   * *   *     *   * *     * *   *     *   * *   *     *] (22)
//12: [*   *     *   * *   *     *   * *   *     *   * *   *     *   *] (24)
//13: [*   *     *   *   *   * *   *     *   * *   *   *   *     *   *] (26)
//14: [*   *   *   *     *   *   *   * *   *   *   *     *   *   *   *] (28)
//15: [*   *   *   *   *   *   *   *     *   *   *   *   *   *   *   *] (30)
//16: [*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  ] (31)
//17: [*   *   *   *     *   *   *   *   *   *   *   * *   *   *   *  ] (29)
//18: [*   *     *   *   *   * *   *   *   *     *   *   *   * *   *  ] (27)
//19: [*   *     *   * *   *     *   *   *   * *   *     *   * *   *  ] (25)
//20: [*     *   * *   *     *   * *   *     *   * *   *     *   * *  ] (23)
//21: [*     *   * *     * *   *     *   * *   *     * *     *   * *  ] (21)
//22: [*     * *     *   * *     * *   *     * *     *   * *     * *  ] (19)
//23: [*     * *     * *     * *     *   * *     * *     * *     * *  ] (17)
//24: [* *     * *     * *     * *     * *     * *     * *     * *    ] (15)
//25: [* *     * *         * *     * *     * *     * * * *     * *    ] (13)
//26: [* *         * *     * * * *     * *         * *     * * * *    ] (11)
//27: [* *         * * * *         * *     * * * *         * * * *    ] ( 9)
//28: [* * * *         * * * *         * * * *         * * * *        ] ( 7)
//29: [* * * *                 * * * *         * * * * * * * *        ] ( 5)
//30: [* * * * * * * *                 * * * * * * * *                ] ( 3)
//31: [* * * * * * * * * * * * * * * *                                ] ( 1)
{
    revbin_permute(f, (1UL<<ldn));
    walsh_wal_dit2_core(f, ldn);
    // =^=
//    walsh_wal_dif2_core(f, ldn);
//    revbin_permute(f, n);
    // =^=
//    zip_rev(f, n);
//    walsh_wal(f, ldn);
    // =^=
//    walsh_wal(f, ldn);
//    unzip_rev(f, n);
    // =^=
//    walsh_wak(f, ldn);
//    inverse_gray_permute(f, n);
//    revbin_permute(f, n);
//    // =^=
//    revbin_permute(f, n);
//    walsh_wal(f, ldn);
//    revbin_permute(f, n);
}
// -------------------------





// UNUSED:
//template <typename Type>
//void walsh_z1_dif2_core(Type *f, ulong ldn)
//// decimation in frequency (DIF) algorithm
//// =^=
////  gray_permute(f, n);  walsh_wak(f,ldn);
//{
//    const ulong n = (1UL<<ldn);
//
//    for (ulong ldm=ldn; ldm>0; --ldm)  // DIF
//    {
//        const ulong m = (1UL<<ldm);
//        const ulong mh = (m>>1);
//        for (ulong r=0; r<n; r+=m)
//        {
//            ulong t1 = r;
//            ulong t2 = r+mh;
//            Type *f2 = f+t2;
//            t2 = r + m - 1;
////            for (ulong j=0; j<mh; ++j,++t1,--t2)
//            for (  ;  t1<t2;  ++t1,--t2)
//            {
//                Type u = f[t1];
//                Type v = f[t2];
//                f[t1] = u + v;
//                f[t2] = u - v;
//            }
//            reverse(f2, mh);
//        }
//    }
//}
//// -------------------------

// UNUSED:
//template <typename Type>
//void walsh_z1_dit2_core(Type *f, ulong ldn)
//// decimation in time (DIT) algorithm
//// =^=
////  walsh_wak(f,ldn);  inverse_gray_permute(f, n);
//{
//    const ulong n = (1UL<<ldn);
//    for (ulong ldm=1; ldm<=ldn; ++ldm)  // DIT
//    {
//        const ulong m = (1UL<<ldm);
//        const ulong mh = (m>>1);
//        for (ulong r=0; r<n; r+=m)
//        {
//            ulong t1 = r;
//            ulong t2 = r+mh;
//            Type *f2 = f+t2;
//            reverse(f2, mh);
//            t2 = r + m - 1;
////            for (ulong j=0; j<mh; ++j,++t1,--t2)
//            for (  ;  t1<t2;  ++t1,--t2)
//            {
//                Type u = f[t1];
//                Type v = f[t2];
//                f[t1] = u + v;
//                f[t2] = u - v;
//            }
//        }
//    }
//}
//// -------------------------

//template <typename Type>
//void walsh_z2(Type *f, ulong ldn)
//// transform wrt. the basis (sequency at end of lines), '*':=1, ' ':=-1:
////    0: [ * * * * * * * * * * * * * * * *                                 ] ( 1)
////    1: [ * * * * * * * *                 * * * * * * * *                 ] ( 3)
////    2: [ * * * *                 * * * *         * * * * * * * *         ] ( 5)
////    3: [ * * * *         * * * *         * * * *         * * * *         ] ( 7)
////    4: [ * *         * * * *         * *     * * * *         * * * *     ] ( 9)
////    5: [ * *         * *     * * * *     * *         * *     * * * *     ] (11)
////    6: [ * *     * *         * *     * *     * *     * * * *     * *     ] (13)
////    7: [ * *     * *     * *     * *     * *     * *     * *     * *     ] (15)
////    8: [ *     * *     * *     * *     *   * *     * *     * *     * *   ] (17)
////    9: [ *     * *     *   * *     * *   *     * *     *   * *     * *   ] (19)
////   10: [ *     *   * *     * *   *     *   * *   *     * *     *   * *   ] (21)
////   11: [ *     *   * *   *     *   * *   *     *   * *   *     *   * *   ] (23)
////   12: [ *   *     *   * *   *     *   *   *   * *   *     *   * *   *   ] (25)
////   13: [ *   *     *   *   *   * *   *   *   *     *   *   *   * *   *   ] (27)
////   14: [ *   *   *   *     *   *   *   *   *   *   *   * *   *   *   *   ] (29)
////   15: [ *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   ] (31)
////   16: [   *   *   *   *   *   *   *   * *   *   *   *   *   *   *   *   ] (30)
////   17: [   *   *   *   * *   *   *   *     *   *   *   * *   *   *   *   ] (28)
////   18: [   *   * *   *   *   *     *   * *   *     *   *   *   * *   *   ] (26)
////   19: [   *   * *   *     *   * *   *     *   * *   *     *   * *   *   ] (24)
////   20: [   * *   *     *   * *   *     * *     *   * *   *     *   * *   ] (22)
////   21: [   * *   *     * *     *   * *     * *   *     * *     *   * *   ] (20)
////   22: [   * *     * *   *     * *     * *     * *     *   * *     * *   ] (18)
////   23: [   * *     * *     * *     * *     * *     * *     * *     * *   ] (16)
////   24: [     * *     * *     * *     * * * *     * *     * *     * *     ] (14)
////   25: [     * *     * * * *     * *         * *     * * * *     * *     ] (12)
////   26: [     * * * *     * *         * * * *         * *     * * * *     ] (10)
////   27: [     * * * *         * * * *         * * * *         * * * *     ] ( 8)
////   28: [         * * * *         * * * * * * * *         * * * *         ] ( 6)
////   29: [         * * * * * * * *                 * * * * * * * *         ] ( 4)
////   30: [                 * * * * * * * * * * * * * * * *                 ] ( 2)
////   31: [                                                                 ] ( 0)
////
//// Self-inverse.
////
//{
//    ulong n = 1UL << ldn;
//
////    for (ulong k=0; k<n; ++k)  sumdiff05(f[k], f[n-1-k]);
////    walsh_z1(f, ldn);
//// =^=
////    walsh_z1(f, ldn);
////    for (ulong k=0; k<n; ++k) sumdiff05(f[n-1-k], f[k]);
//// =^= (up to normalization)
//    reverse(f, n);
//    walsh_z1(f, ldn);
//    reverse(f, n);
//    negate(f, n);
//// =^=
////    negate(f, n/2);
////    walsh_z1(f, ldn);
////    negate(f, n/2);
//}
//// -------------------------
//


#endif  // !defined HAVE_WALSHWALREV_H__

