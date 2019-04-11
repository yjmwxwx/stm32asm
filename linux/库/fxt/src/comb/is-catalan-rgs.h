#if !defined  HAVE_IS_CATALAN_RGS_H__
#define       HAVE_IS_CATALAN_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline bool is_catalan_rgs(const ulong *rgs, ulong n)
// Return whether rgs[] is a valid Catalan RGS, that is,
// a string a[0,1,...,n-1] where a[0]=0 and a[k] <= a[k-1] + 1.
{
    if ( n==0 )  return true;  // nothing to check

    if ( rgs[0] != 0 )  return false;

    for (ulong j=1; j<n; ++j)
        if ( rgs[j] > rgs[j-1] + 1 )  return false;

    return true;
}
// -------------------------


inline bool is_rev_catalan_rgs(const ulong *rgs, ulong n)
// Return whether reversed rgs[] is a valid Catalan RGS.
{
    if ( n==0 )  return true;  // nothing to check

    if ( rgs[n-1] != 0 )  return false;

    for (ulong j=n-1; j!=0; --j)
        if ( rgs[j-1] > rgs[j] + 1 )  return false;

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_CATALAN_RGS_H__
