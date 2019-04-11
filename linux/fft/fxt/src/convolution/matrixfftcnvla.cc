// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/realconvolution.h"
#include "convolution/weightedconvolution.h"
#include "fft/matrixfft.h"
#include "fht/fht-default.h"
#include "aux0/ldn2rc.h"

#include "bits/bit2pow.h"  // ld()

#include "aux1/copy.h"

#include "fxttypes.h"  // ulong


//#define  FFT(fr, fi, ldn, is)  fht_fft(fr, fi, ldn, is)
//#define  FFT(fr, fi, ldn, is)  fft(fr, fi, ldn, is)


void
matrix_fft_auto_convolution(double *f, ulong ldn)
// (cyclic, real) self-convolution:  f[] :=  f[] (*) f[]
// ldn := base-2 logarithm of the array length
{
    if ( ldn<=1 )  // note: slightly ugly
    {
        if ( ldn==1 )
        {
            double t0 = f[0] * f[0] + f[1] * f[1];
            double t1 = f[0] * f[1];  t1 += t1;
            f[0] = t0;
            f[1] = t1;
        }
        else  f[0] *= f[0];

        return;
    }

    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    matrix_fft_auto_convolution(f, nr, nc, 0);
}
// -------------------------


void
matrix_fft_auto_convolution0(double *f, ulong ldn)
// (linear, real) self-convolution:  f[] :=  f[] (*0) f[]
// ldn := base-2 logarithm of the array length
// version for zero padded data:
//   f[k] == 0 for k=n/2 ... n-1
// n = 2**ldn  must be >=2
{
    if ( ldn<=1 )  // note: slightly ugly
    {
        if ( ldn==1 )
        {
            double t0 = f[0] * f[0] + f[1] * f[1];
            double t1 = f[0] * f[1];  t1 += t1;
            f[0] = t0;
            f[1] = t1;
        }
        else  f[0] *= f[0];

        return;
    }

    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    matrix_fft_auto_convolution(f, nr, nc, 1);
}
// -------------------------


// tuning parameter, define to use scratch space:
#define  CP_ROWS  // default on, avoids cache problems

void
matrix_fft_auto_convolution(double *f, ulong nr, ulong nc, int zp/*=0*/)
// auxiliary routine for real self-convolutions via matrix FFT
//
// call with zp==1 if high half of data is zero (for linear convolution)
{
    ulong n = nr * nc;
    ulong nh = n / 2;
    ulong ldc = ld(nc);

#ifdef  CP_ROWS
    ulong mrc = 2 * (nr>nc ? nr : nc);
    double *tr = new double[2*mrc];
    double *ti = tr + mrc;
#else
    double *tr = new double[nr];
#endif


    // ----- column FFTs:
    column_real_complex_ffts(f, nr, nc, zp, tr);


    // ----- weighted row convolutions:
    double v = 1.0/(double)n;
    // row 0:
    fht(f, ldc);
    fht_auto_convolution_core(f, ldc, v);
    fht(f, ldc);

    // row nr/2:  (only if nr>1 and nr even)
    if ( (nr>1) && !(nr&1) )  fht_negacyclic_auto_convolution(f+nh, ldc, v);

    // rows 1, 2, ..., nr-1:  (except possible row nr/2)
    double *pr = f,  *pi = f + n;
    for (ulong k=1; k<nr/2; k++)
    {
        pr += nc;
        pi -= nc;  // note: dependent of order of imag part
        double w = (double)k/(double)nr;

#ifdef  CP_ROWS
//#warning 'FYI: matrix_fft_auto_convolution() does row FFTs in scratch space'

        acopy(pr, tr , nc);
        acopy(pi, ti , nc);
        weighted_complex_auto_convolution(tr, ti, ldc, w, v);
        acopy(tr, pr , nc);
        acopy(ti, pi , nc);

#else  // CP_ROWS
#warning 'matrix_fft_auto_convolution() does row FFTs in-place'

        weighted_complex_auto_convolution(pr, pi, ldc, w, v);  // note: cache problem !

#endif  // CP_ROWS
    }


    // ----- column (inverse) FFTs:
    column_complex_real_ffts(f, nr, nc, tr);

    delete [] tr;
}
// -------------------------

