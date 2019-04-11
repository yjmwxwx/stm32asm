// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>

#include "fft/shortfft.h"  // fft8_dit_core_p1()
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "perm/revbinpermute.h"
#include "aux0/sincos.h"
#include "fxttypes.h"  // ulong


//static const ulong RX = 4;
static const ulong LX = 2;


void
fft_dif4_core_p1(double *fr, double *fi, ulong ldn)
// Auxiliary routine for fft_dif4().
// Decimation in frequency (DIF) radix-4 FFT.
// Output data is in revbin_permuted order.
// ldn := base-2 logarithm of the array length.
// Fixed isign = +1
{
    const ulong n = (1UL<<ldn);

    if ( n<=2 )
    {
        if ( n==2 )
        {
            sumdiff(fr[0], fr[1]);
            sumdiff(fi[0], fi[1]);
        }
        return;
    }

    for (ulong ldm=ldn; ldm>=(LX<<1); ldm-=LX)
    {
        ulong m = (1UL<<ldm);
        ulong m4 = (m>>LX);

        const double ph0 = 2.0 * M_PI / (double)m;
        double ph = 0.0;
        for (ulong j=0; j<m4; j++)
        {
            double c, s, c2, s2, c3, s3;
//            SinCos(j*ph0, &s, &c);
            SinCos(ph, &s, &c);
            ph += ph0;
            csqr(c, s, c2, s2);
            cmult(c, s, c2, s2, c3, s3);

            for (ulong r=0; r<n; r+=m)
            {
                ulong i0 = j + r;
                ulong i1 = i0 + m4;
                ulong i2 = i1 + m4;
                ulong i3 = i2 + m4;

                double xr, yr, ur, vr, xi, yi, ui, vi;

                // {x, u} = {f[i0]+f[i2], f[i0]-f[i2]}:
                sumdiff(fr[i0], fr[i2], xr, ur);
                sumdiff(fi[i0], fi[i2], xi, ui);

                // {y, v} = {f[i1]+f[i3], (f[i1]-f[i3])*(0,is)}:
                sumdiff(fi[i3], fi[i1], yi, vr);
                sumdiff(fr[i1], fr[i3], yr, vi);

                diffsum3(xr, yr, fr[i0]);
                diffsum3(xi, yi, fi[i0]);

                cmult(c2, s2, yr, yi, fr[i1], fi[i1]);

                sumdiff(ur, vr, xr, yr);
                sumdiff(ui, vi, xi, yi);

                cmult(c3, s3, yr, yi, fr[i3], fi[i3]);
                cmult(c,  s,  xr, xi, fr[i2], fi[i2]);
            }
        }
    }


    if ( (ldn&1)!=0 )  // n is not a power of 4, need a radix-8 step
    {
        for (ulong i0=0; i0<n; i0+=8)  fft8_dif_core_p1(fr+i0, fi+i0);
    }
    else
    {
        for (ulong i0=0; i0<n; i0+=4)
        {
            double xr, yr, ur, vr, xi, yi, ui, vi;
            ulong i1 = i0 + 1;
            ulong i2 = i1 + 1;
            ulong i3 = i2 + 1;

            sumdiff(fr[i0], fr[i2], xr, ur);
            sumdiff(fr[i1], fr[i3], yr, vi);
            sumdiff(fi[i0], fi[i2], xi, ui);
            sumdiff(fi[i3], fi[i1], yi, vr);

            sumdiff(xi, yi, fi[i0], fi[i1]);
            sumdiff(ui, vi, fi[i2], fi[i3]);
            sumdiff(xr, yr, fr[i0], fr[i1]);
            sumdiff(ur, vr, fr[i2], fr[i3]);
        }
    }
}
// -------------------------


void
fft_dif4(double *fr, double *fi, ulong ldn, int is)
// Decimation in frequency (DIF) radix-4 FFT.
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
{
    if ( is>0 )  fft_dif4_core_p1(fr, fi, ldn);
    else         fft_dif4_core_p1(fi, fr, ldn);

    revbin_permute(fr, 1UL<<ldn);
    revbin_permute(fi, 1UL<<ldn);
}
// -------------------------
