#if !defined  HAVE_PARTITION_HOOK_PROD_H__
#define       HAVE_PARTITION_HOOK_PROD_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "comb/partition-conj.h"
#include "fxttypes.h"


template <typename Type>
inline Type partition_desc_hook_prod(const ulong *a, ulong m, ulong *b)
// Return product of all hook lengths in the partition a[].
// The partition must be a weakly descending list of length m.
// b[] is used as scratch space for the conjugate partition.
{
    if ( m==0 )  return 1;

    partition_desc_conj(a, m, b);

    Type r = 1;  // return value
    for (ulong j=0; j<m; ++j)  // parts a[j] in a[]
    {
        const ulong aj = a[j];
        for (ulong k=0; k<aj; ++k)
        {
            const ulong th = aj - k;
            const ulong i = k;
            const ulong tv = b[i] - j;
            const ulong f =  tv + th - 1;
            r *= f;
        }
    }

    return r;
}
// -------------------------


template <typename Type>
inline Type partition_asc_hook_prod(const ulong *a, ulong m, ulong *b)
// Return product of all hook lengths in the partition a[].
// The partition must be a weakly ascending list of length m.
// b[] is used as scratch space for the conjugate partition.
{
    if ( m==0 )  return 1;

    ulong mc = partition_asc_conj(a, m, b);

    Type r = 1;  // return value
    for (ulong j=0; j<m; ++j)  // parts a[j] in a[]
    {
        const ulong aj = a[j];
        for (ulong k=0; k<aj; ++k)
        {
            const ulong th = aj - k;
            const ulong i = (mc-1) - k;
            const ulong tv = b[i] - (m - 1 - j);
            const ulong f =  tv + th - 1;
            r *= f;
        }
    }

    return  r;
}
// -------------------------


#endif  // !defined HAVE_PARTITION_HOOK_PROD_H__
