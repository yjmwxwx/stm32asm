// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/rotate.h"
#include "aux0/swap.h"
#include "fxttypes.h"

//#include "fxtalloca.h"


void
perm2ffact(const ulong *x, ulong n, ulong *fc)
// Convert permutation in x[0,...,n-1] into
//   the (n-1) digit falling factorial representation in fc[0,...,n-2].
// We have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
// Works as long as all elements in x[] are distinct.
// This is the so-called "Lehmer code" of a permutation.
// On return fc[k] contains the number of right inversions of position k,
//  the number of j > k where x[j] < x[k].
{
    if ( n==0 )  return;

    for (ulong k=0; k<n-1; ++k)
    {
        ulong xk = x[k];
        ulong i = 0;
        for (ulong j=k+1; j<n; ++j)  if ( x[j]<xk )  ++i;
        fc[k] = i;
    }
}
// -------------------------

void
ffact2perm(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Inverse of perm2ffact():
// Convert the (n-1) digit falling factorial representation
//  in fc[0,...,n-2] into a permutation in x[0,...,n-1].
// Must have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = fc[k];
        if ( i )  rotate_right1(x+k, i+1);
    }
}
// -------------------------

void
ffact2invperm(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Convert the (n-1) digit falling factorial representation in fc[0,...,n-2]
// into permutation in x[0,...,n-1] such that
// the permutation is the inverse of the one computed via ffact2perm().
// Must have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    for (ulong k=n-2; (long)k>=0; --k)
    {
        ulong i = fc[k];
        if ( i )  rotate_left1(x+k, i+1);
    }
}
// -------------------------


void
perm2rfact(const ulong *x, ulong n, ulong *fc)
// Convert permutation in x[0,...,n-1] into
//   the (n-1) digit rising factorial representation in fc[0,...,n-2].
// We have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
// Works as long as all elements in x[] are distinct.
// On return fc[k] contains the number of left inversions of position k,
//  the number of j < k where x[j] > x[k].
{
//    if ( n==0 )  return;

    for (ulong k=1; k<n; ++k)
    {
        ulong xk = x[k];
        ulong i = 0;
        for (ulong j=0; j<k; ++j)  if ( x[j]>xk )  ++i;
        fc[k-1] = i;
    }
}
// -------------------------

void
rfact2perm(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Inverse of perm2rfact():
// Convert the (n-1) digit rising factorial representation in fc[0,...,n-2].
//  into permutation in x[0,...,n-1]
// Must have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    ulong *y = x+n;
    for (ulong k=n-1;  k!=0;  --k, --y)
    {
        ulong i = fc[k-1];
        if ( i )  { ++i;  rotate_left1(y-i, i); }
    }
}
// -------------------------


void
rfact2invperm(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Convert the (n-1) digit rising factorial representation in fc[0,...,n-2].
//  into permutation in x[0,...,n-1] such that
// the permutation is the inverse of the one computed via rfact2perm().
// Must have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    ulong *y = x + 2;
    for (ulong k=0;  k<n-1;  ++k, ++y)
    {
        ulong i = fc[k];
        if ( i )  { ++i;  rotate_right1(y-i, i); }
    }
}
// -------------------------


void
perm_rev_compl(ulong *x, ulong n, bool zb/*=true*/)
// Reverse and complement permutation in x[].
// zb shell reflect if the entires start from 0 (else from 1).
{
    if ( n<=1 )  return;
    const ulong n1 = n + ( zb ? -1UL : +1UL );
    for (ulong a=0, b=n-1; a<=b;  ++a, --b)
    {
        ulong ca = n1 - x[a];
        ulong cb = n1 - x[b];
        x[a] = cb;
        x[b] = ca;
    }
}
// -------------------------
