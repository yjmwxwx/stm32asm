// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>

#include "fxttypes.h"
#include "aux0/sincos.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "perm/revbinpermute.h"

// tuning parameter:
//#define USE_SINCOS3  // default = off
// whether sincos is used for 3*angle
// else: use algebraic relation
//
// sin & cos of triple angle by algebra:
#define SINCOS3ALG(c, s, c3, s3)  { c3 = 4.0*c*(c*c-0.75); s3=4.0*s*(0.75-s*s); }


void
split_radix_fft_dif_core(double *fr, double *fi, ulong ldn)
// Auxiliary routine for split_radix_fft_dif().
//
// Split-radix decimation in frequency (DIF) FFT.
// Output data is in revbin_permuted order.
// ldn := base-2 logarithm of the array length.
// fixed isign == -1
//.
// cf: Duhamel-Hollman, Electronics Letters, Jan. 5, 1984
// orig by: Dave Edelblute, edelblut@cod.nosc.mil, 05 Jan 1993
// modified: R. Mayer
// heavily modified: Joerg Arndt, arndt@jjj.de
//
{
    if ( 0==ldn )  return;

    const ulong n = (1UL<<ldn);
    ulong n2 = 2 * n;
    for (ulong k=0; k<ldn; k++)
    {
        n2 >>= 1;
        ulong n4 = n2 >> 2;
        double e = 2.0 * M_PI / (double)n2;
        for (ulong j=0; j<n4; j++)
        {
            double a = (double)j * e;
            double cc1, ss1, cc3, ss3;
            SinCos(a, &ss1, &cc1);

#if defined USE_SINCOS3
            SinCos(3.0*a, &ss3, &cc3);
#else
            SINCOS3ALG(cc1, ss1, cc3, ss3);
#endif

            ulong ix = j;
            ulong id = (n2<<1);
            while ( ix<n )
            {
                for (ulong i0=ix; i0<n; i0+=id)
                {
                    ulong i1 = i0 + n4;
                    ulong i2 = i1 + n4;
                    ulong i3 = i2 + n4;

                    double tr0, tr1;
                    sumdiff3(fr[i0], fr[i2], tr0);
                    sumdiff3(fr[i1], fr[i3], tr1);

                    double ti0, ti1;
                    sumdiff3(fi[i0], fi[i2], ti0);
                    sumdiff3(fi[i1], fi[i3], ti1);

                    double t3, t4;
                    sumdiff3(tr0, ti1, t3);
                    tr0 = -tr0;

                    sumdiff3_r(tr1, ti0, t4);

                    cmult(ss1, cc1, t4, tr0, fr[i2], fi[i2]);

                    cmult(cc3, ss3, tr1, t3, fi[i3], fr[i3]);
               }

               ix = (id<<1) - n2 + j;
               id <<= 2;
            }
        }
    }

    for (ulong ix=0, id=4;  ix<n;  id*=4)
    {
        for (ulong i0=ix; i0<n; i0+=id)  sumdiff(fr[i0], fr[i0+1]);

        ix = 2*(id-1);
    }

    for (ulong ix=0, id=4;  ix<n;  id*=4)
    {
        for (ulong i0=ix; i0<n; i0+=id)  sumdiff(fi[i0], fi[i0+1]);

        ix = 2*(id-1);
    }
}
// -------------------------


void
split_radix_fft(double *fr, double *fi, ulong ldn, int is)
// Fast Fourier Transform
// Split-radix decimation in frequency (DIF) algorithm.
// ldn := base-2 logarithm of the array length.
// is := sign of the transform (+1 or -1).
{
    if ( is<0 )  split_radix_fft_dif_core(fr, fi, ldn);
    else         split_radix_fft_dif_core(fi, fr, ldn);  // swapped fr, fi

    revbin_permute(fr, 1UL<<ldn);
    revbin_permute(fi, 1UL<<ldn);
}
// -------------------------
