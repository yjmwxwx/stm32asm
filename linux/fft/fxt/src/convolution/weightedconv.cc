// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/weightedconvolution.h"
#include "fft/fft.h"
#include "aux0/cmult.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


#define  FFT(fr, fi, ldn, is)  fht_fft(fr, fi, ldn, is)

#define  FFTC(f, ldn, is)  fht_fft(f, ldn, is)

void
weighted_complex_auto_convolution(double *fr, double *fi, ulong ldn,
                                  double w, double v/*=0.0*/)
// w = weight:
// +0.25 for right angle convolution (-0.25 negates result in fi[])
// +0.5  for negacyclic  convolution (also -0.5)
// +1.0  for cyclic  convolution (also -1.0)
//
// v!=0.0 chooses alternative normalization
{
    ulong n = (1UL<<ldn);

    fourier_shift(fr, fi, n, w);
    FFT(fr, fi, ldn, +1);

    if ( v==0.0 )  v = 1.0/(double)n;
    for (ulong k=0; k<n; k++)  csqr_n(fr[k], fi[k], v);

    FFT(fr, fi, ldn, -1);
    fourier_shift(fr, fi, n, -w);
}
// -------------------------


void
negacyclic_complex_auto_convolution(double *fr, double *fi, ulong ldn,
                                    double v/*=0.0*/)
//
// negacyclic autoconvolution of fr[], fi[]
//
// v!=0.0 chooses alternative normalization
{
    weighted_complex_auto_convolution(fr, fi, ldn, +0.5, v);
}
// -------------------------


void
right_angle_complex_auto_convolution(double *fr, double *fi, ulong ldn,
                                     double v/*=0.0*/)
//
// right angle autoconvolution of fr[], fi[]
//
// useful if fi[] all zero: then the result is the
//   acyclic autoconvolution of fr[]
//   result is in fr[] (index 0, 1, ..., n-1) and fi[] (index n, ..., 2*n-1)
//
// v!=0.0 chooses alternative normalization
{
    weighted_complex_auto_convolution(fr, fi, ldn, +0.25, v);
}
// -------------------------


void
weighted_complex_auto_convolution(Complex *f, ulong ldn, double w, double v/*=0.0*/)
// w = weight:
// +0.25 for right angle convolution (-0.25 negates result in fi[])
// +0.5  for negacyclic  convolution (also -0.5)
// +1.0  for cyclic  convolution (also -1.0)
//
// v!=0.0 chooses alternative normalization
{
    ulong n = (1UL<<ldn);

    fourier_shift(f, n, w);
    FFTC(f, ldn, +1);

    if ( v==0.0 )  v = 1.0/(double)n;
    for (ulong k=0; k<n; k++)
    {
        Complex t = f[k];
        t *= t;
        t *= v;
        f[k] = t;
    }

    FFTC(f, ldn, -1);
    fourier_shift(f, n, -w);
}
// -------------------------


void
negacyclic_complex_auto_convolution(Complex *f, ulong ldn, double v/*=0.0*/)
//
// negacyclic autoconvolution of f[]
//
// v!=0.0 chooses alternative normalization
{
    weighted_complex_auto_convolution(f, ldn, +0.5, v);
}
// -------------------------


void
right_angle_complex_auto_convolution(Complex *f, ulong ldn, double v/*=0.0*/)
//
// right angle autoconvolution of f[]
//
// v!=0.0 chooses alternative normalization
{
    weighted_complex_auto_convolution(f, ldn, +0.25, v);
}
// -------------------------

