#if !defined  HAVE_ARITH_3_PROGRESSION_H__
#define       HAVE_ARITH_3_PROGRESSION_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


inline ulong test_arith_3_progression(const ulong *a, ulong n)
// Return last index of first 3-term arithmetic progression found
// in a[], return 0 if there is none.
{
    // test indices [t1] < [t2] < [t3]
    for (ulong t1=0; t1<n; ++t1)
    {
        for (ulong t2=t1+1; t2<n; ++t2)
        {
            const ulong d1 = a[t1] - a[t2];
            for (ulong t3=t2+1; t3<n; ++t3)
            {
                const ulong d2 = a[t2] - a[t3];
                if ( d1 == d2 )  return t3;
            }
        }
    }
    return 0;
}
// -------------------------


inline bool has_arith_3_progression(const ulong *a, ulong n)
// Return whether there is a 3-term arithmetic progression in a[].
{
    return ( 0 != test_arith_3_progression(a, n) );
}
// -------------------------


inline ulong test_arith_3_progression_eqd(const ulong *a, ulong n)
// Return last index of first equidistant 3-term arithmetic
// progression found in a[], return 0 if there is none.
// Here only progressions with equally separated indices
// [t], [t+s], [t+2*s] are considered
{
    for (ulong s=1; s<n; ++s)  // skip
    {
        // test indices [t], [t+s], [t+2*s]
        for (ulong t=0; t+2*s < n; ++t)
        {
            const ulong d1 = a[t] - a[t+s];
            const ulong d2 = a[t+s] - a[t+2*s];
            if ( d1 == d2 )  return t + 2*s;
        }
    }
    return 0;
}
// -------------------------

inline bool has_arith_3_progression_eqd(const ulong *a, ulong n)
// Return whether there is an equidistant 3-term arithmetic
// progression in a[].
{
    return ( 0 != test_arith_3_progression_eqd(a, n) );
}
// -------------------------


inline ulong test_arith_3_progression_consec(const ulong *a, ulong n)
// Return last index of first 3-term arithmetic progression in three
// consecutive places found in a[], return 0 if there is none.
{
    for (ulong j=2; j<n; ++j)
    {
        const ulong d1 = a[j-2] - a[j-1];
        const ulong d2 = a[j-1] - a[j];
        if ( d1 == d2 )  return  j;
    }
    return 0;
}
// -------------------------

inline bool has_arith_3_progression_consec(const ulong *a, ulong n)
// Return whether there is 3-term arithmetic progression in three
// consecutive places in a[].
{
    return ( 0 != test_arith_3_progression_consec(a, n) );
}
// -------------------------



#endif // !defined HAVE_ARITH_3_PROGRESSION_H__
