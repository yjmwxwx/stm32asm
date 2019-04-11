// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/modarith.h"
#include "mod/mtypes.h"
#include "fxttypes.h"  // ulong

void
chebyT(umod_t n, umod_t x, umod_t &t1, umod_t &t0, umod_t m)
// Compute t1=T(n-1,x), t0=T(n,x) modulo m
// where T(n,x) is the n-th Chebyshev polynomial of the first kind.
{
    if ( n<=1 )
    {
        if ( 1==n )  { t1=1;  t0=x; }
        else         { t1=x;  t0=1; }
        return;
    }

    bool q = (n&1);  // whether n odd
    umod_t nr = (n+q) >> 1;
    umod_t r1, r0;
    chebyT(nr, x, r1, r0, m);
    umod_t T1, T0;
    if ( !q )  // n even
    {
        T1 = mul_mod(r0, r1, m);  // multiplication
        T1 = add_mod(T1, T1, m);
        t1 = sub_mod(T1, x, m);

        T0 = sqr_mod(r0, m);   // squaring
        T0 = add_mod(T0, T0, m);
        t0 = decr_mod(T0, m);
    }
    else  // n odd
    {
        T1 = sqr_mod(r1, m);  // squaring
        T1 = add_mod(T1, T1, m);
        t1 = decr_mod(T1, m);

        T0 = mul_mod(r0, r1, m);  // multiplication
        T0 = add_mod(T0, T0, m);
        t0 = sub_mod(T0, x, m);
    }
}
// -------------------------

umod_t
chebyT(umod_t n, umod_t x, umod_t m)
// Return t=T(n,x) modulo m
// where T(n,x) is the n-th Chebyshev polynomial of the first kind.
{
#if 1
    if ( n<=1 )
    {
        if ( 0==n )  return 1;
        else         return x;
    }

    umod_t t=0,  q=n;
    while ( 0==(q&1) )  { q>>=1; ++t; }
    // here n == q*2^t
    umod_t t1, t0;
    chebyT(q, x, t1, t0, m);
    while ( t )
    {
        t0 = sqr_mod(t0, m);
        t0 = add_mod(t0, t0, m);
        t0 = decr_mod(t0, m);
        --t;
    }
    return t0;
#else
    umod_t t1, t0;
    chebyT(n, x, t1, t0, m);
    return t0;
#endif
}
// -------------------------


#define VERX  // define to use faster algorithm for chebyT2(...)

void
chebyT2(umod_t n, umod_t &t1, umod_t &t0, umod_t m)
// Compute t1=T(n-1,x), t0=T(n,x) modulo m where x=2
// and T(n,x) is the n-th Chebyshev polynomial of the first kind.
// Must have m>4
{
#ifdef VERX
#define x 2
    if ( n<=1 )
    {
        if ( 1==n )  { t1=1; t0=x; }
        else         { t1=x; t0=1; }
        return;
    }

    bool q = (n&1);  // whether n odd
    umod_t nr = (n+q) >> 1;
    umod_t r1, r0;
    chebyT2(nr, r1, r0, m);
    umod_t T1, T0;
    if ( !q )  // n even
    {
        T1 = mul_mod(r0, r1, m);  // multiplication
        T1 = add_mod(T1, T1, m);
        t1 = sub_mod(T1, x, m);

        T0 = sqr_mod(r0, m);   // squaring
        T0 = add_mod(T0, T0, m);
        t0 = decr_mod(T0, m);
    }
    else  // n odd
    {
        T1 = sqr_mod(r1, m);  // squaring
        T1 = add_mod(T1, T1, m);
        t1 = decr_mod(T1, m);

        T0 = mul_mod(r0, r1, m);  // multiplication
        T0 = add_mod(T0, T0, m);
        t0 = sub_mod(T0, x, m);
    }
#undef x
#else
// T_{n} = U_{n} - x*U_{n-1}  (where x=2)
// T_{n-1} = U_{n-1} - x*U_{n-2}
//  (where U_{n-2}=2*x*U_{n-1}-U_{n})
    umod_t u1, u0;
    chebyU2(n, u1, u0, m);
    umod_t r0 = u0;  r0=sub_mod(r0, u1, m);  r0=sub_mod(r0, u1, m);
    t0 = r0;
    umod_t u2 = u1;  u2 = add_mod(u2, u2, m);  u2 = add_mod(u2, u2, m);
    u2 = sub_mod(u2, u0, m);
    umod_t r1 = u1;  r1 = sub_mod(r1, u2, m);  r1 = sub_mod(r1, u2, m);
    t1 = r1;
#endif
}
// -------------------------


umod_t
chebyT2(umod_t n, umod_t m)
// Return t=T(n,x) modulo m where x=2
// and T(n,x) is the n-th Chebyshev polynomial of the first kind.
// Must have m>4
{
#ifdef VERX
    umod_t t1, t0;
    chebyT2(n, t1, t0, m);
    return t0;
#else
// T_{n} = U_{n} - x*U_{n-1}  (where x=2)
    umod_t u1, u0;
    chebyU2(n, u1, u0, m);
    umod_t r0 = u0;  r0=sub_mod(r0, u1, m);  r0=sub_mod(r0, u1, m);
    return r0;
#endif
}
// -------------------------
