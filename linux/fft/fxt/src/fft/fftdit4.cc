// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
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
fft_dit4_core_p1(double *fr, double *fi, ulong ldn)
// Auxiliary routine for fft_dit4()
// Decimation in time (DIT) radix-4 FFT
// Input data must be in revbin_permuted order
// ldn := base-2 logarithm of the array length
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


    ulong ldm = (ldn&1);
    if ( ldm!=0 )  // n is not a power of 4, need a radix-8 step
    {
        for (ulong i0=0; i0<n; i0+=8)  fft8_dit_core_p1(fr+i0, fi+i0);
    }
    else
    {
        for (ulong i0=0; i0<n; i0+=4)
        {
            double xr, yr, ur, vr, xi, yi, ui, vi;
            ulong i1 = i0 + 1;
            ulong i2 = i1 + 1;
            ulong i3 = i2 + 1;

            sumdiff(fr[i0], fr[i1], xr, ur);
            sumdiff(fr[i2], fr[i3], yr, vi);
            sumdiff(fi[i0], fi[i1], xi, ui);
            sumdiff(fi[i3], fi[i2], yi, vr);

            sumdiff(ui, vi, fi[i1], fi[i3]);
            sumdiff(xi, yi, fi[i0], fi[i2]);
            sumdiff(ur, vr, fr[i1], fr[i3]);
            sumdiff(xr, yr, fr[i0], fr[i2]);
        }
    }
    ldm += 2*LX;


    for ( ; ldm<=ldn; ldm+=LX)
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
                cmult(c2, s2, fr[i1], fi[i1], xr, xi);

                sumdiff3_r(xr, fr[i0], ur);
                sumdiff3_r(xi, fi[i0], ui);

                cmult(c,  s,  fr[i2], fi[i2], yr, vr);
                cmult(c3, s3, fr[i3], fi[i3], vi, yi);

                sumdiff(yr, vi);
                sumdiff(yi, vr);

                sumdiff(ur, vr, fr[i1], fr[i3]);
                sumdiff(ui, vi, fi[i1], fi[i3]);
                sumdiff(xr, yr, fr[i0], fr[i2]);
                sumdiff(xi, yi, fi[i0], fi[i2]);
            }
        }
    }
}
// -------------------------


void
fft_dit4(double *fr, double *fi, ulong ldn, int is)
// Decimation in time (DIT) radix-4 FFT
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
{
    revbin_permute(fr, 1UL<<ldn);
    revbin_permute(fi, 1UL<<ldn);

    if ( is>0 )  fft_dit4_core_p1(fr, fi, ldn);
    else         fft_dit4_core_p1(fi, fr, ldn);
}
// -------------------------
