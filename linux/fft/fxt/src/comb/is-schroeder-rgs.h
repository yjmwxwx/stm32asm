#if !defined  HAVE_IS_SCHROEDER_RGS_H__
#define       HAVE_IS_SCHROEDER_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


inline bool is_schroeder_rgs(const ulong *a, ulong n, ulong m0)
// Return whether a[] is a valid Schroeder RGS:
// a Schroeder RGS is a word a[0,1,2,...,n-1] where
// a[k] <= k + 1 (rising factorial numbers),
// a[0] <= m0, and  a[k] + 1 >= max(j=1..k-1, a[j])
// m0 == 0  ==> little Schroeder numbers, A001003
// m0 == 1  ==> large Schroeder numbers, A006318
{
    if ( n==0 )  return true;

    if  ( a[0] > m0 )  return false;

    ulong m = a[0];  // max in prefix
    for (ulong k=1; k<n; ++k)
    {
        if ( a[k] > k + 1 )  return false;
        if ( m > a[k] + 1 )  return false;
        if ( m < a[k] )  m = a[k];
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_SCHROEDER_RGS_H__
