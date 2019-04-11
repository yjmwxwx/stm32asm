// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/modarith.h"
#include "mod/numtheory.h"
#include "mod/factor.h"
#include "mod/primes.h"  // n2qt()
//#include "jjassert.h"
//#include "cmath.h"

#include "fxtalloca.h"
#include "fxttypes.h"


umod_t
sqrt_modp(umod_t a, umod_t p)
// Return x such that x*x==a (mod p)
// p must be an odd prime.
// If a is not a square mod p then return 0.
//.
// cf. Cohen p.33
{
    if ( 1!=kronecker(a, p) )  return 0;  // not a square mod p

    // initialize q, t so that  p == q * 2^t + 1
    umod_t q;  uint t;
    n2qt(p, q, t);

    // find generator of 2-Sylow subgroup:
    umod_t z = 0,  n = 0;
    for (n=1; n<p; ++n)
    {
        if ( -1==kronecker(n, p) )
        {
            z = pow_mod(n, q, p);
            break;
        }
    }

    // jjassert( n<p ); // sqrt_modp(): no generator found !
    if ( n>=p )  return 0;

    // (generator found)

    // initialize:
    umod_t y = z;
    uint r = t;
    umod_t x = pow_mod(a, (q-1)/2, p);
    // a = a*x;  b = a*x*x
//    umod_t b;
//    b = mul_mod(a, x, p);
//    b = mul_mod(b, x, p);
//    x = mul_mod(x, a, p);
    umod_t b = x;
    x = mul_mod(x, a, p);
    b = mul_mod(b, x, p);

    // step3:
    while ( 1 )
    {
        // find exponent:
//        jjassert( mul_mod(a, b, p)==mul_mod(x, x, p) );  // a*b == x*x
//        jjassert( r>0 );
//        jjassert( pow_mod(y, 1ULL<<(r-1), p)==p-1 );    // y^(2^(r-1)) == -1
//        jjassert( pow_mod(b, 1ULL<<(r-1), p)==1ULL );   // b^(2^(r-1)) == +1

        if ( 1==b )  return x;

        uint m;
        for (m=1; m<r; ++m)
        {
            if ( 1==pow_mod(b, 1ULL<<m, p) )  break;
        }

        if ( m==r )  return  0;  // a is not a square mod p

        // reduce exponent:
        umod_t v = pow_mod(y, 1ULL<<(r-m-1), p);
        y = sqr_mod(v, p);
        r = m;
        x = mul_mod(x, v, p);
        b = mul_mod(b, y, p);
    }
}
// -------------------------


umod_t
sqrt_modpp(umod_t a, umod_t p, ulong ex)
// Return r so that r^2 == a (mod p^ex)
// return 0 if there is no such r
{
    umod_t r;

    if ( 2==p )  // case p==2
    {
        if ( false==is_quadratic_residue_2ex(a, ex) )  return 0;  // no sqrt exists
        else  r = 1;  // (1/r)^2  = a mod 2
    }
    else        // case p odd
    {
        umod_t z = a % p;
        r = sqrt_modp(z, p);
        if ( r==0 )  return  0;  // no sqrt exists
    }
    // here r^2 == a (mod p)

    if ( 1==ex )  return  r;


    const umod_t m = ipow(p, ex);
    if ( 2==p )  // case p==2
    {
        ulong x = 1;
        while ( x<ex )  // Newton iteration for inverse sqrt, 2-adic case
        {
            umod_t z = a;
            z = mul_mod(z, r, m);  // a*r
            z = mul_mod(z, r, m);  // a*r*r
            z = sub_mod(3, z, m);  // 3 - a*r*r
            r = mul_mod(r, z/2, m);  // r*(3 - a*r*r)/2 = r*(1 + (1-a*r*r)/2)
            x *= 2;  //  (1/r)^2 == a mod 2^x
        }
        r = mul_mod(r, a, m);
    }
    else   // case p odd
    {
        const umod_t h = inv_modpp(2, p, ex);  // 1/2
        ulong x = 1;
        while ( x<ex )  // Newton iteration for square root
        {
            umod_t ri = inv_modpp(r, p, ex);    // 1/r
            umod_t ar = mul_mod(a, ri, m);      // a/r
            r = add_mod(r, ar, m);              // r+a/r
            r = mul_mod(r, h, m);               // (r+a/r)/2
            x *= 2;  //  r^2 == a mod p^x
        }
    }
    return  r;
}
// -------------------------


umod_t
sqrt_modf(umod_t a, const factorization &mf)
// Return sqrt(a) mod m, given the factorization mf of m
{
    ALLOCA(umod_t, x, mf.nprimes() );

    for (ulong i=0; i<mf.nprimes(); ++i)
    {
        // x[i]=sqrt(a) modulo i-th prime power:
        x[i] = sqrt_modpp( a, mf.prime(i), mf.exponent(i) );
        if ( x[i]==0 )  return 0;  // no sqrt exists
    }

    return  chinese(x, mf);  // combine via CRT
}
// -------------------------


