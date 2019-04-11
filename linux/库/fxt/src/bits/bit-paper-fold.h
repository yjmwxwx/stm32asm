#if !defined  HAVE_BIT_PAPER_FOLD_H__
#define       HAVE_BIT_PAPER_FOLD_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitcount.h"

#include "bits/bitsperlong.h"
#include "fxttypes.h"  // ulong


static inline bool bit_paper_fold(ulong k)
// Return element number k of the paper-folding sequence:
// k=      0, 1, 2, 3, 4, 5, ...
// seq(k)= 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, ...
// Sequence (for k>=1) is entry A014577 of the OEIS.
// Also: for k>=1, the dragon curve turns left if seq(k)=1, else right.
// Also fixed point of morphism (for k>0, identify + with 1 and - with 0)
//   L |--> L+R+L-R,  R |--> L+R-L-R,  + |--> +,  - |--> -
// Also fixed point of morphism (for k>0)
//   L |--> L+R,  R |--> L-R,  + |--> +,  - |--> -
{
//    while ( (k&1)==0 )  k >>= 1;
//    return  ( (k&2)==0 );

    ulong h = k & -k;  // == lowest_one(k)
    k &= (h<<1);
    return  ( k==0 );
}
// -------------------------

static inline ulong bit_dragon_rot(ulong k)
// Return total rotation (as multiple of the right angle)
//   after k steps in the dragon curve corresponding to
//   the paper-folding sequence.
// k=      0, 1, 2, 3, 4, 5, ...
// seq(k)= 0, 1, 2, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 2, ...
// move =  +  ^  -  ^  -  v  -  ^  -  v  +  v  -  v  -  ...
// (+==right, -==left, ^==up, v==down).
// Sequence is entry A005811 of the OEIS.
// We take result modulo 4 to ignore multiples of 360 degree.
// Algorithm: count the ones in gray_code(k).
{
    return  bit_count( k ^ (k>>1) ) & 3;
}
// -------------------------


static inline bool bit_paper_fold_alt(ulong k)
// Return element number k of the alternate paper-folding sequence:
// k=      0, 1, 2, 3, 4, 5, ...
// seq(k)= 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, ...
// Sequence (for k>=1) is entry A106665 of the OEIS.
// Also: the corresponding curve turns left if seq(k)=1, else right.
// Also fixed point of morphism (for k>0, identify + with 1 and - with 0)
// L |--> R+L+R-L,  R |--> R+L-R-L,  + |--> +,  - |--> -
{
// Computation via:  a(4*n) = 1,  a(4*n+2) = 0,  a(2*n+1) = 1-a(n)
//    bool q = 1;
//    while ( (k&1)==0 )  { k >>= 1;  q=!q; }
//    return  ( (k&2)==0 ? q : !q );

    ulong h = k & -k;  // == lowest_one(k)
    h <<= 1;
#if  BITS_PER_LONG == 64
    ulong t = h & (k ^ 0xaaaaaaaaaaaaaaaaUL);
#else
    ulong t = h & (k ^ 0xaaaaaaaaUL);
#endif
    return  ( t!=0 );
}
// -------------------------


static inline ulong bit_paper_fold_alt_rot(ulong k)
// Return total rotation (as multiple of the right angle)
//   after k steps in the alternate paper-folding curve.
// k=      0, 1, 2, 3, 4, 5, ...
// seq(k)= 0, 1, 0, 3, 0, 1, 2, 1, 0, 1, 0, 3, 2, 3, 0, ...
// move =  +  ^  +  v  +  ^  -  ^  +  ^  +  v  -  v  +
// (+==right, -==left, ^==up, v==down).
// Algorithm: count the ones in  (w ^ gray_code(k)).
{
#if  BITS_PER_LONG == 64
    const ulong w = 0xaaaaaaaaaaaaaaaaUL;
#else
    const ulong w = 0xaaaaaaaaUL;
#endif
    return  bit_count( w ^ (k ^ (k>>1)) ) & 3;  // modulo 4
}
// -------------------------


static inline bool bit_paper_fold_general(ulong k, ulong w)
// Return element number k of the general paper-folding sequence:
// bit number x of the words w determines whether
// a left or right fold is made at the step x.
// With w==0 the result is  ! bit_paper_fold(k).
// With w==~0 the result is bit_paper_fold(k).
// The result with ~w is the complement of the result with w.
{
//    ulong h = k & -k;  // == lowest_one(k)
//    k &= (h<<1);
//    bool q = ( h & w );
//    return  ( k==0 ? q : !q );

    ulong h = k & -k;  // == lowest_one(k)
    h <<= 1;
    ulong t = h & (k^w);
    return  ( t!=0 );
}
// -------------------------


static inline ulong bit_paper_fold_general_rot(ulong k, ulong w)
// Return total rotation (as multiple of the right angle)
//   after k steps in the general paper-folding curve.
// Algorithm: count the ones in  (w ^ gray_code(k)).
// With w==~0 the result is bit_dragon_rot(k).
{
    return  bit_count( w ^ (k ^ (k>>1)) ) & 3;  // modulo 4
}
// -------------------------


#endif  // !defined HAVE_BIT_PAPER_FOLD_H__
