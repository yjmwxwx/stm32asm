#if !defined HAVE_GRAYCODE_H__
#define      HAVE_GRAYCODE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong gray_code(ulong x)
// Return the Gray code of x
// ('bit-wise derivative modulo 2')
{
    return  x ^ (x>>1);
}
// -------------------------


static inline ulong inverse_gray_code(ulong x)
// inverse of gray_code()
// note: the returned value contains at each bit position
// the parity of all bits of the input left from it (incl. itself)
//
{
// ----- VERSION 1 (integration modulo 2):
//    ulong h=1, r=0;
//    do
//    {
//        if ( x & 1 )  r^=h;
//        x >>= 1;
//        h = (h<<1)+1;
//    }
//    while ( x!=0 );
//    return r;

// ----- VERSION 2 (apply graycode BITS_PER_LONG-1 times):
//    ulong r = BITS_PER_LONG;
//    while ( --r )  x ^= x>>1;
//    return x;

// ----- VERSION 3 (use: gray ** BITSPERLONG == id):
    x ^= x>>1;  // gray ** 1
    x ^= x>>2;  // gray ** 2
    x ^= x>>4;  // gray ** 4
    x ^= x>>8;  // gray ** 8
    x ^= x>>16;  // gray ** 16
    // here: x = gray**31(input)
    // note: the statements can be reordered at will

#if  BITS_PER_LONG > 32
    x ^= x>>32;  // for 64bit words
#endif

    return  x;
}
// -------------------------


static inline ulong byte_gray_code(ulong x)
// Return the Gray code of bytes in parallel
{
#if  BITS_PER_LONG == 32
    return  x ^ ((x & 0xfefefefeUL)>>1);
#endif

#if  BITS_PER_LONG == 64
    return  x ^ ((x & 0xfefefefefefefefeUL)>>1);
#endif
}
// -------------------------

static inline ulong byte_inverse_gray_code(ulong x)
// Return the inverse Gray code of bytes in parallel
{
#if  BITS_PER_LONG == 32
    x ^= ((x & 0xfefefefeUL)>>1);
    x ^= ((x & 0xfcfcfcfcUL)>>2);
    x ^= ((x & 0xf0f0f0f0UL)>>4);
#endif

#if  BITS_PER_LONG == 64
    x ^= ((x & 0xfefefefefefefefeUL)>>1);
    x ^= ((x & 0xfcfcfcfcfcfcfcfcUL)>>2);
    x ^= ((x & 0xf0f0f0f0f0f0f0f0UL)>>4);
#endif

    return  x;
}
// -------------------------


#endif  // !defined HAVE_GRAYCODE_H__
