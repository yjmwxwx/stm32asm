#if !defined HAVE_BITZIP_PAIRS_H__
#define      HAVE_BITZIP_PAIRS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong bit_zip0_pairs(ulong x)
// Return word with lower half bits(-pairs) in even (pair-)indices,
// i.e., indices 4k+0, 4k+1.
// Upper half must be zero.
// 0000abcd --> 0a0b0c0d (a,b,c,d are pairs of bits).
{
#  if  BITS_PER_LONG == 64
    x = (x | (x<<16)) & 0x0000ffff0000ffffUL;
    x = (x | (x<<8))  & 0x00ff00ff00ff00ffUL;
    x = (x | (x<<4))  & 0x0f0f0f0f0f0f0f0fUL;
    x = (x | (x<<2))  & 0x3333333333333333UL;
//    x = (x | (x<<1))  & 0x5555555555555555UL;
#  else
    x = (x | (x<<8))  & 0x00ff00ffUL;
    x = (x | (x<<4))  & 0x0f0f0f0fUL;
    x = (x | (x<<2))  & 0x33333333UL;
//    x = (x | (x<<1))  & 0x55555555UL;
#  endif

    return  x;
}
// -------------------------

static inline ulong bit_unzip0_pairs(ulong x)
// Gather pairs bits in even positions (4k+0, 4k+1) into lower half.
// Inverse of bit_zip0_pairs().
// Bit pairs at odd (pair-)positions (4k+2, 4k+3) must be zero.
// 0a0b0c0d --> 0000abcd (a,b,c,d are pairs of bits).
{
#  if  BITS_PER_LONG == 64
//    x = (x | (x>>1))  & 0x3333333333333333UL;
    x = (x | (x>>2))  & 0x0f0f0f0f0f0f0f0fUL;
    x = (x | (x>>4))  & 0x00ff00ff00ff00ffUL;
    x = (x | (x>>8))  & 0x0000ffff0000ffffUL;
    x = (x | (x>>16)) & 0x00000000ffffffffUL;
#  else
//    x = (x | (x>>1)) & 0x33333333UL;
    x = (x | (x>>2)) & 0x0f0f0f0fUL;
    x = (x | (x>>4)) & 0x00ff00ffUL;
    x = (x | (x>>8)) & 0x0000ffffUL;
#  endif

    return  x;
}
// -------------------------



#endif  // !defined HAVE_BITZIP_PAIRS_H__
