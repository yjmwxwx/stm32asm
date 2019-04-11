// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "graph/digraph.h"

#include "bits/fibrep.h"  // bin2fibrep()
#include "bits/bit2pow.h"  // one_bit_q()
#include "aux1/copy.h"  // acopy()

//#include "jjassert.h"
//#include "fxtio.h"

#include "fxttypes.h"



digraph *
make_fibrepgray_digraph(ulong n)
{
    ulong *f = new ulong[n];
    for (ulong k=0; k<n; ++k)  f[k] = bin2fibrep(k);

    ulong nc = 0;
    for (ulong k=0; k<n; ++k)
    {
        ulong fk = f[k];
        for (ulong j=0; j<n; ++j)
        {
            if ( j==k )  continue;
            ulong fj = f[j];
            if ( one_bit_q( fj^fk ) )  ++nc;
        }
    }

    ulong *ep, *e;
    digraph * dgp = new digraph(n, nc, ep, e, 1);
    digraph &dg = *dgp;
    acopy(f, dg.vn_, n);

    ulong tnc = 0;
    for (ulong k=0; k<n; ++k)
    {
        ep[k] = tnc;
        ulong fk = f[k];
        for (ulong j=0; j<n; ++j)
        {
            if ( j==k )  continue;
            ulong fj = f[j];
            if ( one_bit_q( fj^fk ) )  e[tnc++] = j;
        }
    }
//    jjassert( nc == tnc );
    ep[n] = tnc;


    delete [] f;

    return  dgp;
}
// -------------------------
