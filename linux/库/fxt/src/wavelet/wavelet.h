#if !defined  HAVE_WAVELET_H__
#define       HAVE_WAVELET_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//: ---------- WAVELET TRANSFORM ----------

//<<
// wavelet/waveletfilter.h:
class wavelet_filter;
//>>

#include "fxttypes.h"  // ulong

// wavelet/wavelet.cc:
void wavelet(double *f, ulong ldn, const wavelet_filter &wf, ulong minm=2);
void wavelet_step(double *f, ulong n, const wavelet_filter &wf, double *t);

// wavelet/invwavelet.cc:
void inverse_wavelet(double *f, ulong ldn, const wavelet_filter &wf, ulong minm=2);
void inverse_wavelet_step(double *f, ulong n, const wavelet_filter &wf, double *t);


#endif  // !defined HAVE_WAVELET_H__
