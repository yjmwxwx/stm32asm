#if !defined HAVE_SORTCOMPLEX_H__
#define      HAVE_SORTCOMPLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "complextype.h"

// sort/sortcomplex.cc:
bool is_complex_sorted(Complex *f, ulong n);
void complex_sort(Complex *f, ulong n);

ulong bsearch_complex(const Complex *f, ulong n, Complex v);


#endif // !defined HAVE_SORTCOMPLEX_H__
