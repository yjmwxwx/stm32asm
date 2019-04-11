#if !defined  HAVE_RANDF_H__
#define       HAVE_RANDF_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"     // ulong

// aux0/randf.cc:
uint rseed(uint s=0);
double rnd01();
void rnd01(double *f, ulong n);
double white_noise();
double white_noise(double *f, ulong n);


#endif  // !defined HAVE_RANDF_H__
