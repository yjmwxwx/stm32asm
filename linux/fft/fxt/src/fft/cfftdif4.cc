// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>

#include "fft/shortfft.h"  // fft8_dit_core_*()
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "perm/revbinpermute.h"
#include "aux0/csincos.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


//static const ulong RX = 4;
static const ulong LX = 2;


void
fft_dif4_core_p1(Complex *f, ulong ldn)
// Auxiliary routine for fft_dif4().
// Radix-4 decimation in frequency (DIF) FFT, fixed isign = +1
// Output data is in revbin_permuted order.
// ldn := base-2 logarithm of the array length.
{
    const ulong n = (1UL<<ldn);

    if ( n<=2 )
    {
        if ( n==2 )  sumdiff(f[0], f[1]);
        return;
    }

    for (ulong ldm=ldn; ldm>=(LX<<1); ldm-=LX)
    {
        ulong m = (1UL<<ldm);
        ulong m4 = (m>>LX);

        const double ph0 = 2.0 * M_PI / (double)m;  // isign
        double ph = 0.0;
        for (ulong j=0; j<m4; j++)
        {
//            double phi = (double)j * ph0;
//            Complex e  = SinCos(phi);
            Complex e  = SinCos(ph);
            ph += ph0;

            Complex e2 = e * e;
            Complex e3 = e2 * e;

            for (ulong r=0; r<n; r+=m)
            {
                ulong i0 = j + r;
                ulong i1 = i0 + m4;
                ulong i2 = i1 + m4;
                ulong i3 = i2 + m4;

                Complex x, y, u, v;
                sumdiff(f[i0], f[i2], x, u);
                sumdiff(f[i1], f[i3], y, v);
                v *= Complex(0, +1);  // isign

                diffsum3(x, y, f[i0]);
                f[i1] = y * e2;

                sumdiff(u, v, x, y);
                f[i3] = y * e3;
                f[i2] = x * e;
            }
        }
    }


    if ( ldn & 1 )  // n is not a power of 4, need a radix-8 step
    {
        for (ulong i0=0; i0<n; i0+=8)  fft8_dif_core_p1(f+i0);  // isign
    }
    else
    {
        for (ulong i0=0; i0<n; i0+=4)
        {
            ulong i1 = i0 + 1;
            ulong i2 = i1 + 1;
            ulong i3 = i2 + 1;

            Complex x, y, u, v;
            sumdiff(f[i0], f[i2], x, u);
            sumdiff(f[i1], f[i3], y, v);
            v *= Complex(0, +1);  // isign
            sumdiff(x, y, f[i0], f[i1]);
            sumdiff(u, v, f[i2], f[i3]);
        }
    }
}
// -------------------------


void
fft_dif4_core_m1(Complex *f, ulong ldn)
// Auxiliary routine for fft_dif4().
// Radix-4 decimation in frequency (DIF) FFT, fixed isign = -1
// Output data is in revbin_permuted order.
// ldn := base-2 logarithm of the array length
{
    const ulong n = (1UL<<ldn);

    if ( n<=2 )
    {
        if ( n==2 )  sumdiff(f[0], f[1]);
        return;
    }

    for (ulong ldm=ldn; ldm>=(LX<<1); ldm-=LX)
    {
        ulong m = (1UL<<ldm);
        ulong m4 = (m>>LX);

        const double ph0 = -2.0 * M_PI / (double)m;  // isign
        double ph = 0.0;
        for (ulong j=0; j<m4; j++)
        {
//            double phi = (double)j * ph0;
//            Complex e  = SinCos(phi);
            Complex e  = SinCos(ph);
            ph += ph0;

            Complex e2 = e * e;
            Complex e3 = e2 * e;

            for (ulong r=0; r<n; r+=m)
            {
                ulong i0 = j + r;
                ulong i1 = i0 + m4;
                ulong i2 = i1 + m4;
                ulong i3 = i2 + m4;

                Complex x, y, u, v;
                sumdiff(f[i0], f[i2], x, u);
                sumdiff(f[i1], f[i3], y, v);
                v *= Complex(0, -1);  // isign

                diffsum3(x, y, f[i0]);
                f[i1] = y * e2;

                sumdiff(u, v, x, y);
                f[i3] = y * e3;
                f[i2] = x * e;
            }
        }
    }


    if ( ldn & 1 )  // n is not a power of 4, need a radix-8 step
    {
        for (ulong i0=0; i0<n; i0+=8)  fft8_dif_core_m1(f+i0);  // isign
    }
    else
    {
        for (ulong i0=0; i0<n; i0+=4)
        {
            ulong i1 = i0 + 1;
            ulong i2 = i1 + 1;
            ulong i3 = i2 + 1;

            Complex x, y, u, v;
            sumdiff(f[i0], f[i2], x, u);
            sumdiff(f[i1], f[i3], y, v);
            v *= Complex(0, -1);  // isign
            sumdiff(x, y, f[i0], f[i1]);
            sumdiff(u, v, f[i2], f[i3]);
        }
    }
}
// -------------------------


void
fft_dif4(Complex *f, ulong ldn, int is)
// Fast Fourier Transform
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
// radix-4 decimation in frequency algorithm
{
    if ( is>0 )  fft_dif4_core_p1(f, ldn);
    else         fft_dif4_core_m1(f, ldn);
    revbin_permute(f, 1UL<<ldn);
}
// -------------------------

