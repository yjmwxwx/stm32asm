#if !defined  HAVE_IS_SETPART_RGS_H__
#define       HAVE_IS_SETPART_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

inline bool is_setpart_rgs(const ulong *s, ulong n)
// Return whether s[0,1,...,n-1] is a valid RGS of a set partition:
// a string s[0, 1, ..., n-1] such that
// s[k] <= max(s[0], s[1], ..., s[k-1]) + 1.
{
    if ( n == 0 )  return true;  // Nothing to check

    ulong mx = s[0];  // maximum of prefix
    if ( mx != 0 )  return false;

    for (ulong j=1; j<n; ++j)
    {
        const ulong aj = s[j];
        if ( aj > mx )
        {
            ++mx;
            if ( aj > mx )  return false;
        }
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_SETPART_RGS_H__
