#if !defined  HAVE_IS_CAYLEY_PERM_H__
#define       HAVE_IS_CAYLEY_PERM_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/bitarray.h"

#include "fxttypes.h"


inline bool is_cayley_perm(const ulong *a, ulong n, bitarray *B)
// Return whether a[] is a valid Cayley permutation:
// all elements from 0 to the maximum value occur at least once.
{
    if ( n==0 )  return true;

    ulong mx = 0;
    for (ulong j=0; j<n; ++j)
        if ( a[j] > mx )  mx = a[j];

    if ( mx>=n )  return false;  // some value must be missing

    B->clear_all();

    for (ulong j=0; j<n; ++j)  B->set(a[j]);

    ulong fc = B->first_clear();
    if ( fc > mx )  return false;

    return  true;
}
// -------------------------


#endif  // !defined HAVE_IS_CAYLEY_PERM_H__
