// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bpol/bitpolmod-arith.h"
#include "mod/factor.h"

ulong
bitpol_el_order(ulong c, ulong h, const factorization &mfact, ulong a)
// Return order of A modulo polynomial C.
// C must be irreducible.
// h must be equal 1<<(deg(c)-1).
// mfact must contain the factorization of 2**deg(c)-1.
// The routine may loop if either:
//  - the polynomial C is reducible
//  - h is not set correctly
//  - mfact is not set correctly
{
    ulong e = mfact.product();
    for (ulong i=0; i<mfact.nprimes(); ++i)
    {
        ulong p = mfact.prime(i);
        ulong f = mfact.primepow(i);

        e /= f;

        ulong g1 = bitpolmod_power(a, e, c, h);
        while ( g1!=1 )
        {
            g1 = bitpolmod_power(g1, p, c, h);
            e *= p;
        }
    }

    return e;
}
// -------------------------

ulong
bitpol_order(ulong c, ulong h, const factorization &mfact)
// Return order of polynomial C.
// C must be irreducible.
// h must be equal 1<<(deg(c)-1).
// mfact must contain the factorization of 2**deg(c)-1.
// The routine may loop if either:
//  - the polynomial C is reducible
//  - h is not set correctly
//  - mfact is not set correctly
// Same as: bitpol_el_order(c, h, mfact, 2)
{
    ulong e = mfact.product();
    for (ulong i=0; i<mfact.nprimes(); ++i)
    {
        ulong p = mfact.prime(i);
        ulong f = mfact.primepow(i);

        e /= f;

        ulong g1 = bitpolmod_xpower(e, c, h);
        while ( g1!=1 )
        {
            g1 = bitpolmod_power(g1, p, c, h);
            e *= p;
        }
    }

    return e;
}
// -------------------------
