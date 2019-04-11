#if !defined  HAVE_WALSHPAL_H__
#define       HAVE_WALSHPAL_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "perm/revbinpermute.h"
#include "walsh/walshwak.h"  // walsh_wak()


template <typename Type>
inline void walsh_pal(Type *f, ulong ldn)
// Walsh transform wrt. to Walsh-Paley basis (pal-functions).
// Self-inverse.
//.
// The basis (sequency at end of lines, '*':=1, ' ':=-1):
//  0: [* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *] ( 0)
//  1: [* * * * * * * * * * * * * * * *                                ] ( 1)
//  2: [* * * * * * * *                 * * * * * * * *                ] ( 3)
//  3: [* * * * * * * *                                 * * * * * * * *] ( 2)
//  4: [* * * *         * * * *         * * * *         * * * *        ] ( 7)
//  5: [* * * *         * * * *                 * * * *         * * * *] ( 6)
//  6: [* * * *                 * * * * * * * *                 * * * *] ( 4)
//  7: [* * * *                 * * * *         * * * * * * * *        ] ( 5)
//  8: [* *     * *     * *     * *     * *     * *     * *     * *    ] (15)
//  9: [* *     * *     * *     * *         * *     * *     * *     * *] (14)
// 10: [* *     * *         * *     * * * *     * *         * *     * *] (12)
// 11: [* *     * *         * *     * *     * *     * * * *     * *    ] (13)
// 12: [* *         * * * *         * * * *         * * * *         * *] ( 8)
// 13: [* *         * * * *         * *     * * * *         * * * *    ] ( 9)
// 14: [* *         * *     * * * *     * *         * *     * * * *    ] (11)
// 15: [* *         * *     * * * *         * * * *     * *         * *] (10)
// 16: [*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  ] (31)
// 17: [*   *   *   *   *   *   *   *     *   *   *   *   *   *   *   *] (30)
// 18: [*   *   *   *     *   *   *   * *   *   *   *     *   *   *   *] (28)
// 19: [*   *   *   *     *   *   *   *   *   *   *   * *   *   *   *  ] (29)
// 20: [*   *     *   * *   *     *   * *   *     *   * *   *     *   *] (24)
// 21: [*   *     *   * *   *     *   *   *   * *   *     *   * *   *  ] (25)
// 22: [*   *     *   *   *   * *   *   *   *     *   *   *   * *   *  ] (27)
// 23: [*   *     *   *   *   * *   *     *   * *   *   *   *     *   *] (26)
// 24: [*     * *     * *     * *     * *     * *     * *     * *     *] (16)
// 25: [*     * *     * *     * *     *   * *     * *     * *     * *  ] (17)
// 26: [*     * *     *   * *     * *   *     * *     *   * *     * *  ] (19)
// 27: [*     * *     *   * *     * *     * *     * *   *     * *     *] (18)
// 28: [*     *   * *   *     *   * *   *     *   * *   *     *   * *  ] (23)
// 29: [*     *   * *   *     *   * *     * *   *     *   * *   *     *] (22)
// 30: [*     *   * *     * *   *     * *     *   * *     * *   *     *] (20)
// 31: [*     *   * *     * *   *     *   * *   *     * *     *   * *  ] (21)
{
    const ulong n = 1UL<<ldn;
    revbin_permute(f, n);
    walsh_wak(f, ldn);
// =^=
//    walsh_wak(f, ldn);
//    revbin_permute(f, n);
}
// -------------------------



#endif  // !defined HAVE_WALSHPAL_H__
