// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph.h"

#include "bits/parenwords.h"  // is_parenword()

#include "bits/bitcombcolex.h"  // next_colex_comb()
#include "bits/bitcount.h"  // bit_count()
#include "bits/bitrotate.h"  // bit_rotate_left()
#include "perm/reverse.h"  // reverse()
#include "aux1/copy.h"  // acopy()

#include "jjassert.h"  // jjnote: asserts used in code: paren gray graph

#include "fxttypes.h"


static ulong Catalan[]=
{
    0UL, 1UL, 2UL, 5UL, 14UL, 42UL, 132UL, 429UL, 1430UL, 4862UL, 16796UL,
    58786UL, 208012UL, 742900UL, 2674440UL, 9694845UL, 35357670UL
//    129644790UL, 477638700UL, 1767263190UL, 6564120420UL };
};
// -------------------------

static bool
parengray_is_neighbor(ulong fk, ulong fj, ulong pcd, ulong /*nb*/)
{
    ulong xr = fj^fk;
    bool q = false;
    if ( 2==bit_count( xr ) )
    {
        switch ( pcd )
        {
        case 0:  // Gray:
            q = true;  break;
        case 1:  // changes '11' and '101' only (paths ex. for all n):
            if ( (xr&(xr>>1)) || (xr&(xr>>2)) )  q = true;
            break;
        case 2:  // changes '11' only (path exists for n=6):
            if ( xr & (xr>>1) )  q = true;
            break;
        default:  jjassert(0);  // criterion does not exist;
        }
    }

    return q;
}
// -------------------------


digraph *
make_parengray_digraph(ulong nb, ulong pcd)
{
    ulong n = Catalan[nb];
    ulong *f = new ulong[n];
    {
        ulong k = 0;
        ulong c = last_comb(nb, 2*nb);
        do
        {
            if ( is_parenword(c) )
            {
                f[k++] = c;
//                jjassert( k<=n );
//                if ( k>=n )  break;
            }
        }
        while ( (c = prev_colex_comb(c)) );
        jjassert( k==n );
        reverse(f, n);
    }

    ulong nc = 0;
    for (ulong k=0; k<n; ++k)  // count number of edges
    {
        ulong fk = f[k];
        for (ulong j=0; j<n; ++j)
        {
            if ( j==k )  continue;
            ulong fj = f[j];
            if ( parengray_is_neighbor(fk, fj, pcd, nb) )  ++nc;
        }
    }

    ulong *cp = new ulong[n+1];
    ulong *c = new ulong[nc];
    nc = 0;
    for (ulong k=0; k<n; ++k)  // fill in edges
    {
        cp[k] = nc;
        ulong fk = f[k];
        for (ulong j=0; j<n; ++j)
        {
            if ( j==k )  continue;
            ulong fj = f[j];
            if ( parengray_is_neighbor(fk, fj, pcd, nb) )  c[nc++] = j;
        }
    }
    cp[n] = nc;




//    digraph(ulong ng, ulong ne, ulong *&ep, ulong *&e, bool vnq=false)
    ulong *ep, *e;
//    digraph dg(n, nc, ep, e, 1);
    digraph *dgp = new digraph(n, nc, ep, e, 1);
    digraph &dg = *dgp;

    acopy(f, dg.vn_, n);
    acopy(c, dg.e_, nc);
    acopy(cp, dg.ep_, n+1);

    delete [] c;
    delete [] cp;
    delete [] f;

    return  dgp;
}
// -------------------------
