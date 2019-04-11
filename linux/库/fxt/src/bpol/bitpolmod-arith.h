#if !defined  HAVE_BITPOLMOD_ARITH_H__
#define       HAVE_BITPOLMOD_ARITH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpol-gcd.h"  // bitpol_egcd()

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bithigh.h"  // highest_one() for powering
//#include "cmath.h"

//<<
// Modular arithmetic with polynomials over Z/2Z.
// The polynomial W represented by the word w is
//   W = pol(w) =: \sum_k{ [bit_k(w)] * x^k}
// The modulus is C and
//   h needs to be a mask with one bit set:
//   h == highest_one(c) >> 1  == 1UL << (degree(C)-1)
//>>


#define  MULT_UNROLL  // define to unroll loops 4-fold
#define  SQUARE_BY_MULT  // whether to square via multiplication


static inline ulong bitpolmod_times_x(ulong a, ulong c, ulong h)
// Return  (A * x) mod C
//
// If C is a primitive polynomial of degree n
// successive calls will cycle through all 2**n-1
// n-bit words and the sequence of bits
// (any fixed position) of a constitutes
// a shift register sequence (SRS).
// Start with a=2 to get an SRS that starts with
// n-1 consecutive zeros (use bit 0 of a)
{
    ulong s = a & h;
    a <<= 1;
    if ( s )  a ^= c;
    return  a;
}
// -------------------------

static inline ulong bitpolmod_times_x2(ulong a, ulong c, ulong h)
// Return  (A * x * x) mod C
// Used for squaring.
{
    { ulong s=a&h; a<<=1;  if (s) a^=c; }
    { ulong s=a&h; a<<=1;  if (s) a^=c; }
    return  a;
}
// -------------------------

static inline ulong bitpolmod_div_x(ulong a, ulong c, ulong h)
// Return  (A / x) mod C
// C must have nonzero constant term: (c&1)==1
//
// If C is a primitive polynomial of degree n
// successive calls will cycle through all 2**n-1
// n-bit words and the sequence of bits
// (any fixed position) of a constitutes
// a shift register sequence (SRS).
{
    ulong s = a & 1;
    a >>= 1;
    if ( s )
    {
        a ^= (c>>1);
        a |= h;  // so it also works for  n == BITS_PER_LONG
    }
    return  a;
}
// -------------------------


static inline ulong bitpolmod_inv_x(ulong c, ulong h)
// Return  (1 / x) mod C
// C must have nonzero constant term: (c&1)==1
// c>>1 == (C-1)/x = (0-1)/x == -1/x == 1/x (mod C).
{
// commented out lines take care of cases when x has no inverse mod C:
//    if ( 0==(c & 1) )  return 0;
//    if ( 1==c )  return 0;

    ulong a = (c>>1);
    a |= h;  // so it also works for  n == BITS_PER_LONG
    return  a;
}
// -------------------------


static inline ulong bitpolmod_mult(ulong a, ulong b, ulong c, ulong h)
// Return  (A * B) mod C
//
// Must have  deg(A) < deg(C)  and  deg(B) < deg(C)
//.
// With b=2 (== 'x') the result is identical to
//   bitpolmod_times_x(a, c, h)
{
    ulong t = 0;
    do
    {
#ifndef MULT_UNROLL
        if ( b & 1 )  t ^= a;
        b >>= 1;

        ulong s = a & h;
        a <<= 1;
        if ( s )  a ^= c;

#else  // unrolled:
        { if (b&1) t^=a;  b>>=1; ulong s=a&h; a<<=1;  if (s) a^=c; }
        { if (b&1) t^=a;  b>>=1; ulong s=a&h; a<<=1;  if (s) a^=c; }
        { if (b&1) t^=a;  b>>=1; ulong s=a&h; a<<=1;  if (s) a^=c; }
        { if (b&1) t^=a;  b>>=1; ulong s=a&h; a<<=1;  if (s) a^=c; }
#endif
    }
    while ( b );
    return  t;
}
// -------------------------

