#if !defined  HAVE_NORMALBASIS_H__
#define       HAVE_NORMALBASIS_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bpol/poly-tab.h"  // precomputed normal polynomials
#include "bpol/normal-solvequadratic.h"  // solve x^2+x==c

#include "fxttypes.h"

// bpol/bitpol-normal.cc:
bool bitpol_normal2_q(ulong c, ulong n);
bool bitpol_normal_q(ulong c, ulong n, ulong iq=0, ulong *M=0);

// bpol/normal-mult.cc:
ulong normal_mult(ulong a, ulong b, const ulong *M, ulong n);


#endif  // !defined HAVE_NORMALBASIS_H__
