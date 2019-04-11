// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/weightedconvolution.h"
#include "convolution/realconvolution.h"
#include "fft/matrixfft.h"
#include "aux0/ldn2rc.h"
#include "restrict.h"

#include "bits/bit2pow.h"  // ld()

#include "aux1/copy.h"

#include "fxttypes.h"  // ulong

//#define  FFT(fr, fi, ldn, is)  fht_fft(fr, fi, ldn, is)


void
matrix_fft_convolution(double * restrict f, double * restrict g, ulong ldn)
// (cyclic, real) convolution:  g[] :=  f[] (*) g[]
// ldn := base-2 logarithm of the array length
{
    if ( ldn<=1 )  // note: slightly ugly
    {
        if ( ldn==1 )
        {
            double t0 = f[0] * g[0] + f[1] * g[1];
            double t1 = f[0] * g[1] + f[1] * g[0];
            g[0] = t0;
            g[1] = t1;
        }
        else  g[0] *= f[0];

        return;
    }

    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    matrix_fft_convolution(f, g, nr, nc, 0);
}
// -------------------------


void
matrix_fft_convolution0(double * restrict f, double * restrict g, ulong ldn)
// (linear, real) convolution:  g[] :=  f[] (*) g[]
// ldn := base-2 logarithm of the array length
// input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// n = 2**ldn  must be >=2
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    matrix_fft_convolution(f, g, nr, nc, 1);
}
// -------------------------


// tuning parameter:
#define  CP_ROWS  1  // 0 or 1 (use scratch space, default)


void
matrix_fft_convolution(double * restrict f, double * restrict g,
                       ulong nr, ulong nc, int zp/*=0*/)
// auxiliary routine for real convolutions via matrix FFT
//
// call with zp==1 if high half of data is zero (for linear convolution)
{
    const ulong n = nc * nr;
    const int is = 1;

    ulong mrc = 2 * (nr>nc ? nr : nc);
    double *tr = new double[2*mrc];
    double *ti = tr + mrc;

    column_ffts(f, g, nr, nc, is, zp, tr, ti);

    ulong ldc = ld(nc);
    double v = 1.0/(2.0*(double)n);
    double *pr = f,  *pi = g;
    for (ulong k=0; k<nr; k++)
    {
        double w = (double)k/(double)nr;

#if  ( CP_ROWS==1 )
//#warning 'FYI: matrix_fft_convolution() does row FFTs in scratch space'
        acopy(pr, tr , nc);
        acopy(pi, ti , nc);
        weighted_complex_auto_convolution(tr, ti, ldc, w, v);
        acopy(tr, pr , nc);
        acopy(ti, pi , nc);
#else  // CP_ROWS
#warning 'matrix_fft_convolution() does row FFTs in-place'
        weighted_complex_auto_convolution(pr, pi, ldc, w, v);
#endif  // CP_ROWS

        pr += nc;
        pi += nc;  // note: dependent of order of imag part
    }

    // save half of the work by:
    column_complex_imag_ffts(f, g, nr, nc, tr);

    delete [] tr;
}
// -------------------------
