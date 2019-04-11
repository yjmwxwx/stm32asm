#if !defined  HAVE_SUBSET_LEX_COMPARE_H__
#define       HAVE_SUBSET_LEX_COMPARE_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline int subset_lex_compare(const Type *a, ulong na,
                              const Type *b, ulong nb,
                              bool rlq=false)
// Compare a[] and b[] with repect to subset-lex order.
// Return +1 if a[] >> b[], -1 if a[] << b[], 0 if a[]==b[].
{
    ulong ea = 0;  // last index such that a[ea-1] != 0
    for (ulong j=0; j<na; ++j)  if ( a[j] != 0 )  ea = j + 1;

    ulong eb = 0;  // last index such that b[eb-1] != 0
    for (ulong j=0; j<nb; ++j)  if ( b[j] != 0 )  eb = j + 1;


    const ulong m = (ea < eb ? ea : eb);  // min(ea, eb)
    for (ulong j=0; j<m; ++j)
    {
        ulong aj = a[j],  bj = b[j];
        if ( aj != bj )
        {
            bool q = ( aj < bj );
            // rlq = false for mixed radix numbers
            // rlq = true for compositions and partitions, where
            // the underlying run-length encoding is subset-lex
            q ^= rlq;
            if ( q )
            {
                if ( j == ea-1 )  return -1;
                else              return +1;
            }
            else  // bj < aj
            {
                if ( j == eb-1 )  return +1;
                else              return -1;
            }
        }
    }

    if ( ea == eb )  return 0;
    return ( ea > eb ? +1 : -1 );
}
// -------------------------


#endif  // !defined HAVE_SUBSET_LEX_COMPARE_H__
