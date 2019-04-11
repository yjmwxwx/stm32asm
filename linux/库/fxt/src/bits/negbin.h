#if !defined  HAVE_NEGBIN_H__
#define       HAVE_NEGBIN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitzip.h"  // bit_zip0()

#include "fxttypes.h"
#include "bits/bitsperlong.h"


//: Conversion to and from radix(-2).

static inline ulong bin2neg(ulong x)
// binary --> radix(-2)
//.
// HAKMEM, item 128
{
#if  BITS_PER_LONG >= 64
    // mask in radix 2 is ...10101010
    const ulong m = 0xaaaaaaaaaaaaaaaaUL;
#else
    const ulong m = 0xaaaaaaaaUL;
#endif
    x += m;
    x ^= m;
    return  x;
}
// -------------------------

static inline ulong neg2bin(ulong x)
// radix(-2) --> binary
// inverse of bin2neg()
{
#if  BITS_PER_LONG >= 64
    const ulong m = 0xaaaaaaaaaaaaaaaaUL;
#else
    const ulong m = 0xaaaaaaaaUL;
#endif
    x ^= m;
    x -= m;
    return  x;
}
// -------------------------


static inline ulong negbin_fixed_point(ulong k)
// Return the k-th fixed point of bin2neg()
// With k=000000ABCDEF (binary) the returned value is 0A0B0C0D0E0F.
{
#if 1
    return bit_zip0(k);
#else
    ulong f = 0;
    for (ulong m=1, s=0;  m!=0;  m<<=1, ++s)  f ^= ( (k&m)<<s );
    return  f;
#endif
}
// -------------------------



static inline ulong next_negbin(ulong x)
// With x the radix(-2) representation of n
// return radix(-2) representation of n+1.
{
#if 1  // version 1:
#if  BITS_PER_LONG >= 64
    const ulong m = 0xaaaaaaaaaaaaaaaaUL;
#else
    const ulong m = 0xaaaaaaaaUL;
#endif
    x ^= m;
    ++x;
    x ^= m;
    return x;

#else  // version 2:
    ulong s = x << 1;
    ulong y = x ^ s;
    y += 1;
    s ^= y;
    return s;

    // version 3:  use mask 0x5555 and decrement
#endif  // VERSION
}
// -------------------------

static inline ulong prev_negbin(ulong x)
// With x the radix(-2) representation of n
// return radix(-2) representation of n-1.
{
#if 1  // version 1:
#if  BITS_PER_LONG >= 64
    const ulong m = 0xaaaaaaaaaaaaaaaaUL;
#else
    const ulong m = 0xaaaaaaaaUL;
#endif
    x ^= m;
    --x;
    x ^= m;
    return x;

#else  // version 2:
#if  BITS_PER_LONG >= 64
    const ulong m = 0x5555555555555555UL;
#else
    const ulong m = 0x55555555UL;
#endif
    x ^= m;
    ++x;
    x ^= m;
    return x;
#endif  // VERSION
}
// -------------------------


static inline ulong negbin_add(ulong a, ulong b)
// Addition of two numbers in radix(-2) representation.
{
#if 1

#if  BITS_PER_LONG >= 64
    const ulong m = 0xaaaaaaaaaaaaaaaaUL;
#else
    const ulong m = 0xaaaaaaaaUL;
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
    return bin2neg( neg2bin(a) + neg2bin(b) );
#endif
}
// -------------------------

#endif  // !defined HAVE_NEGBIN_H__
