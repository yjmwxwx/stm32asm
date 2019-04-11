#if !defined  HAVE_IS_CATALAN_STEP_RGS_H__
#define       HAVE_IS_CATALAN_STEP_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline bool is_catalan_step_rgs(const ulong *rgs, ulong n)
// Return whether rgs[] is a valid Catalan (step-)RGS.
// The RGS are a[] such that a[k] >= a[k-1] (weakly ascending) and a[k]<=k.
// The RGS describe lattice paths from (0,0) to (n,n) with steps
// (+1,0) and (+1,+1) that do not go below the diagonal.
// Same as: rising factorial numbers where the digits are sorted.
{
    if ( n==0 )  return true;  // nothing to check

    for (ulong j=0; j<n; ++j)  // digits in range?
        if ( rgs[j] > j )  return false;

    for (ulong j=1; j<n; ++j)  // sorted?
        if ( rgs[j] < rgs[j-1] )  return false;

    return true;
}
// -------------------------



#endif  // !defined HAVE_IS_CATALAN_STEP_RGS_H__
