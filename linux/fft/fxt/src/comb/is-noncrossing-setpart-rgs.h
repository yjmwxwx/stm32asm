#if !defined  HAVE_IS_NONCROSSING_SETPART_RGS_H__
#define       HAVE_IS_NONCROSSING_SETPART_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtalloca.h"

#include "fxttypes.h"


inline ulong test_noncrossing_setpart_rgs(const ulong *R, ulong n)
// Return first index where the RGS for set partitions in R[]
//   has a crossing of the set partition.
// Return 0 if R[] corresponds to a non-crossing partition.
{
    if ( n <= 3 )  return 0;  // smallest crossing partition has size 4

#if 1
    // Complexity is O(n^2)

    ALLOCA(bool, F, n);  // whether value forbidden
    for (ulong j=0; j<n; ++j)  F[j] = false;

    ulong j = 1;
    do
    {
        const ulong v = R[j];
        if ( F[v] )  return j;  // j>=4

        const ulong v1 = R[j-1];

        // with down step, forbid values v+1 ... v1
        for (ulong t = v+1; t<=v1; ++t)  F[t] = true;
        // Max of total number of writes to F[] for all RGS, n>=0:
        // 0, 0, 1, 2, 3, 5, 7, 9, 12, 15, 18, 22, 26, 30, 35, ...
        // Apparent g.f.: x^2 /((1-x)^2 * (1-x^3)), cf. A001840
        // a(n) = floor( n*(n+1)/6 )
    }
    while ( ++j < n );
    return 0;

#else  // slightly slower:
    // Complexity is O(n^2).

    ALLOCA(ulong, B, n);  // begin of sets
    ALLOCA(ulong, E, n);  // end of sets
    for (ulong j=0; j<n; ++j)  B[j] = E[j] = 0;

    for (ulong j=0; j<n; ++j)
    {
        ulong v = R[j];
        if ( B[v] == 0 )  B[v] = j + 1;  // new set begins
        else
        {
            E[v] = j + 1;

            const ulong bv = B[v];
            // Search for (forbidden) pattern "XYXY" for all X < Y.
            // No prior set (X) must have ended after
            //   set containing v (Y) has started:
            while ( v-- != 0 )
                if ( E[v] > bv )  return j;
        }
    }
    return 0;
#endif
}
// -------------------------

inline bool is_noncrossing_setpart_rgs(const ulong *R, ulong n)
// Return whether the RGS for set partitions in R[]
//   corresponds to a non-crossing partition.
{ return ( 0 == test_noncrossing_setpart_rgs(R, n) ); }


#endif // !defined HAVE_IS_NONCROSSING_SETPART_RGS_H__
