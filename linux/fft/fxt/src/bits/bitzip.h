#if !defined HAVE_BITZIP_H__
#define      HAVE_BITZIP_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitbutterfly.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"

static inline ulong bit_zip(ulong x)
// Return word with lower half bits in even indices
//  and upper half bits in odd indices.
{
#if 1

#  if  BITS_PER_LONG == 64
    x = butterfly_16(x);
#  endif
    x = butterfly_8(x);
    x = butterfly_4(x);
    x = butterfly_2(x);
    x = butterfly_1(x);

#else

#  if  BITS_PER_LONG == 64
    ulong y =  (x >> 32);
    x &= 0xffffffffUL;
    x = (x | (x<<16)) & 0x0000ffff0000ffffUL;
    y = (y | (y<<16)) & 0x0000ffff0000ffffUL;
    x = (x | (x<<8))  & 0x00ff00ff00ff00ffUL;
    y = (y | (y<<8))  & 0x00ff00ff00ff00ffUL;
    x = (x | (x<<4))  & 0x0f0f0f0f0f0f0f0fUL;
    y = (y | (y<<4))  & 0x0f0f0f0f0f0f0f0fUL;
    x = (x | (x<<2))  & 0x3333333333333333UL;
    y = (y | (y<<2))  & 0x3333333333333333UL;
    x = (x | (x<<1))  & 0x5555555555555555UL;
    y = (y | (y<<1))  & 0x5555555555555555UL;
    x |= (y<<1);
#  else
    ulong y =  (x >> 16);
    x &= 0xffffUL;
    x = (x | (x<<8))  & 0x00ff00ffUL;
    y = (y | (y<<8))  & 0x00ff00ffUL;
    x = (x | (x<<4))  & 0x0f0f0f0fUL;
    y = (y | (y<<4))  & 0x0f0f0f0fUL;
    x = (x | (x<<2))  & 0x33333333UL;
    y = (y | (y<<2))  & 0x33333333UL;
    x = (x | (x<<1))  & 0x55555555UL;
    y = (y | (y<<1))  & 0x55555555UL;
    x |= (y<<1);
#  endif

#endif

    return  x;
}
// -------------------------


static inline ulong bit_unzip(ulong x)
// Return word with even indexed bits in lower half
//  and odd indexed bits in upper half.
// Inverse of bit_zip()
{
#if 1

    x = butterfly_1(x);
    x = butterfly_2(x);
    x = butterfly_4(x);
    x = butterfly_8(x);
#  if  BITS_PER_LONG == 64
    x = butterfly_16(x);
#  endif

#else

#  if  BITS_PER_LONG == 64
    ulong y = (x >> 1) & 0x5555555555555555UL;
    x &= 0x5555555555555555UL;
    x = (x | (x>>1))  & 0x3333333333333333UL;
    y = (y | (y>>1))  & 0x3333333333333333UL;
    x = (x | (x>>2))  & 0x0f0f0f0f0f0f0f0fUL;
    y = (y | (y>>2))  & 0x0f0f0f0f0f0f0f0fUL;
    x = (x | (x>>4))  & 0x00ff00ff00ff00ffUL;
    y = (y | (y>>4))  & 0x00ff00ff00ff00ffUL;
    x = (x | (x>>8))  & 0x0000ffff0000ffffUL;
    y = (y | (y>>8))  & 0x0000ffff0000ffffUL;
    x = (x | (x>>16)) & 0x00000000ffffffffUL;
    y = (y | (y>>16)) & 0x00000000ffffffffUL;
    x |= (y<<32);
#  else
    ulong y = (x >> 1) & 0x55555555UL;
    x &= 0x55555555UL;
    x = (x | (x>>1)) & 0x33333333UL;
    x = (x | (x>>2)) & 0x0f0f0f0fUL;
    x = (x | (x>>4)) & 0x00ff00ffUL;
    x = (x | (x>>8)) & 0x0000ffffUL;
    x |= (y<<16);
#  endif

#endif

    return  x;
}
// -------------------------

static inline ulong bit_zip0(ulong x)
// Return word with lower half bits in even indices.
// upper half must be zero.
// Same effect as bit_zip() but faster.
// 0000abcd --> 0a0b0c0d (a,b,c,d are bits).
{
#if 1

#  if  BITS_PER_LONG == 64
    x = (x | (x<<16)) & 0x0000ffff0000ffffUL;
    x = (x | (x<<8))  & 0x00ff00ff00ff00ffUL;
    x = (x | (x<<4))  & 0x0f0f0f0f0f0f0f0fUL;
    x = (x | (x<<2))  & 0x3333333333333333UL;
    x = (x | (x<<1))  & 0x5555555555555555UL;
#  else
    x = (x | (x<<8))  & 0x00ff00ffUL;
    x = (x | (x<<4))  & 0x0f0f0f0fUL;
    x = (x | (x<<2))  & 0x33333333UL;
    x = (x | (x<<1))  & 0x55555555UL;
#  endif


#else

#  if  BITS_PER_LONG == 64
    { ulong m = 0x00000000ffff0000UL;  m&=x;  x^=m;  x^=(m<<16); }
    { ulong m = 0x0000ff000000ff00UL;  m&=x;  x^=m;  x^=(m<<8); }
    { ulong m = 0x00f000f000f000f0UL;  m&=x;  x^=m;  x^=(m<<4); }
    { ulong m = 0x0c0c0c0c0c0c0c0cUL;  m&=x;  x^=m;  x^=(m<<2); }
    { ulong m = 0x2222222222222222UL;  m&=x;  x^=m;  x^=(m<<1); }
#  else
    { ulong m = 0x0000ff00UL;  m&=x;  x^=m;  x^=(m<<8); }
    { ulong m = 0x00f000f0UL;  m&=x;  x^=m;  x^=(m<<4); }
    { ulong m = 0x0c0c0c0cUL;  m&=x;  x^=m;  x^=(m<<2); }
    { ulong m = 0x22222222UL;  m&=x;  x^=m;  x^=(m<<1); }
#  endif

#endif

    return  x;
}
// -------------------------

