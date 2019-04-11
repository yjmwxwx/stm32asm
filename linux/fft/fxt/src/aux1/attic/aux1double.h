#if !defined HAVE_AUX1DOUBLE_H__
#define      HAVE_AUX1DOUBLE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// aux1/aux1double.cc:
//void chop(double *f, ulong n, double eps=1e-6);
double norm_l2(const double *f, ulong n);
double normalize(double *f, ulong n, double v=1.0);
//double sigma(const double *f, ulong n, double *mp=0);
//void   mean_sigma(const double *f, ulong n, double *mp, double *sp);
//void   smooth(double *f, ulong n, ulong m=1);
double rms_diff(const double *f, const double *g, ulong n);
//ulong *histogram(const double *f, ulong n, ulong nbox, ulong *hh=0);

//void welch_win(double *f, ulong n);

//void ri_multiply(const double *fr, const double *fi,
//                 double *gr, double *gi, ulong n);


#endif  // !defined HAVE_AUX1DOUBLE_H__
