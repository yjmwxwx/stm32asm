#if !defined  HAVE_RAND_IDX_H__
#define       HAVE_RAND_IDX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

#include <cstdlib>  // rand()

inline ulong rand_idx(ulong m)
// Return random number in the range [0, 1, ..., m-1].
// Must have m>0.
{
    if ( m==1 )  return 0;  // could also use % 1
    ulong x = (ulong)rand();
    x ^= x>>16;    // avoid using low bits of rand() alone
    return  x % m;
}
// -------------------------


#endif  // !defined HAVE_RAND_IDX_H__
