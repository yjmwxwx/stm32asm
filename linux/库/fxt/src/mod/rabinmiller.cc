// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/primes.h"
#include "mod/mtypes.h"
#include "mod/modarith.h"

#include "fxttypes.h"


void
n2qt(const umod_t n, umod_t &q, uint &t)
// Set q,t so that  n == q * 2^t + 1
// n must not equal 1, else routine loops.
{
    q = n - 1;  t = 0;
    while ( 0==(q & 1) )  { q >>= 1; ++t; }
}
// -------------------------


bool
is_strong_pseudo_prime(const umod_t n, const umod_t a, const umod_t q, const uint t)
// Return whether n is a strong pseudoprime to base a.
// q and t must be set so that  n == q * 2^t + 1
{
    umod_t b = pow_mod(a, q, n);

    if ( 1==b )  return true;  // passed
    // if ( n-1==b )  return true;  // passed

    uint e = 1;
    while ( (b!=1) && (b!=(n-1)) && (e<t) )
    {
        b = mul_mod(b, b, n);
        e++;
    }
//    cout << "is_strong_pseudo_prime: b=" << b << " e=" << e << endl;

    if ( b!=(n-1) )  return false;  // =--> composite

    return  true;  // passed
}
// -------------------------


bool
rabin_miller(umod_t n, uint cm/*=0*/)
// Miller-Rabin compositeness test.
// Return true of none of the bases <=cm prove compositeness.
// If false is returned, then n is proven composite (also for n=1 or n=0).
// If true is returned the probability
//   that n is composite is less than (1/4)^cm
//.
// cf. Cohen p.414
{
    if ( n<=1 )  return false;
    if ( n < small_prime_limit )  return  is_small_prime( (ulong)n );

    umod_t q;  uint t;
    n2qt(n, q, t);

//    cout << "rabin_miller: q=" << q << " t=" << t << endl;

    if ( 0==cm )  cm = 20;  // default
    uint c = 0;
    while ( ++c <= cm )
    {
        umod_t a = c + 1;
//        cout << "rabin_miller: n=" << n << " a=" << a << endl;

        // if n is a c-SPP, then it also is a c**k (k>1) SPP.
        // That is, powers of a non-witness are non-witnesses.
        // So we skip perfect powers:
        if ( is_small_perfpow((ulong)a) )  continue;  // jjcast

        if ( a >= n )  return  true;
        if ( !is_strong_pseudo_prime(n, a, q, t) )
        {
//            cout << "rabin_miller: WITNESS  a=" << a << endl;
            return false;  // proven composite
        }
    }

    return true;  // strong pseudoprime for all tested bases
}
// -------------------------
