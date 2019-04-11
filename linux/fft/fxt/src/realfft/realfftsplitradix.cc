// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "realfft/realfft.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "aux0/constants.h"  // COS_1_PI_8, SIN_1_PI_8
#include "aux1/arith1.h"  // negate()
#include "perm/revbinpermute.h"
#include "perm/revbinpermute0.h"
#include "aux0/sincos.h"
#include "fxttypes.h"  // ulong

#include <cmath>  // M_PI, M_SQRT1_2

// tuning parameter:
#define  USE_SINCOS3  0  // 0 to use algebra (default) or 1 for sincos call
//
// sin & cos of triple angle by algebra:
#define SINCOS3ALG(c, s, c3, s3) \
{ c3 = 4.0*c*(c*c-0.75); s3=4.0*s*(0.75-s*s); }

// original Fortran code by Sorensen; published in H.V. Sorensen, D.L. Jones,
// M.T. Heideman, C.S. Burrus (1987) Real-valued fast fourier transform
// algorithms.  IEEE Trans on Acoustics, Speech, & Signal Processing, 35,
// 849-863.  Adapted to C by Bill Simpson, 1995
// derived from: static char RCSreal2herm_c[] =
// "$Id: real2herm.c,v 1.1 1996/09/02 01:47:12 wedgingt Beta $";
// Further optimizations by Joerg Arndt

void
split_radix_real_complex_fft(double *x, ulong ldn, int is/*=-1*/)
//
// Transform length is n=2**ldn
//
// Ordering of output:
//
// f[0]     = re[0] (==zero frequency, purely real)
// f[1]     = re[1]
//         ...
// f[n/2-1] = re[n/2-1]
// f[n/2]   = re[n/2]    (==nyquist frequency, purely real)
//
// f[n/2+1] = im[n/2-1]
// f[n/2+2] = im[n/2-2]
//         ...
// f[n-1]   = im[1]
//
// Corresponding real and imag parts (with the exception of
// zero and nyquist freq) are found in f[i] and f[n-i]
//
// The order of imaginary parts is the same as in fht_real_complex_fft
// (reversed wrt. easy_ordering_real_complex_fft())
//
{
    if ( ldn>0 )
    {
        revbin_permute(x, 1UL<<ldn);
        split_radix_real_complex_fft_dit_core(x, ldn);

        if ( (is>0) && (ldn>=2) )  // prefer isign = -1
        {
            ulong nh = ( (1UL<<ldn) >> 1);
            negate(x+nh+1, nh-1);
        }
    }
}
// -------------------------


void
split_radix_real_complex_fft0(double *x, ulong ldn, int is/*=-1*/)
// Version for zero padded arrays
{
    if ( ldn>0 )
    {
        revbin_permute0(x, 1UL<<ldn);
        split_radix_real_complex_fft_dit_core(x, ldn);

        if ( (is>0) && (ldn>=2) )  // prefer isign = -1
        {
            ulong nh = ((1UL<<ldn) >>1);
            negate(x+nh+1, nh-1);
        }
    }
}
// -------------------------


void
split_radix_complex_real_fft(double *x, ulong ldn, int is/*=-1*/)
//
// Transform length is n=2**ldn
//
// Ordering of input must be
// like the output of split_radix_real_complex_fft()
//
{
    if ( ldn>0 )
    {
        if ( (is>0) && (ldn>=2) )  // prefer isign = -1
        {
            ulong nh = ( (1UL<<ldn) >>1);
            negate(x+nh+1, nh-1);
        }

        split_radix_complex_real_fft_dif_core(x, ldn);
        revbin_permute(x, 1UL<<ldn);
    }
}
// -------------------------


