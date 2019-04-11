#if !defined  HAVE_SLOWCONVOLUTION_H__
#define       HAVE_SLOWCONVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// convolution/slowcocnvl.cc:
void slow_complex_convolution(const double *fr, const double *fi,
                              double *gr, double *gi, ulong n);

void slow_complex_auto_convolution(double *fr, double *fi, ulong n);


#include "convolution/slowcnvl.h"
#include "convolution/slowcnvla.h"
#include "convolution/slowweightedcnvl.h"
#include "convolution/slowcnvlhalf.h"
#include "convolution/slowtwodimcnvl.h"

#endif  // !defined HAVE_SLOWCONVOLUTION_H__
