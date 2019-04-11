#if !defined  HAVE_BITPOL_FACTOR_H__
#define       HAVE_BITPOL_FACTOR_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// bpol/berlekamp.cc:
void setup_q_matrix(ulong c, ulong d, ulong *ss);
ulong bitpol_refine_factors(ulong *f, ulong nf, const ulong *nn, ulong r);
ulong bitpol_factor_squarefree(ulong c, ulong *f);

// bpol/bitpol-factor.cc:
ulong bitpol_factor(ulong c, ulong *f, ulong *e);
void bitpol_sort_factorization(ulong *f, ulong *e, ulong fct);
ulong bitpol_test_factorization(ulong c, const ulong *f, const ulong *e, ulong fct, ulong &fi);


#endif  // !defined HAVE_BITPOL_FACTOR_H__

