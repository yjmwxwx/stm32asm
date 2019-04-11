#if !defined HAVE_BITSWAP_H__
#define      HAVE_BITSWAP_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong bit_swap_01(ulong a, ulong k1, ulong k2)
// Return a with bits at positions [k1] and [k2] swapped.
// Bits must have different values (!)
// (i.e. one is zero, the other one)
// k1==k2 is allowed (a is unchanged then)
{
    return  a ^ ( (1UL<<k1) ^ (1UL<<k2) );
}
// -------------------------


static inline ulong bit_swap(ulong a, ulong k1, ulong k2)
// Return a with bits at positions [k1] and [k2] swapped.
// k1==k2 is allowed (a is unchanged then)
{
#if 1  // Branch free:
    ulong x = ((a>>k1) ^ (a>>k2)) & 1;  // one if bits differ
    a ^= (x<<k2);  // change if bits differ
    a ^= (x<<k1);  // change if bits differ
#else
    ulong x = (a >> k1) ^ (a >> k2);
    // something to do if bit[k1]!=bit[k2]:
    if ( 0!=(x&1) )  a = bit_swap_01(a, k1, k2);
#endif
    return  a;
}
// -------------------------


static inline ulong bit_swap_1(ulong x)
// Return x with neighbor bits swapped.
{
#if  BITS_PER_LONG == 32
    ulong m = 0x55555555UL;
#else
#if  BITS_PER_LONG == 64
    ulong m = 0x5555555555555555UL;
#endif
#endif
    return  ((x & m) << 1) | ((x & (~m)) >> 1);
//    return  ( (x>>1) & m ) | ( (x & m) << 1 );
}
// -------------------------

static inline ulong bit_swap_2(ulong x)
// Return x with groups of 2 bits swapped.
{
#if  BITS_PER_LONG == 32
    ulong m = 0x33333333UL;
#else
#if  BITS_PER_LONG == 64
    ulong m = 0x3333333333333333UL;
#endif
#endif
    return  ((x & m) << 2) | ((x & (~m)) >> 2);
}
// -------------------------

static inline ulong bit_swap_4(ulong x)
// Return x with groups of 4 bits swapped.
{
#if  BITS_PER_LONG == 32
    ulong m = 0x0f0f0f0fUL;
#else
#if  BITS_PER_LONG == 64
    ulong m = 0x0f0f0f0f0f0f0f0fUL;
#endif
#endif
    return  ((x & m) << 4) | ((x & (~m)) >> 4);
}
// -------------------------

static inline ulong bit_swap_8(ulong x)
// Return x with groups of 8 bits swapped.
{
#if  BITS_PER_LONG == 32
    ulong m = 0x00ff00ffUL;
#else
#if  BITS_PER_LONG == 64
    ulong m = 0x00ff00ff00ff00ffUL;
#endif
#endif
    return  ((x & m) << 8) | ((x & (~m)) >> 8);
}
// -------------------------


static inline ulong bit_swap_16(ulong x)
// Return x with groups of 16 bits swapped.
//
// For 32 bit words this is identical to either of
//   rotate_left(x,16) or rotate_right(x,16)
{
#if  BITS_PER_LONG == 32
//    ulong m = 0x0000ffffUL;
    // following line is optimized to 'roll $16,%eax' by gcc:
//    return  ((x & m) << 16) | ((x & (m<<16)) >> 16);
    return (x << 16) | (x >> 16);  // most simple

#else
#if  BITS_PER_LONG == 64
    ulong m = 0x0000ffff0000ffffUL;
    return  ((x & m) << 16) | ((x & (~m)) >> 16);
#endif
#endif
}
// -------------------------


#if  BITS_PER_LONG == 64
static inline ulong bit_swap_32(ulong x)
// Return x with groups of 32 bits swapped.
{
//    ulong m = 0x00000000ffffffffUL;
    // following line is optimized to 'rolq $32, %rdi' by gcc:
//    return  ((x & m) << 32) | ((x & (m<<32)) >> 32);
    return (x << 32) | (x >> 32);  // most simple

//    return  ((x & m) << 32) | ((x & (~m)) >> 32);
}
// -------------------------
#endif


#endif  // !defined HAVE_BITSWAP_H__
