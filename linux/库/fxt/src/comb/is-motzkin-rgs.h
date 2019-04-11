#if !defined  HAVE_IS_MOTZKIN_RGS_H__
#define       HAVE_IS_MOTZKIN_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


inline bool is_motzkin_rgs(const ulong *a, ulong n, ulong i=1)
// Return whether a[] is a valid Motzkin RGS:
// words a[0,1,...,n-1] where a[0] = 0, a_[k] <= a[k-1] + 1,
//  and there are no more than i=1 consecutive up-steps.
// Works for othe values of i as well.
{
    if ( n==0 )  return true;

    if  ( a[0] != 0 )  return false;

    ulong t = a[0];  // previous digit
    ulong u = 0;
    for (ulong k=1; k<n; ++k)
    {
        const ulong d = a[k];
        if ( d > t + 1 )  return false;
        if ( d > t )  u += 1;  else  u = 0;
        if ( u > i )  return false;
        t = d;
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_MOTZKIN_RGS_H__