void
split_radix_real_complex_fft_dit_core(double *x, ulong ldn)
// Fixed isign == -1
{
    if ( ldn==0 )  return;

    const ulong n = (1UL<<ldn);
    for (ulong ix=0, id=4;  ix<n;  id*=4)
    {
        for (ulong i0=ix; i0<n; i0+=id)  sumdiff(x[i0], x[i0+1]);
        ix = 2*(id-1);
    }

    ulong n2 = 2;
    ulong nn = n>>1;
    while ( nn>>=1 )
    {
        ulong ix = 0;
        n2 <<= 1;
        ulong id = n2<<1;
        ulong n4 = n2>>2;
        ulong n8 = n2>>3;

        do  // ix
        {
            for (ulong i0=ix; i0<n; i0+=id)
            {
                ulong i1 = i0;
                ulong i2 = i1 + n4;
                ulong i3 = i2 + n4;
                ulong i4 = i3 + n4;

                double t1;
                diffsum3_r(x[i3], x[i4], t1);  // {a, b, s} <--| {a, b-a, a+b}
                sumdiff3(x[i1], t1, x[i3]);   // {a, b, d} <--| {a+b, b, a-b}

                if ( n4!=1 )  // note: optimise
                {
                    i1 += n8;
                    i2 += n8;
                    i3 += n8;
                    i4 += n8;

                    double t2;
                    sumdiff(x[i3], x[i4], t1, t2);
                    t1 = -t1 * M_SQRT1_2;
                    t2 *= M_SQRT1_2;

                    sumdiff(t1, x[i2], x[i4], x[i3]);
                    sumdiff3(x[i1], t2, x[i2]);  // {a, b, d} <--| {a+b, b, a-b}
                }
            }

            ix = (id<<1) - n2;
            id <<= 2;
        }
        while ( ix<n );

        double e = 2.0*M_PI/(double)n2;
        for (ulong j=1; j<n8; j++)
        {
            double a = (double)j * e;
            double cc1, ss1, cc3, ss3;
            SinCos(a, &ss1, &cc1);

#if ( USE_SINCOS3==1 )
            SinCos(3.0*a, &ss3, &cc3);
#else
            SINCOS3ALG(cc1, ss1, cc3, ss3);
#endif

            ix = 0;
            id = n2<<1;
            do
            {
                for (ulong i0=ix; i0<n; i0+=id)
                {
                    ulong i1 = i0 + j;
                    ulong i2 = i1 + n4;
                    ulong i3 = i2 + n4;
                    ulong i4 = i3 + n4;

                    ulong i5 = i0 + n4 - j;
                    ulong i6 = i5 + n4;
                    ulong i7 = i6 + n4;
                    ulong i8 = i7 + n4;

                    double t1, t2;
                    cmult(cc1, ss1, x[i7], x[i3], t2, t1);
                    double t3, t4;
                    cmult(cc3, ss3, x[i8], x[i4], t4, t3);

                    sumdiff(t2, t4);   // {a, b} <--| {a+b, a-b}
                    sumdiff(t2, x[i6], x[i8], x[i3]);

                    sumdiff_r(t1, t3);  // {a, b} <--| {a+b, b-a}
                    sumdiff(t3, x[i2], x[i4], x[i7]);

                    sumdiff3(x[i1], t1, x[i6]);   // {a, b, d} <--| {a+b, b, a-b}
                    diffsum3_r(t4, x[i5], x[i2]);  // {a, b, s} <--| {a, b-a, a+b}
                }

                ix = (id<<1) - n2;
                id <<= 2;
            }
            while ( ix<n );
        }
    }
}
// -------------------------


void
split_radix_complex_real_fft_dif_core(double *x, ulong ldn)
// isign == -1
{
    const ulong n = (1UL<<ldn);
    ulong nn = n>>1;
    ulong n2 = n<<1;
    while ( nn >>= 1 )
    {
        ulong ix = 0;
        ulong id = n2;
        n2 >>= 1;
        ulong n4 = n2>>2;
        ulong n8 = n4>>1;

        do  // ix
        {
            for (ulong i0=ix; i0<n; i0+=id)
            {
                ulong i1 = i0;
                ulong i2 = i1 + n4;
                ulong i3 = i2 + n4;
                ulong i4 = i3 + n4;

                double t1;
                sumdiff3(x[i1], x[i3], t1);

                x[i2] += x[i2];
                x[i4] += x[i4];

                sumdiff3_r(x[i4], t1, x[i3]);

                if ( n4!=1 )  // note: optimise
                {
                    i1 += n8;
                    i2 += n8;
                    i3 += n8;
                    i4 += n8;

                    double t2;
                    sumdiff3(x[i1], x[i2], t1);
                    sumdiff(x[i4], x[i3], t2, x[i2]);

                    t2 = -t2 * M_SQRT2;
                    t1 *= M_SQRT2;
                    sumdiff(t2, t1, x[i3], x[i4]);
                }
            }

            ix = (id<<1) - n2;
            id <<= 2;
        }
        while ( ix<n );

        double e = 2.0*M_PI/(double)n2;
        for (ulong j=1; j<n8; j++)
        {
            double a = (double)j*e;
            double cc1, ss1, cc3, ss3;
            SinCos(a, &ss1, &cc1);

#if  ( USE_SINCOS3==1 )
            SinCos(3.0*a, &ss3, &cc3);
#else
            SINCOS3ALG(cc1, ss1, cc3, ss3);
#endif

            ix = 0;
            id = n2<<1;
            do  // ix-loop
            {
                for (ulong i0=ix; i0<n; i0+=id)
                {
                    ulong i1 = i0 + j;
                    ulong i2 = i1 + n4;
                    ulong i3 = i2 + n4;
                    ulong i4 = i3 + n4;

                    ulong i5 = i0 + n4 - j;
                    ulong i6 = i5 + n4;
                    ulong i7 = i6 + n4;
                    ulong i8 = i7 + n4;

                    double t1, t2;
                    sumdiff3(x[i1], x[i6], t1);  // {a, b, d} <--| {a+b, b, a-b}
                    sumdiff3(x[i5], x[i2], t2);  // {a, b, d} <--| {a+b, b, a-b}

                    double t3, t4;
                    sumdiff(x[i8], x[i3], t3, x[i6]);
                    sumdiff(x[i4], x[i7], t4, x[i2]);

                    double t5;
                    sumdiff3(t1, t4, t5);  // {a, b, d} <--| {a+b, b, a-b}
                    sumdiff3(t2, t3, t4);  // {a, b, d} <--| {a+b, b, a-b}

                    cmult(ss1, cc1, t5, t4, x[i7], x[i3]);
                    cmult(cc3, ss3, t1, t2, x[i4], x[i8]);
                }

                ix = (id<<1) - n2;
                id <<= 2;
            }
            while ( ix<n );
        }
    }

    for (ulong ix=0, id=4;  ix<n;  id*=4)
    {
        for (ulong i0=ix; i0<n; i0+=id)  sumdiff(x[i0], x[i0+1]);
        ix = 2*(id-1);
    }
}
// -------------------------
