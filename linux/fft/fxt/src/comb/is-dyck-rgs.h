#if !defined  HAVE_IS_DYCK_RGS_H__
#define       HAVE_IS_DYCK_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline bool is_dyck_rgs(const ulong *rgs, ulong n, ulong i=1)
// Return whether rgs[] is a valid (i+1)-ary Dyck word, that is,
// a word a[0,1,...,n-1] where a[0]=0 and a[j] <= a[j-1] + i.
{
    if ( n==0 )  return true;  // nothing to check

    if ( rgs[0] != 0 )  return false;

    for (ulong j=1; j<n; ++j)
        if ( rgs[j] > rgs[j-1] + i )  return false;

    return true;
}
// -------------------------



#endif  // !defined HAVE_IS_DYCK_RGS_H__
