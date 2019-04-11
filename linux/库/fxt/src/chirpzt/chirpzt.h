#if !defined  HAVE_CHIRPZT_H__
#define       HAVE_CHIRPZT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"


//: chirp z-transform

// chirpzt/fftarblen.cc: (arbitrary length FFT)
void fft_arblen(Complex *f, ulong n, int is);

// chirpzt/fftfract.cc: (fractional FFT)
void fft_fract(Complex *x, ulong n, double v);
void fft_fract(double *x, double *y, ulong n, double v);


// chirpzt/slowfracft.cc:
void slow_fract_ft(Complex *f, ulong n, double v);
void slow_fract_ft(double *fr, double *fi, ulong n, double v);

// chirpzt/slowzt.cc:
void slow_zt(Complex *f, ulong n, Complex z);
void slow_zt(double *f, ulong n, double z);


#endif  // !defined HAVE_CHIRPZT_H__
