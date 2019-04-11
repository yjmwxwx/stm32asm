// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"
#include "aux0/csincos.h"
#include "perm/revbinpermute.h"

#include <cmath>  // M_PI


void
fft_depth_first_dit2(Complex *f, ulong ldn, int is)
// Decimation in time (DIT) radix-2 FFT, depth-first version.
// Compared to usual FFT this one
// - does more trig computations
// - is (far) better memory local
{
    const ulong n = 1UL<<ldn;
    const double pi = is * M_PI;

    revbin_permute(f, n);

    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        const double phi = pi/(double)(mh);
        for (ulong r=0; r<n; r+=m)
        {
            for (ulong j=0; j<mh; ++j)
            {
                ulong i0 = r + j;
                ulong i1 = i0 + mh;

                Complex u = f[i0];
                Complex v = f[i1] *  SinCos( phi * (double)j );

                f[i0] = u + v;
                f[i1] = u - v;
            }
        }
    }
}
// -------------------------


void
fft_dit2(Complex *f, ulong ldn, int is)
// Decimation in time (DIT) radix-2 FFT.
{
    const ulong n = 1UL<<ldn;
    const double pi = is * M_PI;

    revbin_permute(f, n);

    for (ulong ldm=1; ldm<=ldn; ++ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        const double phi = pi / (double)mh;
        for (ulong j=0; j<mh; ++j)
        {
            Complex w = SinCos( phi * (double)j );
            for (ulong r=0; r<n; r+=m)
            {
                ulong i0 = r + j;
                ulong i1 = i0 + mh;

                Complex u = f[i0];
                Complex v = f[i1] * w;

                f[i0] = u + v;
                f[i1] = u - v;
            }
        }
    }
}
// -------------------------

