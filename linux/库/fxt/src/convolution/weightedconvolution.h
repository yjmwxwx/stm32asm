#if !defined  HAVE_WEIGHTEDCONVOLUTION_H__
#define       HAVE_WEIGHTEDCONVOLUTION_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"
#include "restrict.h"


// convolution/fhtnegacnvl.cc:
void fht_negacyclic_auto_convolution(double *x, ulong ldn, double v=0.0);
void fht_negacyclic_convolution(double * restrict f, double * restrict g, ulong ldn);


// convolution/weightedconv.cc:
void weighted_complex_auto_convolution(double *fr, double *fi, ulong ldn, double w, double v=0.0);
void negacyclic_complex_auto_convolution(double *fr, double *fi, ulong ldn, double v=0.0);
void right_angle_complex_auto_convolution(double *fr, double *fi, ulong ldn, double v=0.0);
void weighted_complex_auto_convolution(Complex *f, ulong ldn, double w, double v=0.0);
void negacyclic_complex_auto_convolution(Complex *f, ulong ldn, double v=0.0);
void right_angle_complex_auto_convolution(Complex *f, ulong ldn, double v=0.0);


#endif  // !defined HAVE_WEIGHTEDCONVOLUTION_H__
