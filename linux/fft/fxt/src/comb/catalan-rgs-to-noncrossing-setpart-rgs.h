#if !defined  HAVE_CATALAN_RGS_TO_NONCROSSING_SETPART_RGS_H__
#define       HAVE_CATALAN_RGS_TO_NONCROSSING_SETPART_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtalloca.h"

#include "fxttypes.h"


inline void catalan_rgs_to_noncrossing_setpart_rgs(const ulong *A, ulong n,
                                                   ulong *P)
// Compute the RGS for a noncrossing set partition from the
//   Catalan RGS given in A[].  Result is written to P[].
// Complexity is O(n).
{
    if ( n==0 )  return;

    P[0] = 0;

    ALLOCA(ulong, B, n);  // P[x] is the current offset for element x
    // P[j] == z + B[z] where z = A[j] (during processing)
    for (ulong k=0; k<n; ++k)  B[k] = 0;

    ulong d = 0;  // total of down steps so far
    ulong y = 0;  // element before current

    for (ulong j=1; j<n; ++j)
    {
        const ulong z = A[j];  // current element

        // Update from below if needed:
        if ( z != 0 )
        {
            const ulong bz = B[z];
            const ulong b1 = B[z-1];
            if ( b1 > bz )  B[z] = b1;
        }

        P[j] = z + B[z];

        if ( y > z )  // down step
        {
            d += (y-z);

//            Now increase offset for all i > z:
//            for (ulong i=z+1; i<n; ++i)  B[i] = d;
            // better:
            B[z+1] = d;  // later updated upwards
        }

        y = z;
    }
}
// -------------------------


#endif // !defined HAVE_CATALAN_RGS_TO_NONCROSSING_SETPART_RGS_H__
