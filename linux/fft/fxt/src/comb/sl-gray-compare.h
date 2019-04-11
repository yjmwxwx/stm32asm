#if !defined  HAVE_SL_GRAY_COMPARE_H__
#define       HAVE_SL_GRAY_COMPARE_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

template <typename Type>
inline int sl_gray_compare(const Type *a, ulong na,
                           const Type *b, ulong nb,
                           const ulong *m1)
// Compare a[] and b[] with respect to SL-Gray order.
// Return +1 if a[] >> b[], -1 if a[] << b[], 0 if a[]==b[].
// m1[] must be the array of nines.
{
    ulong ea = 0;  // last index such that a[ea-1] != 0
    for (ulong j=0; j<na; ++j)  if ( a[j] != 0 )  ea = j + 1;

    ulong eb = 0;  // last index such that b[eb-1] != 0
    for (ulong j=0; j<nb; ++j)  if ( b[j] != 0 )  eb = j + 1;

    bool d = false;
    const ulong m = (ea < eb ? ea : eb);  // min(ea, eb)
    for (ulong j=0; j<m; ++j)
    {
        ulong aj = a[j],  bj = b[j];

        if ( aj != bj )
        {
            int q;
            if ( aj < bj )
            {
                if ( j == ea-1 )  q = -1;
                else              q = +1;
            }
            else  // bj < aj
            {
                if ( j == eb-1 )  q = +1;
                else              q = -1;
            }

            if ( d )  q = -q;

            return q;
        }

//        d ^= ( 0 != (j & 1UL) );

        if ( j != m - 1 ) // only if not at end
        {
            const ulong t = aj;
            if ( 0 != (m1[j] & 1) )  // even radix
            {
                if ( 0 == (t & 1UL) )  d = !d;
            }
            else
            {
                if ( 0 != (t & 1UL) )  d = !d;
            }
        }
    }

    if ( ea == eb )  return 0;

    int q = ( ea > eb ? +1 : -1 );
    if ( d )  q = -q;

    return q;
}
// -------------------------

#endif  // !defined HAVE_SL_GRAY_COMPARE_H__
