#if !defined  HAVE_IS_YOUNG_TAB_RGS_H__
#define       HAVE_IS_YOUNG_TAB_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//#include "jjassert.h"


inline bool is_young_tab_rgs(const ulong *x, ulong n, ulong *st, bool cst=false)
// Return whether x[0..n-1] is a valid restricted growth strings (RGS)
// for a standard Young tableau: the k-th occurrence of a digit d must
// precede the k-th occurrence of d-1.
// If cst is set then st[] should contain the partition corresponding
// to the digit statistics.
// Must have st a pointer to (at least) n elements, regardless of cst.
{
    if ( n==0 )  return true;  // nothing to check

    for (ulong j=0; j<n; ++j)  // digit x[j] <= j ?
    {
//        jjassert_not( x[j] > j );
        if ( x[j] > j )  return false;
    }

    if ( cst )
    {
        // does st[] reflect the digit stats?
        for (ulong j=0; j<n; ++j)  st[x[j]] -= 1;  // subtract actual stats
        for (ulong j=0; j<n; ++j)
        {
//            jjassert_not( st[j] != 0 );
            if ( st[j] != 0 )  return false;  // st[j] was not the actual value
        }
    }

    for (ulong j=0; j<n; ++j)  st[j] = 0;  // init stats

//    jjassert_not( x[0] != 0 );
    if ( x[0] != 0 )  return false;  // first must be 0

    // k-th occurrence of a digit d must precede the k-th occurrence of d-1:
    for (ulong j=0; j<n; ++j)
    {
        ulong d = x[j];
        if ( d!=0 )
        {
//            jjassert_not( st[d-1] <= st[d] );
            if ( st[d-1] <= st[d] )   return false;
        }
        st[d] += 1;
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_YOUNG_TAB_RGS_H__
