#if !defined  HAVE_PARTITION_ODD_TO_DIST_H__
#define       HAVE_PARTITION_ODD_TO_DIST_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "sort/sort.h"
#include "perm/reverse.h"

#include "fxttypes.h"


inline ulong partition_asc_odd_to_dist(const ulong *a, ulong ma, ulong *t)
// From the partition a[0,1,..,ma-1] into odd parts compute the
// corresponding partition t[0,1,...,mt-1] into distinct parts, as
// ascending list of parts.  Return mt, the number of parts in t[].
// a[] only needs to have all identical parts consecutive.
{
    if ( ma <= 1 )
    {
        if ( ma != 0 )  t[0] = a[0];
        return ma;
    }

    ulong mt = 0;
    ulong p = a[0];  // last part
    ulong c = 1;  // multiplicity of part
    for (ulong j=1; j<ma; ++j)
    {
        ulong aj = a[j];  // current part;
        if ( p == a[j] )  c += 1;  // same part as last
        else
        {
            do  // write parts according to binary expansion of multiplicity c:
            {
                if ( (c & 1UL) != 0 )  t[mt++] = p;
                p *= 2;  c >>= 1;
            }
            while ( c != 0 );

            p = aj;
            c = 1;
        }
    }

    do  // write parts according to binary expansion of multiplicity c:
    {
        if ( (c & 1UL) != 0 )  t[mt++] = p;
        p *= 2;  c >>= 1;
    }
    while ( c != 0 );

    selection_sort(t, mt);
    return mt;
}
// -------------------------


inline ulong partition_asc_dist_to_odd(const ulong *a, ulong ma, ulong *t)
// From the partition a[0,1,..,ma-1] into distinct parts compute the
// corresponding partition t[0,1,...,mt-1] into odd parts, as weakly
// increasing list of parts.  Return mt, the number of parts in t[].
{
    ulong mt = 0;
    for (ulong j=0; j<ma; ++j)
    {
        ulong aj = a[j];
        if ( (aj & 1UL) == 1 )  t[mt++] = aj;  // odd part
        else
        {
            ulong e = 0;  // 2-valuation of aj
            do  { ++e;  aj>>=1; }  while ( (aj & 1UL) == 0 );
            // make that 2**e parts aj / (2**e):
            e = 1UL << e;
            while ( e != 0 )  { t[mt++] = aj;  --e; }
        }
    }

    selection_sort(t, mt);
    return mt;
}
// -------------------------


inline ulong partition_desc_odd_to_dist(const ulong *a, ulong ma, ulong *t)
// From the partition a[0,1,..,ma-1] into odd parts compute the
// corresponding partition t[0,1,...,mt-1] into distinct parts, as
// descending list of parts.  Return mt, the number of parts in t[].
// a[] only needs to have all identical parts consecutive.
{
    ulong mt = partition_asc_odd_to_dist(a, ma, t);
    reverse(t, mt);
    return mt;
}
// -------------------------


inline ulong partition_desc_dist_to_odd(const ulong *a, ulong ma, ulong *t)
// From the partition a[0,1,..,ma-1] into distinct parts compute the
// corresponding partition t[0,1,...,mt-1] into odd parts, as weakly
// decreasing list of parts.  Return mt, the number of parts in t[].
{
    ulong mt = partition_asc_dist_to_odd(a, ma, t);
    reverse(t, mt);
    return mt;
}
// -------------------------

#endif // !defined HAVE_PARTITION_ODD_TO_DIST_H__
