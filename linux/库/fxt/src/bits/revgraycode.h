#if !defined HAVE_REVGRAYCODE_H__
#define      HAVE_REVGRAYCODE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong rev_gray_code(ulong x)
// Return the reversed Gray code of x.
// ('bit-wise derivative modulo 2 towards high bits').
// Also: multiplication by x+1 as binary polynomial.
// Also: return x^2+x in binary normal basis.
// rev_gray_code(x) == revbin( gray_code( revbin(x) ) )
{
    return  x ^ (x<<1);
}
// -------------------------


static inline ulong inverse_rev_gray_code(ulong x)
// Inverse of rev_gray_code()
// Note: the returned value contains at each bit position the parity
//   of all bits of the input right from it (incl. itself).
// Also: division by x+1 as powers series over GF(2)
// Also: return solution of z = x^2+x in binary normal basis.
// Note: the statements can be reordered at will.
// inverse_rev_gray_code(x) == revbin( inverse_gray_code( revbin(x) ) )
{
    // use: rev_gray ** BITSPERLONG == id:
    x ^= x<<1;  // rev_gray ** 1
    x ^= x<<2;  // rev_gray ** 2
    x ^= x<<4;  // rev_gray ** 4
    x ^= x<<8;  // rev_gray ** 8
    x ^= x<<16;  // rev_gray ** 16
    // here: x = rev_gray**31(input)
#if  BITS_PER_LONG >= 64
    x ^= x<<32;  // for 64bit words
#endif
    return  x;
}
// -------------------------



#endif  // !defined HAVE_REVGRAYCODE_H__
