#if !defined HAVE_BITCOMBCOLEX_H__
#define      HAVE_BITCOMBCOLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong first_comb(ulong k)
// Return the first combination of (i.e. smallest word with) k bits,
// i.e.  00..001111..1 (k low bits set)
// Must have:  0 <= k <= BITS_PER_LONG
{
//    ulong x = ~0UL;
//    if ( BITS_PER_LONG != k )  x = ~(x<<k);

    if ( k==0 )  return 0;  // shift with BITS_PER_LONG is undefined
    return ~0UL >> ( BITS_PER_LONG - k );
}
// -------------------------


static inline ulong last_comb(ulong k, ulong n=BITS_PER_LONG)
// Return the last combination of (biggest n-bit word with) k bits
// i.e.  1111..100..00 (k high bits set)
// Must have:  0 <= k <= n <= BITS_PER_LONG
{
//    if ( BITS_PER_LONG == k )  return  ~0UL;
//    else return  ((1UL<<k)-1) << (n - k);
    return  first_comb(k) << (n - k);
}
// -------------------------

#define  COLEX_COMB_VERSION  0  // 0 (default) or 1

#if  COLEX_COMB_VERSION == 0
static inline ulong next_colex_comb(ulong x)
// Return smallest integer greater than x with the same number of bits set.
//
// colex order (5 over 3):
//   set        word    set reversed (sorted!)
//  0  1  2    ..111    2  1  0
//  0  1  3    .1.11    3  1  0
//  0  2  3    .11.1    3  2  0
//  1  2  3    .111.    3  2  1
//  0  1  4    1..11    4  1  0
//  0  2  4    1.1.1    4  2  0
//  1  2  4    1.11.    4  2  1
//  0  3  4    11..1    4  3  0
//  1  3  4    11.1.    4  3  1
//  2  3  4    111..    4  3  2
//
//  Examples:
//    000001 -> 000010 -> 000100 -> 001000 -> 010000 -> 100000
//    000011 -> 000101 -> 000110 -> 001001 -> 001010 -> 001100 -> 010001 -> ...
//    000111 -> 001011 -> 001101 -> 001110 -> 010011 -> 010101 -> 010110 -> ...
//
//  Special cases:
//    0 -> 0
//    all bits on the high side (i.e. last combination) -> 0
//.
// based on code by Doug Moore / Glenn Rhoads
// note: might want to use bitscan near end
{
    ulong r = x & -x;       // lowest set bit
    x += r;                 // replace lowest block by a one left to it

    if ( 0==x )  return 0;  // input was last combination

    ulong z = x & -x;       // first zero beyond lowest block
    z -= r;                 // lowest block  (cf. lowest_block())

    while ( 0==(z&1) )  { z >>= 1; }  // move block to low end of word
    return  x | (z>>1);     // need one bit less of low block
}
// -------------------------

#else  //   COLEX_COMB_VERSION
// Alternative implementation:

static inline ulong next_colex_comb(ulong x)
// Return smallest integer greater than x with the same number of bits set.
//
//  Example: (the bits marked by '.' remain fixed)
//    x         = ....01111100000000
//    z         = 000000000100000000   (the lowest set bit)
//    v=x+z     = ....10000000000000   (first zero beyond burst of ones)
//    v^x       = 000011111100000000
//    v^x/z     = 000000000000111111
//    v^x/z>>2  = 000000000000001111
//    next      = ....10000000001111
//.
//  Code based on code taken from Torsten Sillke's bitmani.h:
//  http://www.mathematik.uni-bielefeld.de/~sillke/ALGORITHMS/
//  The algorithm can be found in hakmem, shortcut by me.
{
    // begin shortcut
    if ( x & 1 )  // easy case
    {
        ulong z = ~x;  z &= -z;   // lowest unset bit
        if ( 0==z )  return  0;   // x was == 0xffffffff
        x += (z>>1);              // same as:  x ^= z;  x ^= (z>>1);
        return  x;
    }
    // end shortcut

    ulong z = x & -x;  // lowest set bit
    ulong v = x + z;   // zero beyond burst

    if ( v )  v += ((v^x)/z >> 2);  // note: could use bitscan & shift

    return  v;  // ==0 if input was the last combination
}
// -------------------------

#endif  //   COLEX_COMB_VERSION
#undef  COLEX_COMB_VERSION


static inline ulong prev_colex_comb(ulong x)
// Inverse of next_colex_comb()
{
#if 1
    x = next_colex_comb( ~x );
    if ( 0!=x )  x = ~x;
    return  x;

#else
    if ( 0==(x & 1) )  // easy case
    {
        ulong b = x & -x;  // lowest set bit
        x -= (b>>1);  // move right
    }
    else
    {
        ulong k = ~x;  k &= -k;  --k;  // low block of set bits
        x ^= k;  // remove low block
        if ( x==0 )  return 0;  // last combination (i.e. first in colex order)
        ulong b = x & -x;  // lowest set bit
        x -= (b>>1);  // move right

        do  { k <<= 1; }  while ( 0==(k&x) );  // join block
        x ^= (k>>1);
    }
    return x;
#endif
}
// -------------------------




#endif  //  !defined HAVE_BITCOMBCOLEX_H__
