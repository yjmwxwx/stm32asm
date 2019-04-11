#if !defined  HAVE_PERMRAND_SDC_H__
#define       HAVE_PERMRAND_SDC_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "perm/permrand.h"
#include "fxttypes.h"

inline void random_sdc_permutation(ulong *p, ulong n,
                                   const ulong *d, ulong nd,
                                   ulong *tv=0)
// sdc := Sets into Distinct Cycles.
//
// Let NN={0,1,...,n-1},
// S0 be the set of the d[0] smallest elements of NN,
// S1 be the set of the d[1] smallest elements of NN \ S0
// S2 be the set of the d[2] smallest elements of NN \ { S0 union S1 }
// and so on.
// Let m0 = min(S0), m1 = min(S1) etc.,
// write a<<b for "a precedes b".
//
// Generate random permutation such that
//  x << m0 for all elements (!=m0) of S0,
//  m0 << x << m1 for all elements (!=m1) of S1,
//  m1 << x << m2 for all elements (!=m2) of S2,
// and so on.
//
// As canonical cycle form (CCF):
//  The elements of S0 are in one cycle C0,
//  the elements of S1 are in one cycle C1!=C0,
//  the elements of S2 are in one cycle C2!=C1, C2!=C0,
// and so on.
{
    ulong w = 0;  // number of elements specified via d[]
    for (ulong k=0; k<nd; ++k)  w += d[k];

    ulong *v = tv;
    if ( tv==0 )  v = new ulong[w];
    for (ulong k=0; k<w; ++k)  v[k] = k;

    ulong e = 0,  j = 0;
    while ( e<nd )
    {
        const ulong de = d[e];
        swap2( v[j], v[j+de-1] );  // cycle end
        if ( de>2 )  random_permute( v+j, de-1 );  // make cycle random
        j += de;  ++e;
    }

    random_permutation(p, n);

    e = 0;  j = 0;
    while ( e<w )  // sort w smallest elements in p[] according to v[]
    {
        if ( p[j]<w )  { p[j]=v[e];  ++e; }
        ++j;
    }

    if ( tv==0 )  delete [] v;
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_SDC_H__
