// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph.h"

#include "fxttypes.h"
//#include "jjassert.h"


digraph *
make_complete_digraph(ulong n)
// Initialization for the complete graph.
{
    ulong ng = n, ne = n*(n-1);

    ulong *ep, *e;
//    digraph dg(ng, ne, ep, e);
    digraph * dgp = new digraph(ng, ne, ep, e);

    ulong j = 0;
    for (ulong k=0; k<ng; ++k)  // for all nodes
    {
        ep[k] = j;
        for (ulong i=0; i<n; ++i)  // connect to all nodes
        {
            if ( k==i )  continue;  // skip loops
            e[j++] = i;
        }
    }
    ep[ng] = j;
//    jjassert( j<=ne );

    return  dgp;
}
// -------------------------

