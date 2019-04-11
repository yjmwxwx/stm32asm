#if !defined  HAVE_IS_SHIFTED_YOUNG_TAB_RGS_H__
#define       HAVE_IS_SHIFTED_YOUNG_TAB_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

inline bool is_delayed_young_tab_rgs(const ulong *A, ulong n, ulong h, ulong s=1)
// Return whether the first occurence of a digit d is
// preceded by at least s+1 occurences of d-1.
// Always true for s==0.
{
    // fixme: inefficient
//    const ulong h = height();
    for (ulong d=0; d<h; ++d)
    {
        ulong ct0 = 0, ct1 = 0;
        for (ulong k=0; k<n; ++k)
        {
            ct0 += (A[k]==d);
            ct1 += (A[k]==d+1);
            if ( ct1 != 0 )
                if ( (ct1 - ct0) < s )  return false;
        }
    }
    return true;
}
// -------------------------


inline bool is_falling_young_tab_rgs(const ulong *P, ulong h, ulong s=1)
// Return whether falling multiplicities with difference at least s.
// Same as: allowing only partitions into distinct parts (with diff>=s).
// Always true for s==0.
{
//    const ulong md = height() - 1;
    const ulong md = h - 1;
    for (ulong j=md; j>0; --j)
        if ( P[j-1] - P[j] < s )
            return false;

    return true;
}
// -------------------------


inline bool is_shifted_young_tab_rgs(const ulong *A, const ulong *P,
                                     ulong n, ulong h, ulong s=1)
// Return whether still valid if row k is shifted to the right
//  by s positions with respect to row k-1.
// Always true for s==0.
{
    if ( ! is_falling_young_tab_rgs(P, h, s) )  return false;
    if ( ! is_delayed_young_tab_rgs(A, n, h, s) )  return false;
    return true;
}
// -------------------------

#endif // !defined HAVE_IS_SHIFTED_YOUNG_TAB_RGS_H__
