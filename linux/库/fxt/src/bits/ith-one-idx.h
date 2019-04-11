#if !defined  HAVE_ITH_ONE_IDX_H__
#define       HAVE_ITH_ONE_IDX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitsperlong.h"
#include "fxttypes.h"

//#include "jjassert.h"


static inline ulong ith_one_idx(ulong x, ulong i)
// Return index of the i-th set bit of x
// where 0 <= i < bit_count(x).
{
#if  BITS_PER_LONG == 32
    ulong x2 = x - ((x>>1) & 0x55555555UL);                     // 0-2 in 2 bits
    ulong x4 = ((x2>>2) & 0x33333333UL) + (x2 & 0x33333333UL);  // 0-4 in 4 bits
    ulong x8 = ((x4>>4) + x4) & 0x0f0f0f0fUL;                   // 0-8 in 8 bits
    ulong ct = (x8 * 0x01010101UL) >> 24;  // bit count
#else
    ulong x2 = x - ((x>>1) & 0x5555555555555555UL);                            // 0-2 in 2 bits
    ulong x4 = ((x2>>2) & 0x3333333333333333UL) + (x2 & 0x3333333333333333UL);  // 0-4 in 4 bits
    ulong x8 = ((x4>>4) + x4) & 0x0f0f0f0f0f0f0f0fUL;                          // 0-8 in 8 bits
    ulong ct = (x8 * 0x0101010101010101UL) >> 56;  // bit count
#endif

    ++i;
    if ( ct < i )  return ~0UL;  // less than i bits set

#if  BITS_PER_LONG == 32
    ulong x16 = (0x00ff00ffUL & x8) + (0x00ff00ffUL & (x8>> 8));  // 0-16 in 16 bits
//    ulong x32 = (0x0000ffffUL & x16) + (0x0000ffffUL & (x16>>16));  // 0-32 in 32 bits
//    jjassert( x32 == bit_count(x) );
#else
    ulong x16 = (0x00ff00ff00ff00ffUL & x8) + (0x00ff00ff00ff00ffUL & (x8>>8));     // 0-16 in 16 bits
    ulong x32 = (0x0000ffff0000ffffUL & x16) + (0x0000ffff0000ffffUL & (x16>>16));  // 0-32 in 32 bits

//    ulong x64 = (0x00000000ffffffffUL & x32) + (0x00000000ffffffffUL & (x32>>32));  // 0-64 in 64 bits
//    jjassert( x64 == bit_count(x) );
#endif

    ulong w, s = 0;

#if  BITS_PER_LONG > 32
    w = x32 & 0xffffffffUL;
    if ( w < i )  { s += 32;  i -= w; }

    x16 >>= s;
#endif
    w = x16 & 0xffff;
    if ( w < i )  { s += 16;  i -= w; }

    x8 >>= s;
    w = x8 & 0xff;
    if ( w < i )  { s += 8;  i -= w; }

    x4 >>= s;
    w = x4 & 0xf;
    if ( w < i )  { s += 4;  i -= w; }

    x2 >>= s;
    w = x2 & 3;
    if ( w < i )  { s += 2;  i -= w; }

#if 1
    x >>= s;
    s += ( (x&1) != i );
#else
    x >>= s;
    w = x & 1;
    if ( w < i )  { s += 1;  i -= w; }
#endif

    return s;
}
// -------------------------


//static inline ulong ith_one_idx(ulong x, ulong i)
//// Return index of the i-th set bit of x
//// where 0 <= i < bit_count(x).
//{
//#if  BITS_PER_LONG == 32
//    ulong y = x - ((x>>1) & 0x55555555UL);             // 0-2 in 2 bits
//    y = ((y>>2) & 0x33333333UL) + (y & 0x33333333UL);  // 0-4 in 4 bits
//    y = ((y>>4) + y) & 0x0f0f0f0fUL;                   // 0-8 in 8 bits
//    ulong ct = (y*0x01010101UL) >> 24;  // bit count
//#else
//    ulong y = x - ((x>>1) & 0x5555555555555555UL);                     // 0-2 in 2 bits
//    y = ((y>>2) & 0x3333333333333333UL) + (y & 0x3333333333333333UL);  // 0-4 in 4 bits
//    y = ((y>>4) + y) & 0x0f0f0f0f0f0f0f0fUL;                           // 0-8 in 8 bits
//    ulong ct = (y * 0x0101010101010101UL) >> 56;  // bit count
//#endif
//
//    if ( ct <= i )  return ~0UL;  // less than i bits set
//
//    ulong s = 0;
//    while ( i >= (y & 0xff) )  // scan over bytes
//    {
//        i -= (y & 0xff);
//        y >>= 8;
//        s += 8;
//    }
//    x >>= s;
//
//    --s;  ++i;  // allow test for zero
//    while ( i )  // scan over bits
//    {
//        i -=  x & 1;
//        x >>= 1;
//        ++s;
//    }
//
//    return s;
//}
//// -------------------------


#endif  // !defined HAVE_ITH_ONE_IDX_H__
