// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/fact2perm.h"  // rfact2perm()
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"


void
print_arrangement_rgs_perm(const char *bla,
                           const ulong *a, ulong n,
                           ulong *rfc,
                           ulong *p,
                           bool zb/*=false*/)
// The positions of nonzero digits determine the subset, and
//   their values (decreased by 1) are the (left) inversion table
//   (a rising factorial number) for the permutation.
{
    zb = !zb;

    ulong ns = 0;  // elements in set
    for (ulong j=0; j<n; ++j)
    {
        if ( a[j] != 0 )
        {
            p[ns] = j + zb;
            if ( ns!=0 )  // skip leading zero in inversion table
                rfc[ns-1] = a[j] - 1;
            ++ns;
        }
    }

    if ( ns>=2 )
        rfact2perm(rfc, ns, p, false);

    print_vec(bla, p, ns, false);
}
// -------------------------
