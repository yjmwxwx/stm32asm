#if !defined HAVE_ZEROBYTE_H__
#define      HAVE_ZEROBYTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong contains_zero_byte(ulong x)
// Determine if any sub-byte of x is zero:
// Return zero when x contains no zero-byte and nonzero when it does.
//
// To scan for other values than zero (e.g. 0xa5) use:
//  contains_zero_byte( x ^ 0xa5a5a5a5UL )
{
#if 1

#if  BITS_PER_LONG == 32
    return  0x80808080UL & ( x - 0x01010101UL ) & ~x;
#else
    return  0x8080808080808080UL & ( x - 0x0101010101010101UL ) & ~x;
#endif

#else

#if  BITS_PER_LONG == 32
// Subtract 1 from each of the bytes and then look for bytes
//   where the borrow propagated all the way to the most significant bit.

    return  ((x-0x01010101UL)^x) & (~x) & 0x80808080UL;

    // return ((x-0x01010101UL) ^ x) & 0x80808080UL;
    // ...  gives false alarms when a byte of x is 0x80:
    //   hex: 80-01 = 7f,  7f^80 = ff,  ff & 80 = 80
    // Therefor for strings where the high bit of every byte is known to be zero
    //  (for example: ascii-strings) the simple version can be used.
#endif

#if  BITS_PER_LONG == 64
    return  ((x-0x0101010101010101UL) ^ x) & (~x) & 0x8080808080808080UL;
#endif

#endif
}
// -------------------------


#endif  // !defined HAVE_ZEROBYTE_H__
