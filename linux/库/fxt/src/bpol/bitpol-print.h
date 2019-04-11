#if !defined  HAVE_BITPOL_PRINT_H__
#define       HAVE_BITPOL_PRINT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


//<<
// Printing binary polynomials in different formats:
//
//  ascii format:
//  bitpol_print()  ==   bitpol_print_factorization()
//   x^7+x^4+x^3+1  ==   (x+1)^5 *  (x^2+x+1)
//
//  coefficient list:
//  bitpol_print_coeff()  ==   bitpol_print_coeff_factorization()
//       (7,4,3,0)  ==  (1,0)^5 * (2,1,0)
//
//  TeX format:
//  bitpol_print_tex()      ==   bitpol_print_tex_factorization()
// x^{7} + x^{4} + x^{3} + 1  ==   \left(x + 1\right)^{5} \cdot  \left(x^{2} + x + 1\right)
//>>


// bpol/bitpol-print.cc:
void bitpol_print(const char *bla, ulong c, bool sq=true);
void bitpol_print_bin(const char *bla, ulong c);
void bitpol_print_coeff(const char *bla, ulong c);
void bitpol_print_tex(const char *bla, ulong c);

void bitpol_print_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct);
void bitpol_print_bin_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct);
void bitpol_print_coeff_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct);
void bitpol_print_tex_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct);
void bitpol_print_short_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct);


#endif  // !defined HAVE_BITPOL_PRINT_H__
