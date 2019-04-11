#if !defined HAVE_BITCOUNT_H__
#define      HAVE_BITCOUNT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitasm.h"


static inline ulong bit_count(ulong x)
// Return number of set bits.
// The sequence of values returned for x = 0, 1, 2, 3, ... is
// 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, ...
// (OEIS sequence A000120).
{
#ifdef HAVE_AMD64_POPCNT  // currently not auto-detected

    return  asm_bit_count(x);

#else  // HAVE_AMD64_POPCNT


#if  BITS_PER_LONG == 32
//    // VERSION 1:
//    x = (0x55555555UL & x) + (0x55555555UL & (x>> 1));  // 0-2 in 2 bits
//    x = (0x33333333UL & x) + (0x33333333UL & (x>> 2));  // 0-4 in 4 bits
//    x = (0x0f0f0f0fUL & x) + (0x0f0f0f0fUL & (x>> 4));  // 0-8 in 8 bits
//    x = (0x00ff00ffUL & x) + (0x00ff00ffUL & (x>> 8));  // 0-16 in 16 bits
//    x = (0x0000ffffUL & x) + (0x0000ffffUL & (x>>16));  // 0-32 in 32 bits
//    return x;

//    // VERSION 2:
//    x  = ((x>>1) & 0x55555555UL) + (x & 0x55555555UL);  // 0-2 in 2 bits
//    x  = ((x>>2) & 0x33333333UL) + (x & 0x33333333UL);  // 0-4 in 4 bits
//    x  = ((x>>4) + x) & 0x0f0f0f0fUL;                   // 0-8 in 8 bits
//    x +=  x>> 8;                                        // 0-16 in 8 bits
//    x +=  x>>16;                                        // 0-32 in 8 bits
//    return  x & 0xff;

    // VERSION 3:
    x -=  (x>>1) & 0x55555555UL;                        // 0-2 in 2 bits
    x  = ((x>>2) & 0x33333333UL) + (x & 0x33333333UL);  // 0-4 in 4 bits
    x  = ((x>>4) + x) & 0x0f0f0f0fUL;                   // 0-8 in 8 bits
    x *= 0x01010101UL;
    return  x>>24;

#endif

#if  BITS_PER_LONG == 64
//    // VERSION 1:
//    x = (0x5555555555555555UL & x) + (0x5555555555555555UL & (x>> 1));  // 0-2 in 2 bits
//    x = (0x3333333333333333UL & x) + (0x3333333333333333UL & (x>> 2));  // 0-4 in 4 bits
//    x = (0x0f0f0f0f0f0f0f0fUL & x) + (0x0f0f0f0f0f0f0f0fUL & (x>> 4));  // 0-8 in 8 bits
//    x = (0x00ff00ff00ff00ffUL & x) + (0x00ff00ff00ff00ffUL & (x>> 8));  // 0-16 in 16 bits
//    x = (0x0000ffff0000ffffUL & x) + (0x0000ffff0000ffffUL & (x>>16));  // 0-32 in 32 bits
//    x = (0x00000000ffffffffUL & x) + (0x00000000ffffffffUL & (x>>32));  // 0-64 in 64 bits
//    return x;

//    // VERSION 2:
//    x = ((x>>1) & 0x5555555555555555UL) + (x & 0x5555555555555555UL);  // 0-2 in 2 bits
//    x = ((x>>2) & 0x3333333333333333UL) + (x & 0x3333333333333333UL);  // 0-4 in 4 bits
//    x = ((x>>4) + x) & 0x0f0f0f0f0f0f0f0fUL;                           // 0-8 in 8 bits
//    x +=  x>> 8;                                                       // 0-16 in 8 bits
//    x +=  x>>16;                                                       // 0-32 in 8 bits
//    x +=  x>>32;                                                       // 0-64 in 8 bits
//    return  x & 0xff;

    // VERSION 3:
    x -=  (x>>1) & 0x5555555555555555UL;                                // 0-2 in 2 bits
    x  = ((x>>2) & 0x3333333333333333UL) + (x & 0x3333333333333333UL);  // 0-4 in 4 bits
    x  = ((x>>4) + x) & 0x0f0f0f0f0f0f0f0fUL;                           // 0-8 in 8 bits
    x *= 0x0101010101010101UL;
    return  x>>56;

#endif
#endif  // HAVE_AMD64_POPCNT
}
// -------------------------

