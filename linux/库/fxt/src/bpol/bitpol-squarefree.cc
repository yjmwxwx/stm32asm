// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpol-arith.h"
#include "bpol/bitpol-gcd.h"
#include "bpol/bitpol-squarefree.h"
//#include "jjassert.h"
#include "fxttypes.h"  // ulong

ulong
bitpol_sreduce(ulong c)
// Let c == \prod_{k}{E_k} * (\prod_{j}{S_j^{s_j}})^{2^x}
// where E_k, S_j are irreducible factors
// and the E_k are not necessarily distinct from the S_j.
//
// Return polynomial f where
// f = \prod_{k}{E_k} * (\prod_{j}{S_j^{s_j}})^{1}
//
// Call repeatedly until the returned polynomial
// equals c to remove all even exponents.
{
    ulong s = bitpol_test_squarefree(c);
    if ( 0==s )  return c;  // c is square-free

    ulong f = bitpol_div(c, s);

//    jjassert( bitpol_pure_square_q(s) );
    do  // here s is a pure square and s>1
    {
        s = bitpol_pure_sqrt(s);
    }
    while ( bitpol_pure_square_q(s) );

    ulong g = bitpol_gcd(s, f);
    s = bitpol_div(s, g);
    f = bitpol_mult(f, s);

//    jjassert( f==bitpol_gcd(f, c) );

    return f;
}
// -------------------------


ulong
bitpol_factor_squarefree(ulong c, ulong *sf, ulong *se)
// Set sf[], se[] so that
// c == \prod_{i}{sf[i]^se[i]}
// where all sf[i] are square-free.
// Return number of factors.
//.
// Algorithm as given by Cohen
{
    ulong fct = 0;  // count factors
    ulong e = 1;
    ulong t0 = c;

 step2:
    if ( t0<2 )  return fct;
    ulong d = bitpol_deriv(t0);
    ulong t = bitpol_gcd(t0, d);
    ulong v = bitpol_div(t0, t);
    ulong k = 0;

 step3:
    if ( v<2 )
    {
        t0 = bitpol_pure_sqrt(t);
        e *= 2;
        goto step2;
    }

    // step4:
    ++k;
    if ( 0==(k&1) )  t = bitpol_div(t, v);

    // step5:
    ulong w = bitpol_gcd(t, v);

    ulong ek = e*k;
    ulong s = bitpol_div(v, w);
    if ( s>1 )
    {
        sf[fct] = s;
        se[fct] = ek;
        ++fct;
        v = w;
        t = bitpol_div(t, v);
        goto step3;
    }
    return fct;
}
// -------------------------
