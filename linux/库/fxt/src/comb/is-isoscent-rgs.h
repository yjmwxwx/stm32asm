#if !defined  HAVE_IS_ISOSCENT_RGS_H__
#define       HAVE_IS_ISOSCENT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline bool is_isoscent_rgs(const ulong *a, ulong n)
// Return whether a[] is a valid isoscent sequence.
// A isoscent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0,
//   d(k)>=0, and d(k) <= 1 + eq([d(1), d(2), ..., d(k-1)]) and eq(.)
//   counts the number of isoscents of its argument.
{
    if ( n==0 )  return true;

    // the first element must be zero:
    if  ( a[0] != 0 )  return false;

    ulong na = 0;  // number of isoscents so far
    for (ulong j=1; j<n; ++j)
    {
        if ( a[j] > na + 1 )  // at most na+1
            return false;

        na += (a[j] == a[j-1]);
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_ISOSCENT_RGS_H__
