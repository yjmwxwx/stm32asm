// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "mod/mod.h"
#include "perm/revbinpermute.h"
#include "bits/bit2pow.h"  // ld()


void
ntt_dit2l(mod *f, ulong ldn, int is)
//
// decimation in time
// revbin_permutes data at entry
//
{
    const ulong n = 1UL<<ldn;
    revbin_permute(f, n);

    const mod rn = mod::root2pow( (int)(is>0 ? ld(n) : -ld(n)) );

    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        ulong m = (1UL<<ldm);
        ulong mh = (m>>1);

        ulong x = (1UL<<(ldn-ldm));
        mod dw = rn.pow(x);  // "=" exp(2*pi*i/n)^(j*2^(ldn-ldm))
        mod w = mod::one;

        for (ulong j=0; j<mh; ++j)
        {
            for (ulong r=0; r<n; r+=m)
            {
                ulong t1 = r + j;
                ulong t2 = t1 + mh;

                mod v = f[t2] * w;
                mod u = f[t1];

                f[t1] = u + v;
                f[t2] = u - v;
            }
            w *= dw;
        }
    }
}
// -------------------------


void
ntt_dif2l(mod *f, ulong ldn, int is)
//
// decimation in frequency
// revbin_permutes data before exit
//
{
    const ulong n = 1UL<<ldn;
    const mod rn = mod::root2pow( (int)(is>0 ? ld(n) : -ld(n)) );

    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        ulong m = (1UL<<ldm);
        ulong mh = (m>>1);

        ulong x = (1UL<<(ldn-ldm));
        mod dw = rn.pow(x);  // "=" exp(2*pi*i/n)^(j*2^(ldn-ldm))
        mod w = mod::one;

        for (ulong j=0; j<mh; ++j)
        {
            for (ulong r=0; r<n; r+=m)
            {
                ulong t1 = r + j;
                ulong t2 = t1 + mh;

                mod v = f[t2];
                mod u = f[t1];

                f[t1] = (u + v);
                f[t2] = (u - v) * w;
            }
            w *= dw;
        }
    }

    revbin_permute(f, n);
}
// -------------------------
