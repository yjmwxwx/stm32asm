#if !defined  HAVE_PERMRAND_ORD_H__
#define       HAVE_PERMRAND_ORD_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/permrand.h"  // random_permute()

#include "aux0/swap.h"
#include "fxttypes.h"


inline void random_ord01_permutation(ulong *p, ulong n)
// Random permutation such that elements 0 and 1 are in order.
{
    random_permutation(p, n);
    ulong t = 0;
    while ( p[t]>1 )  ++t;
    if ( p[t]==0 )  return;  // already in correct order
    p[t] = 0;
    do { ++t; }  while ( p[t]!=0 );
    p[t] = 1;
}
// -------------------------


inline void random_ordk_permutation(ulong *p, ulong n, ulong k)
// Random permutation such that the k smallest elements are in order.
// Must have k<=n.
{
    random_permutation(p, n);
    for (ulong j=0, e=0;  e<k;  ++j)  if ( p[j]<k )  { p[j]=e;  ++e; }
}
// -------------------------


inline void random_lastk_permutation(ulong *p, ulong n, ulong k)
// Random permutation such that 0 appears as last of the k smallest elements.
// Must have k<=n.
{
    random_permutation(p, n);
    if ( k<=1 )  return;

    ulong p0=0, pl=0;  // position of 0, and last (in k smallest elements)
    for (ulong t=0, j=0;  j<k;  ++t)
    {
        if ( p[t]<k )
        {
            pl = t;  // update position of last
            if ( p[t]==0 )  { p0 = t; }  // record position of 0
            ++j;   // j out of k smallest found
        }
    }
    // here t is the position of the last of the k smallest elements
    swap2( p[p0], p[pl] );
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_ORD_H__
