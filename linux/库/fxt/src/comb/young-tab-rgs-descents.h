#if !defined  HAVE_YOUNG_TAB_RGS_DESCENTS_H__
#define       HAVE_YOUNG_TAB_RGS_DESCENTS_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

//#include "jjassert.h"

inline ulong young_tab_rgs_descent_set(const ulong *a, ulong n, ulong *d)
// Return the number of descents of the tableau.
// Write the set of corresponding positions into d[].
// A descent in a standard Young tableau is a entry i such that i+1
// lies strictly below and weakly left of i.
{
    if ( n <= 1 )  return 0;

    ulong k = 0;
    for (ulong i=0; i<n-1; ++i)
    {
        if ( a[i+1] > a[i] )  // descent
        {
            d[k] = i + 1;
            k += 1;
        }
    }

    return k;
}
// -------------------------


inline ulong young_tab_rgs_major_index(const ulong *a, ulong n)
// Return the major index of the tableau.
// A descent in a standard Young tableau is a entry i such that i+1
// lies strictly below (and weakly left of) i.  The major index is the
// sum of all such i.
// Return value s in range 0 <= s <= n*(n-1)/2
{
    if ( n <= 1 )  return 0;

    ulong mi = 0;
    for (ulong i=0; i<n-1; ++i)
        if ( a[i+1] > a[i] )   mi += i + 1;

    return mi;
}
// -------------------------


inline ulong young_tab_rgs_descent_number(const ulong *a, ulong n)
// Return the number of descents of the tableau.
// A descent in a standard Young tableau is a entry i such that i+1
// lies strictly below and weakly left of i.
{
    if ( n <= 1 )  return 0;

    ulong dn = 0;
    for (ulong i=0; i<n-1; ++i)
        if ( a[i+1] > a[i] )   dn += 1;

    return dn;
}
// -------------------------



#endif // !defined HAVE_YOUNG_TAB_RGS_DESCENTS_H__
