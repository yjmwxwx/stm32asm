// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph-paths.h"
#include "graph/digraph.h"

#include "aux0/swap.h"
#include "aux0/factorial.h"
#include "comb/num2perm.h"  // perm2num(), num2perm()
#include "perm/perminvert.h"

#include "sort/minmaxmed23.h"
#include "sort/sort.h"

//#include "comb/perm-trotter2.h"

#include "fxttypes.h"


static inline void star_swap(ulong *x, ulong c)
{
    // star transpositions:
    swap2( x[0], x[c] );
}
// -------------------------


static inline void adj_swap(ulong *x, ulong c)
{
    // adjacent transpositions:
    swap2(x[c-1], x[c]);
}
// -------------------------

digraph *
make_perm_gray_digraph(ulong n, bool stq)
// Initialization for directed graph:
// Gray code permutations of n elements
// with star transpositions if stq==true,
// otherwise with adjacent changes.
{
    ulong ng = factorial(n);
    ulong ne = ng * (n-1);  // number of edges
    ulong *ep, *e;
    digraph * dgp = new digraph(ng, ne, ep, e);

    ulong xx[32];  // permutations
    ulong p = 0;
    for (ulong k=0; k<ng; ++k)  // for all nodes
    {
        ep[k] = p;
        num2perm_rfact(k, xx, n);

        for (ulong j=1;  j<n;  ++j)
//        for (ulong j=n-1;  j!=0;  --j)
        {
            if ( stq ) star_swap(xx, j);
            else       adj_swap(xx, j);

            ulong vc = perm2num_rfact(xx, n);
            e[p++] = vc;

            // unswap:
            if ( stq ) star_swap(xx, j);
            else       adj_swap(xx, j);
        }
    }
    ep[ng] = p;

    return  dgp;
}
// -------------------------

