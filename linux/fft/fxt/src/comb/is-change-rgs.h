#if !defined  HAVE_IS_CHANGE_RGS_H__
#define       HAVE_IS_CHANGE_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline bool is_change_rgs(const ulong *a, ulong n)
// Return whether a[] is a valid change sequence.
// A change sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0,
//   d(k)>=0, and d(k) <= 1 + chg([d(1), d(2), ..., d(k-1)]) and chg(.)
//   counts the number of changes of its argument.
// See OEIS sequence A000522.
{
    if ( n==0 )  return true;

    // the first element must be zero:
    if  ( a[0] != 0 )  return false;

    ulong nc = 0;  // number of changes so far
    for (ulong j=1; j<n; ++j)
    {
        if ( a[j] > nc + 1 )  // at most nc+1
            return false;

        nc += (a[j] != a[j-1]);
    }

    return true;
}
// -------------------------


#endif // !defined HAVE_IS_CHANGE_RGS_H__
