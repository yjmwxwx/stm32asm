#if !defined  HAVE_CORRELATION_H__
#define       HAVE_CORRELATION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "complextype.h"
#include "fxttypes.h"

//: Real correlation
// correlation/fhtcorr.cc:
void fht_correlation(double *f, double *g, ulong ldn);
void fht_auto_correlation(double *f, ulong ldn);
void fht_correlation0(double *f, double *g, ulong ldn);
void fht_auto_correlation0(double *f, ulong ldn);
void fht_auto_correlation_core(double *f, ulong ldn, double v=0.0);

// correlation/fftcorr.cc:
void fft_correlation(double *f, double *g, ulong ldn);
void fft_auto_correlation(double *f, ulong ldn);
void fft_correlation0(double *f, double *g, ulong ldn);
void fft_auto_correlation0(double *f, ulong ldn);


//: Complex correlation
// correlation/fftcocorr.cc:
void fft_complex_auto_correlation(double *fr, double *fi, ulong ldn);
void fft_complex_correlation(double *fr, double *fi, double *gr, double *gi, ulong ldn);


// correlation/slowcocorr.cc:
void slow_complex_correlation(const double *fr, const double *fi,
                              const double *gr, const double *gi,
                              double *hr, double *hi, ulong n);
void slow_complex_correlation(const double *fr, const double *fi,
                              double *gr, double *gi, ulong n);
void slow_complex_auto_correlation(double *fr, double *fi, ulong n);


#endif  // !defined HAVE_CORRELATION_H__
