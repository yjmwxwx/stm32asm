#if !defined HAVE_BITCOMBMINCHANGE_H__
#define      HAVE_BITCOMBMINCHANGE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitlow.h"
#include "bits/graycode.h"
#include "bits/revgraycode.h"
#include "bits/bitcount.h"
#include "bits/bit2pow.h"
#include "bits/bitsequency.h"


#if  0
static inline ulong igc_next_minchange_comb(ulong x)
// Return the inverse Gray code of the next combination in minimal-change order.
// Input must be the inverse Gray code of the current combination.
//.
// Original code by by Doug Moore.
// Only cosmetical changes by me.
{
    ulong g = rev_gray_code(x);
    ulong i = 2;
    ulong cb;  // ==candidate bits;
    do
    {
        ulong y = (x & ~(i-1)) + i;
        ulong j = lowest_one(y) << 1;
        ulong h = !!(y & j);
        cb = ((j-h) ^ g) & (j-i);
        i = j;
    }
    while ( 0==cb );

    return  x + lowest_one(cb);
}
// -------------------------
#else
static inline ulong igc_next_minchange_comb(ulong x)
// Alternative version, faster.
// Constant amortized time (CAT).
{
    ulong gx = gray_code( x );
#if 0
//    ulong w = lowest_one(gx) >> 1;
//    ulong i = ( w>1 ? w : 2 );
#else
    ulong i = 2;
#endif
    do
    {
        ulong y = x + i;
        i <<= 1;
        ulong gy = gray_code( y );
        ulong r = gx ^ gy;

        // Check that change consists of exactly one bit
        // of the new and one bit of the old pattern:
        if ( is_pow_of_2( r & gy ) && is_pow_of_2( r & gx ) )  return y;
        // is_pow_of_2(x):=((x & -x) == x)  returns 1 also for x==0.
        // But this cannot happen for both tests at the same time
    }
    while ( 1 );
    return  0;  // not reached
}
// -------------------------
#endif


static inline ulong igc_next_minchange_comb(ulong x, ulong k)
// Alternative version, uses the fact that the difference
// of two successive x is the smallest possible power of 2.
// Should be fast if the CPU has a bitcount instruction.
// k must be the bit-count of x
// Constant amortized time (CAT).
// Note: this version has 2 arguments.
{
    ulong y;
    ulong i = 2;
    do
    {
        y = x + i;
        i <<= 1;
    }
    while ( bit_count( gray_code(y) ) != k );
    return  y;
}
// -------------------------


static inline ulong igc_prev_minchange_comb(ulong x, ulong k)
// Return the inverse Gray code of the previous combination in minimal-change order.
// Input must be the inverse Gray code of the current combination.
// Constant amortized time (CAT).
// With input==first the output is the last for n=BITS_PER_LONG
{
    ulong y, i = 1;
    do
    {
        i <<= 1;
        y = x - i;
    }
    while ( bit_count( gray_code(y) ) != k );
    return  y;
}
// -------------------------

static inline ulong igc_last_comb(ulong k, ulong n)
// Return the (inverse Gray code of the) last combination
// as in igc_next_minchange_comb().
//
// Example (n=6)   c:=first_comb(n) == 111111
//
//   k:  f=first_seq(k)   c^(f>>1) == return
//   0:     ......        111111 (!) special case:  return 0==......
//   1:     .....1        111111
//   2:     ....1.        11111.
//   3:     ...1.1        1111.1
//   4:     ..1.1.        111.1.
//   5:     .1.1.1        11.1.1
//   6:     1.1.1.        1.1.1.
{
    if ( 0==k )  return 0;

#if ( BITS_PER_LONG < 64 )
    const ulong f = 0xaaaaaaaaUL >> (BITS_PER_LONG-k);  // == first_sequency(k);
#else
    const ulong f = 0xaaaaaaaaaaaaaaaaUL >> (BITS_PER_LONG-k);  // == first_sequency(k);
#endif
    const ulong c =  ~0UL >> (BITS_PER_LONG-n);  // == first_comb(n);
    return c ^ (f>>1);
    // =^=  (by Doug Moore)
//    return  ((1UL<<n) - 1) ^ (((1UL<<k) - 1) / 3);
}
// -------------------------


static inline ulong next_minchange_comb(ulong x, ulong last)
// Not efficient, just to explain the usage of igc_next_minchange_comb()
// Must have: last==igc_last_comb(k, n)
//
// Example with  k==3, n==5:
//      x       inverse_gray_code(x)
//    ..111       ..1.1 == first_sequency(k)
//    .11.1       .1..1
//    .111.       .1.11
//    .1.11       .11.1
//    11..1       1...1
//    11.1.       1..11
//    111..       1.111
//    1.1.1       11..1
//    1.11.       11.11
//    1..11       111.1 == igc_last_comb(k, n)
{
    x = inverse_gray_code(x);
    if ( x==last )  return 0;
    x = igc_next_minchange_comb(x);
    return  gray_code(x);
}
// -------------------------

#endif  // !defined HAVE_BITCOMBMINCHANGE_H__
