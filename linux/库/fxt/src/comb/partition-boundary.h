#if !defined  HAVE_PARTITION_BOUNDARY_H__
#define       HAVE_PARTITION_BOUNDARY_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

static inline ulong partition_asc_perimeter(const ulong *x, ulong m)
// Return the perimeter of a partition, that is,
// the sum of all elements with at least one non-neighbor.
{
    if ( m==0 )  return 0;

    ulong p = x[0];
    if ( m != 1 )  p += x[m-1];

    for (ulong j=1; j<m-1; ++j)
    {
        bool q1 = ( (x[j] - x[j-1]) > 1 );
        bool q2 = ( (x[j+1] - x[j]) > 1 );
        if ( q1 || q2 )  p += x[j];
    }
    return p;
}
// -------------------------


static inline ulong partition_asc_boundary_size(const ulong *x, ulong m)
// Return the size of the boundary of a partition, that is,
// the number of all elements with at least one non-neighbor.
{
    if ( m==0 )  return 0;

    ulong p = 1;
    if ( m != 1 )  p += 1;

    for (ulong j=1; j<m-1; ++j)
    {
        bool q1 = ( (x[j] - x[j-1]) > 1 );
        bool q2 = ( (x[j+1] - x[j]) > 1 );
        if ( q1 || q2 )  p += 1;
    }

    return p;
}
// -------------------------


#endif // !defined HAVE_PARTITION_BOUNDARY_H__
