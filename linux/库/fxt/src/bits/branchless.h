#if !defined HAVE_BRANCHLESS_H__
#define      HAVE_BRANCHLESS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"

//<<
// Some functions that avoid if-statements.
// The upos_*() functions only work for a limited range
// in order to have the highest bit emulate the carry flag.
// The trick is to use signed shift right to get a mask
// which == 0xfff... if a carry ocurred or zero else.
//
// With CPUs that have conditional-move instructions
// the compiler should produce branch-free machine code.
// GCC does that (in many situations; check to be sure).
//>>


static inline ulong upos_max(ulong a, ulong b)
// Return maximum(a, b)
// Both a and b must not have the most significant bit set
{
#if 1
    ulong d = b - a;
    d &= (ulong)( (long)d >> (BITS_PER_LONG-1) );
    // here: d ==
    // 0    if  b > a
    // b-a  if  a > b  (negative as signed type)
    return  b - d;

#else  // fxtbook version (triggers "conversion changes signedness" warning):
    long d = b - a;
    d &= (d>>(BITS_PER_LONG-1));
    // here: d ==
    // 0    if  b > a
    // b-a  if  a > b  (negative as signed type)
    return  b - d;
#endif
}
// -------------------------


static inline ulong upos_min(ulong a, ulong b)
// Return minimum(a, b)
// Both a and b must not have the most significant bit set
{
#if 1
    ulong d = b - a;
    d &= (ulong)( (long)d >> (BITS_PER_LONG-1) );
    return  a + d;

#else  // fxtbook version (triggers "conversion changes signedness" warning):
    long d = b - a;
    d &= (d>>(BITS_PER_LONG-1));
    return  a + d;
#endif
}
// -------------------------


static inline ulong upos_abs_diff(ulong a, ulong b)
// Return abs(a-b)
// Both a and b must not have the most significant bit set
{
#if 1
    ulong d1 = b - a;
    ulong d2 = (d1 & (ulong)( (long)d1 >> (BITS_PER_LONG-1)) ) << 1;
    return  d1 - d2;  // == (b - d) - (a + d);

#else  // fxtbook version (triggers "conversion changes signedness" warning):
    long d1 = b - a;
    long d2 = (d1 & (d1>>(BITS_PER_LONG-1)))<<1;
    return  d1 - d2;  // == (b - d) - (a + d);
#endif
}
// -------------------------


static inline void upos_sort2(ulong &a, ulong &b)
// Set {a, b} := {min(a, b), max(a,b)}
// Both a and b must not have the most significant bit set
{
#if 1
    ulong d = b - a;
    d &= (ulong)( (long)d >> (BITS_PER_LONG-1) );
    a += d;
    b -= d;

#else  // fxtbook version (triggers "conversion changes signedness" warning):
    long d = b - a;
    d &= (d>>(BITS_PER_LONG-1));
    a += d;
    b -= d;
#endif
}
// -------------------------


static inline ulong upos_add_sat(ulong a, ulong b)
// Return a + b
// If result overflows, return 0xfff...
// Both a and b must not have the most significant bit set
{
    ulong x = a + b;   // bit 31 set iff overflow
    ulong y = (ulong)( ((long)x) >> (BITS_PER_LONG-1) );
    // y == 0xfff.. if overflow, else 0
    return  (x | y);
}
// -------------------------

static inline ulong upos_sub_sat(ulong a, ulong b)
// Return a - b
// if result underflows, return zero
// Both a and b must not have the most significant bit set
{
    ulong x = a - b;  // bit 31 set iff underflow
    ulong y = (ulong)( ((long)x) >> (BITS_PER_LONG-1) );
    // y == 0xfff.. if underflow, else 0
    return  (x & ~y);
}
// -------------------------


static inline ushort add_sat16(ushort a, ushort b)
// Add two 16-bit numbers
// if result overflows, return 0xffff.
// Must have: sizeof(int)==4
{
    uint x = a + b;    // bit 16 set iff overflow
    uint y = x << 15;  // bit 31 set iff overflow
    y = (uint)( ((int)y) >> (31) );
    // y == 0xfff.. if overflow, else 0
    return (ushort)(x | y);
}
// -------------------------

static inline ushort sub_sat16(ushort a, ushort b)
// Add two 16-bit numbers
// if result underflows, return zero.
// Must have: sizeof(int)==4
{
    uint x = a - b;  // bits 16..31 set iff underflow
    uint y = (uint)( ((int)x) >> (31) );
    // y == 0xfff.. if underflow, else 0
    return (ushort)(x & ~y);
}
// -------------------------


static inline long max0(long x)
// Return max(0, x), i.e. return zero for negative input
// No restriction on input range
{
    return  x & ~(x >> (BITS_PER_LONG-1));
}
// -------------------------

static inline long min0(long x)
// Return min(0, x), i.e. return zero for positive input
// No restriction on input range
{
    return  x & (x >> (BITS_PER_LONG-1));
}
// -------------------------


static inline long clip_range0(long x, long m)
// Code equivalent (for m>0) to:
//   if ( x<0 )  x = 0;
//   else if ( x>m )  x = m;
//   return  x;
{
//    if ( (ulong)x > (ulong)m )  x = m & ~(x >> (BITS_PER_LONG-1));

    if ( x<0 )  x = 0;
    /*else*/  // commented out to make (compiled) function really branchless
    {
        if ( x>m )  x = m;
    }
    return  x;
}
// -------------------------

static inline long clip_range(long x, long mi, long ma)
// Code equivalent to (for mi<=ma):
//   if ( x<mi )  x = mi;
//   else if ( x>ma )  x = ma;
{
    x -= mi;
    x = clip_range0(x, ma-mi);
    x += mi;
    return  x;
}
// -------------------------

// in order to toggle a value x between two values a, b:
// for integers:
//  pre-calculate:  t  = a ^ b;
//  toggle:         x ^= t;
// for floats:
//  pre-calculate:  t = a + b;
//  toggle:         x = t - x;


// Paul Hsieh gives: (cf. http://www.pobox.com/~qed/optimize.html )

// test if inside square with side length m a power of 2:
// replace: if ( x>=0 && x<m && y>=0 && y<m )
// by:      if ( ((unsigned)(x|y))<m )

//static inline long max(long a, long b)
//{
//    b = a - b;
//    a -= b & (b>>(BITS_PER_LONG-1));
//    return a;
//}
//// -------------------------


//static inline long abs(long x)
//{
//    long t = x >> (BITS_PER_LONG-1);
//    return  (x ^ t) - t;
//}
//// -------------------------

//static inline long abs(long a)
//{
//    return a - ( (a+a) & (a>>(BITS_PER_LONG-1)) );
//}
//// -------------------------

//static inline long min(long a, long b)
//{
//    b = b - a;
//    a += b & (b>>(BITS_PER_LONG-1));
//    return a;
//}
//// -------------------------


#endif  // !defined HAVE_BRANCHLESS_H__
