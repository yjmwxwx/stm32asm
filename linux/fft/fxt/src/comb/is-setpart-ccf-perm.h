#if !defined  HAVE_IS_SETPART_CCF_PERM_H__
#define       HAVE_IS_SETPART_CCF_PERM_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


inline bool is_setpart_ccf_perm(ulong const *f, ulong n)
// Return whether f[], read as canonical cyle form (CCF) of a permutation
// is valid as a set partition of the form
//  (a1, a2, ..., ai), (b1, b2, ..., bj), (c1, c2, ..., ck), ...
// such that ai < bj < ck < ...
// and the last element in each group is the minimal element and
// the other elements in each group appear in increasing order.
{
    ulong mn = 0;  // minimum (indicates cycle end)
    for (ulong j=1; j<n; ++j)
    {
        ulong fj = f[j];
        if ( f[j-1] > f[j] )  // cycle end
        {
            if ( fj < mn )  return false;
            mn = fj;
        }
    }
    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_SETPART_CCF_PERM_H__
