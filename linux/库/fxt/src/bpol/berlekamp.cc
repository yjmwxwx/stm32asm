// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "bpol/bitpol-factor.h"
#include "bpol/bitpol-arith.h"
#include "bpol/bitpol-gcd.h"
#include "bpol/bitpol-degree.h"
#include "bpol/bitpolmod-arith.h"
#include "bmat/bitmat-funcs.h"
#include "bmat/bitmat-inline.h"

//#include "jjassert.h"

#include "fxtalloca.h"
#include "fxttypes.h"


void
setup_q_matrix(ulong c, ulong d, ulong *ss)
// Compute the Q-matrix for the degree-d polynomial c.
// Used in Berlekamp's factorization algorithm.
{
    ulong h = 1UL << (d-1);
    {
        ulong x2 = 2UL;  // == 'x'
        ulong q = 1UL;
        x2 = bitpolmod_mult(x2, x2, c, h);
        for (ulong k=0;  k<d;  ++k)
        {
            ss[k] = q;
            q = bitpolmod_mult(q, x2, c, h);
        }
        bitmat_transpose(ss, d, ss);
    }
}
// -------------------------


ulong
bitpol_refine_factors(ulong *f, ulong nf, const ulong *nn, ulong r)
// Given the nullspace nn[0,...,r-1] of (Q-id)
// and nf factors f[0,...,nf-1] whose product equals c
// (typically nf=1 and f[0]==c)
// then get all r irreducible factors of c.
{
    ALLOCA(ulong, ss, r);
    for (ulong j=0; j<r; ++j)  // for all elements t in nullspace
    {
        ulong t = nn[j];

        // skip trivial elements in nullspace:
        if ( bitpol_deg(t)==0 )  continue;

        ulong sc = 0;
        for (ulong b=0; b<nf; ++b)  // for all elements bv in set
        {
            ulong bv = f[b];
            ulong db = bitpol_deg(bv);
            if ( db <= 1 )  // bv cannot be reduced
            {
                ss[sc++] = bv;
            }
            else
            {
                for (ulong s=0; s<2; ++s)  // for all elements in GF(2)
                {
                    ulong ti = t ^ s;
                    ulong g = bitpol_gcd(bv, ti);
                    if ( bitpol_deg(g) >= 1 )  ss[sc++] = g;
                }
            }
        }

//        jjassert( sc>=nf );
        nf = sc;
        for (ulong k=0; k<nf; ++k)  f[k] = ss[k];

        if ( nf>=r )  break;  // done
        // nf>r would be an error
    }
//    jjassert( r == nf );

    return nf;
}
// -------------------------


ulong
bitpol_factor_squarefree(ulong c, ulong *f)
// Fill irreducible factors of square-free polynomial c into f[]
// Return number of factors.
//.
// Berlekamp's algorithm:  nullspace of (Q-matrix - id).
{
    ulong d = bitpol_deg(c);

    if ( d<=1 )  // trivial cases:  0, 1, x, x+1
    {
        f[0] = c;
        if ( 0==c )  d = 1;  // 0==0^1
        return d;
    }

    ALLOCA(ulong, ss, d);
    setup_q_matrix(c, d, ss);
    bitmat_add_unit(ss, d);

    ALLOCA(ulong, nn, d);
    ulong r = bitmat_nullspace(ss, d, nn);

    f[0] = c;
    ulong nf = 1;
    if ( r>1 )  bitpol_refine_factors(f, nf, nn, r);
//    jjassert( r == nf );

    return r;
}
// -------------------------
