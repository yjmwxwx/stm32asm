#if !defined  HAVE_COMPOSITION_NZ_RANK_H__
#define       HAVE_COMPOSITION_NZ_RANK_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// comb/composition-nz-rank.cc:

ulong composition_nz_rank(const ulong *x, ulong m);
ulong composition_nz_unrank(ulong r, ulong *x, ulong n);

ulong composition_nz_rl_rank(const ulong *x, ulong m);
ulong composition_nz_rl_unrank(ulong r, ulong *x, ulong n);

ulong composition_nz_subset_lex_rank(const ulong *x, ulong m, ulong n);
ulong composition_nz_subset_lex_unrank(ulong r, ulong *x, ulong n);

ulong composition_nz_gray_rank(const ulong *x, ulong m, ulong n);
ulong composition_nz_gray_unrank(ulong r, ulong *x, ulong n);


#endif  // !defined HAVE_COMPOSITION_NZ_RANK_H__
