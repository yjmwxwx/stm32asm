// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph.h"

#include "sort/sort.h"
#include "sort/bsearch.h"
#include "bits/bitcombcolex.h"
#include "aux0/binomial.h"

#include "fxttypes.h"  // ulong

#include "jjassert.h"  // jjnote: asserts used in code: MTL graph


digraph *
make_mtl_digraph(ulong k, bool rq/*=0*/)
// Initialization for the "middle two levels" graph
{
    ulong k2 = 2*k-1;
    ulong ng = 2*binomial(k2, k);
    ulong ne = ng * k;  // number of edges
    if ( rq )  ne -= (k-1);

    ulong *ep, *e;
//    digraph dg(ng, ne, ep, e, true);
    digraph * dgp = new digraph(ng, ne, ep, e, true);
    digraph &dg = *dgp;

    ulong *vn = dg.vn_;
    ulong mask = first_comb(k2);
    ulong comb = first_comb(k);
    ulong nct = 0;  // Node counter
    do
    {
        vn[nct++] = comb;
        jjassert( nct < ng );
        vn[nct++] = mask & ~comb;
        comb = next_colex_comb(comb);
    }
    while ( comb < mask );
    jjassert( nct == ng );

    quick_sort(vn, ng);

    ulong p = 0;
    ulong j = 0;
    if ( rq )  // force path to start "canonically":
    {
        ulong x = k;
        ep[j] = p;  e[p++] = x;  ++j;  // 0000111 --> 0001111
//        print_bin(" 2nd= ", vn[x], pbn);  cout << endl;
        // #0   == 0000111
        // #1   == 0001011
        // #2   == 0001101
        // #3   == 0001110
        // #k+1 == 0001111
    }

    for (  ; j<ng; ++j)  // for all nodes
    {
        ep[j] = p;
        ulong v = vn[j];  // value of node
        for (ulong b=1;  0!=(b & mask);  b<<=1)
        {
            ulong vc = v ^ b;  // change one bit
            ulong x = bsearch(vn, ng, vc);
            if ( ng != x )
            {
                jjassert( p<ne );
                e[p++] = x;
            }
        }
    }
    ep[ng] = p;
    jjassert( p==ne );

    return  dgp;
}
// -------------------------
