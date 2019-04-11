#if !defined  HAVE_FHT2D_H__
#define       HAVE_FHT2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong

//: -------- 2-dimensional transform:
// fht/skipfht.cc:
void skip_fht(double *f, ulong n, ulong d, double *w);
void skip_fht0(double *f, ulong n, ulong d, double *w);

// fht/twodimfht.cc:
void row_column_fht(double *f, ulong nr, ulong nc);  // aux
void y_transform(double *f, ulong nr, ulong nc);  // aux
void twodim_fht(double *f, ulong nr, ulong nc);


#endif  // !defined HAVE_FHT2D_H__
