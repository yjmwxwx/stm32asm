#if !defined  HAVE_IS_SMOOTH_H__
#define       HAVE_IS_SMOOTH_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


inline bool is_left_smooth(const ulong *a, ulong n, ulong d=1)
// Return whether a[] has maximal up-step <= d.
{
    for (ulong j=1; j<n; ++j)
        if ( a[j] > a[j-1] + d )  return false;
    return true;
}
// -------------------------

inline bool is_right_smooth(const ulong *a, ulong n, ulong d=1)
// Return whether a[] has maximal down-step <= d.
{
    for (ulong j=1; j<n; ++j)
        if ( a[j-1] > a[j] + d )  return false;
    return true;
}
// -------------------------


inline bool is_smooth(const ulong *a, ulong n, ulong d=1)
// Return whether a[] is smooth, that is, abs(a[k] - a[k-1]) <= d
{
    if ( ! is_left_smooth(a, n, d) )  return false;
    if ( ! is_right_smooth(a, n, d) )  return false;
    return true;
}
// -------------------------


inline bool is_left_2smooth(const ulong *a, ulong n)
// Return whether a[] is left-2smooth, that is,
// the maximal up-step is <= 1,
// and there are no consecutive up-steps.
{
    for (ulong j=1; j<n; ++j)
        if ( a[j] > a[j-1] + 1 )  return false;
    for (ulong j=2; j<n; ++j)
        if ( a[j] > a[j-2] + 2 )  return false;

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_SMOOTH_H__
