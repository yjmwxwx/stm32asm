// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph-paths.h"
#include "graph/digraph.h"

#include "bits/bitlow.h"
#include "bits/bitrotate.h"

#include "fxttypes.h"
#include "jjassert.h"  // jjnote: asserts used in code: Gray graph


digraph *
make_gray_digraph(ulong n, bool rq/*=0*/)
// Initialization for directed graph:
// Gray code graph for n-bit words.
{
    ulong ng = 1UL<<n;

    ulong ne = ng * n;  // number of edges
    ulong *ep, *e;
    digraph * dgp = new digraph(ng, ne, ep, e);

    ulong p = 0;
    ulong k = 0;
    if ( rq )  // force path to start as 0 1 3:
    {
        ep[k] = p;  e[p++] = 1;  ++k;  // 0 --> 1
        ep[k] = p;  e[p++] = 3;  ++k;  // 1 --> 3
    }

    for (  ; k<ng; ++k)  // for all nodes
    {
        ep[k] = p;
        for (ulong c=0, b=1;  c<n;  ++c, b<<=1)
        {
            ulong vc = k ^ b;  // change one bit
            e[p++] = vc;
        }
    }
    ep[ng] = p;

    return  dgp;
}
// -------------------------


ulong
start_monotonic_gray_path(digraph_paths &dp, ulong n)
// Let path start as (a canonical monotonic Gray path):
//
// Return number of positions marked.
//
// Example for 5 bits: (return==10)
// 0:  ..... 0  0
// 1:  ....1 1  1
// 2:  ...11 2  3
// 3:  ...1. 1  2
// 4:  ..11. 2  6
// 5:  ..1.. 1  4
// 6:  .11.. 2  12
// 7:  .1... 1  8
// 8:  11... 2  24
// 9:  1.... 1  16
{
    for (ulong k=0; k<dp.ng_; ++k)  dp.qq_[k] = 0;
    ulong ns = 0;
    jjassert( dp.mark(0, ns) );
    jjassert( dp.mark(1, ns) );
    if ( n>=2 )
    {
        jjassert( dp.mark(3, ns) );
        ulong *rv = dp.rv_;
        for (ulong k=3;  k<2*n; ++k)
        {
            ulong p = rv[k-2];
            p = bit_rotate_left(p, 1, n);
            jjassert( dp.mark(p, ns) );
        }
    }
    return  ns;
}
// -------------------------
