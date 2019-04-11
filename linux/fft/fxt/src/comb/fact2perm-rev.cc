// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtalloca.h"
#include "aux0/swap.h"
#include "perm/reverse.h"
#include "fxttypes.h"

//#include "jjassert.h"


void
perm2ffact_rev(const ulong *x, ulong n, ulong *fc)
// Convert permutation in x[0,...,n-1] into
//   the (n-1) digit (reversal) factorial representation in fc[0,...,n-2].
// We have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
{
    if ( n==0 )  return;

    ALLOCA(ulong, ti, n);  // inverse permutation
    for (ulong k=0; k<n; ++k)  ti[x[k]] = k;
    for (ulong k=0; k<n-1; ++k)
    {
        ulong j;  // find element k
        for (j=k; j<n; ++j)  if ( ti[j]==k )  break;
        j -= k;
        fc[k] = j;
        reverse(ti+k, j+1);
//        jjassert( j<n-k );
    }
//    jjassert( is_identity(ti, n) );
}
// -------------------------

void
ffact2perm_rev(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Convert the (n-1) digit falling factorial representation in fc[0,...,n-2].
// into permutation in x[0,...,n-1]
// Must have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
// Inverse of perm2ffact_rev().
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = fc[k];
        // Lehmer: rotate_right1(x+k, i+1);
        if ( i ) reverse(x+k, i+1);
    }
}
// -------------------------


void
perm2rfact_rev(const ulong *x, ulong n, ulong *fc)
// Convert permutation in x[0,...,n-1] into
//   the (n-1) digit (reversal) factorial representation in fc[0,...,n-2].
// We have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
{
    if ( n==0 )  return;

    ALLOCA(ulong, ti, n);  // inverse permutation
    for (ulong k=0; k<n; ++k)  ti[x[k]] = k;
    for (ulong k=n-1; k!=0; --k)
    {
        ulong j;  // find element k
        for (j=0; j<=k; ++j)  if ( ti[j]==k )  break;
//        jjassert( j<=k );
        j = k - j;
        fc[k-1] = j;
        reverse(ti+k-j, j+1);
    }
//    jjassert( is_identity(ti, n) );
}
// -------------------------

void
rfact2perm_rev(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Convert the (n-1) digit rising factorial representation in fc[0,...,n-2].
//  into permutation in x[0,...,n-1]
// Must have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
// Inverse of perm2rfact_rev().
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    ulong *y = x+n;
    for (ulong k=n-1;  k!=0;  --k, --y)
    {
        ulong i = fc[k-1];
        if ( i )
        {
            ++i;
            // Lehmer: rotate_left1(y-i, i);
            reverse(y-i, i);
        }
    }
}
// -------------------------
