#if !defined HAVE_AUXPRINT_H__
#define      HAVE_AUXPRINT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"


// aux1/auxprint.cc:
extern double print_epsilon;
void print(const char *bla, const double *f, ulong n, double eps=0.0);
//void print_twodim(const char *bla, const double *f, ulong r, ulong c, double eps=0.0);

// aux1/graphprint.cc:
void graph_print(const char *bla, const double *f, ulong n, ulong width=60, double eps=0.0);




//// aux1/auxprint.cc:
//void c_print(const char *what, const Complex *c, long n, double eps=0.0);
//void ri_print(const char *bla, const double *fr, const double *fi, long n, double eps=0.0);
//
//
//void approx_eq(const double *f, const double *g, ulong n,
//               const char *bla, double eps=1e-12);
//
//void approx_eq(const Complex *f, const Complex *g, ulong n,
//               const char *bla, double eps=1e-12);
//
//void approx_eq(const ulong *f, const ulong *g, ulong n, const char *bla);


#endif  // !defined HAVE_AUXPRINT_H__
