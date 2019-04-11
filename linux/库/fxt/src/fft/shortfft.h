#if !defined  HAVE_SHORTFFT_H__
#define       HAVE_SHORTFFT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "complextype.h"  // Complex

// fft/fft8ditcore.cc:
void fft8_dit_core_p1(Complex *f);
void fft8_dit_core_m1(Complex *f);

void fft8_dit_core_p1(double *fr, double *fi);

inline void fft8_dit_core_m1(double *fr, double *fi)
{ fft8_dit_core_p1(fi, fr); }


// fft/fft8difcore.cc:
void fft8_dif_core_p1(Complex *f);
void fft8_dif_core_m1(Complex *f);

void fft8_dif_core_p1(double *fr, double *fi);

inline void fft8_dif_core_m1(double *fr, double *fi)
{ fft8_dif_core_p1(fi, fr); }


// fft/fft9.cc:
void fft9_m1(Complex *x);
void fft9_p1(Complex *x);
void fft9_m1(double *xr, double *xi);
void fft9_p1(double *xr, double *xi);


#endif  // !defined HAVE_SHORTFFT_H__
