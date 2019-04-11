#if !defined HAVE_BITBUTTERFLY_H__
#define      HAVE_BITBUTTERFLY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"


//: The butterfly_*() functions are used in bit_zip() and bit_unzip()

#define BIT_BUTTERFLY_VER 1  // default is 1 (faster)


#if  BITS_PER_LONG == 64
static inline ulong butterfly_16(ulong x)
// Swap the two central blocks of 16 bits.
{
#if BIT_BUTTERFLY_VER == 1

    const ulong ml = 0x0000ffff00000000UL;
    const ulong s = 16;
    const ulong mr = ml >> s;
    const ulong t = ((x & ml) >> s ) | ((x & mr) << s );
    x = (x & ~(ml | mr)) | t;
    return  x;

#else

    const ulong m = 0x0000ffffffff0000UL;
    ulong c = x & m;
    c ^= (c<<16) ^ (c>>16);
    c &= m;
    return  x ^ c;

#endif
}
// -------------------------
#endif



static inline ulong butterfly_8(ulong x)
// Swap in each block of 32 bits the two central blocks of 8 bits.
{
#if BIT_BUTTERFLY_VER == 1

#if  BITS_PER_LONG == 64
    const ulong ml = 0x00ff000000ff0000UL;
#else
    const ulong ml = 0x00ff0000UL;
#endif
    const ulong s = 8;
    const ulong mr = ml >> s;
    const ulong t = ((x & ml) >> s ) | ((x & mr) << s );
    x = (x & ~(ml | mr)) | t;
    return  x;

#else


#if  BITS_PER_LONG == 64
    const ulong m = 0x00ffff0000ffff00UL;
#else
    const ulong m = 0x00ffff00UL;
#endif
    ulong c = x & m;
    c ^= (c<<8) ^ (c>>8);
    c &= m;
    return  x ^ c;

#endif
}
// -------------------------


static inline ulong butterfly_4(ulong x)
// Swap in each block of 16 bits the two central blocks of 4 bits.
{
#if BIT_BUTTERFLY_VER == 1

#if  BITS_PER_LONG == 64
    const ulong ml = 0x0f000f000f000f00UL;
#else
    const ulong ml = 0x0f000f00UL;
#endif
    const ulong s = 4;
    const ulong mr = ml >> s;
    const ulong t = ((x & ml) >> s ) | ((x & mr) << s );
    x = (x & ~(ml | mr)) | t;
    return  x;

#else

#if  BITS_PER_LONG == 64
    const ulong m = 0x0ff00ff00ff00ff0UL;
#else
    const ulong m = 0x0ff00ff0UL;
#endif
    ulong c = x & m;
    c ^= (c<<4) ^ (c>>4);
    c &= m;
    return  x ^ c;

#endif
}
// -------------------------


static inline ulong butterfly_2(ulong x)
// Swap in each block of 8 bits the two central blocks of 2 bits.
{
#if BIT_BUTTERFLY_VER == 1

#if  BITS_PER_LONG == 64
    const ulong ml = 0x3030303030303030UL;
#else
    const ulong ml = 0x30303030UL;
#endif
    const ulong s = 2;
    const ulong mr = ml >> s;
    const ulong t = ((x & ml) >> s ) | ((x & mr) << s );
    x = (x & ~(ml | mr)) | t;
    return  x;

#else

#if  BITS_PER_LONG == 64
    const ulong m = 0x3c3c3c3c3c3c3c3cUL;
#else
    const ulong m = 0x3c3c3c3cUL;
#endif
    ulong c = x & m;
    c ^= (c<<2) ^ (c>>2);
    c &= m;
    return  x ^ c;

#endif
}
// -------------------------


static inline ulong butterfly_1(ulong x)
// Swap in each block of 4 bits the two central bits.
{
#if BIT_BUTTERFLY_VER == 1

#if  BITS_PER_LONG == 64
    const ulong ml = 0x4444444444444444UL;
#else
    const ulong ml = 0x44444444UL;
#endif
    const ulong s = 1;
    const ulong mr = ml >> s;
    const ulong t = ((x & ml) >> s ) | ((x & mr) << s );
    x = (x & ~(ml | mr)) | t;
    return  x;

#else

#if  BITS_PER_LONG == 64
    const ulong m = 0x6666666666666666UL;
#else
    const ulong m = 0x66666666UL;
#endif
    ulong c = x & m;
    c ^= (c<<1) ^ (c>>1);
    c &= m;
    return  x ^ c;

#endif
}
// -------------------------

#undef BIT_BUTTERFLY_VER



#endif  // !defined HAVE_BITBUTTERFLY_H__
