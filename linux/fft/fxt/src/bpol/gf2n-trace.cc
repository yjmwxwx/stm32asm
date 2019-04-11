// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpolmod-arith.h"
#include "bits/parity.h"

#include "fxttypes.h"


ulong
gf2n_trace(ulong a, ulong c, ulong h)
// Return the trace of A, an element of GF(2**k).
// GF(2**k) represented as polynomials modulo C.
//
// trace(A) = \sum_{j=0}^{k-1}{A^(2^j)}
//
// h needs to be a mask with one bit set:
//  h == highest_one(c) >> 1  == 1UL << (degree(C)-1)
//
// the value returned is zero or one
{
    ulong t = a;
    ulong d = h;
    while ( (d>>=1) )
    {
        t = bitpolmod_square(t, c, h);
        t ^= a;
    }
    return  t;
}
// -------------------------


ulong
gf2n_trace_vector(ulong g, ulong c, ulong h)
// Return traces of powers of G, an element of GF(2**k).
// GF(2**k) represented as polynomials modulo C.
//
// h needs to be a mask with one bit set:
//  h == highest_one(c) >> 1  == 1UL << (degree(C)-1)
//
// The returned word can be used for accelerated
// trace computations if G is a generator of GF(2**k)
// represented as polynomials modulo (irreducible) C
//  (usually G='x'=2UL and C a primitive polynomial)
{
    ulong tv = 0;  // return
    ulong m = 1;  // mask
    ulong s = h;  // aux counter
    ulong p = 1;  // powers of g
    // p==g^0, g^1, g^2, g^3, ..., g^{deg(c)-1}
    do
    {
        ulong q = gf2n_trace(p, c, h);
        if ( q )  tv ^= m;
        m <<= 1;
        p = bitpolmod_mult(p, g, c, h);
    }
    while ( (s>>=1) );

    return  tv;
}
// -------------------------

ulong
gf2n_trace_vector_x(ulong c, ulong n)
// Return vector of traces of powers of x, where
//  x is a root of the irreducible polynomial C.
// Must have:  n == degree(C)
{
    c &= ~( 2UL<<(n-1) );  // remove coefficient c[n]

    ulong t = 1;  // set t[0]=1, will be corrected at the end
    for (ulong k=1; k<n; ++k)
    {
        if ( k & 1 )  // k odd: use recursion
        {
            ulong cv = c >> (n-k);  // polynomials coefficients [n-1]..[n-k]
            cv &= t;                // vector (j=1, k,  c[n-j]*t[k-j])
            cv = parity(cv);        //    sum (j=1, k,  c[n-j]*t[k-j])
            t |=  (cv<<k);
        }
        else  // k even:  copy t[k/2] to t[k]
        {
            t |= ( (t>>(k/2)) & 1 ) << k;
        }
    }

    // correct t[0]:
//    t ^= 1;  t |= (n & 1);
    t ^= ((n+1)&1);  // change low bit if n is even

    return t;
}
// -------------------------


ulong
gf2n_half_trace(ulong a, ulong c, ulong h)
// Return the half-trace of A, an element of GF(2**k).
// GF(2**k) represented as polynomials modulo C.
// k must be odd.
//
// halftrace(A) = \sum_{j=0}^{(k-1)/2}{A^(4^(j))}
//
// Let T be the trace, H the halftrace of A.
// Then: H + H^2 = A + T
//   therefore:
// if   (T==0)  both H and H+1 solve y^2+y=A;
// else (T==1)  y^2+y=A has no solutions.
//  further:
// H(A) + H(A)^2 == H(A + A^2)
//
// h needs to be a mask with one bit set:
//  h == highest_one(c) >> 1  == 1UL << (degree(C)-1)
{
    ulong t = a;
    ulong d = h;
    while ( d>>=2 )
    {
        t = bitpolmod_square(t, c, h);
        t = bitpolmod_square(t, c, h);
        t ^= a;
    }
    return  t;
}
// -------------------------

