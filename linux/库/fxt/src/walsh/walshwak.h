#if !defined  HAVE_WALSHWAK_H__
#define       HAVE_WALSHWAK_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "walsh/walshwak2.h"
#include "walsh/walshwak4.h"
#include "walsh/walshwak8.h"
#include "walsh/walshwakloc2.h"
#include "fxttypes.h"




template <typename Type>
inline void walsh_wak(Type *f, ulong ldn)
// Transform wrt. to Walsh-Kronecker basis (wak-functions).
// Self-inverse.
//.
// The basis: (sequency at end of lines, '*':=+1, ' ':=-1)
//  0: [* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *] ( 0)
//  1: [*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  ] (31)
//  2: [* *     * *     * *     * *     * *     * *     * *     * *    ] (15)
//  3: [*     * *     * *     * *     * *     * *     * *     * *     *] (16)
//  4: [* * * *         * * * *         * * * *         * * * *        ] ( 7)
//  5: [*   *     *   * *   *     *   * *   *     *   * *   *     *   *] (24)
//  6: [* *         * * * *         * * * *         * * * *         * *] ( 8)
//  7: [*     *   * *   *     *   * *   *     *   * *   *     *   * *  ] (23)
//  8: [* * * * * * * *                 * * * * * * * *                ] ( 3)
//  9: [*   *   *   *     *   *   *   * *   *   *   *     *   *   *   *] (28)
// 10: [* *     * *         * *     * * * *     * *         * *     * *] (12)
// 11: [*     * *     *   * *     * *   *     * *     *   * *     * *  ] (19)
// 12: [* * * *                 * * * * * * * *                 * * * *] ( 4)
// 13: [*   *     *   *   *   * *   *   *   *     *   *   *   * *   *  ] (27)
// 14: [* *         * *     * * * *     * *         * *     * * * *    ] (11)
// 15: [*     *   * *     * *   *     * *     *   * *     * *   *     *] (20)
// 16: [* * * * * * * * * * * * * * * *                                ] ( 1)
// 17: [*   *   *   *   *   *   *   *     *   *   *   *   *   *   *   *] (30)
// 18: [* *     * *     * *     * *         * *     * *     * *     * *] (14)
// 19: [*     * *     * *     * *     *   * *     * *     * *     * *  ] (17)
// 20: [* * * *         * * * *                 * * * *         * * * *] ( 6)
// 21: [*   *     *   * *   *     *   *   *   * *   *     *   * *   *  ] (25)
// 22: [* *         * * * *         * *     * * * *         * * * *    ] ( 9)
// 23: [*     *   * *   *     *   * *     * *   *     *   * *   *     *] (22)
// 24: [* * * * * * * *                                 * * * * * * * *] ( 2)
// 25: [*   *   *   *     *   *   *   *   *   *   *   * *   *   *   *  ] (29)
// 26: [* *     * *         * *     * *     * *     * * * *     * *    ] (13)
// 27: [*     * *     *   * *     * *     * *     * *   *     * *     *] (18)
// 28: [* * * *                 * * * *         * * * * * * * *        ] ( 5)
// 29: [*   *     *   *   *   * *   *     *   * *   *   *   *     *   *] (26)
// 30: [* *         * *     * * * *         * * * *     * *         * *] (10)
// 31: [*     *   * *     * *   *     *   * *   *     * *     *   * *  ] (21)
{
    if ( ldn<=13 )  walsh_wak_dif4(f, ldn);
    else            walsh_wak_loc_dif2(f, ldn);
}
// -------------------------



#endif  // !defined HAVE_WALSHWAK_H__
