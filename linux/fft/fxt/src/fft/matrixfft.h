#if !defined  HAVE_MATRIXFFT_H__
#define       HAVE_MATRIXFFT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"      // ulong
#include "complextype.h"   // Complex


// fft/matrixfft.cc:
void matrix_fft(double *fr, double *fi, ulong ldn, int is);
void matrix_fft0(double *fr, double *fi, ulong ldn, int is);
void matrix_fft(Complex *f, ulong ldn, int is);
void matrix_fft0(Complex *f, ulong ldn, int is);

// fft/rowffts.cc:
void row_ffts(double *fr, double *fi, ulong nr, ulong nc, int is);  // aux
void row_weighted_ffts(double *fr, double *fi, ulong nr, ulong nc, int is);  // aux
void row_ffts(Complex *f, ulong nr, ulong nc, int is);  // aux
void row_weighted_ffts(Complex *f, ulong nr, ulong nc, int is);  // aux

// fft/rowcnvls.cc:
void row_weighted_auto_convolutions(double *fr, double *fi, ulong nr, ulong nc, double v);  // aux
void row_weighted_auto_convolutions(Complex *f, ulong nr, ulong nc, double v);  // aux

// fft/columnffts.cc:
void column_ffts(double *fr, double *fi, ulong nr, ulong nc, int is, int zp, double *tr, double *ti);  // aux
void column_ffts(Complex *f, ulong nr, ulong nc, int is, int zp, Complex *tmp);  // aux
void column_real_complex_ffts(double *fr, ulong nr, ulong nc, int zp, double *t);  // aux
void column_complex_real_ffts(double *fr, ulong nr, ulong nc, double *t);  // aux
void column_complex_imag_ffts(const double *fr, double *fi, ulong r, ulong c, double *tmp);  // aux


#endif  // !defined HAVE_MATRIXFFT_H__