static inline ulong bit_count_15(ulong x)
// Return number of set bits, must have at most 15 set bits.
{
#if  BITS_PER_LONG == 32
    x -=  (x>>1) & 0x55555555UL;                        // 0-2 in 2 bits
    x  = ((x>>2) & 0x33333333UL) + (x & 0x33333333UL);  // 0-4 in 4 bits
    x *= 0x11111111UL;
    return  x>>28;
#endif

#if  BITS_PER_LONG == 64
    x -=  (x>>1) & 0x5555555555555555UL;                                // 0-2 in 2 bits
    x  = ((x>>2) & 0x3333333333333333UL) + (x & 0x3333333333333333UL);  // 0-4 in 4 bits
    x *= 0x1111111111111111UL;
    return  x>>60;
#endif
}
// -------------------------

static inline ulong bit_count_3(ulong x)
// Return number of set bits, must have at most 3 set bits.
{
#if  BITS_PER_LONG == 32
    x -=  (x>>1) & 0x55555555UL;  // 0-2 in 2 bits
    x *= 0x55555555UL;
    return  x>>30;
#endif

#if  BITS_PER_LONG == 64
    x -=  (x>>1) & 0x5555555555555555UL;  // 0-2 in 2 bits
    x *= 0x5555555555555555UL;
    return  x>>62;
#endif
}
// -------------------------


static inline int bit_count_cmp(const ulong &a, const ulong &b)
// Compare bit counts of a and b.
{
    ulong ca = bit_count(a);
    ulong cb = bit_count(b);
    return  ( ca==cb ? 0 : (ca>cb ? +1 : -1) );
}
// -------------------------


static inline ulong bit_count_sparse(ulong x)
// Return number of bits set.
{
#if 0
    // The loop will execute once for each bit of x set:
    ulong n = 0;
    while ( x )  { ++n;  x &= (x-1); }
    return  n;

#else
    // The loop will execute ceil(c/4) if c bits of x are set:
    ulong n = 0;
    do
    {
        n += (x!=0);  x &= (x-1);
        n += (x!=0);  x &= (x-1);
        n += (x!=0);  x &= (x-1);
        n += (x!=0);  x &= (x-1);
    }
    while ( x );
    return  n;

#endif
}
// -------------------------

static inline ulong bit_count_dense(ulong x)
// Return number of bits set.
// The loop (of bit_count_sparse()) will execute once for
//   each unset bit (i.e. zero) of x.
{
    return  BITS_PER_LONG - bit_count_sparse( ~x );
}
// -------------------------


static inline ulong bit_block_count(ulong x)
// Return number of bit blocks.
// E.g.:
// ..1..11111...111.  -> 3
// ...1..11111...111  -> 3
// ......1.....1.1..  -> 3
// .........111.1111  -> 2
{
//    return  bit_count(gray_code(x))/2 + (x & 1);
    return  (x & 1) + bit_count( (x^(x>>1)) ) / 2;
}
// -------------------------


static inline ulong bit_block_ge2_count(ulong x)
// Return number of bit blocks with at least 2 bits.
// E.g.:
// ..1..11111...111.  -> 2
// ...1..11111...111  -> 2
// ......1.....1.1..  -> 0
// .........111.1111  -> 2
{
    // return bit_block_count( interior_ones(x) );
    return  bit_block_count( x & ( (x<<1) & (x>>1) ) );
}
// -------------------------


static inline ulong bit_count_01(ulong x)
// Return number of bits in a word
// for words of the special form 00...0001...11
{
#if defined  BITS_USE_ASM
    if ( 1>=x )  return x;
    x = asm_bsr(x);
    return  x + 1;
#else  // BITS_USE_ASM

    ulong ct = 0;
    ulong a;

#if  BITS_PER_LONG == 64
    a = (x & (1UL<<32)) >> (32-5);  // test bit 32
    x >>= a;  ct += a;
#endif
    a = (x & (1UL<<16)) >> (16-4);  // test bit 16
    x >>= a;  ct += a;

    a = (x & (1UL<<8)) >> (8-3);  // test bit 8
    x >>= a;  ct += a;

    a = (x & (1UL<<4)) >> (4-2);  // test bit 4
    x >>= a;  ct += a;

    a = (x & (1UL<<2)) >> (2-1);  // test bit 2
    x >>= a;  ct += a;

    a = (x & (1UL<<1)) >> (1-0);  // test bit 1
    x >>= a;  ct += a;

    ct += x & 1;  // test bit 0

    return ct;

#endif  // BITS_USE_ASM
}
// -------------------------

// bits/bitcount-v.cc:
ulong bit_count_v(const ulong *x, ulong n);


#endif  // !defined HAVE_BITCOUNT_H__
