#if !defined  HAVE_LEX_COMPARE_H__
#define       HAVE_LEX_COMPARE_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline int lex_compare(const Type *a, ulong na, const Type *b, ulong nb)
// Compare a[] and b[] lexicographically.
// Return +1 if a[] >> b[], -1 if a[] << b[], 0 if a[]==b[].
{
    const ulong m = (na < nb ? na : nb);  // min(na, nb)

    for (ulong j=0; j<m; ++j)
    {
        ulong aj = a[j],  bj = b[j];
        if ( aj != bj )
        {
            if ( aj > bj )  return +1;
            return -1;
        }
    }

    if ( na == nb )  return 0;
    if ( na > nb )  return +1;
    return -1;
}
// -------------------------



#endif  // !defined HAVE_LEX_COMPARE_H__
