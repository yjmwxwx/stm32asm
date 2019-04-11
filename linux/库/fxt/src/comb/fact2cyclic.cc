// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "fxttypes.h"


void
ffact2cyclic(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Generate cyclic permutation in x[]
//   from the (n-2) digit factorial number in fc[0,...,n-3].
// Falling radices:  [n-1, ..., 3, 2]
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;

    for (ulong k=n-1; k>1; --k)
    {
        ulong z = n-1-k;  // 0, ..., n-3
        ulong i = fc[z];
        swap2(x[k], x[i]);
    }

    if ( n>1 )  swap2(x[0], x[1]);
}
// -------------------------


void
rfact2cyclic(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Generate cyclic permutation in x[]
//   from the (n-2) digit factorial number in fc[0,...,n-3].
// Rising radices:  [2, 3, ..., n-1]
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;

    for (ulong k=n-1; k>1; --k)
    {
        ulong i = fc[k-2];  // k-2 == n-3, ..., 0
        swap2(x[k], x[i]);
    }

    if ( n>1 )  swap2(x[0], x[1]);
}
// -------------------------