static inline ulong bit_unzip0(ulong x)
// Gather bits in even positions into lower half.
// Inverse of bit_zip0().
// Bits at odd positions must be zero.
// 0a0b0c0d --> 0000abcd (a,b,c,d are bits).
{
#if 1

#  if  BITS_PER_LONG == 64
    x = (x | (x>>1))  & 0x3333333333333333UL;
    x = (x | (x>>2))  & 0x0f0f0f0f0f0f0f0fUL;
    x = (x | (x>>4))  & 0x00ff00ff00ff00ffUL;
    x = (x | (x>>8))  & 0x0000ffff0000ffffUL;
    x = (x | (x>>16)) & 0x00000000ffffffffUL;
#  else
    x = (x | (x>>1)) & 0x33333333UL;
    x = (x | (x>>2)) & 0x0f0f0f0fUL;
    x = (x | (x>>4)) & 0x00ff00ffUL;
    x = (x | (x>>8)) & 0x0000ffffUL;
#  endif

#else

#  if  BITS_PER_LONG == 64
    { ulong m = 0x2222222222222222UL<<1;   m&=x;  x^=m;  x^=(m>>1); }
    { ulong m = 0x0c0c0c0c0c0c0c0cUL<<2;   m&=x;  x^=m;  x^=(m>>2); }
    { ulong m = 0x00f000f000f000f0UL<<4;   m&=x;  x^=m;  x^=(m>>4); }
    { ulong m = 0x0000ff000000ff00UL<<8;   m&=x;  x^=m;  x^=(m>>8); }
    { ulong m = 0x00000000ffff0000UL<<16;  m&=x;  x^=m;  x^=(m>>16); }
#  else
    { ulong m = 0x22222222UL<<1;  m&=x;  x^=m;  x^=(m<<1); }
    { ulong m = 0x0c0c0c0cUL<<2;  m&=x;  x^=m;  x^=(m<<2); }
    { ulong m = 0x00f000f0UL<<4;  m&=x;  x^=m;  x^=(m<<4); }
    { ulong m = 0x0000ff00UL<<8;  m&=x;  x^=m;  x^=(m<<8); }
#  endif

#endif

    return  x;
}
// -------------------------


#define  BPLH  (BITS_PER_LONG/2)

static inline void bit_zip2(ulong x, ulong &lo, ulong &hi)
// Bits of lower half word spread out into even positions of lo,
// bits of upper half word spread out into even positions of hi.
{
#if 1

    x = bit_zip(x);
#  if  BITS_PER_LONG == 64
    lo = x & 0x5555555555555555UL;
    hi = (x>>1) & 0x5555555555555555UL;
#  else
    lo = x & 0x55555555UL;
    hi = (x>>1) & 0x55555555UL;
#  endif

#else
    hi = bit_zip0( x >> BPLH );
    lo = bit_zip0( (x << BPLH) >> (BPLH) );
#endif
}
// -------------------------

static inline ulong bit_unzip2(ulong lo, ulong hi)
// Inverse of bit_zip2(x, lo, hi).
{
#if 1
    return  bit_unzip( (hi<<1) | lo  );
#else
    return  bit_unzip0(lo) | (bit_unzip0(hi) << BPLH);
#endif
}
// -------------------------

static inline ulong bit_zip2(ulong x, ulong y)
// 2-word version:
// only the lower half of x and y are merged
{
    return  bit_zip( (y<<BPLH) + x );
}
// -------------------------

static inline void bit_unzip2(ulong t, ulong &x, ulong &y)
// 2-word version:
// only the lower half of x and y are filled
{
    t = bit_unzip(t);
    y = t >> BPLH;

//    x = t ^ (y<<BPLH);
#if  BITS_PER_LONG == 64
    x = t & 0x00000000ffffffffUL;
#else
    x = t & 0x0000ffffUL;
#endif
}
// -------------------------

//ulong
//bit_zip(ulong a, ulong b)
//{
//    ulong x = 0;
//    ulong m = 1, s = 0;
//    for (ulong k=0; k<BPLH; ++k)
//    {
//        x |= (a & m) << s;
//        ++s;
//        x |= (b & m) << s;
//        m <<= 1;
//    }
//    return  x;
//}
//// -------------------------
//
//
//void
//bit_unzip(ulong x, ulong &a, ulong &b)
//{
//    a = 0;  b = 0;
//    ulong m = 1, s = 0;
//    for (ulong k=0; k<BPLH; ++k)
//    {
//        a |= (x & m) >> s;
//        ++s;
//        m <<= 1;
//        b |= (x & m) >> s;
//        m <<= 1;
//    }
//}
//// -------------------------
#undef  BPLH


#endif  // !defined HAVE_BITZIP_H__
