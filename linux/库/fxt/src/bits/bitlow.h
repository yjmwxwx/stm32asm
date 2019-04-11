#if !defined HAVE_BITLOW_H__
#define      HAVE_BITLOW_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitasm.h"


static inline ulong lowest_one_idx(ulong x)
// Return index of lowest bit set.
// Bit index ranges from zero to BITS_PER_LONG-1.
// Examples:
//    ***1 --> 0
//    **10 --> 1
//    *100 --> 2
// Return 0 (also) if no bit is set.
{
#if defined  BITS_USE_ASM
    return  asm_bsf(x);
#else  // BITS_USE_ASM

//    if ( 1>=x )  return  x-1;  // 0 if 1, ~0 if 0
//    if ( 0==x )  return  0;

    ulong r = 0;
    x &= -x;  // isolate lowest bit

#if 1  // branchless version
#if  BITS_PER_LONG >= 64
    r |= ( (x & 0xffffffff00000000UL) != 0 );  r <<= 1;
    r |= ( (x & 0xffff0000ffff0000UL) != 0 );  r <<= 1;
    r |= ( (x & 0xff00ff00ff00ff00UL) != 0 );  r <<= 1;
    r |= ( (x & 0xf0f0f0f0f0f0f0f0UL) != 0 );  r <<= 1;
    r |= ( (x & 0xccccccccccccccccUL) != 0 );  r <<= 1;
    r |= ( (x & 0xaaaaaaaaaaaaaaaaUL) != 0 );
#else  // BITS_PER_LONG >= 64
    r |= ( (x & 0xffff0000UL) != 0 );  r <<= 1;
    r |= ( (x & 0xff00ff00UL) != 0 );  r <<= 1;
    r |= ( (x & 0xf0f0f0f0UL) != 0 );  r <<= 1;
    r |= ( (x & 0xccccccccUL) != 0 );  r <<= 1;
    r |= ( (x & 0xaaaaaaaaUL) != 0 );
#endif  // BITS_PER_LONG >= 64

#else // version by Nathan Bullock

#if  BITS_PER_LONG >= 64
    if ( x & 0xffffffff00000000UL )  r += 32;
    if ( x & 0xffff0000ffff0000UL )  r += 16;
    if ( x & 0xff00ff00ff00ff00UL )  r += 8;
    if ( x & 0xf0f0f0f0f0f0f0f0UL )  r += 4;
    if ( x & 0xccccccccccccccccUL )  r += 2;
    if ( x & 0xaaaaaaaaaaaaaaaaUL )  r += 1;
#else  // BITS_PER_LONG >= 64
    if ( x & 0xffff0000UL )  r += 16;
    if ( x & 0xff00ff00UL )  r += 8;
    if ( x & 0xf0f0f0f0UL )  r += 4;
    if ( x & 0xccccccccUL )  r += 2;
    if ( x & 0xaaaaaaaaUL )  r += 1;
#endif  // BITS_PER_LONG >= 64
#endif

    return r;
#endif  // BITS_USE_ASM
}
// -------------------------


static inline ulong lowest_one_idx_parity(ulong x)
// Return the parity of the index of the lowest set bit.
// Return zero with x=0.
// Sequence for x>=0 (OEIS sequence A096268):
// 0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,...
{
    x &= -x;  // isolate lowest bit
#if BITS_PER_LONG == 64
    return  0 != (x & 0xaaaaaaaaaaaaaaaaUL);
#else
    return  0 != (x & 0xaaaaaaaaUL);
#endif
}
// -------------------------


static inline ulong lowest_one(ulong x)
// Return word where only the lowest set bit in x is set.
// Return 0 if no bit is set.
{
//    if ( 0==x )  return 0;
//    return  ((x^(x-1)) >> 1) + 1;

//    return  (x & (x-1)) ^ x;

    return  x & -x;  // use: -x == ~x + 1
}
// -------------------------

static inline ulong lowest_zero(ulong x)
// Return word where only the lowest unset bit in x is set.
// Return 0 if all bits are set.
{
//    return  (x ^ (x+1)) & ~x;
//    return  ((x ^ (x+1)) >> 1 ) + 1;
//    return (x+1) & ~x;

    x = ~x;
    return  x & -x;
}
// -------------------------


static inline ulong lowest_block(ulong x)
// Isolate lowest block of ones.
{
#if 0  // jj's version, printed in the fxtbook (incorrect for words 1+0*)

    ulong l = x & -x;  // lowest bit
    ulong y = x + l;
    x ^= y;
    return  x & (x>>1);

#else  // Mike Engber's (correct) versions

#  if 1

    // Example:
    // x   = *****011100
    // l   = 00000000100
    // y   = *****100000
    // x^y = 00000111100
    // ret = 00000011100

    ulong l = x & -x;  // lowest bit
    ulong y = x + l;
    y ^= x;
    return  y & x;

#  else

    ulong l = x & -x;       // low bit mask
    ulong c = (l + x) & x;  // low bit run cleared
    return c ^ x;           // low bit run mask

#  endif
#endif
}
// -------------------------

static inline ulong clear_lowest_one(ulong x)
// Return word where the lowest bit set in x is cleared.
// Return 0 for input == 0.
{
    return  x & (x-1);
}
// -------------------------

static inline ulong set_lowest_zero(ulong x)
// Return word where the lowest unset bit in x is set.
// Return ~0 for input == ~0.
{
    return  x | (x+1);
}
// -------------------------


static inline ulong low_ones(ulong x)
// Return word where all the (low end) ones are set.
// Example:  01011011 --> 00000011
// Return 0 if lowest bit is zero:
//       10110110 --> 0
{
    x = ~x;
    x &= -x;
    --x;
    return x;

//    if ( ~0UL==x )  return ~0UL;
//    return (((x+1)^x) >> 1);
}
// -------------------------

static inline ulong low_zeros(ulong x)
// Return word where all the (low end) zeros are set.
// Example:  01011000 --> 00000111
// Return 0 if all bits are set.
{
    x &= -x;
    --x;
    return x;

//    if ( 0==x )  return ~0UL;
//    return (((x-1)^x) >> 1);
}
// -------------------------


static inline ulong low_match(ulong x, ulong y)
// Return word that contains all bits at the low end where x and y match.
// If x = *0W and y = *1W, then 00W is returned.
{
    x ^= y;   // bit-wise difference
    x &= -x;  // lowest bit that differs in both words
    x -= 1;   // mask that covers equal bits at low end
    x &= y;   // isolate matching bits
    return x;
}
// -------------------------


#endif  // !defined HAVE_BITLOW_H__
