// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtalloca.h"
#include "perm/rotate.h"
#include "fxttypes.h"


//#include "jjassert.h"
//#include "fxtio.h"

void
perm2ffact_rot(const ulong *x, ulong n, ulong *fc)
// Convert permutation in x[0,...,n-1] into
//   the (n-1) digit (rot) factorial representation in fc[0,...,n-2].
// We have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
{
#if 1
    if ( n==0 )  return;

    ALLOCA(ulong, t, n);
//    for (ulong k=0; k<n; ++k)  t[k] = x[k];
    for (ulong k=0; k<n; ++k)  t[x[k]] = k;  // inverse permutation
    for (ulong k=0; k<n-1; ++k)
    {
        ulong s = 0;  while ( t[k+s] != k )  ++s;
        if ( s!=0 )  rotate_left(t+k, n-k, s);
        fc[k] = s;
    }
//    for (ulong k=0; k<n; ++k)  jjassert( t[k] == k );

#else  // very complicated version:
    // Algorithm: look for position of cyclic (mod n) successor:
    if ( n<2 )
    {
        if ( n==2 )  fc[0] = (x[1]!=0);
        return;
    }

    ALLOCA(ulong, t, n);  // copy of permutation
    for (ulong k=0; k<n; ++k)  t[k] = x[k];

    for (ulong k=n-2, len=2;  len<n;  --k, ++len)
    {
//        jjassert( k-1 < n );
//        jjassert( k < n );
        ulong lp = k-1;
        ulong le = t[lp];
        ulong re  = n;  // == +infinity
        ulong rp = k;

        // find minimal element to the right that is greater than le:
        for (ulong j=k; j<n; ++j)
        {
            ulong e = t[j];
            if ( (e>le) && (e<re) )  { re=e;  rp=j; }
        }

        // If all right elements are less than le, use minimum:
        if ( re==n )
        {
            for (ulong j=k; j<n; ++j)
            {
                ulong e = t[j];
                if ( e<re )  { re=e; rp=j; }
            }
        }

        ulong i = rp - k;
        if ( i )  i = len-i;
//        cout << endl << " :" << k << " len=" << len
//             << " le=" << le << " re=" << re << " rp=" << rp << " i=" << i << endl;
//        jjassert( i < len );
//        jjassert( k > 0 );
        fc[k] = i;
        rotate_right(t+k, len, i);
    }

    // find zero:
    ulong j = 0;  while ( t[j]!=0 )  ++j;
    fc[0] = ( j==0 ? 0 : n - j );
#endif
}
// -------------------------



void
ffact2perm_rot(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Inverse of perm2ffact_rot().
// Convert the (n-1) digit falling factorial representation in fc[0,...,n-2].
// into permutation in x[0,...,n-1]
// Must have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    for (ulong k=0, len=n;  k<n-1;  ++k, --len)
    {
        ulong i = fc[k];
        rotate_left(x+k, len, i);
    }
}
// -------------------------


void
perm2rfact_rot(const ulong *x, ulong n, ulong *fc)
// Convert permutation in x[0,...,n-1] into
//   the (n-1) digit (swaps) factorial representation in fc[0,...,n-2].
// We have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
{
    if ( n==0 )  return;

    ALLOCA(ulong, t, n);
    for (ulong k=0; k<n; ++k)  t[x[k]] = k;  // inverse permutation
    for (ulong k=0; k<n-1; ++k)
    {
        ulong s = 0;  while ( t[k+s] != k )  ++s;
        if ( s!=0 )  rotate_left(t+k, n-k, s);
        fc[n-2-k] = s;
    }
}
// -------------------------


void
rfact2perm_rot(const ulong *fc, ulong n, ulong *x, bool iq/*=true*/)
// Inverser of perm2rfact_rot().
// Convert the (n-1) digit rising factorial representation in fc[0,...,n-2].
//  into permutation in x[0,...,n-1]
// Must have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
// Set iq==true if permutation shall be initialized with 0,1,...,n-1.
{
    if ( n==0 )  return;

    if ( iq )  for (ulong k=0; k<n; ++k)  x[k] = k;
    for (ulong k=n-2, len=n;  len>1;  --k, --len)
    {
        ulong i = fc[k];
        rotate_left(x+n-len, len, i);
    }
}
// -------------------------
