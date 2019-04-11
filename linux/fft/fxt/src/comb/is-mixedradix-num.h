#if !defined  HAVE_IS_MIXEDRADIX_NUM_H__
#define       HAVE_IS_MIXEDRADIX_NUM_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


inline bool is_mixedradix_num(const ulong *a, ulong n, const ulong *m1)
// Return whether a[j] <= m1[j] for 0<=j<n.
{
    for (ulong j=0; j<n; ++j)
        if ( a[j] > m1[j] )  return false;
    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_MIXEDRADIX_NUM_H__
