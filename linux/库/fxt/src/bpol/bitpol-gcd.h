#if !defined  HAVE_BITPOL_GCD_H__
#define       HAVE_BITPOL_GCD_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bpol/bitpol-arith.h"  // bitpol_div(), bitpol_rem()
#include "bits/bitlow.h"  // lowest_one_idx()
//#include "bits/cswap.h"  // cswap_lt()
#include "fxttypes.h"

//<<
// GCD, EGCD and inverse with polynomials over Z/2Z
// The polynomial W represented by the word w is
//  W = pol(w) =: \sum_k{ [bit_k(w)] * x^k}
//>>

inline ulong bitpol_gcd(ulong a, ulong b)
// Return polynomial gcd(A, B)
{
    if ( a<b )  { ulong t=a; a=b; b=t; }  // swap if deg(A)<deg(B)
    // here: b<=a
    while ( 0!=b )
    {
        ulong c = bitpol_rem(a, b);
        a = b;
        b = c;
    }
    // a *= inverse( leading_coeff(a) )
    return  a;
}
// -------------------------


inline ulong bitpol_binary_gcd(ulong a, ulong b)
// Return polynomial gcd(A, B)
{
    if ( (a==0) || (b==0) )  return a|b;  // one (or both) of a, b zero?
//    {  // one (or both) of a, b zero?
//        ulong ta = a^b,  to = a|b;
//        if ( ta==to )  return to;
//    }

#if 0
    ulong k = 0;
    while ( !((a|b)&1) )  // both divisible by x
    {
        k++;
        a >>= 1;
        b >>= 1;
    }
    while ( !(a&1) )  a >>= 1;
    while ( !(b&1) )  b >>= 1;
#else
    ulong ka = lowest_one_idx(a);
    a >>= ka;
    ulong kb = lowest_one_idx(b);
    b >>= kb;
    ulong k = ( ka<kb ? ka : kb );
#endif

    while ( a!=b )
    {
        if ( a < b )  { ulong t=a; a=b; b=t; }  // swap if deg(A)<deg(B)
//        { ulong x=a^b;  if (a>=b) x=0;  a^=x;  b^=x; }  // same, branchless
//        cswap_lt(a, b);  // same, with AMD64: branchless assembler

        ulong t = (a^b) >> 1;
#if 0
        while ( !(t&1) )  t >>= 1;
        a = t;
#else
        a = (t >> lowest_one_idx(t));
#endif
    }

    return  a << k;
}
// -------------------------


inline ulong bitpol_egcd(ulong u, ulong v, ulong &iu, ulong &iv)
// Return u3 and set u1,v1 so that  gcd(u,v) == u3 == u*u1 + v*u2
//
// If u3==1 then u1 is the inverse of u modulo v
//          and  u2 is the inverse of v modulo u
//.
// Cf. Knuth2, p.325
{
    ulong u1 = 1,  u2 = 0;
    ulong v1 = 0,  v3 = v;
    ulong u3 = u,  v2 = 1;
    while ( v3!=0 )
    {
//        ulong q = bitpol_div(u3, v3);  // == u3 / v3;
        ulong q, t3;
        bitpol_divrem(u3, v3, q, t3);

        ulong t1 = u1 ^ bitpol_mult(v1, q);  // == u1 - v1 * q;
        u1 = v1;  v1 = t1;

//        ulong t3 = u3 ^ bitpol_mult(v3, q);  // == u3 - v3 * q;
        u3 = v3;  v3 = t3;

        ulong t2 = u2 ^ bitpol_mult(v2, q);  // == u2 - v2 * q;
        u2 = v2;  v2 = t2;
    }

    iu = u1;  iv = u2;
    return u3;
}
// -------------------------



#endif  // !defined HAVE_BITPOL_GCD_H__
