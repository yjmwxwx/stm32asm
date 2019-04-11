#if !defined  HAVE_RESAMPLE_H__
#define       HAVE_RESAMPLE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// aux1/resample.cc:
ulong resample_sinc(const double *a, ulong an, double af, double *b, double bf, ulong bn);
ulong sample_up_linear(const double *f, ulong nf, double v, double *g, ulong ng);
ulong sample_down_linear(const double *f, ulong nf, double v, double *g, ulong ng);
ulong resample_linear(const double *f, ulong nf, double v, double *g, ulong ng);


#endif  // !defined HAVE_RESAMPLE_H__
