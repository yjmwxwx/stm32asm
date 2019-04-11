#if !defined HAVE_COMB_PRINT_H__
#define      HAVE_COMB_PRINT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// comb/print-set.cc:
void print_set(const char *bla, const ulong *x, ulong n, ulong off=0);
void print_set_as_deltaset(const char *bla, const ulong *f, ulong n, ulong N, const char *c01=0);
void print_set1_as_deltaset(const char *bla, const ulong *x, ulong n, ulong N, const char *c01=0);
ulong print_deltaset_as_set(const char *bla, const ulong *x, ulong n, int eq=0);
ulong print_deltaset_as_set1(const char *bla, const ulong *x, ulong n, int eq=0);
void print_deltaset(const char *bla, const ulong *x, ulong n, const char *c01=0);


// comb/print-mset.cc:
ulong print_multi_deltaset_as_set(const char *bla, const ulong *x, ulong n, bool cq=true);
ulong print_multi_deltaset_as_set_alph(const char *bla, const ulong *x, ulong n, bool cq=true);


// comb/print-perm.cc:
void print_perm(const char *bla, const ulong *f, ulong n, bool dfz=false);


// comb/print-setpart.cc:
void print_setpart(const char *bla, const ulong *f, ulong n, ulong ns, ulong off=1);


// comb/print-vec.cc:
void print_vec(const char *bla, const ulong *x, ulong n, bool dfz=false);
void print_vec1(const char *bla, const ulong *x, ulong n);
void print_vec_rev(const char *bla, const ulong *x, ulong n, bool dfz=false);
void print_sign_vec(const char *bla, const ulong *x, ulong n);
void print_sym_vec(const char *bla, const ulong *x, ulong n);


// comb/print-mixedradix.cc:
void print_mixedradix(const char *bla, const ulong *f, ulong n, bool dfz=false);

// comb/print-gray.cc:
void print_gray(const ulong *f, ulong n);
void print_gray_delta(const ulong *f, ulong n, ulong lb=0);


#endif  // !defined HAVE_COMB_PRINT_H__
