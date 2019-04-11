#if !defined  HAVE_SLOWFT_H__
#define       HAVE_SLOWFT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong
#include "complextype.h"  // type Complex

//: -------- Slow algorithms:

// fft/slowft.cc:
void slow_ft(Complex *f, ulong n, int is);
void slow_ft(double *fr, double *fi, ulong n, int is);
void slow_twodim_ft(Complex *f, ulong nr, ulong nc, int is);
void slow_twodim_ft(double *fr, double *fi, ulong r, ulong c, int is);

// fft/recfft2.cc:
void recursive_fft_dit2(Complex *a, ulong ldn, int is);
void recursive_fft_dif2(Complex *a, ulong ldn, int is);


#endif  // !defined HAVE_SLOWFT_H__
