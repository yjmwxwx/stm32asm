// This file is part of the FXT library.
// Copyright (C) 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph-paths.h"
#include "graph/digraph.h"

#include "aux0/factorial.h"
#include "comb/num2perm.h"  // perm2num(), num2perm()
#include "perm/reverse.h"

#include "fxttypes.h"



digraph *
make_perm_pref_rev_digraph(ulong n)
// Initialization for directed graph:
// permutations are connected by prefix reversals
{
    ulong ng = factorial(n);

    ulong ne = ng * (n-1);  // number of edges
    ulong *ep, *e;
    digraph * dgp = new digraph(ng, ne, ep, e);


    ulong xx[32];  // aux: permutations
    ulong yy[32];  // aux: prefix-reversed permutations
    ulong p = 0;
    for (ulong k=0; k<ng; ++k)  // for all nodes
    {
        ep[k] = p;

        num2perm_ffact(k, xx, n);
        for (ulong j=2;  j<=n;  ++j)
        {
            for (ulong i=0; i<n; ++i)  yy[i] = xx[i];
            reverse(yy, j);

            ulong vc = perm2num_ffact(yy, n);
            e[p++] = vc;
        }
    }
    ep[ng] = p;

    return  dgp;
}
// -------------------------

