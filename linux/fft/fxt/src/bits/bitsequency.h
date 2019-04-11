#if !defined HAVE_BITSEQUENCY_H__
#define      HAVE_BITSEQUENCY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/graycode.h"
#include "bits/bitcount.h"
#include "bits/bitcombcolex.h"
#include "fxttypes.h"
#include "bits/bitsperlong.h"

static inline ulong bit_sequency(ulong x)
// Return the number of zero-one (or one-zero)
//  transitions (sequency) of x.
{
    return bit_count( gray_code(x) );
}
// -------------------------


static inline ulong first_sequency(ulong k)
// Return the first (i.e. smallest) word with sequency k,
// e.g.  00..00010101010 (seq 8)
// e.g.  00..00101010101 (seq 9)
// Must have:  0 <= k <= BITS_PER_LONG
{
    if ( k==0 )  return 0;

#if ( BITS_PER_LONG < 64 )
    const ulong m = 0xaaaaaaaaUL;
#else
    const ulong m = 0xaaaaaaaaaaaaaaaaUL;
#endif
    return  m >> (BITS_PER_LONG-k);

    // =^=
//    return inverse_gray_code( first_comb(k) );

    // =^= (by Doug Moore)
//    ulong s = ((1UL<<k) - 1);
//    return  s ^ (s / 3);
}
// -------------------------

static inline ulong last_sequency(ulong k, ulong n=BITS_PER_LONG)
// Return the last (i.e. biggest) word with sequency k.
{
    ulong x = inverse_gray_code( last_comb(k, n) );
    return  x;
}
// -------------------------


static inline ulong next_sequency(ulong x)
// Return next word with the same number
// of zero-one transitions (sequency) as x.
// The value of the lowest bit is conserved.
//
// Zero is returned when there is no further sequence.
//
// e.g.:
//  ...1.1.1 ->
//  ..11.1.1 ->
//  ..1..1.1 ->
//  ..1.11.1 ->
//  ..1.1..1 ->
//  ..1.1.11 ->
//  .111.1.1 ->
//  .11..1.1 ->
//  .11.11.1 ->
//  .11.1..1 ->
//  .11.1.11 -> ...
//
{
    x = gray_code(x);
    x = next_colex_comb(x);
    x = inverse_gray_code(x);
    return x;
}
// -------------------------

static inline ulong prev_sequency(ulong x)
{
    x = gray_code(x);
    x = prev_colex_comb(x);
    x = inverse_gray_code(x);
    return x;
}
// -------------------------

static inline ulong complement_sequency(ulong x)
// Return word whose sequency is BITS_PER_LONG - s
// where s is the sequency of x
{
#if ( BITS_PER_LONG < 64 )
    return x ^ 0xaaaaaaaaUL;
#else
    return x ^ 0xaaaaaaaaaaaaaaaaUL;
#endif
}
// -------------------------


#endif  // !defined HAVE_BITSEQUENCY_H__
