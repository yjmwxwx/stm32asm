#if !defined  HAVE_HARMONIC_WAVELET_H__
#define       HAVE_HARMONIC_WAVELET_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong

// wavelet/harmonic-wavelet.cc:
void harmonic_wavelet(double *fr, double *fi, ulong ldn);
void inverse_harmonic_wavelet(double *fr, double *fi, ulong ldn);


#endif  // !defined HAVE_HARMONIC_WAVELET_H__
