#if !defined  HAVE_NUM_BITPOL_H__
#define       HAVE_NUM_BITPOL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
//#include "bits/bitsperlong.h"

// bpol/num-bitpol.cc:

//: num_irredpol_tab[n] == number of degree-n binary irreducible polynomials
extern const ulong * const num_irredpol_tab;  // == num_lyndon_tab[]

//: num_primpol_tab[n] == number of degree-n binary primitive polynomials
extern const ulong num_primpol_tab[BITS_PER_LONG+1];

//: num_normalpol_tab[n] == number of degree-n binary normal polynomials
extern const ulong num_normalpol_tab[BITS_PER_LONG+1];


#endif  // !defined HAVE_NUM_BITPOL_H__
