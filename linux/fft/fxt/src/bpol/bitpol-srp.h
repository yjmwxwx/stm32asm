#if !defined  HAVE_BITPOL_SRP_H__
#define       HAVE_BITPOL_SRP_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bpol/bitpol-arith.h"  // bitpol_div_x2p1()
//#include "bits/bitsperlong.h"  // BITS_PER_LONG
#include "fxttypes.h"  // ulong


inline ulong bitpol_pol2srp(ulong f, ulong d)
// Return  the self-reciprocal polynomial S=x^d*F(x+1/x) where d=deg(f).
// W = sum(j=0, d,   F(j)*x^(d-j)*(1+x^2)^j )  where
//   F(j) is the j-th coefficient of F.
// Must have: d==degree(F)
{
    ulong w = 1;  // == (x^2+1)^j
    ulong s = 0;
    do  // for j = 0 ... d:
    {
        if ( f & 1 )  s ^= (w << d);  // S += F(j)*x^(d-j)*(1+x^2)^j
        w ^= (w<<2);                  // w *= (1+x^2)
        f >>= 1;                      // next coefficient to low end
    }
    while ( d-- );
    return s;
}
// -------------------------

inline ulong bitpol_srp2pol(ulong s, ulong hd)
// Inverse of bitpol_pol2srp().
// Must have: hd = degree(s)/2 (note: _half_ of the degree).
// Only the lower half coefficients are accessed, i.e.
//   the routine works for degree(S) <= 2*BITS_PER_LONG-2.
{
    ulong f = 0;
    ulong mh = 1UL << hd;
    ulong ml = 1;
    do
    {
        ulong b = s & mh;  // central coefficient
//        s ^= b;  // set central coefficient to zero (not needed)
        if ( b )  f |= ml;  // positions 0,1,...,hd
        ml <<= 1;
        s = bitpol_div_x2p1(s);  // exact division by (x^2+1)
    }
    while ( (mh>>=1) );
    return f;
}
// -------------------------

#endif  // !defined HAVE_BITPOL_SRP_H__
