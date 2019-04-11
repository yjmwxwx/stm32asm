#if !defined  HAVE_BITTRANSFORMS_H__
#define       HAVE_BITTRANSFORMS_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"


static inline ulong blue_code(ulong a)
// Self-inverse.
// range [0..2^k-1] is mapped onto itself
// work \prop log_2(BITS_PER_LONG)
//.
// With  B:=blue,  G:=gray,  I:=inverse_gray
//   G(B(G(B(a)))) == a
//   G(B(G(a)))    == B(a)
//   I(B(I(a)))    == B(a)
//   G(B(a))       == B(I(a))
// With  P:=parity
//   P(B(a)) == a % 2
{
    ulong s = BITS_PER_LONG >> 1;
    ulong m = ~0UL << s;
    do
    {
        a ^= ( (a&m) >> s );
        s >>= 1;
        m ^= (m>>s);
    }
    while ( s );
    return  a;
}
// -------------------------



static inline ulong yellow_code(ulong a)
// Self-inverse.
// work \prop log_2(BITS_PER_LONG)
//.
// With  Y:=yellow,  B:=blue,  r:=revbin
//   B(a) == Y(r(Y(a)))
//   Y(a) == r(B(r(a)))
//   r(a) == Y(B(Y(a))) == B(Y(B(a)))
// With  P:=parity
//   P(Y(a)) == highest_one(a) == "sign(a)"
{
    ulong s = BITS_PER_LONG >> 1;
    ulong m = ~0UL >> s;
    do
    {
        a ^= ( (a&m) << s );
        s >>= 1;
        m ^= (m<<s);
    }
    while ( s );
    return  a;
}
// -------------------------


static inline ulong red_code(ulong a)
// work \prop log_2(BITS_PER_LONG)
// =^=  revbin( blue_code(a) );
{
    ulong s = BITS_PER_LONG >> 1;
    ulong m = ~0UL >> s;
    do
    {
        ulong u = a & m;
        ulong v = a ^ u;
        a = v ^ (u<<s);
        a ^= (v>>s);
        s >>= 1;
        m ^= (m<<s);
    }
    while ( s );
    return  a;
}
// -------------------------


static inline ulong green_code(ulong a)
// work \prop log_2(BITS_PER_LONG)
// =^=  revbin( yellow_code(a) );
{
    ulong s = BITS_PER_LONG >> 1;
    ulong m = ~0UL << s;
    do
    {
        ulong u = a & m;
        ulong v = a ^ u;
        a = v ^ (u>>s);
        a ^= (v<<s);
        s >>= 1;
        m ^= (m>>s);
    }
    while ( s );
    return  a;
}
// -------------------------


#endif  // !defined HAVE_BITTRANSFORMS_H__
