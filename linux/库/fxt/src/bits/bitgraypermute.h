#if !defined  HAVE_BITGRAYPERMUTE_H__
#define       HAVE_BITGRAYPERMUTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitsperlong.h"
#include "fxttypes.h"


#if  BITS_PER_LONG == 64
static inline ulong left_swap_16(ulong x)
// Return 64-bit word with two leftmost quarters swapped.
{
    const ulong mr = 0x0000ffff00000000UL;
    const ulong s = 16;
    const ulong ml = mr << s;
    const ulong t = ((x & ml) >> s) | ((x & mr) << s);
    x = (x & ~(ml | mr)) | t;
    return  x;
}
// -------------------------
#endif



static inline ulong left_swap_8(ulong x)
// Return word with two leftmost quarters of each 32-bit block swapped.
{
#if  BITS_PER_LONG == 64
    const ulong mr = 0x00ff000000ff0000UL;
#else
    const ulong mr = 0x00ff0000UL;
#endif
    const ulong s = 8;
    const ulong ml = mr << s;
    const ulong t = ((x & ml) >> s) | ((x & mr) << s);
    x = (x & ~(ml | mr)) | t;
    return  x;
}
// -------------------------


static inline ulong left_swap_4(ulong x)
// Return word with two leftmost quarters of each 16-bit block swapped.
{
#if  BITS_PER_LONG == 64
    const ulong mr = 0x0f000f000f000f00UL;
#else
    const ulong mr = 0x0f000f00UL;
#endif
    const ulong s = 4;
    const ulong ml = mr << s;
    const ulong t = ((x & ml) >> s) | ((x & mr) << s);
    x = (x & ~(ml | mr)) | t;
    return  x;
}
// -------------------------


static inline ulong left_swap_2(ulong x)
// Return word with two leftmost quarters of each 8-bit block swapped.
{
#if  BITS_PER_LONG == 64
    const ulong mr = 0x3030303030303030UL;
#else
    const ulong mr = 0x30303030UL;
#endif
    const ulong s = 2;
    const ulong ml = mr << s;
    const ulong t = ((x & ml) >> s) | ((x & mr) << s);
    x = (x & ~(ml | mr)) | t;
    return  x;
}
// -------------------------


static inline ulong left_swap_1(ulong x)
// Return word with two leftmost bits of each 4-bit block swapped.
{
#if  BITS_PER_LONG == 64
    const ulong mr = 0x4444444444444444UL;
#else
    const ulong mr = 0x44444444UL;
#endif
    const ulong s = 1;
    const ulong ml = mr << s;
    const ulong t = ((x & ml) >> s) | ((x & mr) << s);
    x = (x & ~(ml | mr)) | t;
    return  x;
}
// -------------------------


static inline ulong bit_gray_permute(ulong x)
// Return word with gray-permuted bits.
{
    x = left_swap_1(x);
    x = left_swap_2(x);
    x = left_swap_4(x);
    x = left_swap_8(x);
#if  BITS_PER_LONG == 64
    x = left_swap_16(x);
#endif
    return  x;
}
// -------------------------

static inline ulong bit_inverse_gray_permute(ulong x)
// Inverse of bit_gray_permute()
{
#if  BITS_PER_LONG == 64
    x = left_swap_16(x);
#endif
    x = left_swap_8(x);
    x = left_swap_4(x);
    x = left_swap_2(x);
    x = left_swap_1(x);
    return  x;
}
// -------------------------

#undef SH


#endif  // !defined HAVE_BITGRAYPERMUTE_H__
