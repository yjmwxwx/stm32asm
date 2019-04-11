#if !defined  HAVE_NUMTHEORY_H__
#define       HAVE_NUMTHEORY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "mod/mtypes.h"
//#include "mod/factor.h"
class factorization;


// mod/kronecker.cc:
int kronecker(umod_t a, umod_t b);
//int reciprocity(umod_t a, umod_t b);

// mod/euler-phi.cc:
umod_t euler_phi(umod_t n);
umod_t euler_phi(umod_t pr, ulong ex);
umod_t euler_phi(const factorization &ff);

// mod/chinese.cc:
umod_t chinese(const umod_t *x, const factorization &f);


// mod/cyclic.cc:
bool is_cyclic(const factorization &f);


// mod/order.cc:
umod_t order_mod(umod_t x, umod_t m, const factorization &phifact);

// mod/maxorder.cc:
umod_t maxorder_mod(const factorization &mf);
umod_t maxorder_element_mod(const factorization &mf, const factorization &pf);

// mod/quadresidue.cc:
bool is_quadratic_residue_2ex(umod_t a, ulong x);
bool is_quadratic_residue(umod_t a, const factorization &mf);


// mod/sqrtmod.cc:
umod_t sqrt_modp(umod_t a, umod_t p);
umod_t sqrt_modpp(umod_t a, umod_t p, long ex);
umod_t sqrt_modf(umod_t a, const factorization &mf);


#endif  // !defined HAVE_NUMTHEORY_H__
