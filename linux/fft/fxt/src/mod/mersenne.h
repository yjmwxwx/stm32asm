#if !defined  HAVE_MERSENNE_H__
#define       HAVE_MERSENNE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "mod/factor.h"
#include "sort/bsearch.h"
#include "mod/mtypes.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"

// mod/mersenne-factors.cc:
extern const umod_t mersenne_prime_factor_tab[];  // zero terminated

//// mod/mersenne-generators.cc:
//extern const ulong mersenne_generators_tab[];
//extern const umod_t mersenne_maxorder_tab[];

// mod/mersenne-exponents.cc:
extern const ulong mersenne_exp_tab[];
extern const ulong mersenne_exp_tab_len;

inline bool is_mersenne_x(ulong x)
// Return true if x is the exponent of a known Mersenne prime.
{
    ulong idx = bsearch(mersenne_exp_tab, mersenne_exp_tab_len, x);
    return  ( mersenne_exp_tab_len != idx );
}
// -------------------------

inline umod_t mersenne(ulong e)
{
    umod_t m = ~0UL >> ( BITS_PER_LONG - e );
    if ( e==0 )  m = 0;  // shift with BITS_PER_LONG is undefined
    return m;
}
// -------------------------

inline umod_t mersenne_factorization(ulong e, factorization *F)
{
    umod_t m = mersenne(e);
    F->make_factorization(m, mersenne_prime_factor_tab);
    return m;
}
// -------------------------


#endif  // !defined HAVE_MERSENNE_H__
