#if !defined  HAVE_BITMAT_FUNCS_H__
#define       HAVE_BITMAT_FUNCS_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "restrict.h"


// bmat/bitmat-mult-mm.cc:
void bitmat_mult_MM(const ulong *M1, const ulong *M2, ulong n, ulong *P);


// bmat/bitmat-transpose.cc:
void bitmat_transpose(const ulong *M, ulong n, ulong *T);


// bmat/bitmat-nullspace.cc:
ulong bitmat_nullspace(const ulong *M, ulong n, ulong *Ns);
ulong bitmat_test_nullspace(const ulong *M, ulong n, const ulong *Ns, ulong r);


// bmat/bitmat-inverse.cc:
bool bitmat_inverse_q(const ulong *M, ulong n, const ulong *Mi);
bool bitmat_inverse(const ulong *M, ulong n, ulong * restrict Mi,
                     const ulong * restrict B=0);
bool bitmat_invert(ulong *M, ulong n);


// bmat/bitmat-hessenberg.cc:
bool bitmat_is_hessenberg(const ulong *H, ulong n);
void bitmat_hessenberg(const ulong *M, ulong n, ulong *H);


// bmat/bitmat-charpoly.cc:
ulong bitmat_hessenberg2charpoly(const ulong *H, ulong n);
ulong bitmat_charpoly(const ulong *M, ulong n);


// bmat/bitmat-print.cc:
void bitmat_print(const char *bla, const ulong *M, ulong n, ulong nv=0);


// bmat/bitmat-kronecker.cc:
void bitmat_kronecker(const ulong *M1, ulong n1, const ulong *M2, ulong n2, ulong *K);


#endif  // !defined HAVE_BITMAT_FUNCS_H__
