// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/numtheory.h"
#include "mod/factor.h"

#include "aux0/ipow.h"
#include "fxttypes.h"


umod_t
euler_phi(umod_t n)
{
    factorization ff(n);
    return  euler_phi(ff);
}
// -------------------------

umod_t
euler_phi(umod_t pr, ulong ex)
{
    umod_t v = pr - 1;
    if ( ex>1 )  v *= ipow(pr, ex-1);
    return v;
}
// -------------------------

umod_t
euler_phi(const factorization &ff)
//
// let f = \prod_i{p_i^{e_i}}
// then euler_phi(f) =
//  == \prod_i{ euler_phi(p_i^{e_i}) }
//  == \prod_i{ p_i^{e_i}-p_i^{e_i-1} }
//  == \prod_i{ (p_i-1) * p_i^{e_i-1} }
//
{
    umod_t p = 1;
    for (ulong i=0; i<ff.nprimes(); ++i)
    {
        p *= euler_phi(ff.prime(i), ff.exponent(i) );
    }

    return p;
}
// -------------------------
