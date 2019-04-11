#if !defined  HAVE_BITPOL_ARITH_H__
#define       HAVE_BITPOL_ARITH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bithigh.h"  // highest_one()
//#include "bits/revgraycode.h"  // inverse_rev_gray_code()
#include "bits/bitsperlong.h"
#include "fxttypes.h"


//<<
// Arithmetic with polynomials over Z/2Z
// The polynomial W represented by the word w is
//  W = pol(w) =: \sum_k{ [bit_k(w)] * x^k}
//>>

#define  MULT_UNROLL  // define to unroll loops 4-fold

inline ulong bitpol_mult(ulong a, ulong b)
// Return  A * B
// B=2 corresponds to multiplication with 'x'
// Note that the result will silently overflow
//  if deg(A)+deg(B) >= BITS_PER_LONG
{
    ulong t = 0;
    do
    {
        if ( b & 1 )  t ^= a;
        b >>= 1;  a <<= 1;
#ifdef MULT_UNROLL
        if ( b & 1 )  t ^= a;
        b >>= 1;  a <<= 1;
        if ( b & 1 )  t ^= a;
        b >>= 1;  a <<= 1;
        if ( b & 1 )  t ^= a;
        b >>= 1;  a <<= 1;
#endif
    }
    while ( b );
    return  t;
}
// -------------------------

inline ulong bitpol_square(ulong a)
// Return A * A
// == bit_zip(a)
// == bit_zip0(a)
// == bitpol_mult(a, a);
{
    ulong t = 0,  m = 1UL;
    do
    {
        if ( a&1 )  t ^= m;
        m <<= 2;  a >>= 1;
#ifdef  MULT_UNROLL
        if ( a&1 )  t ^= m;
        m <<= 2;  a >>= 1;
        if ( a&1 )  t ^= m;
        m <<= 2;  a >>= 1;
        if ( a&1 )  t ^= m;
        m <<= 2;  a >>= 1;
#endif
    }
    while ( a );
    return t;
}
// -------------------------


inline ulong bitpol_power(ulong a, ulong e)
// Return A ** e
// Overflow will occur even for moderate exponents
{
    if ( 0==a )  return 0;
    if ( 0==e )  return 1;

    ulong s = a;
    while ( 0==(e&1) )
    {
        s = bitpol_square(s);
        e >>= 1;
    }

    a = s;
    while ( 0!=(e>>=1) )
    {
        s = bitpol_square(s);
        if ( e & 1 )  a = bitpol_mult(a, s);
    }
    return  a;
}
// -------------------------


inline ulong bitpol_rem(ulong a, const ulong b)
// Return  R = A % B = A - (A/B)*B
// Must have: B!=0
{
//    if ( 0==b ) return a;  // allow b==0
    const ulong db = highest_one_idx(b);
    ulong da;
    while ( db <= (da=highest_one_idx(a)) )
    {
        if ( 0==a )  break;  // needed because highest_one_idx(0)==highest_one_idx(1)
        a ^= (b<<(da-db));
    }
    return  a;

    // version for polynomials of small degree:
//    while ( b <= a )
//    {
//        ulong t = b;
//        while ( (a^t) > t )  t <<= 1;
//        // =^= while ( highest_one(a) > highest_one(t) )  t <<= 1;
//        a ^= t;
//    }
//    return  a;

//    if ( b <= a )
//    {
//        ulong t = b;
//        while ( (a^t) > t )  t <<= 1;
//        ulong h = highest_one(t);
//        do
//        {
//            a ^= t;
//            do
//            {
//                t >>= 1;
//                h >>= 1;
//            }
//            while ( h > a );
//        }
//        while ( t>=b );
//    }
//    return  a;
}
// -------------------------

inline ulong bitpol_div(ulong a, ulong b)
// Return  Q = A / B
// Must have B!=0.
{
//    if ( 0==b )  return 0;  //  allow b==0
    const ulong db = highest_one_idx(b);
    ulong q = 0;  // quotient
    ulong da;
    while ( db <= (da=highest_one_idx(a)) )
    {
        if ( 0==a )  break;  // needed because highest_one_idx(0)==highest_one_idx(1)
        a ^= (b<<(da-db));
        q ^= (1UL<<(da-db));
    }
    return  q;

//    if ( b > a )  return 0;
//    ulong t = b;
//    ulong qb = 1;
//    while ( (a^t) > t )  { t <<= 1;  qb <<= 1; }
//    ulong h = highest_one(t);
//    ulong q = 0;
//    do
//    {
//        a ^= t;
//        q ^= qb;
//        do
//        {
//            t >>= 1;
//            h >>= 1;
//            qb >>= 1;
//        }
//        while ( h > a );
//    }
//    while ( t>=b );
//    return  q;
}
// -------------------------


inline void bitpol_divrem(ulong a, ulong b, ulong &q, ulong &r)
// Set R, Q so that  A == Q * B + R.
// Must have B!=0.
// Equivalent to:   q=bitpol_div(a,b);  r=bitpol_rem(a,b);
{
//    if ( 0==b ) { r=a; q=0; return; }  // allow b==0

    const ulong db = highest_one_idx(b);
    q = 0;  // quotient
    ulong da;
    while ( db <= (da=highest_one_idx(a)) )
    {
        if ( 0==a )  break;  // needed because highest_one_idx(0)==highest_one_idx(1)
        a ^= (b<<(da-db));
        q ^= (1UL<<(da-db));
    }
    r = a;
}
// -------------------------

inline ulong bitpol_div_xp1(ulong a)
// Return power series  A / (x+1)
// If A is a multiple of x+1, then the returned value
//   is the exact division by x+1
// Function identical to inverse_rev_gray_code(a)
{
    a ^= a<<1;  // rev_gray ** 1
    a ^= a<<2;  // rev_gray ** 2
    a ^= a<<4;  // rev_gray ** 4
    a ^= a<<8;  // rev_gray ** 8
    a ^= a<<16;  // rev_gray ** 16
#if  BITS_PER_LONG >= 64
    a ^= a<<32;  // for 64bit words
#endif
    return a;
}
// -------------------------

inline ulong bitpol_div_x2p1(ulong a)
// Return power series  A / (x^2+1)
// If A is a multiple of x^2+1, then the returned value
//   is the exact division by x^2+1
{
    a ^= a<<2;  // rev_gray ** 2
    a ^= a<<4;  // rev_gray ** 4
    a ^= a<<8;  // rev_gray ** 8
    a ^= a<<16;  // rev_gray ** 16
#if  BITS_PER_LONG >= 64
    a ^= a<<32;  // for 64bit words
#endif
    return a;
}
// -------------------------



#undef MULT_UNROLL

#endif  // !defined HAVE_BITPOL_ARITH_H__
