#if !defined  HAVE_SLOWHT_H__
#define       HAVE_SLOWHT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong
#include "complextype.h"  // type Complex

//: -------- Slow algorithms:
// fht/slowht.cc:
void slow_ht(double *f, ulong n);
void slow_ht(Complex *f, ulong n);
void slow_row_column_ht(double *f, ulong nr, ulong nc);
void slow_twodim_ht(double *f, ulong nr, ulong nc);

// fht/recfht2.cc:
void recursive_fht_dit2(double *a, ulong ldn);
void recursive_fht_dif2(double *a, ulong ldn);

#endif  // !defined HAVE_SLOWHT_H__
