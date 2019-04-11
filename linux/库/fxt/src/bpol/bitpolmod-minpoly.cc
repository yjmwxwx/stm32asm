// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpolmod-arith.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"

//#include "jjassert.h"

ulong
bitpolmod_minpoly(ulong a, ulong c, ulong n, ulong &bp)
// Compute the minimal polynomial p(x) of A modulo C
// Return the degree of p().
// The polynomial p() is written to bp
//  (its coefficients are in GF(2)).
{
    const ulong x = 2;  // a root of C
    const ulong h = 1UL << (n-1);  // aux
    ulong s = a;
    ulong m = 1;  // minpoly
    ulong d = 0;  // degree
    do
    {
        ulong t = x ^ s;  // x - a^(2^d)
        ++d;
        m = bitpolmod_mult(m, t, c, h);
        s = bitpolmod_square(s, c, h);
    }
    while ( s != a );

    if ( d==n )  m ^= c;
    bp = m;

    return  d;
}
// -------------------------


ulong
bitpolmod_minpoly2(ulong a, ulong c, ulong n, ulong &bp)
// Compute the minimal polynomial p(x) of A modulo C
// Return the degree of p().
// The polynomial p() is written to bp
//  (its coefficients are in GF(2)).
// NOTE: prefer the routine bitpolmod_minpoly()!
{
    ulong p[BITS_PER_LONG+1];
    for (ulong k=0; k<=n; ++k)  p[k] = 0;
    p[0] = 1;
    const ulong h = 1UL << (n-1);  // aux
    ulong s = a;
    ulong d;  // degree
    for (d=1; d<=n; ++d)
    {
        for (ulong k=d; 0!=k; --k)  p[k] = p[k-1];
        p[0] = 0;
        for (ulong k=0; k<d; ++k)  p[k] ^= bitpolmod_mult(p[k+1], s, c, h);
        s = bitpolmod_square(s, c, h);

        if ( s == a )  break;
    }

    // Here all coefficients are either zero or one,
    //  so we can fill them into a binary word:
    ulong p2 = 0;
    for (ulong j=0; j<=d; ++j)  p2 |= (p[j] << j);
    bp = p2;

//    // Check that coefficients are in GF(2):
//    ulong q = 0;
//    for (ulong j=0; j<=d; ++j)  q  |= p[j];
//    jjassert( 0==(q>>1) );

    return  d;
}
// -------------------------

