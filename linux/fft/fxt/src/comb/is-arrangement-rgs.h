#if !defined  HAVE_IS_ARRANGEMENT_RGS_H__
#define       HAVE_IS_ARRANGEMENT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline bool is_arrangement_rgs(const ulong *a, ulong n)
// Return whether a[] is a valid arrangement RGS:
// every digit is at most 1 + the number of nonzero digits in the prefix.
{
    ulong w = 1;
    for (ulong j=0; j<n; ++j)
    {
        if ( a[j] > w )  return false;
        w += ( a[j] != 0 );
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_ARRANGEMENT_RGS_H__
