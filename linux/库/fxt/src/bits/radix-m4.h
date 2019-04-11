#if !defined  HAVE_RADIX_M4_H__
#define       HAVE_RADIX_M4_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "bits/bitsperlong.h"

//: Conversion to and from radix(-4).

static inline ulong bin_to_radm4(ulong x)
// binary --> radix(-4)
{
#if  BITS_PER_LONG >= 64
    // mask in binary is ...110011001100
    // mask in radix 4 is ...30303030
    const ulong m = 0xccccccccccccccccUL;
#else
    const ulong m = 0xccccccccUL;
#endif
    x += m;
    x ^= m;
    return  x;
}
// -------------------------

static inline ulong radm4_to_bin(ulong x)
// radix(-4) --> binary
// inverse of bin_to_radm4()
{
#if  BITS_PER_LONG >= 64
    const ulong m = 0xccccccccccccccccUL;
#else
    const ulong m = 0xccccccccUL;
#endif
    x ^= m;
    x -= m;
    return  x;
}
// -------------------------


static inline ulong next_radm4(ulong x)
// With x the radix(-4) representation of n
// return radix(-4) representation of n+1.
{
#if  BITS_PER_LONG >= 64
    const ulong m = 0xccccccccccccccccUL;
#else
    const ulong m = 0xccccccccUL;
#endif
    x ^= m;
    ++x;
    x ^= m;
    return x;
}
// -------------------------

static inline ulong prev_radm4(ulong x)
// With x the radix(-4) representation of n
// return radix(-4) representation of n-1.
{
#if  BITS_PER_LONG >= 64
    const ulong m = 0xccccccccccccccccUL;
#else
    const ulong m = 0xccccccccUL;
#endif
    x ^= m;
    --x;
    x ^= m;
    return x;
}
// -------------------------


static inline ulong radm4_add(ulong a, ulong b)
// Addition of two numbers in radix(-4) representation.
{
#if 1

#if  BITS_PER_LONG >= 64
    const ulong m = 0xccccccccccccccccUL;
#else
    const ulong m = 0xccccccccUL;
#endif

#if 1
    a ^= m;  b ^= m;
    ulong t = a + b;
    t -= m;
    t ^= m;
    return t;
#endif

#if 0
    a ^= m;  b ^= m;
    a -= m;  b -= m;
    ulong t = a + b;
    t += m;
    t ^= m;
    return t;
#endif

#else
    return bin_to_radm4( radm4_to_bin(a) + radm4_to_bin(b) );
#endif
}
// -------------------------


#endif  // !defined HAVE_RADIX_M4_H__
