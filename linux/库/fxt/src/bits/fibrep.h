#if !defined  HAVE_FIBREP_H__
#define       HAVE_FIBREP_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
//#include "bits/bitlow.h"  // lowest_one_idx()


static inline ulong bin2fibrep(ulong b)
// Return Fibonacci representation of b
// Limitation: the first Fibonacci number greater
//  than b must be representable as ulong.
// 32 bit:  b < 2971215073=F(47) [F(48)=4807526976 > 2^32]
// 64 bit:  b < 12200160415121876738=F(93) [F(94) > 2^64]
{
    ulong f0=1, f1=1, s=1;
    while ( f1<=b )  { ulong t = f0+f1;  f0=f1;  f1=t;  s<<=1; }
    ulong f = 0;
    while ( b )
    {
        s >>= 1;
        if ( b>=f0 )  { b -= f0;  f^=s; }
        { ulong t = f1-f0;  f1=f0;  f0=t; }
    }
    return f;
}
// -------------------------

static inline ulong fibrep2bin(ulong f)
// Return binary representation of f
// Inverse of bin2fibrep().
{
    ulong f0=1, f1=1;
    ulong b = 0;
    while ( f )
    {
        if ( f&1 )   b += f1;
        { ulong t=f0+f1;  f0=f1;  f1=t; }
        f >>= 1;
    }
    return b;
}
// -------------------------

static inline ulong next_fibrep(ulong x)
// With x the Fibonacci representation of n
// return Fibonacci representation of n+1.
{
    // 2 examples:         //  ex. 1             //  ex.2
    //                     // x == [*]0 010101   // x == [*]0 01010
    ulong y = x | (x>>1);  // y == [*]? 011111   // y == [*]? 01111
    ulong z = y + 1;       // z == [*]? 100000   // z == [*]? 10000
    z = z & -z;            // z == [0]0 100000   // z == [0]0 10000
    x ^= z;                // x == [*]0 110101   // x == [*]0 11010
    x &= ~(z-1);           // x == [*]0 100000   // x == [*]0 10000

    return x;
}
// -------------------------

static inline ulong prev_fibrep(ulong x)
// With x the Fibonacci representation of n
// return Fibonacci representation of n-1.
{
#if 1  // VERSION 3:  (DEFAULT, fastest)
    // 2 examples:         //  ex. 1             //  ex.2
    //                     // x == [*]0 100000   // x == [*]0 10000
    ulong y = x & -x;      // y == [0]0 100000   // y == [0]0 10000
    x ^= y;                // x == [*]0 000000   // x == [*]0 00000
#if BITS_PER_LONG == 64
    ulong m = 0x5555555555555555UL;  // m == ...01010101
#else
    ulong m = 0x55555555UL;  // m == ...01010101
#endif
    if ( m & y )  m >>= 1;  // m == ...01010101   // m == ...0101010
    m &= (y-1);            // m == [0]0 010101   // m == [0]0 01010
    x ^= m;                // x == [*]0 010101   // x == [*]0 01010
    return x;
#endif  // ver 3

#if 0  // VERSION 2:
    //                        x == [*]0 100000
    ulong y = x & -x;      // y == [0]0 100000
    x ^= y;                // x == [*]0 000000
    y >>= 1;               // y == [0]0 010000
    y |= (y>>2);           // y == [0]0 010100
    y |= (y>>4);           // y == [0]0 010101
    y |= (y>>8);
    y |= (y>>16);
#if BITS_PER_LONG == 64
    y |= (y>>32);
#endif
    x ^= y;                // x == [*]0 010101
    return x;
#endif  // ver 2

#if 0  // VERSION 1:
//    if ( x&1 )  return  x ^ 1UL;
    ulong i = lowest_one_idx(x);
    x ^= (1UL<<i);
    ++i;
#if BITS_PER_LONG == 64
    x ^= (0x5555555555555555UL >> (BITS_PER_LONG-i));
#else
    x ^= (0x55555555UL >> (BITS_PER_LONG-i));
#endif
    return x;
#endif  // ver 1
}
// -------------------------

static inline bool is_fibrep(ulong f)
// Return whether f is a valid Fibonacci representation
// i.e. whether it does not contain two adjacent ones
{
    return  ( 0==(f&(f>>1)) );
}
// -------------------------


#endif  // !defined HAVE_FIBREP_H__
