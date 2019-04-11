#if !defined HAVE_AUX0DOUBLE_H__
#define      HAVE_AUX0DOUBLE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"     // ulong


// aux0/aux0double.cc:
double pythag(double a, double b);
double extr3_estimate(const double *f);
double extr3_estimate(const double *f, double &xval);
double sinc(double x);

void chop(double &x, double eps=1e-6);


// aux0/aux0print.cc:
void print_fixed(const char *bla, double v, long nd, bool sq);


#endif  // !defined HAVE_AUX0DOUBLE_H__
