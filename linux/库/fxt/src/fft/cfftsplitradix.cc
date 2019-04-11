// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>

#include "fxttypes.h"
#include "complextype.h"
#include "aux0/sumdiff.h"
#include "perm/revbinpermute.h"
#include "aux0/sincos.h"


// tuning parameter:
//#define USE_SINCOS3  // default = off
// whether sincos is used for 3*angle
// else: use algebraic relation
//
// sin & cos of triple angle by algebra:
#define SINCOS3ALG(c, s, c3, s3)  { c3 = 4.0*c*(c*c-0.75); s3=4.0*s*(0.75-s*s); }


void
split_radix_dif_fft_core(Complex *f, ulong ldn)
// Split-radix decimation in frequency (DIF) FFT.
// ldn := base-2 logarithm of the array length.
// Fixed isign = +1
// Output data is in revbin_permuted order.
{
    if ( ldn==0 )  return;

    const ulong n = (1UL<<ldn);

    double s2pi = 2.0*M_PI;  // pi*2*isign
    ulong n2 = 2*n;
    for (ulong k=1; k<ldn; k++)
    {
        n2 >>= 1;  // == n>>(k-1) == n, n/2, n/4, ..., 4
        const ulong n4 = n2 >> 2;  // == n/4, n/8, ..., 1
        const double e = s2pi / (double)n2;

        {  // j==0:
            const ulong j = 0;
            ulong ix = j;
            ulong id = (n2<<1);
            while ( ix<n )
            {
                for (ulong i0=ix; i0<n; i0+=id)
                {
                    ulong i1 = i0 + n4;
                    ulong i2 = i1 + n4;
                    ulong i3 = i2 + n4;

                    Complex t0, t1;
                    sumdiff3(f[i0], f[i2], t0);
                    sumdiff3(f[i1], f[i3], t1);

                    // t1 *= Complex(0, 1);  // +isign
                    t1 = Complex(-t1.imag(), t1.real());

                    sumdiff(t0, t1);
                    f[i2] = t0;  // * Complex(cc1, ss1);
                    f[i3] = t1;  // * Complex(cc3, ss3);
               }

               ix = (id<<1) - n2 + j;
               id <<= 2;
            }
        }

        for (ulong j=1; j<n4; j++)
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
                    // f[i0] = f[i0] + f[i2]
                    // f[i1] = f[i1] + f[i3]
                    // f[i2] = (f[i0]-f[i2] + (is*I) * (f[i1]-f[i3])) * SinCos(a)
                    // f[i3] = (f[i0]-f[i2] - (is*I) * (f[i1]-f[i3])) * SinCos(3*a)

                    Complex t0, t1;
                    sumdiff3(f[i0], f[i2], t0);
                    sumdiff3(f[i1], f[i3], t1);

                    // t1 *= Complex(0, is);
                    // t1 *= Complex(0, 1);  // +isign
                    t1 = Complex(-t1.imag(), t1.real());

                    sumdiff(t0, t1);
                    f[i2] = t0 * Complex(cc1, ss1);
                    f[i3] = t1 * Complex(cc3, ss3);
               }

               ix = (id<<1) - n2 + j;
               id <<= 2;
            }
        }
    }

    for (ulong ix=0, id=4;  ix<n;  id*=4)
    {
        for (ulong i0=ix; i0<n; i0+=id)  sumdiff(f[i0], f[i0+1]);
        ix = 2*(id-1);
    }
}
// -------------------------


void
split_radix_dit_fft_core(Complex *f, ulong ldn)
// Split-radix decimation in time (DIT) FFT.
// ldn := base-2 logarithm of the array length.
// Fixed isign = -1
// Input data must be in revbin_permuted order.
{
    if ( ldn==0 )  return;

    const ulong n = (1UL<<ldn);

    for (ulong ix=0, id=4;  ix<n;  id*=4)
    {
        for (ulong i0=ix; i0<n; i0+=id)  sumdiff(f[i0], f[i0+1]);
        ix = 2*(id-1);
    }

    double s2pi = -2.0*M_PI;  // pi*2*isign
    ulong n2 = 2;
    for (ulong k=ldn-1; k>=1; k--)
    {
        n2 <<= 1;  // == 4, 8, 16, ..., n
        ulong n4 = n2 >> 2;
        double e = s2pi / (double)n2;  // +isign

        {  // j==0:
            const ulong j = 0;
            ulong ix = j;
            ulong id = (n2<<1);
            while ( ix<n )
            {
                for (ulong i0=ix; i0<n; i0+=id)
                {
                    ulong i1 = i0 + n4;
                    ulong i2 = i1 + n4;
                    ulong i3 = i2 + n4;

                    Complex t0 = f[i3];
                    Complex t1 = f[i2];

                    sumdiff(t0, t1);
                    // t1 *= Complex(0, 1);  // -isign
                    t1 = Complex(-t1.imag(), t1.real());

                    sumdiff3(f[i0], t0, f[i2]);
                    sumdiff3(f[i1], t1, f[i3]);
               }

               ix = (id<<1) - n2 + j;
               id <<= 2;
            }
        }

        for (ulong j=1; j<n4; j++)
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

                    Complex t0 = f[i3] * Complex(cc3, ss3);
                    Complex t1 = f[i2] * Complex(cc1, ss1);

                    sumdiff(t0, t1);
                    // t1 *= Complex(0, -is);  // t1 /= Complex(0, is);
                    // t1 *= Complex(0, 1);  // -isign
                    t1 = Complex(-t1.imag(), t1.real());

                    sumdiff3(f[i0], t0, f[i2]);
                    sumdiff3(f[i1], t1, f[i3]);
               }

               ix = (id<<1) - n2 + j;
               id <<= 2;
            }
        }
    }
}
// -------------------------


void
split_radix_fft(Complex *f, ulong ldn, int is)
// Fast Fourier Transform.
// ldn := base-2 logarithm of the array length.
// is := sign of the transform (+1 or -1)
// Uses (DIF and DIT) split-radix algorithms.
{
    if ( is>0 )
    {
        split_radix_dif_fft_core(f, ldn);
        revbin_permute(f, 1UL<<ldn);
    }
    else
    {
        revbin_permute(f, 1UL<<ldn);
        split_radix_dit_fft_core(f, ldn);
    }
}
// -------------------------
