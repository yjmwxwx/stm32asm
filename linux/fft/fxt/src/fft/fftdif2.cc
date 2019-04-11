// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"
#include "aux0/csincos.h"
#include "perm/revbinpermute.h"

#include <cmath>  // M_PI


void
fft_depth_first_dif2(Complex *f, ulong ldn, int is)
// Decimation in frequency (DIF) radix-2 FFT, depth-first version.
// Compared to usual fft this one
// - does more trig computations
// - is (far) better memory local
{
    const ulong n = (1UL<<ldn);
    const double pi = is * M_PI;
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        const double phi = pi / (double)mh;
        for (ulong r=0; r<n; r+=m)
        {
            for (ulong j=0; j<mh; ++j)
            {
                ulong i0 = r + j;
                ulong i1 = i0 + mh;

                Complex u = f[i0];
                Complex v = f[i1];

                f[i0] = (u + v);
                f[i1] = (u - v) * SinCos( phi*(double)j );
            }
        }
    }

    revbin_permute(f, n);
}
// -------------------------


void
fft_dif2(Complex *f, ulong ldn, int is)
// Decimation in frequency (DIT) radix-2 FFT.
{
    const ulong n = (1UL<<ldn);
    const double pi = is * M_PI;
    for (ulong ldm=ldn; ldm>=1; --ldm)
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);
        const double phi = pi / (double)mh;
        for (ulong j=0; j<mh; ++j)
        {
            Complex w = SinCos( phi*(double)j );
            for (ulong r=0; r<n; r+=m)
            {
                ulong i0 = r + j;
                ulong i1 = i0 + mh;
                Complex u = f[i0];
                Complex v = f[i1];

                f[i0] = (u + v);
                f[i1] = (u - v) * w;
            }
        }
    }

    revbin_permute(f, n);
}
// -------------------------

