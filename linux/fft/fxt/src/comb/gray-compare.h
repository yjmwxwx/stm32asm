#if !defined  HAVE_GRAY_COMPARE_H__
#define       HAVE_GRAY_COMPARE_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline int gray_compare(const Type *a, ulong na, const Type *b, ulong nb)
// Compare a[] and b[] with respect to Gray code order.
// Return +1 if a[] >> b[], -1 if a[] << b[], 0 if a[]==b[].
{
    const ulong m = (na < nb ? na : nb);  // min(na, nb)

    bool d = false;
    for (ulong j=0; j<m; ++j)
    {
        ulong aj = a[j],  bj = b[j];
        if ( aj != bj )
        {
            int q;
            if ( aj > bj )  q = +1;
            else            q = -1;

            if ( d )  q = -q;
            return q;
        }

        if ( aj & 1UL )  d = !d;
    }

    if ( na == nb )  return 0;
    int q;
    if ( na > nb )  q = +1;
    else            q = -1;

    if ( d )  q = -q;

    return q;
}
// -------------------------



#endif  // !defined HAVE_GRAY_COMPARE_H__
