#if !defined HAVE_SYMMETRY_H__
#define      HAVE_SYMMETRY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// aux1/symmetry.cc:
int symm_q(const double *f, ulong n, double eps=1e-5);
int symm_0_q(const double *f, ulong n, double eps=1e-5);

int any_symm_q(const double *f, ulong n, double eps=1e-5);

void symm_0(double *f, ulong n, int s=+1);
void symm(double *f, ulong n, int s=+1);


#endif // !defined HAVE_SYMMETRY_H__
