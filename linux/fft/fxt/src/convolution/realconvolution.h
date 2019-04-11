#if !defined  HAVE_REALCONVOLUTION_H__
#define       HAVE_REALCONVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//: REAL CONVOLUTION

// convolution/fhtcnvlcore.cc:
void fht_convolution_core(const double *x, double *y, ulong ldn, double v=0.0);  // aux
void fht_convolution_revbin_permuted_core(const double *x, double *y, ulong ldn, double v=0.0);  // aux

// convolution/fhtcnvlacore.cc:
void fht_auto_convolution_core(double *x, ulong ldn, double v=0.0);  // aux
void fht_auto_convolution_revbin_permuted_core(double *x, ulong ldn, double v=0.0);  // aux

// convolution/fhtcnvl.cc:
void fht_convolution(double *f, double *g, ulong ldn);
void fht_convolution0(double *f, double *g, ulong ldn);

// convolution/fhtcnvla.cc:
void fht_auto_convolution(double *f, ulong ldn);
void fht_auto_convolution0(double *f, ulong ldn);

// convolution/fhtloccnvl.cc:
void loc_fht_convolution(double *f, double *g, ulong ldn);
void loc_fht_convolution0(double *f, double *g, ulong ldn);

// convolution/fhtloccnvla.cc:
void loc_fht_auto_convolution(double *f, ulong ldn);
void loc_fht_auto_convolution0(double *f, ulong ldn);

// convolution/fftcnvl.cc:
void fht_fft_convolution(double *f, double *g, ulong ldn);
void split_radix_fft_convolution(double *f, double *g, ulong ldn);
void fht_fft_convolution0(double *f, double *g, ulong ldn);
void split_radix_fft_convolution0(double *f, double *g, ulong ldn);
void fft_convolution_core1(const double *x, double *y, ulong ldn, double v=0.0);  // aux
void fft_convolution_core2(const double *x, double *y, ulong ldn, double v=0.0);  // aux

// convolution/fftcnvla.cc:
void fht_fft_auto_convolution(double *f, ulong ldn);
void split_radix_fft_auto_convolution(double *f, ulong ldn);
void fht_fft_auto_convolution0(double *f, ulong ldn);
void split_radix_fft_auto_convolution0(double *f, ulong ldn);
void fft_auto_convolution_core1(double *x, ulong ldn, double v=0.0);  // aux
void fft_auto_convolution_core2(double *x, ulong ldn, double v=0.0);  // aux

// convolution/twodimfhtcnvl.cc:
void twodim_fht_convolution_core(const double *f, double *g, ulong nr, ulong nc);  // aux

// convolution/matrixfftcnvla.cc:
void matrix_fft_auto_convolution(double *f, ulong ldn);
void matrix_fft_auto_convolution0(double *f, ulong ldn);
void matrix_fft_auto_convolution(double *f, ulong r, ulong c, int zp=0);

// convolution/matrixfftcnvl.cc:
void matrix_fft_convolution(double *f, double *g, ulong ldn);
void matrix_fft_convolution0(double *f, double *g, ulong ldn);
void matrix_fft_convolution(double *f, double *g, ulong r, ulong c, int zp=0);


#endif  // !defined HAVE_REALCONVOLUTION_H__
