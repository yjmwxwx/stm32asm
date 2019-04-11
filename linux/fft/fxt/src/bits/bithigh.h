#if !defined HAVE_BITHIGH_H__
#define      HAVE_BITHIGH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bithigh-edge.h"  // highest_one_01edge()

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitasm.h"
#include "bits/bitldeq.h"  // ld_neq()


static inline ulong highest_one(ulong x)
// Return word where only the highest bit in x is set.
// Return 0 if no bit is set.
{
#if defined  BITS_USE_ASM
    if ( 0==x )  return 0;
    x = asm_bsr(x);
    return  1UL << x;
#else
    x = highest_one_01edge(x);
    return  x ^ (x >> 1);
#endif  // BITS_USE_ASM
}
// -------------------------


static inline ulong highest_zero(ulong x)
// Return word where only the highest unset bit in x is set.
// Return 0 if all bits are set.
{
    return  highest_one( ~x );
}
// -------------------------

static inline ulong set_highest_zero(ulong x)
// Return word where the highest unset bit in x is set.
// Return ~0 for input == ~0.
{
//    if ( ~0UL==x )  return  ~0UL;
    return  x | highest_one( ~x );
}
// -------------------------

static inline ulong highest_one_idx(ulong x)
// Return index of highest bit set.
// Return 0 if no bit is set.
{
#if defined  BITS_USE_ASM
    return  asm_bsr(x);
#else  // BITS_USE_ASM

#if  BITS_PER_LONG == 64
#define MU0 0x5555555555555555UL  // MU0 == ((-1UL)/3UL) == ...01010101_2
#define MU1 0x3333333333333333UL  // MU1 == ((-1UL)/5UL)   == ...00110011_2
#define MU2 0x0f0f0f0f0f0f0f0fUL  // MU2 == ((-1UL)/17UL)  == ...00001111_2
#define MU3 0x00ff00ff00ff00ffUL  // MU3 == ((-1UL)/257UL)  == (8 ones)
#define MU4 0x0000ffff0000ffffUL  // MU4 == ((-1UL)/65537UL) == (16 ones)
#define MU5 0x00000000ffffffffUL  // MU5 == ((-1UL)/4294967297UL) == (32 ones)
#else
#define MU0 0x55555555UL  // MU0 == ((-1UL)/3UL) == ...01010101_2
#define MU1 0x33333333UL  // MU1 == ((-1UL)/5UL)   == ...00110011_2
#define MU2 0x0f0f0f0fUL  // MU2 == ((-1UL)/17UL)  == ...00001111_2
#define MU3 0x00ff00ffUL  // MU3 == ((-1UL)/257UL)  == (8 ones)
#define MU4 0x0000ffffUL  // MU4 == ((-1UL)/65537UL) == (16 ones)
#endif

    ulong r = (ulong)ld_neq(x, x & MU0)
        + ((ulong)ld_neq(x, x & MU1) << 1)
        + ((ulong)ld_neq(x, x & MU2) << 2)
        + ((ulong)ld_neq(x, x & MU3) << 3)
        + ((ulong)ld_neq(x, x & MU4) << 4);
#if  BITS_PER_LONG > 32
    r += ((ulong)ld_neq(x, x & MU5) << 5);
#endif
    return r;

#undef MU0
#undef MU1
#undef MU2
#undef MU3
#undef MU4
#undef MU5
#endif
}
// -------------------------


//static inline ulong highest_one_idx(ulong x)
//// Return index of highest bit set.
//// Return 0 if no bit is set.
//{
//#if defined  BITS_USE_ASM
//    return  asm_bsr(x);
//#else  // BITS_USE_ASM
//
//    if ( 0==x )  return  0;
//
////    // this version avoids all if-statements:
////    x = ( highest_one(x) << 1 ) - 1;
////    return  bit_count_01(x) - 1;
//
//    ulong r = 0;
//#if  BITS_PER_LONG >= 64
////    if ( x & (~0UL<<32) )  { x >>= 32;  r += 32; }
//    if ( x & 0xffffffff00000000UL )  { x >>= 32;  r += 32; }
//#endif
//    if ( x & 0xffff0000UL )  { x >>= 16;  r += 16; }
//    if ( x & 0x0000ff00UL )  { x >>=  8;  r +=  8; }
//    if ( x & 0x000000f0UL )  { x >>=  4;  r +=  4; }
//    if ( x & 0x0000000cUL )  { x >>=  2;  r +=  2; }
//    if ( x & 0x00000002UL )  {            r +=  1; }
//    return r;
//#endif  // BITS_USE_ASM
//}
//// -------------------------

static inline ulong highest_zero_idx(ulong x)
{
    return highest_one_idx( ~x );
}
// -------------------------


static inline ulong high_zeros(ulong x)
// Return word where all the (high end) zeros are set.
// e.g.:  00011001 --> 11100000
// Return 0 if highest bit is set:
//        11011001 --> 00000000
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
#if  BITS_PER_LONG >= 64
    x |= x >> 32;
#endif
    return  ~x;
}
// -------------------------


static inline ulong high_ones(ulong x)
// Return word where all the (high end) ones are set.
// e.g.  11001011 --> 11000000
// Return 0 if highest bit is zero:
//       01110110 --> 00000000
{
#if 1
    return  high_zeros( ~x );
#else
    // arithmetic shift may be expensive
    long y = (long)x;
    y &= y >> 1;
    y &= y >> 2;
    y &= y >> 4;
    y &= y >> 8;
    y &= y >> 16;
#if  BITS_PER_LONG >= 64
    y &= y >> 32;
#endif
    return  (ulong)y;
#endif
}
// -------------------------

#endif  // !defined HAVE_BITHIGH_H__
