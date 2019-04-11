// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph.h"
#include "aux0/swap.h"

#include "fxttypes.h"


digraph *
make_debruijn_digraph(ulong n)
{
    ulong ng = 2*n, ne = 2*ng;
    ulong *ep, *e;
    digraph * dgp = new digraph(ng, ne, ep, e);

    ulong j = 0;
    for (ulong k=0; k<ng; ++k)  // for all nodes
    {
        ep[k] = j;
        ulong r = (2*k) % ng;
        e[j++] = r;  // connect node k to node (2*k) mod ng
        r = (2*k+1) % ng;
        e[j++] = r;  // connect node k to node (2*k+1) mod ng
    }
    ep[ng] = j;

    return  dgp;
}
// -------------------------


digraph *
make_complement_shift_digraph(ulong n)
{
    ulong ng = 2*n, ne = 2*ng;
    ulong *ep, *e;
    digraph * dgp = new digraph(ng, ne, ep, e);

    ulong i = 0;
    for (ulong k=0; k<ng; ++k)  // for all nodes
    {
        ep[k] = i;
        ulong r = (2*k) % ng;
        e[i++] = r;  // connect node k to node (2*k) mod ng
        r = (2*k+1) % ng;
        e[i++] = r;  // connect node k to node (2*k+1) mod ng
    }
    ep[ng] = i;
    // Here we have a De Bruijn graph.

    for (ulong k=0, j=ng-1;  k<j;  ++k, --j) swap2(e[ep[k]], e[ep[j]]);  // end with ones
    for (ulong k=0, j=ng-1;  k<j;  ++k, --j) swap2(e[ep[k]+1], e[ep[j]+1]);

    return  dgp;
}
// -------------------------


digraph *
make_debruijn_digraph(ulong n, ulong m)
// m-ary version
{
    ulong ng = m*n, ne = m*ng;
    ulong *ep, *e;
    digraph * dgp = new digraph(ng, ne, ep, e);

    ulong j = 0;
    for (ulong k=0; k<ng; ++k)  // for all nodes
    {
        ep[k] = j;
        for (ulong i=0; i<m; ++i)
        {
            ulong r = (m*k+i) % ng;
            e[j++] = r;  // connect node k to node (m*k+j) mod ng
        }
    }
    ep[ng] = j;

    return  dgp;
}
// -------------------------

