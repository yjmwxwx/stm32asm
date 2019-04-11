#if !defined  HAVE_SLANT_H__
#define       HAVE_SLANT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong

// walsh/slant.cc:
void slant(double *f, ulong ldn);
void inverse_slant(double *f, ulong ldn);
void slant_seq(double *f, ulong ldn);
void inverse_slant_seq(double *f, ulong ldn);


#endif  // !defined HAVE_SLANT_H__
