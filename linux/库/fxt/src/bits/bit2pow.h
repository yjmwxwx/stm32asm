#if !defined HAVE_BIT2POW_H__
#define      HAVE_BIT2POW_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bithigh.h"
#include "bits/bitasm.h"


static inline ulong ld(ulong x)
// Return floor(log2(x)),
// i.e. return k so that 2^k <= x < 2^(k+1)
// If x==0, then 0 is returned (!)
{
//    ulong k = 0;
//    while ( x>>=1 )  { ++k; }
//    return k;

#if defined  BITS_USE_ASM
    return  asm_bsr(x);
#else
    return  highest_one_idx(x);
#endif  // BITS_USE_ASM
}
// -------------------------

//static inline int ild(ulong x)
//// Version returning type int
//{
//    return (int)ld(x);
//}
//// -------------------------


//static inline unsigned long long ld(unsigned long long x)
//// Return k so that 2^k <= x < 2^(k+1)
//// If x==0, then 0 is returned (!)
//{
//#if  BITS_PER_LONG == 64
//    return  highest_one_idx(x);
//#else
//    ulong  r = highest_one_idx( x>>32 );
//    if ( r )  return  r + 32;
//    else      return  highest_one_idx( x );
//#endif
//}
//// -------------------------


static inline bool is_pow_of_2(ulong x)
// Return whether x == 0(!) or x == 2**k
{
    return  !(x & (x-1));
//    return  ((x & -x) == x);
}
// -------------------------

static inline bool one_bit_q(ulong x)
// Return whether x \in {1,2,4,8,16,...}
{
    ulong m = x - 1;
    return  (((x^m)>>1) == m);
}
// -------------------------



static inline ulong next_pow_of_2(ulong x)
// Return x if x=2**k
// else return 2**ceil(log_2(x))
// Exception: returns 0 for x==0
{
    if ( is_pow_of_2(x) )  return x;

#if defined  BITS_USE_ASM
    ulong n = 1UL<<ld(x);  // n<x
    return  n << 1;

#else
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
#if BITS_PER_LONG == 64
    x |= x >> 32;
#endif
    return  x + 1;

#endif
}
// -------------------------


//static inline ulong next_exp_of_2(ulong x)
//// Return k if x=2**k else return k+1.
//// Exception: returns 1 for x==0
//{
//    ulong ldx = ld(x);
//    ulong n = 1UL<<ldx;  // n<=x
//    if ( n==x )  return  ldx;
//    else         return  ldx+1;
//}
//// -------------------------


static inline ulong next_exp_of_2(ulong x)
// Return k if x=2**k else return k+1.
// Exception: returns 0 for x==0.
{
    if ( x <= 1 )  return 0;
    return ld(x-1) + 1;
}
// -------------------------



#endif  // !defined HAVE_BIT2POW_H__
