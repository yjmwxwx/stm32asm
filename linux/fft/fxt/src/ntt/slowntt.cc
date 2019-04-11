// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/mod.h"
#include "bits/bit2pow.h"  // ld()

#include "fxttypes.h"
#include "fxtalloca.h"


void
slow_ntt(mod *f, ulong n, int is)
//
// Number theoretic transform by definition (slow!)
//
{
    const mod rn = mod::root2pow( (int)(is>0 ? ld(n) : -ld(n)) );

    ALLOCA(mod, g, n);
    for (ulong k=0; k<n; ++k)
    {
        mod t = mod::zero;
        mod w = mod::one;
        mod dw = rn.pow(k);

        for (ulong x=0; x<n; ++x)
        {
            t += (w*f[x]);
            w *= dw;
        }

        g[k] = t;
    }

    for (ulong x=0; x<n; ++x)  f[x] = g[x];
}
// -------------------------
