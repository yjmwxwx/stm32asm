#if !defined  HAVE_BITXTRANSFORMS_H__
#define       HAVE_BITXTRANSFORMS_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong blue_xcode(ulong a, ulong x)
{
    x &= (BITS_PER_LONG-1);  // modulo BITS_PER_LONG
    ulong s = BITS_PER_LONG >> 1;
    ulong m = ~0UL << s;
    while ( s )
    {
        if ( x & 1 )  a ^= ( (a&m) >> s );
        x >>= 1;
        s >>= 1;
        m ^= (m>>s);
    }
    return  a;
}
// -------------------------


static inline ulong yellow_xcode(ulong a, ulong x)
{
    x &= (BITS_PER_LONG-1);  // modulo BITS_PER_LONG
    ulong s = BITS_PER_LONG >> 1;
    ulong m = ~0UL >> s;
    while ( s )
    {
        if ( x & 1 )  a ^= ( (a&m) << s );
        x >>= 1;
        s >>= 1;
        m ^= (m<<s);
    }
    return  a;
}
// -------------------------


static inline ulong red_xcode(ulong a, ulong x)
{
    x &= (BITS_PER_LONG-1);  // modulo BITS_PER_LONG
    ulong s = BITS_PER_LONG >> 1;
    ulong m = ~0UL >> s;
    while ( s )
    {
        if ( x & 1 )
        {
            ulong u = a & m;
            ulong v = a ^ u;
            a = v ^ (u<<s);
            a ^= (v>>s);
        }
        x >>= 1;
        s >>= 1;
        m ^= (m<<s);
    }
    return  a;
}
// -------------------------


static inline ulong green_xcode(ulong a, ulong x)
{
    x &= (BITS_PER_LONG-1);  // modulo BITS_PER_LONG
    ulong s = BITS_PER_LONG >> 1;
    ulong m = ~0UL << s;
    while ( s )
    {
        if ( x & 1 )
        {
            ulong u = a & m;
            ulong v = a ^ u;
            a = v ^ (u>>s);
            a ^= (v<<s);
        }
        x >>= 1;
        s >>= 1;
        m ^= (m>>s);
    }
    return  a;
}
// -------------------------



#endif  // !defined HAVE_BITXTRANSFORMS_H__
