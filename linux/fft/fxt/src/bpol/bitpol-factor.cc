// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/bitpol-factor.h"
#include "bpol/bitpol-irred.h"
#include "bpol/bitpol-squarefree.h"
#include "bpol/bitpol-degree.h"

//#include "jjassert.h"

#include "aux0/swap.h"

#include "fxttypes.h"


ulong
bitpol_factor(ulong c, ulong *f, ulong *e)
// Factorize the binary polynomial c:
// c = \prod_{i=0}^{fct-1}{f[i]^e[i]}
// The number of factors (fct) is returned.
{
    ulong d = bitpol_deg(c);
    if ( d<=1 )  // trivial cases:  0, 1, x, x+1
    {
        f[0] = c;
        if ( 0==c )  d = 1;  // 0==0^1
        return  d;
    }

    // get square-free part:
    ulong cf = bitpol_make_squarefree(c);

    // ... and factor it:
    ulong fct = bitpol_factor_squarefree(cf, f);

    // All exponents are one:
    for (ulong j=0; j<fct; ++j)  { e[j] = 1; }

    // Here f[], e[] is a valid factorization of the square-free part cf

    // Update exponents with square part:
    ulong cs = bitpol_div(c, cf);
    for (ulong j=0; j<fct; ++j)
    {
        if ( 1==cs )  break;
        ulong fj = f[j];
        ulong g = bitpol_gcd(cs, fj);
        while ( 1!=g )
        {
            ++e[j];
            cs = bitpol_div(cs, fj);
            if ( 1==cs )  break;
            g = bitpol_gcd(cs, fj);
        }
    }
//    jjassert( 1==cs );

    return fct;
}
// -------------------------

void
bitpol_sort_factorization(ulong *f, ulong *e, ulong fct)
// sort wrt. to irreducible factors.
{
    const ulong n = fct;
    for (ulong i=0; i<n; ++i)  // selection sort
    {
        ulong v = f[i];
        ulong m = i;  // position of minimum
        ulong j = n;
        while ( --j > i )  // search (index of) minimum
        {
            if ( f[j]<v )
            {
                m = j;
                v = f[m];
            }
        }

        swap2(f[i], f[m]);
        swap2(e[i], e[m]);
    }
}
// -------------------------


ulong
bitpol_test_factorization(ulong c, const ulong *f, const ulong *e, ulong fct, ulong &fi)
// Test whether  c == \prod_{i=0, 1, ..., fct-1}{f[i]^e[i]}
// with all f[i] irreducible.
// Returns zero if factorization is ok, else
// the first index such that an error occured
//   with f[i]^e[i] is written to fi
// and the return value indicates the type of error:
//   1: failure with trivial factorization (c should be zero or one)
//   2: factor f[fi] is reducible
//   3: f[fi] does not divide c
//   4: f[fi]^e[fi] does not divide c
//   5: product != c
{
    if ( 0==c )
    {
        if ( (1==fct) && (1==f[0]) && (1==e[0]) )  return 0;
        return 1;
    }

    if ( 1==c )
    {
        if ( fct!=0 )  return 1;
    }

    ulong p = 1;
    for (ulong i=0; i<fct; ++i)
    {
        fi = i;
        ulong z = f[i];
        ulong hz = bitpol_h(z);
        if ( 0==bitpol_irreducible_q(z, hz) )  return 2;
        if ( bitpol_gcd(c, z)!=z )  return 3;
        z = bitpol_power(z, e[i]);
        if ( bitpol_gcd(c, z)!=z )  return 4;
        p = bitpol_mult(p, z);
    }

    if ( p!=c )  return 5;

    return 0;
}
// -------------------------

