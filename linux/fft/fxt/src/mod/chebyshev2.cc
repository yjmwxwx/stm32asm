// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/modarith.h"
#include "mod/mtypes.h"
#include "fxttypes.h"  // ulong


void
chebyU(umod_t n, umod_t x, umod_t &u1, umod_t &u0, umod_t m)
// Compute u1=U(n-1, x), u0=U(n, x) modulo m
// where U(n, x) is the n-th Chebyshev polynomial of the second kind.
{
    if ( n<=1 )
    {
        if ( 1==n )  { u1=1;  u0=add_mod(x, x, m); }
        else         { u1=0;  u0=1; }
        return;
    }

    umod_t nr = n >> 1;
    umod_t r1, r0;
    chebyU(nr, x, r1, r0, m);
    umod_t ue = mul_mod(add_mod(r0, r1, m), sub_mod(r0, r1, m), m);

    bool q = !(n&1);  // whether n even
    if ( q )  // n even
    {
        u0 = ue;
        umod_t t = mul_mod(r1, x, m);
        t = sub_mod(r0, t, m);
        t = mul_mod(r1, t, m);
        u1 = add_mod(t, t, m);
    }
    else
    {
        u1 = ue;
        umod_t t = mul_mod(r0, x, m);
        t = sub_mod(t, r1, m);
        t = mul_mod(t, r0, m);
        u0 = add_mod(t, t, m);
    }
}
// -------------------------

umod_t
chebyU(umod_t n, umod_t x, umod_t m)
// Return t=U(n, x) modulo m
// where U(n, x) is the n-th Chebyshev polynomial of the second kind.
{
    umod_t u1, u0;
    chebyU(n, x, u1, u0, m);
    return u0;
}
// -------------------------

#define VERX  // define to use faster algorithm for chebyU2(...)

void
chebyU2(umod_t n, umod_t &u1, umod_t &u0, umod_t m)
// Compute  u1=U(n-1, x), u0=U(n, x) modulo m where x=2
// and U(n, x) is the n-th Chebyshev polynomial of the second kind.
// Must have m>4
{
    if ( n<=1 )
    {
        if ( 1==n )  { u1 = 1; u0 = 4; /* 4==2*x */ }
        else         { u1 = 0; u0 = 1; }
        return;
    }

#ifdef VERX
    umod_t nr = n >> 1;
    umod_t r1, r0;
    chebyU2(nr, r1, r0, m);
    umod_t ue = mul_mod(add_mod(r0, r1, m), sub_mod(r0, r1, m), m);

    bool q = !(n&1);  // whether n even
    if ( q )  // n even
    {
        u0 = ue;
        umod_t t = add_mod(r1, r1, m);
        t = sub_mod(r0, t, m);
        t = mul_mod(r1, t, m);
        u1 = add_mod(t, t, m);
    }
    else
    {
        u1 = ue;
        umod_t t = add_mod(r0, r0, m);
        t = sub_mod(t, r1, m);
        t = mul_mod(t, r0, m);
        u0 = add_mod(t, t, m);
    }

#else

    ulong q = n & 1;
    umod_t nr = (n-q) >> 1;
    q ^= 1UL;  // whether n is even
    umod_t ru1, ru0;
    chebyU2(nr, ru1, ru0, m);  // recursion
    umod_t s1 = mul_mod(ru1, ru1, m);  // s1=ru1^2
    umod_t s2 = mul_mod(ru0, ru0, m);  // s2=ru0^2
    umod_t s3 = add_mod(ru0, ru1, m);
    s3 = mul_mod(s3, s3, m);  // s3=(ru0+ru1)^2
    umod_t ds = sub_mod(s2, s1, m);  // ds=s2-s1
    if ( q )
    {
        u0 = ds;
        umod_t t = sub_mod(s3, s2, m);
        umod_t p = s1;
        p = add_mod(p, p, m);
        p = add_mod(p, p, m);
        p = add_mod(p, s1, m);  // == 5*s1 == (2*x+1)*s1
        u1 = sub_mod(t, p, m);  // u1 = s3-s2-((2*x)+1)*s1
    }
    else
    {
        u1 = ds;
        umod_t t = sub_mod(s1, s3, m);
        umod_t p = s2;
        p = add_mod(p, p, m);
        p = add_mod(p, p, m);
        p = add_mod(p, s2, m);  // == 5*s2 == (2*x+1)*s2
        u0 = add_mod(t, p, m);  // u0 = s1+((2*x)+1)*s2-s3
    }
#endif
}
// -------------------------


umod_t
chebyU2(umod_t n, umod_t m)
// Return u=U(n, x) modulo m where x=2
// and U(n, x) is the n-th Chebyshev polynomial of the second kind.
// Must have m>4
{
    umod_t u1, u0;
    chebyU2(n, u1, u0, m);
    return u0;
}
// -------------------------

