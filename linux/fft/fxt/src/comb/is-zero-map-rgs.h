#if !defined  HAVE_IS_ZERO_MAP_RGS_H__
#define       HAVE_IS_ZERO_MAP_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

inline bool is_zero_map_rgs(const ulong *a, ulong n)
// Return whether a[] is a zero-map RGS:
//   each digit a[k] is either zero or the (one-based) index
//   of a zero in the prefix.
// RGS is for set paritions, cf. A000110.
{
    for (ulong j=0; j<n; ++j)
    {
        ulong d = a[j];
        if ( d > j )  return false;
        --d;   // make zero-based
        if ( a[d] != 0 )  return false;  // must point to a zero
    }

    return true;
}
// -------------------------

inline bool is_zero_map_rgs(const ulong *a, ulong n, ulong s, ulong *t)
// Return whether a[] is a zero-map RGS with at most s repeats:
//   each digit a[k] is either zero or the (one-based) index
//   of a zero in the prefix and there are at most s digits pointing
//   to the same zero in the prefix.
{
    for (ulong j=0; j<n; ++j)  t[j] = 0;

    for (ulong j=0; j<n; ++j)
    {
        ulong d = a[j];
        if ( d > j )  return false;
        if ( d != 0 )
        {
            --d;   // make zero-based
            if ( a[d] != 0 )  return false;
            if ( t[d] == s )  return false;
            ++t[d];
        }
    }

    return true;
}
// -------------------------

#endif  // !defined HAVE_IS_ZERO_MAP_RGS_H__
