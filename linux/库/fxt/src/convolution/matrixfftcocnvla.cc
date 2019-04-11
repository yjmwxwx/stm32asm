// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/complexconvolution.h"
#include "fft/matrixfft.h"
#include "fft/fft.h"
#include "fht/fht.h"
#include "aux0/ldn2rc.h"

#include "bits/bit2pow.h"  // ld()
#include "perm/revbinpermute.h"
#include "perm/revbinpermute0.h"
#include "bits/revbin.h"  // revbin()

#include "aux0/swap.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


// tuning parameter:
#define  USE_OLD_ALGORITHM    0  // 0 (default, revbin_permute for transpose)  or 1
#define  USE_SPLRX  0  // whether split-radix DIF/DIT FFTs are used (default=0)
//
#if  ( USE_OLD_ALGORITHM==1 )
//#warning "FYI: using simple algorithm for matrix_fft_auto_convolution(Complex *f, ...)"
#else  // USE_OLD_ALGORITHM
//#warning "FYI: using revbin_permute for transpose for matrix_fft_auto_convolution(Complex *f, ...)"
#if  ( USE_SPLRX==1 )
//#warning 'FYI: matrix_fft_complex_auto_convolution() uses split-radix FFTs'
#define  DIT_FFT_CORE  split_radix_fft_dit_core  // isign = -1
#define  DIF_FFT_CORE  split_radix_fft_dif_core  // isign = +1
#else
//#warning 'FYI: matrix_fft_complex_auto_convolution() uses radix-4 FFTs'
#define  DIT_FFT_CORE  fft_dit4_core_m1  // isign = -1
#define  DIF_FFT_CORE  fft_dif4_core_p1  // isign = +1
#endif
#endif  // USE_OLD_ALGORITHM


void
matrix_fft_auto_convolution(Complex *f, ulong ldn)
// (complex, cyclic) self-convolution:  f[] :=  f[] (*) f[]
// ldn := base-2 logarithm of the array length
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    matrix_fft_auto_convolution(f, nr, nc, 0);
}
// -------------------------


void
matrix_fft_auto_convolution0(Complex *f, ulong ldn)
// (complex, linear) self-convolution:  f[] :=  f[] (*0) f[]
// ldn := base-2 logarithm of the array length
// Input data must be zero padded:  f[n/2] .. f[n-1] == 0
// n = 2**ldn,  must be >=2
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    matrix_fft_auto_convolution(f, nr, nc, 1);
}
// -------------------------


void
matrix_fft_auto_convolution(Complex *f, ulong nr, ulong nc, int zp/*=0*/)
// Auxiliary routine for complex self-convolutions via matrix FFT.
// Call with zp==1 if high half of data is zero (for linear convolution).
{
#if ( USE_OLD_ALGORITHM==1 )

    const ulong n = nc * nr;
    const int is = 1;

    Complex *t = new Complex[nr];

    column_ffts(f, nr, nc, is, zp, t);
    double v = 1.0/n;
    row_weighted_auto_convolutions(f, nr, nc, v);
    column_ffts(f, nr, nc, -is, 0, t);

    delete [] t;

#else  // USE_OLD_ALGORITHM

    const ulong n = nc * nr;
    ulong ldr = ld(nr),  ldc = ld(nc);

    if ( zp ) revbin_permute0(f, n);
    else      revbin_permute(f, n);
    ::swap2(nr, nc);
    ::swap2(ldr, ldc);

    const int is = -1;  // must be -1
    ulong k;
    Complex *tf;
    for (k=0, tf=f; k<nr; ++k, tf+=nc)
    {
        DIT_FFT_CORE(tf, ldc);  // is = -1
        ulong rk = revbin(k, ldr);
        fourier_shift(tf, nc, is*1.0*(double)rk/(double)nr);
    }

    revbin_permute(f, n);
    ::swap2(nr, nc);
    ::swap2(ldr, ldc);

    double v = 1.0/(double)n;
    for (k=0, tf=f; k<nr; ++k, tf+=nc)
    {
        fht_dif_core(tf, ldc);
        fht_auto_convolution_revbin_permuted_core(tf, ldc, v);
        fht_dit_core(tf, ldc);
    }

    revbin_permute(f, n);
    ::swap2(nr, nc);
    ::swap2(ldr, ldc);

    for (k=0, tf=f; k<nr; ++k, tf+=nc)
    {
        ulong rk = revbin(k, ldr);
        fourier_shift(tf, nc, -is*1.0*(double)rk/(double)nr);
        DIF_FFT_CORE(tf, ldc);  // is = +1
    }

    revbin_permute(f, n);
#endif  // USE_OLD_ALGORITHM
}
// -------------------------


void
matrix_fft_complex_auto_convolution(double *fr, double *fi, ulong ldn)
// (complex, cyclic) self-convolution:
//   (fr, fi)[] :=  (fr, fi)[] (*) (fr, fi)[]
// ldn := base-2 logarithm of the array length.
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    matrix_fft_complex_auto_convolution(fr, fi, nr, nc);
}
// -------------------------

void
matrix_fft_complex_auto_convolution0(double *fr, double *fi, ulong ldn)
// (complex, linear) self-convolution:
//   (fr, fi)[] :=  (fr, fi)[] (*0) (fr, fi)[]
// ldn := base-2 logarithm of the array length.
// Input data must be zero padded:  f[n/2] .. f[n-1] == 0
// n = 2**ldn,  must be >=2
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    matrix_fft_complex_auto_convolution(fr, fi, nr, nc, 1);
}
// -------------------------


void
matrix_fft_complex_auto_convolution(double *fr, double *fi, ulong nr, ulong nc, int zp/*=0*/)
// Auxiliary routine for the computation of complex convolutions via matrix FFT.
// Call with zp==1 if high half of data is zero (for linear convolution)
{
    const ulong n = nc * nr;
    const int is = 1;

    double *tr = new double[2*nr];
    double *ti = tr + nr;

    column_ffts(fr, fi, nr, nc, is, zp, tr, ti);
    double v = 1.0/(double)n;
    row_weighted_auto_convolutions(fr, fi, nr, nc, v);
    column_ffts(fr, fi, nr, nc, -is, 0, tr, ti);

    delete [] tr;
}
// -------------------------
