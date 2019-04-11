// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/factor.h"
#include "mod/primes.h"
#include "mod/numtheory.h"

#include "aux0/gcd.h"
#include "fxttypes.h"



//#define  MO_DEBUG  // define for debug
#ifdef MO_DEBUG
#warning '******** MO_DEBUG'
#include "jjassert.h"
#endif


umod_t
maxorder_mod(const factorization &modfact)
// Return the maximal order in the group of units (Z/mZ)*
// modfact must be the factorization of m.
//
// If  m = 2^e0 * \prod_i{p_i^{e_i}}  i=1...k
// Then maxorder = lcm(f0,f1,f2,...,fk)
// where f0 = 2^e0 if e0 \in {0,1,2}, else (2^e0)/2
// and fi = euler_phi(p_i^{e_i}) = (p_i-1) * p_i^{e_i-1}
{
    ulong k = 0;
    umod_t m = 1;
    if ( 2 == modfact.prime(0) )
    {
        ulong e = modfact.exponent(0);
        m = ( 1ULL << (e-1) );
        if ( modfact.exponent(0) >= 3 )  m >>= 1;
        k++;
    }

    while ( k < modfact.nprimes() )
    {
        umod_t f = euler_phi(modfact.prime(k), modfact.exponent(k));
        m = lcm(m, f);
        k++;
    }

    return  m;
}
// -------------------------


umod_t
maxorder_element_mod(const factorization &modfact,
                     const factorization &phifact)
// Return element of maximal order modulo m.
// modfact must be the factorization of m,
// phifact must be the factorization of euler_phi(m)
{
    umod_t m = modfact.product();
    if ( m==2 )  return  1;

    umod_t mo = maxorder_mod(modfact);
    for (umod_t x=2;  x<m;  ++x)
    {
        umod_t xo = order_mod(x, m, phifact);
        if ( mo == xo )  return  x;
    }

#ifdef MO_DEBUG
    // cannot happen, maxorder element is found before:
    cout << " m=" << m << "  mo=" << mo << endl;
    cout << " m=" << modfact.product() << " == " << modfact << endl;
    cout << " phi=" << phifact.product() << " == " << phifact << endl;

    jjassert( modfact.check() );
    jjassert( phifact.check() );

    jjassert( 0 );  // maxorder_element() failed.
#endif
    return  0;
}
// -------------------------