static inline ulong bitpolmod_square(ulong a, ulong c, ulong h)
// Return A*A mod C
// == bitpolmod_mult(a, a, c, h);
// compute \sum_{k=0}^{d}{a_k\,x^k} as \sum_{k=0}^{d}{a_k\,x^{2k}}
{
#ifdef SQUARE_BY_MULT

    return bitpolmod_mult(a, a, c, h);

#else  // SQUARE_BY_MULT

    ulong t = 0, s = 1;
    do
    {
#ifndef MULT_UNROLL
        if ( a&1 )  t ^= s;
        a >>= 1;
        s = bitpolmod_times_x2(s, c, h);
#else  // unrolled:
        if (a&1) t^=s;  a>>=1; s=bitpolmod_times_x2(s, c, h);
        if (a&1) t^=s;  a>>=1; s=bitpolmod_times_x2(s, c, h);
        if (a&1) t^=s;  a>>=1; s=bitpolmod_times_x2(s, c, h);
        if (a&1) t^=s;  a>>=1; s=bitpolmod_times_x2(s, c, h);
#endif  // MULT_UNROLL
    }
    while ( a );
    return t;
#endif  // SQUARE_BY_MULT
}
// -------------------------


inline ulong bitpolmod_power(ulong a, ulong e, ulong c, ulong h)
// Return (A ** e)  mod C
{
#if 1  // left-to-right powering:
    ulong s = a;
    ulong b = highest_one(e);
    while ( b>1 )
    {
        b >>= 1;
        s = bitpolmod_square(s, c, h);  // s *= s;
        if ( e & b )  s = bitpolmod_mult(s, a, c, h);   // s *= a;
    }
    return s;

#else  // right-to-left powering:

    if ( 0==e )  return 1;  // avoid hang with e==0 in following while
    ulong s = a;
    while ( 0==(e&1) )
    {
        s = bitpolmod_square(s, c, h);
        e >>= 1;
    }

    a = s;
    while ( 0!=(e>>=1) )
    {
        s = bitpolmod_square(s, c, h);
        if ( e & 1 )  a = bitpolmod_mult(a, s, c, h);
    }
    return  a;

#endif
}
// -------------------------

inline ulong bitpolmod_xpower(ulong e, ulong c, ulong h)
// Return (x ** e)  mod C
{
    ulong s = 2;  // 'x'
    ulong b = highest_one(e);
    while ( b>1 )
    {
        b >>= 1;
        s = bitpolmod_square(s, c, h);  // s *= s;
        if ( e & b )  s = bitpolmod_times_x(s, c, h);   // s *= x;
    }
    return s;
}
// -------------------------

inline ulong bitpolmod_inverse_irred(ulong a, ulong c, ulong h)
// Return (A ** -1)  mod C
// Must have: C irreducible.
//
// With irreducible C the inverse of A can be obtained via
// i = bitpolmod_power(a, r1, c, h)
//  where r1 = (h<<1)-2 = max_order - 1 = 2^degree(C) - 2
// Then  1 == bitpolmod_mult(a, i, c, h)
{
    ulong r1 = (h<<1) - 2;  // max order minus one
    ulong i = bitpolmod_power(a, r1, c, h);
    return  i;
}
// -------------------------

inline ulong bitpolmod_inverse(ulong a, ulong c)
// Return the inverse of A modulo C if it exists, else zero.
// Must have deg(A) < deg(C)
{
    ulong i, t;  // t unused
    ulong g = bitpol_egcd(a, c, i, t);
    if ( g!=1 )  i = 0;
    return i;
}
// -------------------------

inline ulong bitpolmod_divide(ulong a, ulong b, ulong c, ulong h)
// Return A/B modulo C.
// Must have: gcd(b,c)==1
{
    ulong i = bitpolmod_inverse(b, c);
    a = bitpolmod_mult(a, i, c, h);
    return a;
}
// -------------------------


static inline ulong bitpolmod_sqrt(ulong a, ulong c, ulong h)
// Return sqrt(A)  mod C
// Using the identity sqrt(A) = A^(2^(n-1)) where n=deg(C)
{
    ulong d = h;
    while ( (d>>=1) )  a = bitpolmod_square(a, c, h);
    return  a;
}
// -------------------------


#undef MULT_UNROLL
#undef SQUARE_BY_MULT

#endif  // !defined HAVE_BITPOLMOD_ARITH_H__
