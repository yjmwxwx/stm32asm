#if !defined  HAVE_IS_SYMMETRIC_H__
#define       HAVE_IS_SYMMETRIC_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <fxttypes.h>

template <typename Type>
inline bool is_symmetric(const Type *a, ulong n)
// Return whether a[] is symmetric.
{
    if ( n > 1 )
    {
        for (ulong j=0, k=n-1;  j<k;  ++j, --k)
            if ( a[j] != a[k] )  return false;
    }

    return true;
}
// -------------------------

#endif // !defined HAVE_IS_SYMMETRIC_H__
