#if !defined  HAVE_IS_CATALAN_PATH_H__
#define       HAVE_IS_CATALAN_PATH_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

inline bool is_catalan_path(const ulong *x, ulong n2)
// Return whether x[0..n] is a valid Catalan path, i.e.,
// x[0] = 0,  abs(x[j]-x[j-1]) == 1,  and x[n-1] <= 1.
{
    if ( n2==0 )  return true;  // nothing to check

    if ( x[0] != 0 )  return false;
    if ( x[n2-1] > 1 )  return false;

    for (ulong j=1; j<n2; ++j)
    {
        ulong d = x[j] - x[j-1];
        if ( (long)d < 0 )  d = -d;
        if ( d > 1 )   return false;
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_CATALAN_PATH_H__
