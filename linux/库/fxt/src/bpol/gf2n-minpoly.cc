// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/gf2n.h"
#include "bits/bitsperlong.h"
//#include "jjassert.h"
#include "fxttypes.h"  // ulong


ulong
gf2n_minpoly(GF2n a, ulong &bp)
// Compute the minimal polynomial p(x) of a \in GF(2**n).
// Return the degree of p().
// The polynomial p() is written to bp
//  (its coefficients are in GF(2)).
// A version that does not depend on class GF2n is
//  given in bpol/bitpolmod-minpoly.cc
{
    if ( a.v_ < 2 )  { bp = 2 ^ a.v_;  return 1; }

    const GF2n x(2UL);  // a root of the polynomial GF2n::c_
    GF2n s = a;
    GF2n m(1UL);  // minpoly
    ulong d = 0;  // degree
    do
    {
        m *= (x - s);  // x - a^(2^d)
        ++d;
        s = s.sqr();
    }
    while ( s != a );

    if ( d==GF2n::n_ )  m.v_ ^= GF2n::c_;
    bp = m.v_;

    return  d;
}
// -------------------------


ulong
gf2n_minpoly2(GF2n a, ulong &bp)
// Compute the minimal polynomial p(x) of a \in GF(2**n).
// Return the degree of p().
// The polynomial p() is written to bp
//  (its coefficients are in GF(2)).
// A version that does not depend on class GF2n is
//  given in bpol/bitpolmod-minpoly.cc
// NOTE: prefer the routine gf2n_minpoly()!
{
    GF2n p[BITS_PER_LONG+1];
    ulong n = GF2n::n_;
    for (ulong k=0; k<=n; ++k)  p[k] = 0;
    p[0] = 1;
    GF2n s = a;
    ulong d;  // degree
    for (d=1; d<=n; ++d)
    {
        for (ulong k=d; 0!=k; --k)  p[k] = p[k-1];
        p[0] = 0;
        for (ulong k=0; k<d; ++k)  p[k] += p[k+1] * s;

        s = s.sqr();
        if ( s == a )  break;
    }

    // Here all coefficients are either zero or one,
    //  so we can fill them into a binary word:
    ulong p2 = 0;
    for (ulong j=0; j<=d; ++j)  p2 |= (p[j].v_ << j);
    bp = p2;

    // Check that coefficients are in GF(2):
//    ulong q = 0;
//    for (ulong j=0; j<=d; ++j)  q  |= (p[j].v_);
//    jjassert( 0==(q>>1) );

    return  d;
}
// -------------------------


GF2n
gf2n_eval_poly(GF2n a, ulong bp)
// Evalute polynomial bp (coefficients \in GF(2))
//  for argument a \in GF(2**n).
{
    GF2n s = GF2n::one;
    GF2n v = GF2n::zero;
    while ( bp )
    {
        if ( bp & 1UL )  v += s;
        bp >>= 1;
        s *= a;
    }
    return  v;
}
// -------------------------

