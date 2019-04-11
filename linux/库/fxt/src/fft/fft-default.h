#if !defined  HAVE_FFT_DEFAULT_H__
#define       HAVE_FFT_DEFAULT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft.h"

#include "fxttypes.h"      // ulong
#include "complextype.h"   // Complex


//: Default FFT implementations

inline void fft(double *fr, double *fi, ulong ldn, int is)
{ fht_fft(fr, fi, ldn, is); }

inline void fft(Complex *f, ulong ldn, int is)
{ fht_fft(f, ldn, is); }


#endif  // !defined HAVE_FFT_DEFAULT_H__
