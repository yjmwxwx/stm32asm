#if !defined  HAVE_BITSEPARATE_H__
#define       HAVE_BITSEPARATE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitgather.h"


static inline ulong bit_separate(ulong w, ulong m, ulong s=BITS_PER_LONG/2)
// Return  word with bits of w separated as indicated by m.
// Bits at positions where m is 0/1 are moved to the low/high end.
// Examples:
//  w = ABCDEFGH
//  m = 00111100
//  ==> CDEFABGH
//
//  w = ABCDEFGH
//  m = 01010101
//  ==> BDFHACEG
//
// s must contain the number of ones set in m.
// For the default s exactly half of the bits must be set in m
{
    ulong a0 = bit_gather(w, ~m);
    ulong a1 = bit_gather(w,  m);
    return  (a0 ^ (a1<<s));
}
// -------------------------


static inline ulong bit_separate_subwords(ulong w, ulong m, ulong s)
// Bit-separate all length-s subwords of w.
// s>=2 must divide BITS_PER_LONG.
// The mask must be such that exactly half of the bits
//   in each subword are set.
// Examples:
//  s = 4
//  w = ABCD EFGH
//  m = 0011 1010
//  ==> CDAB EGFH
//
//  s = 2
//  w = AB CD EF GH
//  m = 01 10 01 10
//  ==> BA CD FE GH
//
// For s==BITS_PER_LONG the result is as with bit_separate(w, m)
//  if half of the bits of m are set.
{
    ulong swm = ~0UL >> ( BITS_PER_LONG - s );  // sub word mask
    swm <<= ( BITS_PER_LONG - s );  // at high end
    ulong h = s/2;
    ulong a = 0;  // return
    do
    {
        a <<= s;
        ulong m1 = m  & swm;
        ulong m0 = m1 ^ swm;
        ulong a0 = bit_gather(w, m0);
        ulong a1 = bit_gather(w, m1);
        a |= (a0 ^ (a1<<h));
    }
    while ( (swm>>=s) );
    return  a;
}
// -------------------------


#endif  // !defined HAVE_BITSEPARATE_H__
