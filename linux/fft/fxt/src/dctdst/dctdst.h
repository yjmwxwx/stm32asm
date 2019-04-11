#if !defined  HAVE_DCTDST_H__
#define       HAVE_DCTDST_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

//: cosine and sine transforms

// dctdst/cosrot.cc:
void cos_rot(const double *x, double *y, ulong n);  // aux


// dctdst/dct.cc:
//void dct(double *x, ulong ldn, double *y=0);
//void dct_basis(double *f, ulong n, ulong k);

// dctdst/dcth.cc:
void dcth(double *x, ulong ldn, double *y=0);
void idcth(double *x, ulong ldn, double *y=0);
void dcth_basis(double *f, ulong n, ulong k);

// dctdst/dctzapata.cc:
void dcth_zapata(double *x, ulong ldn, double *y=0);

// dctdst/dct4.cc:
void dct4(double *f, ulong n);
void idct4(double *f, ulong n);
void dct4_basis(double *f, ulong n, ulong k);


// dctdst/dst.cc:
void dst(double *x, ulong ldn, double *y=0);
void dst_basis(double *f, ulong n, ulong k);

// dctdst/dsth.cc:
void dsth(double *x, ulong ldn, double *y=0);
void idsth(double *x, ulong ldn, double *y=0);
void dsth_basis(double *f, ulong n, ulong k);


#endif  // !defined HAVE_DCTDST_H__
