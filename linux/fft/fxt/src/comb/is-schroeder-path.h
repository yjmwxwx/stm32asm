#if !defined  HAVE_IS_SCHROEDER_PATH_H__
#define       HAVE_IS_SCHROEDER_PATH_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

inline bool is_schroeder_path(const ulong *x, ulong n2)
// Return whether x[0..n2] is a valid Schroeder path, i.e.,
// whether it is a valid Motzkin path and
// all horizontal stretches have even length.
{
    if ( ! is_motzkin_path(x, n2) )  return false;

    for (ulong i=1, z=0;  i<=n2;  ++i)
    {
        if ( x[i] - x[i-1] != 0 )
        {
            if ( z != 0 )  return false;
            z = 0;
        }
        else  z = 1 - z;
    }

    return true;
}
// -------------------------


#endif  // !defined HAVE_IS_SCHROEDER_PATH_H__
