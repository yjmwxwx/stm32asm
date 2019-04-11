#if !defined  HAVE_IS_PARTITION_ASC_H__
#define       HAVE_IS_PARTITION_ASC_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


inline bool is_partition_asc(const ulong *a, ulong m, ulong n)
// Return whether a[0, 1, ..., m-1] is a valid partition of n
// represented as a weakly ascending list of parts.
{
    if ( n==0 )  return true;

    if ( a[0] == 0 )  return false;

    for (ulong j=1; j<m; ++j)  // parts ascending?
        if ( a[j-1] > a[j] )
            return false;

    ulong s = 0;  // sum of parts OK?
    for (ulong j=0; j<m; ++j)  s += a[j];
    if ( s != n )  return false;

    return true;
}
// -------------------------

#endif // !defined HAVE_IS_PARTITION_ASC_H__
