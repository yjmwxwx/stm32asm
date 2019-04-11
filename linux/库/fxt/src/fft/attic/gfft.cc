// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"
#include "bits/grsnegative.h"
#include "bits/graycode.h"
#include "perm/graypermute.h"
#include "perm/revbinpermute.h"
#include "aux0/sincos.h"


void
gfft_dif2_core(Complex *f, ulong ldn, int is)
{
    const ulong n = (1UL<<ldn);
    inverse_gray_permute(f, n);

    const double pi = is*M_PI;

    for (ulong ldm=ldn; ldm>1; --ldm) // DIF
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);

        const double phi = pi/(double)(mh);

        for (ulong r=0; r<n; r+=m)
        {
            ulong i0 = r;
            ulong i1 = r + m - 1;

            Complex u = f[i0];
            Complex v = f[i1];

            f[i0] = u + v;
            f[i1] = u - v;

            for (ulong j=1; j<mh; ++j)
            {
                ++i0;
                --i1;

                double s,c;
                SinCos(phi*(double)(gray_code(j)), &s, &c);

                u = f[i0];
                v = f[i1];

                f[i0] =  u + v;
                f[i1] = (u - v) * Complex(c, s);
            }
        }
    }

    for (ulong r=0; r<n-1; r+=2)
    {
        ulong i0 = r;
        ulong i1 = r + 1;

        Complex u = f[i0];
        Complex v = f[i1];

        f[i0] = u + v;
        f[i1] = u - v;
    }
}
// -------------------------


void
gfft_dit2_core(Complex *f, ulong ldn, int is)
// inverse of gfft_dif2_core()
{
    const ulong n = (1UL<<ldn);
    for (ulong r=0; r<n-1; r+=2)
    {
        ulong i0 = r;
        ulong i1 = r + 1;

        Complex u = f[i0];
        Complex v = f[i1];

        f[i0] = u + v;
        f[i1] = u - v;
    }

    const double pi = is*M_PI;
    for (ulong ldm=2; ldm<=ldn; ++ldm) // DIT
    {
        const ulong m = (1UL<<ldm);
        const ulong mh = (m>>1);

        const double phi = pi/(double)(mh);

        for (ulong r=0; r<n; r+=m)
        {
            ulong i0 = r;
            ulong i1 = r + m - 1;

            Complex u = f[i0];
            Complex v = f[i1];

            f[i0] = u + v;
            f[i1] = u - v;

            for (ulong j=1; j<mh; ++j)
            {
                ++i0;
                --i1;

                double s,c;
                SinCos(phi*(double)(gray_code(j)), &s, &c);

                u = f[i0];
                v = f[i1] * Complex(c, s);

                f[i0] = u + v;
                f[i1] = u - v;
            }
        }
    }

    gray_permute(f, n);
}
// -------------------------


void
gfft(Complex *f, ulong ldn, int is)
{
    ulong n = 1UL<<ldn;
#if  1
    gfft_dif2_core(f, ldn, is);
    for (ulong k=0; k<n; ++k)  if ( grs_negative_q(k) )  f[k] = -f[k];
    revbin_permute(f, n);
#else
    revbin_permute(f, n);
    for (ulong k=0; k<n; ++k)  if ( grs_negative_q(k) )  f[k] = -f[k];
    gfft_dit2_core(f, ldn, is);
#endif
}
// -------------------------

void
gfft_auto_convolution(Complex *f, ulong ldn)
{
    int is = +1;
    gfft_dif2_core(f, ldn, is);

    ulong n = 1UL<<ldn;
    double v = 1.0 / (double)n;
    for (ulong k=0; k<n; ++k)
    {
        Complex t = f[k] * f[k];
        if ( grs_negative_q(k) )  t = -t;
        f[k] = t * v;
    }

    gfft_dit2_core(f, ldn, -is);
}
// -------------------------


void
gfft_convolution(Complex *f, Complex *g, ulong ldn)
{
    int is = +1;
    gfft_dif2_core(f, ldn, is);
    gfft_dif2_core(g, ldn, is);

    ulong n = 1UL<<ldn;
    double v = 1.0 / (double)n;
    for (ulong k=0; k<n; ++k)
    {
        Complex t = f[k] * g[k];
        if ( grs_negative_q(k) )  t = -t;
        g[k] = t * v;
    }

    gfft_dit2_core(g, ldn, -is);
}
// -------------------------

