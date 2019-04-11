// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bpol/bitpolmod-arith.h"
#include "mod/factor.h"


ulong
gf2n_order(ulong g, ulong c, ulong h, const factorization &mfact)
// Return order of g \in GF(2**n) with field polynomial c.
// c must be irreducible
// h must be equal 1<<(deg(c)-1)
// mfact must contain the factorization of 2**deg(c)-1
// The routine may loop if either:
//  - the polynomial c is reducible
//  - deg(g) >= deg(c)
//  - h is not set correctly
//  - mfact is not set correctly
{
    if ( 0==g )  return 0;  // not in multiplicative group

    ulong m = mfact.product();
    ulong e = m;
    for (ulong i=0; i<mfact.nprimes(); ++i)
    {
        ulong p = mfact.prime(i);
        ulong f = mfact.primepow(i);

        e /= f;

        ulong g1 = bitpolmod_power(g, e, c, h);
        while ( g1!=1 )
        {
            g1 = bitpolmod_power(g1, p, c, h);
            e *= p;
        }
    }

    return e;
}
// -------------------------
