// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtalloca.h"
#include "aux0/swap.h"
#include "fxttypes.h"


void
perm2ffact_swp(const ulong *x, ulong n, ulong *fc)
// Convert permutation in x[0, 1, ..., n-1] into
//   the (n-1) digit (swaps) factorial representation in fc[0, 1, ..., n-2].
// We have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
// Work is proportional to n.
{
    if ( n==0 )  return;

    ALLOCA(ulong, t, n);
    for (ulong k=0; k<n; ++k)  t[k] = x[k];
    ALLOCA(ulong, ti, n);  // inverse permutation
    for (ulong k=0; k<n; ++k)  ti[t[k]] = k;

    for (ulong k=0; k<n-1; ++k)
    {
        ulong tk = t[k];  // >= k
        fc[k] = tk - k;
        ulong j = ti[k];  // location of element k, j>=k
        ti[tk] = j;
        t[j] = tk;
    }
}
// -------------------------

void
ffact2perm_swp(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Inverse of perm2ffact_swp().
// Permutation is different than that obtained via ffact2perm().
// Work is proportional to n.
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = fc[k];
        swap2( x[k], x[k+i] );
    }
}
// -------------------------

void
ffact2invperm_swp(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Generate inverse permutation wrt. ffact2perm_swp().
// Work is proportional to n.
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;

    if ( n<=1 )  return;

    ulong k = n-2;
    do
    {
        ulong i = fc[k];
        swap2( x[k], x[k+i] );
    }
    while ( k-- );
}
// -------------------------


void
perm2rfact_swp(const ulong *x, ulong n, ulong *fc)
// Convert permutation in x[0, 1, ..., n-1] into
//   the (n-1) digit (swaps) factorial representation in fc[0, 1, ..., n-2].
// We have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
// Work is proportional to n.
{
    if ( n==0 )  return;

    ALLOCA(ulong, t, n);
    for (ulong k=0; k<n; ++k)  t[k] = x[k];
    ALLOCA(ulong, ti, n);  // inverse permutation
    for (ulong k=0; k<n; ++k)  ti[t[k]] = k;

    for (ulong k=0; k<n-1; ++k)
    {
        ulong j = ti[k];  // location of element k, j>=k
        fc[n-2-k] = j - k;
        ulong tk = t[k];  // >=k
        ti[tk] = j;
        t[j] = tk;
    }
}
// -------------------------

void
rfact2perm_swp(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Inverse of perm2rfact_swp().
// Permutation is different than that obtained via rfact2perm().
// Work is proportional to n.
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    for (ulong k=0, j=n-2;  k<n-1;  ++k, --j)
    {
        ulong i = fc[k];
        swap2( x[j], x[j+i] );
    }
}
// -------------------------


void
rfact2invperm_swp(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Generate inverse permutation wrt. rfact2perm_swp().
// Work is proportional to n.
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    if ( n<=1 )  return;
    ulong k = n-2, j=0;
    do
    {
        ulong i = fc[k];
        swap2( x[j], x[j+i] );
        ++j;
    }
    while ( k-- );
}
// -------------------------


