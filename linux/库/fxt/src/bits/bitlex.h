#if !defined HAVE_BITLEX_H__
#define      HAVE_BITLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitcount.h"
#include "bits/bithigh.h"


static inline ulong next_lexrev(ulong x)
// Return next word in subset-lexrev order.
// Start with a one-bit word at position n-1 to
// generate 2**n subsets of length n.
// E.g., for n==4 the subsets are
//     word   subset of {0,1,2,3}
//     1...   {0}
//     11..   {0, 1}
//     111.   {0, 1, 2}
//     1111   {0, 1, 2, 3}
//     11.1   {0, 1, 3}
//     1.1.   {0, 2}
//     1.11   {0, 2, 3}
//     1..1   {0, 3}
//     .1..   {1}
//     .11.   {1, 2}
//     .111   {1, 2, 3}
//     .1.1   {1, 3}
//     ..1.   {2}
//     ..11   {2, 3}
//     ...1   {3}
//     ....   {}
// Note (1): the first element of the subset corresponds
// to the highest set bit.  When interpreting the binary
// words via "bit(n)==element n" (as usual), the order
// would be:
//     1...           { 3 }
//     11..        { 2, 3 }
//     111.     { 1, 2, 3 }
//     1111  { 0, 1, 2, 3 }
//     11.1     { 0, 2, 3 }
//     1.1.        { 1, 3 }
//     1.11     { 0, 1, 3 }
//     1..1        { 0, 3 }
//     .1..           { 2 }
//     .11.        { 1, 2 }
//     .111     { 0, 1, 2 }
//     .1.1        { 0, 2 }
//     ..1.           { 1 }
//     ..11        { 0, 1 }
//     ...1           { 0 }
// Note (2): the lex order for the delta sets would simply
// be the counting order (of the words or reversed words
// depending on the interpretation as explained above).
{
    ulong x0 = x & -x;  // lowest one
    if ( 1 != x0 )  // easy case: set bit right of lowest one
    {
        x0 >>= 1;
        x ^= x0;
        return  x;
    }
    else  // lowest one at word end
    {
//        x ^= x0;  // clear lowest one
        x ^= 1;  // clear lowest one

        x0 = x & -x;  // new lowest one ...
//        x0 ^= (x0>>1);  x ^= x0;  // ... is moved one to the right
        x0 >>= 1;  x -= x0;  // ... is moved one to the right
        return  x;
    }
}
// -------------------------


static inline ulong prev_lexrev(ulong x)
// Return previous word in subset-lexrev order.
// Start with zero and use 2**n calls
// generate 2**n subsets of length n.
// E.g., for n==4:
//  ....  =  0
//  ...1  =  1
//  ..11  =  3
//  ..1.  =  2
//  .1.1  =  5
//  .111  =  7
//  .11.  =  6
//  .1..  =  4
//  1..1  =  9
//  1.11  = 11
//  1.1.  = 10
//  11.1  = 13
//  1111  = 15
//  111.  = 14
//  11..  = 12
//  1...  =  8
//
{
    ulong x0 = x & -x;  // lowest one
    if ( x & (x0<<1) )  // easy case: next higher bit is set
    {
        x ^= x0;  // clear lowest one
        return x;
    }
    else
    {
//        x0 ^= (x0<<1);  x ^= x0;  // move lowest one to the left
        x += x0;  // move lowest one to the left
        x |= 1;   // set rightmost bit
        return x;
    }
}
// -------------------------


static inline ulong negidx2lexrev(ulong k)
//
//   k:  negidx2lexrev(k)
//   0:  .....
//   1:  ....1
//   2:  ...11
//   3:  ...1.
//   4:  ..1.1
//   5:  ..111
//   6:  ..11.
//   7:  ..1..
//   8:  .1..1
//   9:  .1.11
//  10:  .1.1.
//  11:  .11.1
//  12:  .1111
//  13:  .111.
//  14:  .11..
//  15:  .1...
//  16:  1...1
//
{
    ulong z = 0;
    ulong h = highest_one(k);
    while ( k )
    {
        while ( 0 == (h & k) )  h >>= 1;
        z ^= h;
        ++k;
        k &= h - 1;
    }

    return  z;
}
// -------------------------

static inline ulong lexrev2negidx(ulong x)
// inverse of negidx2lexrev()
{
    if ( 0==x )  return 0;
    ulong h = x & -x;  // lowest one
    ulong r = (h-1);
    while ( x^=h )
    {
        r += (h-1);
        h = x & -x;  // next higher one
    }
    r += h;  // highest one
    return  r;

//    if ( 0==x )  return 0;
//    ulong h = highest_one(x);
//    ulong r = h - 1;
//    x ^= h;
//    if ( x )   r += lexrev2negidx(x);
//    else       r += r + 1;
//    return r;

//    ulong r = 0;
//    ulong h = highest_one(x);
//    while ( x )
//    {
//        while ( 0==(h&x) )  h >>= 1;
//        r ^= h;
//        x = next_lexrev(x);
//        if ( 0==x )  return r;
//        while ( 0==(h&x) )  h >>= 1;
//        x ^= h;
//    }
//    return  r;

//    ulong r = 0;
//    while ( x )
//    {
//        ulong h = highest_one(x);
//        r ^= h;
//        x = next_lexrev(x);
//        h = highest_one(x);
//        x ^= h;
//    }
//    return  r;
}
// -------------------------



static inline bool is_lexrev_fixed_point(ulong x)
// Return whether x is a fixed point in the prev_lexrev() - sequence
{
    if ( x & 1 )  return  (1==x);

    ulong w = bit_count(x);
    if ( w != (w & -w) )  return  false;
    if ( 0==x )  return  true;
    return  0 != ( (x & -x) & w );
}
// -------------------------



#endif  // !defined HAVE_BITLEX_H__
