// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"
#include "aux0/csincos.h"
#include "perm/revbinpermute.h"

#include <cmath>  // M_PI


//static const ulong RX = 4;
static const ulong LX = 2;


void
fft_dit4l(Complex *f, ulong ldn, int is)
// Decimation in time (DIT) radix-4 FFT.
// Non-optimized learners version.
{
    double s2pi = ( is>0 ? 2.0*M_PI : -2.0*M_PI );

    const ulong n = (1UL<<ldn);

    revbin_permute(f, n);

    ulong ldm = (ldn&1);

    if ( ldm!=0 )  // n is not a power of 4, need a radix-2 step
    {
        for (ulong r=0; r<n; r+=2)
        {
            Complex a0 = f[r];
            Complex a1 = f[r+1];

            f[r]   = a0 + a1;
            f[r+1] = a0 - a1;
        }
    }

    ldm += LX;

    for ( ; ldm<=ldn ; ldm+=LX)
    {
        ulong m = (1UL<<ldm);
        ulong m4 = (m>>LX);
        double ph0 = s2pi / (double)m;

        for (ulong j=0; j<m4; j++)
        {
            double phi = (double)j * ph0;
            Complex e  = SinCos(phi);
            Complex e2 = SinCos(2.0*phi);
            Complex e3 = SinCos(3.0*phi);

            for (ulong r=0; r<n; r+=m)
            {
                ulong i0 = j + r;
                ulong i1 = i0 + m4;
                ulong i2 = i1 + m4;
                ulong i3 = i2 + m4;

                Complex a0 = f[i0];
                Complex a1 = f[i2];  // (!)
                Complex a2 = f[i1];  // (!)
                Complex a3 = f[i3];

                a1 *= e;
                a2 *= e2;
                a3 *= e3;

                Complex t0 = (a0+a2) + (a1+a3);
                Complex t2 = (a0+a2) - (a1+a3);

                Complex t1 = (a0-a2) + Complex(0, is) * (a1-a3);
                Complex t3 = (a0-a2) - Complex(0, is) * (a1-a3);

                f[i0] = t0;
                f[i1] = t1;
                f[i2] = t2;
                f[i3] = t3;
            }
        }
    }
}
// -------------------------
