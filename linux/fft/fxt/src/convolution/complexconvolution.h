#if !defined  HAVE_COMPLEXCONVOLUTION_H__
#define       HAVE_COMPLEXCONVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"


//: Complex convolution:

// convolution/fftcocnvl.cc:
void fft_complex_auto_convolution(Complex *f, ulong ldn, double v=0.0);
void fft_complex_convolution(Complex *f, Complex *g, ulong ldn, double v=0.0);
void fft_complex_auto_convolution(double *fr, double *fi, ulong ldn, double v=0.0);
void fft_complex_convolution(double *fr, double *fi, double *gr, double *gi, ulong ldn, double v=0.0);


// convolution/matrixfftcocnvla.cc:
void matrix_fft_auto_convolution(Complex *f, ulong ldn);
void matrix_fft_auto_convolution0(Complex *f, ulong ldn);
void matrix_fft_auto_convolution(Complex *f, ulong nr, ulong nc, int zp=0);
void matrix_fft_complex_auto_convolution(double *fr, double *fi, ulong ldn);
void matrix_fft_complex_auto_convolution0(double *fr, double *fi, ulong ldn);
void matrix_fft_complex_auto_convolution(double *fr, double *fi, ulong nr, ulong nc, int zp=0);

// The rest are generated files:

// convolution/cfhtcnvlcore.cc:
void fht_convolution_core(const Complex *x, Complex *y, ulong ldn, double v=0.0);  // aux
void fht_convolution_revbin_permuted_core(const Complex *x, Complex *y, ulong ldn, double v=0.0);  // aux

// convolution/cfhtcnvlacore.cc:
void fht_auto_convolution_core(Complex *x, ulong ldn, double v=0.0);  // aux
void fht_auto_convolution_revbin_permuted_core(Complex *x, ulong ldn, double v=0.0);  // aux


// convolution/cfhtcnvl.cc:
void fht_convolution(Complex *f, Complex *g, ulong ldn);
void fht_convolution0(Complex *f, Complex *g, ulong ldn);

// convolution/cfhtcnvla.cc:
void fht_auto_convolution(Complex *f, ulong ldn);
void fht_auto_convolution0(Complex *f, ulong ldn);


#endif  // !defined HAVE_COMPLEXCONVOLUTION_H__
