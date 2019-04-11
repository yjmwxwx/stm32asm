#if !defined  HAVE_COMPOSITION_NZ_CONJ_H__
#define       HAVE_COMPOSITION_NZ_CONJ_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


inline ulong composition_nz_conj(const ulong *x, ulong m, ulong *c)
// Write conjugate of composition x[] (m non-zero parts) to c[].
// Return number of parts written to c[].
// Conjugation is swapping separators and non-separators
//   in the "stars and bars" representation.
// For example, [5,3,1,2,2] and [1,1,1,1,2,1,3,2,1] are conjugates:
//
//       5       3   1  2   2
//  |* * * * *|* * *|*|* *|* *|
//  |*|*|*|*|* *|*|* * *|* *|*|
//   1 1 1 1  2  1   3    2  1
//
{
    if ( m==0 )  return 0;

    c[0] = 0;

    ulong r=0, w=0;  // read position, write position
    while ( r < m )  // for all parts x[r]
    {
        ++c[w];  // one unit goes to last write position
        ulong pr = x[r];
        ++r;
        while ( --pr )  // pr - 1 new write position(s)
        {
            ++w;
            c[w] = 1;
        }
    }

    return  w + 1;
}
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_CONJ_H__
